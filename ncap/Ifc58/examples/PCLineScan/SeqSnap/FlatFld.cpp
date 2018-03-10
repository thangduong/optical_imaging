/******************************************************************************
 *
 * MODULE
 *    FlatFld.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/FlatFld.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 4/03/00 2:05p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "FlatFld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatField dialog


CFlatField::CFlatField(CWnd* pParent /*=NULL*/)
	: CDialog(CFlatField::IDD, pParent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CAM_ATTR attr;
	PCL_FFC_ATTR ffcAttr;

	theapp->m_cam->GetAttr(&attr);
	theapp->m_cam->GetFlatFieldAttr(&ffcAttr);
		
	//{{AFX_DATA_INIT(CFlatField)
	m_FlatFieldEnable = theapp->m_iCap->GetFlatFieldCorrState();
	m_GainMapTo = 0;
	m_OffsetMapTo = -1;
	m_ExplicitGain = 1.0f;
	m_ExplicitOffset = 0;
	m_MaxXPos = 0;
	m_MaxXPos2 = 0;
	m_maxOffset = 0;
	//}}AFX_DATA_INIT
	m_maxOffset = ffcAttr.maxOffset;
	m_MaxXPos = attr.dwWidth-1;
	m_MaxXPos2 = attr.dwWidth-1;
	if (theapp->m_srcBitspp < 16)
		m_GainMapTo = (1 << theapp->m_srcBitspp) - 1;
	else
		m_GainMapTo = 255;
}


void CFlatField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlatField)
	DDX_Control(pDX, IDC_GAIN_PLOT, m_ctlGainPlot);
	DDX_Control(pDX, IDC_OFFSET_PLOT, m_ctlOffsetPlot);
	DDX_Check(pDX, IDC_FLAT_FIELD_ENABLE, m_FlatFieldEnable);
	DDX_Text(pDX, IDC_GAIN_MAPTO, m_GainMapTo);
	DDV_MinMaxUInt(pDX, m_GainMapTo, 0, 65536);
	DDX_Text(pDX, IDC_OFFSET_MAPTO, m_OffsetMapTo);
	DDV_MinMaxInt(pDX, m_OffsetMapTo, -1, 65536);
	DDX_Text(pDX, IDC_EXPLICIT_GAIN, m_ExplicitGain);
	DDV_MinMaxFloat(pDX, m_ExplicitGain, 0.f, 4.f);
	DDX_Text(pDX, IDC_EXPLICIT_OFFSET, m_ExplicitOffset);
	DDV_MinMaxUInt(pDX, m_ExplicitOffset, 0, 1023);
	DDX_Text(pDX, IDC_MAX_X_POS, m_MaxXPos);
	DDX_Text(pDX, IDC_MAX_X_POS2, m_MaxXPos2);
	DDX_Text(pDX, IDC_MAX_OFFSET, m_maxOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlatField, CDialog)
	//{{AFX_MSG_MAP(CFlatField)
	ON_BN_CLICKED(IDC_SET_GAINS, OnSetGains)
	ON_BN_CLICKED(IDC_SET_OFFSETS, OnSetOffsets)
	ON_BN_CLICKED(IDC_READ_FFC_FILE, OnReadFfcFile)
	ON_BN_CLICKED(IDC_WRITE_FFC_FILE, OnWriteFfcFile)
	ON_BN_CLICKED(IDC_FLAT_FIELD_ENABLE, OnFlatFieldEnable)
	ON_BN_CLICKED(IDC_SET_EXPLICIT_OFFSETS, OnSetExplicitOffsets)
	ON_BN_CLICKED(IDC_SET_EXPLICIT_GAIN, OnSetExplicitGain)
	ON_BN_CLICKED(IDC_SET_OFFSETS_SPECTRUM, OnSetOffsetsSpectrum)
	ON_BN_CLICKED(IDC_SET_GAIN_SPECTRUM, OnSetGainSpectrum)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatField message handlers

void CFlatField::OnSetGains() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_cam->Freeze();
	theapp->m_cam->SetFlatFieldGain(m_GainMapTo); 
	m_FlatFieldEnable = theapp->m_iCap->GetFlatFieldCorrState();
	UpdateData(FALSE);
	PlotGainOffset();
	theapp->m_cam->Grab();
	
}

void CFlatField::OnSetOffsets() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_cam->Freeze();
	theapp->m_cam->SetFlatFieldOffset(m_OffsetMapTo); 	
	m_FlatFieldEnable = theapp->m_iCap->GetFlatFieldCorrState();
	UpdateData(FALSE);
	theapp->m_cam->Grab();
	PlotGainOffset();
}


