
#ifndef __VidSrcT_h__
#define __VidSrcT_h__




#ifdef IVS_IMPORT_ONLY
#define IVS_EXT_API  __declspec(dllimport)
#else
#define IVS_EXT_API  __declspec(dllexport)
#endif

#define IVSAPI __stdcall

#define IVSCALL IVS_EXT_API IVSAPI


#define VS_CONFIG_FILE_PARM_NAME "ConfigFile"
#define VS_PORT_NUM_PARM_NAME "PortNum"


typedef void *pVOID;
typedef BYTE *pBYTE;
typedef WORD *pWORD;

typedef DWORD HCProcThread;

#if defined __midl && !defined _ODL
typedef long DWORD;
#endif


#include <VnVar.h>
#include <disptype.h>

struct IVideoSrc;
struct IDistribOS;


typedef struct VSPARAM {
	CVSStr parmName;
	CVnVar parmVal;
} VSPARAM;




#define MAX_NUM_VS_CREATE_PARAMS 6

typedef struct VSPROPS {
	CVSStr productName; 	// Name of the product/model which the Video Source, e.g., "Imaging Tech. PCDig"
	CVSStr installedName; // Name assigned to video source when installed, e.g., "ITI.PCD.0"
	DWORD realTimeFeed;
	CVSStr driverDllName;
	DWORD attributeMask;
	DWORD numCreateParams;
	VSPARAM createParams[MAX_NUM_VS_CREATE_PARAMS];
} VSPROPS;

typedef VSPROPS *LPVSPROPS;


// Interrupt Events supported by Image Capture Modules
typedef enum VS_ICAP_INTR_EVENT {
	VS_ICAP_INTR_VB, 		// vertical blank 
	VS_ICAP_INTR_ODD_VB,	// odd vertical blank 
	VS_ICAP_INTR_EVEN_VB,	// even vertical blank 
	VS_ICAP_INTR_AM,		// interrupt from AM daughter module
	VS_ICAP_INTR_TRIG,		// interrupt on start of triggered acquire
	VS_ICAP_INTR_ACQ_ADRS, // interrupt when the board peculiar set acquisition address occurs
	VS_ICAP_INTR_ACQ,		// interrupt on End of Acquisition
	VS_ICAP_INTR_BMDONE,	// interrupt when a BM transfer is complete
	VS_ICAP_INTR_INPORT,	// interrupt when the External In port line goes active
	VS_ICAP_INTR_END_TRIG,	// interrupt on end of triggered acquire
	VS_ICAP_INTR_SOACQ,	// interrupt on Start of Acquisition
	VS_ICAP_INTR_EOF,		// interrupt on End of Frame


	VS_ICAP_INTR_MAX_EVENT  /* MUST be last !!! */
} VS_ICAP_INTR_EVENT;

typedef DWORD VS_INTREVENT;
#define VS_INTREVENT_INVALID 0xfffffffful

typedef LONG HVSINTERRUPT;


typedef enum VS_INTR_WAIT_TYPE {
	VS_INTR_TIMED_OUT,
	VS_INTR_SIGNALED,
	VS_EVENT1_SIGNALED,
	VS_EVENT2_SIGNALED,
	VS_EVENT3_SIGNALED,
	VS_INTR_ERR_NOT_EVENT_SETTING
} VS_INTR_WAIT_TYPE;



typedef enum VS_DEPTH {
	VS_PIX8        = 8,
	VS_PIX10       = 10,
	VS_PIX12       = 12,
	VS_PIX16       = 16,
	VS_PIX24       = 24,
	VS_PIX32       = 32
} VS_DEPTH;

typedef enum VS_COLOR {
	VS_MONO,
	VS_RED,
	VS_GREEN,
	VS_BLUE,
	VS_RGB,
	VS_RGB_PACK24,
	VS_MONO_WORD_LO,
	VS_MONO_WORD_HI,
	VS_RGB_PLANAR,
	VS_aRGB_PLANAR,
	VS_YCRCB,
	VS_YCRCBMONO,
	VS_YUV420PLANAR,
	VS_NUM_COLOR_MODES	// Always keep last
} VS_COLOR;

typedef DWORD HVSGRAB;

typedef DWORD HVnObject;


/* Field status defines */
typedef enum VS_FIELD_STATUS {
	VS_EVEN_FIELD,                       /* Field status is even */
	VS_ODD_FIELD,                        /* Field status is odd */
	VS_NEXT_FIELD                       /* Next field acquisition */
} VS_FIELD_STATUS;

/* Scan Mode status defines */
typedef enum VS_ILACE {
	VS_NILACED,    /* Scan Mode is No interlace */
	VS_ILACED		/* Scan Mode is Interlaced */
} VS_ILACE;	


typedef enum VS_RECORD_PARM {
	VS_NUM_IFRAMES,
	VS_MAX_FRAME_RATE,
	VS_RP_WIDTH,
	VS_RP_HEIGHT,
	VS_RP_BITS_PER_PIXEL,
	VS_RP_COLOR,
	VS_RP_FRAME_RATE,

	VS_NUM_RECORD_PARMS
} VS_RECORD_PARM;


typedef enum VS_FRAME_ENCODE {
	VS_FRAME_NO_ENCODE=0,
	VS_FRAME_JPEG_ENCODE=1,
	VS_FRAME_DJPEG_ENCODE=2,
	VS_FRAME_AVI_ENCODE=3,

	VS_FRAME_NUM_ENCODES=4
} VS_FRAME_ENCODE;


#define VS_INFINITE_FRAMES -1
#define VS_WAIT_NEWER_FRAME -1
#define VS_FRAME_LAST_RECEIVED -1

#define VS_WAIT_FOREVER 0xffffffff


#define VS_MAX_CAM_NAME_LEN 80

typedef struct VS_CAM_ATTR {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	VS_COLOR color;
	float	xZoom;
	float	yZoom;
	CHAR	camName[VS_MAX_CAM_NAME_LEN];
} VS_CAM_ATTR;


