// StaticPresentationView.cpp: implementation of the CStaticPresentationView class.
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

IMPLEMENT_DYNCREATE( CStaticPresentationView, CPresentationView )

HRESULT CStaticPresentationView::ShowContextMenu(unsigned long dwID, tagPOINT *ppt, IUnknown *pcmdtReserved, IDispatch *)
{
	return S_OK;
}
