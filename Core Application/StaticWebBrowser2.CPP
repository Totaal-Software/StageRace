// StaticWebBrowser2.cpp: implementation of the CStaticWebBrowser2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CStaticWebBrowser2::PreTranslateMessage(MSG *pMsg)
{
	switch( pMsg->message )
	{
		case WM_SYSKEYDOWN:
			if(pMsg->wParam==VK_F10)
  				return TRUE;
			break;
		case WM_RBUTTONUP:
		case WM_CONTEXTMENU:
			return TRUE;
	}
	return CWebBrowser2::PreTranslateMessage(pMsg);
}
