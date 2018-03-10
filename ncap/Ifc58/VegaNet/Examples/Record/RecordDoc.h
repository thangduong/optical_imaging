// RecordDoc.h : interface of the CRecordDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDDOC_H__DD858F1D_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
#define AFX_RECORDDOC_H__DD858F1D_962D_11D5_B1ED_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRecordDoc : public CDocument
{
protected: // create from serialization only
	CRecordDoc();
	DECLARE_DYNCREATE(CRecordDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRecordDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRecordDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDDOC_H__DD858F1D_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
