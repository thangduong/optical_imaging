/******************************************************************************
 *
 * MODULE   
 *		PcPlus.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCPlus.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/04/04 9:23a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCVisionPlus class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999, 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCVPLUS_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCVPLUS_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IMemory.h>

#define PCVISIONPLUS_MODNAME "PCVisionplus"

/*
** PCVPlus Interrupt events 
*/
typedef enum {

	PCP_INTR_SOT,
	PCP_INTR_EOT,
	PCP_INTR_INPORT,
	PCP_INTR_SW_TIMER,
	PCP_INTR_VB,
	PCP_INTR_EVEN_VB,
	PCP_INTR_ODD_VB,

	PCP_INTR_ACQ_ADRS,
	PCP_INTR_BMDONE,
	PCP_INTR_AM_CASCADE,
	PCP_INTR_EOFRM,

	PCVPLUS_INTR_MAX_EVENT  /* MUST be last !!! */
} PCVPLUS_INTR_EVENT;


/* Zoom constants  used for subsampling and zooming on PCVPlus */
typedef enum {
	PCP_ZOOM_NONE,
	PCP_ZOOM_IN_X2,
	PCP_ZOOM_IN_X4,
	PCP_ZOOM_OUT_X2,
} PCP_ZOOM_TYPE;



typedef enum {
	PCP_DISABLED,
	PCP_ENABLED
} PCP_BMTYP;

/* Acqusition register defines: */
typedef enum {
	PCP_FREEZE = 0,
	PCP_SNAP   = 2,
	PCP_GRAB   = 3
} PCP_ACQTYP;


typedef enum {
	PCP_AMCC_REG_SPACE,
	PCP_ID_AND_FPGA_REG_SPACE,
	PCP_ACQ_MOD_AND_LUTS_REG_SPACE,
	PCP_FRAME_BUF_CNTRL_REG_SPACE,
	PCP_FRAME_BUF_SPACE,
		
	PCP_NUM_ADDR_SPACES
} PCP_ADRSPACE_TYPE;
           
typedef enum {
	PCP_PLL_MODE_STRIPPED_SYNC,
	PCP_PLL_MODE_SEPARATE_SYNC,
	PCP_XTAL_MODE = 4,
	PCP_VSCAN_MODE = 5
} PCP_TIMING_MODES;

typedef enum {
	PCP_HSYNC_OUT,
	PCP_COMPOSITE_OUT
} PCP_CSYNCSEL_TYPE;

// value of type PCP_PORTIO_CHANNELS is used as channelNum for functions such as OutportVal,InportVal
typedef enum {
	PCP_PARALLEL_IO_CHAN,
	PCP_MISC0_IO_CHAN,
	PCP_MISC1_IO_CHAN,
	PCP_MISC2_IO_CHAN,

} PCP_PORTIO_CHANNELS;


#define PCVPLUS_MAX_NUM_CAMERAS 2

#define PCP_RESET 1
#define PCP_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define PCP_BM_MUTEX_TIMEOUT 2000 // 2 seconds

#define PCP_PCI_DEVICE_ID       7

#define PCP_DEF_RS512x480P "RS170 512x480 PLL"
#define PCP_DEF_RS640x480P "RS170 640x480 PLL"
#define PCP_DEF_RS512x480X "RS170 512x480 Crystal"
#define PCP_DEF_RS640x480X "RS170 640x480 Crystal"

#define PCP_DEF_CC512x512P "CCIR 512x512 PLL"
#define PCP_DEF_CC768x574P "CCIR 768x574 PLL"
#define PCP_DEF_CC512x512X "CCIR 512x512 Crystal"
#define PCP_DEF_CC768x574X "CCIR 768x574 Crystal"

#define PCP_DEFAULT_CAMERA 	PCP_DEF_RS640x480X

#define PCP_MAX_NUM_OCT_ENTRIES 0x10000

#define PCP_INFINITE_SEQ_FRAMES 1

#define PCP_NUM_EDESC_SLOTS 0x400

#define PCP_NUM_PLL_REGS 7
#define PCP_NUM_DAC_REGS 4

#define PCP_XTAL_FREQ_MHZ 14.31818
#define PCP_XTAL_FREQ_KHZ 14318.18

#define MHZ_TO_KHZ 1000.0
#define KHZ_TO_MHZ 0.001
#define KHZ_TO_HZ  1000.0
#define HZ_TO_KHZ  0.001

#define PCP_NUM_SCHEMA_FRAME_IDS 4

#define PCP_OCT_CHECK_CACHED_ONLY 0

