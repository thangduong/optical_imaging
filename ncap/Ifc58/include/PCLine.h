/******************************************************************************
 *
 * MODULE   
 *		PCLine.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCLine.h $
 *		$Revision: 1.1 $
 *		$Modtime: 7/01/02 11:20a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCLine class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_PCLine_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_PCLine_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define PCLINESCAN_MODNAME "PCLineScan"

/*
** PCLine Interrupt events 
*/
typedef enum {

	PCL_INTR_VB, 	  /* vertical blank */
	PCL_INTR_HB,
	PCL_INTR_TRIG0,
	PCL_INTR_TRIG1,
	PCL_INTR_SOACQ,
	PCL_INTR_EOACQ,
	PCL_INTR_INPORT,
	PCL_INTR_ACQ_ADRS,
	PCL_INTR_BMDONE,
	PCL_INTR_SW_TIMER,
	PCL_INTR_RLE_RESULT,



	PCL_INTR_MAX_EVENT  /* MUST be last !!! */
} PCL_INTR_EVENT;


/* Zoom constants  used for subsampling on PCLine */
typedef enum {
	PCL_ZOOM_INQUIRE=-1,
	PCL_ZOOM_NO=0,
	PCL_ZOOM_X2,
	PCL_ZOOM_X4,
	PCL_ZOOM_X8
} PCL_ZOOM_TYPE;



typedef enum {
	PCL_DISABLED,
	PCL_ENABLED
} PCL_BMTYP;

/* Acqusition register defines: */
typedef enum {
	PCL_FREEZE = 0,
	PCL_SNAP   = 2,
	PCL_GRAB   = 3
} PCL_ACQTYP;


typedef enum {
	PCL_AMCC_REG_SPACE,
	PCL_CONTROL_REG_SPACE,
	PCL_FRAME_BUF_SPACE,
	PCL_RLE_RESULTS_SRAM,

		
	PCL_NUM_ADDR_SPACES
} PCL_ADRSPACE_TYPE;
           

typedef enum {
	PCL_8BIT_1TAP,
	PCL_16BIT_1TAP,
	PCL_24BIT_1TAP,
	PCL_32BIT_1TAP,
	PCL_8BIT_2TAP,
	PCL_8BIT_4TAP,
	PCL_16BIT_2TAP,

	PCL_NUM_SFORMS,
	PCL_NO_SFORM=0xffff
} PCL_SFORM_TYPE;

typedef enum {
	PCL_FFC_8BIT_MODE,
	PCL_FFC_10BIT_MODE

} PCL_FFC_MODE_TYPE;


#define PCL_PIX8 8
#define PCL_PIX32 32
#define PCL_PIX24 24

#define PCL_RESET 1
#define ACQ_MUTEX_TIMEOUT 2000 // 2 seconds

#define PCL_PCI_DEVICE_ID       0x6


#define PCL_MAX_NUM_OCT_ENTRIES 0x40000

#define PCL_DEF_LINE_SCAN_1K "PCLineScan Standard LineScan 1K"
#define PCL_DEF_AREA_SCAN_1Kx1K "PCLineScan Standard AreaScan 1Kx1K"
#define PCL_DEFAULT_CAMERA 	PCL_DEF_LINE_SCAN_1K


#define PCL_INFINITE_SEQ_FRAMES 15

#define PCL_NUM_EDESC_SLOTS 0x2002


#define PCL_OCT_CHECK_CACHED_ONLY 0

#define PCL_DUMP_ZONE_BUF_SIZE 0x2000

#define PCL_MAX_NUM_AOI_GRAB_RECS 4

#define PCL_NUM_FRABUF_POOL_PAGES 0x2000

#define PCL_RLE_ENTRY_SIZE 8

// PCLine Grab options
#define PCL_GOPT_RLE_ENCODE IFC_GOPT_MOD_PECULIAR1
#define PCL_GOPT_RLE_DEST_FBUF IFC_GOPT_MOD_PECULIAR2
#define PCL_GOPT_RLE2FBUF_ENCODE (PCL_GOPT_RLE_ENCODE|PCL_GOPT_RLE_DEST_FBUF)

#define PCL_RLE_SRAM_SIZE 0x80000
#define PCL_RLE_SRAM_NUM_ENTRIES (PCL_RLE_SRAM_SIZE/PCL_RLE_ENTRY_SIZE)


#define PCL_FFC_12BIT_MAX_OFFSET 0x000003ff
#define PCL_FFC_8BIT_MAX_OFFSET  0x0000003f
#define PCL_FFC_MAX_GAIN	4.0f

