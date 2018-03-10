// FrameDlyDoc.h : interface of the CFrameDlyDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEDLYDOC_H__3F90F943_1DAB_4B3B_84AF_942C328FEA1E__INCLUDED_)
#define AFX_FRAMEDLYDOC_H__3F90F943_1DAB_4B3B_84AF_942C328FEA1E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFrameDlyDoc : public CDocument
{
protected: // create from serialization only
	CFrameDlyDoc();
	DECLARE_DYNCREATE(CFrameDlyDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameDlyDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameDlyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFrameDlyDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEDLYDOC_H__3F90F943_1DAB_4B3B_84AF_942C328FEA1E__INCLUDED_)
