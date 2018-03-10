/******************************************************************************
 *
 * MODULE   
 *		ICapMod.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ICapMod.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/29/04 5:11p $
 *
 * ABSTRACT  
 *		IFC interface of the CICapMod class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright  (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_ICAPMOD_H__3353EEC3_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_ICAPMOD_H__3353EEC3_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>

#include <ifcclass.h>
typedef CICapMod *PCICapMod;

#define IFC_INFINITE_FRAMES -1
#define IFC_WAIT_NEWER_FRAME -1
#define IFC_MOST_RECENT_FRAME -2
#define IFC_FRAME_LAST_RECEIVED -1

// Interrupt Events supported by Image Capture Modules
typedef enum {
	ICAP_INTR_VB, 		// vertical blank 
	ICAP_INTR_ODD_VB,	// odd vertical blank 
	ICAP_INTR_EVEN_VB,	// even vertical blank 
	ICAP_INTR_AM,		// interrupt from AM daughter module
	ICAP_INTR_TRIG,		// interrupt on start of triggered acquire
	ICAP_INTR_ACQ_ADRS, // interrupt when the board peculiar set acquisition address occurs
	ICAP_INTR_ACQ,		// interrupt on End of Acquisition
	ICAP_INTR_BMDONE,	// interrupt when a BM transfer is complete
	ICAP_INTR_INPORT,	// interrupt when the External In port line goes active
	ICAP_INTR_END_TRIG,	// interrupt on end of triggered acquire
	ICAP_INTR_SOACQ,	// interrupt on Start of Acquisition
	ICAP_INTR_EOF,		// interrupt on End of Frame
	ICAP_INTR_SW_TIMER, // interrupt on Software Timer



	ICAP_INTR_MAX_EVENT  /* MUST be last !!! */
} ICAP_INTR_EVENT;


typedef DWORD HTRIGOP;

typedef DWORD MEMLOCKHDL;


// Define Read Area Options
#define IFC_ROPT_SYSCOLOR_CLIP	0x00000001
#define IFC_ROPT_YCRCBMONO_PAD	0x00000002
#define IFC_ROPT_FLATDRIVER		0x00000004
#define IFC_ROPT_ODD_BYTE_ONLY	0x00000008	// Read only the hi-byte of each 16-bit WORD

#define IFC_ROPT_DONT_WAIT		0x00000010
#define IFC_ROPT_VERT_PLANAR	0x00000020	// read color plane after plane so as to triple the height of the image
#define IFC_ROPT_VERT_DOUBLE	0x00000040
#define IFC_ROPT_AUTO_FRAME_LOCK	0x00000080



#define IFC_ACTIVE_CAMERA_FLAG 0x8000


typedef struct {
	DWORD frameBufNumBytes;

} IFC_IMAGECAP_CAPS;

typedef struct {
	DWORD dwMinTimeConsec;		// Min time between consecutive interrupts since grab started,microseconds
	DWORD dwMaxTimeConsec;		// Max time between consecutive interrupts since grab started,microseconds
	DWORD dwNumBMDoneInterrupts;	// Number of Bus-Master-Complete interrupts since grab started
} IFC_GRABPHYS_STATS;

typedef struct {
	DWORD NumberOfFramesLocked;	 // Number of frames currently locked in the ring buffer
	DWORD NumberOfFramesLost;	// Number of frames aquired but overwritten or lost due to no unlocked space available
	DWORD NumberOfFramesMissed; // Number of frames that the grab service missed, i.e., the grab service was unable to read a frame in time
	DWORD CurrentFrameSeqNum;	// Sequence number of next frame to be received
	DWORD NumberOfFramesAwaitDelivery; // Number of frames in the ring buffer not yet delivered to user via GrabWaitFrameEx
} IFC_GRAB_STATS;


#include <ParntMod.h>
#include <Camera.h>
#include <AcqMod.h>
#include <IFrame.h>
#include <Intrupt.h>




