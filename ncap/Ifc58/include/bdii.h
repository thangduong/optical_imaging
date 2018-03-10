

#if !defined(_BDII_H_)
#define _BDII_H_


#ifdef _IFCDLL

#include <BDIIapi.h>
#include <BdtTbl.h>

#else

#define BDII_OK 0

#define BDII_VIDEO_PORT_FORMAT   DWORD
typedef BDII_VIDEO_PORT_FORMAT *PBDII_VIDEO_PORT_FORMAT;

#define BDII_VIDEO_PORT_SETTINGS DWORD
typedef BDII_VIDEO_PORT_SETTINGS *PBDII_VIDEO_PORT_SETTINGS;

typedef void *PBDT_FUNC_TABLE;


typedef unsigned char UINT8;

typedef struct
{
	UINT32 x;
	UINT32 y;
	UINT32 width;
	UINT32 height;
} BDII_ROI, *PBDII_ROI;


typedef struct
{
	UINT32 videoStandard;	
	UINT32 pixelClock;		
	UINT32 hFrontPorch;				
	UINT32 hSync;			
	UINT32 hBackPorch;				
	UINT32 hActive;		
	UINT32 hPolarity;
	UINT32 vFrontPorch;				
	UINT32 vSync;			
	UINT32 vBackPorch;				
	UINT32 vActive;	
	UINT32 vPolarity;
	UINT32 frameType;	
} BDII_VIDEO_FORMAT, *PBDII_VIDEO_FORMAT;

typedef enum {
	BDII_FIELD_PROCESS_ALL,
	BDII_FIELD_PROCESS_ODD_ONLY,
	BDII_FIELD_PROCESS_EVEN_ONLY

} BDII_FIELD_PROCESS_TYPE;


typedef enum {
	BDII_VIDEO_STD_NTSC,
	BDII_VIDEO_STD_PAL,	
	BDII_VIDEO_STD_SECAM,
	BDII_VIDEO_STD_NONE
} BDII_VIDEO_STANDARD_TYPE;




typedef struct
{
	BDII_VIDEO_FORMAT videoFormat;
	UINT32 xmin;	  				
	UINT32 xlen;	  				
	UINT32 ymin;	  				
	UINT32 ylen;	  				
	UINT32 scaleX;					
	UINT32 scaleY;	
	UINT32 fieldProcess;
	UINT32 fieldOrder;
} BDII_ACQ_WINDOW, *PBDII_ACQ_WINDOW;


typedef struct
{
	// xmin
	UINT32 granulX;		// x must be a multiple of this number
	UINT32 minX;			// x cannot be smaller than this number
	UINT32 maxX;			// x cannot be bigger than this number
	
	// ymin
	UINT32 granulY;		// y must be a multiple of this number
	UINT32 minY;			// y cannot be smaller than this number
	UINT32 maxY;			// y cannot be bigger than this number

	// xlen
	UINT32 granulXlen;	// xlen must be a multiple of this number
	UINT32 minXlen;		// xlen cannot be smaller than this number
	UINT32 maxXlen;		// xlen cannot be bigger than this number

	// ylen
	UINT32 granulYlen;	// ylen must be a multiple of this number
	UINT32 minYlen;		// ylen cannot be smaller than this number
	UINT32 maxYlen;		// ylen cannot be bigger than this number

	// Scale.x
	UINT32 scaleGranulX;	// scaleX must be a multiple of this number
	UINT32 scaleMinX;		// scaleX cannot be smaller than this number
	UINT32 scaleMaxX;		// scaleX cannot be bigger than this number
	UINT32 minFactorX;	// xlen/scaleX (scale down) cannot be greater than this number
	UINT32 maxFactorX;	// (scaleX*100)/xlen (zoom up) cannot be greater than this number

	// Scale.y
	UINT32 scaleGranulY;	// scaleY must be a multiple of this number
	UINT32 scaleMinY;		// scaleY cannot be smaller than this number
	UINT32 scaleMaxY;		// scaleY cannot be bigger than this number
	UINT32 minFactorY;	// ylen/scaleY (scale down) cannot be greater than this number
	UINT32 maxFactorY;	// scaleY/ylen (zoom up) cannot be greater than this number
	
} BDII_ACQ_WINDOW_CAPS, *PBDII_ACQ_WINDOW_CAPS;


