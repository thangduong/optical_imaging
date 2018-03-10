/******************************************************************************
 *
 * MODULE   
 *		PCVision.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCVision.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:43a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCVision class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998-1999 (c) Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_PCVISION_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_PCVISION_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <ICapMod.h>
#include <PcvReg.h>
#include <IFCTyp.h>
#include <PCVFrame.h>
#include <ClrSpace.h>


#define PCVISION_MODNAME "PCVision"

/*
** PCVision Interrupt events 
*/
typedef enum {

	PCV_INTR_VB, 	  /* vertical blank */
	PCV_INTR_ODD_VB,
	PCV_INTR_EVEN_VB,
	PCV_INTR_AM,
	PCV_INTR_TRIG,
	PCV_INTR_ACQ_ADRS,
	PCV_INTR_ACQ,
	PCV_INTR_BMDONE,
	PCV_INTR_INPORT,

	PCV_INTR_MAX_EVENT  /* MUST be last !!! */
} PCV_INTR_EVENT;


/* Zoom constants  used for subsampling on IC-PCI/PCVISION */
typedef enum {
	PCV_ZOOM_INQUIRE=-1,
	PCV_ZOOM_NO=0,
	PCV_ZOOM_X2,
	PCV_ZOOM_X4,
	PCV_ZOOM_X8
} PCV_ZOOM_TYPE;



typedef enum {
	PCV_DISABLED,
	PCV_ENABLED
} PCV_BMTYP;

/* Acqusition register defines: */
typedef enum {
	PCV_FREEZE = 0,
	PCV_SNAP   = 2,
	PCV_GRAB   = 3
} PCV_ACQTYP;


typedef enum {
	PCV_32BIT_REG_SPACE,
	PCV_16BIT_REG_SPACE,
	PCV_AMMOD_SPACE,
	PCV_FRAME_BUF_SPACE,
		
	PCV_NUM_ADDR_SPACES
} PCV_ADRSPACE_TYPE;
           

#define PCV_PIX8 8
#define PCV_PIX32 32
#define PCV_PIX24 24

#define PCV_RESET 1
#define ACQ_MUTEX_TIMEOUT 2000			// 2 seconds
#define BM_MUTEX_TIMEOUT 2000			// 2 seconds
#define PCV_NUM_EDESC_SLOTS 0x400		// 1024
#define PCV_DUMP_ZONE_BUF_SIZE 0x2000	// 8192

