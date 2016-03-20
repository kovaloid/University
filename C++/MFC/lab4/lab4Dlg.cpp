// lab4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab4.h"
#include "lab4Dlg.h"

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


// Clab4Dlg dialog




Clab4Dlg::Clab4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clab4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// Clab4Dlg message handlers

BOOL Clab4Dlg::OnInitDialog()
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

void Clab4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab4Dlg::OnPaint()
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
HCURSOR Clab4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab4Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	char strnChar[10];
	char strnRepCnt[10];
	char strnFlags[16];

	/*CString str;
	for (int i = 15; i >= 0; i--) 
    {
        if ((1 << i) & nFlags) 
            str=+(CString)"1";
        else 
			str=+(CString)"0";
    }*/

	itoa(nChar, strnChar, 10);
	itoa(nRepCnt, strnRepCnt,10);
	itoa(nFlags, strnFlags, 2);

	CString strKeyPressed=(CString)"You pressed the key: \nnChar="+(CString)strnChar+
	(CString)"\nnReptCnt="+(CString)strnRepCnt+
	(CString)"\nnFlags="+(CString)strnFlags;

	MessageBox(strKeyPressed);

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);

	/*Параметры:
	nChar
		Определяет код с виртуальной клавишей данной клавиши.
	nRepCnt
		Содержит повторный счет, число раз, сколько нажатие 
		клавиши повторено, когда пользователь удерживает клавишу.
	nFlags
		Определяет скэн-код, код перехода клавиши, предыдущее 
		состояние клавиши и контекстный код, как показано в 
		следующем списке:

	0-7		Скэн-код (значение OEM зависимый). Младший байт 
			старшего слова. 	
	8		Расширенная клавиша типа функциональной клавиши или 
			клавиши на цифровой клавиатуре 
			(1 если это - расширенная клавиша, иначе 0). 	
	9-10 	Не используеться. 	
	11-12 	Для  внутреннего использования  Windows. 	
	13		Контекстный код (1 если клавиша ALT нажата в то время 
			как нажата  клавиша, иначе 0). 	
	14		Предыдущее состояние клавиши (1 если клавиша внизу  
			перед обращением, 0 если клавиша вверху). 	
	15		Состояние Перехода (1 если клавиша отпускается, 0 если 
			клавиша нажимается).

	Для WM_KEYDOWN сообщения, бит перехода клавиши (бит 15) - 0, и 
	бит контекстного кода (бит 13) - 0.*/
}
