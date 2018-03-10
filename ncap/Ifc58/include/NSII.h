/******************************************************************************
 *
 * MODULE   
 *		NSII.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/NSII.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/16/04 3:03p $
 *
 * ABSTRACT  
 *		IFC interface of the CNetSightII class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_NetSightII_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_NetSightII_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define NETSIGHTII_MODNAME "NetSight-II"

#define NSP_MAX_VID_BUFFERS 3


#define NSP_CAM_SWITCH_ON
#define NSP_FRAME_LOCK_ON



#define NSP_MAX_NUM_CAMERAS 3
#define NSP_EVENT_MUTEX_WAIT 4000


#define NSP_GOPT_ALL_CHAN_GRAB IFC_GOPT_MOD_PECULIAR1

/*
** NSPlus Interrupt events 
*/
typedef enum {

	NSP_INTR_VB, 	  
	NSP_INTR_ODD_VB,
	NSP_INTR_EVEN_VB,
	NSP_INTR_EOFRM,

	NSP_INTR_SOT,

	NSP_INTR_BMDONE,
	NSP_INTR_START_OF_FIELD, 	 
	NSP_INTR_START_OF_ODD,
	NSP_INTR_START_OF_EVEN,
	NSP_INTR_START_OF_FRAME,

	NSP_INTR_BMDONE2,
	NSP_INTR_BMDONE3,
	NSP_INTR_SKIPPED_FIELD,
	NSP_INTR_INPORT,
	NSP_INTR_LOSS_OF_SYNC,
	NSP_INTR_TRIG_SKIPPED,
	NSP_INTR_SW_TIMER,
	NSP_INTR_AIO_FIFO_OVERFLOW,
	NSP_INTR_AIO_DECISION_ABSENT,
	NSP_INTR_AIO_DECISION_LATE,

	NSP_INTR_DATAPIN0,
	NSP_INTR_DATAPIN1,
	NSP_INTR_DATAPIN2,
	NSP_INTR_DATAPIN3,
	NSP_INTR_DATAPIN4,
	NSP_INTR_DATAPIN5,
	NSP_INTR_DATAPIN6,
	NSP_INTR_DATAPIN7,

	NSP_INTR_MAX_EVENT  /* MUST be last !!! */
} NETSIGHTPLUS_INTR_EVENT;


/* Zoom constants  used for subsampling on NSPlus */
typedef enum {
	NSP_ZOOM_INQUIRE = -1,
	NSP_ZOOM_OUT_NO = 0,
	NSP_ZOOM_OUT_X2,
	NSP_ZOOM_OUT_X4,
	NSP_ZOOM_OUT_X8
} NSP_ZOOM_TYPE;



typedef enum {
	NSP_DISABLED,
	NSP_ENABLED
} NSP_BMTYP;

/* Acqusition register defines: */
typedef enum {
	NSP_FREEZE = 0,
	NSP_SNAP   = 2,
	NSP_GRAB   = 3
} NSP_ACQTYP;


typedef enum {
//	NSP_FRAME_BUF_SPACE,
		
	NSP_NUM_ADDR_SPACES
} NSP_ADRSPACE_TYPE;
           
typedef enum {
	NSP_PLL_MODE_STRIPPED_SYNC,
	NSP_PLL_MODE_SEPARATE_SYNC,
	NSP_XTAL_MODE = 4,
	NSP_VSCAN_MODE = 5
} NSP_TIMING_MODES;



typedef enum {
	NSP_8_BIT_RED_CHANNEL,
	NSP_8_BIT_GREEN_CHANNEL,
	NSP_8_BIT_BLUE_CHANNEL,
	NSP_8_BIT_ALPHA_CHANNEL,
	NSP_32_BIT_ALPHA_RGB,
	NSP_IN_MODE_RESERVED1,
	NSP_16_BIT_YCBCR_4_2_2,
	NSP_16_BIT_YCRCB_4_2_2,
	NSP_24_BIT_PACKED,
	NSP_32_BIT_PLANAR = 0xC,
} NSP_IN_MODE_TYPE;

#define NSP_RESET 1
#define NSP_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define NSP_BM_MUTEX_TIMEOUT 2000 // 2 seconds
#define NSP_FRAME_MUTEX_TIMEOUT 2000 // 2 seconds

#define NSP_PCI_DEVICE_ID       0x2011
#define NSP_VENDOR_ID 0x11EC

#define NSP_DEF_RS512x480P "NSP_DEF_RS512x480P"
#define NSP_DEF_RS640x480P "NSP_DEF_RS640x480P"
#define NSP_DEF_CC512x512P "NSP_DEF_CC512x512P"
#define NSP_DEF_CC760x574P "NSP_DEF_CC760x574P"



#define NSP_DEFAULT_CAMERA 	NSP_DEF_RS640x480P
#define NSP_DEFAULT_CAMERA 	NSP_DEF_RS640x480P


#define NSP_INFINITE_SEQ_FRAMES 1

#define NSP_NUM_EDESC_SLOTS 0x400


#define NSP_XTAL_FREQ_MHZ 14.31818
#define NSP_XTAL_FREQ_KHZ 14318.18

#define NSP_MHZ_TO_KHZ 1000.0
#define NSP_KHZ_TO_MHZ 0.001
#define NSP_KHZ_TO_HZ  1000.0
#define NSP_HZ_TO_KHZ  0.001


#define NUM_SCHEMA_FRAME_IDS 4


