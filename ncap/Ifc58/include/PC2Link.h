/******************************************************************************
 *
 * MODULE   
 *		PC2Link.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PC2Link.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/22/04 10:26a $
 *
 * ABSTRACT  
 *		IFC interface of the CPC2Link class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCPC2Link_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCPC2Link_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define CL2_MODNAME "PC2-CamLink"

#define CL2_MAX_VID_BUFFERS 3

#define CL2_DEF_LINE_SCAN_1K "CamLink Standard LineScan 1K"
#define CL2_DEF_AREA_SCAN_1Kx1K "CamLink Standard AreaScan 1Kx1K"

#define CL2_FRAME_LOCK_ON


#define CL2_MAX_NUM_CAMERAS 1
#define CL2_EVENT_MUTEX_WAIT 4000

#define CL2_NUM_EVENT_TYPES 5

/*
** PCPC2Link Interrupt events 
*/
typedef enum {

	CL2_INTR_VB, 	  /* vertical blank */
	CL2_INTR_HB,
	CL2_INTR_EOFRM,
	CL2_INTR_SOT,

	CL2_INTR_BMDONE,

	CL2_INTR_FRAME_SKIPPED,
	CL2_INTR_ERROR_PIXEL_CLOCK,
	CL2_INTR_END_OF_NLINES,
	CL2_INTR_INPORT,
	CL2_INTR_ERROR_LINE_SIZE,


	CL2_INTR_MAX_EVENT  /* MUST be last !!! */
} CL2_INTR_EVENT;


/* Zoom constants  used for subsampling on PCPC2Link */
typedef enum {
	CL2_ZOOM_INQUIRE = -1,
	CL2_ZOOM_OUT_NO = 0,
	CL2_ZOOM_OUT_X2,
	CL2_ZOOM_OUT_X4,
	CL2_ZOOM_OUT_X8
} CL2_ZOOM_TYPE;



/* Acqusition register defines: */
typedef enum {
	CL2_FREEZE = 0,
	CL2_SNAP   = 2,
	CL2_GRAB   = 3
} CL2_ACQTYP;


typedef enum {
//	CL2_FRAME_BUF_SPACE,
		
	CL2_NUM_ADDR_SPACES
} CL2_ADRSPACE_TYPE;
           



#define CL2_RESET 1
#define CL2_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define CL2_BM_MUTEX_TIMEOUT 2000 // 2 seconds
#define CL2_FRAME_MUTEX_TIMEOUT 2000 // 2 seconds

#define CL2_PCI_DEVICE_ID       0x2021
#define CL2_VENDOR_ID 0x11EC


#define CL2_DEFAULT_CAMERA 	CL2_DEF_LINE_SCAN_1K


#define CL2_INFINITE_SEQ_FRAMES 1

#define CL2_NUM_EDESC_SLOTS 0x400


#define CL2_ROPT_CROP_ADJUST_ONLY 0x00010000


#define NUM_SCHEMA_FRAME_IDS 4


#define CL2_DUMP_ZONE_BUF_SIZE 0x2000

#define CL2_MAX_NUM_AOI_GRAB_RECS 4

typedef void *HCL2AUTOREAD;


#define CL2_TRI_STATE_OUTPUT_VAL 2

class IFC_EXT_API CPC2Link;

#include <ICapMod.h>
#include <IFCTyp.h>

#ifdef _IFCDLL

#include <corhw.h>
#include <corhw_err.h>
#include <pc2cl_User.h>
#include <CorHwApiX.h>
#include <CL2Tbl.h>


#ifdef IFC_ENABLE
#undef IFC_ENABLE
#endif

#else

typedef PVOID PCORHW_HOST_BUFFER_LIST;
typedef PVOID CORHW_GRAB_HANDLE;
typedef PVOID PCORHW_GRAB_HANDLE;
typedef PVOID PCORHW_VIDEO_FORMAT;
typedef PVOID PCL2_EVENT_MSG;
typedef PVOID CL2_TRANSFER_HANDLE;
typedef PVOID *PCL2_TRANSFER_HANDLE;
typedef PVOID PCORHWAPIX;
typedef void *PCL2_FUNC_TABLE;


#endif

#include <CL2Reg.h>
#include <CL2Cam.h>
#include <CL2Frame.h>
#include <ClrSpace.h>




