// lab9Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab9.h"
#include "lab9Dlg.h"

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


// Clab9Dlg dialog




Clab9Dlg::Clab9Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab9Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_Club = AfxGetApp()->LoadIcon(IDI_CLUB);
	m_Diamond = AfxGetApp()->LoadIcon(IDI_DIAMOND);
	m_Heart = AfxGetApp()->LoadIcon(IDI_HEART);
	m_Spade = AfxGetApp()->LoadIcon(IDI_SPADE);
}

void Clab9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARD1, m_Card1);
	DDX_Control(pDX, IDC_CARD4, m_Card4);
	DDX_Control(pDX, IDC_CARD2, m_Card2);
	DDX_Control(pDX, IDC_CARD3, m_Card3);
	DDX_Control(pDX, IDC_AMT_LEFT, m_Amt_Left);
}

BEGIN_MESSAGE_MAP(Clab9Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DEALCARDS, &Clab9Dlg::OnBnClickedDealcards)
	ON_BN_CLICKED(IDCANCEL, &Clab9Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Clab9Dlg message handlers

BOOL Clab9Dlg::OnInitDialog()
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
	m_Amt_Remaining=100.00;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab9Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab9Dlg::OnPaint()
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
HCURSOR Clab9Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HICON& Clab9Dlg::PickRandomCard()
{
	//Выбрать номер карты случайным образом
		int num=(rand()%4);
	//Проссумировать кол-во выпавших карт одной масти
		m_Cards[num]++;
	//В зависимости от выпавшего номера вернуть адрес иконки
		switch(num)
		{
			case 0: return m_Club;
			case 1: return m_Diamond;
			case 2: return m_Heart;
		}
	return m_Spade;
}


void Clab9Dlg::CalculateWinnings()
{
	int pairs=0;
	for(int i=0; i<4; i++)
	{
		if(m_Cards[i]==2)
		{
			if(pairs>0)
			{
				m_Amt_Remaining+=3.00;
				break;
			}
			else
			{
				pairs++;
			}
		}
		else if(m_Cards[i]==3)
		{
			m_Amt_Remaining+=6.00;
			break;

		}
		else if (m_Cards[i]==4)
		{
			m_Amt_Remaining+=9.00;
			break;
		}
	}
}


void Clab9Dlg::DealCards()
{
	//Обнуляем заначение выпавших карт одной масти
		for(int i=0; i<4; i++) m_Cards[i]=0;
	//Меняем иконку в элементах управления иконками
		m_Card1.SetIcon(PickRandomCard());
		m_Card2.SetIcon(PickRandomCard());
		m_Card3.SetIcon(PickRandomCard());
		m_Card4.SetIcon(PickRandomCard());
}


void Clab9Dlg::OnBnClickedDealcards()
{
	// TODO: Add your control notification handler code here
	//Отнять два доллара при сдаче карт
		m_Amt_Remaining-=2.00;
	//Сдать карты
		DealCards();
	//Подсчитать выйгрыш
		CalculateWinnings();
	//Изменить заголовок элемента Group Box
		CString s;
		s.Format(L"Amount Remaining $ %.2f", m_Amt_Remaining);
		m_Amt_Left.SetWindowText(s);
}

void Clab9Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CString s;
	//Добавить в сторку размер выйгрыша
		s.Format(L"Good game! I have $ %.2f.", m_Amt_Remaining);
	//Выдать окно сообщения 
		MessageBox(s, L"Thank you for game in FourUp!");

	OnCancel();
}
