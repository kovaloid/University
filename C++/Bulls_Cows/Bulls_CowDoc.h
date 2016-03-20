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
	int m_color; //���� ������
	vector<int> m_gen_number; //����� ���������� ����������� [4]
	vector<int> m_field; //������� ���� [14][10]
	void Init_Field(); //������� ������ ���� ��� ����� ����
	void Reset_Last_Row(); //������� ����� ������ ������
	void Number_Generator(); //���������� ���������� �������
};

class CBulls_CowDoc : public CDocument
{
public:
	CBulls_Cow b; //������ ���� ����
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
