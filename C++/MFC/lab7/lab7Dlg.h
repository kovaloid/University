// lab7Dlg.h : header file
//
#include "SetDlg.h"

#pragma once


// Clab7Dlg dialog
class Clab7Dlg : public CDialog
{
// Construction
public:
	Clab7Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB7_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CSetDlg m_dlg;
	int m_Radius;
	int m_Direction;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExitButton();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedDrawgraphicsButton();
};
