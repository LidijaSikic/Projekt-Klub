
// Klub.h : main header file for the Klub application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKlubApp:
// See Klub.cpp for the implementation of this class
//

class CKlubApp : public CWinApp
{
public:
	CKlubApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKlubApp theApp;
