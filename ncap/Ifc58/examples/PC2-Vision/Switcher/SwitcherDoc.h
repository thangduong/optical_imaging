// SwitcherDoc.h : interface of the CSwitcherDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHERDOC_H__9AFEEA63_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_SWITCHERDOC_H__9AFEEA63_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSwitcherDoc : public CDocument
{
protected: // create from serialization only
	CSwitcherDoc();
	DECLARE_DYNCREATE(CSwitcherDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitcherDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitcherDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHERDOC_H__9AFEEA63_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
