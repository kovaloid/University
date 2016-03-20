#if !defined(AFX_BULLS_COW_H__CCE018C7_2CF5_44A5_AEEF_1A7CF91A9436__INCLUDED_)
#define AFX_BULLS_COW_H__CCE018C7_2CF5_44A5_AEEF_1A7CF91A9436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CBulls_CowApp : public CWinApp
{
public:		
	CBulls_CowApp();	
	enum { IDD = IDD_PRAVILA};
	public:
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

#endif
