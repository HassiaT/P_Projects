
// ColorBlockGameView.h : interface of the CColorBlockGameView class
//

#pragma once


class CColorBlockGameView : public CView
{
protected: // create from serialization only
	CColorBlockGameView() noexcept;
	DECLARE_DYNCREATE(CColorBlockGameView)

// Attributes
public:
	CColorBlockGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();
	virtual ~CColorBlockGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP();
	

public:
	virtual void onInitialUpdate();
};

#ifndef _DEBUG  // debug version in ColorBlockGameView.cpp
inline CColorBlockGameDoc* CColorBlockGameView::GetDocument() const
   { return reinterpret_cast<CColorBlockGameDoc*>(m_pDocument); }
#endif

