
// ColorBlockGame.h : main header file for the ColorBlockGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CColorBlockGameApp:
// See ColorBlockGame.cpp for the implementation of this class
//

class CColorBlockGameApp : public CWinApp
{
public:
	CColorBlockGameApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CColorBlockGameApp theApp;
