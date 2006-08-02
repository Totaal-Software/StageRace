// DlgInsertItemInCommunique.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInsertItemInCommunique dialog


CDlgInsertItemInCommunique::CDlgInsertItemInCommunique(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInsertItemInCommunique::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInsertItemInCommunique)
	m_identifier = _T("");
	m_type = 0;
	//}}AFX_DATA_INIT
}


void CDlgInsertItemInCommunique::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInsertItemInCommunique)
	DDX_Text(pDX, IDC_IDENTIFIER, m_identifier);
	DDX_Radio(pDX, IDC_RADIO1, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInsertItemInCommunique, CDialog)
	//{{AFX_MSG_MAP(CDlgInsertItemInCommunique)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInsertItemInCommunique message handlers
