// srspeed.h : main header file for the SRSPEED application
//

#if !defined(AFX_SRSPEED_H__96A09624_3E1C_11D4_92E2_0040954019F4__INCLUDED_)
#define AFX_SRSPEED_H__96A09624_3E1C_11D4_92E2_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSrspeedApp:
// See srspeed.cpp for the implementation of this class
//

class CSrspeedApp : public CWinApp
{
public:
	CSrspeedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrspeedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSrspeedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSPEED_H__96A09624_3E1C_11D4_92E2_0040954019F4__INCLUDED_)
