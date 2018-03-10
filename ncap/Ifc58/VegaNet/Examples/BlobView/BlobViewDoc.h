// BlobViewDoc.h : interface of the CBlobViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOBVIEWDOC_H__AD5EF08F_01EC_11D5_B181_00105A0F576C__INCLUDED_)
#define AFX_BLOBVIEWDOC_H__AD5EF08F_01EC_11D5_B181_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBlobViewDoc : public CDocument
{
protected: // create from serialization only
	CBlobViewDoc();
	DECLARE_DYNCREATE(CBlobViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlobViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBlobViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBlobViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBVIEWDOC_H__AD5EF08F_01EC_11D5_B181_00105A0F576C__INCLUDED_)
