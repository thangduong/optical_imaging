/******************************************************************************
 *
 * MODULE   
 *		PCLink.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCLink.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/24/03 9:55a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCLink class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_PCLink_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_PCLink_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IMemory.h>


#define PCCamLink_MODNAME "PCCamLink"

/*
** PCLink Interrupt events 
*/
typedef enum {

	LNK_INTR_VB, 	  /* vertical blank */
	LNK_INTR_HB,
	LNK_INTR_TRIG0,
	LNK_INTR_TRIG1,
	LNK_INTR_SOACQ,
	LNK_INTR_EOACQ,
	LNK_INTR_INPORT,
	LNK_INTR_ACQ_ADRS,
	LNK_INTR_BMDONE,
	LNK_INTR_SW_TIMER,
	LNK_INTR_SOFEN,


	LNK_INTR_MAX_EVENT  /* MUST be last !!! */
} LNK_INTR_EVENT;


/* Zoom constants  used for subsampling on PCLink */
typedef enum {
	LNK_ZOOM_INQUIRE=-1,
	LNK_ZOOM_NO=0,
	LNK_ZOOM_X2,
	LNK_ZOOM_X4,
	LNK_ZOOM_X8
} LNK_ZOOM_TYPE;



typedef enum {
	LNK_DISABLED,
	LNK_ENABLED
} LNK_BMTYP;

/* Acqusition register defines: */
typedef enum {
	LNK_FREEZE = 0,
	LNK_SNAP   = 2,
	LNK_GRAB   = 3
} LNK_ACQTYP;


typedef enum {
	LNK_AMCC_REG_SPACE,
	LNK_CONTROL_REG_SPACE,
	LNK_FRAME_BUF_SPACE,

		
	LNK_NUM_ADDR_SPACES
} LNK_ADRSPACE_TYPE;
           

typedef enum {
	LNK_8BIT_1TAP,
	LNK_16BIT_1TAP,
	LNK_24BIT_1TAP,
	LNK_32BIT_1TAP,
	LNK_8BIT_2TAP,
	LNK_8BIT_4TAP,
	LNK_16BIT_2TAP,
	LNK_16BIT_1TAP_AC,

	LNK_NUM_SFORMS,
	LNK_NO_SFORM=0xffff
} LNK_SFORM_TYPE;


// value of type LNK_PORTIO_CHANNELS is used as channelNum for functions such as OutportVal,InportVal
typedef enum {
	LNK_PARALLEL_IO_CHAN,
	LNK_TTL0_IO_CHAN,
	LNK_TTL1_IO_CHAN,
	LNK_TTL2_IO_CHAN,
	LNK_DIFF0_IO_CHAN,
	LNK_DIFF1_IO_CHAN,
	LNK_OPTO0_IO_CHAN,
	LNK_OPTO1_IO_CHAN

} LNK_PORTIO_CHANNELS;


#define LNK_PIX8 8
#define LNK_PIX32 32
#define LNK_PIX24 24

#define LNK_RESET 1
#define ACQ_MUTEX_TIMEOUT 2000 // 2 seconds

#define LNK_PCI_DEVICE_ID       8

#define LNK_DEF_LINE_SCAN_1K "CamLink Standard LineScan 1K"
#define LNK_DEF_AREA_SCAN_1Kx1K "CamLink Standard AreaScan 1Kx1K"

#define LNK_MAX_OCT_ENTRIES 0x40000

#define LNK_DEFAULT_CAMERA 	LNK_DEF_LINE_SCAN_1K

#define LNK_INFINITE_SEQ_FRAMES 15


#define LNK_OCT_CHECK_CACHED_ONLY 0

#define LNK_DUMP_ZONE_BUF_SIZE 0x2000

#define LNK_MAX_NUM_AOI_GRAB_RECS 4

#define LNK_MIN_NUM_FRABUF_POOL_PAGES 0x1000   // 16MB


// PCLink Grab options

typedef struct {
	LNK_SFORM_TYPE sForm;
	DWORD numHorzTaps;
	DWORD BMStepSize;
	DWORD numVertTaps;	
} LNK_USER_GEO_PROP, *LPLNK_USER_GEO_PROP;



#define LNK_USER_GEO_LOAD_FNAME "UserGeometryLoad"
#define LNK_USER_GEO_PROP_FNAME "UserGeometryProperties"



#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CPCLink;

#include <ICapMod.h>
#include <LnkReg.h>
#include <IFCTyp.h>
#include <LnkFrame.h>
#include <ClrSpace.h>
#include <LnkCam.h>





typedef DWORD (IFCAPI *pfLNK_USER_GEO_LOAD)(CPCLink *pcl,DWORD *oct,DWORD srcOffset,DWORD dx,DWORD dy,DWORD bytesPerPixel); 
typedef BOOL (IFCAPI *pfLNK_USER_GEO_PROP)(CPCLink *pcl,LPLNK_USER_GEO_PROP lpProps); 


