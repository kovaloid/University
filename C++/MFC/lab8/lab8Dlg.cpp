// lab8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab8.h"
#include "lab8Dlg.h"

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


// Clab8Dlg dialog




Clab8Dlg::Clab8Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab8Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_PenColor = RGB(0, 0, 0);
	m_PenWidth=1;
}

void Clab8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PENWIDTH, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 1, 32);
	DDX_Radio(pDX, IDC_SOLID_PEN, m_PenStyle);
	DDX_Control(pDX, IDC_SHAPES, m_ShapesCombo);
	DDX_Control(pDX, IDC_BRUSHSTYLE, m_BrushStyleList);
}

BEGIN_MESSAGE_MAP(Clab8Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CLEARBTN, &Clab8Dlg::OnBnClickedClearbtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(IDC_PENCOLOR, &Clab8Dlg::OnStnClickedPencolor)
	ON_LBN_SELCHANGE(IDC_BRUSHSTYLE, &Clab8Dlg::OnLbnSelchangeBrushstyle)
	ON_STN_CLICKED(IDC_BRUSHCOLOR, &Clab8Dlg::OnStnClickedBrushcolor)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Clab8Dlg message handlers

BOOL Clab8Dlg::OnInitDialog()
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
	//�������� ��������� �� ������� ���������� Picture
		CWnd* p_Canvas=GetDlgItem(IDC_CANVAS);
	//�������� ���������� ���� � ���������� m_Canvas
		p_Canvas->GetWindowRect(&m_Canvas);
	//����������� ���������� ��� ���������� �������
		ScreenToClient(&m_Canvas);
	//�������� ���������� ����
		m_Canvas.DeflateRect(2,2,1,1);

	//�������� ��������� �� ������� ����������
		CWnd* pPenColor=GetDlgItem(IDC_PENCOLOR);
	//�������� ���������� �������� ����������
		pPenColor->GetWindowRect(&m_PenColorSwatch);
	//�������� ���������� ������������ ���������� �������
		ScreenToClient(&m_PenColorSwatch);
	//C����� ����� 
		m_PenColorSwatch.DeflateRect(2,2,1,1);

	//�������� ��������� �� ������� ����������
		CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);
	/*���������� �������� �������� ��������������� ��� IDC_SPIN1*/
		pSpin->SetRange(1,32);
	//���������� ��������� �������� �������� � 1;
		pSpin->SetPos(1);

	//���������� ��������� ������� �������
		m_ShapesCombo.SetCurSel(0);

	//�������� ��������� �� ������� ����������
		CWnd* pBrushColor=GetDlgItem(IDC_BRUSHCOLOR);
	//�������� ���������� �������� ����������
		pBrushColor->GetWindowRect(&m_BrushColorSwatch);
	//�������� ���������� ������������ ���������� �������
		ScreenToClient(&m_BrushColorSwatch);
	//C����� �����
		m_BrushColorSwatch.DeflateRect(2,2,1,1);

	//�������� ��������� �� ������� ����������
		CWnd* pPreviewColor=GetDlgItem(IDC_BRUSHPREVIEW);
	//�������� ���������� �������� ����������
		pPreviewColor->GetWindowRect(&m_BrushPreviewSwatch);
	//�������� ���������� ������������ ���������� �������
		ScreenToClient(&m_BrushPreviewSwatch);
	//C����� �����
		m_BrushPreviewSwatch.DeflateRect(2,2,1,1);
	//���������� ��������� ���� �����
		m_BrushColor=RGB(0,0,0);
	//������� ����� �����
		m_Brush.CreateStockObject(WHITE_BRUSH);

	//�������� �������� ������ � ������� ListBox
		m_BrushStyleList.AddString(L"(none)");
		m_BrushStyleList.AddString(L"Solid");
		m_BrushStyleList.AddString(L"LL-UR Diagonal");
		m_BrushStyleList.AddString(L"UL-LR Diagonal");
		m_BrushStyleList.AddString(L"Grid");
		m_BrushStyleList.AddString(L"Grid Diagonal");
		m_BrushStyleList.AddString(L"Horizontal");
		m_BrushStyleList.AddString(L"Vertical");
		m_BrushStyleList.AddString(L"White");
		m_BrushStyleList.AddString(L"Light Gray");
		m_BrushStyleList.AddString(L"Medium Gray");
		m_BrushStyleList.AddString(L"Dark Gray");
		m_BrushStyleList.AddString(L"Black");
	//���������� ��������� ������� ������� �� 8 ��������
		m_BrushStyleList.SetCurSel(8);

	//���������� � ������ ������ ���������
		m_pMF = new CMetaFileDC;
	//������� ��������
		m_pMF->Create();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab8Dlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting
	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;
	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialog::OnPaint();
	//}

	CPaintDC dc(this);
	//�������� ���������
		HMETAFILE hmf=m_pMF->Close();
	//��������������� ���������
		dc.PlayMetaFile(hmf);
	//������������ ��������� �� ������ ������ ���������� temp
		CMetaFileDC* temp=new CMetaFileDC;
	//�������� �������
		temp->Create();
	//������������ ���������
		temp->PlayMetaFile(hmf);
	//�������� ������������� � ���������
		//DeleteMetaFile(hmf);
		//delete hmf;
	//������������ ���������� ��������� �����������
		m_pMF=temp; 
	//���� ������ ��� ���� ������� ������ OnPaint, �� �������� ������� ������
		static int firstTime=TRUE;
		if(firstTime)
		{
			OnBnClickedClearbtn();
			firstTime=FALSE;
		}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab8Dlg::OnBnClickedClearbtn()
{
	// TODO: Add your control notification handler code here
	//�������� ��������� �� �������� ����������
		CClientDC dc(this);
	//������� ��������
		HMETAFILE hmf=m_pMF->Close();
	//������� ������ � ���������
		//::DeleteMetaFile(hmf);
		//delete hmf;
	//C������ ����� ��������
		m_pMF=new CMetaFileDC;
		m_pMF->Create();
		m_pMF->SetAttribDC(dc);
	//������� ������� ����
		dc.SelectStockObject(NULL_PEN);
	//�������� ����
		dc.Rectangle(m_Canvas);
	//�������� ������� � ��������
		m_pMF->SelectStockObject(NULL_PEN);
		m_pMF->Rectangle(m_Canvas.left,m_Canvas.top,
			m_Canvas.right+1,m_Canvas.bottom+1);
}

