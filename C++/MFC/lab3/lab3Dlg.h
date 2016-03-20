// lab3Dlg.h : header file
//

#pragma once


// Clab3Dlg dialog
class Clab3Dlg : public CDialog
{
// Construction
public:
	Clab3Dlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	enum { IDD = IDD_LAB3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	int m_PrevX;
	int m_PrevY;

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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
