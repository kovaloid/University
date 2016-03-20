// lab2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab2.h"
#include "lab2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Clab2Dlg dialog




Clab2Dlg::Clab2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEST_EDIT, m_TestEdit);
	DDX_Check(pDX, IDC_ENABLED_CHECK, m_EnableCheck);
	DDX_Check(pDX, IDC_VISIBLE_CHECK, m_VisibleCheck);
}

BEGIN_MESSAGE_MAP(Clab2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXIT2_BUTTON, &Clab2Dlg::OnExitButton)
	ON_BN_CLICKED(IDC_TEST_BUTTON, &Clab2Dlg::OnTestButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &Clab2Dlg::OnClearButton)
	ON_BN_CLICKED(IDC_VISIBLE_CHECK, &Clab2Dlg::OnBnClickedVisibleCheck)
	ON_BN_CLICKED(IDC_ENABLED_CHECK, &Clab2Dlg::OnBnClickedEnabledCheck)
	ON_EN_CHANGE(IDC_TEST_EDIT, &Clab2Dlg::OnEnChangeTestEdit)
END_MESSAGE_MAP()


// Clab2Dlg message handlers

BOOL Clab2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//Устаноить переменную флажка VisibleCheck и EnabledCheck в состояние TRUE
		m_VisibleCheck=TRUE;
		m_EnableCheck=TRUE;
	//Обновить экран
		UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Clab2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab2Dlg::OnExitButton()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void Clab2Dlg::OnTestButton()
{
	// TODO: Add your control notification handler code here
	m_TestEdit="This is a Test";
	UpdateData(FALSE);
}

void Clab2Dlg::OnClearButton()
{
	// TODO: Add your control notification handler code here
	m_TestEdit=" ";
	UpdateData(FALSE);
}

void Clab2Dlg::OnBnClickedVisibleCheck()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_VisibleCheck==TRUE)
		GetDlgItem(IDC_TEST_EDIT)->ShowWindow(SW_SHOW);
	else
		GetDlgItem(IDC_TEST_EDIT)->ShowWindow(SW_HIDE);
}

void Clab2Dlg::OnBnClickedEnabledCheck()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_EnableCheck==TRUE)
		GetDlgItem(IDC_TEST_EDIT)->EnableWindow(SW_SHOW);
	else
		GetDlgItem(IDC_TEST_EDIT)->EnableWindow(SW_HIDE);
}

void Clab2Dlg::OnEnChangeTestEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);
	CString UpperValue;
	UpperValue=m_TestEdit;
	UpperValue.MakeUpper();
	if(UpperValue=="PAINT")
	{
		system("pbrush.exe");
		m_TestEdit=" ";
		UpdateData(FALSE);
	}
	if(UpperValue=="CALCULATOR")
	{
		system("calc.exe");
		m_TestEdit=" ";
		UpdateData(FALSE);
	}
	if(UpperValue=="BEEP")
	{
		MessageBeep((WORD)-2);
		m_TestEdit=" ";
		UpdateData(FALSE);
	}
}
