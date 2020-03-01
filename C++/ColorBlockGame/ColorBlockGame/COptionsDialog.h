#pragma once

#include "afxwin.h"


// COptionsDialog dialog

class COptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(CWnd* pParent = nullptr);   // standard constructor

	COptionsDialog(bool bRowColumn, CWnd* pParent = nullptr);   // standard constructor

	virtual ~COptionsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	CButton b_IDOK;
	CButton b_IDCANCEL;
	CButton b_IDDEFAULT;
	CEdit c_EDIT1;
	CEdit c_EDIT2;
	CStatic c_STATIC1;
	CStatic c_STATIC2;
	int nRow1;
	int nColumn1;
	
	virtual BOOL OnInitDialog();


private:
	bool m_RowColumnDialog;


public:
	afx_msg void OnBnClickedButtonDefault();
};