typedef struct VS_GRAB_EXT_ATTR {
	ULONGLONG ArrivalTime; // system time that frame arrived in microseconds
	DWORD frameSeqNum;  // Sequence Number of this frame since the grab was begun
	BOOL FrameIsLocked; // TRUE if frame is locked in the grab ring buffer
	DWORD acquiredDy;	// Height of the acquired image
	int ringSeqNum;	// Slot number of frame in ring buffer, i.e., 0..(num frames in ring buffer-1)
} VS_GRAB_EXT_ATTR;

typedef VS_CAM_ATTR *LPVS_CAM_ATTR;

typedef struct VS_AOI_DESC {
	int	x;
	int y;
	int dx;
	int dy;
} VS_AOI_DESC,*LPVS_AOI_DESC;

typedef struct VS_ZOOMCAP {
	float minXZoom;		// less than 1.0 compress, greater than 1.0 stretch
	float maxXZoom;
	float stepSizeX;	// the ratio of size X divided by the next smaller size offered
	float minYZoom;
	float maxYZoom;
	float stepSizeY;	// the ratio of size Y divided by the next smaller size offered
} VS_ZOOMCAP;

typedef VS_ZOOMCAP *LPVS_ZOOMCAP;

typedef struct VS_READCAP {
	BOOL sysColorRemap;		// can remap system colors to closest gray value
	DWORD dwAlignXStart;	// Number of bytes which X Start must be multiple of
	DWORD dwAlignXSize;		// Number of bytes which X Size must be multiple of
	DWORD dwAlignDst;		// Number of bytes which destination address must be multiple of
	DWORD dwMinAoiXSize;	// the smallest AOI in X dimension, 0 means AOI-X not supported
	DWORD dwMinAoiYSize;	// the smallest AOI in Y dimension, 0 means AOI-Y not supported
	BOOL bYcrcbPad;			// can perform BM Ycrcb pad on 8-bit mono
} VS_READCAP;

typedef VS_READCAP *LPVS_READCAP;



typedef enum VS_LUTID_TYPE {
	VS_INPUT_LUT1,
	VS_INPUT_LUT2,
	VS_INPUT_LUT3,
	VS_INPUT_LUT4,
	VS_OUTPUT_LUT1,
	VS_OUTPUT_LUT2,
	VS_OUTPUT_LUT3,
	VS_OUTPUT_LUT4,
	VS_NUM_LUTIDS
} VS_LUTID_TYPE;

typedef enum VS_LUT_PORTION_TYPE {
	VS_LUT_LOW_BYTE,
	VS_LUT_HIGH_BYTE,
	VS_LUT_FULL_WORD,
	VS_LUT_INTELLI_WIDTH
} VS_LUT_PORTION_TYPE;

typedef enum VS_LUT_PIX_SIZE_TYPE {
	VS_LUT_PIX_SIZE_8=8,
	VS_LUT_PIX_SIZE_10=10,
	VS_LUT_PIX_SIZE_12=12,
	VS_LUT_PIX_SIZE_14=14,
	VS_LUT_PIX_SIZE_16=16,
	VS_NUM_LUT_PIX_SIZES
} VS_LUT_PIX_SIZE_TYPE;

typedef enum VS_POLARITY_TYPE {
	VS_ACTIVE_LOW,
	VS_ACTIVE_HIGH
} VS_POLARITY_TYPE;

typedef enum {
	VS_LEVEL_LOW,
	VS_LEVEL_HIGH
} VS_LEVEL_TYPE;

typedef enum VS_EDGE_TYPE {
	VS_FALLING_EDGE,
	VS_RISING_EDGE
} VS_EDGE_TYPE;

typedef enum VS_ENABLE_TYPE {
	VS_DISABLE,
	VS_ENABLE
} VS_ENABLE_TYPE;

typedef enum VS_TRIG_SRC_TYPE {
	VS_SOFT_TRIG,
	VS_EXT0_TRIG,            
	VS_EXT1_TRIG,            
	VS_EXT2_TRIG,            
	VS_EXT3_TRIG
} VS_TRIG_SRC_TYPE;

typedef enum VS_SYNC_TYPE {
	VS_SYNC,
	VS_ASYNC
} VS_SYNC_TYPE;

typedef enum VS_STROBE_MODE_TYPE {
	VS_FAST_STROBE,
	VS_SLOW_STROBE
} VS_STROBE_MODE_TYPE;

typedef enum VS_FRAME_RESET_SIZE_TYPE {
	VS_FRAME_RESET_OFFSET_PERIOD,
	VS_FRAME_RESET_ONE_LINE
} VS_FRAME_RESET_SIZE_TYPE;

typedef enum VS_CSC_TYPE {
	VS_CSC_USE_CUSTOM_MATRIX,
	VS_CSC_RGB_TO_RGB,
	VS_CSC_RGB_TO_YUV,
	VS_CSC_RGB_TO_YIQ,
	VS_CSC_RGB_TO_YCRCB444,
	VS_CSC_RGB_TO_YCRCB422,
	VS_CSC_RGB_TO_YCBCR422,
	VS_CSC_RGB_TO_HSI
} VS_CSC_TYPE;


typedef enum VS_TIMING_SRC_TYPE {
	VS_PLL_SEPARATE_SYNC,
	VS_PLL_STRIPPED_SYNC,
	VS_XTAL_SEPARATE_SYNC_OUT,	// only HSync on HSync output
	VS_XTAL_COMPOSITE_SYNC_OUT,
	VS_VARIABLE_SCAN
} VS_TIMING_SRC_TYPE;

typedef struct {
	float redGain;
	float greenGain;
	float blueGain;

} VS_BAYER_EXT_ATTR,*PVS_BAYER_EXT_ATTR;


#ifndef VSP_MOD_UNIQUE_BASE
#define VSP_MOD_UNIQUE_BASE 0x4000
#endif


#ifndef VS_PGRP_MOD_PECULIAR_BASE
#define VS_PGRP_MOD_PECULIAR_BASE 0x14
#endif

