// 3Cam1GrabDoc.h : interface of the C3Cam1GrabDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3CAM1GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_)
#define AFX_3CAM1GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class C3Cam1GrabDoc : public CDocument
{
protected: // create from serialization only
	C3Cam1GrabDoc();
	DECLARE_DYNCREATE(C3Cam1GrabDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3Cam1GrabDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3Cam1GrabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C3Cam1GrabDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3CAM1GRABDOC_H__E1B3769A_56C9_4B8E_AC6C_B89C2D7CD095__INCLUDED_)
