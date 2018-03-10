// OElem.cpp: implementation of the COlayElem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "overlay.h"
#include "OElem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COlayElem::COlayElem()
{
	m_Color = RGB(0,0,0);
}

COlayElem::COlayElem(COLORREF color)
{
	m_Color = color;
}

COlayElem::~COlayElem()
{
}

CFreeLine::CFreeLine(COLORREF color, int iThickness):
COlayElem(color),m_iLineThickness(iThickness)
{
};

CFreeLine::~CFreeLine()
{
	if(!m_PointList.IsEmpty())
	{
	    POSITION pos;
		COPoint *pPoint;
		pos = m_PointList.GetHeadPosition();
		pPoint = (COPoint*)m_PointList.GetAt(pos); 
		delete pPoint;
		// Iterate through the list in head-to-tail order.
		while(m_PointList.GetNext(pos) && pos!=NULL){
			pPoint = (COPoint*)m_PointList.GetAt(pos); 
			delete pPoint;
		}
		m_PointList.RemoveAll();
	}
}

void CFreeLine::AddPoint(int x, int y)
{
	m_PointList.AddTail(new COPoint(x,y));
};

void CFreeLine::Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent)
{
	CPen *pOldPen;
	CPen *pPen = new CPen(PS_SOLID, (int)(m_iLineThickness * (fZoomX+fZoomY)/2), m_Color); 
	pOldPen = pDC->SelectObject(pPen);

	POSITION pos;
	COPoint *pPoint;
	pos = m_PointList.GetHeadPosition();
	pPoint = (COPoint*)m_PointList.GetAt(pos); 
	pDC->MoveTo( (int)(pPoint->x * fZoomX), (int)(pPoint->y * fZoomY));
	// Iterate through the list in head-to-tail order.
	while(m_PointList.GetNext(pos) && pos!=NULL){
		pPoint = (COPoint*)m_PointList.GetAt(pos);
		pDC->LineTo( (int)(pPoint->x * fZoomX), (int)(pPoint->y * fZoomY) );
	}
	pDC->SelectObject(pOldPen);
	delete pPen;
};


COLine::COLine()
{
	m_p1.x = 0;
	m_p1.y = 0;
	m_p2.x = 0;
	m_p2.y = 0;
}
COLine::~COLine()
{
}

COLine::COLine(COLORREF color, int iThickness, CPoint &p1, CPoint &p2):
COlayElem(color),m_iLineThickness(iThickness)
{
	m_p1.x = p1.x;
	m_p1.y = p1.y;
	m_p2.x = p2.x;
	m_p2.y = p2.y;
}

void COLine::Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent)
{
	CPen *pOldPen;
	CPen *pPen = new CPen(PS_SOLID, int(m_iLineThickness * (fZoomX+fZoomY)/2), m_Color); 
	pOldPen = pDC->SelectObject(pPen);

	pDC->MoveTo((int)(m_p1.x*fZoomX), (int)(m_p1.y*fZoomY));
	pDC->LineTo((int)(m_p2.x*fZoomX), (int)(m_p2.y*fZoomY));

	pDC->SelectObject(pOldPen);
	delete pPen;
}

CORectangle::CORectangle()
{
	SetRectEmpty(&m_rcPosition);
}

CORectangle::CORectangle(COLORREF color, LPRECT rect):
COlayElem(color)
{
	CopyRect(&m_rcPosition, rect);
}

CORectangle::CORectangle(COLORREF color, CPoint &p1, CPoint &p2):
COlayElem(color)
{
   m_rcPosition.left	= min(p1.x, p2.x);
   m_rcPosition.right	= max(p1.x, p2.x);
   m_rcPosition.top		= min(p1.y, p2.y);
   m_rcPosition.bottom	= max(p1.y, p2.y);
}


CORectangle::~CORectangle()
{
}

void CORectangle::Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent)
{
	CBrush *pOldBrush;
	CBrush *pBrush = new CBrush(m_Color); 
	pOldBrush = pDC->SelectObject(pBrush);
	CPen *pOldPen;
	CPen *pPen = new CPen(PS_SOLID, 1, m_Color); 
	pOldPen = pDC->SelectObject(pPen);

	pDC->Rectangle( int(m_rcPosition.left * fZoomX),
					int(m_rcPosition.top * fZoomY),
					int(m_rcPosition.right * fZoomX),
					int(m_rcPosition.bottom * fZoomY));

	pDC->SelectObject(pOldBrush);
	delete pBrush;
	pDC->SelectObject(pOldPen);
	delete pPen;
}



COEllipse::COEllipse():
CORectangle()
{
}

COEllipse::COEllipse(COLORREF color, LPRECT rect):
CORectangle(color, rect)
{

}

COEllipse::COEllipse(COLORREF color, CPoint &p1, CPoint &p2):
CORectangle(color, p1, p2)
{

}

COEllipse::~COEllipse()
{
}

void COEllipse::Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent)
{
	CBrush *pOldBrush;
	CBrush *pBrush = new CBrush(m_Color); 
	pOldBrush = pDC->SelectObject(pBrush);
	CPen *pOldPen;
	CPen *pPen = new CPen(PS_SOLID, 1, m_Color); 
	pOldPen = pDC->SelectObject(pPen);

	pDC->Ellipse(	int(m_rcPosition.left * fZoomX),
					int(m_rcPosition.top * fZoomY),
					int(m_rcPosition.right * fZoomX),
					int(m_rcPosition.bottom * fZoomY));

	pDC->SelectObject(pOldBrush);
	delete pBrush;
	pDC->SelectObject(pOldPen);
	delete pPen;
}

COText::COText()
{
}

COText::COText(COLORREF color, CPoint &p, CString str):
COlayElem(color)
{
	m_p.x = p.x;
	m_p.y = p.y;
	m_strText = str;
};

COText::~COText()
{
}
void COText::Display(CDC *pDC, float fZoomX, float fZoomY, COLORREF transparent)
{
	pDC->SetBkColor(transparent);
	pDC->SetTextColor(m_Color);
	pDC->TextOut((int)(m_p.x * fZoomX), (int)(m_p.y * fZoomY), m_strText);
}

