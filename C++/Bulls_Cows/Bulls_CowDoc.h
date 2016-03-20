#include <vector>
using namespace std;

#if !defined(AFX_BULLS_COWDOC_H__3D45B690_255F_4D70_A098_959700DB79C4__INCLUDED_)
#define AFX_BULLS_COWDOC_H__3D45B690_255F_4D70_A098_959700DB79C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CBulls_Cow
{
public:
	CBulls_Cow();
	int m_color; //цвет шарика
	vector<int> m_gen_number; //число загаданное компьютером [4]
	vector<int> m_field; //матрица поля [14][10]
	void Init_Field(); //создает пустое поля для новой игры
	void Reset_Last_Row(); //создает новую нижнюю строку
	void Number_Generator(); //генерирует комбинацию шариков
};

class CBulls_CowDoc : public CDocument
{
public:
	CBulls_Cow b; //объект вида окна
	virtual BOOL OnNewDocument();
	virtual ~CBulls_CowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	CBulls_CowDoc();
	DECLARE_DYNCREATE(CBulls_CowDoc);
	DECLARE_MESSAGE_MAP()	
};

#endif
