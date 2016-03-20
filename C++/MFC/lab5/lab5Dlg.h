// lab5Dlg.h : header file
//

#pragma once


// Clab5Dlg dialog
class Clab5Dlg : public CDialog
{
// Construction
public:
	Clab5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB5_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	int m_SpeedEdit;
	afx_msg void OnEnChangeSpeedEdit();
	afx_msg void OnFileCurrentspeed();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnHelpSayhello();
};