class IFC_EXT_API CPCLine;

#include <ICapMod.h>
#include <PclReg.h>
#include <IFCTyp.h>
#include <PCLFrame.h>
#include <ClrSpace.h>
#include <PCLCam.h>


typedef struct {
	PCL_SFORM_TYPE sForm;
	DWORD numHorzTaps;
	DWORD BMStepSize;
	DWORD numVertTaps;	
} PCL_USER_GEO_PROP, *LPPCL_USER_GEO_PROP;


typedef struct {
	WORD x;
	WORD y;
	WORD len;
	BYTE tag;
	BYTE chan;
} PCL_RLE_FEATURE_DESC,*LPPCL_RLE_FEATURE_DESC;


typedef struct {
      DWORD x0,y0,x1,y1;
      DWORD x_cent;
      DWORD y_cent;
      DWORD area;
      DWORD xsum,ysum;
      DWORD perim;
      DWORD fIgnore;
      DWORD tag;
} PCL_BLOB_DESC;



#define PCL_USER_GEO_LOAD_FNAME "UserGeometryLoad"
#define PCL_USER_GEO_PROP_FNAME "UserGeometryProperties"


typedef DWORD (IFCAPI *pfPCL_USER_GEO_LOAD)(CPCLine *pcl,DWORD *oct,DWORD srcOffset,DWORD dx,DWORD dy,DWORD bytesPerPixel); 
typedef BOOL (IFCAPI *pfPCL_USER_GEO_PROP)(CPCLine *pcl,LPPCL_USER_GEO_PROP lpProps); 


