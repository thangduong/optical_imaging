/******************************************************************************
 *
 * MODULE   
 *		Camera.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Camera.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/29/04 4:12p $
 *
 * ABSTRACT  
 *		IFC interface of the CICamera class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c)1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CAMERA_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_CAMERA_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Iobject.h>
#include <ParntMod.h>
#include <IFrame.h>
#include <IFCTyp.h>
#include <Config.h>
#include <ddraw.h>


#define IFC_MAX_CAM_NAME_LEN 80
#define IFC_MSGS

typedef struct {
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwBytesPerPixel;
	DWORD dwBitsPerPixel;
	IFC_COLOR color;
	float	xZoom;
	float	yZoom;
	char	camName[IFC_MAX_CAM_NAME_LEN];
} CAM_ATTR;

typedef enum {
	IFC_RS170_CAM,
	IFC_CCIR_CAM,
	IFC_DIG_AREA_SCAN,
	IFC_DIG_LINE_SCAN

} IFC_STD_CAM_TYPE;


typedef struct {
	double ArrivalTime; // system time that frame arrived in microseconds
	DWORD frameSeqNum;  // Sequence Number of this frame since the grab was begun
	BOOL FrameIsLocked; // TRUE if frame is locked in the grab ring buffer
	BOOL potentiallyBad;
	DWORD camPortNum;
	DWORD objectIndex;
} GRAB_EXT_ATTR;

typedef CAM_ATTR *LPCAM_ATTR;

typedef struct {
	int	x;
	int y;
	int dx;
	int dy;
} IFC_AOI_DESC,*LPIFC_AOI_DESC;

typedef struct {
	float minXZoom;		// less than 1.0 compress, greater than 1.0 stretch
	float maxXZoom;
	float stepSizeX;	// the ratio of size X divided by the next smaller size offered
	float minYZoom;
	float maxYZoom;
	float stepSizeY;	// the ratio of size Y divided by the next smaller size offered
} ZOOMCAP;

typedef ZOOMCAP *LPZOOMCAP;

typedef struct {
	BOOL sysColorRemap;		// can remap system colors to closest gray value
	DWORD dwAlignXStart;	// Number of bytes which X Start must be multiple of
	DWORD dwAlignXSize;		// Number of bytes which X Size must be multiple of
	DWORD dwAlignDst;		// Number of bytes which destination address must be multiple of
	DWORD dwMinAoiXSize;	// the smallest AOI in X dimension, 0 means AOI-X not supported
	DWORD dwMinAoiYSize;	// the smallest AOI in Y dimension, 0 means AOI-Y not supported
	BOOL bYcrcbPad;			// can perform BM Ycrcb pad on 8-bit mono
	BOOL bHwLineRev;
} READCAP;

typedef READCAP *LPREADCAP;

typedef enum {
	INPUT_LUT1,
	INPUT_LUT2,
	INPUT_LUT3,
	INPUT_LUT4,
	OUTPUT_LUT1,
	OUTPUT_LUT2,
	OUTPUT_LUT3,
	OUTPUT_LUT4,
	IFC_NUM_LUTIDS
} LUTID_TYPE;

typedef enum {
	LUT_LOW_BYTE,
	LUT_HIGH_BYTE,
	LUT_FULL_WORD,
	LUT_INTELLI_WIDTH,
	LUT_MID_BYTE
} LUT_PORTION_TYPE;

typedef enum {
	IFC_LUT_PIX_SIZE_8=8,
	IFC_LUT_PIX_SIZE_10=10,
	IFC_LUT_PIX_SIZE_12=12,
	IFC_LUT_PIX_SIZE_14=14,
	IFC_LUT_PIX_SIZE_16=16,
	IFC_NUM_LUT_PIX_SIZES
} IFC_LUT_PIX_SIZE_TYPE;

typedef enum {
	IFC_ACTIVE_LOW,
	IFC_ACTIVE_HIGH
} IFC_POLARITY_TYPE;

typedef enum {
	IFC_LEVEL_LOW,
	IFC_LEVEL_HIGH
} IFC_LEVEL_TYPE;

typedef enum {
	IFC_FALLING_EDGE,
	IFC_RISING_EDGE,
	IFC_POL_ACTIVE_LOW,
	IFC_POL_ACTIVE_HIGH,
	IFC_BOTH_EDGE,
	IFC_DOUBLE_PULSE_RISING_EDGE,
	IFC_DOUBLE_PULSE_FALLING_EDGE,

} IFC_EDGE_TYPE;

typedef enum {
	IFC_DISABLE,
	IFC_ENABLE
} IFC_ENABLE_TYPE;

typedef enum {
	IFC_SOFT_TRIG,
	IFC_EXT0_TRIG,            
	IFC_EXT1_TRIG,            
	IFC_EXT2_TRIG,            
	IFC_EXT3_TRIG,
	IFC_EXT_AUTO_TRIG,
	IFC_FREQ_TRIG,
	

} IFC_TRIG_SRC_TYPE;

typedef enum {
	IFC_SYNC,
	IFC_ASYNC
} IFC_SYNC_TYPE;

typedef enum {
	IFC_FAST_STROBE,
	IFC_SLOW_STROBE
} IFC_STROBE_MODE_TYPE;

typedef enum {
	IFC_FRAME_RESET_OFFSET_PERIOD,
	IFC_FRAME_RESET_ONE_LINE
} IFC_FRAME_RESET_SIZE_TYPE;

typedef enum {
	IFC_CSC_USE_CUSTOM_MATRIX,
	IFC_CSC_RGB_TO_RGB,
	IFC_CSC_RGB_TO_YUV,
	IFC_CSC_RGB_TO_YIQ,
	IFC_CSC_RGB_TO_YCRCB444,
	IFC_CSC_RGB_TO_YCRCB422,
	IFC_CSC_RGB_TO_YCBCR422,
	IFC_CSC_RGB_TO_HSI
} IFC_CSC_TYPE;


#define IFC_BOARD_SERIAL_PORT0 "BRD0"
#define IFC_BOARD_SERIAL_PORT1 "BRD1"

typedef enum {
	IFC_PLL_SEPARATE_SYNC,
	IFC_PLL_STRIPPED_SYNC,
	IFC_XTAL_SEPARATE_SYNC_OUT,	// only HSync on HSync output
	IFC_XTAL_COMPOSITE_SYNC_OUT,
	IFC_VARIABLE_SCAN
} IFC_TIMING_SRC_TYPE;

typedef enum {
	IFC_BAUD_300 = 300 ,
	IFC_BAUD_600 = 600 ,
	IFC_BAUD_1200= 1200,
	IFC_BAUD_2400= 2400,
	IFC_BAUD_4800= 4800,
	IFC_BAUD_9600= 9600,
	IFC_BAUD_14400 = 14400 ,
	IFC_BAUD_19200= 19200,
	IFC_BAUD_38400= 38400,
	IFC_BAUD_56000= 56000,
	IFC_BAUD_57600= 57600,
	IFC_BAUD_115200= 115200,
	IFC_BAUD_128000= 128000,
	IFC_BAUD_256000= 256000
} IFC_BAUD_RATE_TYPE;


typedef enum {
	IFC_NOPARITY,
	IFC_ODDPARITY,
	IFC_EVENPARITY,
	IFC_MARKPARITY,
	IFC_SPACEPARITY         
} IFC_COM_PARITY_TYPE;

typedef enum {
	IFC_ONESTOPBIT,
	IFC_1_5_STOPBITS,
	IFC_TWOSTOPBITS
} IFC_COM_STOPBIT_TYPE;

typedef enum {
	IFC_COM_4BITS=4,
	IFC_COM_5BITS=5,
	IFC_COM_6BITS=6,
	IFC_COM_7BITS=7,
	IFC_COM_8BITS=8
} IFC_COM_BYTESIZE_TYPE;


typedef enum {
	IFC_VIDEO_STD_AUTO,
	IFC_VIDEO_STD_NTSC,
	IFC_VIDEO_STD_PAL,
	IFC_VIDEO_STD_SECAM,
	IFC_VIDEO_STD_NONE,
	IFC_VIDEO_STD_NTSC_JAPAN,
	IFC_VIDEO_STD_PAL_M,
	IFC_VIDEO_STD_PAL_N,
	IFC_VIDEO_STD_PAL_COMB,
	IFC_VIDEO_STD_NTSC_443_50HZ,
	IFC_VIDEO_STD_NTSC_N,
	IFC_VIDEO_STD_PAL_443_60HZ,
	IFC_VIDEO_STD_NTSC_443_60HZ,

} IFC_VIDEO_STD_TYPE;

typedef enum {
	IFC_BAYER_NONE,
	IFC_BAYER_GB_RG,	 // first line GBGBGB..., 2nd line RGRGRG..., 3rd line GBGBGB...,etc...
	IFC_BAYER_GB_RG_DEZIPPER, // Zipper effect removal algo, slower than IFC_BAYER_GB_RG
	IFC_BAYER_RG_GB_DEZIPPER, // Zipper effect removal algo,  // first line RGRGRG ..., 2nd line ...GBGBGB
	IFC_BAYER_BG_GR_DEZIPPER,
	IFC_BAYER_BG_GR,
	IFC_BAYER_GB_RG_GOLD_EAGLE,
	IFC_BAYER_RG_GB_GOLD_EAGLE,
	IFC_BAYER_BG_GR_GOLD_EAGLE,



} IFC_BAYER_FILTER_TYPE;

// These are the parameters common to all modules. A given module
// will usually support a subset of these common parameters and
// also have some module-specific parameters.
//
typedef enum {
	P_PIXEL_SIZE=1,			// RANGE 1..32
	P_STROBE_MODE,
	P_STROBE_POLARITY,
	P_STROBE_DELAY,
	P_FRAME_RESET_MODE,
	P_FRAME_RESET_POLARITY,
	P_FRAME_RESET_OFFSET,
	P_FRAME_RESET_SIZE,


	P_TRIGGER_ENABLE,		// IFC_ENABLE_TYPE
	P_TRIGGER_SRC,			// IFC_TRIG_SRC_TYPE
	P_TRIGGER_POLARITY,		// IFC_EDGE_TYPE
	P_TRIGGER_STATE,		// IFC_LEVEL_TYPE
	P_GEN_SW_TRIGGER,		// any value

	P_CONTRAST,				// range 0..100
	P_BRIGHTNESS,			// range 0..100
	P_CUR_ACQ_LINE,


	P_LEN_ENABLE,			// IFC_ENABLE_TYPE
	P_LEN_SYNC,				// IFC_SYNC_TYPE
	P_LEN_POLARITY, 		// IFC_EDGE_TYPE

	P_FEN_ENABLE,			// IFC_ENABLE_TYPE
	P_FEN_POLARITY, 		// IFC_EDGE_TYPE
	P_HORZ_OFF,				// Module peculiar integer range	
	P_WIDTH_PIXELS,			// Module peculiar integer range	
	P_VERT_OFF,				// Module peculiar integer range	
	P_HEIGHT_PIXELS,		// Module peculiar integer range	

	P_FIRST_FIELD_STAT,		// IFC_FIELD_STATUS
	P_FIRST_FIELD_CMD,		// IFC_FIELD_STATUS
	P_SCAN_MODE_STAT,		// IFC_ILACE

	P_HSYNC_FREQ,
	P_HSYNC_WIDTH,
	P_HSYNC_POLARITY,
	P_HSYNC_SRC,
	P_HSYNC_SIGNAL_TYPE,
	P_VSYNC_FREQ,
	P_VSYNC_WIDTH,
	P_VSYNC_POLARITY,
	P_VSYNC_SRC,
	P_VSYNC_SIGNAL_TYPE,
	P_PIXEL_CLK_FREQ,
	P_PIXEL_CLK_POLARITY,
	P_TIMING_SRC,
	P_PIXEL_CLK_SIGNAL_TYPE,
	P_NUM_EQ_PULSES_FPORCH,
	P_NUM_EQ_PULSES_BPORCH,
	P_EQ_PULSE_WIDTH,
	P_SERR_PULSE_WIDTH,
	P_CLAMP_MODE,
	P_CLAMP_SEG,
	P_CLAMP_HSYNC_EDGE,
	P_CLAMP_OFFSET_TIME,
	P_CLAMP_LEVEL,
	P_PEDESTAL,
	P_TIMING_INPUT_CHANNEL,

	// Genral Color Space Option: can affect both CSC matrix and LUTS. If 
	// this parameter is applicable, P_COLOR_SPACE_CONV_COEFFS is
	// ignored.
	P_COLOR_SPACE_CONV,

	// Coefficients for linear color space conversion matrix. For most 
	// hardware modules this is subordinate to P_COLOR_SPACE_CONV. I.e.
	// if P_COLOR_SPACE_CONV is applicable then this is ignored.
	P_COLOR_SPACE_CONV_COEFFS,

	// Identifies the set of parameter groups applicable for a given camera definition
	P_PARAM_GROUPS_APPLICABLE, 

	P_PIXEL_COLOR,
	P_ANALOG_GAIN,
	P_APPLICABLE_CAM_PORT,
	P_STROBE_ENABLE,

	P_INPUT_LUT1_FILE,
	P_INPUT_LUT2_FILE,
	P_INPUT_LUT3_FILE,
	P_INPUT_LUT4_FILE,
	P_FIELD_SRC,
	P_FIELD_SHIFT,
	P_CAM_MODEL_NAME,
	P_COM_PORT_NAME,
	P_COM_PORT_BYTESIZE,
	P_COM_PORT_BAUDRATE,
	P_COM_PORT_PARITY,
	P_COM_PORT_STOPBITS,
	P_VIDEO_STANDARD,	// video composite/component type IFC_VIDEO_COMP_TYPE
	P_BAYER_FILTER,
	P_SATURATION,
	P_HUE,
	P_BAYER_GAIN_RED,
	P_BAYER_GAIN_GREEN,
	P_BAYER_GAIN_BLUE,
	P_FRAME_RESET_GATE, 		// IFC_ENABLE_TYPE
	P_FRAMES_PER_TRIGGER,
	P_STROBE_DURATION,
	P_TRIGGER_DEBOUNCE,
	P_WEN_ENABLE,
	P_WEN_POLARITY,
	P_WEN_VERTICAL_OFFSET,
	P_CAM_PIXEL_SIZE,	// Used to indicate low level camera pixel size when different from P_PIXEL_SIZE

	P_HORZ_ACTIVE,
	P_VERT_ACTIVE,
	P_HORZ_INACTIVE,	// An Horizontal Inactive count applied to all taps involved in an acquisition
	P_VERT_INACTIVE, 	// An Vertical Inactive count applied to all taps involved in an acquisition

	P_VFRAME_TRIGGER_ENABLE,
	P_VFRAME_TRIGGER_POLARITY,
	P_VFRAME_TRIGGER_DEBOUNCE,
	P_FRAME_TRIG_FREQ,


    // Add new types above as needed

	GEN_PARAM_END_MARKER,	// Always keep these three last.
    IFC_LAST_SUP_PARAM = -1, 
    PARAM_NOT_SUPPORTED = 0,
	P_ALL_CAM_PARAMS_ID = 0xa0000000
} COMMON_PARAMS_TYPE;

#define MOD_PECULIAR_PARAM_BASE 0x1000

// List of module common Cnf File Table IDs, grown down begining with MOD_PECULIAR_PARAM_BASE-1
#define IFC_CNF_FILE_UNSUPPORTED_TOKEN  (MOD_PECULIAR_PARAM_BASE-1)

typedef int ACQ_PARAMS_TYPE;


#define LAST_SUPPORT_GROUP -1
#define MAX_NUM_PARAM_GROUPS 0x20


#define MAX_NUM_ACQ_PARAMS 150

/**************************************************************************
***************************************************************************
**
** Parameter manipulation structures
**
***************************************************************************
***************************************************************************
*/
/* supported parameter types */
typedef enum {
    IFC_ENUM_TYPE,
    IFC_INTEGER_TYPE,
    IFC_FLOAT_TYPE,
    IFC_STRING_TYPE,
    IFC_POINTER_TYPE,
    IFC_FLOAT_SET_TYPE,
    IFC_INT_SET_TYPE
} IFC_PARAM_KIND;