typedef enum {

	PCP_LUT1_HIGH_BYTE_OUT,
	PCP_STATIC_PAGE_ADDR

} PCP_LUT2_ADDR_TYPE;


#define PCP_DUMP_ZONE_BUF_SIZE 0x2000

#define PCP_MAX_NUM_AOI_GRAB_RECS 4


#include <ICapMod.h>
#include <PCPReg.h>
#include <IFCTyp.h>
#include <PCPFrame.h>
#include <ClrSpace.h>
#include <PCPCam.h>



#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCVisionPlus : public CICapMod
{
public:
	friend void  PCPwManBmReg(pCModule mod, WORD wReg, DWORD dwVal);
	friend DWORD PCPrManBmReg(pCModule mod, WORD wReg);

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
	void WriteCamera(PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual DWORD RegTableNumEntries(); //  returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); //  returns address of static reg table
	virtual void ModDataInit(); //  initializes module peculiar data
	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CPCVisionPlus();
	virtual ~CPCVisionPlus();
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
	virtual BOOL GetGrabStats(HIFCGRAB grabID, IFC_GRAB_STATS *stats);


	virtual BOOL SeqSnap(CICamera *camera, pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER);
	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);

	virtual HTRIGOP StartTrigOps(CICamera *camera);
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime);
	virtual BOOL TrigSnap(HTRIGOP trigOp, DWORD trigSource = PCP_EXT_TRIG0);
	virtual BOOL StopTrigOps(HTRIGOP trigOp);

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
	IFC_FIELD_STATUS GetFieldStatus(void);
	IFC_FIELD_STATUS GetFieldStatusLatchedAtEof(void);

	// Basic Read Area Functions
	virtual void ReadDestPitchArea (CPCPFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPCPFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPCPFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
			BOOL ReadAreaNoBm (CPCPFrame *frame, short x,short y,short dx,short dy,pDWORD dest,DWORD dest_dx=0,DWORD readOptions = 0);
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
	virtual pBYTE SeqSnapPhys(CICamera *camera, DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=IFC_WAIT_FOREVER,DWORD *acquiredDys=NULL);
	virtual int WaitPhysFrame(CICamera *camera,  BYTE **frameAddr=NULL, int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD dwMilliseconds=IFC_WAIT_FOREVER, DWORD *acquiredDy=NULL);
	virtual BOOL GetGrabPhysStats(IFC_GRABPHYS_STATS *stats);


	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);
	virtual BOOL IsActiveCamera(pSTRING camName);

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
	virtual void InportMode(BOOL strobed, IFC_EDGE_TYPE latchEdge, DWORD channelNum = 0);
	virtual WORD InportVal(DWORD channelNum = 0);
	virtual WORD InportInterruptPolarity( IFC_EDGE_TYPE intrEdge,DWORD channelNum=0);

	virtual BOOL FPGAByteWrite(BYTE val);
	virtual BOOL LoadFpga(char *szFpgaFileName);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual void ClearFrameBuffer(void);

	void SetPllBufferMode(BOOL b);
	BOOL IsPllBuffered();
	BOOL SetTimingSrc(DWORD dwTimingSrc, WORD wTimingChan);
	double CalcActualHorizFreq(double dHorizFreq);
	DWORD CalcRdiv(double dHorizFreq);
	DWORD CalcPixelsPerLine(double dHorizFreq, double dPixClkFreq);
	double CalcActualPixClkFreq(double dHorizFreq, double dPixClkFreq);
	BOOL ProgramPll(double dHorizFreq, double dPixClkFreq);
	void SetPllRdiv(double dHorizFreq);
	void SetHsyncWidth(double dHsyncWidth, double dHorizFreq, double dPixClkFreq);
	double GetHsyncWidth(double dHorizFreq, double dPixClkFreq);
	void SetVsyncFreq(double dVertFreq, double dHorizFreq);
	double GetVsyncFreq(double dHorizFreq);
	void SetVsyncWidth(double dVsyncLines);
	double GetVsyncWidth(double dHorizFreq);
	void SetVfrontPorch(int dwFpNumEqPulses);
	int GetVfrontPorch();
	void SetVbackPorch(int dwBpNumEqPulses);
	void SetFieldShiftMode(const DWORD dwEnable, double dVertFreq);
	DWORD GetFieldShiftMode(double dVertFreq);

	void SetDacBufferMode(BOOL b);
	BOOL IsDacBuffered();
	WORD DacRefVoltsToVal(double dVolts);
//	double DacRefValToVolts(WORD wVal);
	WORD DacClmpVoltsToVal(double dVolts);