typedef enum {
	VS_BAYER_NONE,
	VS_BAYER_GB_RG,	 // first line GBGBGB..., 2nd line RGRGRG..., 3rd line GBGBGB...,etc...
	VS_BAYER_GB_RG_DEZIPPER, // Zipper effect removal algo, slower than VS_BAYER_GB_RG
	VS_BAYER_RG_GB_DEZIPPER, // Zipper effect removal algo,  // first line RGRGRG ..., 2nd line ...GBGBGB
	VS_BAYER_BG_GR_DEZIPPER,
	VS_BAYER_BG_GR,
	VS_BAYER_GB_RG_GOLD_EAGLE,
	VS_BAYER_RG_GB_GOLD_EAGLE,
	VS_BAYER_BG_GR_GOLD_EAGLE,



} VS_BAYER_FILTER_TYPE;

typedef enum {
	VS_YCRCBTORGB16,
	VS_YCRCBTORGB24,
	VS_YCRCBTORGB32
} VS_YCRCBTORGB;

typedef enum {
	VS_RGB16TOYCRCB,
	VS_RGB24TOYCRCB,
	VS_RGB32TOYCRCB,
} VS_RGBTOYCRCB;


// These are the parameters common to all modules. A given module
// will usually support a subset of these common parameters and
// also have some module-specific parameters.
//
typedef enum VS_ACQ_PARAMS_TYPE {
    VSP_PARAM_NOT_SUPPORTED = 0,
	VSP_PIXEL_SIZE=1,			// RANGE 1..32
	VSP_STROBE_MODE,
	VSP_STROBE_POLARITY,
	VSP_STROBE_DELAY,
	VSP_FRAME_RESET_MODE,
	VSP_FRAME_RESET_POLARITY,
	VSP_FRAME_RESET_OFFSET,
	VSP_FRAME_RESET_SIZE,


	VSP_TRIGGER_ENABLE,		// VS_ENABLE_TYPE
	VSP_TRIGGER_SRC,			// VS_TRIG_SRC_TYPE
	VSP_TRIGGER_POLARITY,		// VS_EDGE_TYPE
	VSP_TRIGGER_STATE,		// VS_LEVEL_TYPE
	VSP_GEN_SW_TRIGGER,		// any value

	VSP_CONTRAST,				// range 0..100
	VSP_BRIGHTNESS,			// range 0..100
	VSP_CUR_ACQ_LINE,


	VSP_LEN_ENABLE,			// VS_ENABLE_TYPE
	VSP_LEN_SYNC,				// VS_SYNC_TYPE
	VSP_LEN_POLARITY, 		// VS_EDGE_TYPE

	VSP_FEN_ENABLE,			// VS_ENABLE_TYPE
	VSP_FEN_POLARITY, 		// VS_EDGE_TYPE
	VSP_HORZ_OFF,				// Module peculiar integer range	
	VSP_WIDTH_PIXELS,			// Module peculiar integer range	
	VSP_VERT_OFF,				// Module peculiar integer range	
	VSP_HEIGHT_PIXELS,		// Module peculiar integer range	

	VSP_FIRST_FIELD_STAT,		// VS_FIELD_STATUS
	VSP_FIRST_FIELD_CMD,		// VS_FIELD_STATUS
	VSP_SCAN_MODE_STAT,		// VS_ILACE

	VSP_HSYNC_FREQ,
	VSP_HSYNC_WIDTH,
	VSP_HSYNC_POLARITY,
	VSP_HSYNC_SRC,
	VSP_HSYNC_SIGNAL_TYPE,
	VSP_VSYNC_FREQ,
	VSP_VSYNC_WIDTH,
	VSP_VSYNC_POLARITY,
	VSP_VSYNC_SRC,
	VSP_VSYNC_SIGNAL_TYPE,
	VSP_PIXEL_CLK_FREQ,
	VSP_PIXEL_CLK_POLARITY,
	VSP_TIMING_SRC,
	VSP_PIXEL_CLK_SIGNAL_TYPE,
	VSP_NUM_EQ_PULSES_FPORCH,
	VSP_NUM_EQ_PULSES_BPORCH,
	VSP_EQ_PULSE_WIDTH,
	VSP_SERR_PULSE_WIDTH,
	VSP_CLAMP_MODE,
	VSP_CLAMP_SEG,
	VSP_CLAMP_HSYNC_EDGE,
	VSP_CLAMP_OFFSET_TIME,
	VSP_CLAMP_LEVEL,
	VSP_PEDESTAL,
	VSP_TIMING_INPUT_CHANNEL,

	// Genral Color Space Option: can affect both CSC matrix and LUTS. If 
	// this parameter is applicable, P_COLOR_SPACE_CONV_COEFFS is
	// ignored.
	VSP_COLOR_SPACE_CONV,

	// Coefficients for linear color space conversion matrix. For most 
	// hardware modules this is subordinate to P_COLOR_SPACE_CONV. I.e.
	// if P_COLOR_SPACE_CONV is applicable then this is ignored.
	VSP_COLOR_SPACE_CONV_COEFFS,

	// Identifies the set of parameter groups applicable for a given camera definition
	VSP_PARAM_GROUPS_APPLICABLE, 

	VSP_PIXEL_COLOR,
	VSP_ANALOG_GAIN,
	VSP_APPLICABLE_CAM_PORT,
	VSP_STROBE_ENABLE,

	VSP_INPUT_LUT1_FILE,
	VSP_INPUT_LUT2_FILE,
	VSP_INPUT_LUT3_FILE,
	VSP_INPUT_LUT4_FILE,

	VSP_FIELD_SRC,
	VSP_FIELD_SHIFT,
	VSP_CAM_MODEL_NAME,
	VSP_COM_PORT_NAME,
	VSP_COM_PORT_BYTESIZE,
	VSP_COM_PORT_BAUDRATE,
	VSP_COM_PORT_PARITY,
	VSP_COM_PORT_STOPBITS,
	VSP_VIDEO_STANDARD,	// video composite/component type IFC_VIDEO_COMP_TYPE
	VSP_BAYER_FILTER,
	VSP_SATURATION,
	VSP_HUE,
	VSP_BAYER_GAIN_RED,
	VSP_BAYER_GAIN_GREEN,
	VSP_BAYER_GAIN_BLUE,
	VSP_FRAME_RESET_GATE, 		// IFC_ENABLE_TYPE
	VSP_FRAMES_PER_TRIGGER,
	VSP_STROBE_DURATION,
	VSP_TRIGGER_DEBOUNCE,
	VSP_WEN_ENABLE,
	VSP_WEN_POLARITY,
	VSP_WEN_VERTICAL_OFFSET,
	VSP_CAM_PIXEL_SIZE,	// Used to indicate low level camera pixel size when different from P_PIXEL_SIZE

	VSP_HORZ_ACTIVE,
	VSP_VERT_ACTIVE,
	VSP_HORZ_INACTIVE,	// An Horizontal Inactive count applied to all taps involved in an acquisition
	VSP_VERT_INACTIVE, 	// An Vertical Inactive count applied to all taps involved in an acquisition

	VSP_VFRAME_TRIGGER_ENABLE,
	VSP_VFRAME_TRIGGER_POLARITY,
	VSP_VFRAME_TRIGGER_DEBOUNCE,

    // Add new types above as needed

	VSP_GEN_PARAM_END_MARKER,	// Always keep these three last.

	VSP_MOD_UNIQUE_1 = VSP_MOD_UNIQUE_BASE,
	VSP_MOD_UNIQUE_2,
	VSP_MOD_UNIQUE_3,
	VSP_MOD_UNIQUE_4,
	VSP_MOD_UNIQUE_5,
	VSP_MOD_UNIQUE_6,
	VSP_MOD_UNIQUE_7,
	VSP_MOD_UNIQUE_8,
	VSP_MOD_UNIQUE_9,
	VSP_MOD_UNIQUE_10,
	VSP_MOD_UNIQUE_11,
	VSP_MOD_UNIQUE_12,
	VSP_MOD_UNIQUE_13,
	VSP_MOD_UNIQUE_14,
	VSP_MOD_UNIQUE_15,
	VSP_MOD_UNIQUE_16,
	VSP_MOD_UNIQUE_17,
	VSP_MOD_UNIQUE_18,
	VSP_MOD_UNIQUE_19,
	VSP_MOD_UNIQUE_20,
	VSP_MOD_UNIQUE_21,
	VSP_MOD_UNIQUE_22,
	VSP_MOD_UNIQUE_23,
	VSP_MOD_UNIQUE_24,
	VSP_MOD_UNIQUE_25,
	VSP_MOD_UNIQUE_26,
	VSP_MOD_UNIQUE_27,
	VSP_MOD_UNIQUE_28,
	VSP_MOD_UNIQUE_29,
	VSP_MOD_UNIQUE_30,
	VSP_MOD_UNIQUE_31,
	VSP_MOD_UNIQUE_32,
	VSP_MOD_UNIQUE_33,
	VSP_MOD_UNIQUE_34,
	VSP_MOD_UNIQUE_35,
	VSP_MOD_UNIQUE_36,
	VSP_MOD_UNIQUE_37,
	VSP_MOD_UNIQUE_38,
	VSP_MOD_UNIQUE_39,
	VSP_MOD_UNIQUE_40,
	VSP_MOD_UNIQUE_41,
	VSP_MOD_UNIQUE_42,
	VSP_MOD_UNIQUE_43,
	VSP_MOD_UNIQUE_44,
	VSP_MOD_UNIQUE_45,
	VSP_MOD_UNIQUE_46,
	VSP_MOD_UNIQUE_47,
	VSP_MOD_UNIQUE_48,
	VSP_MOD_UNIQUE_49,
	VSP_MOD_UNIQUE_50,
	VSP_MOD_UNIQUE_51,
	VSP_MOD_UNIQUE_52,
	VSP_MOD_UNIQUE_53,
	VSP_MOD_UNIQUE_54,
	VSP_MOD_UNIQUE_55,
	VSP_MOD_UNIQUE_56,
	VSP_MOD_UNIQUE_57,
	VSP_MOD_UNIQUE_58,
	VSP_MOD_UNIQUE_59,
	VSP_MOD_UNIQUE_60,
	VSP_MOD_UNIQUE_61,
	VSP_MOD_UNIQUE_62,
	VSP_MOD_UNIQUE_63,
	VSP_MOD_UNIQUE_64,
	VSP_MOD_UNIQUE_65,
	VSP_MOD_UNIQUE_66,
	VSP_MOD_UNIQUE_67,
	VSP_MOD_UNIQUE_68,
	VSP_MOD_UNIQUE_69,
	VSP_MOD_UNIQUE_70,
	VSP_MOD_UNIQUE_71,
	VSP_MOD_UNIQUE_72,
	VSP_MOD_UNIQUE_73,
	VSP_MOD_UNIQUE_74,
	VSP_MOD_UNIQUE_75,
	VSP_MOD_UNIQUE_76,
	VSP_MOD_UNIQUE_77,
	VSP_MOD_UNIQUE_78,
	VSP_MOD_UNIQUE_79,
	VSP_MOD_UNIQUE_80,
	VSP_MOD_UNIQUE_81,
	VSP_MOD_UNIQUE_82,
	VSP_MOD_UNIQUE_83,
	VSP_MOD_UNIQUE_84,
	VSP_MOD_UNIQUE_85,
	VSP_MOD_UNIQUE_86,
	VSP_MOD_UNIQUE_87,
	VSP_MOD_UNIQUE_88,
	VSP_MOD_UNIQUE_89,
	VSP_MOD_UNIQUE_90,
	VSP_MOD_UNIQUE_91,
	VSP_MOD_UNIQUE_92,
	VSP_MOD_UNIQUE_93,
	VSP_MOD_UNIQUE_94,
	VSP_MOD_UNIQUE_95,
	VSP_MOD_UNIQUE_96,
	VSP_MOD_UNIQUE_97,
	VSP_MOD_UNIQUE_98,
	VSP_MOD_UNIQUE_99,
	VSP_MOD_UNIQUE_100,

    VS_LAST_SUP_PARAM = 0x7ff0, 
	VSP_ALL_CAM_PARAMS_ID = 0x7ff1

} VS_ACQ_PARAMS_TYPE;