typedef struct
{
	// Brightness
	INT32 brightnessLinearMin;	// minimum valid register value for brightness 
	INT32 brightnessLinearMax;	// maximum valid register value for brightness 
	INT32 brightnessLinearDefault;// default register value for brightness
	INT32 brightnessPercentMin;	// minimum percentage change in brightness that can be applied (negative % value)
	INT32 brightnessPercentMax;	// maximum percentage change in brightness that can be applied (positive % value)
	INT32 brightnessPercentStep;	// granularity of the percent change. Delta percentage changes 
								// smaller than this number will have no effect on the brightness

	// Contrast
	INT32 contrastLinearMin;		// minimum valid register value for contrast 
	INT32 contrastLinearMax;		// maximum valid register value for contrast 
	INT32 contrastLinearDefault;	// default register value for contrast
	INT32 contrastPercentMin;		// minimum percentage change in contrast that can be applied (positive % value)
	INT32 contrastPercentMax;		// maximum percentage change in contrast that can be applied (positive % value)
	INT32 contrastPercentStep;	// granularity of the percent change. Delta percentage changes 
								// smaller than this number will have no effect on the contrast

	// Saturation
	INT32 saturationLinearMin;	// minimum valid register value for saturation 
	INT32 saturationLinearMax;	// maximum valid register value for saturation 
	INT32 saturationLinearDefault;// default register value for saturation
	INT32 saturationPercentMin;	// minimum percentage change in saturation that can be applied (positive % value)
	INT32 saturationPercentMax;	// maximum percentage change in saturation that can be applied (positive % value)
	INT32 saturationPercentStep;	// granularity of the percent change. Delta percentage changes 
								// smaller than this number will have no effect on the saturation

	// Hue
	INT32 hueLinearMin;			// minimum valid register value for hue 
	INT32 hueLinearMax;			// maximum valid register value for hue 
	INT32 hueLinearDefault;		// default register value for hue
	INT32 hueDegreeMin;			// minimum degree change in hue that can be applied (negative % value)
	INT32 hueDegreeMax;			// maximum degree change in hue that can be applied (positive % value)
	INT32 hueDegreeStep;			// granularity of the degree change. Delta percentage changes 
								// smaller than this number will have no effect on the hue


	// Camera Selector
	UINT32 nbCompositeColor;		// Number of composite color inputs available
	UINT32 nbCompositeMono;		// Number of composite monochrome inputs available
	UINT32 nbYC;					// Number of Y/C inputs available
	UINT32 nbRGB;				// Number of RGB inputs available
	
} BDII_ANALOG_CONTROL_CAPS, *PBDII_ANALOG_CONTROL_CAPS;



typedef struct
{
	UINT32 width;
	UINT32 height;
	UINT32 bytePerPixel;
	BDII_ROI roi;
} BDII_BUFFER, *PBDII_BUFFER;





typedef struct
{
	UINT32 physicalAddress;
	UINT32 blockSize;
} BDII_SG_MEMORY_BLOCK, *PBDII_SG_MEMORY_BLOCK;




#define BDII_EVENT_EXTERNAL_TRIGGER		0
#define BDII_EVENT_END_OF_FRAME			1

// Memory type
#define BDII_MEMORY_CONTIGUOUS      0
#define BDII_MEMORY_SCATTER_GATHER  1

typedef struct
{
	UINT32 event;
	UINT32 memoryType;
	BDII_BUFFER buffer;
	void *virtualAddr;
	void *pMemoryDesc;
	PBDII_SG_MEMORY_BLOCK pSGBlock;
	UINT32 nbBlocks;
	// Common 
	UINT32 *pState;
} BDII_HOST_BUFFER, *PBDII_HOST_BUFFER, **PPBDII_HOST_BUFFER;


#define BDII_CYCLE_MODE_ASYNCHRONOUS            1
#define BDII_CYCLE_MODE_SYNCHRONOUS             2
#define BDII_CYCLE_MODE_SYNCHRONOUS_WITH_TRASH  3
#define BDII_CYCLE_MODE_OFF                     4

typedef struct
{
	UINT32 cycleMode;
	UINT32 nbBuffer;
	PPBDII_HOST_BUFFER ppHost_Buffer;
} BDII_HOST_BUFFER_LIST, *PBDII_HOST_BUFFER_LIST;



typedef struct
{
	UINT32 pixelFormat;
	UINT32 width;
	UINT32 height;
} BDII_IN_VIP, *PBDII_IN_VIP;


typedef struct
{
	UINT32 regId;
	UINT32 value;
} BDII_REG, *PBDII_REG;



typedef struct
{
	UINT8 regId;
	UINT8 value;
} BDII_REG8, *PBDII_REG8;



typedef struct
{
	UINT32 regId;
	//... see Saa7114 manual for register definitions 
	//... and Saa7114.h for structure definition
} BDII_SAA7114_REG, *PBDII_SAA7114_REG;

typedef struct 
{
   BOOL fInitialized;               // TRUE if structure is initialized. Must call BdII_THS8083_Initialize first before using this structure.

} BDII_SAA7114_MODULE, *PBDII_SAA7114_MODULE;



