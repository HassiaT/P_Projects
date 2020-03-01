
// CColorBlockGameDoc.h : interface of the CColorBlockGameDoc class
//
#pragma once
#include "ColorBlockBoard.h"
#include <stack>



class CColorBlockGameDoc : public CDocument
{


protected: // create from serialization only
	CColorBlockGameDoc();
	virtual ~CColorBlockGameDoc();
	DECLARE_DYNCREATE(CColorBlockGameDoc)

	// Attributes
public:

	// Operations
public:

	void UndoLastMove();
	bool CheckUndo();
	void RedoLast();
	bool CheckRedo();

	COLORREF getcolorcell(int _row, int _column) {
		return theboard->getcolorcell(_row, _column);
	}

	void setuptheboard(void) {
		theboard->setuptheboard();
	}

	int Getboardwidth() {
		return theboard->Getboardwidth();
	}

	void Setboardwidth(int width) {
		theboard->Setboardwidth(width);
	}

	int Getboardheight() {
		return theboard->Getboardheight();
	}

	void Setboardheight(int height) {
		theboard->Setboardheight(height);
	}


	void deleteboard(void)
	{
		theboard->deleteboard();
	}

	bool isGameOver() {
		return theboard->isgameOver();
	}

	int getNbcolors() {
		return theboard->GetNBColors();
	}

	void setNbcolors(int colors);

	int deleteRangeofBlocks(int row, int column) {
		std::shared_ptr<ColorBlockBoard> newBoard(theboard);
		stackUndo.push(newBoard);
		ClearRedo();
		int blocks = theboard->deleteRangeofBlocks(row, column);
		if (theboard->isgameOver())
			ClearUndo();
		return blocks;
	}

	int getRemainingBlocks() {
		return theboard->getRemainingBlocks();
	}

	int Getboardcolumns() {
		return theboard->Getboardcolumns();
	}

	void Setboardcolumns(int cols) {
		theboard->Setboardcolumns(cols);
	}

	int Getboardrows() {
		return theboard->Getboardrows();
	}

	void Setboardrows(int rows) {
		theboard->Setboardrows(rows);
	}

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//ColorBlockBoard theboard;
	std::shared_ptr<ColorBlockBoard> theboard;



	// Generated message map functions
protected:
	void ClearUndo();
	void ClearRedo();
	std::stack<std::shared_ptr<ColorBlockBoard>> stackUndo;
	std::stack<std::shared_ptr<ColorBlockBoard>> stackRedo;
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