void Clab8Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);

	//��������� ���� �� ������� ������ ������� ���������.
	if(m_Canvas.PtInRect(point))
	{
		//��������� ���������� ������ ���� ����������
			m_LineStart=point;
			m_LineEnd=point;

			m_IsDrawing=true;

			m_Pen.DeleteObject();
		//�������� ���������� ���������� � ���� ��������
			UpdateData(TRUE);
		//������� ����� ����� � ������ �������
			m_Pen.CreatePen(m_PenStyle, m_PenWidth, m_PenColor);

		//��������� ����
			SetCapture();
	}
}

void Clab8Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnMouseMove(nFlags, point);

	/*
	if( (nFlags & MK_LBUTTON) && m_Canvas.PtInRect(point))
	{
		//�������� ��������� �� �������� ����������
			CClientDC dc(this);
			dc.SelectObject(&m_Pen);
		//��������� ���������� ������ ���������� m_LineEnd
			m_LineEnd=point;
		//���������� �����
			dc.MoveTo(m_LineStart);
			dc.LineTo(m_LineEnd);
		//��������� ������� ���������� m_LineStart �������� ������� �������
			m_LineStart=m_LineEnd;
	}
	*/

	tmp=point;

	if(m_IsDrawing&& (nFlags & MK_LBUTTON) && m_Canvas.PtInRect(point))
	{
		//���������� ������ ������� ��������� ����
			DrawShape(true);
		//�������� ���������� ����� �� ������� ��������� �������
			m_LineStart=m_LineEnd;
		//������� ���������� � ���������� ����� ������
			DrawShape(true);
	}
}

void Clab8Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonUp(nFlags, point);

	//��������� ����� ���������
		m_IsDrawing=FALSE;

	//���� ����� �������� ������ ������� ���������, �� ���������� ������ ������������
		if(m_Canvas.PtInRect(point))
		{
			m_LineEnd=point;
			DrawShape();
		}
	//���� ���, �� �������
		else
		{
			DrawShape(true);
		}
		m_LineStart=point;

	ReleaseCapture();
}

void Clab8Dlg::OnStnClickedPencolor()
{
	// TODO: Add your control notification handler code here
	//������� ������ ������ ���������� ������ ������ ����� � �������� ��� � ������������ ������� �������� �����
		CColorDialog dlg(m_PenColor);
	//����� ����������� ����
		if(dlg.DoModal()==IDOK)
		{
			//��������� �����
				m_PenColor=dlg.GetColor();
			//�������� �����
				CBrush swatch;
				swatch.CreateSolidBrush(m_PenColor);
			//�������� ������ ��������� ����������
				CClientDC dc(this);
			//������������ ���������� ��������� ������
				dc.FillRect(&m_PenColorSwatch, &swatch);
		}
}

