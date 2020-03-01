// COptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ColorBlockGame.h"
#include "COptionsDialog.h"
#include "afxdialogex.h"

#define DEFAULTDIM1 15
#define DEFAULTDIM2 35

// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialogEx)

COptionsDialog::COptionsDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
{

}

COptionsDialog::COptionsDialog(bool bRowColumn, CWnd * pParent) : CDialog(IDD_DIALOG_OPTIONS, pParent), nRow1(0), nColumn1(0), m_RowColumnDialog(bRowColumn)
{

}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, b_IDOK);
	DDX_Control(pDX, IDCANCEL, b_IDCANCEL);
	DDX_Control(pDX, IDC_BUTTON_DEFAULT, b_IDDEFAULT);
	DDX_Control(pDX, IDC_EDIT_VALUE_1, c_EDIT1);
	DDX_Control(pDX, IDC_EDIT_VALUE_2, c_EDIT2);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, c_STATIC1);
	DDX_Control(pDX, IDC_STATIC_TEXT_2, c_STATIC2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, nRow1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, nColumn1);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, &COptionsDialog::OnBnClickedButtonDefault)
END_MESSAGE_MAP()


// COptionsDialog message handlers


BOOL COptionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (m_RowColumnDialog)
	{
		SetWindowText(_T("Updating number of blocks"));
		c_STATIC1.SetWindowText(_T("Number of rows:"));
		c_STATIC2.SetWindowText(_T("Number of columns:"));
	}
	else {
		SetWindowText(_T("Updating size of blocks"));
		c_STATIC1.SetWindowText(_T("Width of blocks:"));
		c_STATIC2.SetWindowText(_T("Height of blocks:"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionsDialog::OnBnClickedButtonDefault()
{
	if (m_RowColumnDialog)
		nRow1 = nColumn1 = DEFAULTDIM1;
	else
		nRow1 = nColumn1 = DEFAULTDIM2;
	UpdateData(false);
}
