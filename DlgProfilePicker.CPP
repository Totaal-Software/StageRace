// DlgProfilePicker.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProfilePicker dialog


CDlgProfilePicker::CDlgProfilePicker(CAllSettings* alls, bool bLock, HANDLE hSemaphore)
	: CStageRaceWnd<CDialog>(CHelp::HLP_UNKNOWN, CDlgProfilePicker::IDD)
{
	m_bLocked = bLock;
	m_bChanged = false;
	m_pAllsettings = alls;
	m_hSemaphore = hSemaphore;
	//{{AFX_DATA_INIT(CDlgProfilePicker)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProfilePicker::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProfilePicker)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProfilePicker, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgProfilePicker)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_REMOVE, OnRemove)
	ON_BN_CLICKED(ID_RENAME, OnRename)
	ON_BN_CLICKED(ID_SETCURRENT, OnSetcurrent)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_ADJUSTFILENAMES, OnAdjustfilenames)
	ON_BN_CLICKED(IDC_USEPROFILENAMES, OnUseprofilenames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProfilePicker message handlers

BOOL CDlgProfilePicker::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	DrawList();

	if( m_bLocked )
	{
		GetDlgItem( ID_ADD )->EnableWindow(false);
		GetDlgItem( ID_REMOVE )->EnableWindow(false);
		GetDlgItem( ID_RENAME )->EnableWindow(false);
		GetDlgItem( IDC_ADJUSTFILENAMES )->EnableWindow(false);
		GetDlgItem( IDC_USEPROFILENAMES )->EnableWindow(false);
	}

	((CListBox*)GetDlgItem(IDC_LIST))->SetCurSel(m_pAllsettings->ProfilesGetCurrent());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProfilePicker::DrawList(int select)
{
	// List
	((CListBox*)GetDlgItem(IDC_LIST))->ResetContent();
	for( int i=0; i<m_pAllsettings->ProfilesGetCount(); i++ )
	{
		if( i==m_pAllsettings->ProfilesGetCurrent() )
			((CListBox*)GetDlgItem(IDC_LIST))->AddString(m_pAllsettings->ProfilesGetName(i) + TEXT("  (") + LoadStr( IDS_DIV93 ) + TEXT(")") );
		else
			((CListBox*)GetDlgItem(IDC_LIST))->AddString(m_pAllsettings->ProfilesGetName(i));
	}
	// Selection in list
	if( select >= 0 )
		((CListBox*)GetDlgItem(IDC_LIST))->SetCurSel(select);

	// Check boxes at bottom
	GetDlgItem( IDC_ADJUSTFILENAMES )->EnableWindow( m_pAllsettings->ProfilesGetCount()>1 );
	GetDlgItem( IDC_USEPROFILENAMES )->EnableWindow( m_pAllsettings->ProfilesGetAdjustFileNames() );
	CheckDlgButton( IDC_ADJUSTFILENAMES, m_pAllsettings->ProfilesGetAdjustFileNames() );
	CheckDlgButton( IDC_USEPROFILENAMES, m_pAllsettings->ProfilesGetUseProfileNames() );
}

void CDlgProfilePicker::OnAdd() 
{
	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	
	WaitForSingleObject(m_hSemaphore,INFINITE);
	
	if( m_pAllsettings->ProfilesAdd() )
	{
		((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.RedrawDoc();

		m_bChanged = true;
		DrawList(i);
	}

	ReleaseSemaphore(m_hSemaphore,1,NULL);
}

void CDlgProfilePicker::OnRename() 
{
	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	if( i!=LB_ERR )
	{
		WaitForSingleObject(m_hSemaphore,INFINITE);

		if( m_pAllsettings->ProfilesRename(i) )
		{
			((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.RedrawDoc();

			m_bChanged = true;
			DrawList(i);
		}

		ReleaseSemaphore(m_hSemaphore,1,NULL);
	}
	else
		MessageBeep(MB_ICONASTERISK);
}

void CDlgProfilePicker::OnRemove() 
{
	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	if( (i!=LB_ERR) && (i!=0) /* 0 is main profile, not to be removed! */ )
	{
		WaitForSingleObject(m_hSemaphore,INFINITE);

		m_pAllsettings->ProfilesRemove(i);

		ReleaseSemaphore(m_hSemaphore,1,NULL);

		((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.RedrawDoc();
		m_bChanged = true;
		DrawList(i);
	}
	else
		MessageBeep(MB_ICONASTERISK);
}

void CDlgProfilePicker::OnSetcurrent() 
{
	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	if( i!=LB_ERR )
	{
		if( i!=m_pAllsettings->ProfilesGetCurrent() )
		{
			WaitForSingleObject(m_hSemaphore,INFINITE);

			m_pAllsettings->ProfilesSetCurrent(i);

			ReleaseSemaphore(m_hSemaphore,1,NULL);

			((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.RedrawDoc();
			m_bChanged = true;
			DrawList(i);
		}
	}
	else
		MessageBeep(MB_ICONASTERISK);
}

void CDlgProfilePicker::OnDblclkList() 
{
	OnSetcurrent();
}

int CDlgProfilePicker::DoModal() 
{
	CStageRaceWnd<CDialog>::DoModal();
	if( m_bChanged )
		return IDOK;
	else
		return IDCANCEL;
}

BOOL CDlgProfilePicker::PreTranslateMessage(MSG* pMsg) 
{
	// Check for [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_RETURN )
	{
		int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
		if( i != m_pAllsettings->ProfilesGetCurrent() )
		{
			OnSetcurrent();
			return TRUE;
		}
	};
	
	return CStageRaceWnd<CDialog>::PreTranslateMessage(pMsg);
}

void CDlgProfilePicker::OnAdjustfilenames() 
{
	bool b = IsDlgButtonChecked( IDC_ADJUSTFILENAMES )>0;

	WaitForSingleObject(m_hSemaphore,INFINITE);
	m_pAllsettings->ProfilesSetAdjustFileNames(b);
	ReleaseSemaphore(m_hSemaphore,1,NULL);

	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	m_bChanged = true;
	DrawList(i);
}

void CDlgProfilePicker::OnUseprofilenames() 
{
	bool b = IsDlgButtonChecked( IDC_USEPROFILENAMES )>0;
	
	WaitForSingleObject(m_hSemaphore,INFINITE);
	m_pAllsettings->ProfilesSetUseProfileNames(b);
	ReleaseSemaphore(m_hSemaphore,1,NULL);

	int i = ((CListBox*)GetDlgItem(IDC_LIST))->GetCurSel();
	m_bChanged = true;
	DrawList(i);
}
