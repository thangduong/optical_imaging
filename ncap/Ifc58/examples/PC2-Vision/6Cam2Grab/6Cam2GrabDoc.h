// 6Cam2GrabDoc.h : interface of the C6Cam2GrabDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_6CAM2GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_)
#define AFX_6CAM2GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class C6Cam2GrabDoc : public CDocument
{
protected: // create from serialization only
	C6Cam2GrabDoc();
	DECLARE_DYNCREATE(C6Cam2GrabDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C6Cam2GrabDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C6Cam2GrabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C6Cam2GrabDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_6CAM2GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_)