typedef struct VS_STREAM_FRAME_ATTR {
	ULONGLONG ArrivalTime; // system time that frame arrived in microseconds
	DWORD frameSeqNum;  // Sequence Number of this frame since the grab was begun
} VS_STREAM_FRAME_ATTR,*PVS_STREAM_FRAME_ATTR;



// Define Read Area Options
#define VS_ROPT_SYSCOLOR_CLIP	0x00000001
#define VS_ROPT_YCRCBMONO_PAD	0x00000002
#define VS_ROPT_FLATDRIVER		0x00000004
#define VS_ROPT_ODD_BYTE_ONLY	0x00000008	// Read only the hi-byte of each 16-bit WORD

/**************************************************************************
***************************************************************************
**
** Parameter manipulation structures
**
***************************************************************************
***************************************************************************
*/
/* supported parameter types */
typedef enum VS_PARAM_KIND {
    VS_ENUM_TYPE,
    VS_INTEGER_TYPE,
    VS_FLOAT_TYPE,
    VS_STRING_TYPE,
    VS_POINTER_TYPE,
    VS_FLOAT_SET_TYPE,
    VS_INT_SET_TYPE
} VS_PARAM_KIND;

/* structure to return float ranges */
typedef struct VS_RANGE {
    double Min;
    double Max;
    double Step;
	DWORD regBaseValue;
} VS_RANGE;


