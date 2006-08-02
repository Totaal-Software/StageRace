// EditCommunique.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCommunique dialog


CEditCommunique::CEditCommunique(const CStageRaceDoc* pDoc)
: CStageRaceWnd<cdxCDynamicDialog>(CHelp::HLP_DLG_LSTP_COMM, CEditCommunique::IDD)
{
	ActivateAutoPos("Communiqué");
	m_pDoc = pDoc;
	m_pPreviewWnd = NULL;
	m_nFS = 0;
	m_nHS = 0;
	m_bChanged = false;
	//{{AFX_DATA_INIT(CEditCommunique)
	m_contents = _T("");
	m_title = _T("");
	m_date = _T("");
	//}}AFX_DATA_INIT
}

void CEditCommunique::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<cdxCDynamicDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditCommunique)
	DDX_Text(pDX, IDC_CONTENTS, m_contents);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Text(pDX, IDC_DATE, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditCommunique, CStageRaceWnd<cdxCDynamicDialog>)
	//{{AFX_MSG_MAP(CEditCommunique)
	ON_EN_CHANGE(IDC_TITLE, OnChange)
	ON_COMMAND(ID_VIEW_PREVIEW, OnViewPreview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEW, OnUpdateViewPreview)
	ON_COMMAND(ID_INSERT_ORDERTEAMCAPTAINVEHICLES_ONGENERALCLASSIFICATION, OnInsertOrderteamcaptainvehiclesOngeneralclassification)
	ON_UPDATE_COMMAND_UI(ID_INSERT_ORDERTEAMCAPTAINVEHICLES_ONGENERALCLASSIFICATION, OnUpdateInsertOrderteamcaptainvehiclesOngeneralclassification)
	ON_COMMAND(ID_INSERT_ORDERTEAMCAPTAINVEHICLES_ONSTAGECLASSIFICATION, OnInsertOrderteamcaptainvehiclesOnstageclassification)
	ON_UPDATE_COMMAND_UI(ID_INSERT_ORDERTEAMCAPTAINVEHICLES_ONSTAGECLASSIFICATION, OnUpdateInsertOrderteamcaptainvehiclesOnstageclassification)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_INSERT_PAGEBREAK, OnInsertPagebreak)
	ON_COMMAND(ID_INSERT_ITEM, OnInsertItem)
	ON_COMMAND(ID_EDIT_APPLYSTYLETOSELECTION_BOLD, OnEditApplystyletoselectionBold)
	ON_COMMAND(ID_EDIT_APPLYSTYLETOSELECTION_ITALIC, OnEditApplystyletoselectionItalic)
	ON_COMMAND(ID_EDIT_APPLYSTYLETOSELECTION_UNDERLINED, OnEditApplystyletoselectionUnderlined)
	ON_UPDATE_COMMAND_UI(ID_EDIT_APPLYSTYLETOSELECTION_UNDERLINED, OnUpdateEditApplystyletoselection)
	ON_EN_CHANGE(IDC_CONTENTS, OnChange)
	ON_EN_CHANGE(IDC_DATE, OnChange)
	ON_UPDATE_COMMAND_UI(ID_EDIT_APPLYSTYLETOSELECTION_ITALIC, OnUpdateEditApplystyletoselection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_APPLYSTYLETOSELECTION_BOLD, OnUpdateEditApplystyletoselection)
	ON_COMMAND(ID_INSERT_PARAGRAPHTITLE, OnInsertParagraphtitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ARRANGE THE MENUS TO WORK PROPERLY
// (UI UPDATE NOTIFICATION IS NOT SENT BY DEFAULT)

void CEditCommunique::UpdateMenu(CMenu * pSubMenu)
{
	// Update the menu items of the menu pointed to
	CCmdUI cmdUI;
	cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
	for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
	{
		cmdUI.m_nIndex = i;
		cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
		cmdUI.m_pMenu = pSubMenu;
		cmdUI.DoUpdate(this, FALSE);
	}
}

void CEditCommunique::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	// Get the menu that is being opened and update the items
	UpdateMenu( pPopupMenu );
}

/////////////////////////////////////////////////////////////////////////////
// MAKE SURE THE THING DOES SOME CHECKING ON EXIT

void CEditCommunique::OnCancel()
{
	if( m_bChanged )
	{
		// If something changed, we only exit if
		// the user wants to discard the changes
		if( MessageBox( LoadStr( IDS_MBT_60 ), LoadStr( IDS_MBC_60 ), MB_YESNO|MB_DEFBUTTON2 )==IDNO )
			return;
	}
	CStageRaceWnd<cdxCDynamicDialog>::OnCancel();
}