/* structure to return float ranges */
typedef struct{
    double Min;
    double Max;
    double Step;
	DWORD regBaseValue;
}IFC_RANGE;


/* arrays to return float/int value sets */
#define MAX_ARRAY_SIZE 32
#define MAX_IFC_PARAM_LEN 80

#define MAX_PARAM_APPLICABLE_LEN 200

/* structure to return enumerated arguments */
typedef struct{
    char *argName;
    double argValue;
	DWORD regValue;
}IFC_ENUM_ARG,*PIFC_ENUM_ARG;

#define MAX_ENUM_ARG_PER_PARAM 16

typedef double (IFCAPI *IFC_PARAM_GET_HANDLER) (CICamera *cam, ACQ_PARAMS_TYPE paramID,DWORD index);
typedef BOOL (IFCAPI *IFC_PARAM_SET_HANDLER) (CICamera *cam, ACQ_PARAMS_TYPE paramID, DWORD index, double data);

typedef BOOL (IFCAPI *IFC_PARAM_APPLICABILITY_QUERY) (CICamera *cam, ACQ_PARAMS_TYPE paramID, DWORD index, char *ReasonNotApplicable);


#define IFC_MAX_PARAM_ARRAY_DIM 10

// Parameter Capability Flags
#define IFC_PARAMCAP_READ_ONLY 1
#define IFC_PARAMCAP_WRITE_ONLY 2
#define IFC_PARAMCAP_READWRITE 0

