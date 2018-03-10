/******************************************************************************
 *
 * MODULE   
 *		BanditII.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Bandit2.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/13/03 2:15p $
 *
 * ABSTRACT  
 *		IFC interface of the CBanditII class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_Bandit_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_Bandit_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>


#define BANDIT2_MODNAME "BanditII"

#define BDT_MAX_VID_BUFFERS 3

#define BANDITII_NUM_COMPOSITE_PORTS 6

#define BANDITII_NUM_YC_PORTS 2
#define BANDITII_COMP_TOTAL_PORTS (BANDITII_NUM_COMPOSITE_PORTS+BANDITII_NUM_YC_PORTS)


#define BANDITII_NUM_RGB_PORTS 3

#define BANDIT_MAX_NUM_CAMERAS (BANDITII_NUM_COMPOSITE_PORTS+BANDITII_NUM_YC_PORTS+BANDITII_NUM_RGB_PORTS)

typedef enum {
	BDT_CAM_PORT_RGB,
	BDT_CAM_PORT_COMPOSITE,
	BDT_CAM_PORT_YC,
} BDT_CAM_PORT_TYPE;

#define BDT_CAM_PORT_NONE -1


/*
** BanditII Interrupt events 
*/
typedef enum {

	BDT_INTR_VB, 	  
	BDT_INTR_EOFRM,

	BDT_INTR_SOT,

	BDT_INTR_BMDONE,

	BDT_INTR_MAX_EVENT  /* MUST be last !!! */
} BANDITII_INTR_EVENT;


/* Zoom constants  used for subsampling on BanditII */
typedef enum {
	BDT_ZOOM_INQUIRE = -1,
	BDT_ZOOM_OUT_NO = 0,
	BDT_ZOOM_OUT_X2,
	BDT_ZOOM_OUT_X4,
	BDT_ZOOM_OUT_X8
} BDT_ZOOM_TYPE;


typedef enum {
	BDT_BOARD_MODEL_ALL= 0x0000,   // Wild Card, can be any of the models listed below
	BDT_BOARD_MODEL_CV = 0x0001,   // Saa7114 Only
	BDT_BOARD_MODEL_RGB= 0x0002,   // Saa7114 + Ths8083 
	BDT_BOARD_MODEL_MV = 0x0004   // Ths8083 Only

} BDT_MODEL_TYPE;


typedef enum {
	BDT_DISABLED,
	BDT_ENABLED
} BDT_BMTYP;

/* Acqusition register defines: */
typedef enum {
	BDT_FREEZE = 0,
	BDT_SNAP   = 2,
	BDT_GRAB   = 3
} BDT_ACQTYP;


typedef enum {
//	BDT_FRAME_BUF_SPACE,
		
	BDT_NUM_ADDR_SPACES
} BDT_ADRSPACE_TYPE;
           




#define BDT_RESET 1
#define BDT_ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define BDT_BM_MUTEX_TIMEOUT 2000 // 2 seconds
#define BDT_FRAME_MUTEX_TIMEOUT 2000 // 2 seconds

#define BDT_PCI_DEVICE_ID       0x8c12
#define BDT_VENDOR_ID 0x5333

#define BDT_DEF_RS512x480P "BDT_DEF_RS512x480P"
#define BDT_DEF_RS640x480P "BDT_DEF_RS640x480P"
#define BDT_DEF_CC512x512P "BDT_DEF_CC512x512P"
#define BDT_DEF_CC768x574P "BDT_DEF_CC768x574P"

#define BDR_DEF_RS512x480P "BDR_DEF_RS512x480P"
#define BDR_DEF_RS640x480P "BDR_DEF_RS640x480P"

#define BDR_DEF_CC512x512P "BDR_DEF_CC512x512P"
#define BDR_DEF_CC768x574P "BDR_DEF_CC768x574P"

#define BDT_DEFAULT_CAMERA 	BDT_DEF_RS640x480P
#define BDR_DEFAULT_CAMERA 	BDR_DEF_RS640x480P


#define BDT_INFINITE_SEQ_FRAMES 1

#define BDT_NUM_EDESC_SLOTS 0x400


#define BDT_XTAL_FREQ_MHZ 14.31818
#define BDT_XTAL_FREQ_KHZ 14318.18

