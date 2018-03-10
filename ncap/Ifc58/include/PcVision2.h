/******************************************************************************
 *
 * MODULE   
 *		PCVision2.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PcVision2.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/04/04 1:53p $
 *
 * ABSTRACT  
 *		IFC interface of the CPCVision2 class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCVision2_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCVision2_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define PCVISION2_MODNAME "PC2Vision"

#define P2V_MAX_VID_BUFFERS 3


#define P2V_CAM_SWITCH_ON
#define P2V_FRAME_LOCK_ON

#define P2V_NULL_PLL_GAIN 255


#define P2V_MAX_NUM_CAMERAS 6
#define P2V_EVENT_MUTEX_WAIT 4000

#define IFC_V2_FE_REG_BASE		0x0
#define IFC_V2_THS8083_REG_BASE 0x100
#define IFC_V2_THS8083_NUM_REG	0x41
#define IFC_V2_DE_REG_BASE		0x1000


#define P2V_GOPT_ALL_CHAN_GRAB IFC_GOPT_MOD_PECULIAR1

typedef enum {
	P2V_FAMILY_P2V,
	P2V_FAMILY_NSP,
	P2V_FAMILY_MEMBERS
} P2V_FAMILY_TYPE;



/*
** PCVision2 Interrupt events 
*/
typedef enum {

	P2V_INTR_VB, 	  
	P2V_INTR_ODD_VB,
	P2V_INTR_EVEN_VB,
	P2V_INTR_EOFRM,

	P2V_INTR_SOT,

	P2V_INTR_BMDONE,
	P2V_INTR_START_OF_FIELD, 	 
	P2V_INTR_START_OF_ODD,
	P2V_INTR_START_OF_EVEN,
	P2V_INTR_START_OF_FRAME,

	P2V_INTR_BMDONE2,
	P2V_INTR_BMDONE3,
	P2V_INTR_SKIPPED_FIELD,
	P2V_INTR_INPORT,
	P2V_INTR_LOSS_OF_SYNC,
	P2V_INTR_TRIG_SKIPPED,
	P2V_INTR_SW_TIMER,
	P2V_INTR_DATAPIN0,
	P2V_INTR_DATAPIN1,
	P2V_INTR_DATAPIN2,
	P2V_INTR_DATAPIN3,
	P2V_INTR_DATAPIN4,
	P2V_INTR_DATAPIN5,
	P2V_INTR_DATAPIN6,
	P2V_INTR_DATAPIN7,

	P2V_INTR_MAX_EVENT  /* MUST be last !!! */
} PCVISION2_INTR_EVENT;


/* Zoom constants  used for subsampling on PCVision2 */
typedef enum {
	P2V_ZOOM_INQUIRE = -1,
	P2V_ZOOM_OUT_NO = 0,
	P2V_ZOOM_OUT_X2,
	P2V_ZOOM_OUT_X4,
	P2V_ZOOM_OUT_X8
} P2V_ZOOM_TYPE;



typedef enum {
	P2V_DISABLED,
	P2V_ENABLED
} P2V_BMTYP;

/* Acqusition register defines: */
typedef enum {
	P2V_FREEZE = 0,
	P2V_SNAP   = 2,
	P2V_GRAB   = 3
} P2V_ACQTYP;


typedef enum {
//	P2V_FRAME_BUF_SPACE,
		
	P2V_NUM_ADDR_SPACES
} P2V_ADRSPACE_TYPE;
           
typedef enum {
	P2V_PLL_MODE_STRIPPED_SYNC,
	P2V_PLL_MODE_SEPARATE_SYNC,
	P2V_XTAL_MODE = 4,
	P2V_VSCAN_MODE = 5
} P2V_TIMING_MODES;




#define P2V_RESET 1
#define P2V_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define P2V_BM_MUTEX_TIMEOUT 2000 // 2 seconds
#define P2V_FRAME_MUTEX_TIMEOUT 2000 // 2 seconds

#define P2V_PCI_DEVICE_ID       0x0200
#define P2V_VENDOR_ID 0x11EC

#define P2V_DEF_RS512x480P "P2V_DEF_RS512x480P"
#define P2V_DEF_RS640x480P "P2V_DEF_RS640x480P"
#define P2V_DEF_CC512x512P "P2V_DEF_CC512x512P"
#define P2V_DEF_CC760x574P "P2V_DEF_CC760x574P"



#define P2V_DEFAULT_CAMERA 	P2V_DEF_RS640x480P
#define P2V_DEFAULT_CAMERA 	P2V_DEF_RS640x480P