/* arrays to return float/int value sets */
#define VS_MAX_ARRAY_SIZE 32
#define VS_MAX_PARAM_LEN 80

#define VS_MAX_PARAM_APPLICABLE_LEN 200

#define MAX_ENUM_ARG_NAME_LEN 48
/* structure to return enumerated arguments */

typedef struct VS_ENUM_ARG {
    CHAR argName[MAX_ENUM_ARG_NAME_LEN];
    double argValue;
	DWORD regValue;
}VS_ENUM_ARG,*PVS_ENUM_ARG;

#define VS_MAX_ENUM_ARG_PER_PARAM 16

#define VS_MAX_PARM_PRESENT_NAME_LEN 42


#define VS_MAX_PARAM_ARRAY_DIM 16

// Parameter Capability Flags
#define VS_PARAMCAP_READ_ONLY 1
#define VS_PARAMCAP_WRITE_ONLY 2
#define VS_PARAMCAP_READWRITE 0

typedef struct VS_PARAM_CAPS {
    VS_ACQ_PARAMS_TYPE param;		/* enumerated value */
	CHAR presentationName[VS_MAX_PARM_PRESENT_NAME_LEN];		/* Presentation name for the Parameter */
    CHAR paramName[VS_MAX_PARAM_LEN];      /* string representation of the enumerated value */
    VS_PARAM_KIND paramType;  /* enumerated:  ENUM_TYPE, VS_INTEGER_TYPE, VS_FLOAT_TYPE, */
                                /* VS_STRING_TYPE, POINTER_TYPE, FLOAT_SET_TYPE, INT_SET_TYPE */
	DWORD		dwArrayDim;		/* normally 1, greater if parameter is a vector */
	DWORD memberGroupMask;		/* Mask which identifies which groups this parameter belongs to */
    VS_ENUM_ARG enumArgs[VS_MAX_ENUM_ARG_PER_PARAM];    /* used when parameter is enumerated type, must specify in argValue increasing order  */
    VS_RANGE Range;         /* used when parameter is a float */
    DWORD dwCapFlags;              /* parameter capabilities flag mask */
	DWORD parentGroupMask;		/* Mask which identifies any parent groups of the groups which this parameter belongs to */
} VS_PARAM_CAPS,*PVS_PARAM_CAPS;


typedef DWORD HVIDSTREAM;
typedef DWORD HVIDSTREAMSRV;


typedef DWORD HVSEVENT;

#define VS_WAIT_STATUS_TIMEOUT 0x7fffffff
#define VS_WAIT_STATUS_MSG_RCV 0x7ffffffe



#ifndef __midl

#ifndef __IDistribOS_FWD_DEFINED__
#define __IDistribOS_FWD_DEFINED__
typedef interface IDistribOS IDistribOS;
#endif 	/* __IDistribOS_FWD_DEFINED__ */

#define VS_IMAGEPROC_FUNC_POP_COUNT 20
typedef DWORD (IVSAPI *VS_IMAGEPROC_FUNC)(IDistribOS *pObj, VS_CAM_ATTR *attr, BYTE *image, BYTE *arg , DWORD argSize); 


#define VS_INVOKE_FUNC_POP_COUNT 4
typedef DWORD (IVSAPI *VS_INVOKE_FUNC)(IDistribOS *pObj); 

#define VS_INVOKE_PARM_BLK_FUNC_POP_COUNT 12
typedef DWORD (IVSAPI *VS_INVOKE_PARM_BLK_FUNC)(IDistribOS *pObj,BYTE *paramBlock,DWORD numParamBytes); 

#define VS_INVOKE_VSPARAM_FUNC_POP_COUNT 12
typedef DWORD (IVSAPI *VS_INVOKE_VSPARAM_FUNC)(IDistribOS *pObj,DWORD numParams, VSPARAM params[]); 


#endif


#define VS_MAX_NUM_INV_PARM_BYTES 100

typedef struct IVSV_EXT_API VS_INVOKE_DESC {
	DWORD  m_structSize;
	CVSStr m_dllName;
	CVSStr m_funcName; // Exported function of prototype VS_IMAGEPROC_FUNC
	ULONG  m_numParmBytes;
	BYTE   m_parmBlock[VS_MAX_NUM_INV_PARM_BYTES];
	DWORD m_reserved;
} VS_INVOKE_DESC,*PVS_INVOKE_DESC;


typedef DWORD HSERVERTHREAD;

typedef DWORD HPROCESSTHREAD;

typedef DWORD HVSMESSAGE;


#if defined(__midl) || !defined(__cplusplus)

