// lab5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab5.h"
#include "lab5Dlg.h"

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


// Clab5Dlg dialog




Clab5Dlg::Clab5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SPEED_EDIT, m_SpeedEdit);
}

BEGIN_MESSAGE_MAP(Clab5Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_SPEED_EDIT, &Clab5Dlg::OnEnChangeSpeedEdit)
	ON_COMMAND(ID_FILE_CURRENTSPEED, &Clab5Dlg::OnFileCurrentspeed)
	ON_COMMAND(ID_FILE_EXIT, &Clab5Dlg::OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, &Clab5Dlg::OnHelpAbout)
	ON_COMMAND(ID_HELP_SAYHELLO, &Clab5Dlg::OnHelpSayhello)
END_MESSAGE_MAP()


// Clab5Dlg message handlers

BOOL Clab5Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab5Dlg::OnPaint()
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
HCURSOR Clab5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab5Dlg::OnEnChangeSpeedEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}

void Clab5Dlg::OnFileCurrentspeed()
{
	// TODO: Add your command handler code here
	char strSpeed[100];
	itoa(m_SpeedEdit,strSpeed,10);
	CString str=(CString)strSpeed;
	MessageBox(str, _T("Current Speed"), MB_OK);
}

void Clab5Dlg::OnFileExit()
{
	// TODO: Add your command handler code here
	OnOK();
}

void Clab5Dlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void Clab5Dlg::OnHelpSayhello()
{
	// TODO: Add your command handler code here
	MessageBox(L"Hello!", L"Hello!", MB_OK);
}
