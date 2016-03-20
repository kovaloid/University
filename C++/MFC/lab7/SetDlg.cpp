// SetDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "lab7.h"
#include "SetDlg.h"


// диалоговое окно CSetDlg

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RED_RADIO, m_RedRadio);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	ON_BN_CLICKED(IDC_RED_RADIO, &CSetDlg::OnBnClickedRedRadio)
	ON_BN_CLICKED(IDC_GREEN_RADIO, &CSetDlg::OnBnClickedGreenRadio)
	ON_BN_CLICKED(IDC_BLUE_RADIO, &CSetDlg::OnBnClickedBlueRadio)
END_MESSAGE_MAP()


// обработчики сообщений CSetDlg

void CSetDlg::OnBnClickedRedRadio()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnBnClickedGreenRadio()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSetDlg::OnBnClickedBlueRadio()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