#define PCV_MAX_NUM_AOI_GRAB_RECS 4
#define PCV_NUM_SCHEMA_FRAME_IDS 4


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCVision : public CICapMod
{
public:
	void SetYCRCBacqMode(BOOL bMode);
	BOOL GetYCRCBacqMode(void);
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldStatus(void);
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldCmd(void);
	virtual BOOL SetInterlaceFirstFieldCmd(IFC_FIELD_STATUS eFirstField);
	virtual DWORD Revision();
	virtual void ReleaseCamFrame(CICamera * camera, CIFrame * frame);
	BOOL ActiveCamAttr(LPCAM_ATTR lpAttr);
	void Cleanup();
	virtual CIFrame * GetCamFrame(CICamera * cam);
	BOOL InitializeRegs();
	virtual BOOL ModInit();
	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual BOOL ReadUserConfigFile(const char *szCfgFileName);
	virtual BOOL ProcessCamerasInConfigFile(const char *szCfgFileName = NULL);
	virtual pSTRING GetFirstCamType(void);
	virtual pSTRING GetNextCamType(void);
	virtual BOOL WriteConfigFile(const char *szCfgFileName, IFC_CFG_CAMERA_SPECIFIER eCamFlag = IFC_CFG_CURRENT_CAMERA, BOOL CreateCamDefs=TRUE);
	virtual BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName);
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual DWORD RegTableNumEntries(); // provided by leaf class returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); // provided by leaf class returns address of static reg table
	virtual void ModDataInit(); // provided by leaf class, initializes module peculiar data
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CPCVision();
	virtual ~CPCVision();

	virtual BOOL CreateSeqFrame(int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual CIFrame *CreateFrame(DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual void DeleteAllFrames(void);

	virtual void GrabRelease(HIFCGRAB grabID, int seqNum);
	virtual void GrabLock(HIFCGRAB grabID, int seqNum);
	virtual int GrabStop(HIFCGRAB grabID);
	virtual int GrabWaitFrame(HIFCGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual HIFCGRAB Grab(CICamera *camera,DWORD dwOptions, pBYTE dests[], int ringNumFrames,int totalNumFrames=IFC_INFINITE_FRAMES, short x=0, short y=0, short dx=0, short dy=0);
	virtual int GrabFrameSeqNum(HIFCGRAB grabID,int frameRingNum=IFC_FRAME_LAST_RECEIVED);
	virtual BOOL GrabGetExtAttr(HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);
	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);



	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);


	virtual HTRIGOP StartTrigOps(CICamera *camera);
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime);
	virtual BOOL TrigSnap(HTRIGOP trigOp,DWORD trigSource=0);
	virtual BOOL StopTrigOps(HTRIGOP trigOp);

	virtual BOOL SetZoom(CICamera *camera,float &xZoom, float &yZoom);
	virtual BOOL SetZoom(float &xZoom, float &yZoom);
	virtual void GetZoomCaps(CICamera *camera,LPZOOMCAP lpCaps);
	virtual void Freeze(CICamera *camera);
	virtual void Snap(CICamera *camera);
	virtual void Grab(CICamera *camera);
	virtual void ReleaseCamMutex(CICamera *camera);
	virtual CIFrame *GetCamMutex(CICamera *camera);
	virtual void GetReadCaps(LPREADCAP lpCaps);
	virtual void SetReadColorRemap(BOOL bEnabled);

	// Basic Read Area Functions

	virtual void ReadDestPitchArea (CPCVFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPCVFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPCVFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
	virtual BOOL ReadArea (CICamera *camera, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0);
	float ReadPerformance(void);

	BOOL ReadPlaneArea (CPCVFrame *frame,short plane,
							 short x,short y,short dx,short dy,pDWORD darray);

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
	virtual BOOL WaitStartVB ( CIFrame *frame);
	virtual BOOL WaitVertBlank (CIFrame *frame);
	virtual BOOL WaitNotVB ( CIFrame *frame, BOOL vbsync);
	virtual BOOL WaitAcq(CIFrame *frame);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);
	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL);
	virtual BOOL GetGrabPhysStats(IFC_GRABPHYS_STATS *stats);


	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual void ClearFrameBuffer(void);




	// Internal system element functions
	short LatencyTimer ( short mode);
	WORD BMIlace ( short mode);
	WORD Pixsz ( short mode);
	short MemSize (void);
	short VblankStatus (void);
	IFC_FIELD_STATUS FieldStatus (void);
	IFC_ILACE ScanModeStatus (void);
	short AmTrigEnable ( short mode);
	short Fcount ( short count);
	BOOL AcqPending (void);
	BOOL AcqInProcess (void);
	short AcqFstart (void);
	short ImagePitch (short pitch, short pixsz);
	void PutBmAoix ( WORD x, short pixsz);
	WORD GetBmAoix (short pixsz);
	void PutBmFirstfStart (DWORD addr);
	DWORD GetBmFirstfStart (void);
	void PutBmSecondfStart (DWORD addr);
	DWORD GetBmSecondfStart (void);
	void PutAcqStartAddr (DWORD addr);
	DWORD GetAcqStartAddr (void);
	DWORD GetCurrentAcqAddress (void);
	DWORD BmCount (long count);
	BOOL BmFifoFull (void);
	BOOL BmDone (void);
	short BusRequest (short mode);
	short SoftReset (short mode);
	short FifoReset (short mode);

	virtual WORD OutportStrobeVal(IFC_LEVEL_TYPE val, DWORD channelNum=0);
	virtual void OutportVal(WORD val, DWORD channelNum=0);
	virtual void InportMode(BOOL strobed,IFC_EDGE_TYPE latch_edge, DWORD channelNum=0);
	virtual WORD InportVal(DWORD channelNum=0);
	virtual WORD InportInterruptpolarity( IFC_EDGE_TYPE intr_edge, DWORD channelNum=0);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	short			m_memsz;		/* Memory Size */
	short			m_amtrig;		/* AM Trigger mode */
	short			m_fcount;		/* Acquisition frame count */
	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/
	short			m_pixszOverride;	/* if nonzero, this value will override icp_pixsz writes */ 	   

	OS_sem_t		m_AcqMutex;

	OSHANDLE		m_GrabStartStopMutex;

	DWORD			m_framesInSchema;
	CPCVFrame		*m_SchemaFrameids[PCV_NUM_SCHEMA_FRAME_IDS];

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */
	HIFCGRAB		m_grabID;


protected:
	IFC_DECLARE_DYNCREATE(CPCVision)

	DWORD* GetFrameBufBaseAddr();
	/* Display API specific. */
	WORD m_sel1,m_sel2;
	IFC_EDDS m_edds1,m_edds1b,m_edds2,m_edds2b;  /*space for more descriptors*/
	BYTE *m_unaligned_buf1,*m_unaligned_buf2;
	BYTE *m_buf1,*m_buf2;
	DWORD m_phys1,m_phys2;
	BOOL m_ppBuffInitFlag;

private:
	HANDLE m_grabFMO;
	void *m_grabArea;


	CInterrupt*		m_AcqAddrIntr;
	CInterrupt*		m_VBIntr;
	BOOL m_SchemaAdjacent;

	// Process peculiar grab components
	typedef struct {
		BYTE *dest;
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[PCV_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} PCV_UNIQUE_GRAB_REC;
	PCV_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;


	void InitPpBuffs(void);
	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL SetLineio (CPCVFrame *frame,short x,short y,pSHORT xsz,pDWORD offadr,pDWORD ilacedata);
	void IlaceData(DWORD field1,DWORD ilacedata,short *pixsz,DWORD *field2);
	BOOL WaitBmDone (void);
	BOOL BmReadArea (CPCVFrame *frame,
		short xsz,DWORD offadr,DWORD ilace,short dx,short dy, pBYTE pmemdest);
	BOOL BmReadPlaneArea (CPCVFrame *frame,short plane,
		short xsz,DWORD offadr,DWORD ilace,short dx,short dy, pBYTE pmemdest);
	CPCVFrame *HostSchemaFrame(LPCAM_ATTR lpAttr,BOOL adjacent=TRUE);
	BOOL ReadAreaLocked(CPCVFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	BOOL BmReadSubregion(DWORD region,DWORD offset,DWORD numbytes);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	PCV_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	BOOL m_pad80;

	BOOL ProcessGrabCommand(HANDLE hSpawner);

	// The following functions operate on the currently active camera

	CClrSpace *clrSpace;
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CICamera *m_trigOpCamera;

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);
};
#endif

#endif // !defined(AFX_PCVISION_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
