// lab11Doc.cpp : implementation of the Clab11Doc class
//

#include "stdafx.h"
#include "lab11.h"

#include "lab11Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab11Doc

IMPLEMENT_DYNCREATE(Clab11Doc, CDocument)

BEGIN_MESSAGE_MAP(Clab11Doc, CDocument)
END_MESSAGE_MAP()


// Clab11Doc construction/destruction

Clab11Doc::Clab11Doc()
{
	// TODO: add one-time construction code here

}

Clab11Doc::~Clab11Doc()
{
}

BOOL Clab11Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Clab11Doc serialization

void Clab11Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Clab11Doc diagnostics

#ifdef _DEBUG
void Clab11Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Clab11Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Clab11Doc commands
