#if !defined(AFX_BULLS_COWVIEW_H__70496009_B36B_4DC0_B89C_99C30F9A1337__INCLUDED_)
#define AFX_BULLS_COWVIEW_H__70496009_B36B_4DC0_B89C_99C30F9A1337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
#define IDC_MYBUTTON 100 //идентификатор кнопки

class CBulls_CowView : public CView
{
public:
	CBulls_CowDoc* GetDocument();
	int full; //количество шариков в данной €чейке
	int st; //номер €чейки (строки)
	int row; //строка матрицы пол€
	int column; //столбец матрицы пол€
	int bulls; //количество быков
	int cows; //количество коров
	CStatic* m_Static1;	
	CStatic* m_Static2;	
	CStatic* m_Static3;	
	CStatic* m_Static4;	
	CStatic* m_Static5;	
	CStatic* m_Static6;	
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CBulls_CowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	CBulls_CowView();
	DECLARE_DYNCREATE(CBulls_CowView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CBulls_CowDoc* CBulls_CowView::GetDocument()
   { return (CBulls_CowDoc*)m_pDocument; }
#endif

#endif
