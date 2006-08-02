// MsgBoxHardwareKey.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxHardwareKey dialog


CMsgBoxHardwareKey::CMsgBoxHardwareKey()
	: CDialog(CMsgBoxHardwareKey::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMsgBoxHardwareKey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CMsgBoxHardwareKey, CDialog)
	//{{AFX_MSG_MAP(CMsgBoxHardwareKey)
	ON_BN_CLICKED(IDC_HELP_OK, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxHardwareKey message handlers

BOOL CMsgBoxHardwareKey::Create(CWnd* pParent)
{
	return CDialog::Create( IDD_MSGBOX_HARDWAREKEY, pParent );
}

void CMsgBoxHardwareKey::OnHelp() 
{
	((CStartScreen*)GetParent())->OnOK();
//	OnOK();
//	OnOK not necessary, as this dialog will
//	disappear when its parent is destroyed
	CHelp::Topic( CHelp::HLP_DLG_HARDWAREKEY );
}