void CFlatField::OnReadFfcFile() 
{
	CFileDialog dg(TRUE,"ffc",NULL,	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "FFC Files (*.ffc)|*.ffc|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
   		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
		theapp->m_cam->ReadFlatField(fname.GetBuffer(80));
		fname.ReleaseBuffer();
	}		
	PlotGainOffset();
	
}

void CFlatField::OnWriteFfcFile() 
{
	int result;
	CFileDialog dg(FALSE,"ffc",NULL,	
    			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
                "FFC Files (*.ffc)|*.ffc|"
                "All Files (*.*)|*.*||");
	result = dg.DoModal();
	if (result == IDOK) {
		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
		theapp->m_cam->SaveFlatField(fname.GetBuffer(80));
		fname.ReleaseBuffer();
	}		
}

void CFlatField::OnFlatFieldEnable() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_iCap->SetFlatFieldCorrState(m_FlatFieldEnable); 
}


BOOL CFlatField::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PlotGainOffset();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlatField::OnSetExplicitOffsets() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_cam->WriteFlatFieldOffsets(m_ExplicitOffset);	
	PlotGainOffset();
}


void CFlatField::OnSetExplicitGain() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_cam->WriteFlatFieldGains(m_ExplicitGain);	
	PlotGainOffset();
}

void CFlatField::OnSetOffsetsSpectrum() 
{
	DWORD i;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CAM_ATTR attr;
		
	theapp->m_cam->GetAttr(&attr);
	DWORD *offsets=new DWORD[attr.dwWidth];
	DWORD offsetMask=(attr.dwBitsPerPixel>8)?PCL_FFC_12BIT_MAX_OFFSET:PCL_FFC_8BIT_MAX_OFFSET;
	for (i=0 ; i < attr.dwWidth; i++)
		offsets[i] = i&offsetMask;
	theapp->m_cam->WriteFlatFieldOffsets(offsets,0,attr.dwWidth);	
	delete [] offsets;	
	PlotGainOffset();
}

void CFlatField::OnSetGainSpectrum() 
{
	DWORD i;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CAM_ATTR attr;
		
	theapp->m_cam->GetAttr(&attr);
	float *gains=new float[attr.dwWidth];
	for (i=0 ; i < attr.dwWidth; i++)
		gains[i] = i*PCL_FFC_MAX_GAIN / attr.dwWidth;
	theapp->m_cam->WriteFlatFieldGains(gains,0,attr.dwWidth);	
	delete [] gains;		
	PlotGainOffset();
}



void CFlatField::PlotGainOffset()
{
	DWORD i;
	CBrush cbr;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CAM_ATTR attr;
	PCL_FFC_ATTR ffcAttr;
	RECT cRect;
	CDC *hdc;
	POINT pt;

	theapp->m_cam->GetAttr(&attr);
	theapp->m_cam->GetFlatFieldAttr(&ffcAttr);
	cbr.CreateSolidBrush(RGB(0x80,0x0,0x80));


	float *gains=new float[attr.dwWidth];
	theapp->m_cam->ReadFlatFieldGains(gains,0,attr.dwWidth);	
	m_ctlGainPlot.GetClientRect(&cRect);
	hdc = m_ctlGainPlot.GetDC();
	hdc->FillRect(&cRect,&cbr);

	for (i=0 ; i < attr.dwWidth; i++) {
		pt.x = i * cRect.right / attr.dwWidth;
		pt.y = cRect.bottom;
		hdc->MoveTo(pt);
		pt.y = cRect.bottom - (long)(gains[i] * cRect.bottom / ffcAttr.maxGain);
		hdc->LineTo(pt);
	}
	ReleaseDC(hdc);
	delete [] gains;	
	m_ctlGainPlot.ValidateRect(NULL);


	DWORD *offsets=new DWORD[attr.dwWidth];
	theapp->m_cam->ReadFlatFieldOffsets(offsets,0,attr.dwWidth);	
	m_ctlOffsetPlot.GetClientRect(&cRect);
	hdc = m_ctlOffsetPlot.GetDC();
	hdc->FillRect(&cRect,&cbr);

	for (i=0 ; i < attr.dwWidth; i++) {
		pt.x = i * cRect.right / attr.dwWidth;
		pt.y = cRect.bottom;
		hdc->MoveTo(pt);
		pt.y = cRect.bottom - (long)(offsets[i] * cRect.bottom / ffcAttr.maxOffset);
		hdc->LineTo(pt);
	}
	ReleaseDC(hdc);
	delete [] offsets;	
	m_ctlOffsetPlot.ValidateRect(NULL);


	cbr.DeleteObject();

}

void CFlatField::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	PlotGainOffset();
	
	// Do not call CDialog::OnPaint() for painting messages
}
