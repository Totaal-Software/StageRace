// DlgNewParagraphTitle.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewParagraphTitle dialog


CDlgNewParagraphTitle::CDlgNewParagraphTitle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewParagraphTitle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewParagraphTitle)
	m_title = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNewParagraphTitle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewParagraphTitle)
	DDX_Text(pDX, IDC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewParagraphTitle, CDialog)
	//{{AFX_MSG_MAP(CDlgNewParagraphTitle)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewParagraphTitle message handlers