typedef struct
{
	UINT32 regId;
//	... see Ths8083 manual for register definitions 
//	... and Ths8083.h for structure definition
} BDII_THS8083_REG, *PBDII_THS8083_REG;


typedef struct 
{
   BOOL fInitialized;               // TRUE if structure is initialized. Must call BdII_THS8083_Initialize first before using this structure.
   BDII_ACQ_WINDOW acqWindow;       // Current video format definition
   UINT32 outputPixelFormat;        // Output Pixel Format

} BDII_THS8083_MODULE, *PBDII_THS8083_MODULE;

typedef struct
{
	UINT32 hSyncPresent;		
	UINT32 nbPixels;			
	UINT32 nbLines;			// Number of lines per field detected
} BDII_THS8083_STATUS, *PBDII_THS8083_STATUS;

typedef struct
{
	BDII_BUFFER buffer;
	UINT32 physicalAddress;
} BDII_VIDEO_BUFFER, *PBDII_VIDEO_BUFFER, **PPBDII_VIDEO_BUFFER;


typedef struct
{
	UINT32 nbBuffer;
	PBDII_VIDEO_BUFFER pVideoBuffer;
} BDII_VIDEO_BUFFER_LIST, *PBDII_VIDEO_BUFFER_LIST;



#define BDII_XFER_HOST_TO_VIDEO		1	// Host buffer to Video buffer
#define BDII_XFER_VIDEO_TO_HOST		2	// Video buffer to Host buffer

typedef struct
{
	BOOL direction;
	PBDII_HOST_BUFFER_LIST pHostBufferList;
	PBDII_VIDEO_BUFFER_LIST pVideoBufferList;
} BDII_DMA_TRANSFER, *PBDII_DMA_TRANSFER;



#ifdef __cplusplus 
	extern "C" {
#endif

#define NTLIBAPI __declspec(dllexport) __stdcall
		

#define BDII_STATUS DWORD
//
// Global Management Interface
//
BDII_STATUS NTLIBAPI BdII_Init();
BDII_STATUS NTLIBAPI BdII_Get_Driver_Handle(HANDLE *phDriver);



//
// S3 Front-End High-Level Interface
//
BDII_STATUS NTLIBAPI BdII_S3_FE_Init(UINT32 boardIndex);
BDII_STATUS NTLIBAPI BdII_S3_FE_SetWindowAcquisition(UINT32 boardIndex, PBDII_VIDEO_PORT_FORMAT pVideoPortFormat, PBDII_VIDEO_BUFFER_LIST pVideoBufferList);
BDII_STATUS NTLIBAPI BdII_S3_FE_AcquireVideo(UINT32 boardIndex);
BDII_STATUS NTLIBAPI BdII_S3_FE_FreezeVideo(UINT32 boardIndex);
BDII_STATUS NTLIBAPI BdII_S3_FE_AcquireNFrames(UINT32 boardIndex, UINT32 nbFrames);
BDII_STATUS NTLIBAPI BdII_S3_FE_SetColorByteSwap( UINT32 boardIndex, BOOL fColorByteSwap);
BDII_STATUS NTLIBAPI BdII_S3_FE_SetVideoPort(UINT32 boardIndex, PBDII_VIDEO_PORT_SETTINGS pVideoPortSettings);
BDII_STATUS NTLIBAPI BdII_S3_FE_SetVideoPortOffset( UINT32 boardIndex, UINT32 horizontalOffset, UINT32 verticalOffset);


//
// S3 Dma Interface
//
BDII_STATUS NTLIBAPI BdII_S3_DMA_InitTransfer(UINT32 boardIndex, PBDII_DMA_TRANSFER pDmaTransfer, PUINT32 pTransferHandle);
BDII_STATUS NTLIBAPI BdII_S3_DMA_StartAutoTransfer(UINT32 boardIndex, UINT32 transferHandle);
BDII_STATUS NTLIBAPI BdII_S3_DMA_StopAutoTransfer(UINT32 boardIndex, UINT32 transferHandle);
BDII_STATUS NTLIBAPI BdII_S3_DMA_StartTransfer(UINT32 boardIndex, UINT32 transferHandle);
BDII_STATUS NTLIBAPI BdII_S3_DMA_ReleaseTransfer(UINT32 boardIndex, UINT32 transferHandle);



BDII_STATUS NTLIBAPI BdII_Eeprom_ReadData(UINT32 boardIndex, UINT32 offset, void *pData, UINT32 size);
BDII_STATUS NTLIBAPI BdII_Eeprom_WriteData(UINT32 boardIndex, UINT32 offset, void *pData, UINT32 size);

#ifdef __cplusplus 
	}
#endif //__cplusplus




#endif

#endif

