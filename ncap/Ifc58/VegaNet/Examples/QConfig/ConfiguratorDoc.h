// ConfiguratorDoc.h : interface of the CConfiguratorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATORDOC_H__5F5B5B39_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
#define AFX_CONFIGURATORDOC_H__5F5B5B39_C772_11D2_B530_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CConfiguratorDoc : public CDocument
{
protected: // create from serialization only
	CConfiguratorDoc();
	DECLARE_DYNCREATE(CConfiguratorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfiguratorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfiguratorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:


// Generated message map functions
protected:
	//{{AFX_MSG(CConfiguratorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATORDOC_H__5F5B5B39_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
