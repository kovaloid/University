// lab11View.h : interface of the Clab11View class
//


#pragma once


class Clab11View : public CFormView
{
protected: // create from serialization only
	Clab11View();
	DECLARE_DYNCREATE(Clab11View)

public:
	enum{ IDD = IDD_LAB11_FORM };

// Attributes
public:
	Clab11Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~Clab11View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_EnableTask1Check;
	BOOL m_EnableTask2Check;
	BOOL m_EnableTask3Check;
	long m_Task1Edit;
	long m_Task2Edit;
	long m_Task3Edit;
};

#ifndef _DEBUG  // debug version in lab11View.cpp
inline Clab11Doc* Clab11View::GetDocument() const
   { return reinterpret_cast<Clab11Doc*>(m_pDocument); }
#endif

