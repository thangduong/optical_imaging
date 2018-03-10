/******************************************************************************
 *
 * MODULE   
 *		Amv.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/AmV.h $
 *		$Revision: 1.1 $
 *		$Modtime: 4/27/00 3:38p $
 *
 * ABSTRACT  
 *		IFC interface of the CAmV class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_AMV_H__E99D9D72_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_AMV_H__E99D9D72_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <ICapMod.h>
#include <AcqMod.h>
#include <AmvReg.h>

// Note: Floating point constants are double by default.
#define XTAL_FREQ_MHZ 14.31800
#define XTAL_FREQ_KHZ 14318.00

#define MHZ_TO_KHZ 1000.0
#define KHZ_TO_MHZ 0.001
#define KHZ_TO_HZ  1000.0
#define HZ_TO_KHZ  0.001

#define NUM_AMV_CAM_MODULES 4
#define AMV_MAX_NUM_CAMERAS 4

#define NUM_PLL_REGS 7

typedef enum {
	AMV_PLLREG0,
	AMV_PLLREG1,
	AMV_PLLREG2,
	AMV_PLLREG3,
	AMV_PLLREG4,
	AMV_PLLREG5,
	AMV_PLLREG6
} AMV_PLLREGS_TYPE;


typedef enum {

	AMV_HSYNC_OUT,
	AMV_COMPOSITE_OUT

} AMV_CSYNCSEL_TYPE;

/* Acqusition register defines: */
typedef enum {
	AMV_FREEZE = 0,
	AMV_SNAP   = 2,
	AMV_GRAB   = 3
} AMV_ACQTYP;

typedef enum {
	AMV_AMCC_REG_SPACE,
	AMV_ID_AND_FPGA_REG_SPACE,
	AMV_ACQ_MOD_AND_LUTS_REG_SPACE,
	AMV_FRAME_BUF_CNTRL_REG_SPACE,
	AMV_FRAME_BUF_SPACE,
		
	AMV_NUM_ADDR_SPACES
} AMV_ADRSPACE_TYPE;

typedef enum {
	AMV_RS170_CAM,
	AMV_CCIR_CAM
} AMV_CAM_STD;


/***************************************************************************
**
** AMV Interrupts
**
*/
typedef enum {

    AMV_INTR_EXTIN_0,   /* External Input 0 Interrupt */
    AMV_INTR_EXTIN_1,   /* External Input 1 Interrupt */
    AMV_INTR_SOT,		/* Start of trigger Interupt */
    AMV_INTR_EOT,		/* End of trigger Interupt  */

    AMV_INTR_MAX_EVENT    /* must be last !!! */
} AMV_INTR_EVENT;


/* Standard Camera Definition Names */
#define AMV_DEF_RS512x480P "DEF_RS512x480P"
#define AMV_DEF_RS640x480P "DEF_RS640x480P"
#define AMV_DEF_RS720x480P "DEF_RS720x480P"
#define AMV_DEF_RS752x480P "DEF_RS752x480P"

#define AMV_DEF_CC512x512P "DEF_CC512x512P"
#define AMV_DEF_CC720x574P "DEF_CC720x574P"
#define AMV_DEF_CC768x574P "DEF_CC768x574P"
#define AMV_DEF_CC920x574P "DEF_CC920x574P"

#define AMV_DEF_RS512x480X "DEF_RS512x480X"
#define AMV_DEF_RS640x480X "DEF_RS640x480X"
#define AMV_DEF_RS720x480X "DEF_RS720x480X"
#define AMV_DEF_RS752x480X "DEF_RS752x480X"

#define AMV_DEF_CC512x512X "DEF_CC512x512X"
#define AMV_DEF_CC720x574X "DEF_CC720x574X"
#define AMV_DEF_CC768x574X "DEF_CC768x574X"
#define AMV_DEF_CC920x574X "DEF_CC920x574X"

#define AMV_MAX_CAM_DEF		256

#define AmvDefCamName AMV_DEF_RS640x480X

