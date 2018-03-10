/******************************************************************************
 *
 * MODULE   
 *		x64.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/x64.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/15/03 11:33a $
 *
 * ABSTRACT  
 *		IFC interface of the Cx64 class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCx64_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCx64_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define X64_MODNAME "X64-CL"

#define X64_MAX_VID_BUFFERS 3

#define X64_DEF_LINE_SCAN_1K "CamLink Standard LineScan 1K"
#define X64_DEF_AREA_SCAN_1Kx1K "CamLink Standard AreaScan 1Kx1K"



#define X64_MAX_NUM_CAMERAS 4

#define X64_EVENT_MUTEX_WAIT 4000


/*
** PCx64 Interrupt events 
*/
typedef enum {

//	X64_INTR_VB, 	  /* vertical blank */
//	X64_INTR_EOFRM,

	X64_INTR_STATUS_LOCAL_DMA,
	X64_INTR_HOST_LOCAL_BUFFER,
	X64_INTR_PORT_ABC,
	X64_INTR_PORT_DEF,
	X64_INTR_PORT_GH,
	X64_INTR_TRIG,
	X64_INTR_STATUS_LOCAL_DMA2,
	X64_INTR_MSG_LOST,

	X64_INTR_MAX_EVENT,  /* MUST be last !!! */

	X64_INTR_BMDONE,

} X64_INTR_EVENT;


/* Zoom constants  used for subsampling on PCx64 */
typedef enum {
	X64_ZOOM_INQUIRE = -1,
	X64_ZOOM_OUT_NO = 0,
	X64_ZOOM_OUT_X2,
	X64_ZOOM_OUT_X4,
	X64_ZOOM_OUT_X8
} X64_ZOOM_TYPE;




/* Acqusition register defines: */
typedef enum {
	X64_FREEZE = 0,
	X64_SNAP   = 2,
	X64_GRAB   = 3
} X64_ACQTYP;


typedef enum {
//	X64_FRAME_BUF_SPACE,
		
	X64_NUM_ADDR_SPACES
} X64_ADRSPACE_TYPE;
           


#define X64_RESET 1
#define X64_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define X64_BM_MUTEX_TIMEOUT 2000 // 2 seconds
#define X64_FRAME_MUTEX_TIMEOUT 2000 // 2 seconds

#define X64_PCI_DEVICE_ID       0x2064
#define X64_VENDOR_ID 0x11EC




#define X64_DEFAULT_CAMERA 	X64_DEF_LINE_SCAN_1K


#define X64_INFINITE_SEQ_FRAMES 1


#define NUM_SCHEMA_FRAME_IDS 4



#define X64_DUMP_ZONE_BUF_SIZE 0x4000

#define X64_MAX_NUM_AOI_GRAB_RECS 4

typedef void *HX64AUTOREAD;



#define X64_TRI_STATE_OUTPUT_VAL 2


class IFC_EXT_API Cx64;

#include <ICapMod.h>
#include <X64Reg.h>
#include <IFCTyp.h>
#include <ClrSpace.h>

#ifdef _IFCDLL

#include <X64Api.h>
#include <X64int.h>
#include <X64Tbl.h>

#else

typedef void *PCORHW_HOST_BUFFER_LIST;
typedef void *PX64_ACQ_HANDLE;
typedef void *PX64_FUNC_TABLE;
typedef void *PCORHW_ACQ_WINDOW;
typedef void *PX64_DMA_INTERNAL_TO_HOST_TRANSFER;
typedef void *PX64_INTERNAL_BUFFER_HANDLE;
#define CORHW_STATUS						long
typedef void *PCORHW_INT_ROI;
typedef void *PCORHW_VIDEO_FORMAT;
typedef void *PCORHW_DMA_INTERNAL_TO_HOST_TRANSFER;
typedef PVOID X64_TRANSFER_HANDLE;
typedef PVOID *PX64_TRANSFER_HANDLE;


#endif

#include <X64Frame.h>
#include <X64Cam.h>




#ifdef __cplusplus
class IFC_EXT_API Cx64 : public CICapMod
{
public:

	virtual DWORD Revision();
	virtual void ReleaseCamFrame(CICamera * camera, CIFrame * frame);
//	BOOL ActiveCamAttr(LPCAM_ATTR lpAttr);
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
	virtual BOOL BaseAddrInit();

	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	Cx64();
	virtual ~Cx64();
	virtual BOOL CreateSeqFrame(int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual CIFrame *CreateFrame(DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual void DeleteAllFrames(void);

	virtual void GrabRelease(HIFCGRAB grabID, int seqNum);
	virtual void GrabLock(HIFCGRAB grabID, int seqNum);
	virtual int GrabStop(CICamera *cam, HIFCGRAB grabID);
	virtual int GrabWaitFrame(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);

	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual int GrabFrameSeqNum(HIFCGRAB grabID,int frameRingNum=IFC_FRAME_LAST_RECEIVED);

	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);

	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);


	virtual BOOL SetZoom(CICamera *camera,float &xZoom, float &yZoom);
	virtual void GetZoomCaps(CICamera *camera,LPZOOMCAP lpCaps);
	virtual void Freeze(CICamera *camera);
	virtual void Snap(CICamera *camera);
	virtual void Grab(CICamera *camera);
	virtual void ReleaseCamMutex(CICamera *camera);
	virtual CIFrame *GetCamMutex(CICamera *camera);
	virtual void GetReadCaps(LPREADCAP lpCaps);
	virtual void SetReadColorRemap(BOOL bEnabled);