#define P2V_INFINITE_SEQ_FRAMES 1

#define P2V_NUM_EDESC_SLOTS 0x400

#define P2V_MHZ_TO_KHZ 1000.0
#define P2V_KHZ_TO_MHZ 0.001
#define P2V_KHZ_TO_HZ  1000.0
#define P2V_HZ_TO_KHZ  0.001


#define NUM_SCHEMA_FRAME_IDS 4



#define P2V_DUMP_ZONE_BUF_SIZE 0x2000

#define P2V_MAX_NUM_AOI_GRAB_RECS 6

typedef void *HP2VAUTOREAD;



#define P2V_TRI_STATE_OUTPUT_VAL 2



#ifdef __cplusplus
class IFC_EXT_API CPCVision2;
#endif

#include <ICapMod.h>
#include <Pv2Reg.h>
#include <IFCTyp.h>
#include <Pv2Frame.h>
#include <ClrSpace.h>

#ifdef _IFCDLL

#include <Pcv2Api.h>
#include <Pcv2Tbl.h>

#else

typedef void *PCORHW_HOST_BUFFER_LIST;
typedef void *PV2_FRAME_DELAY_SEQUENCE;
#define V2_TRANSFER_HANDLE  PVOID
typedef void *PCORHW_MASTER_MODE;
typedef void *PCORHW_VIDEO_FORMAT;
typedef void *PV2_ERR_EVENT_MESSAGE;
typedef void *PV2_FUNC_TABLE;
typedef void *PV2_XFER_MESSAGE;

#endif

#include <Pv2Cam.h>