typedef struct {
    ACQ_PARAMS_TYPE param;		/* enumerated value */
	char *presentationName;		/* Presentation name for the Parameter */
    char paramName[MAX_IFC_PARAM_LEN];      /* string representation of the enumerated value */
    IFC_PARAM_KIND paramType;  /* enumerated:  ENUM_TYPE, IFC_INTEGER_TYPE, IFC_FLOAT_TYPE, */
                                /* IFC_STRING_TYPE, POINTER_TYPE, FLOAT_SET_TYPE, INT_SET_TYPE */
	DWORD		dwArrayDim;		/* normally 1, greater if parameter is a vector */
	DWORD memberGroupMask;		/* Mask which identifies which groups this parameter belongs to */
    IFC_ENUM_ARG enumArgs[MAX_ENUM_ARG_PER_PARAM];    /* used when parameter is enumerated type, must specify in argValue increasing order  */
    IFC_RANGE Range;         /* used when parameter is a float */
    DWORD dwCapFlags;              /* parameter capabilities flag mask */
    DWORD reg[IFC_MAX_PARAM_ARRAY_DIM];
	IFC_PARAM_GET_HANDLER GetHandler;
	IFC_PARAM_SET_HANDLER SetHandler;
	DWORD parentGroupMask;		/* Mask which identifies any parent groups of the groups which this parameter belongs to */
	IFC_PARAM_APPLICABILITY_QUERY ApplTestFunc;
}IFC_PARAM_CAPS,*PIFC_PARAM_CAPS;

