#include "stdafx.h"
#include "windows.h"
#include "mmsystem.h"
#include "Bulls_Cow.h"
#include "Bulls_CowDoc.h"
#include "Bulls_CowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBulls_CowView, CView)
BEGIN_MESSAGE_MAP(CBulls_CowView, CView)	
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CBulls_CowView::CBulls_CowView()
{
	full=1;
	st=1;
	column=2; row=1;
	bulls=0; cows=0;	
	m_Static1 = new CStatic();
	m_Static2 = new CStatic();
	m_Static3 = new CStatic();
	m_Static4 = new CStatic();
	m_Static5 = new CStatic();
	m_Static6 = new CStatic();
}

CBulls_CowView::~CBulls_CowView(){}

BOOL CBulls_CowView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CBulls_CowView::OnDraw(CDC* pDC)
{
	CBulls_CowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBitmap bitmap;
    BITMAP bmp;
	bitmap.DeleteObject();
	bitmap.LoadBitmap(IDB_FIELD);
	bitmap.GetObject(sizeof(BITMAP), &bmp);
	pDC->DrawState(CPoint(0,0),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
	for(int j=0; j<14; j++)
	{
		for(int i=0; i<10; i++)
		{
			bitmap.DeleteObject();
			switch(pDoc->b.m_field[i+10*j])
			{
			case 0:
					bitmap.LoadBitmap(IDB_BLACK);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break;
			case 1:
					bitmap.LoadBitmap(IDB_BLUE);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break;
			case 2:
					bitmap.LoadBitmap(IDB_BROWN);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break;
			case 3:
					bitmap.LoadBitmap(IDB_GREEN);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break;
			case 4:
					bitmap.LoadBitmap(IDB_RED);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break;            
			case 5:
					bitmap.LoadBitmap(IDB_YELLOW);
					bitmap.GetObject(sizeof(BITMAP), &bmp);            
				pDC->DrawState(CPoint(32*i,32*j),CSize(bmp.bmWidth,bmp.bmHeight),bitmap, DST_BITMAP);
					break; 
			case -1:  
					break; 
			}            
		}
	}
}

#ifdef _DEBUG
void CBulls_CowView::AssertValid() const
{
	CView::AssertValid();
}

void CBulls_CowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBulls_CowDoc* CBulls_CowView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBulls_CowDoc)));
	return (CBulls_CowDoc*)m_pDocument;
}
#endif

void CBulls_CowView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int x=(int)point.x/32; //координата по горизонтали
    int y=(int)point.y/32; //координата по вертикали
	static int x0;      //координаты выбранного шарика
    static int y0;
	
	CBulls_CowDoc* pDoc=GetDocument();
	if((x>1 && x<8) && y==13)
	{
		if((pDoc->b.m_field[x+10*y]>-1 && pDoc->b.m_field[x+10*y]<6) && full==1)
		{
			x0=x; y0=y;
			pDoc->b.m_field[column+10*row]=pDoc->b.m_field[x0+10*y0];
			pDoc->b.m_field[x0+10*y0]=-1;
			full=2;		
			column++;
		}
		if((pDoc->b.m_field[x+10*y]>-1 && pDoc->b.m_field[x+10*y]<6) && full==2)
		{
			x0=x; y0=y;
			pDoc->b.m_field[column+10*row]=pDoc->b.m_field[x0+10*y0];
			pDoc->b.m_field[x0+10*y0]=-1;
			full=3;		
			column++;
		}
		if((pDoc->b.m_field[x+10*y]>-1 && pDoc->b.m_field[x+10*y]<6) && full==3)
		{
			x0=x; y0=y;
			pDoc->b.m_field[column+10*row]=pDoc->b.m_field[x0+10*y0];
			pDoc->b.m_field[x0+10*y0]=-1;
			full=4;		
			column++;
		}
		if((pDoc->b.m_field[x+10*y]>-1 && pDoc->b.m_field[x+10*y]<6) && full==4)
		{
			x0=x; y0=y;
			pDoc->b.m_field[column+10*row]=pDoc->b.m_field[x0+10*y0];
			pDoc->b.m_field[x0+10*y0]=-1;
			full=5;			
		}
	}
	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}

