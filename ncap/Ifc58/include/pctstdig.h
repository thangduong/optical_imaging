/******************************************************************************
 *
 * MODULE   
 *		PCTstDig.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pctstdig.h $
 *		$Revision: 1.1 $
 *		$Modtime: 3/20/00 1:45p $
 *
 * ABSTRACT  
 *		IFC interface of the CPCTstDig class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999 (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_PCTstDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_PCTstDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>

/*
** PCTstDig Interrupt events 
*/
typedef enum {

	PCT_INTR_VB, 	  /* vertical blank */
	PCT_INTR_HB,
	PCT_INTR_TRIG0,
	PCT_INTR_TRIG1,
	PCT_INTR_SOACQ,
	PCT_INTR_EOACQ,
	PCT_INTR_INPORT,
	PCT_INTR_ACQ_ADRS,
	PCT_INTR_BMDONE,
	PCT_INTR_SW_TIMER,


	PCT_INTR_MAX_EVENT  /* MUST be last !!! */
} PCT_INTR_EVENT;



/* Acqusition register defines: */
typedef enum {
	PCT_FREEZE = 0,
	PCT_SNAP   = 2,
	PCT_GRAB   = 3
} PCT_ACQTYP;


typedef enum {
	PCT_AMCC_REG_SPACE,
	PCT_CONTROL_REG_SPACE,
		
	PCT_NUM_ADDR_SPACES
} PCT_ADRSPACE_TYPE;
  
typedef enum {
	PCT_PLL,
	PCT_XTAL,
} PCT_TIMING_SRC_TYPE;

         
#define PCT_DEF_RS512x480P "PCT_DEF_RS512x480P"
#define PCT_DEF_RS640x480P "PCT_DEF_RS640x480P"
#define PCT_DEF_RS720x480P "PCT_DEF_RS720x480P"
#define PCT_DEF_RS752x480P "PCT_DEF_RS752x480P"
#define PCT_DEF_RS512x480X "PCT_DEF_RS512x480X"
#define PCT_DEF_RS640x480X "PCT_DEF_RS640x480X"
#define PCT_DEF_RS720x480X "PCT_DEF_RS720x480X"
#define PCT_DEF_RS752x480X "PCT_DEF_RS752x480X"

#define PCT_DEF_CC512x512P "PCT_DEF_CC512x512P"
#define PCT_DEF_CC720x574P "PCT_DEF_CC720x574P"
#define PCT_DEF_CC768x574P "PCT_DEF_CC768x574P"
#define PCT_DEF_CC920x574P "PCT_DEF_CC920x574P"
#define PCT_DEF_CC512x512X "PCT_DEF_CC512x512X"
#define PCT_DEF_CC720x574X "PCT_DEF_CC720x574X"
#define PCT_DEF_CC768x574X "PCT_DEF_CC768x574X"
#define PCT_DEF_CC920x574X "PCT_DEF_CC920x574X"


#define PCT_PCI_DEVICE_ID       0x100
#define PCT_MODULE_NAME "PCT"

#define TST_NUM_PLL_REGS 7
#define TST_NUM_DAC_REGS 8

// Note: Floating point constants are double by default.
#define XTAL_FREQ_MHZ 14.31818
#define XTAL_FREQ_KHZ 14318.18

#define MHZ_TO_KHZ 1000.0
#define KHZ_TO_MHZ 0.001
#define KHZ_TO_HZ  1000.0
#define HZ_TO_KHZ  0.001


#include <ICapMod.h>
#include <PctReg.h>
#include <IFCTyp.h>
#include <pctcam.h>


#define XTAL_MODE  1
#define PCT_DEFAULT_CAMERA 	PCT_DEF_RS512x480X
#define ACQ_MUTEX_TIMEOUT 2000 // 2 seconds
#define PCR_DUMP_ZONE_BUF_SIZE 0x2000
#define PCT_MAX_NUM_CAMERAS 2

class PCTCam;