#define IFC_MAX_PARM_PRESENT_NAME_LEN 42


typedef enum {
	IFC_PGRP_CAM_TIMING_INPUT=1,// Parameters pertaining to camera timing inputs
	IFC_PGRP_CAM_TIMING_OUTPUT, // Parameters pertaining to camera timing outputs
	IFC_PGRP_MULTI_CAMERA,		// Parameters pertaining to multiple cameras on one board
	IFC_PGRP_GENERAL_ACQ,		// General acquisition parameters, e.g., window generator, pixel depth, pixel color, ...
	IFC_PGRP_TRIGGER,			// Trigger,strobe, frame reset related parameters
	IFC_PGRP_CUSTOM_CAMERA,		// Advanced custom camera definition parameters, e.g. special EXO files
	IFC_PGRP_ANALOG_SETTINGS,	// Parameters which impact an analog signal, e.g., gain,nref,pref,low-pass-filter
	IFC_PGRP_WINDOW_GENERATOR,	// Parameters pertaining to the window generator
	IFC_PGRP_CAM_TIMING,		// Parameters pertaining to camera timing outputs
	IFC_PGRP_PROG_TIMING_GEN,	// Parameters pertaining to the programmable timing generator
	IFC_PGRP_TRIG_STROBE_RESET, // Trigger,strobe, frame reset related parameters
	IFC_PGRP_STROBE,			// Parameters pertaining to camera strobe settings
	IFC_PGRP_FRAME_RESET,		// Parameters pertaining to camera frame reset
	IFC_PGRP_SERIAL_PORT,		// Parameters pertaining to camera control serial port
	IFC_PGRP_CONDITIONING,		// Video signal conditioning, e.g. contrast,brightness,hue, saturation, ...


	IFC_PGRP_MOD_PECULIAR1=0x14,
	IFC_PGRP_MOD_PECULIAR2=0x15,
	IFC_PGRP_MOD_PECULIAR3=0x16,
	IFC_PGRP_MOD_PECULIAR4=0x17,
	IFC_PGRP_MOD_PECULIAR5=0x18,
	IFC_PGRP_MOD_PECULIAR6=0x19,
	IFC_PGRP_MOD_PECULIAR7=0x1a,
	IFC_PGRP_MOD_PECULIAR8=0x1b,
	IFC_PGRP_MOD_PECULIAR9=0x1c,
	IFC_PGRP_MOD_PECULIAR10=0x1d,
	IFC_PGRP_MOD_PECULIAR11=0x1e,
	IFC_PGRP_MOD_PECULIAR12=0x1f,
	IFC_PGRP_NUM_GROUPS,
    IFC_LAST_SUPPORT_PGRP = -1, 
    IFC_GROUP_NOT_SUPPORTED = 0,
	IFC_PGRP_TOP_LEVEL=0x80000000

} IFC_PARAM_GROUP_TYPE;

#define PGRP_ID_TO_MASK(pGrpID) (1<<pGrpID)

#define IFC_PGRP_CAM_TIMING_INPUT_MASK		PGRP_ID_TO_MASK(IFC_PGRP_CAM_TIMING_INPUT)
#define IFC_PGRP_CAM_TIMING_OUTPUT_MASK		PGRP_ID_TO_MASK(IFC_PGRP_CAM_TIMING_OUTPUT)
#define IFC_PGRP_MULTI_CAMERA_MASK			PGRP_ID_TO_MASK(IFC_PGRP_MULTI_CAMERA)
#define IFC_PGRP_GENERAL_ACQ_MASK			PGRP_ID_TO_MASK(IFC_PGRP_GENERAL_ACQ)
#define IFC_PGRP_TRIGGER_MASK				PGRP_ID_TO_MASK(IFC_PGRP_TRIGGER)
#define IFC_PGRP_CUSTOM_CAMERA_MASK			PGRP_ID_TO_MASK(IFC_PGRP_CUSTOM_CAMERA)
#define IFC_PGRP_ANALOG_SETTINGS_MASK		PGRP_ID_TO_MASK(IFC_PGRP_ANALOG_SETTINGS)
#define IFC_PGRP_WINDOW_GENERATOR_MASK		PGRP_ID_TO_MASK(IFC_PGRP_WINDOW_GENERATOR)
#define IFC_PGRP_CAM_TIMING_MASK			PGRP_ID_TO_MASK(IFC_PGRP_CAM_TIMING)
#define IFC_PGRP_PROG_TIMING_GEN_MASK		PGRP_ID_TO_MASK(IFC_PGRP_PROG_TIMING_GEN)
#define IFC_PGRP_TRIG_STROBE_RESET_MASK		PGRP_ID_TO_MASK(IFC_PGRP_TRIG_STROBE_RESET)
#define IFC_PGRP_STROBE_MASK				PGRP_ID_TO_MASK(IFC_PGRP_STROBE)
#define IFC_PGRP_FRAME_RESET_MASK			PGRP_ID_TO_MASK(IFC_PGRP_FRAME_RESET)
#define IFC_PGRP_SERIAL_PORT_MASK			PGRP_ID_TO_MASK(IFC_PGRP_SERIAL_PORT)
#define IFC_PGRP_CONDITIONING_MASK			PGRP_ID_TO_MASK(IFC_PGRP_CONDITIONING)


#define IFC_ALL_PARAM_GROUPS				0xffffffff


