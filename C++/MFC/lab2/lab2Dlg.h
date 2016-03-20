// lab2Dlg.h : header file
//

#pragma once


// Clab2Dlg dialog
class Clab2Dlg : public CDialog
{
// Construction
public:
	Clab2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	CString m_TestEdit;
	BOOL m_EnableCheck;
	BOOL m_VisibleCheck;
	afx_msg void OnExitButton();
	afx_msg void OnTestButton();
	afx_msg void OnClearButton();
	afx_msg void OnBnClickedVisibleCheck();
	afx_msg void OnBnClickedEnabledCheck();
	afx_msg void OnEnChangeTestEdit();
};
