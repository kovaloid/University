#pragma once


// диалоговое окно CSetDlg

class CSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CSetDlg();

// Данные диалогового окна
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_RedRadio;
	afx_msg void OnBnClickedRedRadio();
	afx_msg void OnBnClickedGreenRadio();
	afx_msg void OnBnClickedBlueRadio();
};
