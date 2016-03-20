// lab9.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Clab9App:
// See lab9.cpp for the implementation of this class
//

class Clab9App : public CWinApp
{
public:
	Clab9App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Clab9App theApp;