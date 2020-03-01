
// ColorBlockGame.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ColorBlockGame.h"
#include "MainFrm.h"

#include "ColorBlockGameDoc.h"
#include "ColorBlockGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorBlockGameApp

BEGIN_MESSAGE_MAP(CColorBlockGameApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CColorBlockGameApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CColorBlockGameApp construction

CColorBlockGameApp::CColorBlockGameApp() noexcept
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ColorBlockGame.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CColorBlockGameApp object

CColorBlockGameApp theApp;


// CColorBlockGameApp initialization

BOOL CColorBlockGameApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CColorBlockGameDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CColorBlockGameView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CColorBlockGameApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGamelevel3couleurs();
	afx_msg void OnGamelevel5couleurs();
	afx_msg void OnGamelevel7couleurs();
};

CAboutDlg::CAboutDlg() noexcept : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_COMMAND(ID_GAMELEVEL_3COULEURS, &CAboutDlg::OnGamelevel3couleurs)
	ON_COMMAND(ID_GAMELEVEL_5COULEURS, &CAboutDlg::OnGamelevel5couleurs)
	ON_COMMAND(ID_GAMELEVEL_7COULEURS, &CAboutDlg::OnGamelevel7couleurs)
END_MESSAGE_MAP()

// App command to run the dialog
void CColorBlockGameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CColorBlockGameApp message handlers





void CAboutDlg::OnGamelevel3couleurs()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnGamelevel5couleurs()
{
	// TODO: Add your command handler code here
}


void CAboutDlg::OnGamelevel7couleurs()
{
	// TODO: Add your command handler code here
}
