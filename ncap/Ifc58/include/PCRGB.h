/******************************************************************************
 *
 * MODULE   
 *		PcRgb.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCRGB.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:40a $
 *
 * ABSTRACT  
 *		IFC interface of the CPcRgb class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999 (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCRGB_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCRGB_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define PCRGB_MODNAME "PCRgb"

/*
** PcRgb Interrupt events 
*/
typedef enum {

	PCR_INTR_SOT,
	PCR_INTR_EOT,
	PCR_INTR_INPORT,
	PCR_INTR_SW_TIMER,

	PCR_INTR_ACQ_ADRS,
	PCR_INTR_BMDONE,
	PCR_INTR_AM_CASCADE,
	PCR_INTR_EOFRM,

	PCR_INTR_VB, 	  
	PCR_INTR_EVEN_VB,
	PCR_INTR_ODD_VB,

	PCRGB_INTR_MAX_EVENT  /* MUST be last !!! */
} PCRGB_INTR_EVENT;


/* Zoom constants  used for subsampling on PcRgb */
typedef enum {
	PCR_ZOOM_INQUIRE = -1,
	PCR_ZOOM_OUT_NO = 0,
	PCR_ZOOM_OUT_X2,
	PCR_ZOOM_OUT_X4,
	PCR_ZOOM_OUT_X8
} PCR_ZOOM_TYPE;

// value of type PCR_PORTIO_CHANNELS is used as channelNum for functions such as OutportVal,InportVal
typedef enum {
	PCR_PARALLEL_IO_CHAN,
	PCR_MISC_IO_CHAN

} PCR_PORTIO_CHANNELS;

typedef enum {
	PCR_DISABLED,
	PCR_ENABLED
} PCR_BMTYP;

/* Acqusition register defines: */
typedef enum {
	PCR_FREEZE = 0,
	PCR_SNAP   = 2,
	PCR_GRAB   = 3
} PCR_ACQTYP;


typedef enum {
	PCR_AMCC_REG_SPACE,
	PCR_ID_AND_FPGA_REG_SPACE,
	PCR_ACQ_MOD_AND_LUTS_REG_SPACE,
	PCR_FRAME_BUF_CNTRL_REG_SPACE,
	PCR_FRAME_BUF_SPACE,
		
	PCR_NUM_ADDR_SPACES
} PCR_ADRSPACE_TYPE;
           
typedef enum {
	PCR_PLL_MODE_STRIPPED_SYNC,
	PCR_PLL_MODE_SEPARATE_SYNC,
	PCR_XTAL_MODE = 4,
	PCR_VSCAN_MODE = 5
} PCR_TIMING_MODES;


#define PCRGB_MAX_NUM_CAMERAS 2

typedef enum {
	PCR_8_BIT_RED_CHANNEL,
	PCR_8_BIT_GREEN_CHANNEL,
	PCR_8_BIT_BLUE_CHANNEL,
	PCR_8_BIT_ALPHA_CHANNEL,
	PCR_32_BIT_ALPHA_RGB,
	PCR_IN_MODE_RESERVED1,
	PCR_16_BIT_YCBCR_4_2_2,
	PCR_16_BIT_YCRCB_4_2_2,
	PCR_24_BIT_PACKED,
	PCR_32_BIT_PLANAR = 0xC,
} PCR_IN_MODE_TYPE;

#define PCR_RESET 1
#define ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define BM_MUTEX_TIMEOUT 2000 // 2 seconds

#define PCR_PCI_DEVICE_ID       5

#define PCR_DEF_RS512x480P "PCR_DEF_RS512x480P"
#define PCR_DEF_RS640x480P "PCR_DEF_RS640x480P"
#define PCR_DEF_RS720x480P "PCR_DEF_RS720x480P"
#define PCR_DEF_RS752x480P "PCR_DEF_RS752x480P"
#define PCR_DEF_RS512x480X "PCR_DEF_RS512x480X"
#define PCR_DEF_RS640x480X "PCR_DEF_RS640x480X"
#define PCR_DEF_RS720x480X "PCR_DEF_RS720x480X"
#define PCR_DEF_RS752x480X "PCR_DEF_RS752x480X"

