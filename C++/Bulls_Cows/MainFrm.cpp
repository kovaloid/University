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
	cs.cx = 334; //ширина окна
	cs.cy = 505; //высота окна
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU; //стиль окна
	return TRUE;
}

void CMainFrame::OnIndex()
{	
	MessageBox("Компьютер загадывает последовательность из четырех шаров разного цвета.\nЗадача игрока за шесть ходов узнать расположение и цвет загаданных шаров.\nКликая по шарам левой кнопкой мыши устанавливайте их в ячейки, начиная с верхнего ряда.\nКогда ряд расставлен, нажмите правую кнопку мыши чтобы узнать о его правильности.\nЧтобы удалить шары из заполняемого ряда нажмите кнопку Delete.\nКоровы - это количество угаданных шаров без совпадения позиции.\nА быки - это количество шаров, которые стоят на своих местах.", "Правила",MB_ICONINFORMATION);
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