typedef BOOL (IFCAPI *IFC_PARAM_GROUP_APPLICABLE_QUERY) (CICamera *cam, IFC_PARAM_GROUP_TYPE groupID, char *ReasonNotApplicable);


typedef struct _IFC_PARAM_GROUP_PROPS IFC_PARAM_GROUP_PROPS,*PIFC_PARAM_GROUP_PROPS;
struct _IFC_PARAM_GROUP_PROPS {
    IFC_PARAM_GROUP_TYPE group;		// enumerated value 
	DWORD groupMask;				// Mask value for this group 
	PIFC_PARAM_GROUP_PROPS childGroups;
	char *presentationName;			// Presentation name for the Parameter 
	char *nickName;					// A shortened form of the presentation name
    char groupName[MAX_IFC_PARAM_LEN];      // string representation of the enumerated value 
	IFC_PARAM_GROUP_APPLICABLE_QUERY ApplTestFunc;
};


#define MAKE_GROUP_ENTRY(groupID,prettyName,nickName)  	{ (IFC_PARAM_GROUP_TYPE)groupID, 1<<groupID, NULL, prettyName, nickName, #groupID }
#define MAKE_PARENT_GROUP_ENTRY(groupID,prettyName,nickName,childGroups,ApplTestFunc)  	{ (IFC_PARAM_GROUP_TYPE)groupID, 1<<groupID, childGroups, prettyName, nickName, #groupID,ApplTestFunc }




#define IFC_GET_ENUM_PARAM(camera,param,paramType) ((paramType)((int)((camera)->GetAcqParam(param))))


#include <ifcpamac.h>



#define NOT_DIRECT_REG_MAP -1
#define PARAM_NULL_ENTRY -1



#define IFC_RULE_START_TOKEN "UartRuleStart"
#define IFC_RULE_END_TOKEN "UartRuleEnd"
#define IFC_RULE_STR_TOKEN "UartStr"

typedef struct {
	ACQ_PARAMS_TYPE paramID;
	double paramVal[IFC_MAX_PARAM_ARRAY_DIM];
} IFC_RULE_PARM;

#define IFC_MAX_PARMS_IN_RULE 6
#define IFC_MAX_RULE_STR_LEN 80


typedef struct _IFC_UART_RULE IFC_UART_RULE;
typedef IFC_UART_RULE *PIFC_UART_RULE;

struct _IFC_UART_RULE {
	IFC_RULE_PARM conditions[IFC_MAX_PARMS_IN_RULE];
	DWORD numConditions;
	BYTE  ruleStr[IFC_MAX_RULE_STR_LEN];
	DWORD numRuleBytes;
	IFC_UART_RULE *next;
};


typedef struct _IFC_CAMERA_DEF_TYPE IFC_CAMERA_DEF_TYPE,*PIFC_CAMERA_DEF_TYPE;

#define IFC_MAX_CAMERA_NAME_LEN 80
#define IFC_MAX_CAMERA_ORIGIN_LEN 200

#define IFC_MAX_SYMBOL_TABLE_ENTRIES 800
#define IFC_MAX_UNSUPPORTED_PARM_LINES 40

struct _IFC_CAMERA_DEF_TYPE {
    char CameraName[IFC_MAX_CAMERA_NAME_LEN];      /* string representation of the camera name */
	IFC_CAMERA_DEF_TYPE *next;
	union {
		struct {
			double m_commonVals[GEN_PARAM_END_MARKER][IFC_MAX_PARAM_ARRAY_DIM];
			double m_peculiarVals[MAX_NUM_ACQ_PARAMS-GEN_PARAM_END_MARKER][IFC_MAX_PARAM_ARRAY_DIM];
		};
		double m_paramVals[MAX_NUM_ACQ_PARAMS][IFC_MAX_PARAM_ARRAY_DIM];
	};
	char CameraOrigin[IFC_MAX_CAMERA_ORIGIN_LEN];
	char UnSupportedParamLines[IFC_MAX_UNSUPPORTED_PARM_LINES][IFC_MAX_CFG_FILE_LINELEN];
	char SrcGroupName[IFC_CONFIG_TOKEN_MAX_LEN];
	IFC_UART_RULE *ruleList;
	void *ModuleSpecific;
};


#define IFC_CAMERA_ORIGIN_INTERNAL "Internal"


#define IFC_MAX_NUM_INPUT_LUTS 4
#define IFC_MAX_NUM_OUTPUT_LUTS 4

#define IFC_PAGE_8BIT_FLAG		0x01
#define IFC_PAGE_10BIT_FLAG		0x02
#define IFC_PAGE_12BIT_FLAG		0x04
#define IFC_PAGE_14BIT_FLAG		0x08
#define IFC_PAGE_16BIT_FLAG		0x10

// Grab Options
#define IFC_GOPT_SINGLE_DEST		0x80000000
#define IFC_GOPT_AUTO_FRAME_LOCK	0x00000001
#define IFC_GOPT_SYSCOLOR_CLIP		0x00000002
#define IFC_GOPT_LEFTJUSTIFIED		0x00000004
#define IFC_GOPT_FRAME_TIME_TAG		0x00000008
#define IFC_GOPT_VERT_PLANAR		0x00000010
#define IFC_GOPT_PLANAR_INIT		0x00000020
#define IFC_GOPT_AUTO_SW_TRIG		0x00000040


// The following are reserved for module peculiar grab options
#define IFC_GOPT_MOD_PECULIAR1		0x00010000
#define IFC_GOPT_MOD_PECULIAR2		0x00020000
#define IFC_GOPT_MOD_PECULIAR3		0x00040000
#define IFC_GOPT_MOD_PECULIAR4		0x00080000

typedef struct {
	int bitDepth;
	int numEntries;
	DWORD pageSizeMask;
} IFC_LUT_CAP_TYPE;

typedef struct {
	int numInputLUTs;		
	IFC_LUT_CAP_TYPE inputLUTs[IFC_MAX_NUM_INPUT_LUTS];
	int numOutputLUTs;
	IFC_LUT_CAP_TYPE outputLUTs[IFC_MAX_NUM_OUTPUT_LUTS];
} LUTCAP;

typedef LUTCAP *LPLUTCAP;