#define PCR_DEF_CC512x512P "PCR_DEF_CC512x512P"
#define PCR_DEF_CC720x574P "PCR_DEF_CC720x574P"
#define PCR_DEF_CC768x574P "PCR_DEF_CC768x574P"
#define PCR_DEF_CC920x574P "PCR_DEF_CC920x574P"
#define PCR_DEF_CC512x512X "PCR_DEF_CC512x512X"
#define PCR_DEF_CC720x574X "PCR_DEF_CC720x574X"
#define PCR_DEF_CC768x574X "PCR_DEF_CC768x574X"
#define PCR_DEF_CC920x574X "PCR_DEF_CC920x574X"

#define PCR_DEFAULT_CAMERA 	PCR_DEF_RS512x480X

#define MAX_NUM_OCT_ENTRIES 0x10000

#define PCR_INFINITE_SEQ_FRAMES 1

#define PCR_NUM_EDESC_SLOTS 0x400

#define NUM_PLL_REGS 7
#define NUM_DAC_REGS 8

#define PCR_XTAL_FREQ_MHZ 14.31818
#define PCR_XTAL_FREQ_KHZ 14318.18

#define MHZ_TO_KHZ 1000.0
#define KHZ_TO_MHZ 0.001
#define KHZ_TO_HZ  1000.0
#define HZ_TO_KHZ  0.001

typedef double CSC_MATRIX[9];

#define NUM_SCHEMA_FRAME_IDS 4

#define PCR_OCT_CHECK_CACHED_ONLY 0

typedef enum {

	PCR_LUT1_HIGH_BYTE_OUT,
	PCR_STATIC_PAGE_ADDR

} PCR_LUT2_ADDR_TYPE;


#define PCR_DUMP_ZONE_BUF_SIZE 0x2000

#define PCR_MAX_NUM_AOI_GRAB_RECS 4


#include <ICapMod.h>
#include <PCRReg.h>
#include <IFCTyp.h>
#include <PCRFrame.h>
#include <ClrSpace.h>
#include <PCRCam.h>



