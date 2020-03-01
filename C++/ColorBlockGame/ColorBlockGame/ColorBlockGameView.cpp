
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
#include "COptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorBlockGameView

IMPLEMENT_DYNCREATE(CColorBlockGameView, CView)

BEGIN_MESSAGE_MAP(CColorBlockGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_GAMELEVEL_3COULEURS, &CColorBlockGameView::OnUpdateGamelevel3couleurs)
	ON_UPDATE_COMMAND_UI(ID_GAMELEVEL_5COULEURS, &CColorBlockGameView::OnUpdateGamelevel5couleurs)
	ON_UPDATE_COMMAND_UI(ID_GAMELEVEL_7COULEURS, &CColorBlockGameView::OnUpdateGamelevel7couleurs)
	ON_COMMAND(ID_GAMELEVEL_3COULEURS, &CColorBlockGameView::OnGamelevel3couleurs)
	ON_COMMAND(ID_GAMELEVEL_5COULEURS, &CColorBlockGameView::OnGamelevel5couleurs)
	ON_COMMAND(ID_GAMELEVEL_7COULEURS, &CColorBlockGameView::OnGamelevel7couleurs)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CColorBlockGameView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CColorBlockGameView::OnSetupBlocksize)
	ON_COMMAND(ID_EDIT_UNDO, &CColorBlockGameView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CColorBlockGameView::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CColorBlockGameView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CColorBlockGameView::OnUpdateEditRedo)
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
void CColorBlockGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int row_coordinate = point.x / pDoc->Getboardheight();
	int col_coordinate = point.y / pDoc->Getboardwidth();
	int count = pDoc->deleteRangeofBlocks(row_coordinate, col_coordinate);
	if (count > 0) {
		Invalidate();
		UpdateWindow();
		if (pDoc->isGameOver())
		{
			int remaining = pDoc->getRemainingBlocks();
			CString message;
			message.Format(_T("You cannot make further moves. Remaining \nBlocks %d"), remaining);
			MessageBox(message, _T("GAME OVER"), MB_OK | MB_ICONINFORMATION);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CColorBlockGameView::OnUpdateGamelevel3couleurs(CCmdUI *pCmdUI)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->getNbcolors() == 3);
}


void CColorBlockGameView::OnUpdateGamelevel5couleurs(CCmdUI *pCmdUI)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->getNbcolors() == 5);
}


void CColorBlockGameView::OnUpdateGamelevel7couleurs(CCmdUI *pCmdUI)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->getNbcolors() == 7);
}


void CColorBlockGameView::OnGamelevel3couleurs()
{
	CColorBlockGameDoc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->setNbcolors(3);
	Invalidate();
	UpdateWindow();
}


void CColorBlockGameView::OnGamelevel5couleurs()
{
	CColorBlockGameDoc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->setNbcolors(5);
	Invalidate();
	UpdateWindow();
}


void CColorBlockGameView::OnGamelevel7couleurs()
{
	CColorBlockGameDoc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->setNbcolors(7);
	Invalidate();
	UpdateWindow();
}


void CColorBlockGameView::OnSetupBlockcount()
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COptionsDialog boxdialog(true, this);
	boxdialog.nRow1 = pDoc->Getboardrows();
	boxdialog.nColumn1 = pDoc->Getboardcolumns();
	if (boxdialog.DoModal() == IDOK) {
		pDoc->deleteboard();
		pDoc->Setboardrows(boxdialog.nRow1);
		pDoc->Setboardcolumns(boxdialog.nColumn1);
		pDoc->setuptheboard();
		ResizeWindow();
	}
}




void CColorBlockGameView::OnSetupBlocksize()
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	COptionsDialog boxdialog(false, this);
	boxdialog.nRow1 = pDoc->Getboardwidth();
	boxdialog.nColumn1 = pDoc->Getboardheight();
	if (boxdialog.DoModal() == IDOK) {
		pDoc->deleteboard();
		pDoc->Setboardrows(boxdialog.nRow1);
		pDoc->Setboardcolumns(boxdialog.nColumn1);
		pDoc->setuptheboard();
		ResizeWindow();
	}
}


void CColorBlockGameView::OnEditUndo()
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLastMove();
	Invalidate();
	UpdateWindow();
}


void CColorBlockGameView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->CheckUndo());
}


void CColorBlockGameView::OnEditRedo()
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();
	Invalidate();
	UpdateWindow();
}



void CColorBlockGameView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	CColorBlockGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->Enable(pDoc->CheckRedo());
}