	// Basic Read Area Functions
	virtual void ReadDestPitchArea (Cx64Frame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (Cx64Frame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (Cx64Frame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
	virtual BOOL ReadArea (CICamera *cam, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0);
	float ReadPerformance(void);

	// Basic Acqusition Functions
	virtual BOOL Freeze(CICamera *cam, CIFrame *frame);
	virtual BOOL Snap(CICamera *cam, CIFrame *frame);
	virtual BOOL Grab(CICamera *cam, CIFrame *frame);
	virtual BOOL SeqGrab(CICamera *cam, DWORD frameCnt,CIFrame **frames);
	virtual BOOL SnapAsync(CICamera *cam, CIFrame *frame);
	virtual BOOL SeqSnap(CICamera *cam, DWORD frameCnt,CIFrame **frames, DWORD numDestFrames=1);
	virtual BOOL SeqSnapAsync(CICamera *cam, DWORD frameCnt,CIFrame **frames);
	virtual short Acqbits(CICamera *cam, CIFrame *frame, short mode);
	virtual BOOL WaitAcq(CICamera *cam, CIFrame *frame);

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


	PCORHW_HOST_BUFFER_LIST CreateHostBufList(Cx64Frame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, DWORD *scatList,DWORD numScatEntries);
	PCORHW_HOST_BUFFER_LIST CreateLockHostBufList(Cx64Frame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, pIFC_EDDS scatLists[],DWORD numScatLists,DWORD readOptions);
	HX64AUTOREAD StartAutoRead (CICamera * cam, Cx64Frame *frame,short x,short y,DWORD src_dx,short dy, DWORD numFrames, pIFC_EDDS *lockRegions, DWORD numLockedRegions,DWORD dest_dx, DWORD readOptions);
	BOOL StopAutoRead ( HX64AUTOREAD autoTrans);
	CORHW_STATUS X64BufferNewOnboard(CICamera * cam, PCORHW_DMA_INTERNAL_TO_HOST_TRANSFER pDmaTransfer1, PX64_INTERNAL_BUFFER_HANDLE phX64InternalBuffer);


	BOOL WaitForGrabStopped(CICamera * cam, double waitTimeMillisecs);

	void DeleteHostBufList(PCORHW_HOST_BUFFER_LIST hBufList);

	DWORD PCx64PixelFormat( IFC_COLOR color,	DWORD dwBitsPerPixel);
	BOOL UpdateAcquireHw(CICamera * cam);
	BOOL X64_SetWindow(CICamera * cam, DWORD readOptions=0);
	BOOL UpdateStrobeParams(CICamera * cam);
	BOOL UpdateExsyncParams(CICamera * cam);
	BOOL UpdatePriParams(CICamera * cam);
	BOOL UpdateCamCtlParams(CICamera * cam);


	DWORD GetPCx64FieldOrder(CICamera * cam);
	void MakePCx64CamList();

	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);
	BOOL SetupX64Table();


	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);
	DWORD ProcessTransferEventMessage( void *pMsg, UINT32 loopMsgCount);
	DWORD  EventThreadProc();


	BOOL UpdateTriggerParams(CICamera * cam);
	BOOL GetGeoRoiParams( Cx64Frame *frame , DWORD roiNum, PCORHW_INT_ROI roiParams);
	BOOL GetGeoAcqParams(CICamera * cam, PCORHW_VIDEO_FORMAT videoFormat,  X64_IMAGE_GEOMETRY_TYPE geo);


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();
	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);


	CX64Cam	*m_pCameras[X64_MAX_NUM_CAMERAS];
	CX64Cam	*m_defActiveCamera;


	OS_sem_t	m_ActiveCameraMutex;

	OSHANDLE	m_GrabStartStopMutex;
	OSHANDLE	m_framesMutex;
	BOOL m_insideUpdateParam;

	DWORD m_numPorts;


	ConfigSymbol *m_SymbolTable;
	HX64AUTOREAD m_ycrcbAutoRead;


protected:
	IFC_DECLARE_DYNCREATE(Cx64)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);


	DWORD m_maxSchemaFrames;

private:

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);

	BOOL WaitBmDone (void);
	BOOL ReadAreaLocked ( Cx64Frame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	X64_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(CICamera *cam, pSTRING fname, CIFrame **frames,short acqcmd,short frcnt, DWORD numDestFrames=1);
	BOOL ProcessGrabCommand(HANDLE hSpawner);
	PCORHW_HOST_BUFFER_LIST GetHostBufList( HX64AUTOREAD autoTrans, X64_TRANSFER_HANDLE *transferHandle);
	DWORD TransferSetBufferStatus( HX64AUTOREAD autoTrans, ULONG hostBufIndex, BOOLEAN free);

	BOOL FpgaInUse(void);


	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EofIntr;

	HANDLE m_grabFMO;

	BOOL m_shutDownAuto;
	
	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[X64_MAX_NUM_CAMERAS][X64_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} X64_UNIQUE_GRAB_REC;
	X64_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;

	BOOL m_fFpgaLoaded;



    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[10]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[X64_DUMP_ZONE_BUF_SIZE];

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);

public:
	PX64_FUNC_TABLE m_vf;
	HMODULE m_brdLib;
	DWORD m_boardModel;


};
#endif
// BOOL IFCAPI PCx64CClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#endif // !defined(AFX_PCx64_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
