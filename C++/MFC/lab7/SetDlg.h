#pragma once


// ���������� ���� CSetDlg

class CSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CSetDlg();

// ������ ����������� ����
	enum { IDD = IDD_CUSTOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_RedRadio;
	afx_msg void OnBnClickedRedRadio();
	afx_msg void OnBnClickedGreenRadio();
	afx_msg void OnBnClickedBlueRadio();
};
