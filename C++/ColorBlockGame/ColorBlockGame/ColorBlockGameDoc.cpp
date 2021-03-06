
// ColorBlockGameDoc.cpp : implementation of the CColorBlockGameDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ColorBlockGame.h"
#endif

#include "ColorBlockBoard.h"

#include <propkey.h>
#include "ColorBlockGameDoc.h"
#include<iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorBlockGameDoc
IMPLEMENT_DYNCREATE(CColorBlockGameDoc, CDocument)
BEGIN_MESSAGE_MAP(CColorBlockGameDoc, CDocument)
END_MESSAGE_MAP()


// CColorBlockGameDoc construction/destruction
CColorBlockGameDoc::CColorBlockGameDoc(void)
{
	std::cout << "In constructor for class ColorBlockGame \n";
	auto delColorBlockBoard = [](ColorBlockBoard* pBoard) {
		std::cout << "Deleting color block board";
		delete pBoard;
	};

	theboard = std::make_shared<ColorBlockBoard>();
}

CColorBlockGameDoc::~CColorBlockGameDoc()
{
	ClearUndo();
	ClearRedo();
}

void CColorBlockGameDoc::UndoLastMove()
{
	if (stackUndo.empty())
		return;
	stackRedo.push(theboard);
	theboard = stackUndo.top();
	stackUndo.pop();
}

bool CColorBlockGameDoc::CheckUndo()
{
	return !stackUndo.empty();
}

void CColorBlockGameDoc::RedoLast()
{
	if (stackRedo.empty())
		return;
	stackUndo.push(theboard);
	theboard = stackRedo.top();
	stackRedo.pop();

}

bool CColorBlockGameDoc::CheckRedo()
{
	return !stackRedo.empty();
}

void CColorBlockGameDoc::setNbcolors(int colors)
{
	theboard->SetNBColors(colors);
	theboard->setuptheboard();
}

BOOL CColorBlockGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	theboard->setuptheboard();
	ClearUndo();
	ClearRedo();
	return TRUE;
}


void CColorBlockGameDoc::ClearUndo()
{
	while (!stackUndo.empty()) {
		stackUndo.pop();
	}
}

void CColorBlockGameDoc::ClearRedo()
{
	while (!stackRedo.empty()) {
		stackRedo.pop();
	}


}

// CColorBlockGameDoc serialization
void CColorBlockGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CColorBlockGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CColorBlockGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorBlockGameDoc::ClearUndo()
{
	std::cout << "Clear";
}

void CColorBlockGameDoc::ClearRedo()
{
}

void CColorBlockGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorBlockGameDoc diagnostics

#ifdef _DEBUG
void CColorBlockGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorBlockGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CColorBlockGameDoc commands