class IFC_EXT_API CPCLink : public CICapMod
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
	CPCLink();
	virtual ~CPCLink();

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


	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL);

	virtual BOOL GetGrabPhysStats(IFC_GRABPHYS_STATS *stats);
	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);


	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);

	virtual HTRIGOP StartTrigOps(CICamera *camera);
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime);
	virtual BOOL TrigSnap(HTRIGOP trigOp,DWORD trigSource=LNK_TMODE_HWTRIG0_ASSERT);
	virtual BOOL StopTrigOps(HTRIGOP trigOp);
	BOOL SetAcqTriggerEvents(LNK_TRIG_MODE_TYPE startEvent , LNK_TRIG_MODE_TYPE stopEvent,DWORD numFramesPerTrig=1);

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
	virtual void ReadDestPitchArea (CLinkFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CLinkFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CLinkFrame *frame, int x, int y, int dx, int dy, pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
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

	void ControlOutportVal(LNK_CAM_CTL_SELECT_TYPE val, LNK_PORTIO_CHANNELS channelNum);

	virtual BOOL FPGAByteWrite(BYTE val);
	virtual BOOL LoadFpga(char *szFpgaFileName);
	LNK_IMAGE_GEOMETRY_TYPE GetBaseGeometry(LNK_IMAGE_GEOMETRY_TYPE eRequestedGeometry,IFC_DEPTH eBitsPerPixel,DWORD numCameras);
	LNK_SFORM_TYPE PCLinkGeo2Sform(DWORD geometry,DWORD bitsPerPixel);
	void WriteOCT(CLinkFrame *frame,DWORD srcOffset,DWORD dy);
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldStatus(void);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual void ClearFrameBuffer(void);


	void ClearOctCache(void);
	void ClearDmaCache(void);
	BOOL ReadAreaSmart ( CLinkFrame *frame,short x,short y,DWORD srcDx, DWORD dy, DWORD lockRegion, 
							DWORD regionOffset, DWORD destDx, DWORD readOptions, BYTE *dest);



	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/
	OSHANDLE		m_AcqMutex;

	CLinkFrame		*m_SchemaFrameids[2];
	DWORD			m_framesInSchema;

	OSHANDLE		m_GrabStartStopMutex;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */
	CLinkCam	*m_pCamera;

protected:
	IFC_DECLARE_DYNCREATE(CPCLink)


private:
	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CLinkFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	DWORD BmLockDescSize ( DWORD region);
	BOOL ReadAreaLocked ( CLinkFrame *frame,int x,int y,DWORD src_dx,int dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);

	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	LNK_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	void MakePCLinkCamList();
	void WriteBMDestptrs(DWORD *pd,DWORD numPointers);
	void WriteRawBMDestptrs(DWORD destIndex, DWORD *pd, DWORD numPointers,BOOL AlreadyCached);

	void WriteRawOCT( DWORD destIndex,DWORD numEntries);
	char *PCLinkGeo2FPGAFiles(char *exoFileStr,DWORD geometry,DWORD bitsPerPixel);

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
	DWORD GetOCTCacheEntry(CLinkFrame *frame,DWORD dx, DWORD dy, DWORD srcOffset, BOOL &newEntry,DWORD numOCTEntries, DWORD &BmStepVal );


	BOOL ProcessGrabCommand(HANDLE hSpawner);
	void DelSharedScatterList(DWORD &listHandle);

	// The following functions operate on the currently active camera

	CClrSpace *m_clrSpace;
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CLinkCam *m_trigOpCamera;

	DWORD m_OCTTable[LNK_MAX_OCT_ENTRIES];

	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_VBIntr;
	HANDLE m_grabFMO;
	void *m_grabArea;

    IFC_EDDS            m_dumpzone;		/* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[LNK_DUMP_ZONE_BUF_SIZE];

	ConfigSymbol *m_SymbolTable;	// Initialized if needed during config file operations.
	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	void *m_VixnSeqSnap;


	// Process peculiar grab components
	typedef struct {
		BYTE *dest;
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[LNK_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} LNK_UNIQUE_GRAB_REC;
	LNK_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;


	HINSTANCE m_UserGeoLib;
	BOOL m_grabThreadIsRemote;

	friend BOOL IFCAPI PCLinkUserGeoSet(CICamera *cam, int parmIndex, DWORD index, double data);
public:
	pfLNK_USER_GEO_LOAD m_UserGeoLoad;
	pfLNK_USER_GEO_PROP m_UserGeoProp;
	DWORD m_numOctEntries;
	DWORD m_numScatterListSlots;
	DWORD m_numLutEntries;
	DWORD m_numFramesPerTrig;
	CIMemory *m_ScatListMem;

};
#endif

BOOL IFCAPI PCLinkCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#ifdef __cplusplus
extern "C" DWORD IFCCALL PCLinkMakeForwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
extern "C" DWORD IFCCALL PCLinkMakeBackwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
#endif

#endif // !defined(AFX_PCLink_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