class IFC_EXT_API CAmV : public CAcqMod  
{
public:
	virtual CICamera* GetCam(DWORD camPortNum = IFC_ACTIVE_CAMERA_FLAG);
	void MakeAmvCamList();
	virtual BOOL WriteConfigFile(const char *szCfgFileName, BOOL eCamFlag = IFC_CFG_CURRENT_CAMERA, BOOL CreateCamDefs = TRUE);
	virtual BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName);
	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual BOOL ProcessCamerasInConfigFile(const char *szCfgFileName = NULL);
	virtual BOOL ReadUserConfigFile(const char *szCfgFileName);
	void WriteCamera(PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs = TRUE);
	void Cleanup();
	PIFC_CAMERA_DEF_TYPE FindCameraType(const char *camName);

	pSTRING GetFirstCamType(void);
	pSTRING GetNextCamType(void);

	BOOL InitializeRegs();
	virtual BOOL ModInit();
	virtual void ModDataInit(); // provided by leaf class, initializes module peculiar data
	virtual DWORD RegTableNumEntries(); // provided by leaf class returns num entries of static reg table
	virtual pIFC_MODREG RegTableAddr(); // provided by leaf class returns address of static reg table

	CAmV();
	virtual ~CAmV();

	DWORD GetFieldShiftMode(double dVertFreq, DWORD dwTimingSrc);
	void SetVsyncWidth(double dVsyncLines);
	double GetVsyncWidth(double dHorizFreq);
	void SetVsyncFreq(double dVertFreq, double dHorizFreq, DWORD dwTimingSrc);
	double GetVsyncFreq(double dHorizFreq, DWORD dwTimingSrc);
	double GetHsyncWidth(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	double GetClampDelay(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	double GetSerrationWidth(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	void SetEqualizationWidth(double dEqualizationWidth, double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	double GetEqualizationWidth(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	void SetVbackPorch(DWORD dwBpNumEqPulses);
	DWORD GetVbackPorch();
	void SetVfrontPorch(DWORD dwFpNumEqPulses);
	DWORD GetVfrontPorch();
	void SetFieldShiftMode(const DWORD dwEnable, double dVertFreq, DWORD dwTimingSrc);
	void SetClampDelay(double dClampDelay, double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	void SetSerrationWidth(double dSerrationWidth, double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	void SetHsyncWidth(double dHsyncWidth, double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	void SetPllRdiv(double dHorizFreq, DWORD dwTimingSrc);
	double CalcActualPixClkFreq(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	DWORD CalcRdiv(double dHorizFreq, DWORD dwTimingSrc);
	double CalcActualHorizFreq(double dHorizFreq, DWORD dwTimingSrc);
	DWORD CalcPixelsPerLine(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	BOOL ProgramPll(double dHorizFreq, double dPixClkFreq, DWORD dwTimingSrc);
	BOOL SetTimingSrc(DWORD dwTimingSrc);
	BOOL IsInterlaceAndFieldSelValid(const DWORD dwIlace, const DWORD dwFldSel);

	BOOL IsDacBuffered();
	void SetDacBufferMode(BOOL b);
	BOOL IsPllBuffered();
	void SetPllBufferMode(BOOL b);

	short			m_stfield;		// Starting field select
	ConfigSymbol*	m_SymbolTable;
	//OSHANDLE		m_BoardMutex;	// Board access mutex

protected:
	IFC_DECLARE_DYNCREATE(CAmV)

	void InitPll();
	void WritePllBuffer();
	void WritePllReg(const WORD wReg, const WORD wVal);
	WORD ReadPllReg(const WORD wReg);

	BOOL	m_bPllBuffered;
	WORD	m_PllBuffer[NUM_PLL_REGS];	// Buffer for PLL writes.
	WORD	m_PllShadow[NUM_PLL_REGS];	// Current values of the PLL registers.

	BOOL	m_bDacBuffered;
	DWORD	reserved1[50];	// Add to object size so as not to elicit MS small-block-heap bug


private:
	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
};

#endif // !defined(AFX_AMV_H__E99D9D72_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
