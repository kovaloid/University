// lab5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Clab5App:
// See lab5.cpp for the implementation of this class
//

class Clab5App : public CWinApp
{
public:
	Clab5App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Clab5App theApp;