#ifdef __cplusplus
class IFC_EXT_API CPCLine : public CICapMod
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
	CPCLine();
	virtual ~CPCLine();

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

	virtual BOOL Snap(CICamera *camera, pBYTE dest,short x=0, short y=0, short dx=0, short dy=0);

	virtual HTRIGOP StartTrigOps(CICamera *camera);
	virtual BOOL TrigRead(HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
	virtual BOOL WaitTrig(HTRIGOP trigOp,long waitTime);
	virtual BOOL TrigSnap(HTRIGOP trigOp,DWORD trigSource=PCL_TMODE_HWTRIG0_ASSERT);
	virtual BOOL StopTrigOps(HTRIGOP trigOp);
	BOOL SetAcqTriggerEvents(PCL_TRIG_MODE_TYPE startEvent , PCL_TRIG_MODE_TYPE stopEvent,DWORD numFramesPerTrig=1);

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
	virtual void ReadDestPitchArea (CPCLFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CPCLFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CPCLFrame *frame, int x, int y, int dx, int dy, pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
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
	PCL_IMAGE_GEOMETRY_TYPE GetBaseGeometry(PCL_IMAGE_GEOMETRY_TYPE eRequestedGeometry,IFC_DEPTH eBitsPerPixel,DWORD numCameras);
	PCL_SFORM_TYPE PclineGeo2Sform(DWORD geometry,DWORD bitsPerPixel);
	DWORD GetActiveChannels(BOOL forRlePurposes=TRUE);
	void WriteOCT(CPCLFrame *frame,DWORD srcOffset,DWORD dy);
	virtual IFC_FIELD_STATUS GetInterlaceFirstFieldStatus(void);
	virtual BOOL GetImageCaptureCaps(IFC_IMAGECAP_CAPS *caps);
	virtual void ClearFrameBuffer(void);

	int GrabWaitRle(HIFCGRAB grabID, BYTE *frameAddr, DWORD bytesAvailable,int FrameSeqNum=IFC_WAIT_NEWER_FRAME, DWORD milliseconds=IFC_WAIT_FOREVER, BOOL lock=TRUE,DWORD *acquiredDy = NULL, BOOL *VirtualFrameEnd=NULL, GRAB_EXT_ATTR *ExtendedAttr=NULL);

	void SetRLEState(BOOL eEnabled, BOOL eGotoFrameBuf=FALSE);
	BOOL GetRLEState(void);
	void SetFlatFieldCorrState(BOOL eEnabled);
	BOOL GetFlatFieldCorrState(void);

	BOOL WriteFFCOffset16(DWORD channels,DWORD index,DWORD offset);
	DWORD ReadFFCOffset16(DWORD channel,DWORD index);
	BOOL WriteFFCOffset8(DWORD channels,DWORD index,DWORD offset);
	DWORD ReadFFCOffset8(DWORD channel,DWORD index);
	BOOL WriteFFCGain16(DWORD channels,DWORD index,float gain);
	float ReadFFCGain16(DWORD channel,DWORD index);
	BOOL WriteFFCGain8(DWORD channels,DWORD index,float gain);
	float ReadFFCGain8(DWORD channel,DWORD index);
	DWORD RlePostProcess ( LPPCL_RLE_FEATURE_DESC src, DWORD numRleEntries,DWORD numBytesAvailable,LPPCL_RLE_FEATURE_DESC dest);
	void ClearOctCache(void);
	DWORD DecodeRle ( LPPCL_RLE_FEATURE_DESC rleSrc, DWORD numRleEntries, DWORD imageWidth, DWORD numBytesAvailable, BYTE *dest,BOOL normalize8Bit=TRUE);
	DWORD ReadRle ( DWORD startRleIndex, DWORD numRleEntries,DWORD numBytesAvailable, BYTE *dest, DWORD readOptions=0);
	BOOL SetRleFrameBufSform(BOOL enable);
	static BOOL BuildBlobs(int PixelsPerLine, int linesPerFrame, int featureCount,LPPCL_RLE_FEATURE_DESC rleSrc, int &numBlobs, PCL_BLOB_DESC* dst, int maxBlobYsize, BOOL tagBlobs=TRUE);
	BOOL ReadAreaSmart ( CPCLFrame *frame,short x,short y,DWORD srcDx, DWORD dy, DWORD lockRegion, 
							DWORD regionOffset, DWORD destDx, DWORD readOptions, BYTE *dest);



	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/
	OSHANDLE		m_AcqMutex;

	CPCLFrame		*m_SchemaFrameids[2];
	DWORD			m_framesInSchema;

	OSHANDLE		m_GrabStartStopMutex;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */
	CPCLCam	*m_pCamera;

protected:
	IFC_DECLARE_DYNCREATE(CPCLine)


private:
	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CPCLFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	DWORD BmLockDescSize ( DWORD region);
	BOOL ReadAreaLocked ( CPCLFrame *frame,int x,int y,DWORD src_dx,int dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	BOOL ReadRleLocked ( DWORD startRleIndex, DWORD numRleEntries,DWORD numBytesAvailable,DWORD lock_region, DWORD region_offset, DWORD readOptions=0);

	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	PCL_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame *frame,short acqcmd,short frcnt);
	void MakePCLineCamList();
	void WriteBMDestptrs(DWORD *pd,DWORD numPointers);
	void WriteRawOCT( DWORD destIndex,DWORD numEntries);
	char *PclineGeo2FPGAFiles(char *exoFileStr,DWORD geometry,DWORD bitsPerPixel);

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
	DWORD GetOCTCacheEntry(CPCLFrame *frame,DWORD dx, DWORD dy, DWORD srcOffset, BOOL &newEntry,DWORD numOCTEntries, DWORD &BmStepVal );


	BOOL ProcessGrabCommand(HANDLE hSpawner);

	// The following functions operate on the currently active camera

	CClrSpace *m_clrSpace;
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CPCLCam *m_trigOpCamera;

	DWORD m_OCTTable[PCL_MAX_NUM_OCT_ENTRIES];

	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_VBIntr;
	HANDLE m_grabFMO;
	void *m_grabArea;

    IFC_EDDS            m_dumpzone;		/* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[PCL_DUMP_ZONE_BUF_SIZE];
	BYTE			m_RleStagingArea[PCL_RLE_SRAM_SIZE+0x1000];

	ConfigSymbol *m_SymbolTable;	// Initialized if needed during config file operations.
	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	void *m_VixnSeqSnap;


	// Process peculiar grab components
	typedef struct {
		BYTE *dest;
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[PCL_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} PCL_UNIQUE_GRAB_REC;
	PCL_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;
	BOOL m_RleFrameBufEnabled;


	HINSTANCE m_UserGeoLib;
	BOOL m_grabThreadIsRemote;

	DWORD m_numFramesPerTrig;

	friend BOOL IFCAPI PCLineUserGeoSet(CICamera *cam, int parmIndex, DWORD index, double data);
public:
	pfPCL_USER_GEO_LOAD m_UserGeoLoad;
	pfPCL_USER_GEO_PROP m_UserGeoProp;

};
#endif

BOOL IFCAPI PCLineCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#ifdef __cplusplus
extern "C" DWORD IFCCALL PCLineMakeForwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
extern "C" DWORD IFCCALL PCLineMakeBackwardOCTEntry(DWORD srcOffset,DWORD numBytes,DWORD *thisCount,DWORD BMStepSize);
#endif

#endif // !defined(AFX_PCLine_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
