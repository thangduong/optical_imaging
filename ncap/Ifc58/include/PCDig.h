/******************************************************************************
 *
 * MODULE   
 *		PCDig.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCDig.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:40a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCDig class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999 (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_PCDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_PCDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IMemory.h>



#define PCDIG_MODNAME "PCDig"

/*
** PCDig Interrupt events 
*/
typedef enum {

	PCD_INTR_VB, 	  /* vertical blank */
	PCD_INTR_HB,
	PCD_INTR_TRIG0,
	PCD_INTR_TRIG1,
	PCD_INTR_SOACQ,
	PCD_INTR_EOACQ,
	PCD_INTR_INPORT,
	PCD_INTR_ACQ_ADRS,
	PCD_INTR_BMDONE,
	PCD_INTR_SW_TIMER,


	PCD_INTR_MAX_EVENT  /* MUST be last !!! */
} PCD_INTR_EVENT;


/* Zoom constants  used for subsampling on IC-PCI/PCDig */
typedef enum {
	PCD_ZOOM_INQUIRE=-1,
	PCD_ZOOM_NO=0,
	PCD_ZOOM_X2,
	PCD_ZOOM_X4,
	PCD_ZOOM_X8
} PCD_ZOOM_TYPE;




typedef enum {
	PCD_DISABLED,
	PCD_ENABLED
} PCD_BMTYP;

/* Acqusition register defines: */
typedef enum {
	PCD_FREEZE = 0,
	PCD_SNAP   = 2,
	PCD_GRAB   = 3
} PCD_ACQTYP;


typedef enum {
	PCD_AMCC_REG_SPACE,
	PCD_CONTROL_REG_SPACE,
	PCD_FRAME_BUF_SPACE,
		
	PCD_NUM_ADDR_SPACES
} PCD_ADRSPACE_TYPE;
           

typedef enum {
	PCD_8BIT_1TAP,
	PCD_16BIT_1TAP,
	PCD_24BIT_1TAP,
	PCD_32BIT_1TAP,
	PCD_8BIT_2TAP,
	PCD_8BIT_4TAP,
	PCD_16BIT_2TAP,

	PCD_NUM_SFORMS
} PCD_SFORM_TYPE;



#define PCD_PIX8 8
#define PCD_PIX32 32
#define PCD_PIX24 24

#define PCD_RESET 1
#define ACQ_MUTEX_TIMEOUT 2000 // 2 seconds

#define PCD_PCI_DEVICE_ID       4


#define PCD_DEF_LINE_SCAN_1K "PCDig Standard LineScan 1K"
#define PCD_DEF_AREA_SCAN_1Kx1K "PCDig Standard AreaScan 1Kx1K"


#define PCD_MAX_NUM_OCT_ENTRIES 0x10000

#define PCD_DEFAULT_CAMERA 	PCD_DEF_LINE_SCAN_1K

#define PCD_INFINITE_SEQ_FRAMES 15

#define PCD_NUM_EDESC_SLOTS 0x402


#define PCD_OCT_CHECK_CACHED_ONLY 0

#define PCD_DUMP_ZONE_BUF_SIZE 0x2000

#define PCD_MAX_NUM_AOI_GRAB_RECS 4

#define PCD_GOPT_FAST_FIXED_LEN IFC_GOPT_MOD_PECULIAR1

#include <ICapMod.h>
#include <PcdReg.h>
#include <IFCTyp.h>
#include <PCDFrame.h>
#include <ClrSpace.h>
#include <PCDCam.h>


typedef struct {
	PCD_SFORM_TYPE sForm;
	DWORD numHorzTaps;
	DWORD BMStepSize;
	DWORD numVertTaps;	
} USER_GEO_PROP, *LPUSER_GEO_PROP;

#define USER_GEO_LOAD_FNAME "UserGeometryLoad"
#define USER_GEO_PROP_FNAME "UserGeometryProperties"


