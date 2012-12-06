// HelpTool.h : main header file for the HELPTOOL application
//

#if !defined(AFX_HELPTOOL_H__8F6F907A_9E30_4620_9DC9_03BA59AB8ACE__INCLUDED_)
#define AFX_HELPTOOL_H__8F6F907A_9E30_4620_9DC9_03BA59AB8ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelpToolApp:
// See HelpTool.cpp for the implementation of this class
//

void Report(CString str);
class CHelpToolApp : public CWinApp
{
public:
	CHelpToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHelpToolApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPTOOL_H__8F6F907A_9E30_4620_9DC9_03BA59AB8ACE__INCLUDED_)
