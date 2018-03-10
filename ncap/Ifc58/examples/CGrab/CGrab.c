/******************************************************************************
 *
 * MODULE
 *    CGrab.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CGrab/CGrab.c $
 *    $Revision: 1.1 $
 *    $Modtime: 7/27/01 10:57a $
 *
 * ABSTRACT
 *    IFC C-wrapper function Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/



#include <stdio.h>
#include <ifcapi.h>


main(int argc,char **argv)
{
	DWORD count;
	short i,j,dx,dy,depth;

	pCICapMod capmod;
	pCICamera cam;
	char *modName=NULL;
	char configFile[80];
	FILE* fp;
	
	BYTE * dest, * pdest;
	
	CAM_ATTR attr;

	if ( argc > 1 ) {
		modName = argv[1];
		sprintf(configFile,"%stest.txt",modName);
	}
	else {
		strcpy(configFile,"C:\\oi\\software\\DalsaCAD1-256T.txt");
	}

	if (!(capmod=IFC_IfxCreateCaptureModule(modName,0,configFile))) {
		if (!(capmod=IFC_IfxCreateCaptureModule(modName,0,NULL))) {
			printf("No Image Capture Module detected");
			exit(0);
		}
		// If user config file not found, add all camera definitions in camera database directory
		CICapMod_ProcessCameraFilesInDir(capmod,"camdb",TRUE);
	}
	cam = CICapMod_GetCam(capmod,0);
	// Get the camera's basic attributes

	CICamera_GetAttr(cam,&attr,TRUE);
		
	depth = (short)attr.dwBytesPerPixel;
	dx = (short)attr.dwWidth;
	dy = (short)attr.dwHeight;
	dest = malloc(depth * dx * (dy + 1));
	pdest = dest;

	/* Fill up the buffer with known pattern */
	for(i=0;i< dy+1;i++)
		for(j=0;j< dx*depth; j++)
			*pdest++ = 0xAA;

	/* Acquire single image using SeqSnap function into dest buffer */
	CICamera_SeqSnap(cam,dest,1,0,0,dx,dy,1000);

	fp = fopen("c:\\oi\\junkdata\\chamber.rlbothon.dat", "wb");

	/* See what we got */
	printf("Host buffer @Begin = %x, %x, %x, %x\n",dest[0],dest[1],dest[2],dest[3]);
	pdest = dest + dx*dy*depth / 2  - 4;
	printf("Host buffer @Middle = %x, %x, %x, %x\n",pdest[0],pdest[1],pdest[2],pdest[3]);
	pdest = dest + dx*dy*depth - 4;
	printf("Host buffer @End = %x, %x, %x, %x\n",pdest[0],pdest[1],pdest[2],pdest[3]);
	printf("Host buffer @Unfilled = %x, %x, %x, %x\n",pdest[4],pdest[5],pdest[6],pdest[7]);

	/* Use Snap_HostBuf to get image into dest buffer */
	for(count=0;count<2000;count++){
		pdest = dest;

		/* Fill up known */
		for(i=0;i< dy+1;i++)
			for(j=0;j< dx*depth; j++)
				*pdest++ = 0xAA;

		CICamera_Snap_HostBuf(cam, dest,0, 0, dx,dy);
		fwrite(dest, 256*256,2,fp);

		/* See what we got */
		printf("Host buffer @Begin = %x, %x, %x, %x\n",dest[0],dest[1],dest[2],dest[3]);
		pdest = dest + dy*dx*depth / 2  - 4;
		printf("Host buffer @Middle = %x, %x, %x, %x\n",pdest[0],pdest[1],pdest[2],pdest[3]);
		pdest = dest + dy*dx*depth - 4;
		printf("Host buffer @End = %x, %x, %x, %x\n",pdest[0],pdest[1],pdest[2],pdest[3]);
		printf("Host buffer @Unfilled = %x, %x, %x, %x\n",pdest[4],pdest[5],pdest[6],pdest[7]);
	}

	fclose(fp); 
	free(dest);

	IFC_IfxDeleteCaptureModule(capmod);
}

