// lab6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab6.h"
#include "lab6Dlg.h"

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


// Clab6Dlg dialog




Clab6Dlg::Clab6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESULTS_EDIT, m_ResultsEdit);
}

BEGIN_MESSAGE_MAP(Clab6Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &Clab6Dlg::OnBnClickedExitButton)
	ON_BN_CLICKED(IDC_OKCANCEL_BUTTON, &Clab6Dlg::OnBnClickedOkcancelButton)
	ON_BN_CLICKED(IDC_YESNOCANCEL_BUTTON, &Clab6Dlg::OnBnClickedYesnocancelButton)
	ON_BN_CLICKED(IDC_RETRYCANCEL_BUTTON, &Clab6Dlg::OnBnClickedRetrycancelButton)
	ON_BN_CLICKED(IDC_YESNO_BUTTON, &Clab6Dlg::OnBnClickedYesnoButton)
END_MESSAGE_MAP()


// Clab6Dlg message handlers

BOOL Clab6Dlg::OnInitDialog()
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

void Clab6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab6Dlg::OnPaint()
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
HCURSOR Clab6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab6Dlg::OnBnClickedExitButton()
{
	// TODO: Add your control notification handler code here
	int iResults;	
	iResults=MessageBox(L"Exit?",
		L"Are you sure want to Exit?",
		MB_YESNO+MB_ICONQUESTION);
	if(iResults==IDYES)
	{
		OnOK();
	}
}

void Clab6Dlg::OnBnClickedOkcancelButton()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults=MessageBox(L"You want Ok and Cancel buttons.",
		L"I am the second parametr of the MessageBox function",
		MB_OKCANCEL+MB_ICONSTOP);
	if(iResults==IDOK)
	{
		m_ResultsEdit="You Clicked the Ok button";
		UpdateData(FALSE);
	}
	if(iResults==IDCANCEL)
	{
		m_ResultsEdit="You clicked on the Cancel button";
		UpdateData(FALSE);
	}
}

void Clab6Dlg::OnBnClickedYesnocancelButton()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults=MessageBox(L"You want Yes, No and Cancel buttons.",
		L"I am the second parameter of the MessageBox function",
		MB_YESNOCANCEL+MB_ICONINFORMATION);
	if(iResults==IDYES)
	{
		m_ResultsEdit="You clicked on the Yes button.";
		UpdateData(FALSE);
	}
	if(iResults==IDNO)
	{
		m_ResultsEdit="You clicked on the No button";
		UpdateData(FALSE);
	}
	if(iResults==IDCANCEL)
	{
		m_ResultsEdit="You clicked on the Cancel button.";
		UpdateData(FALSE);
	}
}

void Clab6Dlg::OnBnClickedRetrycancelButton()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults=MessageBox(L"You want Retry and Cancel buttons.",
		L"I am the second parameter of the MessageBox function",
		MB_RETRYCANCEL+MB_ICONQUESTION);
	if(iResults==IDRETRY)
	{
		m_ResultsEdit="You clicked on the Retry button.";
		UpdateData(FALSE);
	}
	if(iResults==IDCANCEL)
	{
		m_ResultsEdit="You clicked on the Cancel button.";
		UpdateData(FALSE);
	}
}

void Clab6Dlg::OnBnClickedYesnoButton()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults=MessageBox(L"You want Yes and No buttons.",
		L"I am the second parameter of the MessageBox function",
		MB_YESNO+MB_ICONEXCLAMATION);
	if(iResults==IDOK)
	{
		m_ResultsEdit="You clicked on the OK button.";
		UpdateData(FALSE);
	}
	if(iResults==IDNO)
	{
		m_ResultsEdit="You clicked on the NO button.";
		UpdateData(FALSE);
	}
}
