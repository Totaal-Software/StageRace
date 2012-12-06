// License.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicense

IMPLEMENT_DYNCREATE(CLicense, CDocument)

CLicense::CLicense()
{
	m_strTitle = LoadStr( IDS_DIV78 );
}

BEGIN_MESSAGE_MAP(CLicense, CDocument)
	//{{AFX_MSG_MAP(CLicense)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