void Clab8Dlg::DrawShape(bool stretch)
{
	//�������� ������ ��������� ����������
		CClientDC dc(this);
	//���������� �������� DC
		dc.SetAttribDC(dc);
		m_pMF->SetAttribDC(dc);
		dc.IntersectClipRect(m_Canvas);
		m_pMF->IntersectClipRect(m_Canvas);
	//�������� ����� ������� �� ����� �������� �����
		int drawmode=m_ShapesCombo.GetCurSel();
	//������� ���� � �����
		dc.SelectObject(&m_Pen);
		dc.SelectObject(&m_Brush);
	//�������� ��������� � ��������
		m_pMF->SelectObject(&m_Pen);
		m_pMF->SelectObject(&m_Brush);
	//����� ��������� ����
		if(stretch && drawmode!=0)
		{
			//���������� ����� ��������� ����
			dc.SetROP2(R2_NOT);
		}
	//����������� ������ ������
		switch(drawmode)
		{
			//��������� ���������
			case 0:
				m_LineEnd=tmp;
				dc.MoveTo(m_LineStart);
				dc.LineTo(m_LineEnd);
				//�������� ��������� � ��������
				m_pMF->MoveTo(m_LineStart);
				m_pMF->LineTo(m_LineEnd);
				m_LineStart=m_LineEnd;
			break;
			//��������� �����
			case 1:
				dc.MoveTo(m_LineStart);
				dc.LineTo(m_LineEnd);
				//�������� ��������� � ��������, ���� �� ������ ����� ��������� ����
				if(!stretch)
				{
					m_pMF->MoveTo(m_LineStart);
					m_pMF->LineTo(m_LineEnd);
				}
			break;
			//��������� �������
			case 2:
				dc.Ellipse(CRect(m_LineStart,m_LineEnd));
				//�������� ��������� � ��������
				if(!stretch)
				{
					m_pMF->Ellipse(CRect(m_LineStart,m_LineEnd));
				}
			break;
			//��������� ��������������
			case 3:
				dc.Rectangle(CRect(m_LineStart,m_LineEnd));
				//�������� ��������� � ��������
				if(!stretch)
				{
					m_pMF->Rectangle(CRect(m_LineStart,m_LineEnd));
				}
			break;
		}
}
void Clab8Dlg::OnLbnSelchangeBrushstyle()
{
	// TODO: Add your control notification handler code here
	//������� ���������� ������
		m_Brush.DeleteObject();
	//�������� ����� ��������� �������
		int style=m_BrushStyleList.GetCurSel();
	//�� ������ ������� �����, � ��������� ������
		switch(style)
		{
			case 0:
				m_Brush.CreateStockObject(NULL_BRUSH);
			break;
			case 1:
				m_Brush.CreateSolidBrush(m_BrushColor);
			break;
			case 2:
				m_Brush.CreateHatchBrush(HS_BDIAGONAL, m_BrushColor);
			break;
			case 3:
				m_Brush.CreateHatchBrush(HS_FDIAGONAL, m_BrushColor);
			break;
			case 4:
				m_Brush.CreateHatchBrush(HS_CROSS, m_BrushColor);
			break;
			case 5:
				m_Brush.CreateHatchBrush(HS_DIAGCROSS, m_BrushColor);
			break;
			case 6:
				m_Brush.CreateHatchBrush(HS_HORIZONTAL, m_BrushColor);
			break;
			case 7:
				m_Brush.CreateHatchBrush(HS_VERTICAL, m_BrushColor);
			break;
			case 9:
				m_Brush.CreateStockObject(LTGRAY_BRUSH);
			break;
			case 10:
				m_Brush.CreateStockObject(GRAY_BRUSH);
			break;
			case 11:
				m_Brush.CreateStockObject(DKGRAY_BRUSH);
			break;
			case 12:
				m_Brush.CreateStockObject(BLACK_BRUSH);
			break;
		//������� ����� �� ���������
			default:
				m_Brush.CreateStockObject(WHITE_BRUSH);
			break;
		}
	//������� ������� ��������� ���� Preview
		PaintBrushPreview();
}


void Clab8Dlg::PaintBrushPreview()
{
	CClientDC dc(this);
	dc.FillRect(&m_BrushPreviewSwatch,&m_Brush);
}


void Clab8Dlg::OnStnClickedBrushcolor()
{
	// TODO: Add your control notification handler code here
	//������� ������ ����������� ���� ����� �����
		CColorDialog dlg(m_BrushColor);
	//���� ���� ������ ������ ��, �� ��������� ��������� �����
		if(dlg.DoModal()==IDOK)
		{
			m_BrushColor=dlg.GetColor();
			CClientDC dc(this);
			CBrush b(m_BrushColor);
			//������������ ���������� ����� �����
			dc.FillRect(&m_BrushColorSwatch,&b);
		}
	//��������� ������� �������� �����, ��������� ������
		OnLbnSelchangeBrushstyle();
}

void Clab8Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	//������� � ������� ��������
		m_pMF->Close();
		delete m_pMF;
}