typedef DWORD (IFCAPI *PCD_USER_GEO_LOAD)(CPCDig *pcd,DWORD *oct,DWORD srcOffset,DWORD dx,DWORD dy,DWORD bytesPerPixel); 
typedef BOOL (IFCAPI *PCD_USER_GEO_PROP)(CPCDig *pcd,LPUSER_GEO_PROP lpProps); 


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCDig : public CICapMod
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
	void WriteCamera(PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs = TRUE);
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual DWORD RegTableNumEntries(); //  returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); //  returns address of static reg table
	virtual void ModDataInit(); //  initializes module peculiar data
	virtual CICamera * GetCam(DWORD camPortNum);
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CPCDig();
	virtual ~CPCDig();

	virtual BOOL CreateSeqFrame(int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual CIFrame *CreateFrame(DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual void DeleteAllFrames(void);

	virtual void GrabRelease(HIFCGRAB grabID, int seqNum);
	virtual void GrabLock(HIFCGRAB grabID, int seqNum);
	virtual int GrabStop(HIFCGRAB grabID);
	virtual int GrabWaitFrame(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);

	virtual HIFCGRAB Grab(CICamera *camera, DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual int GrabFrameSeqNum(HIFCGRAB grabID,int frameRingNum=IFC_FRAME_LAST_RECEIVED);

	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);

	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL);
	virtual BOOL GetGrabPhysStats(IFC_GRABPHYS_STATS *stats);
	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);


	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);

	virtual HTRIGOP StartTrigOps(CICamera *camera);
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime);
	virtual BOOL TrigSnap(HTRIGOP trigOp,DWORD trigSource=PCD_TMODE_HWTRIG0_ASSERT);
	virtual BOOL StopTrigOps(HTRIGOP trigOp);
	BOOL SetAcqTriggerEvents(PCD_TRIG_MODE_TYPE startEvent , PCD_TRIG_MODE_TYPE stopEvent,DWORD numFramesPerTrig=1);

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
	virtual void ReadDestPitchArea (CPCDFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPCDFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPCDFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
	virtual BOOL ReadArea (CICamera *cam, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0);
	float ReadPerformance(void);

	// Basic Acqusition Functions
	virtual BOOL Freeze(CIFrame *frame);
	virtual BOOL Snap(CIFrame *frame);
	virtual BOOL Grab(CIFrame *frame);
	virtual BOOL SeqGrab(DWORD frameCnt,CIFrame **frames);
	virtual BOOL TrigSnap(CIFrame *frame,DWORD trigSource=0);
	virtual BOOL WaitTrig(CIFrame *frame,long waitTime);
	virtual BOOL SnapAsync(CIFrame *frame);
	virtual BOOL SeqSnap(DWORD frameCnt,CIFrame **frames);
	virtual BOOL SeqSnapAsync(DWORD frameCnt,CIFrame **frames);
	virtual short Acqbits( CIFrame *frame, short mode);
	virtual BOOL WaitAcq(CIFrame *frame);

	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);

	// Internal system element functions
	short LatencyTimer ( short mode);

	void PutAcqStartAddr (DWORD addr);
	DWORD GetAcqStartAddr (void);
	DWORD GetCurrentAcqAddress (void);
	DWORD BmCount (long count);
	BOOL BmFifoFull (void);
	BOOL BmDone (void);
	short BusRequest (short mode);
	short SoftReset (short mode);
	short FifoReset (short mode);

	virtual WORD OutportStrobeVal(IFC_LEVEL_TYPE val,DWORD channelNum=0);
	virtual void OutportVal(WORD val,DWORD channelNum=0);
	virtual void InportMode(BOOL strobed,IFC_EDGE_TYPE latchEdge,DWORD channelNum=0);
	virtual WORD InportVal(DWORD channelNum=0);
	virtual WORD InportInterruptPolarity( IFC_EDGE_TYPE intrEdge,DWORD channelNum=0);

	virtual BOOL FPGAByteWrite(BYTE val);
	virtual BOOL LoadFpga(char *szFpgaFileName);
	PCD_IMAGE_GEOMETRY_TYPE GetBaseGeometry(PCD_IMAGE_GEOMETRY_TYPE eRequestedGeometry,IFC_DEPTH eBitsPerPixel,DWORD numCameras);
	void WriteOCT(CPCDFrame *frame,DWORD srcOffset,DWORD dy);
	void WriteOCTEx(CPCDFrame *frame,DWORD srcOffset,DWORD dy, DWORD aoiDx);
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldStatus(void);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	void DumpGrabStats(HANDLE hFile);
	void ClearGrabStats();
	virtual void ClearFrameBuffer(void);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/
	OSHANDLE		m_AcqMutex;

	CPCDFrame		*m_SchemaFrameids[2];
	DWORD			m_framesInSchema;

	OSHANDLE		m_GrabStartStopMutex;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */
	CPCDCam	*m_pCamera;

