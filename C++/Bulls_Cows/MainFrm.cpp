#include "stdafx.h"
#include "windows.h"
#include "mmsystem.h" 
#include "Bulls_Cow.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_INDEX, OnIndex)
END_MESSAGE_MAP()

CMainFrame::CMainFrame(){}
CMainFrame::~CMainFrame(){}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.cx = 334; //������ ����
	cs.cy = 505; //������ ����
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU; //����� ����
	return TRUE;
}

void CMainFrame::OnIndex()
{	
	MessageBox("��������� ���������� ������������������ �� ������� ����� ������� �����.\n������ ������ �� ����� ����� ������ ������������ � ���� ���������� �����.\n������ �� ����� ����� ������� ���� �������������� �� � ������, ������� � �������� ����.\n����� ��� ����������, ������� ������ ������ ���� ����� ������ � ��� ������������.\n����� ������� ���� �� ������������ ���� ������� ������ Delete.\n������ - ��� ���������� ��������� ����� ��� ���������� �������.\n� ���� - ��� ���������� �����, ������� ����� �� ����� ������.", "�������",MB_ICONINFORMATION);
}

#ifdef _DEBUG

void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif


