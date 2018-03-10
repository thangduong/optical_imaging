//#include <portdefs.h>
#include <windows.h>
#include <mmsystem.h> 
#include <memory.h>
#include <vfw.h>
#include "stdafx.h"

#define AVIIF_KEYFRAME      0x00000010L // this frame is a key frame.
#define PALVERSION      0x300
#define WIDTHBYTES(i)   ((i+31)/32*4)      /* ULONG aligned ! */


static HPALETTE CreategrayPalette (HDC hDC, HBITMAP hbitmap);
static BOOL GetSysPal(LOGPALETTE FAR *pPal);
static WORD DibNumColors(VOID FAR * pv);
static WORD PaletteSize(VOID FAR * pv);
static char   * FindDIBBits (char   * lpbi);
static BOOL GetBitmapFormat(BITMAPINFOHEADER *alpbi, UINT bits, UINT wXSize,UINT wYSize, UINT logical_bitmap, HANDLE *hclrtbl, HANDLE *hwholeDib);
static void FillDib(BITMAPINFOHEADER *lpbi,BYTE   *buff, UINT logical_bitmap, HANDLE hClrTbl, HANDLE hLDib) ;

typedef struct {
				PAVISTREAM		ps, psCompressed, psused;
				PAVIFILE		pfile;
				HANDLE          hcontext;
				HANDLE          hHeaderAndColorTable;  
				HANDLE          hColorTable;
				HANDLE          hwholeDib;
				UINT            logical_bitmap;
			  } AVI_ACQ_TO_FILE_CONTEXT;	

    

#pragma optimize( "", off )


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CreategrayPalette(LPBITMAPINFOHEADER lpbi)                 *
 *                                                                          *
 *  PURPOSE    : Given a Pointer to a BITMAPINFO struct will create a       *
 *               an identity gray scale GDI palette object                  *
 *                                                                          *
 *  RETURNS    : A handle to the palette.                                   *
 *                                                                          *
 ****************************************************************************/
HPALETTE CreategrayPalette (HDC hDC, HBITMAP hbitmap)
{
    LOGPALETTE far *pPal;
    HPALETTE            hpal = NULL;
    WORD                nNumColors;
    BITMAP bm;          
    WORD                i;  

    LOCALHANDLE Haux;                                  
    
    GetObject(hbitmap,sizeof(BITMAP),(LPSTR)&bm);      // Get an instance of the bitmap from the handle                                            
    
    switch (bm.bmBitsPixel){                           // Find out the number of colors in the bitmap
	case 1:
		nNumColors = 2; 
		break;
	case 4:
		nNumColors = 16;
		break;
	case 8:
		nNumColors = 256;
		break;
	default:
		/* A 24 bitcount DDB has no color table */
		nNumColors = 256;
		break;
	}

	/* Allocate for the logical palette structure */
	Haux = LocalAlloc(LPTR,sizeof(LOGPALETTE) + nNumColors * sizeof(PALETTEENTRY));
	pPal = (LOGPALETTE *) LocalLock(Haux);                      // Get a pointer to the palette
	if (!pPal)
    	return NULL;

	pPal->palNumEntries = nNumColors;                           // Initialize the palette structure members
	pPal->palVersion    = PALVERSION;  

	/* Fill in the palette entries for gray levels */
	for (i = 0; i < nNumColors; i++){
	 	pPal->palPalEntry[i].peRed   = pPal->palPalEntry[i].peGreen = pPal->palPalEntry[i].peBlue = (BYTE)i;
	    pPal->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
	    }
	
	/* Overwrite the system colors in our proposed logical palette with Windows System colors, to make it an 
	   identity palette */

//	if (GetSysPal(pPal) == FALSE)
//		MessageBox(NULL,"Can't make identity palette","Error",MB_OK);    
		
	/*Now create a logical color palette.*/		
	hpal = CreatePalette(pPal);
		
	LocalUnlock(Haux);
	LocalFree(Haux);        
        
    return hpal;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetSysPal(LOGPALETTE far *pPal)  					        *
 *                                                                          *
 *  PURPOSE    : Given a Pointer to a palette structure,				    *
 * 				 set the system colors entries in the  					    *
 * 				 structure palette structure to Windows system colors       *
 *				 to obtain an identity palette. 				 			*
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise                        *
 *                                                                          *
 ****************************************************************************/
static BOOL GetSysPal(LOGPALETTE far *pPal)
{
   HDC hdc = GetDC(NULL);
   int nNumSysColors, nNumPalColors, half_sys_colors;
   
   nNumPalColors = GetDeviceCaps(hdc, SIZEPALETTE);  // Get size of palette from VGA Windows driver
   nNumSysColors = GetDeviceCaps(hdc, NUMRESERVED);  // Get number of reserved system colors from VGA driver
   half_sys_colors = nNumSysColors / 2;

   // Get the entries in the system palette for the first half of system colors (10 out of 20) and place them
   // in the corresponding entries in our logical palette.                          
   // E.g. : get system palette entries 0 to 9 and place the in the 0 to 9 entries in our palette
   if (GetSystemPaletteEntries(hdc,0, half_sys_colors, &(pPal->palPalEntry[0])) == 0) {
       ReleaseDC(NULL,hdc);
       return(FALSE);
       }

   // Get the entries in the system palette for the second half of system colors (10 out of 20) and place them
   // in the corresponding entries in our logical palette.                                       
   // E.g. : get system palette entries 246 to 255 and place the in the 246 to 255 entries in our palette
   if (GetSystemPaletteEntries(hdc,nNumPalColors - half_sys_colors, half_sys_colors, 
         					&(pPal->palPalEntry[pPal->palNumEntries - half_sys_colors])) == 0) {
      ReleaseDC(NULL,hdc);   					
      return(FALSE); 
      }
   ReleaseDC(NULL,hdc);
   return TRUE;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : read_from_AVI_file(........)   					        *
 *                                                                          *
 *  PURPOSE    : Given a Pointer to a   buffer,						    *
 * 				 it reads a movie from the AVI file into the buffer		    *
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise                        *
 *                                                                          *
 ****************************************************************************/

BOOL  WINAPI read_from_AVI_file(UINT lstart,DWORD n_frames, LPSTR fname, 
									BYTE   *buff, BITMAPINFOHEADER *bi)
{               
 HRESULT		hr;
 PAVIFILE		pfile = NULL;
 PAVISTREAM		ps = NULL;
 BOOL			ret = TRUE;
 DWORD          ind, ind1, widthbytes;
 PGETFRAME	    gapgf;
 BITMAPINFOHEADER   *lpbi;
 UINT           i,j;
 BYTE	  *	lpBits; 	
 char			lfname[80];
 
 strcpy(lfname,fname);
 if (strchr(lfname,'.') == NULL)
	 strcat(lfname,".avi");
                                                                       
     AVIFileInit();                       // Initialize AVI DLL
     
    // Open the movie file for reading....
    hr = AVIFileOpen(&pfile,			    // returned file pointer
	  		          lfname,		 	    // file name
		       			  0,	    		// mode to open file with (Reading)
		       	  	  NULL);			    // use handler determined from file extension....
						    
    if (hr != AVIERR_OK) {
    	ret = FALSE;
		goto error1;
    }
                                                          
    //Get a pointer to the video stream #0 structure from the AVI File                                                     
    hr = AVIFileGetStream(pfile,&ps,streamtypeVIDEO,0);   
    
    //Prepare to decompress data from stream : get a GETFRAME object pointer
	gapgf = AVIStreamGetFrameOpen(ps, NULL);                                
	
    for ( i=lstart, ind = 0; i<(lstart+n_frames); i++ ) {
		// Could actually return an LPBI for invalid frames
		// so we better force it to NULL.
		// 
		//Decompress data and put it into the DIB pointed to by lpbi
		if (gapgf && i >= (UINT)AVIStreamStart(ps)) 
		    lpbi = (BITMAPINFOHEADER   *)AVIStreamGetFrame(gapgf, i);      
		else
		    lpbi = NULL;

		if (lpbi) {
		    if (buff) {
		    	widthbytes = lpbi->biWidth * (DWORD)lpbi->biBitCount  / 8L;  //Width of bitmap in bytes
		    	lpBits = (BYTE*) FindDIBBits((char   *)lpbi);      		    	// Find the beginning of the bits         

	        	ind1 = lpbi->biSizeImage - widthbytes;                                                
	        	// Reverse the bitmap.
		    	for (j = 0 ; j < (UINT)lpbi->biHeight; j++) {
			    	memcpy(buff+ind,lpBits+ind1, widthbytes); 
			    	ind += widthbytes;
			    	ind1 -= widthbytes;
			    	}
			    }	
            }
            
            memcpy(bi,lpbi,sizeof(BITMAPINFOHEADER));        // Copy the BITMAPINFO header into the passed 
            												   // pointer
        }


error1:                      
	AVIStreamRelease(ps);                   // This unlocks and frees the memory allocated to return the bitmap
	 if (gapgf) 
	    AVIStreamGetFrameClose(gapgf);
    if (pfile)
		AVIFileClose(pfile);
    AVIFileExit();
   return(ret);	
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : PaletteSize(pv)				   					        *
 *                                                                          *
 *  PURPOSE    : Returns the size of the palette in bytes.          		*
 *				 The <pv> parameter can point to a BITMAPINFOHEADER         *
 *				 or BITMAPCOREHEADER structure.						    	*
 *                                                                          *
 ****************************************************************************/
static WORD PaletteSize(VOID FAR * pv)          // Pointer to the bitmap info header structure
{
    #define lpbi ((LPBITMAPINFOHEADER)pv)

    WORD    NumColors;

    NumColors = DibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return NumColors * sizeof(RGBTRIPLE);
    else
        return NumColors * sizeof(RGBQUAD);

    #undef lpbi
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : DibNumColors(pv)				   					        *
 *                                                                          *
 *  PURPOSE    : Returns the number of palette entries in the palette 		*
 *				 The <pv> parameter can point to a BITMAPINFOHEADER         *
 *				 or BITMAPCOREHEADER structure.						    	*
 *                                                                          *
 ****************************************************************************/
static WORD DibNumColors(VOID FAR * pv)          // Pointer to the bitmap info header structure
{
    #define lpbi ((LPBITMAPINFOHEADER)pv)
    #define lpbc ((LPBITMAPCOREHEADER)pv)

    int nBitCount;

    /* With a BITMAPINFOHEADER structure, the number of palette entries
     * is in biClrUsed; otherwise, the count depends on the number of bits
     * per pixel.
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER))
    	{
        if(lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;

        nBitCount = lpbi->biBitCount;
    	}
    else
        nBitCount = lpbc->bcBitCount;

    switch (nBitCount)
    {
        case 1:
            return 2;

        case 4:
            return 16;

        case 8:
            return 256;

        default:
            return 0;
    }

    #undef lpbi
    #undef lpbc
}

/**********************************************************
 ***  FindDIBBits, return the entire DIB
 **********************************************************/

static char   * FindDIBBits (char   *lpbi)
{
   return (lpbi + *(LPDWORD)lpbi + PaletteSize (lpbi));
}





/****************************************************************************
 *                                                                          *
 *  FUNCTION   : acquire_to_AVI_file(........)		   				        *
 *                                                                          *
 *  PURPOSE    : Saves a video frame to AVI file							*
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise					    *
 *                                                                          *
 ****************************************************************************/
BOOL  WINAPI acquire_to_AVI_file(DWORD context,DWORD frame_seqnum,BYTE   *buff) 
{

    AVI_ACQ_TO_FILE_CONTEXT *avi_context;	                          
    BITMAPINFOHEADER *alpbi; 
    BITMAPINFOHEADER   *dibptr;
    HCURSOR  hCursor; 
    HRESULT hr;
    BOOL ret = TRUE;
    
    avi_context = (AVI_ACQ_TO_FILE_CONTEXT *)context;            // Cast to a context pointer
    
    alpbi = (BITMAPINFOHEADER *)GlobalLock(avi_context->hHeaderAndColorTable);  //Get a pointer to color table
                                                 
    // Fill the Dib bits with the contents of buff
    FillDib(alpbi,buff,avi_context->logical_bitmap,avi_context->hColorTable, avi_context->hwholeDib); 
        
    dibptr = (BITMAPINFOHEADER   *)GlobalLock(avi_context->hwholeDib); //Get a pointer to the whole Dib
    if (!dibptr) {
       ret = FALSE; 
       goto error; 
       }
    
    hCursor = SetCursor(LoadCursor(NULL,IDC_WAIT));          //Put the glass-hour indicator
    ShowCursor(TRUE);

    // Now write out each video frame.
	hr = AVIStreamWrite(avi_context->psused,	// stream pointer
			      		frame_seqnum,		    // time of this frame
			      		1,		    			// number of frames to write
			      		(LPBYTE) dibptr +   	// pointer to data
				  		dibptr->biSize  +
           				dibptr->biClrUsed * sizeof(RGBQUAD),
			      		dibptr->biSizeImage,			// size of this frame
			      		AVIIF_KEYFRAME,	   				// flags....
			      		NULL, NULL);                    // Return values not needed
			      
    if (hr != AVIERR_OK)
        ret = FALSE;
error:	
    ShowCursor(FALSE);                    // Restore cursor
    SetCursor(hCursor);                     
    GlobalUnlock(avi_context->hHeaderAndColorTable);       // Unlock color table                            
    GlobalUnlock(avi_context->hwholeDib);                  // Unlock Dib
    return(ret);
}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetBitmapFormat(........)			   				        *
 *                                                                          *
 *  PURPOSE    : Initialize context, allocate memory blocks, 			    *
 *				 create gray level palette.        							*
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise					    *
 *                                                                          *
 ****************************************************************************/
	
static BOOL GetBitmapFormat(BITMAPINFOHEADER *alpbi, UINT bits, UINT wXSize,UINT wYSize, UINT logical_bitmap, HANDLE *hclrtbl, HANDLE *hwholeDib)
{                                                                     
    HDC         hdc ;
    HBITMAP     hbitmap;      
    BITMAP      bm;              
    HANDLE      haux;
    HPALETTE    hpal=NULL, hpalT;
    BITMAPINFOHEADER    bi;
    UINT        a;  
    int         retdib,nLDibColors;  	  // How many colors in logical DIB
    LPBITMAPINFOHEADER  lpPalClrTbl;      // Pointer to the header plus the color table as palette entries.
    RGBQUAD FAR *       lpLDibRGB;        // Temporary Pointer to logical DIB color table
    PALETTEENTRY        peT;
    WORD n;  
    DWORD dwLDibLen;
    
    hdc = GetDC(NULL);
    
    hbitmap = CreateBitmap(wXSize,wYSize,1,bits,NULL);     //Get handle to a bitmap with requested dimensions
	if (!hbitmap) {
	    ReleaseDC(NULL,hdc);              
        return FALSE;
        }
        
    if (bits <= 8) {
    	hpal = CreategrayPalette (hdc, hbitmap);           // Create a gray palette if acquisition is 8 bits
    	if (hpal == NULL)
        	hpal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
        GetObject(hpal,sizeof(nLDibColors),(LPSTR)&nLDibColors);  //Get amount of colors in palette object
		nLDibColors &= 0x0000fffful;
    	}
    else
       logical_bitmap = 0; 
       	
    GetObject(hbitmap,sizeof(bm),(LPSTR)&bm);               // Get an instance of the bitmap


    if (bits <= 8) {
	    if (nLDibColors > 256)  /* Truncate palette entries at 256 if logical palette has more than 256 entries */
        nLDibColors = 256;
	      }
    else  
        nLDibColors = 0;  

    if (bits == 0)    /* If bit count is zero, fill in bit count based on number of colors in palette */
        bits = nLDibColors > 16 ? 8 : 4;

    // Initialize an instance of a DIB header to match the DDB dimensions and chanracteristics
    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = bits;
    bi.biCompression        = BI_RGB;
    bi.biSizeImage          = WIDTHBYTES((DWORD)bm.bmWidth * bits) * bm.bmHeight;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = nLDibColors;
    bi.biClrImportant       = 0;

    // Get a handle to the a memory block containing the header and the color table
    // as palette indices. This is needed for re-mapping pixels if log-bitmap flag is on.
    // If this handle is obtained successfully, it will be returned to the calling function in hclrtbl
    haux = GlobalAlloc(GMEM_FIXED,bi.biSize + nLDibColors * sizeof(RGBQUAD)); 
    lpPalClrTbl = (BITMAPINFOHEADER *)GlobalLock(haux);        //Make a pointer to it.
    if (!lpPalClrTbl) {
        ReleaseDC(NULL,hdc);              
        return FALSE;                     
        }
    *hclrtbl = haux;    

    if (bits <= 8) {
    	hpalT = SelectPalette(hdc,hpal,FALSE);
    	a = RealizePalette(hdc);
        }


    *alpbi = bi;                //Copy headers. alpbi will hold the colors table as RGB values.
    
   /* Now copy the RGBs in the logical palette to the DIB color table.*/
    lpLDibRGB = (RGBQUAD FAR *)((char far *)alpbi + (WORD)alpbi->biSize); //Pointer to the color table in
        																	  // the Dib

    for (n=0; n<alpbi->biClrUsed; n++, lpLDibRGB++)
            {
            GetPaletteEntries(hpal,n,1,&peT);    // Retrieve palette entries into the currently realized palette

            lpLDibRGB->rgbRed      = peT.peRed;      //Assign the logical palette entries to
            lpLDibRGB->rgbGreen    = peT.peGreen;    // the Dib color table
            lpLDibRGB->rgbBlue     = peT.peBlue;
            lpLDibRGB->rgbReserved = (BYTE)0;
            }

    /* Get the color table as palette indices. With DIB_PAL_COLORS flag, the color table is
      filled with logical palette indices. */

    if (logical_bitmap) {
    	*lpPalClrTbl = bi;               // Copy header
    	
    	retdib = GetDIBits(hdc,                    // Device context
        	 	       hbitmap,                    // Bitmap we're copying
            	             0,                    // Starting scan line
             (WORD)bi.biHeight,   				   // Number of scan lines to copy
              	  		  NULL,                    // No pointer to bits
     (LPBITMAPINFO)lpPalClrTbl,  				   // Receives DDB color table
               DIB_PAL_COLORS);    	               // Usage--copy indices into the 
        }                          			       // currently realized logical palette

    
    // Allocate memory to hols a complete Dib, including header, color table and bits.
    dwLDibLen = alpbi->biSize + PaletteSize(alpbi) + alpbi->biSizeImage;
       	
    *hwholeDib = GlobalAlloc(GMEM_MOVEABLE,dwLDibLen);
    if (!(*hwholeDib)) {
    	ReleaseDC(NULL,hdc);              
        return FALSE;
        }

    if (logical_bitmap == 1)
       SelectPalette(hdc,hpalT,FALSE);
       
   	ReleaseDC(NULL,hdc);              
    GlobalUnlock(haux);
    return TRUE;
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : cleanup_acquire_to_AVI_file(........)				        *
 *                                                                          *
 *  PURPOSE    : De-allocates buffers, closes streams and files				*
 *                                                                          *
 ****************************************************************************/

void  WINAPI  cleanup_acquire_to_AVI_file(DWORD context)
{ 
    AVI_ACQ_TO_FILE_CONTEXT *avi_context;	                          
	HANDLE hcontext;   
    avi_context = (AVI_ACQ_TO_FILE_CONTEXT *)context;
    
    if (avi_context->ps)
	AVIStreamClose(avi_context->ps);

    if (avi_context->psCompressed)
	AVIStreamClose(avi_context->psCompressed);

    if (avi_context->pfile)
	AVIFileClose(avi_context->pfile);

    AVIFileExit();             
    
    if (avi_context->hHeaderAndColorTable) {
	    GlobalFree(avi_context->hHeaderAndColorTable);                                              
        }
        
    if (avi_context->hColorTable) {
	    GlobalFree(avi_context->hColorTable);                                              
        }    

    if (avi_context->hwholeDib) {
	    GlobalFree(avi_context->hwholeDib);                                              
        }    
    
	hcontext = avi_context->hcontext;
    if (hcontext) {
	    GlobalUnlock(hcontext);
	    GlobalFree(hcontext);                                              
	}

}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : FillDib(........)			   				 		        *
 *                                                                          *
 *  PURPOSE    : fills the Dib bits with the contents of buff 			    *
 *                                                                          *
 ****************************************************************************/

static void FillDib(BITMAPINFOHEADER *lpbi,BYTE   *buff, UINT logical_bitmap, 
				    HANDLE hColorTable, HANDLE hLDib) 
{
    WORD  *          lpDDBClrTbl;  // Pointer to DIB color table
    BITMAPINFOHEADER    *lpLDib;       // Pointer to logical DIB header
    BYTE   *         lpLDibBits;  
    DWORD               dwLDibLen;    
    HDC                 hdc = NULL;
    DWORD               dw;
    UINT j;  
    DWORD ind1, ind, widthbytes;

    dwLDibLen = lpbi->biSize + PaletteSize(lpbi) + lpbi->biSizeImage;  // Size of logical DIB

    if (!hLDib)
        return;
   
    lpLDib = (BITMAPINFOHEADER*) GlobalLock(hLDib);     // Get a pointer to the block allocated in save setup
    											 // for the whole Dib

    memcpy(lpLDib,lpbi,dwLDibLen-lpbi->biSizeImage);   // Copy the header and color table in RGB format
    													// into the header of the whole Dib chunk
    
    // Get a Pointer to logical DIB bits
    lpLDibBits = (BYTE   *)lpLDib + (WORD)lpLDib->biSize + PaletteSize(lpLDib); 
    
    // Reverse the bits in buff to upside down Dib format
    ind = 0;
	widthbytes = lpLDib->biWidth * (DWORD)lpLDib->biBitCount  / 8L;
	ind1 = lpLDib->biSizeImage - widthbytes;
		    for (j = 0 ; j < (UINT)lpLDib->biHeight; j++) {
			    memcpy(lpLDibBits+ind,buff+ind1, widthbytes); 
			    ind += widthbytes;
			    ind1 -= widthbytes;
			    }

    /* Now if movie is to be saved as palette indices, we must re-map the pixels */       
    /* Convert the DIB bits from indices into the color table (which
     * contains indices into the logical palette) to direct indices
     * into the logical palette.
     *
     * lpDDBClrTbl   Points to the DIB color table, which is a WORD array of
     *               logical palette indices.
     *
     * lpLDibBits    Points to the DIB bits. Each DIB pixel is a index into
     *               the DIB color table.
     */        
     
     if (logical_bitmap == 1) {
		lpDDBClrTbl = (WORD FAR *) (LPSTR)GlobalLock(hColorTable) + (WORD)lpLDib->biSize;

        if (lpbi->biBitCount == 8) {
           for (dw = 0; dw < lpbi->biSizeImage; dw++, ((BYTE   *)lpLDibBits)++)
               *lpLDibBits = (BYTE)lpDDBClrTbl[*lpLDibBits];
        }
        else { // biBits == 4
           for (dw = 0; dw < lpbi->biSizeImage; dw++, ((BYTE   *)lpLDibBits)++)
               *lpLDibBits = (BYTE)(lpDDBClrTbl[*lpLDibBits & 0x0F] |
                             (lpDDBClrTbl[(*lpLDibBits >> 4) & 0x0F] << 4));
        }
    	GlobalUnlock(hColorTable);           
    }                    
        
    GlobalUnlock(hLDib);

}



/****************************************************************************
 *                                                                          *
 *  FUNCTION   : setup_acquire_to_AVI_file(........)   				*
 *                                                                          *
 *  PURPOSE    : Prepare the AVI file to receive data						*
 *                                                                          *
 *  RETURNS    : a context id for the AVI save session, 0 if failure        *
 *                                                                          *
 ****************************************************************************/

DWORD WINAPI  setup_acquire_to_AVI_file(LPSTR fname, UINT dx,UINT dy,UINT bits, DWORD fps,
											UINT logical_bitmap,UINT compress_flag,
                                 			DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, 
                                 			DWORD dwKeyFrameEvery)
{   
    AVI_ACQ_TO_FILE_CONTEXT *avi_context;	                          
    HANDLE hcontext, hHeaderColorTable, haux, haux1;
    BITMAPINFOHEADER *alpbi;
    AVISTREAMINFO strhdr;
    PAVIFILE		pfile = NULL;
    PAVISTREAM		ps = NULL, psCompressed = NULL, psused = NULL;
    AVICOMPRESSOPTIONS	opts;
    HRESULT		hr;
    LONG sil;
	char			lfname[80];
 
	strcpy(lfname,fname);
	if (strchr(lfname,'.') == NULL)
		strcat(lfname,".avi");

    hcontext = GlobalAlloc(GMEM_DISCARDABLE ,sizeof(AVI_ACQ_TO_FILE_CONTEXT));  //Allocate mem for save context
    
    if (!hcontext) {
 	    MessageBox(NULL,"Cannot allocate context memory","Error",MB_OK);
        return(FALSE); 
      }

	avi_context = (AVI_ACQ_TO_FILE_CONTEXT *) GlobalLock(hcontext);            //Get a pointer to the context                                  


    AVIFileInit();				//Initialize AVI stuff
    
    // Open the movie file for writing....
    //
    hr = AVIFileOpen(	 &pfile,			    // returned file pointer
	 			          lfname,		    	// file name
		   OF_WRITE | OF_CREATE,	    		// open file for writing, delete previously existent one if any.
		   			      NULL);			    // use handler determined from file extension....
						    
    if (hr != AVIERR_OK) {
    	cleanup_acquire_to_AVI_file((DWORD)avi_context); 
    	return(0);
	}

    // Set up the stream header information    
    memset(&strhdr, 0, sizeof(strhdr));
    strhdr.fccType                = streamtypeVIDEO;		// stream type
    strhdr.fccHandler             = 0;                      // Compressor handler
    strhdr.dwScale                = 1;                      //dwRate \ dwScale = samples per second.
    														// for video streams it must me frames\sec
    strhdr.dwRate                 = fps;		    		// frames per second
    strhdr.dwSuggestedBufferSize  = 0;  //Buffer used to playback
 															// Should be set to largest chunk in AVI file	
    SetRect(&strhdr.rcFrame, 0, 0,(int) dx-1,(int) dy-1);	 // dimensions of destination rectangle for video frame

    // Create the stream;
    hr = AVIFileCreateStream(pfile,&ps,&strhdr);	    // Get pointer to new stream in ps
    if (hr != AVIERR_OK) {
    	cleanup_acquire_to_AVI_file((DWORD)avi_context);
    	return(0);
    	}

    if (compress_flag) {                                // If compression required, set up options
       memset(&opts, 0, sizeof(opts));
                                                   
       opts.dwFlags = AVICOMPRESSF_VALID |AVICOMPRESSF_KEYFRAMES | AVICOMPRESSF_DATARATE;
       opts.fccType = streamtypeVIDEO;
       opts.fccHandler = fccHandler;                       //E.g. : mmioFOURCC('M', 'R', 'L', 'E');
       opts.dwQuality = dwQuality;                         //Quality factor 0 to 10000
       opts.dwKeyFrameEvery = dwKeyFrameEvery;             // Maximum period between key frames
       opts.dwBytesPerSecond = dwBytesPerSecond;           // Data rate to be used by compressor
    
       hr = AVIMakeCompressedStream(&psCompressed, ps, &opts, NULL); //Get a pointer to a compressed stream
       															// created from the uncompressed stream ps.
       if (hr != AVIERR_OK) {
		   cleanup_acquire_to_AVI_file((DWORD)avi_context); 
		   return(0);                                                                            
    	   }
        }    


    // Allocate memory to hold the BITMAPINFOHEADER plus the color table.
    hHeaderColorTable = GlobalAlloc(GMEM_DISCARDABLE,sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)); 
    
    if (!hHeaderColorTable) {
		cleanup_acquire_to_AVI_file((DWORD)avi_context); 
 	    MessageBox(NULL,"Cannot allocate save memory","Error",MB_OK);
        return(0); 
      }

    // Make a pointer to the BITMAPINFOHEADER plus the color table = alpbi.
    //This will hold the color table as RGB values!
	alpbi = (BITMAPINFOHEADER *) GlobalLock(hHeaderColorTable);                                              
	
	// Initialize context, allocate memory blocks, create gray level palette.                              
    if (GetBitmapFormat(alpbi, bits,dx,dy, logical_bitmap, &haux, &haux1) == FALSE) {
       	GlobalUnlock(hHeaderColorTable);
		cleanup_acquire_to_AVI_file((DWORD)avi_context); 
   	    MessageBox(NULL,"Cannot initialize bitmap","Error",MB_OK);
        return(0); 
	}
    avi_context->hColorTable = haux;              		// Handle to color table as palette indices
    avi_context->logical_bitmap = logical_bitmap;       // Logical Bitmap flag                              
    avi_context->hwholeDib = haux1;                     // Handle to the whole Dib.
    
    psused = (compress_flag) ? psCompressed : ps;       // Pointer to the stream to use.
    
    // Set the stream format for AVI File.
    hr = AVIStreamSetFormat(psused, 0, alpbi,	    // stream format
			           		alpbi->biSize +      //Format size
			          		alpbi->biClrUsed * sizeof(RGBQUAD));      
	sil = GetScode(hr);		       
    if (hr != AVIERR_OK) {                               
    	GlobalUnlock(hHeaderColorTable);
		cleanup_acquire_to_AVI_file((DWORD)avi_context); 
		return(0);
    	}

    // Initialize all member of context structure
    avi_context->psused = psused;
    avi_context->ps = ps;
    avi_context->psCompressed = psCompressed;
    avi_context->pfile = pfile;
    avi_context->hcontext = hcontext;
    avi_context->hHeaderAndColorTable = hHeaderColorTable;

    GlobalUnlock(hHeaderColorTable);  
    
    return ((DWORD)avi_context);
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : save_to_AVI_file                                           *
 *                                                                          *
 *  PURPOSE    : This routine will save the movie pointed to by buff into   *
 				 the specified AVI file.                                    *
 *                                                                          *
 *  RETURNS    : TRUE if successful, FALSE otherwise.                       *
 *                                                                          *
 ****************************************************************************/
BOOL  WINAPI save_to_AVI_file(DWORD n_frames,UINT logical_bitmap, LPSTR fname, BYTE   *buff, 
                                 UINT dx,UINT dy,UINT bits, DWORD fps,UINT compress_flag,
                                 DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, DWORD dwKeyFrameEvery)
{
    DWORD context, bitmapsize,ind,i;
    BOOL ret = TRUE;
 
// Prepare the context for AVI file saving
    context = setup_acquire_to_AVI_file(fname,dx,dy,bits,fps,logical_bitmap,compress_flag,dwBytesPerSecond, 
                                        fccHandler,dwQuality,dwKeyFrameEvery);
    
    if (context == 0)
    	return(FALSE);
    	
    bitmapsize = (DWORD)dx * (DWORD)dy * (DWORD)bits / 8L;
    
    for (i = 0, ind = 0 ; i < n_frames ; i++) {                // i is the frame sequence number            
    	if (!(ret = acquire_to_AVI_file(context,i,buff+ind)))  // Save this frame into the open AVI file
       		break;     
       	ind += bitmapsize;	                         // Increment the index into buff to get next video frame
       	}	
    cleanup_acquire_to_AVI_file(context);
    return(ret);   	
}