typedef VS_INVOKE_DESC CVSInvokeDesc;


#else



class IVSV_EXT_API CVSInvokeDesc : public ::VS_INVOKE_DESC
{
public:
	CVSInvokeDesc();
	~CVSInvokeDesc();

	CVSInvokeDesc(const char *dllName,const char *funcName, BYTE *paramBlock=NULL, DWORD paramBlockSize=0);

	CVSInvokeDesc& operator=( char *DllFuncName);

};


// Default constructor
//
inline CVSInvokeDesc::CVSInvokeDesc()
{
	m_structSize = sizeof(CVSInvokeDesc);
	m_numParmBytes = 0;

}

inline CVSInvokeDesc::~CVSInvokeDesc()
{

}


inline CVSInvokeDesc::CVSInvokeDesc(const char *dllName,const char *funcName, BYTE *paramBlock, DWORD paramBlockSize) 
{
	m_structSize = sizeof(CVSInvokeDesc);
	m_dllName = dllName;
	m_funcName = funcName;
	if (paramBlock && paramBlockSize <= VS_MAX_NUM_INV_PARM_BYTES ) {
		memcpy(m_parmBlock,paramBlock,paramBlockSize);
		m_numParmBytes = paramBlockSize;
	}
	else {
		m_numParmBytes = 0;
	}
}

inline CVSInvokeDesc& CVSInvokeDesc::operator=( char *DllAndFuncName)
{
	char *colon;
	if (colon=strchr(DllAndFuncName,':')) {
		*colon=0;
		m_dllName = DllAndFuncName;
		m_funcName = colon+1;
		*colon=':';
	}
	m_structSize = sizeof(CVSInvokeDesc);
	m_numParmBytes = 0;

	return *this;
}



#endif

#define VS_FRAME_RATE_INCOMING 0.0	// Stream every frame at a rate dictated by the video source
#define VS_FRAME_RATE_AUTO	-1.0	// Automatically adjust frame rate based upon the frame client consumption rate
#define VS_FRAME_RATE_SCALE2	-2.0	// Send every 2nd frame
#define VS_FRAME_RATE_SCALE3	-3.0	// Send every 3rd frame
#define VS_FRAME_RATE_SCALE4	-4.0	// Send every 4th frame
#define VS_FRAME_RATE_SCALE5	-5.0	// Send every 5th frame
#define VS_FRAME_RATE_SCALE6	-6.0	// Send every 6th frame

typedef struct IVSV_EXT_API VS_STREAM_PARAMS {
	VS_FRAME_ENCODE encodeKind;
	DWORD numIframes;
	float desiredFramesPerSecond;
	CVSInvokeDesc processFunc;
} VS_STREAM_PARAMS,*PVS_STREAM_PARAMS;


typedef enum VS_PARAM_GROUP_TYPE {
    VS_GROUP_NOT_SUPPORTED = 0,
	VS_PGRP_CAM_TIMING_INPUT=1,// Parameters pertaining to camera timing inputs
	VS_PGRP_CAM_TIMING_OUTPUT, // Parameters pertaining to camera timing outputs
	VS_PGRP_MULTI_CAMERA,		// Parameters pertaining to multiple cameras on one board
	VS_PGRP_GENERAL_ACQ,		// General acquisition parameters, e.g., window generator, pixel depth, pixel color, ...
	VS_PGRP_TRIGGER,			// Trigger,strobe, frame reset related parameters
	VS_PGRP_CUSTOM_CAMERA,		// Advanced custom camera definition parameters, e.g. special EXO files
	VS_PGRP_ANALOG_SETTINGS,	// Parameters which impact an analog signal, e.g., gain,nref,pref,low-pass-filter
	VS_PGRP_WINDOW_GENERATOR,	// Parameters pertaining to the window generator
	VS_PGRP_CAM_TIMING,		// Parameters pertaining to camera timing outputs
	VS_PGRP_PROG_TIMING_GEN,	// Parameters pertaining to the programmable timing generator
	VS_PGRP_TRIG_STROBE_RESET, // Trigger,strobe, frame reset related parameters
	VS_PGRP_STROBE,			// Parameters pertaining to camera strobe settings
	VS_PGRP_FRAME_RESET,		// Parameters pertaining to camera frame reset

	VS_PGRP_MOD_PECULIAR1=VS_PGRP_MOD_PECULIAR_BASE,
	VS_PGRP_MOD_PECULIAR2=0x15,
	VS_PGRP_MOD_PECULIAR3=0x16,
	VS_PGRP_MOD_PECULIAR4=0x17,
	VS_PGRP_MOD_PECULIAR5=0x18,
	VS_PGRP_MOD_PECULIAR6=0x19,
	VS_PGRP_MOD_PECULIAR7=0x1a,
	VS_PGRP_MOD_PECULIAR8=0x1b,
	VS_PGRP_MOD_PECULIAR9=0x1c,
	VS_PGRP_MOD_PECULIAR10=0x1d,
	VS_PGRP_MOD_PECULIAR11=0x1e,
	VS_PGRP_MOD_PECULIAR12=0x1f,
	VS_PGRP_NUM_GROUPS,
    VS_LAST_SUPPORT_PGRP = 0x7ff0, 
	VS_PGRP_TOP_LEVEL=0x7ff1

} VS_PARAM_GROUP_TYPE;

#define PGRP_ID_TO_MASK(pGrpID) (1<<pGrpID)

