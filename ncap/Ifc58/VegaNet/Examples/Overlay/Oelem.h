// OElem.h: interface for the COlayElem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OELEM_H__9FBCB8E2_FCA2_11D1_A122_00A0246D9D39__INCLUDED_)
#define AFX_OELEM_H__9FBCB8E2_FCA2_11D1_A122_00A0246D9D39__INCLUDED_

#include <afx.h>

class COPoint:public CObject  
{
public:
	COPoint():x(0),y(0){};
	COPoint(int ix, int iy):x(ix),y(iy){};

	int x;
	int y;
};


class COlayElem : public CObject  
{
public:
	COlayElem();
	COlayElem(COLORREF color);
	virtual ~COlayElem();
	virtual void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent) = 0;
	
public:
	COLORREF	m_Color;
	CPen	*m_pOldPen;
	
};

class CFreeLine : public COlayElem  
{
public:
	CFreeLine();
	CFreeLine(COLORREF color, int iThickness);
	void AddPoint(int x, int y);
	virtual ~CFreeLine();
	void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent);

private:
	CObList m_PointList;
	int		m_iLineThickness;
};

class COLine : public COlayElem  
{
public:
	COLine();
	COLine(COLORREF color, int iThickness, CPoint &p1, CPoint &p2);
	virtual ~COLine();
	void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent);

	int m_iLineThickness;

	POINT m_p1;
	POINT m_p2;
};

class CORectangle : public COlayElem  
{
public:
	CORectangle();
	CORectangle(COLORREF color, LPRECT rect);
	CORectangle(COLORREF color, CPoint &p1, CPoint &p2);
	virtual ~CORectangle();
	void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent);

	RECT	m_rcPosition;
};

class COEllipse : public CORectangle  
{
public:
	COEllipse();
	COEllipse(COLORREF color, LPRECT rect);
	COEllipse(COLORREF color, CPoint &p1, CPoint &p2);
	virtual ~COEllipse();
	void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent);
};


class COText : public COlayElem  
{
public:
	COText();
	COText(COLORREF color, CPoint &p1, CString str);
	virtual ~COText();
	void Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent);

	POINT m_p;
	CString m_strText;
};



#endif // !defined(AFX_OELEM_H__9FBCB8E2_FCA2_11D1_A122_00A0246D9D39__INCLUDED_)