#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CICapMod : public  CParentMod
{
public:
	PCIntrCallback CreateIcapIntrCallback(CICamera *cam, ICAP_INTR_EVENT intrEvent, pIntrCallBackFunc func, LPVOID pParam);
	virtual CInterrupt * CreateInterruptObject(CICamera *cam,ICAP_INTR_EVENT intrEvent,BOOL eventSetting=TRUE);
	virtual BOOL CreateSeqFrame(int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual CIFrame *CreateFrame(DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual void DeleteAllFrames(void){};
	void Cleanup();
	virtual CIFrame *GetCamFrame(CICamera *cam);
	virtual void ReleaseCamFrame(CICamera *camera,CIFrame * frame);

	virtual void GrabRelease(HIFCGRAB grabID, int seqNum){};
	virtual void GrabLock(HIFCGRAB grabID, int seqNum){};
	virtual int GrabStop(HIFCGRAB grabID){return 0;};
	virtual int GrabWaitFrame(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL){return 0;};
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0) {return 0;};
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0) {return 0;};
	virtual int GrabFrameSeqNum(HIFCGRAB grabID,int frameRingNum=IFC_FRAME_LAST_RECEIVED) {return 0;};
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr) {return FALSE;};



	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0,DWORD dwMilliseconds=IFC_WAIT_FOREVER){return 0;};
	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0){return 0;};
	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDys=NULL) {return NULL;};
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL){return 0;};
	virtual BOOL GetGrabPhysStats(IFC_GRABPHYS_STATS *stats) { return FALSE; };
	virtual BOOL GetGrabStats(HIFCGRAB grabID,IFC_GRAB_STATS *stats) { return FALSE; };

	virtual HTRIGOP StartTrigOps(CICamera *camera){return 0;};
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest){return 0;};
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime){return 0;};
	virtual BOOL TrigSnap(HTRIGOP trigOp,DWORD trigSource=0){return 0;};
	virtual BOOL StopTrigOps(HTRIGOP trigOp){return 0;};

	virtual BOOL SetZoom(CICamera *camera,float &xZoom, float &yZoom){return 0;};
	virtual void GetZoomCaps(CICamera *camera,LPZOOMCAP lpCaps){};
	virtual void GetReadCaps(LPREADCAP lpCaps){};
	virtual void SetReadColorRemap(BOOL bEnabled){};
	virtual void Freeze(CICamera *camera){};
	virtual void Snap(CICamera *camera){};
	virtual void Grab(CICamera *camera){};
	virtual void ReleaseCamMutex(CICamera *camera){};
	virtual CIFrame *GetCamMutex(CICamera *camera){return 0;};
	virtual CICamera * GetCam(DWORD camPortNum=IFC_ACTIVE_CAMERA_FLAG);
	virtual pSTRING GetCamPortName(DWORD camPortNum, pSTRING camPortName);
	DWORD NumCamPorts(void);

	virtual BOOL Create(char *modname,DWORD seqnum);
	virtual BOOL Create(DWORD seqnum, char *cfgFile){return 0;};
	virtual BOOL WriteConfigFile(const char *szCfgFileName, IFC_CFG_CAMERA_SPECIFIER eCamFlag = IFC_CFG_CURRENT_CAMERA, BOOL CreateCamDefs=TRUE){return 0;};
	virtual BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName){return 0;};

	virtual WORD OutportStrobeVal(IFC_LEVEL_TYPE val,DWORD channelNum=0){return 0;};
	virtual void OutportVal(WORD val,DWORD channelNum=0){};
	virtual void InportMode(BOOL strobed,IFC_EDGE_TYPE latchEdge,DWORD channelNum=0){};
	virtual WORD InportVal(DWORD channelNum=0){return 0;};
	virtual WORD InportInterruptPolarity( IFC_EDGE_TYPE intrEdge,DWORD channelNum=0){return 0;};

	virtual MEMLOCKHDL LockMem(BYTE *ptr,DWORD dwSize);
	virtual void UnLockMem(MEMLOCKHDL memLockHandle);

	CICapMod();
	virtual ~CICapMod();

	// Basic Acqusition Functions
	virtual BOOL Freeze(CIFrame *frame){return 0;};
	virtual BOOL Snap(CIFrame *frame){return 0;};
	virtual BOOL Grab(CIFrame *frame){return 0;};
	virtual BOOL SeqGrab(DWORD frameCnt,CIFrame **frames){return 0;};
	virtual BOOL TrigSnap(CIFrame *frame,DWORD trigSource=0){return 0;};
	virtual BOOL WaitTrig(CIFrame *frame,long waitTime){return 0;};
	virtual BOOL SnapAsync(CIFrame *frame){return 0;};
	virtual BOOL SeqSnap(DWORD frameCnt,CIFrame **frames){return 0;};
	virtual BOOL SeqSnapAsync(DWORD frameCnt,CIFrame **frames){return 0;};
	virtual short Acqbits( CIFrame *frame, short mode){return 0;};
	virtual BOOL WaitStartVB ( CIFrame *frame){return 0;};
	virtual BOOL WaitVertBlank (CIFrame *frame){return 0;};
	virtual BOOL WaitNotVB ( CIFrame *frame, BOOL vbsync){return 0;};
	virtual BOOL WaitAcq(CIFrame *frame){return 0;};

	virtual void ReadDestPitchArea (CICamera *cam, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions= 0);
	virtual BOOL LineReverseRead (CICamera *cam, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions=0);
	virtual BOOL ReadArea (CICamera *cam, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0) {return 0;};
	virtual float ReadPerformance(void) {return 0.0f;};
	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent){return IFC_INTREVENT_INVALID;};
	PIFC_CAMERA_DEF_TYPE FindCameraType(const char *camName, BOOL camModelDef=FALSE);

	virtual DWORD SetAcqTimeout(DWORD dwMilliSeconds);
	virtual DWORD GetAcqTimeout(void);


	virtual void ProcessCameraFileList(const char *szListFileName);
	virtual void ProcessCameraFilesInDir(const pSTRING szPath, BOOL bRecurse = FALSE);
	virtual pSTRING GetFirstCamType(void){return (pSTRING) NULL;};
	virtual pSTRING GetNextCamType(void){return (pSTRING) NULL;};
	PIFC_CAMERA_DEF_TYPE AddCameraType(pSTRING strNewCamName, pSTRING strExistingCamName,pSTRING strOrigin=NULL,pSTRING strSrcGroup=NULL, BOOL camModelDef=FALSE);
	PIFC_CAMERA_DEF_TYPE AddCameraType(pSTRING strNewCamName, PCICapMod srcMod, pSTRING strExistingCamName,pSTRING strOrigin=NULL,pSTRING strSrcGroup=NULL, BOOL camModelDef=FALSE);
	pSTRING GetFirstCameraModel(void);
	pSTRING GetNextCameraModel(void);

	virtual BOOL SetInterlaceFirstFieldCmd(IFC_FIELD_STATUS eFirstField) {return TRUE;};
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldCmd(void) {return IFC_EVEN_FIELD;};
	virtual BOOL SetScanMode(IFC_ILACE eScanMode) { return TRUE;};
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldStatus(void) {return IFC_EVEN_FIELD;};
	virtual IFC_ILACE GetScanMode(void) { return IFC_NILACED;};

	virtual BOOL IsActiveCamera(pSTRING camName) {return FALSE;};
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps) {return FALSE;};
	virtual void ClearFrameBuffer(void) {};
	virtual PIFC_CAMERA_DEF_TYPE GetCamListRoot(void);
	virtual void SetCamListRoot(PIFC_CAMERA_DEF_TYPE newList);

	virtual void SetActiveCamera(CICamera *camera);

	void MakeCamList(IFC_CAMERA_DEF_TYPE *List,DWORD numDefinitions); // public for benefit of CAcqMod derived classes only
	void ClearCamList(PIFC_CAMERA_DEF_TYPE camList=NULL);
	BOOL EnableJitGrabMemLock(void);

	PIFC_UART_RULE AddRule(PIFC_CAMERA_DEF_TYPE camDef,PIFC_UART_RULE rule=NULL);
	PIFC_UART_RULE AddRule(pSTRING CamName,PIFC_UART_RULE rule=NULL);
	PIFC_UART_RULE GetNextRule(pSTRING CamName, PIFC_UART_RULE currentRule=NULL);
	void DeleteRule(PIFC_CAMERA_DEF_TYPE camcnf, PIFC_UART_RULE rule);
	void DeleteRule(pSTRING CamName, PIFC_UART_RULE rule);
	void DeleteAllRules(PIFC_CAMERA_DEF_TYPE camcnf);

	virtual BOOL SetBoardUartToCOMx(DWORD comNum,DWORD uartIndex=0);


	DWORD ContiguousMemAvailable();
	pBYTE ContiguousMemBaseAddr();


	BOOL DeleteCameraType(pSTRING camName);
	BOOL DeleteCameraModel(pSTRING camModelName);
	DWORD SetMaxSchemaFrames(DWORD maxSchemaFrames);


	CAcqMod *m_acqMod;	// Set to child acquistion module if any, otherwise NULL
	PIFC_CAMERA_DEF_TYPE m_CamListRoot;
	PIFC_CAMERA_DEF_TYPE m_camModelList;
	PIFC_CAMERA_DEF_TYPE m_curCamModel;

	HINSTANCE m_QueryParamUILib;

	DWORD			m_acqTimeout;	/* The number of milliseconds to wait for an acquisition to complete */ 

	DWORD			m_PoolPages;
	DWORD           m_PoolBase;   /* Frame buffer memory pool base */
	CIFrame			*m_frameList;

	DWORD m_ContigPoolSize;
	DWORD m_ContigPoolPhysBase;
	DWORD m_ContigPoolLinearBase;
	DWORD m_SeqSnapPhysMinMaxDiff;
	DWORD m_MaxSchemaFrames;


protected:
	PIFC_CAMERA_DEF_TYPE AddAfter(PIFC_CAMERA_DEF_TYPE node, PIFC_CAMERA_DEF_TYPE cnf);
	PIFC_CAMERA_DEF_TYPE AddCameraType(pSTRING camName, BOOL camModelDef=FALSE);
	virtual DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	virtual void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);


	DWORD m_BMCtlRegID;
	BOOL m_JitGrabLockEnabled;

	IFC_DECLARE_DYNCREATE(CICapMod)
};
#endif

#if defined( __cplusplus )
extern "C" {
#endif


LPVOID IFCCALL IfxCICapModRuntimeClass();


#ifdef __cplusplus
}
#endif



#endif // !defined(AFX_ICAPMOD_H__3353EEC3_86BB_11D1_A574_00A0C959E757__INCLUDED_)
