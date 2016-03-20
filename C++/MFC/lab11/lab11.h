// lab11.h : main header file for the lab11 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Clab11App:
// See lab11.cpp for the implementation of this class
//

class Clab11App : public CWinApp
{
public:
	Clab11App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg BOOL OnIdle(LONG lCount);
	DECLARE_MESSAGE_MAP()
};

extern Clab11App theApp;