#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CPCVision2 : public CICapMod
{
public:

	virtual DWORD Revision();
	virtual void ReleaseCamFrame(CICamera * camera, CIFrame * frame);
	BOOL ActiveCamAttr(LPCAM_ATTR lpAttr);
	void Cleanup();
	virtual CIFrame * GetCamFrame(CICamera * cam);
	BOOL InitializeRegs();
	virtual BOOL ModInit();
	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual BOOL ProcessCamerasInConfigFile(const char *szCfgFileName = NULL);
	virtual BOOL ReadUserConfigFile(const char *szCfgFileName);

	pSTRING GetFirstCamType(void);
	pSTRING GetNextCamType(void);
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
	CPCVision2();
	virtual ~CPCVision2();
	virtual BOOL CreateSeqFrame(int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual CIFrame *CreateFrame(DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual void DeleteAllFrames(void);

	virtual void GrabRelease(HIFCGRAB grabID, int seqNum);
	virtual void GrabLock(HIFCGRAB grabID, int seqNum);
	virtual int GrabStop(HIFCGRAB grabID);
	virtual int GrabWaitFrame(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);

	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual int GrabFrameSeqNum(HIFCGRAB grabID,int frameRingNum=IFC_FRAME_LAST_RECEIVED);

	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL);

	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);

	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);


	virtual BOOL SetZoom(CICamera *camera,float &xZoom, float &yZoom);
	virtual BOOL SetZoom(float xZoom, float yZoom);
	virtual void GetZoomCaps(CICamera *camera,LPZOOMCAP lpCaps);
	virtual void Freeze(CICamera *camera);
	virtual void Snap(CICamera *camera);
	virtual void Grab(CICamera *camera);
	virtual void ReleaseCamMutex(CICamera *camera);
	virtual CIFrame *GetCamMutex(CICamera *camera);
	virtual void GetReadCaps(LPREADCAP lpCaps);
	virtual void SetReadColorRemap(BOOL bEnabled);

	// Basic Read Area Functions
	virtual void ReadDestPitchArea (CP2VFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CP2VFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CP2VFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
	virtual BOOL ReadArea (CICamera *cam, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0);
	float ReadPerformance(void);

	// Basic Acqusition Functions
	virtual BOOL Freeze(CIFrame *frame);
	virtual BOOL Snap(CIFrame *frame);
	virtual BOOL Grab(CIFrame *frame);
	virtual BOOL SeqGrab(DWORD frameCnt,CIFrame **frames);
	virtual BOOL SnapAsync(CIFrame *frame);
	virtual BOOL SeqSnap(DWORD frameCnt,CIFrame **frames, DWORD numDestFrames=1);
	virtual BOOL SeqSnapAsync(DWORD frameCnt,CIFrame **frames);
	virtual short Acqbits( CIFrame *frame, short mode);
	virtual BOOL WaitAcq(CIFrame *frame);

	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);
	virtual BOOL IsActiveCamera(pSTRING camName);
	virtual BOOL InterruptEnable(IFC_INTREVENT iEvent, BOOL enable);


	// Internal system element functions

	short SoftReset (short mode);

	virtual WORD OutportStrobeVal(IFC_LEVEL_TYPE val,DWORD channelNum=0);
	virtual void OutportVal(WORD val,DWORD channelNum=0);
	virtual void InportMode(BOOL strobed, IFC_EDGE_TYPE latchEdge, DWORD channelNum = 0);
	virtual WORD InportVal(DWORD channelNum = 0);
	virtual WORD InportInterruptPolarity( IFC_EDGE_TYPE intrEdge,DWORD channelNum=0);

	virtual BOOL LoadFpga(char *szFpgaFileName);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual void ClearFrameBuffer(void);
	virtual PIFC_CAMERA_DEF_TYPE GetCamListRoot(void);
	virtual void SetCamListRoot(PIFC_CAMERA_DEF_TYPE newList);
	virtual BOOL IfxGetBoardParam(IFC_HW_PARAMS eParamId,DWORD *param);
	virtual BOOL SetBoardUartToCOMx(DWORD comNum,DWORD uartIndex=0);



	BOOL SwitchCameraDefineStart(void);
	BOOL SwitchCameraDefineEnd(void);
	BOOL SwitchCameraGrab(void);
	BOOL SwitchCameraSnap(DWORD numFrames=1);
	BOOL SwitchCameraFreeze(void);
	BOOL SetFrameDelaySequence(DWORD *camPortSeq, DWORD numCameras, IFC_TRIG_SRC_TYPE trigSrc);
	BOOL FrameDelaySnap(IFC_TRIG_SRC_TYPE trigSrc, pBYTE dest, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	BOOL FrameDelayWait(DWORD dwMilliseconds=IFC_WAIT_FOREVER);

	
	BOOL GetSyncVals(CP2VCam *cam, DWORD *pValidVideoChannel, DWORD *channelSyncSource, DWORD *connectorSource, P2V_SYNC_SRC_TYPE *pSyncSource=NULL);
	DWORD MapTrigSrcToConn(IFC_TRIG_SRC_TYPE trigSrc, DWORD *llTrigSrc);


	PCORHW_HOST_BUFFER_LIST CreateHostBufList(CP2VFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, DWORD *scatList,DWORD numScatEntries);
	PCORHW_HOST_BUFFER_LIST CreateLockHostBufList(CP2VFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, pIFC_EDDS scatLists[],DWORD numScatLists,DWORD readOptions);
	HP2VAUTOREAD StartAutoRead ( CP2VFrame *frame,short x,short y,DWORD src_dx,short dy, DWORD numFrames, pIFC_EDDS *lockRegions, DWORD numLockedRegions,DWORD dest_dx, DWORD readOptions);
	BOOL StopAutoRead ( HP2VAUTOREAD autoTrans);

	BOOL WaitForGrabStopped(double waitTimeMillisecs);

	void DeleteHostBufList(PCORHW_HOST_BUFFER_LIST hBufList);

	DWORD PCVision2PixelFormat( IFC_COLOR color,	DWORD dwBitsPerPixel);
	BOOL ProgramThs8083(void);
	BOOL UpdateAcquireHw(void);
	BOOL Pv2Ths8083_SetWindow(void);
	BOOL Pv2Ths8083_SetStrobe(void);

	DWORD GetPCVision2FieldOrder(void);
	void MakePCVision2CamList();

	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);

	short			m_fcount;		/* Acquisition frame count */
	short			m_stfield;		/* Starting field select */
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);
	DWORD ProcessTransferEventMessage( void *pMsg, UINT32 loopMsgCount);
	DWORD ProcessAcquireEventMessage( void *pMsg, UINT32 loopMsgCount);
	DWORD ProcessErrorEventMessage( PV2_ERR_EVENT_MESSAGE pMsg, UINT32 loopMsgCount);
	static DWORD  EventThreadProc( CPCVision2 *p2v);

	BOOL UpdateFrameResetParams();
	BOOL UpdateTriggerParams();

	IFC_EDDS *GetTrashBuffer(DWORD trashBufSize);
	DWORD SeqNumToBufIdx(HIFCGRAB grabID,int seqNum);
	BOOL EnableAcqErrorLogging(BOOL enable=TRUE);

	OS_sem_t		m_AcqMutex;


	CP2VFrame		*m_SchemaFrameids[NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();
	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);

	virtual BOOL SetupV2Table();
	virtual BOOL MakeCameras();
	virtual DWORD GetObjectIndex(PV2_XFER_MESSAGE pXferMsg, DWORD seqNum);

	CP2VCam	*m_pCameras[P2V_MAX_NUM_CAMERAS];
	CP2VCam	*m_pActiveCamera;


	OS_sem_t	m_ActiveCameraMutex;

	OSHANDLE	m_GrabStartStopMutex;
	OSHANDLE	m_framesMutex;
	BOOL m_insideUpdateParam;

	DWORD m_numPorts;

	BOOL m_convertTo422On;

	BYTE *m_defaultRingBuf;
	DWORD m_defaultRingNumFrames;
	DWORD m_defaultRingBufSize;
	BYTE *m_defaultRingBufOrig;

	HIFCGRAB m_defGrabId;

	HANDLE m_hXferEventHandleObsolete; // TODO remove on next release
	ConfigSymbol *m_SymbolTable;
	HP2VAUTOREAD m_ycrcbAutoRead;