#define VS_PGRP_CAM_TIMING_INPUT_MASK		PGRP_ID_TO_MASK(VS_PGRP_CAM_TIMING_INPUT)
#define VS_PGRP_CAM_TIMING_OUTPUT_MASK		PGRP_ID_TO_MASK(VS_PGRP_CAM_TIMING_OUTPUT)
#define VS_PGRP_MULTI_CAMERA_MASK			PGRP_ID_TO_MASK(VS_PGRP_MULTI_CAMERA)
#define VS_PGRP_GENERAL_ACQ_MASK			PGRP_ID_TO_MASK(VS_PGRP_GENERAL_ACQ)
#define VS_PGRP_TRIGGER_MASK				PGRP_ID_TO_MASK(VS_PGRP_TRIGGER)
#define VS_PGRP_CUSTOM_CAMERA_MASK			PGRP_ID_TO_MASK(VS_PGRP_CUSTOM_CAMERA)
#define VS_PGRP_ANALOG_SETTINGS_MASK		PGRP_ID_TO_MASK(VS_PGRP_ANALOG_SETTINGS)
#define VS_PGRP_WINDOW_GENERATOR_MASK		PGRP_ID_TO_MASK(VS_PGRP_WINDOW_GENERATOR)
#define VS_PGRP_CAM_TIMING_MASK			PGRP_ID_TO_MASK(VS_PGRP_CAM_TIMING)
#define VS_PGRP_PROG_TIMING_GEN_MASK		PGRP_ID_TO_MASK(VS_PGRP_PROG_TIMING_GEN)
#define VS_PGRP_TRIG_STROBE_RESET_MASK		PGRP_ID_TO_MASK(VS_PGRP_TRIG_STROBE_RESET)
#define VS_PGRP_STROBE_MASK				PGRP_ID_TO_MASK(VS_PGRP_STROBE)
#define VS_PGRP_FRAME_RESET_MASK			PGRP_ID_TO_MASK(VS_PGRP_FRAME_RESET)


#define VS_ALL_PARAM_GROUPS				0xffffffff


#define VS_MAX_NICKNAME_LEN 12


typedef struct VS_PARAM_GROUP_PROPS {
    VS_PARAM_GROUP_TYPE group;		// enumerated value 
	DWORD groupMask;				// Mask value for this group 
	CHAR presentationName[VS_MAX_PARM_PRESENT_NAME_LEN];	// Presentation name for the Parameter group
	CHAR nickName[VS_MAX_NICKNAME_LEN];					// A shortened form of the presentation name
    CHAR groupName[VS_MAX_PARAM_LEN];      // string representation of the enumerated value 
} VS_PARAM_GROUP_PROPS,*PVS_PARAM_GROUP_PROPS;




typedef DWORD VS_CAMERA_DEF_TYPE,*PVS_CAMERA_DEF_TYPE;

#define VS_MAX_CAMERA_NAME_LEN 80
#define VS_MAX_CAMERA_ORIGIN_LEN 200

#define VS_MAX_SYMBOL_TABLE_ENTRIES 800
#define VS_MAX_UNSUPPORTED_PARM_LINES 40



#define VS_CAMERA_ORIGIN_INTERNAL "Internal"


#define VS_MAX_NUM_INPUT_LUTS 4
#define VS_MAX_NUM_OUTPUT_LUTS 4

#define VS_PAGE_8BIT_FLAG		0x01
#define VS_PAGE_10BIT_FLAG		0x02
#define VS_PAGE_12BIT_FLAG		0x04
#define VS_PAGE_14BIT_FLAG		0x08
#define VS_PAGE_16BIT_FLAG		0x10

// Grab Options
#define VS_GOPT_SINGLE_DEST		0x80000000
#define VS_GOPT_AUTO_FRAME_LOCK	0x00000001
#define VS_GOPT_SYSCOLOR_CLIP		0x00000002
#define VS_GOPT_LEFTJUSTIFIED		0x00000004


// The following are reserved for module peculiar grab options
#define VS_GOPT_MOD_PECULIAR1		0x00010000
#define VS_GOPT_MOD_PECULIAR2		0x00020000
#define VS_GOPT_MOD_PECULIAR3		0x00040000
#define VS_GOPT_MOD_PECULIAR4		0x00080000

typedef struct VS_LUT_CAP_TYPE {
	int bitDepth;
	int numEntries;
	DWORD pageSizeMask;
} VS_LUT_CAP_TYPE;

typedef struct VS_LUTCAP {
	int numInputLUTs;		
	VS_LUT_CAP_TYPE inputLUTs[VS_MAX_NUM_INPUT_LUTS];
	int numOutputLUTs;
	VS_LUT_CAP_TYPE outputLUTs[VS_MAX_NUM_OUTPUT_LUTS];
} VS_LUTCAP;

typedef VS_LUTCAP *LPVS_LUTCAP;

typedef DWORD VS_CAM_ID;


#ifdef __midl 
typedef DWORD VSLUTFUNC;
#else
typedef DWORD (IVSAPI *VSLUTFUNC)(DWORD arg ,DWORD *constants); 
#endif

typedef DWORD REGID;

#define VS_CAMERA_REG_BASE 0x8000

typedef enum VS_TRANSFORM_TYPE {
	VS_NO_TRANSFORM,
	VS_FLIP_TRANSFORM,		// Top-Bottom Flip
	VS_MIRROR_TRANSFORM,
	VS_ROT180_TRANSFORM,

	VS_NUM_TRANSFORM_KINDS
} VS_TRANSFORM_TYPE;

#define	VS_FLIP_TRANSFORM_MASK		0x00000001
#define	VS_MIRROR_TRANSFORM_MASK	0x00000002
#define	VS_ROT180_TRANSFORM_MASK	0x00000004



typedef struct  VSAUTHIDENTITY {
	CVSStr User;
    CVSStr Domain;
    CVSStr Password;
} VSAUTHIDENTITY;


typedef enum VS_FILESYS_DOMAIN_TYPE {
	VS_FILESYS_CLIENT,
	VS_FILESYS_SERVER

} VS_FILESYS_DOMAIN_TYPE;


typedef enum VS_RPC_RET_TYPE {
	VS_RPC_RET_VOID,
	VS_RPC_RET_INT,
	VS_RPC_RET_FLOAT,
	VS_RPC_RET_DOUBLE

} VS_RPC_RET_TYPE;


#define VS_PTR_RPC_IN_PARAM  1
#define VS_PTR_RPC_OUT_PARAM 2
#define VS_PTR_RPC_INOUT_PARAM (VS_PTR_RPC_IN_PARAM|VS_PTR_RPC_OUT_PARAM)

// flag values
#define VS_RPC_RESOLVE_IN_OBJ_DOMAIN 1
#define VS_RPC_RESOLVE_IN_CLIENT_DOMAIN 2

