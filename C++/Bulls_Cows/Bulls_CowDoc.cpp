#include "stdafx.h"
#include "Bulls_Cow.h"
#include "Bulls_CowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBulls_CowDoc, CDocument)
BEGIN_MESSAGE_MAP(CBulls_CowDoc, CDocument)
END_MESSAGE_MAP()

CBulls_CowDoc::CBulls_CowDoc()
{
	b.Init_Field();
	b.Number_Generator();
}

CBulls_CowDoc::~CBulls_CowDoc(){}

BOOL CBulls_CowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	b.Init_Field();
	b.Number_Generator();	
	return TRUE;
}

#ifdef _DEBUG
void CBulls_CowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBulls_CowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

CBulls_Cow::CBulls_Cow()
{
	for (int i=0;i<4;i++)
		m_gen_number.push_back(0);
	for (int i=0;i<140;i++)
		m_field.push_back(0);
}

void CBulls_Cow::Reset_Last_Row()
{
	m_field[10*13+0]=-1;
	m_field[10*13+1]=-1;
	m_field[10*13+2]=0;
	m_field[10*13+3]=1;
	m_field[10*13+4]=2;
	m_field[10*13+5]=3;
	m_field[10*13+6]=4;
	m_field[10*13+7]=5;
	m_field[10*13+8]=-1;
	m_field[10*13+9]=-1;
}

void CBulls_Cow::Init_Field()
{
	for(int i=0;i<13;i++)
		for(int j=0;j<10;j++)
			m_field[10*i+j]=-1;
	Reset_Last_Row();
}

void CBulls_Cow::Number_Generator()
{
	srand(GetTickCount()%32000); //инициализация генератора случайных чисел
    m_gen_number[0]=rand()%6;
	for(;;)
	{
		m_gen_number[1]=rand()%6;
		if(m_gen_number[1]!=m_gen_number[0])
			break;
	}
	for(;;)
	{
		m_gen_number[2]=rand()%6;
		if(m_gen_number[2]!=m_gen_number[0] && 
		   m_gen_number[2]!=m_gen_number[1])
			break;
	}
	for(;;)
	{
		m_gen_number[3]=rand()%6;
		if(m_gen_number[3]!=m_gen_number[0] && 
		   m_gen_number[3]!=m_gen_number[1] && 
		   m_gen_number[3]!=m_gen_number[2])
			break;
	}
}