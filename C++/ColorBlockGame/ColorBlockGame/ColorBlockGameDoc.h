
// CColorBlockGameDoc.h : interface of the CColorBlockGameDoc class
//
#pragma once
#include "ColorBlockBoard.h"


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

	COLORREF getcolorcell(int _row, int _column) {
		return theboard.getcolorcell(_row, _column);
	}

	void setuptheboard(void) {
		theboard.setuptheboard();
	}
	int Getboardwidth() {
		return theboard.Getboardwidth();
	}
	int Getboardheight() {
		return theboard.Getboardheight();
	}
	void deleteboard(void)
	{
		theboard.deleteboard();
	}
	int Getboardcolumns() {
		return theboard.Getboardcolumns();
	}

	int Getboardrows() {
		return theboard.Getboardrows();
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
	ColorBlockBoard theboard;


	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
