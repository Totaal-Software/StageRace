// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define _UNICODE
#define _WIN32_WINNT 0x0500

#if !defined(AFX_STDAFX_H__552C7526_B87F_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_STDAFX_H__552C7526_B87F_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN

// MFC core and standard components
#include <afxwin.h>

// MFC extensions
#include <afxext.h>
#include <afxcview.h>

// Used for WM_KICKIDLE
#include <afxpriv.h>

// HTMLHelp implementation
#include <htmlhelp.h>

#include "afxdlgs.h"
#include "afxinet.h"
#include "afxtempl.h"
#include <afxhtml.h>
#include <math.h>

// DAO database support
#include <afxdao.h>
// MS HTML
#include <MsHTML.h>
// Control identifiers for file dialog
#include <dlgs.h>
// Necessary for OptionsPanel.h
#pragma warning(disable:4786)
#include <vector>

// For PresentationView.h
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <atlbase.h>
#include "MSHTMCID.H"
#include "MSHTMHST.H"
// End for PresentationView.h

// MFC support for Windows Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT
// End MFC support for Windows Common Controls

// For COM server
//	#define _ATL_APARTMENT_THREADED
#define _ATL_FREE_THREADED
	#include <atlbase.h>
	//You may derive a class from CComModule and use it if you want to override
	//something, but do not change the name of _Module
	class CStageRaceModule : public CComModule
	{
	public:
		LONG Unlock();
		LONG Lock();
		DWORD dwThreadID;
	};
	extern CStageRaceModule _Module;
	#include <atlcom.h>
// End for COM server

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__552C7526_B87F_11D2_B376_0040954019F4__INCLUDED_)



