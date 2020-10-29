// MainDlg.h : header file
//

#if !defined(AFX_MAINDLG_H__A6290249_DEE6_4DF4_BF95_4B044C46924A__INCLUDED_)
#define AFX_MAINDLG_H__A6290249_DEE6_4DF4_BF95_4B044C46924A__INCLUDED_

#include "HexEdit.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

	HINSTANCE m_hInstMaster;
// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MIFAREONE_DIALOG };
	CHexEdit	m_edit_data;
	CHexEdit	m_edit_key;
	CHexEdit	m_edit_serial;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonWrite();
	afx_msg void OnButtonHalt();
	afx_msg void OnSelchangeComboPortBaud();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__A6290249_DEE6_4DF4_BF95_4B044C46924A__INCLUDED_)