typedef DWORD CAM_ID;

typedef pVOID HIFCGRAB;

typedef DWORD (IFCAPI *IFCLUTFUNC)(DWORD arg ,DWORD *constants); 

typedef enum {
	IFC_NO_TRANSFORM,
	IFC_FLIP_TRANSFORM,		// Top-Bottom Flip
	IFC_MIRROR_TRANSFORM,
	IFC_ROT180_TRANSFORM,

	IFC_NUM_TRANSFORM_KINDS
} IFC_TRANSFORM_TYPE;

#define	IFC_FLIP_TRANSFORM_MASK		0x00000001
#define	IFC_MIRROR_TRANSFORM_MASK	0x00000002
#define	IFC_ROT180_TRANSFORM_MASK	0x00000004


typedef struct {
	DWORD numSurfBufs;
    DDSURFACEDESC   DDSurfDesc;
	LPDIRECTDRAWSURFACE newImageSurface;
	LPDIRECTDRAWSURFACE flipToSurface;

} IFC_ACQ_SURF_DESC;


typedef void *HMSGCALLBACK;

typedef enum {
	IFC_EVENT_START_OF_FIELD,
	IFC_EVENT_START_OF_ODD,
	IFC_EVENT_START_OF_EVEN,
	IFC_EVENT_START_OF_FRAME,

	IFC_EVENT_END_OF_FIELD,
	IFC_EVENT_END_OF_ODD,
	IFC_EVENT_END_OF_EVEN,
	IFC_EVENT_END_OF_FRAME,
	IFC_EVENT_EXTERNAL_TRIGGER,
	IFC_EVENT_VERTICAL_SYNC,	// All VS, even if not grabbing
	IFC_EVENT_NO_HSYNC,
	IFC_EVENT_TRANSFER_COMPLETE,
	IFC_EVENT_TRANSFER_SKIPPED,
	IFC_EVENT_ERROR_PIXEL_CLOCK,
	IFC_EVENT_ERROR_TRIG_SKIPPED,
	IFC_EVENT_END_OF_LINE,


	IFC_NUM_MSG_EVENTS
} IFC_MSG_EVENT_ID;


typedef struct {
	UINT32   counterStamp;     // counter stamp in uS of when event was detected by driver.
	UINT32	eventCount;       // number of this event 
                              // this count should be sequential.  If number is not
                              // sequential then messages were lost because the fifo
                              // was full.
	UINT32   overFlowCount;    // overflow count of fifo (indicates status of fifo when message retrieved)
	IFC_MSG_EVENT_ID eventId;
} IFC_MSG_EVENT_REC;


typedef void (*pMsgCallBackFunc)(IFC_MSG_EVENT_REC *eventMsg,void *pParam);

typedef struct {
	pMsgCallBackFunc cbFunc;
	void *userParam;
} IFC_USER_CALLBACK_REC;

#define IFC_MAX_EVENT_CALLBACKS 8