void CBulls_CowView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CBulls_CowDoc* pDoc=GetDocument();
	int inResult;	
	CString str;
	bulls=0;
	cows=0;
	if(full==5) //заполнена ли вся строка
	{
		//ищем быков
		for(int l=0,i=2;i<6;i++,l++)				
			if(pDoc->b.m_field[i+10*row]==pDoc->b.m_gen_number[l])
				bulls++;
		//ищем коров
		for(int i=2;i<6;i++)
			for(int j=0;j<4;j++)				
				if(pDoc->b.m_field[i+10*row]==pDoc->b.m_gen_number[j])
					cows++;
		column=2;
		row=row+2;
		full=1;		
		cows=cows-bulls; //узнаём кол-во коров, т.к. среди них находятся быки
		str.Format("Быков:%d,коров:%d ",bulls,cows); //заносим в строку количество быков и коров
		
		if(st==1)
		{
			//после заполнения первой строки выводим количество быков и коров
			m_Static1 = new CStatic();		
			m_Static1->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,40,320,56),this);
		}
		if(st==2)
		{	
			//после заполнения второй строки выводим количество быков и коров
			m_Static2 = new CStatic();
			m_Static2->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,103,320,119),this);
		}
		if(st==3)
		{	
			//после заполнения третий строки выводим количество быков и коров
			m_Static3 = new CStatic();
			m_Static3->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,168,320,184),this);
		}
		if(st==4)
		{	
			//после заполнения четвёртой строки выводим количество быков и коров
			m_Static4 = new CStatic();
			m_Static4->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,232,320,248),this);
		}
		if(st==5)
		{
			//после заполнения пятой строки выводим количество быков и коров
			m_Static5 = new CStatic();
			m_Static5->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,296,320,312),this);
		}
		if(st==6)
		{	
			//после заполнения шестой строки выводим количество быков и коров
			m_Static6 = new CStatic();
			m_Static6->Create(str,WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(200,360,320,376),this);
		}

		st++; //переходим на следующую строку
		pDoc->b.Reset_Last_Row();

		if(bulls==4)
		{
			//если 4 быка 		
			inResult=sndPlaySound("res\\vic.wav",SND_SYNC);	
			MessageBox("Ну ты крут!!!","Сообщение",MB_OK|MB_ICONINFORMATION);	
			//создание новой игры
			full=1;
			column=2; row=1;
			bulls=0; cows=0;			
			pDoc->OnNewDocument();
			//удаление указателей на статические окна
			if(1<st) delete m_Static1;
			if(2<st) delete m_Static2;
			if(3<st) delete m_Static3;
			if(4<st) delete m_Static4;
			if(5<st) delete m_Static5;
			if(6<st) delete m_Static6;	
			st=1;
		}
		if(row==13)
		{	
			//если последняя строка заполнена
			MessageBox("Game Over чувак!!!","Сообщение",MB_OK|MB_ICONINFORMATION);
			inResult=sndPlaySound("res\\end.wav",SND_SYNC);
			//создание новой игры
			full=1;
			column=2; row=1;
			bulls=0; cows=0;			
			pDoc->OnNewDocument();
			//удаление указателей на статические окна
			if(1<st) delete m_Static1;
			if(2<st) delete m_Static2;
			if(3<st) delete m_Static3;
			if(4<st) delete m_Static4;
			if(5<st) delete m_Static5;
			if(6<st) delete m_Static6;
			st=1;
		}
	}
	else
	{
		//если поставлены не все шарики
		inResult=sndPlaySound("res\\mis.wav",SND_SYNC);
		AfxMessageBox("Поставь все шарики!!!");
	}		
	bulls=0; cows=0;		
	Invalidate(FALSE);
	CView::OnRButtonUp(nFlags, point);
}

void CBulls_CowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CBulls_CowDoc* pDoc=GetDocument();
	if(nChar==VK_DELETE)
	{
		column=2;		
		for(int i=2;i<6;i++)
			pDoc->b.m_field[i+10*row]=-1;
		pDoc->b.Reset_Last_Row();
		full=1;
		int inResult;
		inResult=sndPlaySound("res\\del.wav",SND_SYNC);	
	}
    Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}