#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPcRgb : public CICapMod
{
public:
	friend void  wManBmReg(pCModule mod, WORD wReg, DWORD dwVal);
	friend DWORD rManBmReg(pCModule mod, WORD wReg);

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
	CPcRgb();
	virtual ~CPcRgb();
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
	virtual BOOL TrigSnap(HTRIGOP trigOp, DWORD trigSource = PCR_EXT_TRIG0);
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
	virtual void ReadDestPitchArea (CPCRFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPCRFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPCRFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
			BOOL ReadAreaNoBm (CPCRFrame *frame, short x,short y,short dx,short dy,pDWORD dest,DWORD dest_dx=0,DWORD readOptions = 0);
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
	void SetVfrontPorch(DWORD dwFpNumEqPulses);
	DWORD GetVfrontPorch();
	void SetVbackPorch(DWORD dwBpNumEqPulses);
	void SetFieldShiftMode(const DWORD dwEnable, double dVertFreq);
	DWORD GetFieldShiftMode(double dVertFreq);
	BOOL SetCscMethod(WORD wCscMethod);
	double GetCscMethod();
	BOOL SetCscCoeff(double dCoeff, DWORD dwIndex, BOOL eWriteThru=TRUE);
	double GetCscCoeff(DWORD dwIndex);
	DWORD CscCoeffToRegVal(double dCoeff);
	double CscRegValToCoeff(const short nVal);

	void SetDacBufferMode(BOOL b);
	BOOL IsDacBuffered();
	WORD DacVoltsToVal(double dVolts);
	double DacValToVolts(WORD wVal);

	BOOL BoardHasCscAndLuts();
	void SetDefaultLutOptions();
	void SelectLutOnFifo1(LUTID_TYPE lutID);
	void SelectLut2HighAddrByte(PCR_LUT2_ADDR_TYPE lut2AddrType);
	void SelectLut2Page(BYTE byPageNum);
	void LoadCscMatrix(const CSC_MATRIX cscMatrix);
	DWORD GetOCTCacheEntry(CPCRFrame *frame,DWORD x, DWORD y, DWORD dx, DWORD dy, 
						   BOOL &AlreadyCached,DWORD numOCTEntries);
	void WriteOCT(CPCRFrame *frame, DWORD x, DWORD y, DWORD dx, DWORD dy,DWORD options=0);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	short			m_fcount;		/* Acquisition frame count */
	short			m_stfield;		/* Starting field select */
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);

	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/

	OS_sem_t		m_AcqMutex;


	CPCRFrame		*m_SchemaFrameids[NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();

	CPCRCam	*m_pCameras[PCRGB_MAX_NUM_CAMERAS];
	CPCRCam	*m_pActiveCamera;

	OS_sem_t	m_ActiveCameraMutex;

	OSHANDLE	m_GrabStartStopMutex;

	typedef struct {
		IFCLUTFUNC func;
		DWORD *constants;
		LUT_PORTION_TYPE lutPortion;
	} PCR_LUT_CACHE_REC;
	PCR_LUT_CACHE_REC m_LutCache[2];

//	WORD m_wStartPort;
	static const CSC_MATRIX m_matrixRgbToRgb;
	static const CSC_MATRIX m_matrixRgbToYuv;
	static const CSC_MATRIX m_matrixRgbToYiq;
	static const CSC_MATRIX m_matrixRgbToYcrcb;

	void SetDiagPattern();

protected:
	IFC_DECLARE_DYNCREATE(CPcRgb)

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
	WORD m_PllBuffer[NUM_PLL_REGS];	// Buffer for PLL writes.
	WORD m_PllShadow[NUM_PLL_REGS];	// Current values of the PLL registers.

	void InitDac();
	void WriteDacBuffer();
	void WriteDacReg(const WORD wReg, const WORD wVal);
	void WriteDacNoOp();
	void WriteDacAddr(const WORD wAddr);
	void WriteDacData(const WORD wData);
	WORD ReadDacReg(const WORD wReg);

	BOOL m_bDacBuffered;
	WORD m_DacBuffer[NUM_DAC_REGS];	// Buffer for DAC writes.
	WORD m_DacShadow[NUM_DAC_REGS];	// Current values of the DAC registers.

	DWORD m_cscCoeffRegs[3];

private:

	ConfigSymbol *m_SymbolTable;
	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);

	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CPCRFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	static REGID ManBmWregs[4];
	static REGID ManBmRregs[4];
	BOOL ReadAreaLocked ( CPCRFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	PCR_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	void MakePcRgbCamList();
	void WriteBMDestptrs(DWORD *pd,DWORD numPointers);
	void WriteRawOCT( DWORD destIndex,DWORD numEntries);
	char *PcrgbGeo2FPGAFiles();
	BOOL ProcessGrabCommand(HANDLE hSpawner);

	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CPCRCam *m_trigOpCamera;

	DWORD OCTTable[MAX_NUM_OCT_ENTRIES];


	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EofIntr;


	HANDLE m_grabFMO;
	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[PCR_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} PCR_UNIQUE_GRAB_REC;
	PCR_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;


    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[PCR_DUMP_ZONE_BUF_SIZE];

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);
	BOOL WaitStartVB(CIFrame *frame);
	BOOL WaitNotVB(CIFrame *frame, BOOL vbsync);
};
#endif
// BOOL IFCAPI PcRgbCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#endif // !defined(AFX_PCRGB_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