void CEditCommunique::OnOK() 
{
	CString userInput;
	
	// Check title
	GetDlgItem( IDC_TITLE )->GetWindowText( userInput );
	userInput.Remove( ' ' );
	if( !userInput.GetLength() )
	{
		MessageBeep( MB_ICONASTERISK );
		return;
	}

	// Check contents
	GetDlgItem( IDC_CONTENTS )->GetWindowText( userInput );
	userInput.Remove( ' ' );
	if( !userInput.GetLength() )
	{
		MessageBeep( MB_ICONASTERISK );
		return;
	}

	// If both exist we proceed with OK, otherwise we already left
	CStageRaceWnd<cdxCDynamicDialog>::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CEditCommunique message handlers

CEditCommunique& CEditCommunique::operator =(const CCommunique &aComm)
{
	this->m_date		= aComm.m_date;
	this->m_title		= aComm.m_title;
	this->m_contents	= aComm.m_contents;
	return *this;
}

BOOL CEditCommunique::OnInitDialog() 
{
	CStageRaceWnd<cdxCDynamicDialog>::OnInitDialog();

   // Set a nice font to the contents area
   m_contentsfont.CreateFont( 15, 0, 0, 0, 0, false, false, NULL, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("Arial"));
   GetDlgItem( IDC_CONTENTS )->SetFont(&m_contentsfont);

	// Control sizing
	AddSzControl(IDC_TITLE,mdRelativeResize,mdNone);
	AddSzControl(IDC_STATICDATE,mdRelativeRepos,mdNone);
	AddSzControl(IDC_DATE,mdRelativeRepos,mdNone);
	AddSzControl(IDC_CONTENTS,mdResize,mdResize);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditCommunique::InsertOrderTeamVehicles(BOOL bGeneral)
{
	CClassification* pClass = NULL;
	
	pClass = ((CStageRaceDoc*)m_pDoc)->GenerateUpTo( m_nFS, m_nHS );
	if( pClass ) // Just to be sure
	{
		// Make a list of teams
		CList<CTeam*, CTeam*> objTeamsList;

		// Select a list of arrivals based on the functions parameter
		CList<CArrival,CArrival&>* pList = NULL;
		if( !bGeneral )
			pList = &pClass->m_classification;
		else
			pList = &pClass->m_generalClassification;

		// Iterate the whole list of arrivals
		POSITION nPos;
		nPos = pList->GetHeadPosition();
		while( nPos )
		{
			CArrival objArr = pList->GetNext( nPos );
			CCompetitor objComp;
			objComp = m_pDoc->CompetitorsGet( objArr.m_staNo );
			
			// Check for every arrival whether its team
			// already exists in our list of teams
			bool bFound = false;
			// To do so, iterate the whole teams list
			POSITION nPosTeams = objTeamsList.GetHeadPosition();
			while( nPosTeams && !bFound )
			{
				if( objComp.m_pTeam ==
						objTeamsList.GetNext( nPosTeams ) )
					bFound = true;
			}
			// If it doesn't exist, we add it
			if( !bFound )
				objTeamsList.AddTail( objComp.m_pTeam );
		}
		delete pClass;

		// Set up the string to insert
		CString cList;
		cList += "\r\n";
		cList += AssembleStr( TEXT("TeamCapOrder"), TEXT("\r\n"), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		cList += "\r\n";
		cList += "\r\n";
		cList += "<OL>\r\n";
		nPos = objTeamsList.GetHeadPosition();
		while( nPos )
		{
			CTeam* pTeam = objTeamsList.GetNext( nPos );
			cList += "   <LI>";
			cList += pTeam->m_name;
			cList += "\r\n";
		}
		cList += "</OL>\r\n";
		cList += "\r\n";
		// Actually insert the text
		((CEdit*)GetDlgItem( IDC_CONTENTS ))->ReplaceSel( cList, TRUE );
	}
}

void CEditCommunique::UpdatePreview()
{
	if( m_pPreviewWnd )
	{
		// Compose a communiqué with the contents of this dialog
		CCommunique comm;
		GetDlgItemText( IDC_CONTENTS, comm.m_contents );
		GetDlgItemText( IDC_DATE, comm.m_date );
		GetDlgItemText( IDC_TITLE, comm.m_title );
		// Send the communiqué's contents to the preview window
		m_pPreviewWnd->SetContents( &comm );
	}
}

CEditCommunique::~CEditCommunique()
{
	if( m_pPreviewWnd )
	{
		// Remove the preview window
		delete m_pPreviewWnd;
		m_pPreviewWnd = NULL;
	}
}

void CEditCommunique::OnChange() 
{
	m_bChanged = true;
	UpdatePreview();
}

void CEditCommunique::OnViewPreview() 
{
	// Make a new preview window when not yet created
	if( !m_pPreviewWnd )
		m_pPreviewWnd = new CPreviewCommunique(this,m_pDoc);
	// Make it visible
	m_pPreviewWnd->ShowWindow(m_pPreviewWnd->IsWindowVisible()?SW_HIDE:SW_SHOW);
	SetFocus();
	UpdatePreview();
}

void CEditCommunique::OnUpdateViewPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_pPreviewWnd && m_pPreviewWnd->IsWindowVisible() );
}

void CEditCommunique::OnInsertOrderteamcaptainvehiclesOngeneralclassification() 
{
	InsertOrderTeamVehicles( TRUE );
}

void CEditCommunique::OnUpdateInsertOrderteamcaptainvehiclesOngeneralclassification(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nHS>0 );	
}