typedef enum {

	NSP_LUT1_HIGH_BYTE_OUT,
	NSP_STATIC_PAGE_ADDR

} NSP_LUT2_ADDR_TYPE;


#define NSP_DUMP_ZONE_BUF_SIZE 0x2000

#define NSP_MAX_NUM_AOI_GRAB_RECS 6

typedef void *HNSPAUTOREAD;



#define NSP_TRI_STATE_OUTPUT_VAL 2
#define NSP_OUTPUT_LED1_CHAN 4
#define NSP_OUTPUT_LED2_CHAN 5
#define NSP_OUTPUT_LED3_CHAN 6
#define NSP_OUTPUT_LED4_CHAN 7
#define NSP_OUTPUT_LED5_CHAN 8
#define NSP_OUTPUT_LED6_CHAN 9



#ifdef __cplusplus
class IFC_EXT_API CNetSightII;
#endif

#include <ICapMod.h>
#include <Pv2Reg.h>
#include <IFCTyp.h>
#include <Pv2Frame.h>
#include <ClrSpace.h>
#include <PCVision2.h>


#ifdef _IFCDLL

#include <nspapi.h>
#include <Pcv2Tbl.h>

#ifdef NET_SIGHT_PLUS
#include <nspTbl.h>
#else
typedef void *PNSP_FUNC_TABLE;
#endif

#else

typedef void *PCORHW_HOST_BUFFER_LIST;
typedef void *PV2_FRAME_DELAY_SEQUENCE;
#define V2_TRANSFER_HANDLE  PVOID
typedef void *PCORHW_MASTER_MODE;
typedef void *PCORHW_VIDEO_FORMAT;
typedef void *PV2_ERR_EVENT_MESSAGE;
typedef void *PV2_FUNC_TABLE;
typedef void *PNSP_FUNC_TABLE;
typedef void *CORHW_AIO_HANDLE;

#endif

#include <NspCam.h>




#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CNetSightII : public CPCVision2
{
public:

	virtual DWORD Revision();
	BOOL ActiveCamAttr(LPCAM_ATTR lpAttr);
	void Cleanup();
	BOOL InitializeRegs();
	virtual BOOL ModInit();
	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);

	virtual BOOL WriteConfigFile(const char *szCfgFileName, IFC_CFG_CAMERA_SPECIFIER eCamFlag = IFC_CFG_CURRENT_CAMERA, BOOL CreateCamDefs=TRUE);
	virtual BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName);
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual DWORD RegTableNumEntries(); //  returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); //  returns address of static reg table
	virtual void ModDataInit(); //  initializes module peculiar data
	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CNetSightII();
	virtual ~CNetSightII();


	virtual void GetZoomCaps(CICamera *camera,LPZOOMCAP lpCaps);



	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);
	virtual BOOL InterruptEnable(IFC_INTREVENT iEvent, BOOL enable);

	// Internal system element functions

	short SoftReset (short mode);

	virtual WORD OutportStrobeVal(IFC_LEVEL_TYPE val,DWORD channelNum=0);
	virtual void OutportVal(WORD val,DWORD channelNum=0);
	virtual void InportMode(BOOL strobed, IFC_EDGE_TYPE latchEdge, DWORD channelNum = 0);
	virtual WORD InportVal(DWORD channelNum = 0);
	virtual WORD InportInterruptPolarity( IFC_EDGE_TYPE intrEdge,DWORD channelNum=0);

	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual PIFC_CAMERA_DEF_TYPE GetCamListRoot(void);
	virtual void SetCamListRoot(PIFC_CAMERA_DEF_TYPE newList);
	virtual BOOL IfxGetBoardParam(IFC_HW_PARAMS eParamId,DWORD *param);
	virtual BOOL SetBoardUartToCOMx(DWORD comNum,DWORD uartIndex=0);
	
	DWORD MapTrigSrcToConn(IFC_TRIG_SRC_TYPE trigSrc, DWORD *llTrigSrc);

	void MakeNetSightPlusCamList();
	virtual BOOL SeqGrab(DWORD frameCnt,CIFrame **frames);
	virtual BOOL SeqSnapAsync(DWORD frameCnt,CIFrame **frames);
	virtual BOOL Freeze(CIFrame *frame);


	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);

	BOOL AdvancedIOStart();
	BOOL AdvancedIOStop();
	BOOL AdvancedIOPause();
	BOOL AdvancedIOEnqueueDecision(NSP_REJECTOR_ID_TYPE rejectorID, DWORD objectIndex, NSP_AIO_DECISION_TYPE decision);

	DWORD SeqNumToBufIdx(HIFCGRAB grabID,int seqNum);
	BOOL EnableAcqErrorLogging(BOOL enable=TRUE);


	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);

	virtual BOOL SetupV2Table();
	virtual BOOL MakeCameras();
	virtual DWORD GetObjectIndex(PV2_XFER_MESSAGE pXferMsg, DWORD seqNum);

	long ConfigAdvancedIO();
	long ConfigAdvancedIOCorhw();



	PNSP_FUNC_TABLE m_vfNsp;
	CORHW_AIO_HANDLE  m_hAIO;
	DWORD mLastObjectIndex;

protected:
	IFC_DECLARE_DYNCREATE(CNetSightII)



private:

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);


};

#endif // #ifdef __cplusplus

#endif // !defined(AFX_NetSightPlus_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