//	double DacSyncClmpValToVolts(WORD wVal);
	WORD DacStripRateToVal(double dVolts);

	void SetDefaultLutOptions();
	void SelectLutOnFifo1(LUTID_TYPE lutID);
	void SelectLut2HighAddrByte(PCP_LUT2_ADDR_TYPE lut2AddrType);
	void SelectLut2Page(BYTE byPageNum);
	void ClearOctCache(void);
	DWORD GetOCTCacheEntry(CPCPFrame *frame,DWORD x, DWORD y, DWORD dx, DWORD dy, 
						   BOOL &AlreadyCached,DWORD numOCTEntries);
	void WriteOCT(CPCPFrame *frame, DWORD x, DWORD y, DWORD dx, DWORD dy);
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	short			m_fcount;		/* Acquisition frame count */
	short			m_stfield;		/* Starting field select */

	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/

	OS_sem_t		m_AcqMutex;


	CPCPFrame		*m_SchemaFrameids[PCP_NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();

	CPCPCam	*m_pCameras[PCVPLUS_MAX_NUM_CAMERAS];
	CPCPCam	*m_pActiveCamera;

	OS_sem_t	m_ActiveCameraMutex;

	OSHANDLE	m_GrabStartStopMutex;

	PCP_ZOOM_TYPE m_xZoom;
	PCP_ZOOM_TYPE m_yZoom;

	typedef struct {
		IFCLUTFUNC func;
		DWORD *constants;
		LUT_PORTION_TYPE lutPortion;
	} PCP_LUT_CACHE_REC;
	PCP_LUT_CACHE_REC m_LutCache[2];


//	void SetDiagPattern();

protected:
	IFC_DECLARE_DYNCREATE(CPCVisionPlus)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);

	void InitPll();
	void WritePllBuffer();
	void WritePllReg(const WORD wReg, const WORD wVal);
	WORD ReadPllReg(const WORD wReg);
	DWORD* GetDMAScatterListBaseAddr();
	DWORD* GetOctBaseAddr();
	DWORD* GetFrameBufBaseAddr();
	void  WriteManBmReg(const DWORD dwRegI, const DWORD dwVal);
	DWORD ReadManBmReg(const DWORD dwRegI);

	BOOL m_bPllBuffered;
	WORD m_PllBuffer[PCP_NUM_PLL_REGS];	// Buffer for PLL writes.
	WORD m_PllShadow[PCP_NUM_PLL_REGS];	// Current values of the PLL registers.

	void InitDac();
	void WriteDacBuffer();
	void WriteDacReg(const WORD wReg, const WORD wVal);
	void WriteDacNoOp();
	void WriteDacAddr(const WORD wAddr);
	void WriteDacData(const WORD wData);
	WORD ReadDacReg(const WORD wReg);

	BOOL m_bDacBuffered;
	WORD m_DacBuffer[PCP_NUM_DAC_REGS];	// Buffer for DAC writes.
	WORD m_DacShadow[PCP_NUM_DAC_REGS];	// Current values of the DAC registers.


private:

	ConfigSymbol *m_SymbolTable;
	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);

	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CPCPFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	static REGID ManBmWregs[4];
	static REGID ManBmRregs[4];
	BOOL ReadAreaLocked ( CPCPFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	PCP_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	void MakePCVPlusCamList();
	void WriteBMDestptrs(DWORD *pd,DWORD numPointers);
	void WriteRawOCT( DWORD destIndex,DWORD numEntries);
	char *PcpGeo2FPGAFiles();
	BOOL ProcessGrabCommand(HANDLE hSpawner);

	void DelSharedScatterList(DWORD &listHandle);

	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CPCPCam *m_trigOpCamera;

	DWORD OCTTable[PCP_MAX_NUM_OCT_ENTRIES];


	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EOFIntr;



	HANDLE m_grabFMO;
	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[PCP_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} PCP_UNIQUE_GRAB_REC;
	PCP_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;
	CIMemory *m_ScatListMem;
	void *m_VixnSeqSnap;
	int m_lastPhysDelivered;
	DWORD m_ringPhysNumFrames;
	DWORD m_dwPhysFrameSize;
	DWORD m_dwPhysDstOffset;


    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[PCP_DUMP_ZONE_BUF_SIZE];

	BOOL m_grabThreadIsRemote;

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);
	BOOL WaitStartVB(CIFrame *frame);
	BOOL WaitNotVB(CIFrame *frame, BOOL vbsync);
};
#endif
// BOOL IFCAPI PCVPlusCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#endif // !defined(AFX_PCVPLUS_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