#ifdef __cplusplus
class IFC_EXT_API CPC2Link : public CICapMod
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
	CPC2Link();
	virtual ~CPC2Link();
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
	virtual void ReadDestPitchArea (CPC2LinkFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPC2LinkFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPC2LinkFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
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


	PCORHW_HOST_BUFFER_LIST CreateHostBufList(CPC2LinkFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, DWORD *scatList,DWORD numScatEntries);
	PCORHW_HOST_BUFFER_LIST CreateLockHostBufList(CPC2LinkFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, pIFC_EDDS scatLists[],DWORD numScatLists,DWORD readOptions);
	HCL2AUTOREAD StartAutoRead ( CPC2LinkFrame *frame,short x,short y,DWORD src_dx,short dy, DWORD numFrames, pIFC_EDDS *lockRegions, DWORD numLockedRegions,DWORD dest_dx, DWORD readOptions);
	BOOL StopAutoRead ( HCL2AUTOREAD autoTrans);

	BOOL WaitForGrabStopped(double waitTimeMillisecs);

	void DeleteHostBufList(PCORHW_HOST_BUFFER_LIST hBufList);

	DWORD PC2LinkPixelFormat( IFC_COLOR color, DWORD dwBitsPerPixel);
	BOOL ProgramCL2(void);
	BOOL UpdateAcquireHw(void);
	BOOL CL2_SetWindow(DWORD readOptions=0);

	DWORD GetPC2LinkFieldOrder(void);
	void MakePC2LinkCamList();

	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);
	BOOL SetupCL2Table();


	short			m_fcount;		/* Acquisition frame count */
	short			m_stfield;		/* Starting field select */
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);
	DWORD ProcessTransferEventMessage( PCL2_EVENT_MSG pXferMsg, UINT32 loopMsgCount);
	DWORD ProcessAcquireEventMessage( PCL2_EVENT_MSG acqMessage, UINT32 loopMsgCount);
	DWORD ProcessErrorEventMessage( PCL2_EVENT_MSG pMsg, UINT32 loopMsgCount);

	static DWORD  EventThreadProc(CPC2Link *cl2);

	BOOL UpdateStrobeParams(void);
	BOOL UpdateTriggerParams();
	BOOL UpdateExsyncParams();
	BOOL UpdatePriParams();
	BOOL UpdateCamCtlParams();
	BOOL EnableAcqErrorLogging(BOOL enable);


	BOOL GetGeoAcqParams(PCORHW_VIDEO_FORMAT videoFormat, CL2_IMAGE_GEOMETRY_TYPE geo);


	OS_sem_t		m_AcqMutex;


	CPC2LinkFrame	*m_SchemaFrameids[NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();
	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);


	DWORD EventEnable(ULONG eventType,  UINT32 events, BOOL enable=TRUE);


	CLnk2Cam	*m_pCameras[CL2_MAX_NUM_CAMERAS];
	CLnk2Cam	*m_pActiveCamera;


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

	ConfigSymbol *m_SymbolTable;
	HCL2AUTOREAD m_ycrcbAutoRead;


protected:
	IFC_DECLARE_DYNCREATE(CPC2Link)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);


	DWORD m_maxSchemaFrames;
	UINT32   m_OverFlowCount;

private:

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);

	BOOL WaitBmDone (void);
	CPC2LinkFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	BOOL ReadAreaLocked ( CPC2LinkFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	CL2_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame **frames,short acqcmd,short frcnt, DWORD numDestFrames=1);
	BOOL ProcessGrabCommand(HANDLE hSpawner);
	PCORHW_HOST_BUFFER_LIST GetHostBufList( HCL2AUTOREAD autoTrans, CL2_TRANSFER_HANDLE *transferHandle);

	BOOL FpgaInUse(void);
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CLnk2Cam *m_trigOpCamera;


	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EofIntr;

	HANDLE m_grabFMO;

	DWORD m_TrashCount;
	DWORD m_CurrentBuffer;
	
	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[CL2_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} CL2_UNIQUE_GRAB_REC;
	CL2_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;

	BOOL m_fFpgaLoaded;


    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[CL2_DUMP_ZONE_BUF_SIZE];

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);
	DWORD m_eventsEnabled[CL2_NUM_EVENT_TYPES];
	DWORD m_intrRefCount[CL2_INTR_MAX_EVENT];
	BOOL	m_AcqErrorLogging;

public:
	PCL2_FUNC_TABLE m_vf;
	HMODULE m_brdLib;
	DWORD m_lastScan;


};
#endif // #ifdef __cplusplus


#endif // !defined(AFX_PCPC2Link_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