#define BDT_MHZ_TO_KHZ 1000.0
#define BDT_KHZ_TO_MHZ 0.001
#define BDT_KHZ_TO_HZ  1000.0
#define BDT_HZ_TO_KHZ  0.001


#define NUM_SCHEMA_FRAME_IDS 4


typedef enum {

	BDT_LUT1_HIGH_BYTE_OUT,
	BDT_STATIC_PAGE_ADDR

} BDT_LUT2_ADDR_TYPE;


#define BDT_DUMP_ZONE_BUF_SIZE 0x2000

#define BDT_MAX_NUM_AOI_GRAB_RECS 4

typedef void *HBDTAUTOREAD;



#define BDT_TRI_STATE_OUTPUT_VAL 2


class IFC_EXT_API CBanditII;

#include <ICapMod.h>
#include <BDTReg.h>
#include <IFCTyp.h>
#include <BDTFrame.h>
#include <ClrSpace.h>
#include <BDTCam.h>
#include <BDTCmRgb.h>

#include <BDII.h>




#ifdef __cplusplus
class IFC_EXT_API CBanditII : public CICapMod
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
	virtual BOOL BaseAddrInit();

	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	virtual pSTRING GetCamPortName(DWORD camPortNum, pSTRING camPortName);

	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CBanditII();
	virtual ~CBanditII();
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
	IFC_FIELD_STATUS GetFieldStatus(void);
	IFC_FIELD_STATUS GetFieldStatusLatchedAtEof(void);

	// Basic Read Area Functions
	virtual void ReadDestPitchArea (CBDTFrame *frame, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual void ReadDestPitchArea (CICamera *camera, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CBDTFrame *frame, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL LineReverseRead (CICamera *camera, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions = 0);
	virtual BOOL ReadArea (CBDTFrame *frame, short x,short y,short dx,short dy,pDWORD darray,DWORD dest_dx=0,DWORD readOptions = 0);
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


	BOOL RgbSupported(void);
	BOOL CompSupported(void);

	int GetFirstCamPort(BDT_CAM_PORT_TYPE camPortType);

	double CalcActualHorizFreq(double dHorizFreq);
	DWORD CalcPixelsPerLine(double dHorizFreq, double dPixClkFreq);
	double CalcActualPixClkFreq(double dHorizFreq, double dPixClkFreq);


	void FramesToVidBufList(DWORD frameCnt,CBDTFrame **frames,int x=0,int y=0,int dx=0,int dy=0,PBDII_VIDEO_BUFFER_LIST pVideoBufferList=NULL);
	PBDII_HOST_BUFFER_LIST CreateHostBufList(CBDTFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, DWORD *scatList,DWORD numScatEntries);
	PBDII_HOST_BUFFER_LIST CreateLockHostBufList(CBDTFrame *frame,int x,int y, int dx, int dy, DWORD numFrames, UINT32 event, UINT32 memoryType, pIFC_EDDS scatLists[],DWORD numScatLists);
	HBDTAUTOREAD StartAutoRead ( CBDTFrame *frame,short x,short y,DWORD src_dx,short dy, DWORD numFrames, pIFC_EDDS *lockRegions, DWORD numLockedRegions,DWORD dest_dx, DWORD readOptions);
	BOOL StopAutoRead ( HBDTAUTOREAD autoTrans);

	void DeleteHostBufList(PBDII_HOST_BUFFER_LIST hBufList);

	DWORD BanditPixelFormat( IFC_COLOR color,	DWORD dwBitsPerPixel);
	BOOL ProgramSaa7114(void);
	BOOL ProgramThs8083(void);
	BOOL ProgramS3FE(void);
	BOOL Is7114Port();
	BOOL ActiveIsRgbPort(void);
	BOOL UpdateAcquireHw(void);
	BOOL BdtSAA7114_SetWindow(void);
	BOOL BdtThs8083_SetWindow(void);
	BOOL BdtThs8083_SetStrobe(void);
	BOOL UpdateTriggerParams();

	DWORD GetBanditFieldOrder(void);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	short			m_fcount;		/* Acquisition frame count */
	short			m_stfield;		/* Starting field select */
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);


	OS_sem_t		m_AcqMutex;


	CBDTFrame		*m_SchemaFrameids[NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	pIFC_EDDS       m_edesc;          /* DMA block descriptor */


	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();

	CICamera	*m_pCameras[BANDIT_MAX_NUM_CAMERAS];
	CICamera	*m_pActiveCamera;

	CBDTCam *m_firstCompCam;
	CBDTRgbCam *m_firstRgbCam;

	OS_sem_t	m_ActiveCameraMutex;

	OSHANDLE	m_GrabStartStopMutex;
	OSHANDLE	m_framesMutex;
	BOOL m_insideUpdateParam;

	DWORD m_numRgbPorts;
	DWORD m_numCompPorts;
	DWORD m_firstRgbPort;
	DWORD m_firstCompPort;

	BOOL m_convertTo422On;

	BYTE *m_defaultRingBuf;
	DWORD m_defaultRingNumFrames;
	DWORD m_defaultRingBufSize;

	HIFCGRAB m_defGrabId;

	typedef struct {
		IFCLUTFUNC func;
		DWORD *constants;
		LUT_PORTION_TYPE lutPortion;
	} BDT_LUT_CACHE_REC;
	BDT_LUT_CACHE_REC m_LutCache[2];

//	WORD m_wStartPort;


protected:
	IFC_DECLARE_DYNCREATE(CBanditII)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);


	BDII_SAA7114_MODULE m_saa7114Reg;
	BDII_THS8083_MODULE m_ths8083Reg;

	BOOL m_FramesCreateSurfaces;
	DWORD m_maxSchemaFrames;
	BOOL m_SAA7114Selected;
	BOOL m_THS8083Selected;
	BDT_MODEL_TYPE m_boardModel;

private:


	void LoadBMSrc(DWORD ilaced,DWORD offadr, DWORD adr2,short Byteppix, DWORD aoidx, DWORD FrameXSize, DWORD FrameYSize);
	BOOL WaitBmDone (void);
	CBDTFrame *HostSchemaFrame(LPCAM_ATTR lpAttr);
	BOOL ReadAreaLocked ( CBDTFrame *frame,short x,short y,DWORD src_dx,short dy,DWORD lock_region, DWORD region_offset,DWORD dest_dx=0, DWORD readOptions=0);
	static DWORD OS_THREADCALL GrabThread(OS_thread_parm grabhdl);
	BDT_ZOOM_TYPE Float2Zoom(float &zoom);
	BOOL StartAcq(pSTRING fname, CIFrame **frames,short acqcmd,short frcnt, DWORD numDestFrames=1);
	BOOL ProcessGrabCommand(HANDLE hSpawner);

	BOOL FpgaInUse(void);
	CIFrame *m_gottenCamFrame;
	WORD m_trigLatest;
	CBDTCam *m_trigOpCamera;


	BYTE *m_BMBuffer;
	DWORD m_BMBufSize;
	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_EofIntr;

	BOOL m_bDDrawError;

	HANDLE m_grabFMO;


	void *m_grabArea;

	// Process peculiar grab components
	typedef struct {
		OS_thread_t		grab_thread;
		OS_sem_t		seq_change_sema[BDT_MAX_NUM_AOI_GRAB_RECS];
		OS_event_t		shutdownEvent;
		OS_event_t		grabCompleteEvent;
		OS_event_t		grabCmdEvent;

	} BDT_UNIQUE_GRAB_REC;
	BDT_UNIQUE_GRAB_REC m_procDepGrabRec;
	HANDLE m_hGrabServiceProcess;
	DWORD m_GrabServiceRefFunc;

	BOOLEAN m_fFpgaLoaded;
	BOOL m_dDrawConnected;

	BDII_VIDEO_BUFFER_LIST m_vidBufList;
	BDII_VIDEO_BUFFER m_vidBuffers[BDT_MAX_VID_BUFFERS];

    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[BDT_DUMP_ZONE_BUF_SIZE];

	void CalcBytesPerPixel(BOOL bPad, IFC_DEPTH depth, DWORD& dwSrcBytesPerPixel, DWORD& dwDestBytesPerPixel);
	BOOL WaitStartVB(CIFrame *frame);
	BOOL WaitNotVB(CIFrame *frame, BOOL vbsync);
	BOOL SetupBdt2Table();

public:
	PBDT_FUNC_TABLE m_vf;
	HMODULE m_brdLib;

};
#endif
// BOOL IFCAPI BanditCClkFreqSet(CICamera *cam, ACQ_PARAMS_TYPE parameter, DWORD index, double data);

#endif // !defined(AFX_Bandit_H__582D6F6E_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