void CEditCommunique::OnInsertOrderteamcaptainvehiclesOnstageclassification() 
{
	InsertOrderTeamVehicles( FALSE );
}

void CEditCommunique::OnUpdateInsertOrderteamcaptainvehiclesOnstageclassification(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nHS>0 );	
}

void CEditCommunique::OnInsertPagebreak() 
{
	// Actually insert the text
	((CEdit*)GetDlgItem( IDC_CONTENTS ))->ReplaceSel( TEXT("\r\n{pagebreak}\r\n"), TRUE );
}

void CEditCommunique::OnInsertItem() 
{
	// Let the user choose and enter some item
	CDlgInsertItemInCommunique dlg;
	if( dlg.DoModal()==IDOK )
	{
		// Check if actually something entered
		if( dlg.m_identifier.GetLength() && (dlg.m_identifier!=TEXT("0")) )
		{
			CString temp;
			// See what is entered and compose an appropriate string
			switch( dlg.m_type )
			{
				case 0:
					temp.Format( TEXT("{comp, %s}"), dlg.m_identifier );
					break;
				case 1:
					temp.Format( TEXT("{team, %s}"), dlg.m_identifier );
					break;
				case 2:
					temp.Format( TEXT("{captain, %s}"), dlg.m_identifier );
					break;
			}
			// Actually insert the text
			// The text is a tag that CHtmlDoc recognizes
			((CEdit*)GetDlgItem( IDC_CONTENTS ))->ReplaceSel( temp, TRUE );
		}
		else
			MessageBeep( MB_ICONASTERISK );
	}
}

void CEditCommunique::OnInsertParagraphtitle() 
{
	// Let the user enter a new paragraph title
	CDlgNewParagraphTitle dlg;
	if( dlg.DoModal()==IDOK )
	{
		// Check if actually something entered
		if( dlg.m_title.GetLength() )
			// Actually insert the text
			// This is emphasized (EM) text
			((CEdit*)GetDlgItem( IDC_CONTENTS ))->ReplaceSel( TEXT("\r\n\r\n<EM>")+dlg.m_title+TEXT("</EM>\r\n\r\n"), TRUE );
		else
			MessageBeep( MB_ICONASTERISK );
	}
}

void CEditCommunique::OnEditApplystyletoselectionBold() 
{
	// See what is selected
	int nStartChar, nEndChar;
	((CEdit*)GetDlgItem(IDC_CONTENTS))->GetSel( nStartChar, nEndChar );

	// Tag selection
	CString c;
	GetDlgItemText(IDC_CONTENTS, c);
	c = c.Left( nStartChar ) + TEXT("<B>") + c.Mid( nStartChar, nEndChar-nStartChar ) + TEXT("</B>") + c.Mid( nEndChar );

	SetDlgItemText(IDC_CONTENTS, c);

	((CEdit*)GetDlgItem(IDC_CONTENTS))->SetSel( nEndChar+7, nEndChar+7 );

	OnChange();
}

void CEditCommunique::OnEditApplystyletoselectionItalic() 
{
	// See what is selected
	int nStartChar, nEndChar;
	((CEdit*)GetDlgItem(IDC_CONTENTS))->GetSel( nStartChar, nEndChar );

	// Tag selection
	CString c;
	GetDlgItemText(IDC_CONTENTS, c);
	c = c.Left( nStartChar ) + TEXT("<I>") + c.Mid( nStartChar, nEndChar-nStartChar ) + TEXT("</I>") + c.Mid( nEndChar );

	SetDlgItemText(IDC_CONTENTS, c);

	((CEdit*)GetDlgItem(IDC_CONTENTS))->SetSel( nEndChar+7, nEndChar+7 );

	OnChange();
}

void CEditCommunique::OnEditApplystyletoselectionUnderlined() 
{
	// See what is selected
	int nStartChar, nEndChar;
	((CEdit*)GetDlgItem(IDC_CONTENTS))->GetSel( nStartChar, nEndChar );

	// Tag selection
	CString c;
	GetDlgItemText(IDC_CONTENTS, c);
	c = c.Left( nStartChar ) + TEXT("<U>") + c.Mid( nStartChar, nEndChar-nStartChar ) + TEXT("</U>") + c.Mid( nEndChar );

	SetDlgItemText(IDC_CONTENTS, c);

	((CEdit*)GetDlgItem(IDC_CONTENTS))->SetSel( nEndChar+7, nEndChar+7 );

	OnChange();
}

void CEditCommunique::OnUpdateEditApplystyletoselection(CCmdUI* pCmdUI) 
{
	int nStartChar, nEndChar;
	((CEdit*)GetDlgItem(IDC_CONTENTS))->GetSel( nStartChar, nEndChar );
	// Only enable if something selected
	pCmdUI->Enable( nStartChar!=nEndChar );
}
