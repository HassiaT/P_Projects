
// ColorBlockGameView.cpp : implementation of the CColorBlockGameView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ColorBlockGame.h"
#endif

#include "ColorBlockGameDoc.h"
#include "ColorBlockGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorBlockGameView

IMPLEMENT_DYNCREATE(CColorBlockGameView, CView)

BEGIN_MESSAGE_MAP(CColorBlockGameView, CView)
END_MESSAGE_MAP()

// CColorBlockGameView construction/destruction

CColorBlockGameView::CColorBlockGameView() noexcept
{
	// TODO: add construction code here

}

CColorBlockGameView::~CColorBlockGameView()
{
}

BOOL CColorBlockGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CColorBlockGameView drawing

void CColorBlockGameView::OnDraw(CDC* /*pDC*/)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CColorBlockGameView diagnostics

#ifdef _DEBUG
void CColorBlockGameView::AssertValid() const
{
	CView::AssertValid();
}

void CColorBlockGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorBlockGameDoc* CColorBlockGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorBlockGameDoc)));
	return (CColorBlockGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorBlockGameView message handlers