#include <ICapMod.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CICamera : public CIobject
{
public:

	virtual BOOL RelativeHOffsetSet(double dHoff){return TRUE;}
	virtual double RelativeHOffsetGet(){return 0;}
	virtual BOOL RelativeVOffsetSet(double dVoff){return TRUE;}
	virtual double RelativeVOffsetGet(){return 0;}

	virtual void ReleaseCamFrame(CIFrame *frame);
	virtual CIFrame * GetCamFrame();
	virtual CInterrupt * CreateInterruptObject(ICAP_INTR_EVENT intrEvent,BOOL eventSetting=TRUE);

	virtual void UpdateParams()=0;
	virtual BOOL AcqParamSupported(ACQ_PARAMS_TYPE paramID);
	virtual double GetAcqParam(ACQ_PARAMS_TYPE paramID,DWORD index=0);
	virtual void SetAcqParam(ACQ_PARAMS_TYPE paramID, double value,DWORD index=0);
	virtual void GetParamCaps(ACQ_PARAMS_TYPE paramID,PIFC_PARAM_CAPS lpParamCaps);
	virtual ACQ_PARAMS_TYPE GetFirstParam(DWORD paramGroupMask=IFC_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE);
	virtual ACQ_PARAMS_TYPE GetNextParam(ACQ_PARAMS_TYPE paramID,DWORD paramGroupMask=IFC_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE);

	virtual IFC_PARAM_GROUP_TYPE GetFirstParamGroup(IFC_PARAM_GROUP_TYPE parentGroupID=IFC_PGRP_TOP_LEVEL);
	virtual IFC_PARAM_GROUP_TYPE GetNextParamGroup(IFC_PARAM_GROUP_TYPE groupID);
	virtual void GetGroupProperties(IFC_PARAM_GROUP_TYPE groupID,PIFC_PARAM_GROUP_PROPS lpGroupProps);
	IFC_PARAM_GROUP_TYPE GetParentGroup(IFC_PARAM_GROUP_TYPE childGroupID);


	virtual BOOL GetFirstEnumArg(ACQ_PARAMS_TYPE paramID, IFC_ENUM_ARG *arg);
	virtual BOOL GetNextEnumArg(ACQ_PARAMS_TYPE paramID, IFC_ENUM_ARG *arg);
	virtual BOOL IsArgSupported(ACQ_PARAMS_TYPE paramID, double arg);
	virtual double ClosestArgSupported(ACQ_PARAMS_TYPE paramID, double arg);
	virtual char *GetArgName(ACQ_PARAMS_TYPE paramID, double dArg);
	virtual double GetArgValue(ACQ_PARAMS_TYPE paramID, const char *szArgName);

	virtual BOOL SetLutFunction(LUTID_TYPE lutID,IFCLUTFUNC func,DWORD *constants,LUT_PORTION_TYPE lutPortion=LUT_INTELLI_WIDTH)=0;
	virtual void ReadLutBuf(LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD)=0;
	virtual void WriteLutBuf(LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD)=0;

	virtual BOOL WriteLutToFile(LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, LPTSTR szFileName, LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual BOOL LoadLutFromFile(LUTID_TYPE lutID, LPTSTR szFileName);

	virtual DWORD ReadLutLoc(LUTID_TYPE lutID, DWORD lutAdr,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void WriteLutLoc(LUTID_TYPE lutID,DWORD lutAdr,DWORD val,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void LinearizeLut(LUTID_TYPE lutID,LUT_PORTION_TYPE lutPortion=LUT_INTELLI_WIDTH);
	virtual void FloodLUT(LUTID_TYPE lutID,DWORD val,LUT_PORTION_TYPE lutPortion=LUT_INTELLI_WIDTH);
	virtual void InvertLut(LUTID_TYPE lutID, LUT_PORTION_TYPE lutPortion);
	virtual void ThresholdLut(LUTID_TYPE lutID, const DWORD dwThreshold, LUT_PORTION_TYPE lutPortion);
	virtual void OffsetLut(LUTID_TYPE lutID, const long lOffset, LUT_PORTION_TYPE lutPortion);
	virtual void BitReverseLinearLut(LUTID_TYPE lutID, LUT_PORTION_TYPE lutPortion);
	void MaskedLinearizeLut(LUTID_TYPE lutID,LUT_PORTION_TYPE lutPortion,DWORD mask);
	void LutPassMostSigBits(LUTID_TYPE lutID,LUT_PORTION_TYPE lutPortion,DWORD numBitsToPass);

	virtual void RgbToHsiLUT(LUTID_TYPE lutID, LUT_PORTION_TYPE lutPortion);
	virtual void GetLUTCaps(LPLUTCAP caps);
	virtual void SetLutPathPage(LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum){};

	virtual void SetLutHostPage(LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum,BOOL leftJustify);
		// leftJustify -- Shift LUT entries to the left so that the pixel bits are the most siginificant of 16

	virtual void SetWindowGen(short x, short y, short dx, short dy);
	virtual BOOL SetCameraType(pSTRING camName,BOOL updateHW=TRUE);
	virtual pSTRING GetNextCamType(void);
	virtual pSTRING GetFirstCamType(void);
	virtual pSTRING GetStdCameraType(IFC_STD_CAM_TYPE stdCamType);

	virtual void Snap(void);
	virtual void Grab(void);

	virtual BOOL Grab(pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);

	virtual void GrabLock(int seqNum);
	virtual void GrabRelease(int seqNum);
	virtual int GrabWaitFrame(BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL);
	virtual int GrabFrameSeqNum(int frameRingNum=IFC_FRAME_LAST_RECEIVED);

	virtual HIFCGRAB Grab(DWORD dwOptions,pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, int x=0, int y=0, int dx=0, int dy=0);
	virtual HIFCGRAB Grab(DWORD dwOptions,pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, int x=0, int y=0, int dx=0, int dy=0);
	virtual HIFCGRAB Grab(DWORD dwOptions,pBYTE dest, int ringNumFrames, LPIFC_AOI_DESC aoiDesc,int totalNumFrames=IFC_INFINITE_FRAMES);

	virtual void GrabLock(HIFCGRAB grabID, int seqNum);
	virtual void GrabRelease(HIFCGRAB grabID, int seqNum);
	virtual int GrabWaitFrameEx(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy=NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	virtual int GrabWaitFrameRead(HIFCGRAB grabID,IFC_FRAME_ENCODE encode,BYTE *dest, DWORD *bytesAvailable,int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	static int DecodeFrame(BYTE *src,DWORD numSrcBytes,IFC_FRAME_ENCODE encode, DWORD &dx, DWORD &dy,IFC_COLOR color, DWORD bitsPerPixel, BYTE *dest);

	virtual int GrabFrameSeqNum(HIFCGRAB grabID, int frameRingNum=IFC_FRAME_LAST_RECEIVED);
	virtual int Freeze(HIFCGRAB grabID=NULL);
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);
	virtual BOOL GetGrabStats(HIFCGRAB grabID,IFC_GRAB_STATS *stats);



	virtual BOOL Snap( pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);
	virtual BOOL SeqSnap(pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0,DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	virtual pBYTE SeqSnapPhys(DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDy=NULL);

	virtual BOOL TrigRead(short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(long waitTime);
	virtual BOOL TrigSnap(DWORD trigSource=0);
	virtual BOOL StartTrigOps(void);
	virtual BOOL StopTrigOps(void);

	virtual BOOL SetZoom(float xZoom, float yZoom);
	virtual void GetZoomCaps(LPZOOMCAP lpCaps);
	CICamera(CICapMod *parent, DWORD port);
	virtual ~CICamera();
	virtual BOOL ReadArea (short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0);
	virtual void LineReverseRead (short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr, DWORD readOptions=0);
	virtual void ReadDestPitchArea (short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions=0);
	virtual void GetAttr(LPCAM_ATTR lpAttr, BOOL zoomCorrected=TRUE);
	virtual void GetReadCaps(LPREADCAP lpCaps);
	virtual void SetReadColorRemap(BOOL bEnabled);

	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);
	virtual BOOL EvaluateRules(DWORD dwOptions=0);
	virtual BOOL SetEvaluateRulesState(BOOL enabled=TRUE);

	virtual BOOL WriteUartCommand(BYTE *cmd,DWORD numBytes, DWORD uartIndex=0);
	virtual BOOL ReadUartCommand(BYTE *cmd,DWORD numBytesToRead, DWORD *numBytesRead,DWORD uartIndex=0);
	virtual BOOL UartCommandResponse(BYTE *cmd,DWORD numCmdBytes,BYTE *response,DWORD numBytesToRead, DWORD *numBytesRead,DWORD uartIndex=0);

	virtual BOOL GetUartPortName(char *Name, DWORD uartIndex=0);

	virtual BOOL GetAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf,BOOL lock) {return FALSE;};
	virtual void UnlockAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf){};

#ifdef IFC_MSGS
	virtual HMSGCALLBACK CreateMessageCallback(IFC_MSG_EVENT_ID msgEvent, pMsgCallBackFunc func, LPVOID pParam);
	virtual void DeleteMessageCallback(HMSGCALLBACK hCallback);
	virtual void SendMessage(IFC_MSG_EVENT_ID msgEvent, IFC_MSG_EVENT_REC *eventMsg);
#endif

	BOOL UpdateParamFromCfg(CConfig *cfg,IFC_PARAM_KIND parmType,DWORD numVals,double *paramVal);
	BOOL WriteParamToCfg(CConfig *cfg, IFC_PARAM_KIND parmType, DWORD numVals, double *paramVal);
	BOOL AddParamsToSymbolTable(PIFC_PARAM_CAPS parmTable,ConfigSymbol *SymbolTable);
	BOOL AddUnSupportedParamLine(CConfig *cfg,PIFC_CAMERA_DEF_TYPE camDef);

	double GetStoredVal(PIFC_CAMERA_DEF_TYPE camDef,ACQ_PARAMS_TYPE paramID,DWORD index=0);
	double GetStoredVal(ACQ_PARAMS_TYPE paramID, DWORD index=0);
	BOOL SetStoredVal(PIFC_CAMERA_DEF_TYPE camDef, ACQ_PARAMS_TYPE paramID, double dVal, DWORD index = 0);
	BOOL SetStoredVal(ACQ_PARAMS_TYPE paramID, double dVal, DWORD index = 0);
	char *GetParamName(ACQ_PARAMS_TYPE paramID, char *szName);
	char *ParamValToString(ACQ_PARAMS_TYPE paramID, double dVal, char *szResult);
	double ParamStringToVal(ACQ_PARAMS_TYPE paramID, const char *szVal);
	void WriteCameraParams(PIFC_CAMERA_DEF_TYPE pCam, CConfig *m_cfg,
		                   ACQ_PARAMS_TYPE modParamBase, ACQ_PARAMS_TYPE modParamEnd);

	PF_IFC_PARAM_QUERYUI GetParamQueryUIProcAddress(ACQ_PARAMS_TYPE paramID);
	BOOL QueryUIParamUpdate(double &dVal,ACQ_PARAMS_TYPE paramID,DWORD index=0,void *pParentCWnd=NULL);

	PF_IFC_PARAM_GROUP_EDITDLG GetParamGroupDlgProcAddress(IFC_PARAM_GROUP_TYPE GroupID);
	BOOL ParamGroupEditDlgExist(IFC_PARAM_GROUP_TYPE GroupID);
	BOOL DoParamGroupEditDialog(IFC_PARAM_GROUP_TYPE GroupID, void *pParentCWnd,ACQ_PARAMS_TYPE focalParam=P_ALL_CAM_PARAMS_ID);
	virtual void AddApplicabilityFuncs(void) {};

	BOOL ParamIsApplicable(ACQ_PARAMS_TYPE paramID, DWORD index=0, char *ReasonNotApplicable=NULL);
	BOOL GroupIsApplicable(IFC_PARAM_GROUP_TYPE groupID, char *ReasonNotApplicable=NULL);

	virtual ACQ_PARAMS_TYPE GetParamAlias(ACQ_PARAMS_TYPE paramID);

	void PrintParamAttributes(ACQ_PARAMS_TYPE paramID=P_ALL_CAM_PARAMS_ID,IFC_PARAM_GROUP_TYPE parentGroupID=IFC_PGRP_TOP_LEVEL,HANDLE file=NULL);

	BOOL CameraIsReserved(pSTRING camName=NULL);



	BOOL TransformSupported(IFC_TRANSFORM_TYPE eTransform);
	virtual BOOL SetTransform(IFC_TRANSFORM_TYPE eTransform);
	IFC_TRANSFORM_TYPE GetCurrentTransform(void);
	BOOL QueryUICameraType();

	virtual BYTE *GetDisplayAddr(DWORD options=0) {return NULL;};


	CICapMod *m_parent;
	DWORD m_port;
	float	m_xZoom;
	float	m_yZoom;
	HIFCGRAB m_grabID;

	PIFC_PARAM_CAPS m_supportedParameters;
	PIFC_PARAM_GROUP_PROPS m_supportedGroups;

	PIFC_CAMERA_DEF_TYPE m_CurrentCam;

	PIFC_CAMERA_DEF_TYPE m_camList;	// List of supported camera structures

	IFC_LUT_PIX_SIZE_TYPE m_LUTHostPixSize[IFC_NUM_LUTIDS];
	DWORD m_LUTHostPageNum[IFC_NUM_LUTIDS];
	BOOL m_LUTHostLeftJustify[IFC_NUM_LUTIDS];
	virtual ACQ_PARAMS_TYPE GetParamIndex(ACQ_PARAMS_TYPE RawID)=0;
	DWORD GetPortNum(void) {return m_port;};
	OSHANDLE SetParamAccessMutex(OSHANDLE mutex);

#ifdef IFC_MSGS
	IFC_USER_CALLBACK_REC m_msgEventCallbacks[IFC_NUM_MSG_EVENTS][IFC_MAX_EVENT_CALLBACKS];
#endif

protected:
	BOOL CheckParamTable(void);
	void BuildParamGroupMask(PIFC_PARAM_GROUP_PROPS beginPoint,DWORD curMask=0);

	DWORD m_SupportedTransforms;
	IFC_TRANSFORM_TYPE m_CurrentTransform;
	BOOL m_EvalRulesEnabled;
	char m_lastPortName[20];
	BOOL m_ComPortTimeout;

private:
	OSHANDLE	m_paramAccessMutex;

};
#endif


#if defined( __cplusplus )
extern "C" {
#endif


double IFCCALL IfxRegGetEnumParam(CICamera *cam, int paramIndex,DWORD index);
BOOL IFCCALL IfxRegSetEnumParam(CICamera *cam, int paramIndex, DWORD index, double data);
double IFCCALL IfxRegGetRangeParam(CICamera *cam, int paramIndex,DWORD index);
BOOL IFCCALL IfxRegSetRangeParam(CICamera *cam, int paramIndex, DWORD index, double data);
double IFCCALL IfxRegGetDatasetParam(CICamera *cam, int paramIndex,DWORD index);
BOOL IFCCALL IfxRegSetDataSetParam(CICamera *cam, int paramIndex, DWORD index, double data);



double IFCCALL IfxLutFileGet(CICamera *cam, int parmIndex,DWORD index);
BOOL IFCCALL IfxLutFileSet(CICamera *cam, int parmIndex, DWORD index, double data);


#ifdef __cplusplus
}
#endif





#endif // !defined(AFX_CAMERA_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)


