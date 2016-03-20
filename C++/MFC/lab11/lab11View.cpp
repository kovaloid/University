// lab11View.cpp : implementation of the Clab11View class
//

#include "stdafx.h"
#include "lab11.h"

#include "lab11Doc.h"
#include "lab11View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab11View

IMPLEMENT_DYNCREATE(Clab11View, CFormView)

BEGIN_MESSAGE_MAP(Clab11View, CFormView)
END_MESSAGE_MAP()

// Clab11View construction/destruction

Clab11View::Clab11View()
	: CFormView(Clab11View::IDD)
{
	// TODO: add construction code here

}

Clab11View::~Clab11View()
{
}

void Clab11View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ENABLE_TASK1_CHECK, m_EnableTask1Check);
	DDX_Check(pDX, IDC_ENABLE_TASK2_CHECK, m_EnableTask2Check);
	DDX_Check(pDX, IDC_ENABLE_TASK3_CHECK, m_EnableTask3Check);
	DDX_Text(pDX, IDC_TASK1_EDIT, m_Task1Edit);
	DDX_Text(pDX, IDC_TASK2_EDIT, m_Task2Edit);
	DDX_Text(pDX, IDC_TASK3_EDIT, m_Task3Edit);
}

BOOL Clab11View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void Clab11View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_EnableTask1Check=TRUE;
	m_EnableTask2Check=TRUE;
	m_EnableTask3Check=TRUE;
	m_Task1Edit=0;
	m_Task2Edit=0;
	m_Task3Edit=0;
	UpdateData(FALSE);
}


// Clab11View diagnostics

#ifdef _DEBUG
void Clab11View::AssertValid() const
{
	CFormView::AssertValid();
}

void Clab11View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

Clab11Doc* Clab11View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab11Doc)));
	return (Clab11Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab11View message handlers