protected:
	IFC_DECLARE_DYNCREATE(CPCDig)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);

private:
	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CPCDFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	DWORD BmLockDescSize ( DWORD region);
	BOOL ReadAreaLocked ( CPCDFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	BOOL ReadAreaSmart ( CPCDFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0, BYTE *dest=NULL);

	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	PCD_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	void MakePCDigCamList();
	void WriteBMDestptrs(DWORD *pd,DWORD numPointers);
	void WriteRawOCT( DWORD destIndex,DWORD numEntries);
	char *PcdigGeo2FPGAFiles(char *exoFileStr,DWORD geometry,DWORD bitsPerPixel,IFC_EDGE_TYPE pixelClkPolarity);

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
	DWORD GetOCTCacheEntry(CPCDFrame *frame,DWORD dx, DWORD dy, DWORD srcOffset, BOOL &AlreadyCached, DWORD &numOCTEntries ,DWORD &BmStepVal );
	void ClearOctCache(void);
	pBYTE SeqSnapPhysBig(CICamera *camera, DWORD numFrames, DWORD destOffset, DWORD dwMilliseconds,DWORD *acquiredDys);
	int WaitPhysBigFrame(CICamera *camera,  BYTE **frameAddr, int FrameSeqNum, DWORD dwMilliseconds,DWORD *acquiredDy);


	BOOL ProcessGrabCommand(HANDLE hSpawner);
	void DelSharedScatterList(DWORD &listHandle);


	// The following functions operate on the currently active camera

	CClrSpace *m_clrSpace;
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CPCDCam *m_trigOpCamera;

	DWORD m_OCTTable[PCD_MAX_NUM_OCT_ENTRIES];

	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_VBIntr;
	HANDLE m_grabFMO;
	void *m_grabArea;

    IFC_EDDS            m_dumpzone;		/* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[PCD_DUMP_ZONE_BUF_SIZE];

	ConfigSymbol *m_SymbolTable;	// Initialized if needed during config file operations.
	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	void *m_VixnSeqSnap;


	// Process peculiar grab components
	typedef struct {
		BYTE *dest;
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[PCD_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} PCD_UNIQUE_GRAB_REC;
	PCD_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;
	CIMemory *m_ScatListMem;


	HINSTANCE m_UserGeoLib;
	BOOL m_grabThreadIsRemote;

	DWORD m_numFramesPerTrig;

	friend BOOL IFCAPI PCDigUserGeoSet(CICamera *cam, int parmIndex, DWORD index, double data);
public:
	PCD_USER_GEO_LOAD m_UserGeoLoad;
	PCD_USER_GEO_PROP m_UserGeoProp;

};
#endif

BOOL IFCAPI PCDigCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#ifdef __cplusplus
extern "C" DWORD IFCCALL PCDigMakeForwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
extern "C" DWORD IFCCALL PCDigMakeBackwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
#endif

#endif // !defined(AFX_PCDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