//	WORD m_wStartPort;


protected:
	IFC_DECLARE_DYNCREATE(CPCVision2)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);


	DWORD m_maxSchemaFrames;
	UINT32   m_OverFlowCount;


	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);

	BOOL WaitBmDone (void);
	CP2VFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	BOOL ReadAreaLocked ( CP2VFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	P2V_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame **frames,short acqcmd,short frcnt, DWORD numDestFrames=1);
	BOOL ProcessGrabCommand(HANDLE hSpawner);
	PCORHW_HOST_BUFFER_LIST GetHostBufList( HP2VAUTOREAD autoTrans, V2_TRANSFER_HANDLE *transferHandle=NULL);

	BOOL FpgaInUse(void);
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CP2VCam *m_trigOpCamera;


	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EofIntr;

	HANDLE m_grabFMO;

	DWORD m_TrashCount;
	DWORD m_CurrentBuffer;
	BOOL m_shutDownAuto;
	
	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[P2V_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} P2V_UNIQUE_GRAB_REC;
	P2V_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;

	BOOL m_fFpgaLoaded;


    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[P2V_DUMP_ZONE_BUF_SIZE];

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);

	BOOL SetFrameDelayValidChannels(HIFCGRAB grabID);
	BOOL GetLastOddFieldStatus(UINT32 boardIndex);


	void *m_switch0TransferHandle;
	UINT32 m_switch0cameraSelector;
	DWORD m_switch0validVideoChannel;
	BYTE *m_switch0Dest;
	DWORD m_numSwitchCams;


	PV2_FRAME_DELAY_SEQUENCE m_frameDelaySeq;
	BOOL m_TrigSeqSet[3];
	DWORD m_fdTriggerSource;
	DWORD m_fdConnectorSource;
	IFC_TRIG_SRC_TYPE m_fdTrigSrc;
	BOOL m_frameDelayActive;
	BOOL m_DoingFrameDelaySnap;
	BOOL m_switchCamDefineEnabled;

	IFC_EDDS *m_TrashScatter;
	BYTE *m_TrashBuf;
	DWORD m_TrashBufSize;
	IFC_EDGE_TYPE m_InportInterruptPolarity;

	PCORHW_MASTER_MODE m_masterModeCache;
	PCORHW_VIDEO_FORMAT m_videoFormatCache;
	BOOL m_AcqErrorLogging;


public:
	PV2_FUNC_TABLE m_vf;
	HMODULE m_brdLib;

	UINT32 m_PixelFormatCache;
	int m_pixelClockSrcCache;
	UINT32 m_clampStartCache;
	UINT32 m_clampStopCache;
	UINT32  m_xminCache;	  			// Number of pixels to crop at the beginning of each line
	UINT32	m_xlenCache;	  			// Number of pixels to acquire per line
	UINT32	m_yminCache;	  			// Number of lines to crop at the beginning of each field
	UINT32	m_ylenCache;	  			// Number of lines to acquire per field
	UINT32	m_scaleXCache;			// Number of pixels output per line after cropping
	UINT32	m_scaleYCache;			// Number of lines output per field after cropping
	UINT32	m_fieldOrderCache;
	UINT32	m_fieldProcessCache;
	int	m_clampEnableCache;
	UINT32 m_wenPolarityCache;
	UINT32 m_wenVerticalOffsetCache;
	int m_wenEnableCache;
	DWORD m_contrastCache;
	int m_brightCache;
	IFC_EDGE_TYPE m_DataPinInterruptPolarity;

};
#endif // #ifdef __cplusplus

#endif // !defined(AFX_PCVision2_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
