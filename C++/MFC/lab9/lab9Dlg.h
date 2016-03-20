// lab9Dlg.h : header file
//

#pragma once


// Clab9Dlg dialog
class Clab9Dlg : public CDialog
{
// Construction
public:
	Clab9Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB9_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HICON m_Club;
	HICON m_Diamond;
	HICON m_Heart;
	HICON m_Spade;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Card1;
	CStatic m_Card4;
	CStatic m_Card2;
	CStatic m_Card3;
	CButton m_Amt_Left;
	double m_Amt_Remaining;
	int m_Cards[5];
	HICON& PickRandomCard();
	void CalculateWinnings();
	void DealCards();
	afx_msg void OnBnClickedDealcards();
	afx_msg void OnBnClickedCancel();
};