#define VS_RPC_MAX_NUM_PTR_DESCS 8

typedef struct VS_RPC_PTR_DESC {
	DWORD stkPtrOffset; // dword offset
	DWORD numBytes;
	DWORD attr;
	DWORD poolOffset;
} VS_RPC_PTR_DESC;


typedef struct VS_RPC_INVOKE_STRUCT {
	DWORD flags;
	DWORD stkBlkSize; // numStackPassedParam in DWORDs (bytes and word params take one whole dword)
	CVSStr funcName;
	VS_RPC_RET_TYPE retType;
	VS_RPC_PTR_DESC ptrDescs[VS_RPC_MAX_NUM_PTR_DESCS];
	DWORD stkBlk; // ptr to stack block
} VS_RPC_INVOKE_STRUCT;



typedef DWORD HBYREFELE;

typedef enum VS_QUEUE_FULL_POLICY {
	VS_QUEUE_FULL_STOP,	 // attempts to enqueue when the queue is full will fail
	VS_QUEUE_FULL_OVERWRITE_OLDEST	// enqueue when the queue is full will cause the oldest queue item to be lost

} VS_QUEUE_FULL_POLICY;

typedef struct VS_INODE_QMNG_ATTR {
	DWORD maxQueueEntries;
	VS_QUEUE_FULL_POLICY qFullPolicy;
} VS_INODE_QMNG_ATTR;


typedef struct VS_IMGNODE_ATTR {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	VS_COLOR color;
	DWORD maxQueueEntries;
	VS_QUEUE_FULL_POLICY qFullPolicy;
	VS_FRAME_ENCODE remoteFrameEncode; // desired frame encode method when consumer is remote
	VARIANT_BOOL	areRemote;

} VS_IMGNODE_ATTR;


typedef struct VS_IMAGE_ATTR {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	VS_COLOR color;
} VS_IMAGE_ATTR;


typedef enum VS_REF_VAL_KIND {
	VS_Q_BY_REF,
	VS_Q_BY_VAL
} VS_REF_VAL_KIND;


typedef struct VS_INODE_IMG_ATTR {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	DWORD dwImageSize;
	VS_COLOR color;
	ULONGLONG ArrivalTime; // system time that frame arrived in microseconds
	DWORD SeqNum;  // Sequence Number of this IMAGE since the grab was begun

} VS_INODE_IMG_ATTR;


typedef struct VS_PRODUCER_ATTR {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	DWORD dwImageSize;
	VS_COLOR color;
	CVSStr nodeName;
	DWORD pid; // process ID
	float stdFrameRate;
	BOOL canHandleByRef; 
	VS_FRAME_ENCODE remoteFrameEncode; // desired frame encode method when consumer is remote

} VS_PRODUCER_ATTR;

typedef struct VS_CONSUMER_ATTR {
	CVSStr nodeName;
	DWORD pid; // process ID
	BOOL canHandleByRef; 

} VS_CONSUMER_ATTR;


typedef struct VS_CONFIG_PRODUCER {
	VS_REF_VAL_KIND enQKind;
	float desiredFrameRate;

} VS_CONFIG_PRODUCER;

typedef struct VS_CONFIG_CONSUMER {
	VS_REF_VAL_KIND deQKind;

} VS_CONFIG_CONSUMER;

typedef enum VS_PROD_CONSMR_ID_KIND {
	VS_PRODUCER_ID,
	VS_CONSUMER_ID
} VS_PROD_CONSMR_ID_KIND;


// GrabToImgNode options
#define VS_AUTO_THROTTLE_PRODUCER 1
#define VS_PRODUCER_SCALE_VAL(scale) ((scale-1)*2)
#define VS_PRODUCER_SCALE_MASK 0x3e

typedef DWORD   COLORREF;

typedef struct {
	WORD x;
	WORD y;
	WORD len;
	WORD tag;
} VS_RLE_FEATURE_DESC,*LPVS_RLE_FEATURE_DESC;


typedef struct VS_BLOB_DESC {
      DWORD x0,y0,x1,y1;
      DWORD x_cent;
      DWORD y_cent;
      DWORD area;
      DWORD xsum,ysum;
      DWORD perim;
      DWORD fIgnore;
      DWORD tag;
} VS_BLOB_DESC;


typedef struct VS_BLOB_DESC_LIST {
	DWORD numBlobs;
	VS_BLOB_DESC blobs[1];
} VS_BLOB_DESC_LIST;

#define FN_WAVE_FORMAT_PCM     1

typedef struct {
    WORD        nChannels;          /* number of channels (i.e. mono, stereo...) */
    DWORD       nSamplesPerSec;     /* sample rate */
    WORD        wBitsPerSample;     /* number of bits per sample of mono data */

} FN_SOUND_DESC;


typedef struct VS_AVICOMPRESSOPTIONS {
    DWORD		fccType;		    /* stream type, for consistency */
    DWORD       fccHandler;                 /* compressor */
    DWORD       dwKeyFrameEvery;            /* keyframe rate */
    DWORD       dwQuality;                  /* compress quality 0-10,000 */
    DWORD       dwBytesPerSecond;           /* bytes per second */
    DWORD       dwFlags;                    /* flags... see below */
    DWORD      lpFormat;                   /* LPVOID save format */
    DWORD       cbFormat;
    DWORD      lpParms;                    /* LPVOID compressor options */
    DWORD       cbParms;
    DWORD       dwInterleaveEvery;          /* for non-video streams only */
} VS_AVICOMPRESSOPTIONS, *LPVS_AVICOMPRESSOPTIONS;

#if defined(__midl) 

typedef BYTE *VS_DIRECT_DEREF_FUNC;

#else

typedef void (IVSAPI *VS_DIRECT_DEREF_FUNC)(LPVOID p1, DWORD OutputId, HBYREFELE deRefHandle);

#endif



#include <pcdigt.h>
#include <camlinkt.h>
#include <pcplust.h>
#include <pcvisnt.h>
#include <pcRgbt.h>


#endif