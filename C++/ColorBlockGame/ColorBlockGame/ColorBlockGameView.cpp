
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

void CColorBlockGameView::ResizeWindow()
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rcmyclient, rcmywindow;
	GetClientRect(&rcmyclient);
	GetParentFrame()->GetWindowRect(&rcmywindow);
	int diffW = rcmywindow.Width() - rcmyclient.Width();
	int diffH = rcmywindow.Height() - rcmyclient.Height();
	rcmywindow.right = rcmywindow.left + pDoc->Getboardwidth() * pDoc->Getboardcolumns() + diffW;
	rcmywindow.bottom = rcmywindow.top + pDoc->Getboardheight()* pDoc->Getboardrows() + diffH;
	GetParentFrame()->MoveWindow(&rcmywindow);
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

void CColorBlockGameView::OnDraw(CDC* pDC)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (!pDoc)
		return;
	int docSave = pDC->SaveDC();
	CRect rcmyClient;
	GetClientRect(&rcmyClient);
	/* getting background color of the document object :*/
	COLORREF clr = pDoc->getcolorcell(-1, -1);
	pDC->FillSolidRect(&rcmyClient, clr);
	CBrush br; //drawing tool
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	for (int i = 0; i < pDoc->Getboardrows(); i++) {
		for (int j = 0; j < pDoc->Getboardcolumns(); j++) {
			clr = pDoc->getcolorcell(i, j);
			CRect rccell;
			rccell.top = i * pDoc->Getboardheight();
			rccell.left = j * pDoc->Getboardwidth();
			rccell.right = rccell.left + pDoc->Getboardwidth();
			rccell.bottom = rccell.top + pDoc->Getboardheight();
			pDC->FillSolidRect(&rccell, clr);
			pDC->Rectangle(&rccell);
		}
	}
	pDC->RestoreDC(docSave);
	br.DeleteObject();

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

void CColorBlockGameView::onInitialUpdate()
{
	CView::OnInitialUpdate();
	ResizeWindow();
}

CColorBlockGameDoc* CColorBlockGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorBlockGameDoc)));
	return (CColorBlockGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorBlockGameView message handlers
