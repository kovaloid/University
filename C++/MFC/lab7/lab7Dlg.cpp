// lab7Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab7.h"
#include "lab7Dlg.h"

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


// Clab7Dlg dialog




Clab7Dlg::Clab7Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab7Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clab7Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &Clab7Dlg::OnBnClickedExitButton)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DRAWGRAPHICS_BUTTON, &Clab7Dlg::OnBnClickedDrawgraphicsButton)
END_MESSAGE_MAP()


// Clab7Dlg message handlers

BOOL Clab7Dlg::OnInitDialog()
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

	int iInstallResult;
	iInstallResult=SetTimer(1, 50, NULL);
	if(iInstallResult==FALSE)
	{
		MessageBox(L"Cannot install timer",
			L"Error message",
			MB_OK+MB_ICONERROR);
	}
	m_dlg.m_RedRadio=0;
	m_Radius=50;
	m_Direction=1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab7Dlg::OnPaint()
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
		//OnBnClickedDrawgraphicsButton();
		///Создать объект контекста устройства(DC)
			CPaintDC dc(this);
		//Создать новое перо
			CPen MyNewPen;
			switch(m_dlg.m_RedRadio)
			{
			case 0:
				MyNewPen.CreatePen(PS_SOLID, 10, RGB(255,0,0));
			break;
			case 1:
				MyNewPen.CreatePen(PS_SOLID, 10, RGB(0,255,0));
			break;
			case 2:
				MyNewPen.CreatePen(PS_SOLID, 10, RGB(0,0,255));
			break;
			}
		//Выбрать перо
			CPen* pOriginalPen;
			pOriginalPen=dc.SelectObject(&MyNewPen);
		// CRect MyRectangle(20, 10, 120,110);
			if (m_Radius < 100)
			{
				CRect MyRectangle(20, 10, 20+m_Radius*2,10+m_Radius*2);
				dc.Ellipse(&MyRectangle);
			}
			else
			{
				int i1=rand()%10;
				int i2=rand()%10;
				int i3=rand()%10;
				int i4=rand()%10;
				int i5=rand()%10;

				CRect MyRectangle1(87+i1, 20+i1, 154+i1, 87+i1);
				dc.Ellipse(&MyRectangle1);

				CRect MyRectangle2(30+i2, 63+i2, 97+i2, 130+i2);
				dc.Ellipse(&MyRectangle2);

				CRect MyRectangle3(144+i3, 63+i3, 210+i3, 130+i3);
				dc.Ellipse(&MyRectangle3);

				CRect MyRectangle4(53+i4, 123+i4, 120+i4, 190+i4);
				dc.Ellipse(&MyRectangle4);

				CRect MyRectangle5(120+i5, 123+i5, 187+i5, 190+i5);
				dc.Ellipse(&MyRectangle5);
			}
		//Выбрать первоначальное перо
			dc.SelectObject(pOriginalPen);

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab7Dlg::OnBnClickedExitButton()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void Clab7Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
}

void Clab7Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//MessageBeep((WORD)-2);
	m_Radius=m_Radius+m_Direction;
	if(m_Radius>=100)
	{
		//m_Direction=-1;
		m_Direction=0;
	}
	if(m_Radius<=10)
	{
		m_Direction=1;
	}
	Invalidate();

	CDialog::OnTimer(nIDEvent);
}

void Clab7Dlg::OnBnClickedDrawgraphicsButton()
{
	// TODO: Add your control notification handler code here
	/////Создать объект контекста устройства(DC)
	//	CClientDC dc(this);
	////Создать новое перо
	//	CPen MyNewPen;
	//	MyNewPen.CreatePen(PS_SOLID, 10, RGB(255,0,0));
	////Выбрать перо
	//	CPen* pOriginalPen;
	//	pOriginalPen=dc.SelectObject(&MyNewPen);
	//	CRect MyRectangle(20, 10, 120,110);
	////Нарисовать круг
	//	dc.Ellipse(&MyRectangle);
	////Выбрать первоначальное перо
	//	dc.SelectObject(pOriginalPen);
	m_dlg.DoModal();
}