class IFC_EXT_API CPCTstDig : public CICapMod
{
public:
	virtual DWORD Revision();
	void Cleanup();
	BOOL InitializeRegs();
	virtual BOOL ModInit();
	void WriteCamera(PIFC_CAMERA_DEF_TYPE pCam);
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual DWORD RegTableNumEntries(); //  returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); //  returns address of static reg table
	virtual void ModDataInit(); //  initializes module peculiar data
	virtual BOOL Create(DWORD seqnum, char * cfgFile);
	virtual BOOL Create(DWORD seqnum);
	CPCTstDig();
	virtual ~CPCTstDig();

	BOOL SetTimingSrc(DWORD dwTimingSrc, WORD wTimingChan);
	DWORD CalcPixelsPerLine(double dHorizFreq, double dPixClkFreq);
	double CalcActualPixClkFreq(double dHorizFreq, double dPixClkFreq);
	BOOL ProgramPll(double dHorizFreq, double dPixClkFreq);
	void SetPllRdiv(double dHorizFreq);
	void InitDac();
	void WriteDacReg(const WORD wReg, const WORD wVal);
	void WriteDacNoOp();
	void WriteDacAddr(const WORD wAddr);
	void WriteDacData(const WORD wData);
	WORD ReadDacReg(const WORD wReg);
	WORD DacVoltsToVal(double dVolts);
//	double DacValToVolts(WORD wVal);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0);

	BOOL ActiveCamAttr(LPCAM_ATTR lpAttr);
//	virtual void ReleaseCamMutex(CICamera *camera);
//	virtual CIFrame *GetCamMutex(CICamera *camera);
	pSTRING GetFirstCamType(void);
	pSTRING GetNextCamType(void);
	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	virtual CICamera* GetActiveCamera();
	virtual void ReleaseActiveCamera();
	PCTCam	*m_pCameras[PCT_MAX_NUM_CAMERAS];

	PCTCam	*m_pActiveCamera;

	OS_sem_t	m_ActiveCameraMutex;

	OS_sem_t		m_AcqMutex;


	virtual IFC_INTREVENT ModInterruptEvent(CICamera *cam,ICAP_INTR_EVENT intrEvent);

	// Internal system element functions
	short LatencyTimer ( short mode);

	virtual BOOL FPGAByteWrite(BYTE val);
	virtual BOOL LoadFpga(char *szFpgaFileName);


	short			m_latencyTimer;
	BYTE			m_irqLine;		/* Interrupt line */
	DWORD			m_mbox1;		/* Mailbox register 1*/
	DWORD			m_mbox2;		/* Mailbox register 2*/
	DWORD			m_mbox3;		/* Mailbox register 3*/
	DWORD			m_mbox4;		/* Mailbox register 4*/
//	OS_sem_t		m_BoardMutex;



protected:
	IFC_DECLARE_DYNCREATE(CPCTstDig)

	DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey);
	void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey);

	void InitPll();
	void WritePllReg(const WORD wReg, const WORD wVal);
	WORD ReadPllReg(const WORD wReg);
	WORD m_PllShadow[TST_NUM_PLL_REGS];	// Current values of the PLL registers.
	WORD m_DacShadow[TST_NUM_DAC_REGS];	// Current values of the DAC registers.
	double CalcActualHorizFreq(double dHorizFreq);
	DWORD CalcRdiv(double dHorizFreq);
	void MakePCTCamList();


private:

	CInterrupt *m_BMDoneIntr;
	CInterrupt *m_AcqAddrIntr;
	CInterrupt *m_VBIntr;
    IFC_EDDS        m_dumpzone;		    /* Note , the dumpzone_annex must immediately follow this component */
	DWORD			m_dumpzoneAnnex[2]; /* space for 3rd Physmem desc */
	BYTE			m_dumpZoneBuf[PCR_DUMP_ZONE_BUF_SIZE];



};



#endif // !defined(AFX_PCTstDig_H__3353EEC4_86BB_11D1_A574_00A0C959E757__INCLUDED_)
