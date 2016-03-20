// lab11Doc.h : interface of the Clab11Doc class
//


#pragma once


class Clab11Doc : public CDocument
{
protected: // create from serialization only
	Clab11Doc();
	DECLARE_DYNCREATE(Clab11Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Clab11Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


