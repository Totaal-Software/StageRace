// PageSettings.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettings property page

CPageSettings::CPageSettings(CHelp::HELP_TOPIC helptopic, UINT nID) : CStageRaceWnd<cdxCDynamicPropPage>(helptopic,nID,(UINT)0)
{
	m_bBinariesMaximized = false;
	//{{AFX_DATA_INIT(CPageSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CPageSettings::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<cdxCDynamicPropPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettings)
	DDX_Control(pDX, IDC_SETTINGS_BINARYSETTINGS, m_ctrlBinarySettings);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageSettings, CStageRaceWnd<cdxCDynamicPropPage>)
	//{{AFX_MSG_MAP(CPageSettings)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(OPN_SELCHANGE,IDC_SETTINGS_BINARYSETTINGS,OnSettingsBinarysettingsSelChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettings message handlers

BOOL CALLBACK EnumChildProc1(HWND hwnd, LPARAM lParam)
{
	if( ((CPageSettings*)lParam)->Get() != hwnd )
		((CPageSettings*)lParam)->Add( hwnd );
	return TRUE;
}

BOOL CALLBACK EnumChildProc2(HWND hwnd, LPARAM lParam)
{
	if( (((CPageSettings*)lParam)->Get() != hwnd)
		&& (::GetParent( hwnd )==((CPageSettings*)lParam)->m_hWnd) )
		::ShowWindow( hwnd,
			((CPageSettings*)lParam)->GetBinariesMaximized()?
				SW_SHOW:SW_HIDE );
	return TRUE;
}

BOOL CPageSettings::OnInitDialog() 
{
	CStageRaceWnd<cdxCDynamicPropPage>::OnInitDialog();
	ArrangeEnabling();

	// Make an image list
	// Note that it can be temporarely
	CImageList list;
	list.Create( IDB_SETTINGS_TOPICS, 18, 1, RGB(255,0,255) );
	m_ctrlBinarySettings.SetImageList(list);

	// Some arrays which help keeping track of inserted groups
	CArray<UINT,UINT&> done;
	CMap<UINT,UINT&,int,int&> mapdone;

	// Insert items
	for( int i=0; i<m_pSettings->ValuesSize(); i++ )
	{
		const CSettings::CSetting* pSet;
		m_pSettings->ValueGetAt( i, &pSet );

		Connect(done,mapdone,pSet->m_nGroupID);
		switch( pSet->m_type )
		{
			case CSettings::CSetting::SINGLEOPTION:
				m_ctrlBinarySettings.AddCheck( pSet->m_nID, pSet->m_bValue?CSettingsPanel::itemChecked:0, done.GetSize() );
				break;
			case CSettings::CSetting::MULTIOPTION:
				m_ctrlBinarySettings.AddRadio( pSet->m_nID, pSet->m_bValue?CSettingsPanel::itemChecked:0, done.GetSize() );
				break;
		}
	}
	
	// Make resizable
	AddSzControl( IDC_SETTINGS_BINARYSETTINGS, mdResize, mdResize);

	EnumChildWindows(
		m_hWnd, // handle to parent window
		&EnumChildProc1, // pointer to callback function
		(LPARAM)this // application-defined value
	);

	if( m_bBinariesMaximized )
		ToggleBigBinaries();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettings::Connect(CArray<UINT,UINT&>& done, CMap<UINT,UINT&,int,int&>& mapdone, UINT nGroupID)
{
	if( !nGroupID )
	{
		done.RemoveAll();
		mapdone.RemoveAll();
		return;
	}
	// Only do this if the required group is not already connected to
	if( !done.GetSize()
		|| (nGroupID != done.GetAt(done.GetSize()-1)) )
	{
		// Search for the required group in the group path
		// that we are currently connected to
		UINT nSearch = nGroupID;
		int nIndex = 0;
		while( nSearch && !mapdone.Lookup( nSearch, nIndex ) )
		{
			// If the required group can not be found in the
			// current group path, we look if there is a parent
			// group for the required group that does exist
			// in the current group path
			const CSettings::CSetting* pSet;
			m_pSettings->ValueGet( nSearch, &pSet );
			nSearch = pSet->m_nGroupID;
		}

		// Remove wasted elements from the map
		int c=0;
		for( int i=0; i<(done.GetSize()-1-nIndex); i++ )
		{
			c++;	// Count the number of items that are removed
					// at the end
			UINT n = done.GetAt(done.GetSize()-1-i);
			mapdone.RemoveKey( n );
		}
		// Remove from the array
		done.SetSize( done.GetSize()-c );

		// If the above code does not already connect to the right
		// group and there is ly a group required, we add it
		if( (!done.GetSize()
			|| (nGroupID != done.GetAt(done.GetSize()-1)) )
			&& nGroupID )
		{
			int i = done.Add( nGroupID );
			mapdone.SetAt( nGroupID, i );
			m_ctrlBinarySettings.AddGroup( nGroupID, CSettingsPanel::itemBold, done.GetSize()-1, m_pSettings->IconGet( nGroupID ) );
		}
	}
}

void CPageSettings::OnSettingsBinarysettingsSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMOPTIONSPANEL *pInfo=(NMOPTIONSPANEL *)pNMHDR;
	m_pSettings->ValueSet( pInfo->idButton, pInfo->bSelected>0 );
	ArrangeEnabling();
}

CPageSettings::~CPageSettings()
{
	delete m_pSettings;
}

void CPageSettings::Add(HWND hwnd)
{
	AddSzControl( hwnd, mdNone, mdRepos);
}

HWND CPageSettings::Get()
{
	return m_ctrlBinarySettings.m_hWnd;
}

void CPageSettings::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Maximize the binaries after hiding all other dialog items

	ToggleBigBinaries();
	CStageRaceWnd<cdxCDynamicPropPage>::OnLButtonDblClk(nFlags, point);
}

bool CPageSettings::GetBinariesMaximized()
{
	return m_bBinariesMaximized;
}

void CPageSettings::OnSize(UINT nType, int cx, int cy) 
{
	if( m_bBinariesMaximized )
		OnLButtonDblClk(0,0);
	CStageRaceWnd<cdxCDynamicPropPage>::OnSize(nType, cx, cy);
}

void CPageSettings::ToggleBigBinaries()
{
	// Only allow this behaviour when there isn't very little
	// content in the binaries box anyway
	if( m_ctrlBinarySettings.IsScroll()
		|| m_bBinariesMaximized )
	{
		EnumChildWindows(
			m_hWnd, // handle to parent window
			&EnumChildProc2, // pointer to callback function
			(LPARAM)this // application-defined value
		);
		m_bBinariesMaximized = !m_bBinariesMaximized;
		m_ctrlBinarySettings.ShowWindow( m_bBinariesMaximized?SW_MAXIMIZE:SW_RESTORE );
	}
}
