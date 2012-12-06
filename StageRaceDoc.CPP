///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// PrimobjAry author: Sander Verhagen
// PrimobjAry date: 01-01-2000
// Filename: StageRaceDoc.cpp
// Description: Implementation file for the CStageRaceDoc class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
// 06-01-2000	SV	Alle variabelenamen aangepast volgens nieuwe conventie
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRaceDoc

IMPLEMENT_DYNCREATE( CStageRaceDoc, CDocument )

BEGIN_MESSAGE_MAP( CStageRaceDoc, CDocument )
	//{{AFX_MSG_MAP(CStageRaceDoc)
	ON_COMMAND(ID_FILE_UPLOAD, OnFileUpload)
	ON_UPDATE_COMMAND_UI(ID_FILE_UPLOAD, OnUpdateFileUpload)
	ON_COMMAND(ID_TOOLS_EXPORTSCANOVISION, OnToolsExportscanovision)
	ON_COMMAND(ID_TOOLS_EXPORTFINISHLYNX, OnToolsExportfinishlynx)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EXPORTSCANOVISION, OnUpdateToolsExportscanovision)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EXPORTFINISHLYNX, OnUpdateToolsExportfinishlynx)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_TOC, OnUpdateGenerateToc)
	ON_COMMAND(ID_VIEW_EVENTITEMSELECTION, OnViewEventItemSelection)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EVENTITEMSELECTION, OnUpdateViewEventItemSelection)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_AUTOMATICALLY, OnUpdateGenerateAutomatically)
	ON_COMMAND(ID_GENERATE_CROSSOUT, OnGenerateCrossout)
	ON_COMMAND(ID_GENERATE_SIGNIN, OnGenerateSignin)
	ON_COMMAND(ID_GENERATE_COMMUNIQUES, OnGenerateCommuniques)
	ON_COMMAND(ID_GENERATE_AUTOMATICALLY, OnGenerateAutomatically)
	ON_COMMAND(ID_GENERATE_ALL, OnGenerateAll)
	ON_COMMAND(ID_GENERATE_TOC, OnGenerateToc)
	ON_COMMAND(ID_GENERATE_ALLSTAGES, OnGenerateAllstages)
	ON_COMMAND(ID_GENERATE_COMPETITORS, OnGenerateCompetitors)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_ALL_BONUSES, OnUpdateConfigureAll)
	ON_COMMAND(ID_CONFIGURE_ALL_BONUSES, OnConfigureAllBonuses)
	ON_COMMAND(ID_CONFIGURE_ALL_CLIMBCL, OnConfigureAllClimbcl)
	ON_COMMAND(ID_CONFIGURE_ALL_HALFSTAGE, OnConfigureAllHalfstage)
	ON_COMMAND(ID_CONFIGURE_ALL_POINTSCL, OnConfigureAllPointscl)
	ON_COMMAND(ID_CONFIGURE_ALL_SPRINTCL, OnConfigureAllSprintcl)
	ON_COMMAND(ID_CONFIGURE_PROFILEPICKER, OnConfigureProfilepicker)
	ON_COMMAND(ID_VIEW_MONITORMODE, OnViewMonitormode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MONITORMODE, OnUpdateViewMonitormode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ADDFILETOMONITOR, OnUpdateViewAddfiletomonitor)
	ON_COMMAND(ID_VIEW_ADDFILETOMONITOR, OnViewAddfiletomonitor)
	ON_COMMAND(ID_TOOLS_SERVER_PROCESSPENDING, OnToolsServerProcesspending)
	ON_COMMAND(ID_TOOLS_SERVER_SENDTEAMS_CODE, OnToolsServerSendteamsCode)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SERVER_SENDTEAMS_CODE, OnUpdateToolsServerSendteamsCode)
	ON_COMMAND(ID_TOOLS_SERVER_SENDTEAMS_NAME, OnToolsServerSendteamsName)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SERVER_SENDTEAMS_NAME, OnUpdateToolsServerSendteamsName)
	ON_COMMAND(ID_EDIT_AUTONUMBER, OnEditAutonumber)
	ON_COMMAND(ID_CONFIGURE_ALL_MOSTAGGRESSIVECL, OnConfigureAllMostaggressivecl)
	ON_COMMAND(ID_CONFIGURE_SETTINGS, Settings)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_ALL_CLIMBCL, OnUpdateConfigureAll)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_ALL_HALFSTAGE, OnUpdateConfigureAll)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_ALL_POINTSCL, OnUpdateConfigureAll)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_ALL_SPRINTCL, OnUpdateConfigureAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_AUTONUMBER, OnUpdateEditAutonumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageRaceDoc construction/destruction

CStageRaceDoc::CStageRaceDoc()
{
	m_hGenerateSemaphore_ChangeToDoc				= CreateSemaphore(NULL, 1, 1, NULL);
	m_hGenerateSemaphore_KeepDocOpen				= CreateSemaphore(NULL, 1, 1, NULL);

	m_IndexTocFlag									= false;
	m_bGenerateAutomatically						= true;
	m_pEventItemSelection							= NULL;

	m_nFileVersion									= GetHardcodedFileVersion();

	m_pListID = (CIdUseList*)malloc(sizeof( CIdUseList ));
	m_pListID->CIdUseList::CIdUseList( this );

	m_bMonitorMode									= false;
	m_pMonitor										= NULL;

	m_references									= 0;
	m_bLongTeamNamesForCOM							= true;
}

CStageRaceDoc::~CStageRaceDoc()
{
	m_pListID->CIdUseList::~CIdUseList();
	free( m_pListID );

	POSITION nPos;
	// Remove teams
	nPos = m_teams.GetStartPosition();
	while( nPos )
	{
		CString czKey;
		CTeam* pTeam;
		m_teams.GetNextAssoc( nPos, czKey, pTeam );
		delete pTeam;
	}
	m_teams.RemoveAll();
	// Remove spare competitors
	nPos = m_spareCompetitors.GetStartPosition();
	while( nPos )
	{
		CCompetitor* pComp;
		m_spareCompetitors.GetNextAssoc( nPos, (void*&)pComp, (void*&)pComp );
		delete pComp;
	}
	m_spareCompetitors.RemoveAll();

	if( m_pEventItemSelection )
	{
		m_pEventItemSelection->DestroyWindow();
		delete m_pEventItemSelection;
		m_pEventItemSelection = NULL;
	}

	// Remove monitor thread
	if( m_bMonitorMode )
	{
		m_bMonitorMode = false;
		SetMonitor();
	}

	CloseHandle( m_hGenerateSemaphore_ChangeToDoc );
	CloseHandle( m_hGenerateSemaphore_KeepDocOpen );
}

BOOL CStageRaceDoc::OnNewDocument()
{
	// The new document is being created
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Try to make the user to save the document
	if( !((CStageRaceApp*)AfxGetApp())->m_key.CheckDongle() )
		OnFileSave();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStageRaceDoc serialization

int CStageRaceDoc::GetHardcodedFileVersion() const
{
	// Compose it from the current program version with
	// one following digit
	return 3123;
}

void CStageRaceDoc::Serialize(CArchive& objAr)
{
	CObject::Serialize(objAr);
	objAr.m_pDocument = (CDocument*) &(this->m_nFileVersion);

	if ( objAr.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////

		POSITION hPos;
		// The one and only version number for the current schema we're using
			objAr << (m_nFileVersion=GetHardcodedFileVersion());

		// Top level communique
			m_communique.Serialize(objAr);

		// Teams list
			m_teams.Serialize(objAr);
			m_idTeams.Serialize(objAr);

		// Competitors list
			m_competitors.Serialize(objAr);
			objAr << m_spareCompetitors.GetCount();
			hPos = m_spareCompetitors.GetStartPosition();
			while( hPos )
			{
				CCompetitor* pComp;
				m_spareCompetitors.GetNextAssoc(hPos, (void*&)pComp, (void*&)pComp);
				pComp->Serialize(objAr);
			}
			m_idCompetitors.Serialize(objAr);

		// Full stages
			objAr << m_fullStages.GetCount();

			for( int i = 1 ; i <= m_fullStages.GetCount() ; i++ )
			{
				StagesGet( i )->Serialize(objAr);
			}

		// Settings
			m_allsettings.Serialize( objAr );
			objAr << (char)m_bGenerateAutomatically;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////

		// First thing to get from the archive is the version no.
		objAr >> m_nFileVersion;

		// Detect if this is a legal version no.
		if( (m_nFileVersion > GetHardcodedFileVersion()) ||
			(m_nFileVersion < /*first ver with this scheme*/ 1070) )
		{
			// If the version no. is illegal, we abort the opening
			objAr.Abort();
			return;
		}

		// FILE STRUCTURE AVAILABLE SINCE 3.00
		if( m_nFileVersion >= 3000 )
		{
				int nCount;
				// Top level communique
					m_communique.Serialize(objAr);

				// Teams list
					m_teams.Serialize(objAr);
					m_idTeams.Serialize(objAr);

				// Competitors list
					m_competitors.Serialize(objAr);

					objAr >> nCount;

					CCompetitor* pComp;
					while( nCount-- )
					{
						pComp = new CCompetitor;
						pComp->Serialize(objAr);
						m_spareCompetitors.SetAt(pComp, pComp);
					}
					
					m_idCompetitors.Serialize(objAr);
				// Full stages
					objAr >> nCount;

					CFullStage objFullStage;
					while( nCount-- )
					{
						StagesFullNew( &objFullStage );
						m_fullStages.GetAt( m_fullStages.GetTailPosition() ).Serialize(objAr);
					}

				// Settings
					m_allsettings.Serialize( objAr );
					char temp;
					objAr >> temp;
					m_bGenerateAutomatically = (temp!=0);
		}
		else
		{	// FILE STRUCTURE AVAILABLE SINCE 2.00
			if( m_nFileVersion >= 2000 )
			{
				int nCount;
				// Top level communique
					m_communique.Serialize(objAr);

				// Teams list
					m_teams.Serialize(objAr);
					m_idTeams.Serialize(objAr);

				// Competitors list
					m_competitors.Serialize(objAr);

					objAr >> nCount;

					CCompetitor* pComp;
					while( nCount-- )
					{
						pComp = new CCompetitor;
						pComp->Serialize(objAr);
						m_spareCompetitors.SetAt(pComp, pComp);
					}
					
					m_idCompetitors.Serialize(objAr);
				// Full stages
					objAr >> nCount;

					CFullStage objFullStage;
					while( nCount-- )
					{
						StagesFullNew( &objFullStage );
						m_fullStages.GetAt( m_fullStages.GetTailPosition() ).Serialize(objAr);
					}

				// Settings
					m_allsettings.Serialize( objAr );
					char temp;
					objAr >> temp;
					m_bGenerateAutomatically = (temp!=0);
			}
			else
			{ // FILE STRUCTURE AVAILABLE SINCE 1.20
				if( m_nFileVersion >= 1200 )
				{
					int nCount;
					// Top level communique
						m_communique.Serialize(objAr);

					// Teams list
						m_teams.Serialize(objAr);
						m_idTeams.Serialize(objAr);

					// Competitors list
						m_competitors.Serialize(objAr);
						m_idCompetitors.Serialize(objAr);
					// Full stages
						objAr >> nCount;

						CFullStage objFullStage;
						while( nCount-- )
						{
							StagesFullNew( &objFullStage );
							m_fullStages.GetAt( m_fullStages.GetTailPosition() ).Serialize(objAr);
						}

					// Settings
						m_allsettings.Serialize( objAr );
				}
				else
				{ // FILE STRUCTURE AVAILABLE SINCE 1.12
					if( m_nFileVersion >= 1120 )
					{
						int nCount;
						// Top level communique
							m_communique.Serialize(objAr);

						// Teams list
							m_teams.Serialize(objAr);
							m_idTeams.Serialize(objAr);

						// Competitors list
							m_competitors.Serialize(objAr);
							m_idCompetitors.Serialize(objAr);

						// Full stages
							objAr >> nCount;

							CFullStage objFullStage;
							while( nCount-- )
							{
								StagesFullNew( &objFullStage );
								m_fullStages.GetAt( m_fullStages.GetTailPosition() ).Serialize(objAr);
							}

						// Settings
							m_allsettings.Serialize( objAr );
					}
					else
					{
						if( m_nFileVersion >= 1070 )
						{ // FILE STRUCTURE AVAILABLE SINCE 1.07
							int nCount;
							// Top level communique
								m_communique.Serialize(objAr);

							// Teams list
								m_teams.Serialize(objAr);
								m_idTeams.Serialize(objAr);

							// Competitors list
								m_competitors.Serialize(objAr);
								m_idCompetitors.Serialize(objAr);

							// Full stages
								objAr >> nCount;

								CFullStage objFullStage;
								while( nCount-- )
								{
									StagesFullNew( &objFullStage );
									m_fullStages.GetAt( m_fullStages.GetTailPosition() ).Serialize(objAr);
								}

							// Settings
								m_allsettings.Serialize( objAr );
						}
						// The file structure of 1.06 and before is not retreived since it does
						// not support our own file version numbering scheme
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStageRaceDoc diagnostics

#ifdef _DEBUG
void CStageRaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStageRaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStageRaceDoc commands

BOOL CStageRaceDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if ( ((CStageRaceApp*) AfxGetApp())->m_key.CheckDongle() )
	{
		MessageBox(	NULL,
			LoadStr( IDS_MBC_31 ),
			LoadStr( IDS_MBT_31 ), MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );
		return FALSE;
	}
	else
	{
		// If the file is about to be saved in a newer file format
		// alert the user and ask if it is okay to proceed
		if( m_nFileVersion!=GetHardcodedFileVersion() )
			if( MessageBox( NULL,
					LoadStr( IDS_MBC_42 ),
					LoadStr( IDS_MBT_42 ),
					MB_YESNO|MB_ICONQUESTION ) == IDNO )
				return FALSE;

		return CDocument::OnSaveDocument(lpszPathName);
	}
}

/////////////////////////////////////////////////////////////////////////////
// "filename.str *" SUPPORT

void CStageRaceDoc::SetModifiedFlag()
{
	((CStageRaceApp*) AfxGetApp())->m_key.CheckDongle( TRUE );
	
	CDocument::SetModifiedFlag();
	CString cTemp = CDocument::GetTitle();
	if( cTemp.Right(2) != " *" )
		this->SetTitle( CDocument::GetTitle() + " *" );
}

CString CStageRaceDoc::GetTitle() const
{
	CString cTemp = CDocument::GetTitle();
	if( cTemp.Right(2) == " *" )
		cTemp = cTemp.Left( cTemp.GetLength() - 2 );
	return cTemp;
}

void CStageRaceDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	Lock();

	CDocument::SetPathName(lpszPathName, bAddToMRU);

	Unlock();

	// Update all the views
	CUpdateViewHint UVH( UV_CONFIGURED, (CObject*)this );
	UpdateAllViews( NULL, TI_ROOT, (CObject*)&UVH );
}

/////////////////////////////////////////////////////////////////////////////
// GENERATION FUNCTIONS

void CStageRaceDoc::OnGenerateAll() 
{
	GenerateAll();
}

void CStageRaceDoc::OnGenerateCompetitors() 
{
	GenerateCompetitors();
}

void CStageRaceDoc::OnGenerateCrossout() 
{
	GenerateCrossout();
}

void CStageRaceDoc::OnGenerateSignin() 
{
	GenerateSignin();
}

void CStageRaceDoc::OnGenerateCommuniques() 
{
	GenerateCommunique(-1,-1);
}

void CStageRaceDoc::OnGenerateAllstages() 
{
	GenerateAllstages();
}

void CStageRaceDoc::OnGenerateToc() 
{
	GenerateToc();
}

void CStageRaceDoc::OnUpdateGenerateToc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() );
}

void CStageRaceDoc::OnGenerateAutomatically() 
{
	m_bGenerateAutomatically = !m_bGenerateAutomatically;
}

void CStageRaceDoc::OnUpdateGenerateAutomatically(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bGenerateAutomatically );
}

//

void CStageRaceDoc::GenerateAll()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = (GENERATE_TYPE)(GTY_CLASS|GTY_COMMUNIQUE|GTY_COMPETITORS|GTY_CROSSOUT|GTY_ORDER|GTY_SIGNIN|GTY_TOC);
	pg->m_what = PWH_ALL;
	pg->m_nFullStage = -1;
	pg->m_nHalfStage = -1;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateAllstages()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = (GENERATE_TYPE)(GTY_CLASS|GTY_ORDER);
	pg->m_what = PWH_ALL;
	pg->m_nFullStage = -1;
	pg->m_nHalfStage = -1;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateSignin()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_SIGNIN;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateOrder(int nFS, int nHS)
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_ORDER;
	pg->m_nFullStage = nFS;
	pg->m_nHalfStage = nHS;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateCrossout()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_CROSSOUT;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();

	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateCompetitors()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_COMPETITORS;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateToc()
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_TOC;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();
	
	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateCommunique(int nFS, int nHS)
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = GTY_COMMUNIQUE;
	pg->m_nFullStage = nFS;
	pg->m_nHalfStage = nHS;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();

	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

void CStageRaceDoc::GenerateClass(PUBLI_WHAT what/*=PWH_ALL*/, int nSubjectFS/*=-1*/, int nSubjectHS/*=-1*/)
{
	GENERATE* pg = new GENERATE;
	pg->m_gt = (GENERATE_TYPE)(GTY_CLASS|GTY_CROSSOUT|GTY_SIGNIN);
	pg->m_what = what;
	pg->m_nFullStage = nSubjectFS;
	pg->m_nHalfStage = nSubjectHS;
	pg->m_pDoc = this;
	pg->m_profile = m_allsettings.ProfilesGetCurrent();

	// Post the request for generating
	m_pGenerator->PostThreadMessage( WM_USER_GENERATE, (WPARAM)pg, NULL );
}

CWinThread* CStageRaceDoc::m_pGenerator = NULL;

void CStageRaceDoc::Init()
{
	m_pGenerator = AfxBeginThread( GenerateThread, (LPVOID)NULL );
}

void CStageRaceDoc::Exit()
{
	if( m_pGenerator )
	{
		m_pGenerator->PostThreadMessage( WM_QUIT, 0, 0 );

		DWORD exit_code;
		if( GetExitCodeThread(m_pGenerator->m_hThread,&exit_code) )
		{
			if( exit_code==STILL_ACTIVE )
				WaitForSingleObject(m_pGenerator->m_hThread, INFINITE);
		}
		m_pGenerator = NULL;
	}
}

void CStageRaceDoc::GenerateSetProgress()
{
	// Increment the progress bar in the status bar
	PostMessage( AfxGetMainWnd()->m_hWnd,
		WM_USER_GENERATE_PROGRESS_INCREMENT, 0, 0 );
}

UINT CStageRaceDoc::GenerateThread(LPVOID pParam)
{
	// INITIALISATION

		CArray<MSG,MSG&> m_queue;

	// MAIN PROCESS

		MSG msg;
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			// Add the new message to the queue
			m_queue.Add(msg);

			// Work until the local queue is empty
			// (as we might be growing it, below)
			while( m_queue.GetSize() )
			{
				// See if there are other relevant messages
				// pending to be added to the queue
				while( PeekMessage(&msg, NULL, WM_USER_GENERATE, WM_USER_GENERATE, PM_REMOVE) )
				{
					m_queue.Add(msg);
				}

				// Empty doubles from the queue
				// Iterate the queue to get every item
				// (but the last, as it can't have doubles
				// after it anymore)
				for( int i=0; i<m_queue.GetSize()-1; i++ )
				{
					MSG msg = m_queue.GetAt(i);
					GENERATE* pg = (GENERATE*)msg.wParam;

					// Make sure we only do this for the known message type
					if( msg.message == WM_USER_GENERATE )
					{
						// Then iterate the queue again to
						// see if there are any doubles behind
						// the one we are looking at
						for( int j=i+1; j<m_queue.GetSize(); )
						{
							MSG msgtest = m_queue.GetAt(j);

							// Make sure we only do this for the known message type
							if( msg.message == WM_USER_GENERATE )
							{
								GENERATE* pgtest = (GENERATE*)msgtest.wParam;
								// Test all items from the GENERATE structure
								if( (pgtest->m_gt == pg->m_gt)
										&& (pgtest->m_nFullStage == pg->m_nFullStage)
										&& (pgtest->m_nHalfStage == pg->m_nHalfStage)
										&& (pgtest->m_pDoc == pg->m_pDoc)
										&& (pgtest->m_profile == pg->m_profile)
										&& (pgtest->m_what == pg->m_what) )
									// Everything matches
									// So we've got ourselves a double
									// Thus remove it!
									m_queue.RemoveAt(j);
								else
									// Only increment if not one removed,
									// otherwise we would soon overrun our
									// array bounds
									j++;
							}
						}
					}
				}

				msg = m_queue.GetAt(0);
				m_queue.RemoveAt(0);
				switch(msg.message)
				{
					case WM_USER_GENERATE:
						{
							GENERATE* pg = (GENERATE*)msg.wParam;

							// Calculate the progress length for the progress bar
							int nProgressLength = 0;

							if( pg->m_gt & GTY_CLASS )
								nProgressLength += pg->m_pDoc->StagesHalfCount() * 5;

							if( pg->m_gt & GTY_COMMUNIQUE )
							{
								if( (pg->m_nFullStage==-1) || (pg->m_nHalfStage==-1) )
									nProgressLength += pg->m_pDoc->StagesHalfCount() +
										pg->m_pDoc->StagesFullCount() + 1;
								else
									nProgressLength += 1;
							}

							if( pg->m_gt & GTY_COMPETITORS )
								nProgressLength += 2;

							if( pg->m_gt & GTY_CROSSOUT )
								nProgressLength += pg->m_pDoc->StagesHalfCount();

							if( pg->m_gt & GTY_ORDER )
							{
								if( (pg->m_nFullStage==-1) || (pg->m_nHalfStage==-1) )
									nProgressLength += pg->m_pDoc->StagesHalfCount();
								else
									nProgressLength += 1;
							}

							if( pg->m_gt & GTY_SIGNIN )
								nProgressLength += pg->m_pDoc->StagesHalfCount();

							if( pg->m_gt & GTY_TOC )
								nProgressLength += 1;

							PostMessage( AfxGetMainWnd()->m_hWnd,
								WM_USER_GENERATE_PROGRESS_SET, nProgressLength, 0 );

						//Sleep(4000);
							
							if( WaitForSingleObject(
									pg->m_pDoc->m_hGenerateSemaphore_KeepDocOpen,0)==WAIT_OBJECT_0 )
							{

								// Do the actual generating
								if( pg->m_gt & GTY_CLASS )
									pg->m_pDoc->GenerateClass_Real( pg->m_what, pg->m_nFullStage, pg->m_nHalfStage );

								if( pg->m_gt & GTY_COMMUNIQUE )
									pg->m_pDoc->GenerateCommunique_Real( pg->m_nFullStage, pg->m_nHalfStage );

								if( pg->m_gt & GTY_COMPETITORS )
									pg->m_pDoc->GenerateCompetitors_Real();

								if( pg->m_gt & GTY_CROSSOUT )
									pg->m_pDoc->GenerateCrossout_Real();

								if( pg->m_gt & GTY_ORDER )
									pg->m_pDoc->GenerateOrder_Real( pg->m_nFullStage, pg->m_nHalfStage );

								if( pg->m_gt & GTY_SIGNIN )
									pg->m_pDoc->GenerateSignin_Real();

								if( pg->m_gt & GTY_TOC )
									pg->m_pDoc->GenerateToc_Real();

								ReleaseSemaphore(
									pg->m_pDoc->m_hGenerateSemaphore_KeepDocOpen,1,NULL);

								delete pg;
							}
						}
						{
							// Check if there are any more new messages
							// If not, indicate "ready"
							if( !PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
							{
								MessageBeep(MB_ICONASTERISK); // "ready"
								PostThreadMessage( AfxGetApp()->m_nThreadID,
									WM_USER_GENERATE_PROGRESS_FINISH, 0, 0 );
							}
						}
						break;
				}
			}
		}

	// CLEANUP
		
		return 0;
}

void CStageRaceDoc::UpdateAllViewsThreaded( CView* pSender, LPARAM lHint, CObject* pHint )
{
	POSITION nPos = GetFirstViewPosition();
	while( nPos )
	{
		CView* pView = GetNextView(nPos);
		if( pView->IsKindOf(RUNTIME_CLASS(CTreeViewMain)) )
		{
			int i = PostMessage( pView->m_hWnd,
				WM_USER_UPDATEALLVIEWS,
				(WPARAM)pHint,
				lHint );

			break;
		}
	}
}

// -1 makes it do ALL!
// NUMBER OF PROGRESS INCREASES: no. of half st. OR 1 (depending on mode)
void CStageRaceDoc::GenerateOrder_Real(int nFS, int nHS)
{
	Lock();

	if( (nFS==-1) || (nHS==-1) )
	{
		CFullStage* pFullStage;
		// Iterate the full stages list
		for( int nFS=1; nFS <= StagesFullCount(); nFS++ )
		{
			// Use every full stage
			pFullStage = StagesGet( nFS );

			CHalfStage* pHalfStage;
			// Iterate the half stages list
			for( int nHS=1; nHS <= pFullStage->CountHalfStages(); nHS++ )
			{
				// Use every half stage
				pHalfStage = StagesGet( nFS, nHS );

				if( pHalfStage->m_stageType!=ST_NORMAL )
					GenerateOrder_Single_Real(nFS,nHS);
				else
					GenerateSetProgress();
			}
		}
	}
	else
	{
		GenerateOrder_Single_Real(nFS,nHS);
	}

	Unlock();

	// Update the views
	UpdateAllViewsThreaded( NULL, TI_TIMETRIALORDER );
}

void CStageRaceDoc::GenerateOrder_Single_Real(int nFS, int nHS)
{
	if( StagesGet(nFS, nHS)->m_timeTrialOrder.GetCount() )
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_TIMETRIALORDER, this, columns );

		// Make the html document
		CHtmlDoc objHtml( CEventItem( this, TI_TIMETRIALORDER, nFS, nHS) );

		objHtml.Header(StagesGet(nFS, nHS)->m_idStartList.GetNo());

		// Print the competitors from the list to the html
		int nOffset = 0;
		for( int i=1; i<=StagesGet(nFS, nHS)->m_timeTrialOrder.GetCount(); i++ )
		{
			CArrival objArrival;
			while( !StagesGet(nFS, nHS)->m_timeTrialOrder.GetAtOrder( i+nOffset, &objArrival ) )
				nOffset++;

			// Print to the html
			objHtml.Competitor( columns, objArrival.m_staNo, &objArrival );

			StagesGet(nFS, nHS)->m_timeTrialOrder.LockRead();

			// Obviously it has been found, but there might be another one with the same order no.
			POSITION nPos = StagesGet(nFS, nHS)->m_timeTrialOrder.GetStartPosition();
			while( nPos )
			{
				CArrival objExtra;
				StagesGet(nFS, nHS)->m_timeTrialOrder.Iterate( nPos, objExtra );
				if( (objArrival.m_order == objExtra.m_order) && (objArrival.m_staNo != objExtra.m_staNo) )
				{
					// Print to the html
					objHtml.Competitor( columns, objExtra.m_staNo, &objExtra );
					i++;
					nOffset--;
				}
			}

			StagesGet(nFS, nHS)->m_timeTrialOrder.UnlockRead();
		}
		objHtml.Footer(columns);
		objHtml.Finish();
	}
	else
		CHtmlDoc::MakeDummy(
			CEventItem( this, TI_TIMETRIALORDER, nFS, nHS ),
			StagesGet(nFS,nHS)->m_idStartList.GetNo() );

	GenerateSetProgress();
}

// NUMBER OF PROGRESS INCREASES: no. of half st. * 5
void CStageRaceDoc::GenerateClass_Real(PUBLI_WHAT what/*=PWH_ALL*/, int nSubjectFS/*=-1*/, int nSubjectHS/*=-1*/)
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	Lock();

	// Variable is true once the subjected stage has come by
	//  or always when PWH_ALL
	//  but never when PWH_NOTHING
	bool bPrint = what==PWH_ALL;

	CClassification					aClass			( this );
	CSprintClassification			aSprint			( this );
	CPointsClassification			aPoints			( this );
	CMostAggressiveClassification	aMostAggressive	( this );
	CClimbsClassification			aClimb			( this );
	CTeamClassification				aTeam			( this );

	// We iterate through all stages
	int nFS = 1, nHS = 1;
	while( StagesGet( nFS ) )
	{
		CHalfStage* pHalfStage;
		// Within every stage we iterate through all half stages
		while( pHalfStage = StagesGet( nFS, nHS ) )
		{
			// Every half stage is put into the classification object
			pHalfStage->Generate(nFS, nHS, &aClass, &aTeam, &aPoints, &aSprint);

			GenerateSetProgress();

			// So, as soon as we added all rankings to the classifications, the sorted
			// results will be available to be used in our html document

			// If this is the half stage the user just edited:
			//  * we make a classification
			//  * we set everything from now on to be regenerated
			if( (((nFS==nSubjectFS) && (nHS==nSubjectHS)) || (what==PWH_ALL)) && (what!=PWH_NOTHING) )
			{
				bPrint = true;
				// Generate stage classification
				aClass.PublishClass( nFS, nHS );

				pHalfStage->PublishTTArrivalList(this, nFS, nHS);
			}

			GenerateSetProgress();

			// GENERAL AND TEAM CLASSIFICATION
				if( bPrint )
				{
					// Generate general classifications
					aClass.PublishGeneral( nFS, nHS, true,
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9),
						m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) );
					aTeam.Publish( nFS, nHS );
				}
				aTeam.StoreClassification();

			// POINTS CLASSIFICATION
				if( pHalfStage->m_pointspointsFinish.GetCount() )
				{
					if( bPrint )
						aPoints.Publish( nFS, nHS );

					// And clear the classification
					aPoints.StoreClassification();
				}
				else
					CHtmlDoc::MakeDummy(
						CEventItem( this, TI_POINTS, nFS, nHS ),
						pHalfStage->m_idPoints.GetNo() );

			GenerateSetProgress();

			// SPRINT CLASSIFICATION
				// Store the stage cl.
				aSprint.StoreClassification();
				if( pHalfStage->m_sprintpointsCount )
				{
					CHtmlDoc* pObjHtml = NULL;

					// Select the columns to print
					PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
					CEventItem::GetPublicationColumns( TI_SPRINT, this, columns );

					// Only if the half stage the user just edited has come by,
					// we make printouts
					if( bPrint )
					{
						// Make the html document
						pObjHtml = new CHtmlDoc( CEventItem( this, TI_SPRINT, nFS, nHS) );

						// We provide the html document with the information
						// to make the headers
						pObjHtml->Header(pHalfStage->m_idSprints.GetNo());
					}

					// Every sprint is put into the sprints classification object
					// To do so we iterate the sprints list for this stage
					int nSprint = 1;
					POSITION nPos;
					nPos = pHalfStage->m_sprints.GetHeadPosition();
					if( nPos )
					{
						while( nPos )
						{
							CArrivalList* pSprint;
							pSprint = &pHalfStage->m_sprints.GetNext( nPos );
							// Then we iterate every sprint to add the competitors to the classification
							DWORD nState = 0;
							CArrival objArrival;
							while( pSprint->IterateSorted( nState, objArrival ) )
							{
								if( objArrival.m_points )
									aSprint.AddCompetitor( objArrival, &aClass, nFS, nHS );
							}

							// Finish this sprint
							aSprint.FinishClassification();
							
							// Only if the half stage the user just edited has come by,
							// we make printouts
							if( pObjHtml )
							{
								// INTERMEDIATE CLASSIFICATION
								pObjHtml->SaySprint( columns, nSprint );
								// For the actual contents, we just have to iterate the
								// sprints classification we just made
								POSITION nPos = aSprint.m_classification.GetHeadPosition();
								while( nPos )
								{
									objArrival = aSprint.m_classification.GetNext( nPos );

									// We write the competitor with his ranking to the html document
									pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );
								}					
							}

							if( nPos )
							{
								// And clear the classification
								aSprint.StoreClassification();
								nSprint++;
							}
						}
					}
					else
						// Finish this sprint
						aSprint.FinishClassification();

					// If this was the last intermediate to add, we decide
					// whether to print the general classification
					if( pObjHtml )
					{
						// See if printing of stage ranking is required
						if( ((CSettingsPublication*)m_allsettings.ValueGet(IDS_SETT_RANK_SPRINT_PRINTSTAGE)) )
						{
							// STAGE CLASSIFICATION
							if( pHalfStage->m_sprintpointsFinish.GetCount() )
							{
								pObjHtml->SayText( columns, AssembleStr( TEXT("TocStage"), TEXT(", "), &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
								// For the actual contents, we just have to iterate the
								// stage classification we made a while ago
								POSITION nPos = aClass.m_classification.GetHeadPosition();
								int nAll = 1; // Provide correct rankings for every printed arrival
								while( nPos )
								{
									CArrival objArrival = aClass.m_classification.GetNext( nPos );

									if( objArrival.m_points )
									{
										// We write the competitor with his ranking to the html document
										objArrival.m_rank = nAll++;
										pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );
									}
								}
							}
						}
						// GENERAL CLASSIFICATION
						pObjHtml->SayText( columns, AssembleStr( TEXT("TocGeneral"), TEXT(", "), &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						if( aSprint.IsUnOfficial() )
							pObjHtml->SayText( columns, AssembleStr( TEXT("Unofficial"), TEXT(", "), &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						// For the actual contents, we just have to iterate the
						// sprints general classification we just made
						nPos = aSprint.m_generalClassification.GetHeadPosition();
						int nAll = 1; // Provide correct rankings for every printed arrival
						while( nPos )
						{
							CArrival objArrival = aSprint.m_generalClassification.GetNext( nPos );

							// We write the competitor with his ranking to the html document
							objArrival.m_rank = nAll++;
							pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );

						}

						pObjHtml->Footer(columns);
						pObjHtml->Finish();
						delete pObjHtml;
					}

					// And clear the classification
					aSprint.StoreClassification();
				}
				else
					CHtmlDoc::MakeDummy(
						CEventItem( this, TI_SPRINT, nFS, nHS ),
						StagesGet(nFS,nHS)->m_idSprints.GetNo() );

			GenerateSetProgress();

			// CLIMB CLASSIFICATION
				if( pHalfStage->m_climbs.GetCount() )
				{
					CHtmlDoc* pObjHtml = NULL;

					// Select the columns to print
					PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
					CEventItem::GetPublicationColumns( TI_CLIMB, this, columns );

					// Only if the half stage the user just edited has come by,
					// we make printouts
					if( bPrint )
					{
						// Make the html document
						pObjHtml = new CHtmlDoc( CEventItem( this, TI_CLIMB, nFS, nHS) );

						// We provide the html document with the information
						// to make the headers
						pObjHtml->Header(pHalfStage->m_idClimbs.GetNo());
					}

					// Every climb is put into the climbs classification object
					// To do so we iterate the climbs list for this stage
					int nSprint = 1;
					POSITION nPos;
					nPos = pHalfStage->m_climbs.GetHeadPosition();
					while( nPos )
					{
						CArrivalList* pClimb;
						pClimb = &pHalfStage->m_climbs.GetNext( nPos );
						// Then we iterate every climb to add the competitors to the classification
						DWORD nState = 0;
						CArrival objArrival;
						while( pClimb->IterateSorted( nState, objArrival ) )
						{
							if( objArrival.m_points )
								aClimb.AddCompetitor( objArrival, &aClass, nFS, nHS );
						}

						// Finish this climb
						aClimb.FinishClassification();
						
						// Only if the half stage the user just edited has come by,
						// we make printouts
						if( pObjHtml )
						{
							// INTERMEDIATE CLASSIFICATION
							pObjHtml->SaySprint( columns, nSprint );
							// For the actual contents, we just have to iterate the
							// climbs clssification we just made
							POSITION nPos = aClimb.m_classification.GetHeadPosition();
							while( nPos )
							{
								objArrival = aClimb.m_classification.GetNext( nPos );

								// We write the competitor with his ranking to the html document
								pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );
							}					
						}

						// If this was the last intermediate to add, we decide
						// whether to print the general classification
						if( !nPos && pObjHtml )
						{
							// GENERAL CLASSIFICATION
							pObjHtml->SayText( columns, AssembleStr( TEXT("TocGeneral"), TEXT(", "), &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
							if( aClimb.IsUnOfficial() )
								pObjHtml->SayText( columns, AssembleStr( TEXT("Unofficial"), TEXT(", "), &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
							// For the actual contents, we just have to iterate the
							// climbs general classification we just made
							POSITION nPos = aClimb.m_generalClassification.GetHeadPosition();
							int nAll = 1; // Provide correct rankings for every printed arrival
							while( nPos )
							{
								CArrival objArrival = aClimb.m_generalClassification.GetNext( nPos );

								// We write the competitor with his ranking to the html document
								objArrival.m_rank = nAll++;
								pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );

							}

							pObjHtml->Footer(columns);
							pObjHtml->Finish();
							delete pObjHtml;
						}

						// And clear the classification
						aClimb.StoreClassification();
						nSprint++;
					}
				}
				else
					CHtmlDoc::MakeDummy(
						CEventItem( this, TI_CLIMB, nFS, nHS ),
						StagesGet(nFS,nHS)->m_idClimbs.GetNo() );

			// MOST AGGRESSIVE CLASSIFICATION
				if( pHalfStage->m_mostaggressivepoints.GetCount() )
				{
					if( pHalfStage->m_mostaggressive.GetCount() )
					{
						// Then we iterate the arrival data to add the competitors to the classification
						DWORD nState = 0;
						CArrival objArrival;
						while( pHalfStage->m_mostaggressive.IterateSorted( nState, objArrival ) )
						{
							if( objArrival.m_points )
								aMostAggressive.AddCompetitor( objArrival, &aClass, nFS, nHS );
						}

						// Finish this climb
						aMostAggressive.FinishClassification();

						if( bPrint )
							aMostAggressive.Publish( nFS, nHS );

						// And clear the classification
						aMostAggressive.StoreClassification();
					}
					else
						CHtmlDoc::MakeDummy(
							CEventItem( this, TI_MOSTAGGRESSIVE, nFS, nHS ),
							pHalfStage->m_idMostAggressive.GetNo() );
				}

			GenerateSetProgress();
			nHS++;

			// Do this on the end in order to use it as last solution for other classifications
			aClass.StoreClassification();
		}
		nHS = 1;
		nFS++;

	}

	Unlock();

	UpdateAllViewsThreaded( NULL, TI_HALFSTAGE );
	UpdateAllViewsThreaded( NULL, TI_SPRINT );
	UpdateAllViewsThreaded( NULL, TI_CLIMB );
	UpdateAllViewsThreaded( NULL, TI_MOSTAGGRESSIVE );
	UpdateAllViewsThreaded( NULL, TI_POINTS );
	UpdateAllViewsThreaded( NULL, TI_CLASSGENERAL );
	UpdateAllViewsThreaded( NULL, TI_TTARRIVALLIST );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK1STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK2STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK3STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK4STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK5STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK6STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK7STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK8STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK9STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK10STAGE );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK1GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK2GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK3GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK4GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK5GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK6GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK7GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK8GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK9GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSMASK10GENERAL );
	UpdateAllViewsThreaded( NULL, TI_CLASSTEAMS );
}

// NUMBER OF PROGRESS INCREASES: no. of half st.
void CStageRaceDoc::GenerateCrossout_Real()
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	CHalfStage* pHalfStage;

	Lock();

	// We iterate through all stages
	int nFS = 1;
	int nHS = 1;
	while( StagesGet( nFS ) )
	{
		// Within every stage we iterate through all half stages
		while( pHalfStage = StagesGet( nFS, nHS ) )
		{
			// For every half stage we make a cross out list except when it's a time trial

			// We start the html

			// Make the html document
			CHtmlDoc objHtml( CEventItem( this, TI_CROSSOUTLIST, nFS, nHS) );
		
			// We provide the html document with the information
			// to make the headers
			objHtml.Header(pHalfStage->m_idCrossOut.GetNo());

			int nCount = 0;
			int nDecade = 0;
			// Make it count to ten on default and to the setting value otherwise
			int nDecadeDefinition = 10;
			if( m_allsettings.ValueGet( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES ) )
				nDecadeDefinition = ((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_modulusCrossOutTeamNames;
			// We keep on searching for competitors until we got them all in our list
			while( nCount < m_competitors.GetCount() )
			{
				CTeam* pTeamFirstStaNo = NULL;
				CCompetitor objComp;
				int nCompetitors[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				int nCrossedOut [10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				// We search for the next ten
				for( int i=1; i<=nDecadeDefinition; i++ )
					// If competitor exists
					{
						int nLookup = nDecade*nDecadeDefinition+i;
						if( m_competitors.Exist( nLookup ) )
						{
							objComp = m_competitors.GetAt( nLookup );

							// We set its StaNo to be printed
							nCompetitors[i-1] = nDecade*nDecadeDefinition+i;

							nCount++;

							// If this is the first of this decade,
							// we remember its team name
							if( pTeamFirstStaNo == NULL )
								pTeamFirstStaNo = objComp.m_pTeam;

							// We check whether this competitor is still in the race
							// If this is not the first stage we check the previous stage's arrival list
							if( (nFS>1) || (nHS>1) )
							{
								// If not, we set the appropriate bit
								if( !StagesGetPrev( nFS, nHS )->m_arrival.Exist( nCompetitors[i-1] )
									|| StagesGetPrev( nFS, nHS )->m_arrival.IsTimeCutted( nCompetitors[i-1] ) )
									nCrossedOut[i-1]=1;
							}
							// We also check the signOut list
							WORD nSignOut = objComp.m_staNo;
							if( pHalfStage->m_signOuts.Exist( nSignOut ) )
								nCrossedOut[i-1]=1;
						}
					}
				nDecade++;

				// If any competitors in this decade, we print it
				if( pTeamFirstStaNo )
				{
					objHtml.CrossOut( nCompetitors, nCrossedOut, pTeamFirstStaNo );
				}
			}

			objHtml.Footer();
			objHtml.Finish();

			GenerateSetProgress();
			nHS++;
		}
		nHS = 1;
		nFS++;

	}

	Unlock();

	// Update the views
	UpdateAllViewsThreaded( NULL, TI_CROSSOUTLIST );
}

// NUMBER OF PROGRESS INCREASES: no. of half st.
void CStageRaceDoc::GenerateSignin_Real()
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	CHalfStage* pHalfStage;

	Lock();

	// We iterate through all stages
	int nFS = 1;
	int nHS = 1;
	while( StagesGet( nFS ) )
	{
		// Within every stage we iterate through all half stages
		while( pHalfStage = StagesGet( nFS, nHS ) )
		{
			// Select the columns to print
			PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
			CEventItem::GetPublicationColumns( TI_SIGNINLIST, this, columns );

			// Make the html document
			CHtmlDoc objHtml( CEventItem( this, TI_SIGNINLIST, nFS, nHS) );

			objHtml.Header(pHalfStage->m_idSignIn.GetNo());

			// Determine from which source the available's list has to be taken
			CStaNoObjectList* pAvail;
			if ( StagesGetPrev( nFS, nHS )==NULL )
				pAvail = &m_competitors;
			else
				pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

			const CAvailableList* pAvailList = NULL;
			if ( pHalfStage->m_stageType==ST_NORMAL )
				pAvailList = new CAvailableList( &pHalfStage->m_signOuts, pAvail );
			else
				pAvailList = new CAvailableList( &pHalfStage->m_signOuts, &pHalfStage->m_timeTrialOrder );

			// Iterate the half stage's competitor list
			CArrival objArrival;
			DWORD nState=0;
			while( pAvailList->IterateSorted( nState, objArrival ) )
			{
				if( CompetitorsExist( objArrival.m_staNo ) )
					objHtml.Competitor( columns, objArrival.m_staNo );
			};

			objHtml.Footer(columns);
			objHtml.Finish();

			GenerateSetProgress();

			delete pAvailList;

			nHS++;
		}
		nHS=1;
		nFS++;
	}

	Unlock();
	
	// Update the views
	UpdateAllViewsThreaded( NULL, TI_SIGNINLIST );
}

// NUMBER OF PROGRESS INCREASES: 2
void CStageRaceDoc::GenerateCompetitors_Real()
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	Lock();

// Make a html document from the competitors list
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_LISTCOMPETITORS1, this, columns );

		// Make the html document
		CHtmlDoc objHtml( CEventItem( this, TI_LISTCOMPETITORS1, 0, 0) );

		objHtml.Header(this->m_idCompetitors.GetNo());

		if( (m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK4 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK5 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK6 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK7 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK8 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK9 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK10 ) ) )
				objHtml.Legenda( columns );

		// Iterate the documents competitors list
		for ( int i=1, nSkipMap=1; // Retrieve all items once
				i<=m_competitors.GetCount(); i++, nSkipMap++)
		{				
			while ( !m_competitors.Exist( nSkipMap ) )
				nSkipMap++ ;
			// Actually fill the html file with competitors
			objHtml.Competitor( columns, nSkipMap );
		};

		objHtml.Footer(columns);
		objHtml.Finish();
	}

	GenerateSetProgress();

// Make a html document from the teams list
	{
		// Calculate column count
		int nColumnCount = 1;
		if( m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_2) ) nColumnCount = 2;
		else if( m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_3) ) nColumnCount = 3;
		else if( m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_4) ) nColumnCount = 4;
		else if( m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_5) ) nColumnCount = 5;
		else if( m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_6) ) nColumnCount = 6;

		int nPerColumn = TeamsCount() / nColumnCount;
		if( TeamsCount() % nColumnCount ) nPerColumn++;

		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_LISTCOMPETITORS2, this, columns );

		// Make the html document
		CHtmlDoc objHtml( CEventItem( this,TI_LISTCOMPETITORS2, 0, 0) );

		objHtml.Header(this->m_idTeams.GetNo());

		if( (m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK4 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK5 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK6 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK7 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK8 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK9 ) ) ||
			(m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) && m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK10 ) ) )
				objHtml.Legenda( columns );

		// Start multicolumn approach
		int nTeams = 0;
		if( nColumnCount > 1 )
			objHtml.StartColumns();

		CTeam* pPreviousTeam = NULL;
		// Iterate the documents competitors list
		for ( int i=1, nSkipMap=1; // Retrieve all items once
				i<=m_competitors.GetCount(); i++, nSkipMap++)
		{				
			CCompetitor objCompetitor;
			while ( !m_competitors.Exist( nSkipMap ) )
				nSkipMap++ ;
			objCompetitor = m_competitors.GetAt( nSkipMap );

			// Check whether this is a competitor from the current team
			if( pPreviousTeam != objCompetitor.m_pTeam )
			{
				if( pPreviousTeam )
					objHtml.TeamFooter( columns, pPreviousTeam );

				// Arrange possibly next column for multicolumn approach
				nTeams++;
				if( (nTeams>nPerColumn) && (nColumnCount>1) )
				{
					objHtml.NextColumn();
					nTeams=1;
				}

				objHtml.TeamHeader( columns, objCompetitor.m_pTeam );
				pPreviousTeam = objCompetitor.m_pTeam;
			}
			// Actually fill the html file with competitors
			objHtml.Competitor( columns, nSkipMap );
		};
		if( pPreviousTeam )
			objHtml.TeamFooter( columns, pPreviousTeam );

		if( nColumnCount > 1 )
			objHtml.EndColumns();
		
		objHtml.Footer(columns);
		objHtml.Finish();
	}

	Unlock();

	UpdateAllViewsThreaded( NULL, TI_LISTCOMPETITORS1 );
	UpdateAllViewsThreaded( NULL, TI_LISTCOMPETITORS2 );

	GenerateSetProgress();
}

// NUMBER OF PROGRESS INCREASES: 1
void CStageRaceDoc::GenerateToc_Real()
{
	if( ((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() )
		return;

	Lock();

	CHtmlDoc objHtml( CEventItem(this, TI_ROOT, 0, 0) );

	// We provide the html document with the information
	// to make the headers
	objHtml.Header(0);
	objHtml.Toc();
	objHtml.Footer();
	objHtml.Finish();

	Unlock();

	// Update all the views
	UpdateAllViewsThreaded( NULL, TI_ROOT, NULL );

	GenerateSetProgress();
}

// -1 makes it do ALL!
// NUMBER OF PROGRESS INCREASES: no. of full st. + no. of half st. + 1 OR 1 (depending on mode)
void CStageRaceDoc::GenerateCommunique_Real(int nFS, int nHS)
{
	Lock();

	if( (nFS==-1) || (nHS==-1) )
	{
		CFullStage* pFullStage;
		// Iterate the full stages list
		for( int nFS=1; nFS <= StagesFullCount(); nFS++ )
		{
			// Use every full stage
			pFullStage = StagesGet( nFS );

			if( !pFullStage->m_communique.IsEmpty() )
				GenerateCommunique_Single_Real(nFS, 0);
			else
				GenerateSetProgress();

			CHalfStage* pHalfStage;
			// Iterate the half stages list
			for( int nHS=1; nHS <= pFullStage->CountHalfStages(); nHS++ )
			{
				// Use every half stage
				pHalfStage = StagesGet( nFS, nHS );

				if( !pHalfStage->m_communique.IsEmpty() )
					GenerateCommunique_Single_Real(nFS, nHS);
				else
					GenerateSetProgress();
			}
		}
		if( !m_communique.IsEmpty() )
			GenerateCommunique_Single_Real(0, 0);
		else
			GenerateSetProgress();
	}
	else
	{
		GenerateCommunique_Single_Real(nFS, nHS);
	}

	Unlock();

	// Update all the views
	UpdateAllViewsThreaded( NULL, TI_COMMUNIQUE );
}

void CStageRaceDoc::GenerateCommunique_Single_Real(int nFS, int nHS)
{
	CHtmlDoc objHtml( CEventItem( this, TI_COMMUNIQUE, nFS, nHS ) );
	objHtml.Header(CommuniqueGet(nFS, nHS)->m_id.GetNo());
	objHtml.Communique(CommuniqueGet(nFS, nHS));
	objHtml.Footer();
	objHtml.Finish();

	GenerateSetProgress();
}

CClassification * CStageRaceDoc::GenerateUpTo(int nSubjFS, int nSubjHS, CClassification* pClass/*=NULL*/, CTeamClassification* pTeam/*=NULL*/)
{
	if( !pClass )
		pClass = new CClassification( this );

	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	CHalfStage* pHalfStage;
	// We iterate through all stages
	int nFS = 1;
	int nHS = 1;
	while( StagesGet( nFS ) && (nFS<=nSubjFS) )
	{
		// Within every stage we iterate through all half stages
		while( pHalfStage = StagesGet( nFS, nHS ) )
		{
			pHalfStage->Generate( nFS, nHS, pClass, pTeam );

			// If we just handled the requested stage,
			// we stop processing
			// Note that particularly StoreClassification must be skipped
			if( (nHS==nSubjHS) && (nFS==nSubjFS) )
				break;

			pClass->StoreClassification();
			if( pTeam )
				pTeam->StoreClassification();

			nHS++;
		}
		nHS = 1;
		nFS++;
	}

	return pClass;
}

/////////////////////////////////////////////////////////////////////////////
// SPARE COMPETITORS FUNCTIONS

void CStageRaceDoc::SpareCompetitorsUpdate( const CCompetitor* pComp, COMPETITOR_FIELD f, CString val )
{
	CCompetitor* pComp1 = (CCompetitor*)pComp;
	switch( f )
	{
		case CF_NAME:
			pComp1->m_competitor = val;
			break;
		case CF_COUNTRY:
			pComp1->m_countryCode = val.Left(3);
			pComp1->m_countryCode.MakeUpper();
			break;
		case CF_UCI:
			pComp1->m_UCICode = val.Left(11);
			pComp1->m_UCICode.MakeUpper();
			break;
		case CF_LICENSE:
			pComp1->m_license = val.Left(11);
			pComp1->m_license.MakeUpper();
			break;
		case CF_CATEGORY:
			pComp1->m_category = val.Left(11);
			break;
	}
	// Update all the views
	CUpdateViewHint UVH( UV_UPDATED, pComp1 );
	UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );
	// Set the document's modified flag
	SetModifiedFlag();
}

// OUT: the position of the first spare competitor
POSITION CStageRaceDoc::SpareCompetitorsGetStartPosition() const
{
	return m_spareCompetitors.GetStartPosition();
}

// IN: the current position
// OUT: the spare competitor at this position and an updated position
const CCompetitor* CStageRaceDoc::SpareCompetitorsIterate(POSITION& nPos) const
{
	void* pComp;
	m_spareCompetitors.GetNextAssoc( nPos, pComp, pComp );
	return (const CCompetitor*)pComp;
}

// IN: the pointer of which the existence needs to be checked
// OUT: is available
bool CStageRaceDoc::SpareCompetitorsExist(const CCompetitor* pComp) const
{
	return m_spareCompetitors.Lookup((void*)pComp, (void*&)pComp)>0;
}

// IN: the pointer that needs to be deleted
// OUT: success
bool CStageRaceDoc::SpareCompetitorsDelete(const CCompetitor* pCompInput)
{
	// Check if the competitor exists
	if(SpareCompetitorsExist( pCompInput ))
	{
		CCompetitor* pComp;
		m_spareCompetitors.Lookup((void*)pCompInput,(void*&)pComp);
	
		// Remove the competitor from the document's spare competitors list
		m_spareCompetitors.RemoveKey( pComp );
		// Actually remove it
		delete pComp;

		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_DELETED, pComp );
		UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );

		return true;
	}
	else
		// Error: doesn't exist
		MessageBox( NULL, LoadStr( IDS_MBC_15 ), LoadStr( IDS_MBT_15 ), MB_OK | MB_ICONERROR);
	return false;
}

// IN: the pointer of the spare competitor that needs to be edited
void CStageRaceDoc::SpareCompetitorsEdit(const CCompetitor* pCompInput)
{
	CCompetitor* pComp;
	m_spareCompetitors.Lookup((void*)pCompInput,(void*&)pComp);

	// Run the edit dialog
	if( pComp->Edit((CStageRaceDoc*const) this) == IDOK )
	{
		// If evaluated positive:
		
		// Update all the views
		if( pComp->m_staNo && !CompetitorsInUse(pComp->m_staNo) )
		{
			// Insert the temporarely original object into the document's competitor list
			m_competitors.Insert( *pComp );

			// Remove the competitor from the document's spare competitors list
			m_spareCompetitors.RemoveKey( pComp );

			// Update all the views
			CUpdateViewHint UVH1( UV_DELETED, pComp );
			UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH1 );
			CUpdateViewHint UVH2( UV_ADDED, pComp );
			UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH2 );

			// Actually remove it
			delete pComp;

			// Generate lists
			if( m_bGenerateAutomatically )
				GenerateCompetitors();
		}
		else
		{
			// Make sure it is still zero if we get here
			pComp->m_staNo = 0;
			// Update all the views
			CUpdateViewHint UVH( UV_UPDATED, pComp );
			UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );
		}

		// Set the document's modified flag
		SetModifiedFlag();
	}
}

// OUT: the amount of spare competitors
int CStageRaceDoc::SpareCompetitorsCount() const
{
	return m_spareCompetitors.GetCount();
}

void CStageRaceDoc::SpareCompetitorsChangeStaNo( const CCompetitor* pCompInput, WORD nNewStaNo )
{
	CCompetitor* pComp;
	m_spareCompetitors.Lookup((void*)pCompInput,(void*&)pComp);

	pComp->m_staNo = nNewStaNo;

	// Update all the views
	if( pComp->m_staNo )
	{
		if( !CompetitorsExist( pComp->m_staNo ) )
		{
			// Insert the temporarely original object into the document's competitor list
			m_competitors.Insert( *pComp );

			// Remove the competitor from the document's spare competitors list
			m_spareCompetitors.RemoveKey( pComp );

			// Update all the views
			CUpdateViewHint UVH1( UV_DELETED, pComp );
			UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH1 );
			CUpdateViewHint UVH2( UV_ADDED, pComp );
			UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH2 );

			// Actually remove it
			delete pComp;

			// Generate lists
			if( m_bGenerateAutomatically )
				GenerateCompetitors();
		}
	}
	else
	{
		// Update all the views
		CUpdateViewHint UVH( UV_UPDATED, pComp );
		UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );
	}

	// Set the document's modified flag
	SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////
// COMPETITORS FUNCTIONS

void CStageRaceDoc::CompetitorsCleanup()
{
	CDlgCleanupCompetitors dlg;
	CLEANUPCOMPETITORS d = (CLEANUPCOMPETITORS)dlg.DoModal();
	if( d!=CLC_NONE )
	{
		DWORD nState=0;
		CCompetitor aComp;			
		bool bDirty = false;
		while( CompetitorsIterateSorted( nState, aComp ) )
		{
			if( CompetitorsCleanupHelper(&aComp,d) )
			{
				Lock();

				m_competitors.Insert(aComp);

				Unlock();

				// Update all the views
				CUpdateViewHint UVH( UV_UPDATED, &aComp );
				UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );
				// Set the document's modified flag
				SetModifiedFlag();

				bDirty = true;
			}
		}
		POSITION nPos = SpareCompetitorsGetStartPosition();
		while( nPos )
		{
			CCompetitor* pComp;
			pComp = (CCompetitor*)SpareCompetitorsIterate( nPos );

			if( CompetitorsCleanupHelper(pComp,d) )
			{
				// Update all the views
				CUpdateViewHint UVH( UV_UPDATED, pComp );
				UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );
				// Set the document's modified flag
				SetModifiedFlag();
			}
		}
		nPos = TeamsGetStartPosition();
		while( nPos )
		{
			CTeam* pTeam;
			TeamsIterate( nPos, (const CTeam*&)pTeam );

			Lock();

			if( TeamsCleanupHelper(pTeam,d) )
			{
				// Update all the views
				CUpdateViewHint UVH( UV_UPDATED, pTeam );
				UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );
				// Set the document's modified flag
				SetModifiedFlag();

				bDirty = true;
			}

			Unlock();
		}
		// Generate lists
		if( bDirty && m_bGenerateAutomatically )
			GenerateCompetitors();
	}
}

bool CStageRaceDoc::CompetitorsCleanupHelper(CCompetitor* pComp, CLEANUPCOMPETITORS clc)
{
	bool bDirty = false;
	if( clc & CLC_CLEANUPCOMMAS )
	{
		CString old = pComp->m_competitor;

		pComp->m_competitor.Replace( TEXT(","), TEXT(", ") );
		while( pComp->m_competitor.Replace( TEXT(",  "), TEXT(", ") ) );
		while( pComp->m_competitor.Replace( TEXT(" ,"), TEXT(",") ) );

		pComp->m_competitor.Replace( TEXT(";"), TEXT("; ") );
		while( pComp->m_competitor.Replace( TEXT(";  "), TEXT("; ") ) );
		while( pComp->m_competitor.Replace( TEXT(" ;"), TEXT(";") ) );

		if( old != pComp->m_competitor )
			bDirty = true;
	}
	if( clc & CLC_CAPITALIZEBEFORECOMMA )
	{
		int i = pComp->m_competitor.Find( ',' );
		if( i!=-1 )
		{
			CString old = pComp->m_competitor;
			pComp->m_competitor.MakeUpper();
			pComp->m_competitor =
				pComp->m_competitor.Left( i )+old.Mid( i );
			if( old != pComp->m_competitor )
				bDirty = true;
		}
	}
	if( clc & CLC_REMOVEREPEATEDSPACES )
	{
		while(pComp->m_competitor.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pComp->m_category.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pComp->m_countryCode.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pComp->m_license.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pComp->m_UCICode.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
	}
	if( clc & CLC_REMOVESPACESAROUND )
	{
		int n = pComp->m_competitor.GetLength()+
			pComp->m_category.GetLength()+
			pComp->m_countryCode.GetLength()+
			pComp->m_license.GetLength()+
			pComp->m_UCICode.GetLength();

		pComp->m_competitor.TrimLeft();
		pComp->m_category.TrimLeft();
		pComp->m_countryCode.TrimLeft();
		pComp->m_license.TrimLeft();
		pComp->m_UCICode.TrimLeft();

		pComp->m_competitor.TrimRight();
		pComp->m_category.TrimRight();
		pComp->m_countryCode.TrimRight();
		pComp->m_license.TrimRight();
		pComp->m_UCICode.TrimRight();

		if( n != pComp->m_competitor.GetLength()+
			pComp->m_category.GetLength()+
			pComp->m_countryCode.GetLength()+
			pComp->m_license.GetLength()+
			pComp->m_UCICode.GetLength() ) bDirty = true;
	}
	if( clc & CLC_COPYUCITOCOUNTRY )
	{
		if( pComp->m_countryCode.IsEmpty() )
		{
			pComp->m_countryCode = pComp->m_UCICode.Left(3);
			pComp->m_countryCode.MakeUpper();
			bDirty = true;
		}
	}
	return bDirty;
}

void CStageRaceDoc::CompetitorsUpdate( WORD nStaNo, COMPETITOR_FIELD f, CString val )
{
	CCompetitor aComp = CompetitorsGet(nStaNo);
	switch( f )
	{
		case CF_NAME:
			aComp.m_competitor = val;
			break;
		case CF_COUNTRY:
			aComp.m_countryCode = val.Left(3);
			aComp.m_countryCode.MakeUpper();
			break;
		case CF_UCI:
			aComp.m_UCICode = val.Left(11);
			aComp.m_UCICode.MakeUpper();
			break;
		case CF_LICENSE:
			aComp.m_license = val.Left(11);
			aComp.m_license.MakeUpper();
			break;
		case CF_CATEGORY:
			aComp.m_category = val.Left(11);
			break;
	}

	Lock();

	m_competitors.Insert( aComp );

	Unlock();

	// Update all the views
	CUpdateViewHint UVH( UV_UPDATED, &aComp );
	UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );
	// Set the document's modified flag
	SetModifiedFlag();
	// Generate lists
	if( m_bGenerateAutomatically )
		GenerateCompetitors();
}

void CStageRaceDoc::CompetitorsChangeStaNo( WORD nStaNo, WORD nNewStaNo )
{
	// Fill a competitor with the appropriate contents
	CCompetitor aEditCompetitor;
	aEditCompetitor = m_competitors.GetAt( nStaNo );

	aEditCompetitor.m_staNo = nNewStaNo;

	if( aEditCompetitor.m_staNo || CompetitorsInUse(nStaNo) )
	{
		if( !CompetitorsExist( aEditCompetitor.m_staNo ) )
		{
			// Update all the views
			if( nStaNo != aEditCompetitor.m_staNo )
				// Check if the competitor can be deleted
				if( !CompetitorsInUse(nStaNo) )
				{
					Lock();

					// Remove the competitor from the document's competitors list
					m_competitors.Remove(nStaNo);

					// Update all the views
					CUpdateViewHint UVH1( UV_DELETED, (CObject*)&nStaNo );
					UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH1 );

					CUpdateViewHint UVH2( UV_UPDATED, &aEditCompetitor );
					UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH2 );

					// Insert the temporarely original object into the document's competitor list
					m_competitors.Insert( aEditCompetitor );

					Unlock();

					// Set the document's modified flag
					SetModifiedFlag();

					// Generate lists
					if( m_bGenerateAutomatically )
						GenerateCompetitors();
				}
				else
					// Error: couldn't be deleted
					MessageBox( NULL, LoadStr( IDS_MBC_3 ), LoadStr( IDS_MBT_3 ), MB_OK | MB_ICONINFORMATION);
		}
		else
			return;
	}
	else
	{
		Lock();

		// Remove the competitor from the document's competitors list
		m_competitors.Remove(nStaNo);

		// Insert the temporarely original object into the document's spare competitor list
		CCompetitor* pNewCompetitor = new CCompetitor( aEditCompetitor );
		m_spareCompetitors.SetAt(pNewCompetitor, pNewCompetitor);

		Unlock();

		// Update all the views
		CUpdateViewHint UVH1( UV_DELETED, (CObject*)&nStaNo );
		UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH1 );
		CUpdateViewHint UVH2( UV_ADDED, pNewCompetitor );
		UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH2 );

		// Set the document's modified flag
		SetModifiedFlag();

		// Generate lists
		if( m_bGenerateAutomatically )
			GenerateCompetitors();
	}
}

// IN: a pointer and a staNo of the two competitors we want swapped
void CStageRaceDoc::CompetitorsSwap(WORD nStaNo1, CCompetitor* pComp2)
{
	// Get the first competitor
	CCompetitor comp1 = m_competitors.GetAt( nStaNo1 );
	// Make a copy
	CCompetitor comp1copy(comp1);
	// Change the first competitor
	comp1.Swap( pComp2 );
	CUpdateViewHint UVH1( UV_UPDATED, &comp1 );
	UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH1 );

	Lock();

	// Put the first competitor back
	m_competitors.Insert( comp1 );

	Unlock();

	// Change the second competitor
	pComp2->Swap( &comp1copy );
	CUpdateViewHint UVH2( UV_UPDATED, pComp2 );
	UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH2 );

	// Set the document's modified flag
	SetModifiedFlag();

	// Generate lists
	if( m_bGenerateAutomatically )
		GenerateCompetitors();
}

// IN: a staNo and a pointer of the two competitors we want swapped
void CStageRaceDoc::CompetitorsSwap(CCompetitor* pComp1, WORD nStaNo2)
{
	CompetitorsSwap( nStaNo2, pComp1 );
}

// IN: staNos of the two competitors we want swapped
void CStageRaceDoc::CompetitorsSwap(WORD nStaNo1, WORD nStaNo2)
{
	// Get the first competitor
	CCompetitor comp1 = m_competitors.GetAt( nStaNo1 );
	// Make a copy
	CCompetitor comp1copy(comp1);
	// Get the second competitor
	CCompetitor comp2 = m_competitors.GetAt( nStaNo2 );
	// Change the first competitor
	comp1.Swap( &comp2 );

	Lock();

	// Put the first competitor back
	m_competitors.Insert( comp1 );
	CUpdateViewHint UVH1( UV_UPDATED, &comp1 );
	UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH1 );
	// Change the second competitor
	comp2.Swap( &comp1copy );
	// Put the second competitor back
	m_competitors.Insert( comp2 );

	Unlock();

	CUpdateViewHint UVH2( UV_UPDATED, &comp2 );
	UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH2 );

	// Set the document's modified flag
	SetModifiedFlag();

	// Generate lists
	if( m_bGenerateAutomatically )
		GenerateCompetitors();
}

// IN: the StaNo of the competitor that needs to be edited
void CStageRaceDoc::CompetitorsEdit(int nStaNo)
{
	// Fill a competitor with the appropriate contents
	CCompetitor aEditCompetitor;
	aEditCompetitor = m_competitors.GetAt( nStaNo );

	// Run the edit dialog
	if( aEditCompetitor.Edit((CStageRaceDoc*const) this) == IDOK )
	{
		// If evaluated positive:
		
		if( aEditCompetitor.m_staNo || CompetitorsInUse(nStaNo) )
		{
			Lock();

			// Update all the views
			if( nStaNo != aEditCompetitor.m_staNo )
			{
				// Check if the competitor can be deleted
				if( !CompetitorsInUse(nStaNo) )
				{
					// Remove the competitor from the document's competitors list
					m_competitors.Remove(nStaNo);

					// Update all the views
					CUpdateViewHint UVH( UV_DELETED, (CObject*)&nStaNo );
					UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );
				}
				else
				{
					aEditCompetitor.m_staNo = nStaNo;
					// Error: couldn't be deleted
					MessageBox( NULL, LoadStr( IDS_MBC_3 ), LoadStr( IDS_MBT_3 ), MB_OK | MB_ICONINFORMATION);
				}
			}
			CUpdateViewHint UVH( UV_UPDATED, &aEditCompetitor );
			UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );

			// Insert the temporarely original object into the document's competitor list
			m_competitors.Insert( aEditCompetitor );

			Unlock();
		}
		else
		{
			Lock();

			// Remove the competitor from the document's competitors list
			m_competitors.Remove(nStaNo);

			Unlock();

			// Insert the temporarely original object into the document's spare competitor list
			CCompetitor* pNewCompetitor = new CCompetitor( aEditCompetitor );
			m_spareCompetitors.SetAt(pNewCompetitor, pNewCompetitor);

			// Update all the views
			CUpdateViewHint UVH1( UV_DELETED, (CObject*)&nStaNo );
			UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH1 );
			CUpdateViewHint UVH2( UV_ADDED, pNewCompetitor );
			UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH2 );
		}

		// Set the document's modified flag
		SetModifiedFlag();

		// Generate lists
		if( m_bGenerateAutomatically )
			GenerateCompetitors();
	}
}

// IN: the StaNo of the competitor that needs to be retrieved
// OUT: the matching competitor
CCompetitor CStageRaceDoc::CompetitorsGet(int nStaNo) const
{
	CCompetitor aComp;
	aComp = m_competitors.GetAt( nStaNo );
	return aComp;
}

// IN: the current position
// OUT: the competitor at this position and an updated position
bool CStageRaceDoc::CompetitorsIterateSorted(DWORD &nState, CCompetitor &aComp) const
{
	return m_competitors.IterateSorted( nState, aComp );
}

// OUT: the amount of competitors
int CStageRaceDoc::CompetitorsCount() const
{
	return m_competitors.GetCount();
}

void CStageRaceDoc::CompetitorsApplyMask()
{
	CMaskApplyDlg dlgMask( this );
	Lock();
	if( dlgMask.DoModal() == IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();
		// Generate lists
		if( m_bGenerateAutomatically )
			GenerateCompetitors();
	}
	Unlock();
}

void CStageRaceDoc::CompetitorsCut(CArray<WORD,WORD>* pStaNos, CPtrArray* pComps)
{
	CompetitorsCopy( pStaNos, pComps );
	int i;

	Lock();

	for( i=0; i<pStaNos->GetSize(); i++ )
		CompetitorsDelete( pStaNos->GetAt(i) );

	Unlock();

	for( i=0; i<pComps->GetSize(); i++ )
		SpareCompetitorsDelete( (CCompetitor*)pComps->GetAt(i) );
}

void CStageRaceDoc::CompetitorsCopy(CArray<WORD,WORD>* pStaNos, CPtrArray* pComps)
{
	CString cClpbrd;
	int i;
	for( i=0; i<pStaNos->GetSize(); i++ )
	{
		CCompetitor cComp = CompetitorsGet( pStaNos->GetAt(i) );
		cClpbrd += cComp.GetClipboardRow();
	}
	for( i=0; i<pComps->GetSize(); i++ )
	{
		cClpbrd += ((CCompetitor*)pComps->GetAt(i))->GetClipboardRow();
	}
	cClpbrd += "\0";

	//put your text in source
	if(OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		TCHAR * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, (cClpbrd.GetLength()+1)*sizeof(TCHAR));
		buffer = (TCHAR*)GlobalLock(clipbuffer);
		_tcscpy(buffer, cClpbrd);
		GlobalUnlock(clipbuffer);
		SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,clipbuffer);
		CloseClipboard();
	}
}

TCHAR CStageRaceDoc::CompetitorsPasteGetChar(char *pStr, int width)
{
    TCHAR tchar;
	switch( width )
	{
		case 2:
			mbstowcs(&tchar, pStr, 1);
			break;
		case 1:
		default:
			tchar = (TCHAR)0xFF&pStr[0];
			// 0xFF to make sure no high byte crap gets into our string
	}
	return tchar;
}

void CStageRaceDoc::CompetitorsPaste(bool bWithStaNos)
{
	BOOL bFirstAsked = TRUE;
	BOOL bFirstRealCompetitor = TRUE;
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Open the clipboard
	OpenClipboard(NULL);

	// Get the clipboard data handle
	int nOffset = 0;
	int nWidth = 2;
	HANDLE hData = GetClipboardData(CF_UNICODETEXT);

	if( hData==NULL )
	{
		nWidth = 1;
		hData = GetClipboardData(CF_TEXT);
	}

	if(	hData!=NULL )
	{

		// Get the clipboard data
		LPVOID lpData = GlobalLock(hData);

		try
		{
			CMsgBoxBeforePaste dlgMsgBox;
			// Set up a character string for the clipboard data
			char* pStr4Delete = new char[256];
			char* pStr = pStr4Delete;
			pStr = (char*)lpData;

			// Read out the string until null terminator
			while (CompetitorsPasteGetChar(pStr,nWidth) != '\0')
			{
				// Keeps track of the no of tabs
				int tabcounter = 0;
				// Temporarily CString variables for integers/bools
				CString tempStaNo, tempTeam, tempMask1, tempMask2, tempMask3, tempMask4, tempMask5, tempMask6, tempMask7, tempMask8, tempMask9, tempMask10;
				// Target competitor
	 			CCompetitor aCompetitor;

				// Extract the column values from the clipboard string
				while (CompetitorsPasteGetChar(pStr,nWidth) != '\r')
				{
					// If a tab occures...
					while (CompetitorsPasteGetChar(pStr,nWidth) == '\t')
					{
						tabcounter++;	// ... we go on to the next column
						pStr+=nWidth;	// and forget about the \t character

						if( tabcounter==1 )
						{
							if(_ttoi(tempStaNo)==0)
							{
								CString test = tempStaNo;
								test.TrimLeft();
								test.TrimRight();
								if( test != "0" )
								{
									aCompetitor.m_competitor = tempStaNo;
									tabcounter++;
								}
							}
						}
					}

					// Handle the actual characters
					switch(tabcounter)
					{
						case 0: tempStaNo					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 1: aCompetitor.m_competitor	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 2: tempTeam					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 3: aCompetitor.m_countryCode	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 4: aCompetitor.m_UCICode		+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 5: aCompetitor.m_license		+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 6: aCompetitor.m_category		+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 7: tempMask1					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 8: tempMask2					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 9: tempMask3					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 10: tempMask4					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 11: tempMask5					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 12: tempMask6					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 13: tempMask7					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 14: tempMask8					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 15: tempMask9					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 16: tempMask10					+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
					} 
					if (CompetitorsPasteGetChar(pStr,nWidth) != '\r')
						pStr+=nWidth; // Go on to the next character
				}

				// Make up all the competitor members
				aCompetitor.m_staNo = _ttoi( tempStaNo );
				if ( aCompetitor.m_staNo > 65535 ) aCompetitor.m_staNo = 65535;
				if ( aCompetitor.m_staNo <     0 ) aCompetitor.m_staNo = 65535;
				if ( !bWithStaNos                ) aCompetitor.m_staNo = 0;

				aCompetitor.m_countryCode.MakeUpper();
				aCompetitor.m_UCICode.MakeUpper();
				aCompetitor.m_license.MakeUpper();

				aCompetitor.m_competitor = aCompetitor.m_competitor.Left(50); // Allowed length
				aCompetitor.m_countryCode = aCompetitor.m_countryCode.Left(3);
				aCompetitor.m_UCICode = aCompetitor.m_UCICode.Left(11);
				aCompetitor.m_license = aCompetitor.m_license.Left(11);
				aCompetitor.m_category = aCompetitor.m_category.Left(11);

				aCompetitor.m_competitor.TrimLeft();
				aCompetitor.m_countryCode.TrimLeft();
				aCompetitor.m_UCICode.TrimLeft();
				aCompetitor.m_license.TrimLeft();
				aCompetitor.m_category.TrimLeft();
				aCompetitor.m_competitor.TrimRight();
				aCompetitor.m_countryCode.TrimRight();
				aCompetitor.m_UCICode.TrimRight();
				aCompetitor.m_license.TrimRight();
				aCompetitor.m_category.TrimRight();

				tempMask1.TrimLeft(); // Throw all spaces out of these temporarily strings
				tempMask2.TrimLeft();
				tempMask3.TrimLeft();
				tempMask4.TrimLeft();
				tempMask5.TrimLeft();
				tempMask6.TrimLeft();
				tempMask7.TrimLeft();
				tempMask8.TrimLeft();
				tempMask9.TrimLeft();
				tempMask10.TrimLeft();
				tempMask1.TrimRight();
				tempMask2.TrimRight();
				tempMask3.TrimRight();
				tempMask4.TrimRight();
				tempMask5.TrimRight();
				tempMask6.TrimRight();
				tempMask7.TrimRight();
				tempMask8.TrimRight();
				tempMask9.TrimRight();
				tempMask10.TrimRight();

				if ( tempMask1!="" ) aCompetitor.m_mask1 = TRUE;	// If still characters in string
								else aCompetitor.m_mask1 = FALSE;	// after throwing away spaces,
				if ( tempMask2!="" ) aCompetitor.m_mask2 = TRUE;	// then there is something we will
								else aCompetitor.m_mask2 = FALSE;	// award with TRUE
				if ( tempMask3!="" ) aCompetitor.m_mask3 = TRUE;
								else aCompetitor.m_mask3 = FALSE;
				if ( tempMask4!="" ) aCompetitor.m_mask4 = TRUE;
								else aCompetitor.m_mask4 = FALSE;
				if ( tempMask5!="" ) aCompetitor.m_mask5 = TRUE;
								else aCompetitor.m_mask5 = FALSE;
				if ( tempMask6!="" ) aCompetitor.m_mask6 = TRUE;
								else aCompetitor.m_mask6 = FALSE;
				if ( tempMask7!="" ) aCompetitor.m_mask7 = TRUE;
								else aCompetitor.m_mask7 = FALSE;
				if ( tempMask8!="" ) aCompetitor.m_mask8 = TRUE;
								else aCompetitor.m_mask8 = FALSE;
				if ( tempMask9!="" ) aCompetitor.m_mask9 = TRUE;
								else aCompetitor.m_mask9 = FALSE;
				if ( tempMask10!="" ) aCompetitor.m_mask10 = TRUE;
								else aCompetitor.m_mask10 = FALSE;

				if( !bFirstAsked || dlgMsgBox.DoModal()==IDOK )
				{
					bFirstAsked = FALSE;

					//Search team
					if(tempTeam=="")
					{
						aCompetitor.m_pTeam = NULL;
					}
					else
					{
						tempTeam.TrimLeft();
						tempTeam.TrimRight();

						//Search for a matching team
						POSITION hPos;
						CTeam* pTeam = NULL;
						
						aCompetitor.m_pTeam=NULL; //Indicates wheter a team has been assigned
						hPos = TeamsGetStartPosition();
						while(hPos)
						{
							//Get the team pointer
							TeamsIterate(hPos, (const CTeam*&)pTeam);
							//Check for a match in the team-code or team-name
							if(!tempTeam.CompareNoCase(pTeam->m_code) || !tempTeam.CompareNoCase(pTeam->m_name))
							{
								aCompetitor.m_pTeam = pTeam;
								break;
							}
						}
						if(aCompetitor.m_pTeam==NULL)
						{
							//No matching team found
							//Do dynamic creation
							TeamsNew( FALSE, &aCompetitor.m_pTeam, &tempTeam, &tempTeam, dlgMsgBox.m_withoutTeamInput==TRUE );
						}
					}

					//Store the new (spare) competitor
					if( aCompetitor.m_staNo )
					{
						bFirstRealCompetitor = FALSE;

						Lock();

						// Put our new competitor into the document
						m_competitors.Insert( aCompetitor );

						Unlock();
					}
					else
					{
						CCompetitor* pNewCompetitor = new CCompetitor( aCompetitor );
						// Insert the temporarely original object into the document's spare competitor list
						m_spareCompetitors.SetAt(pNewCompetitor, pNewCompetitor);
					}

					// Forget about the row terminators, so we can go on with a fresh, new line
					pStr+=nWidth; // for \r
					pStr+=nWidth; // for \n

					// Set the document's modified flag
					SetModifiedFlag();
				}
				else
				{
					pStr = NULL;
					delete pStr4Delete;
					CloseClipboard();
					return;
				}
			}
			pStr = NULL;
			delete pStr4Delete;

			if( !bFirstRealCompetitor )
			{
				// Generate lists
				if( m_bGenerateAutomatically )
					GenerateCompetitors();
			}
			if( !bFirstAsked )
			{
				// Update all the views
				CUpdateViewHint UVH( UV_INVALIDATEALL );
				UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );
			}
		}
		catch(...)
		{
			MessageBox( NULL, LoadStr( IDS_MBC_21 ), LoadStr( IDS_MBT_21 ), MB_OK|MB_ICONEXCLAMATION );
		}
	}
	else
	{
		MessageBox( NULL, LoadStr( IDS_MBC_21 ), LoadStr( IDS_MBT_21 ), MB_OK|MB_ICONEXCLAMATION );
	}

	// Close the clipboard
	CloseClipboard();
}

BOOL CStageRaceDoc::CompetitorsCanPaste() const
{
	OpenClipboard(NULL);
	BOOL b = (BOOL)GetClipboardData( CF_TEXT )
		| (BOOL)GetClipboardData( CF_UNICODETEXT );
	CloseClipboard();
	return b;
}

// OUT: the StaNo of the new competitor
void CStageRaceDoc::CompetitorsNew(BOOL bRepeatedly)
{
	bool bGenerateRequired = false;
	// Repeat "if" it's intended as an "iterating add"
	// "else" do it once
	do
	{
		// Make a new instant and give it the (highest StaNo) + 1
		CCompetitor* pNewCompetitor = new CCompetitor;
		pNewCompetitor->m_staNo = CompetitorsMaxStaNo() + 1;

		// Run the edit dialog and evaluate
		if( pNewCompetitor->Edit((CStageRaceDoc*const) this) == IDOK )
		{
			// If evaluated positive:

			if( pNewCompetitor->m_staNo )
			{
				Lock();

				// Insert the temporarely original object into the document's competitor list
				m_competitors.Insert( *pNewCompetitor );

				Unlock();

				// Update all the views
				CUpdateViewHint UVH( UV_ADDED, pNewCompetitor );
				UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );

				delete pNewCompetitor;

				bGenerateRequired = true;
			}
			else
			{
				// Insert the temporarely original object into the document's spare competitor list
				m_spareCompetitors.SetAt(pNewCompetitor, pNewCompetitor);

				// Update all the views
				CUpdateViewHint UVH( UV_ADDED, pNewCompetitor );
				UpdateAllViews( NULL, TI_SPARECOMPETITORS, (CObject*)&UVH );
			}

			// Set the document's modified flag
			SetModifiedFlag();
		}
		else
			break;
	}
	while(bRepeatedly);
	if( bGenerateRequired && m_bGenerateAutomatically )
		// Generate lists
		GenerateCompetitors();
}

// OUT: the highest currently available StaNo
int CStageRaceDoc::CompetitorsMaxStaNo() const
{
	m_competitors.LockRead();

	CCompetitor objCompetitor;
	POSITION hPos = m_competitors.GetStartPosition( );
	int nMaxStaNo = 0;

	// Iterate through the whole competitors list
	// to know the MaxStaNo
	for( int i = 1 ; i <= m_competitors.GetCount() ; i++ )
	{
		m_competitors.Iterate( hPos, objCompetitor );
		if ( nMaxStaNo < objCompetitor.m_staNo )
			nMaxStaNo = objCompetitor.m_staNo;
	}

	m_competitors.UnlockRead();

	return nMaxStaNo;
}

// IN: the StaNo that needs to be deleted
// OUT: success
bool CStageRaceDoc::CompetitorsDelete(int nStaNo)
{
	// Check if the competitor exists
	if(CompetitorsExist( nStaNo ))
	{
		// Check if the competitor can be deleted
		if( !CompetitorsInUse(nStaNo) )
		{
			Lock();

			// Remove the competitor from the document's competitors list
			m_competitors.Remove(nStaNo);

			Unlock();

			// Set the document's modified flag
			SetModifiedFlag();

			// Generate lists
			if( m_bGenerateAutomatically )
				GenerateCompetitors();

			// Update all the views
			CUpdateViewHint UVH( UV_DELETED, (CObject*)&nStaNo );
			UpdateAllViews( NULL, TI_COMPETITORS, (CObject*)&UVH );

			return true;
		}
		else
			// Error: couldn't be deleted
			MessageBox( NULL, LoadStr( IDS_MBC_16 ), LoadStr( IDS_MBT_16 ), MB_OK | MB_ICONINFORMATION);
	}
	else
		// Error: doesn't exist
		MessageBox( NULL, LoadStr( IDS_MBC_15 ), LoadStr( IDS_MBT_15 ), MB_OK | MB_ICONERROR);
	return false;
}

// IN: the StaNo of which the existence needs to be checked
// OUT: is available
bool CStageRaceDoc::CompetitorsExist(int nStaNo) const
{
	CCompetitor aComp;
	return m_competitors.Exist( nStaNo );
}

// IN: the StaNo for which a mask needs to be set/reset,
//  the no. of the involved mask (1|2|3) and the new value
void CStageRaceDoc::CompetitorsSetMask(int nStaNo, char nMask, bool bOn/* = TRUE*/, bool bSuppressFormalities/* = TRUE*/, bool bSuppressLocks/* = FALSE*/)
{
	if( CompetitorsExist( nStaNo ) )
	{
		CCompetitor aComp = CompetitorsGet( nStaNo );
		aComp.SetMask(nMask,bOn);

		if( !bSuppressLocks )
			Lock();

		m_competitors.Insert( aComp );

		if( !bSuppressLocks )
			Unlock();

		// Made optional for performance reasons
		if( !bSuppressFormalities )
		{
			// Set the document's modified flag
			SetModifiedFlag();
			// Generate lists
			if( m_bGenerateAutomatically )
				GenerateCompetitors();
		}
	}
}

// IN: the StaNo of which the use in stages needs to be checked
// OUT: is used
bool CStageRaceDoc::CompetitorsInUse(int nStaNo)
{
	bool bRet = false;
	// Iterate the entire first stage in order to find the team
	if( StagesFullCount() )
		if( StagesGet(1)->CountHalfStages() )
			if( StagesGet(1, 1)->m_arrival.Exist(nStaNo) )
				bRet = true;

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// TEAMS FUNCTIONS

bool CStageRaceDoc::TeamsCleanupHelper(CTeam* pTeam, CLEANUPCOMPETITORS clc)
{
	bool bDirty = false;
	if( clc & CLC_CLEANUPCOMMAS )
	{
		// team name
		CString old = pTeam->m_name;

		pTeam->m_name.Replace( TEXT(","), TEXT(", ") );
		while( pTeam->m_name.Replace( TEXT(",  "), TEXT(", ") ) );
		while( pTeam->m_name.Replace( TEXT(" ,"), TEXT(",") ) );

		pTeam->m_name.Replace( TEXT(";"), TEXT("; ") );
		while( pTeam->m_name.Replace( TEXT(";  "), TEXT("; ") ) );
		while( pTeam->m_name.Replace( TEXT(" ;"), TEXT(";") ) );

		if( old != pTeam->m_name )
			bDirty = true;

		// manager
		old = pTeam->m_manager;

		pTeam->m_manager.Replace( TEXT(","), TEXT(", ") );
		while( pTeam->m_manager.Replace( TEXT(",  "), TEXT(", ") ) );
		while( pTeam->m_manager.Replace( TEXT(" ,"), TEXT(",") ) );

		pTeam->m_manager.Replace( TEXT(";"), TEXT("; ") );
		while( pTeam->m_manager.Replace( TEXT(";  "), TEXT("; ") ) );
		while( pTeam->m_manager.Replace( TEXT(" ;"), TEXT(";") ) );

		if( old != pTeam->m_manager )
			bDirty = true;
	}
	if( clc & CLC_CAPITALIZEBEFORECOMMA )
	{
		int i = pTeam->m_manager.Find( ',' );
		if( i!=-1 )
		{
			CString old = pTeam->m_manager;
			pTeam->m_manager.MakeUpper();
			pTeam->m_manager =
				pTeam->m_manager.Left( i )+old.Mid( i );
			if( old != pTeam->m_manager )
				bDirty = true;
		}
	}
	if( clc & CLC_REMOVEREPEATEDSPACES )
	{
		while(pTeam->m_name.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pTeam->m_manager.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
		while(pTeam->m_country.Replace(TEXT("  "), TEXT(" ")))
			bDirty = true;
	}
	if( clc & CLC_REMOVESPACESAROUND )
	{
		int n = pTeam->m_name.GetLength()+
			pTeam->m_manager.GetLength()+
			pTeam->m_country.GetLength();

		pTeam->m_name.TrimLeft();
		pTeam->m_manager.TrimLeft();
		pTeam->m_country.TrimLeft();

		pTeam->m_name.TrimRight();
		pTeam->m_manager.TrimRight();
		pTeam->m_country.TrimRight();

		if( n != pTeam->m_name.GetLength()+
			pTeam->m_manager.GetLength()+
			pTeam->m_country.GetLength() ) bDirty = true;
	}
	return bDirty;
}

void CStageRaceDoc::TeamsUpdate( CTeam* pTeam, TEAM_FIELD f, CString val )
{
	Lock();

	switch( f )
	{
		case TF_CODE:
			val.MakeUpper();
			val = val.Left(3);
			// Check whether the 'Code' has been entered
			if(!val.IsEmpty())
			{
				//Check whether the 'Code' is unique
				if( TeamsExist(val)
						&& (TeamsGet( val )!=pTeam) )
					//The code was found and it was from a different team
					//Cancel this team with the same code
					MessageBox(NULL, LoadStr( IDS_MBC_62 ), LoadStr( IDS_MBT_62 ), MB_OK | MB_ICONINFORMATION);
				else
					pTeam->m_code = val;
			}
			break;
		case TF_NAME:
			pTeam->m_name = val;
			break;
		case TF_COUNTRY:
			pTeam->m_country = val;
			break;
		case TF_MANAGER:
			pTeam->m_manager = val;
			break;
	}

	Unlock();

	// Update all the views
	CUpdateViewHint UVH( UV_UPDATED, pTeam );
	UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );
	// Set the document's modified flag
	SetModifiedFlag();
	// Generate lists
	if( m_bGenerateAutomatically )
		GenerateCompetitors();
}

void CStageRaceDoc::TeamsCut(CArray<CTeam*,CTeam*>* pTeams)
{
	TeamsCopy( pTeams );

	Lock();

	for( int i=0; i<pTeams->GetSize(); i++ )
		TeamsDelete( pTeams->GetAt(i) );

	Unlock();
}

void CStageRaceDoc::TeamsCopy(CArray<CTeam*,CTeam*>* pTeams)
{
	CString cClpbrd;
	for( int i=0; i<pTeams->GetSize(); i++ )
	{
		cClpbrd += pTeams->GetAt(i)->GetClipboardRow();
	}
	cClpbrd += "\0";

	//put your text in source
	if(OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		TCHAR * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, (cClpbrd.GetLength()+1)*sizeof(TCHAR));
		buffer = (TCHAR*)GlobalLock(clipbuffer);
		_tcscpy(buffer, cClpbrd);
		GlobalUnlock(clipbuffer);
		SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,clipbuffer);
		CloseClipboard();
	}
}

void CStageRaceDoc::TeamsPaste()
{
	BOOL bFirst = TRUE;
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Open the clipboard
	OpenClipboard(NULL);

	// Get the clipboard data handle
	int nWidth = 2;
	HANDLE hData = GetClipboardData(CF_UNICODETEXT);

	if( hData==NULL )
	{
		nWidth = 1;
		hData = GetClipboardData(CF_TEXT);
	}

	if(	hData!=NULL )
	{

		// Get the clipboard data
		LPVOID lpData = GlobalLock(hData);

		try
		{
			// Set up a char string for the clipboard data
			char* pStr4Delete = new char[256];
			char* pStr = pStr4Delete;
			pStr = (char*)lpData;

			// Read out the string until null terminator
			while (CompetitorsPasteGetChar(pStr,nWidth) != '\0')
			{
				// Keeps track of the no of tabs
				int tabcounter = 0;
				// Target team
	 			CTeam aTeam;

				// Extract the column values from the clipboard string
				while (CompetitorsPasteGetChar(pStr,nWidth) != '\r')
				{
					// If a tab occures...
					while (CompetitorsPasteGetChar(pStr,nWidth) == '\t')
					{
						tabcounter++;	// ... we go on to the next column
						pStr+=nWidth;	// and forget about the \t character
					}

					// Handle the actual characters
					switch(tabcounter)
					{
						case 0: aTeam.m_code	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 1: aTeam.m_name	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 2: aTeam.m_manager	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
						case 3: aTeam.m_country	+= CString( CompetitorsPasteGetChar(pStr,nWidth) );
						break;
					} 
					if (CompetitorsPasteGetChar(pStr,nWidth) != '\r')
						pStr+=nWidth; // Go on to the next character
				}

				// Make up all the team members
				aTeam.m_code.MakeUpper();

				aTeam.m_code.TrimLeft();
				aTeam.m_name.TrimLeft();
				aTeam.m_country.TrimLeft();
				aTeam.m_country.TrimLeft();
				aTeam.m_code.TrimRight();
				aTeam.m_name.TrimRight();
				aTeam.m_country.TrimRight();
				aTeam.m_country.TrimRight();

				aTeam.m_code = aTeam.m_code.Left(3);

				if( aTeam.m_code.GetLength() )
				{
					if ( !bFirst || MessageBox( NULL, LoadStr( IDS_MBC_19 ), LoadStr( IDS_MBT_19 ), MB_YESNO|MB_DEFBUTTON2 )==IDYES )
					{
						bFirst = FALSE;
						// Put our new team into the document
						// Check whether the 'Code' is unique
						CTeam* pStoreTeam = NULL;
						if(TeamsExist(aTeam.m_code))
						{
							pStoreTeam = ((CTeam*)TeamsGet(aTeam.m_code));
							*pStoreTeam = aTeam;
						}
						else
						{
							pStoreTeam = new CTeam(aTeam);
							
							Lock();

							m_teams.SetAt(aTeam.m_code, pStoreTeam);

							Unlock();
						}

						// Update all the views
						CUpdateViewHint UVH( UV_UPDATED, pStoreTeam );
						UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );
					}
					else
					{
						CloseClipboard();
						return;
					}
				}

				// Forget about the row terminators, so we can go on with a fresh, new line
				pStr+=nWidth; // for \r
				pStr+=nWidth; // for \n
			}
			pStr = NULL;
			delete pStr4Delete;

			if( !bFirst )
			{
				// Set the document's modified flag
				SetModifiedFlag();
				// Generate lists
				if( m_bGenerateAutomatically )
					GenerateCompetitors();
			}
		}
		catch(...)
		{
			MessageBox( NULL, LoadStr( IDS_MBC_21 ), LoadStr( IDS_MBT_21 ), MB_OK|MB_ICONEXCLAMATION );
		}
	}
	else
	{
		MessageBox( NULL, LoadStr( IDS_MBC_21 ), LoadStr( IDS_MBT_21 ), MB_OK|MB_ICONEXCLAMATION );
	}

	// Close the clipboard
	CloseClipboard();
}

// IN: a pointer to the team that needs to be edited
void CStageRaceDoc::TeamsEdit(CTeam* pTeam)
{
	// Run the dialog
	if( pTeam->Edit((CStageRaceDoc*const) this, m_hGenerateSemaphore_ChangeToDoc) == IDOK )
	{
		// If evaluated positive:

		// Set the document's modified flag
		SetModifiedFlag();
		// Generate lists
		if( m_bGenerateAutomatically )
			GenerateCompetitors();

		// Update all the views
		CUpdateViewHint UVH( UV_UPDATED, pTeam );
		UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );
	}
}

// OUT: the position of the first team
POSITION CStageRaceDoc::TeamsGetStartPosition() const
{
	return m_teams.GetStartPosition();
}

// IN: the current position
// OUT: the team at this position and an updated position
void CStageRaceDoc::TeamsIterate(POSITION& nPos, const CTeam*& rpTeam) const
{
	CString cDummy;
	CTeam * pTeam;
	m_teams.GetNextAssoc( nPos, cDummy, pTeam );
	rpTeam = pTeam;
}

// OUT: the amount of teams
int CStageRaceDoc::TeamsCount() const
{
	return m_teams.GetCount();
}

// OUT: the amount of teams that actually have competitors attached
int CStageRaceDoc::TeamsCountUsed() const
{
	int nCount = 0;
	POSITION nPos = m_teams.GetStartPosition();
	while( nPos )
	{
		CString cDummy;
		CTeam * pTeam;
		m_teams.GetNextAssoc( nPos, cDummy, pTeam );
		
		if( TeamsInUse(pTeam) ) nCount++;
	}
	return nCount;
}

// IN: suggestions for team code and team name
void CStageRaceDoc::TeamsNew( BOOL bRepeatedly/*=FALSE*/, CTeam** ppNewTeam/*=NULL*/, CString* pcCodeSuggestion/*=NULL*/, CString* pcNameSuggestion/*=NULL*/, bool bSuppressEdit/*=false*/)
{
	if( ppNewTeam )
		*ppNewTeam = NULL;

	// Repeat "if" it's intended as an "iterating add"
	// "else" do it once
	do
	{
		CTeam* pNewTeam = NULL;
		// Make a new instant
		CEditTeam aNewEditTeam;

		// Set some suggestions
		if( pcCodeSuggestion )
		{
			aNewEditTeam.m_szCode = *pcCodeSuggestion;
			aNewEditTeam.m_szCode = aNewEditTeam.m_szCode.Left(3);
			aNewEditTeam.m_szCode.MakeUpper();
			if(bSuppressEdit)
			{
				// Let's do extra our best to compose
				// a code suggestion so that the edit
				// dialog can indeed be suppressed
				if( TeamsExist(aNewEditTeam.m_szCode)
					&& pcNameSuggestion )
				{
					// Compose an array consisting
					// of the single words that
					// are in the team name
					CString team = *pcNameSuggestion;
					team.MakeUpper();
					team.TrimRight();

					CArray<CString,CString> words;
					int i=0;
					while( (i=team.FindOneOf(TEXT("-_/ \\")))!=-1 )
					{
						// We found a word, so let's store it
						CString foundword = team.Left(i);
						foundword.TrimLeft();
						if( foundword.GetLength() )
							words.Add( team.Left(i) );

						// Set up to get the next word
						team = team.Mid(i+1);
						team.TrimLeft();
					}
					// Get the last word
					if( team.GetLength() )
						words.Add( team );

					if( words.GetAt(0)
							.CompareNoCase(TEXT("team"))==0 )
						words.RemoveAt(0);

					// Try to make a team code from
					// the found words 'initials'
					if( words.GetSize()>=3 )
					{
						aNewEditTeam.m_szCode = 
							words.GetAt(0).Left(1) +
							words.GetAt(1).Left(1) +
							words.GetAt(2).Left(1);
						aNewEditTeam.m_szCode.TrimRight();
					}
					if( TeamsExist(aNewEditTeam.m_szCode)
						&& words.GetSize()>=2
						&& words.GetAt(1).GetLength()>=2 )
					{
						aNewEditTeam.m_szCode = 
							words.GetAt(0).Left(1) +
							words.GetAt(1).Left(2);
						aNewEditTeam.m_szCode.TrimRight();
					}
					if( TeamsExist(aNewEditTeam.m_szCode)
						&& words.GetSize()>=2
						&& words.GetAt(0).GetLength()>=2 )
					{
						aNewEditTeam.m_szCode = 
							words.GetAt(0).Left(2) +
							words.GetAt(1).Left(1);
						aNewEditTeam.m_szCode.TrimRight();
					}
					if( TeamsExist(aNewEditTeam.m_szCode) )
					{
						aNewEditTeam.m_szCode =
							words.GetAt(0).Left(3);
						aNewEditTeam.m_szCode.TrimRight();
					}
				}
			}
		}
		if( pcNameSuggestion )
			aNewEditTeam.m_szName = *pcNameSuggestion;

		// Set the pointer to the document object
		aNewEditTeam.m_pStageRaceDoc = this;
		aNewEditTeam.m_pTeam = NULL;
		// Run the edit dialog and evaluate
		if( (bSuppressEdit&&!TeamsExist(aNewEditTeam.m_szCode))
			|| (aNewEditTeam.DoModal() == IDOK) )
		{
			// If evaluated positive:
			//   update the actual team in the document
			pNewTeam = new CTeam;
			*pNewTeam=aNewEditTeam;

			Lock();

			m_teams.SetAt(pNewTeam->m_code, pNewTeam);

			Unlock();

			// Set the document's modified flag
			SetModifiedFlag();

			// Update all the views
			CUpdateViewHint UVH( UV_ADDED, pNewTeam );
			UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );

			// Fill the team pointer
			if( ppNewTeam )
				*ppNewTeam = pNewTeam;
		}
		else
			break;
	}
	while(bRepeatedly);
}

// IN: a pointer to the team that needs to be deleted
bool CStageRaceDoc::TeamsDelete(CTeam* pTeam)
{
	// Check if the team can be deleted
	if( !TeamsInUse(pTeam) )
	{
		// Remove the team from the teams list
		POSITION nPos = m_teams.GetStartPosition();
		while( nPos )
		{
			CString rKey;
			CTeam* pValue;
			m_teams.GetNextAssoc( nPos, rKey, pValue );
			if( pValue==pTeam )
			{
				Lock();

				m_teams.RemoveKey( rKey );

				Unlock();
			}
		}
		// Delete the team from memory
		delete pTeam;

		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_DELETED, pTeam );
		UpdateAllViews( NULL, TI_TEAMS, (CObject*)&UVH );

		pTeam = NULL;

		return true;
	}
	else
	{
		// Error: couldn't be deleted
		CString szMsg;
		szMsg = LoadStr( IDS_DIV21 ) + pTeam->m_code + LoadStr( IDS_DIV22 );
		MessageBox(NULL, szMsg, LoadStr( IDS_DIV23 ), MB_OK | MB_ICONINFORMATION);

		return false;
	}
}

// IN: a pointer to the team of which the use in competitors needs
//  to be checked
// OUT: is used
bool CStageRaceDoc::TeamsInUse(CTeam *pTeam) const
{
	bool bRet = false;

	POSITION hPos;
	CCompetitor objCompetitor;
	
	// Iterate the entire competitors list in order to find the team
	DWORD nState=0;
	while(CompetitorsIterateSorted(nState, objCompetitor))
	{
		
		if(objCompetitor.m_pTeam == pTeam)
		{
			bRet = true;
			break;
		}
	}
	// Iterate the entire competitors list in order to find the team
	hPos = SpareCompetitorsGetStartPosition();
	while(hPos)
	{
		objCompetitor = *SpareCompetitorsIterate(hPos);
		if(objCompetitor.m_pTeam == pTeam)
		{
			bRet = true;
			break;
		}
	}
	
	return bRet;
}

// IN: the team code of which the existence needs to be checked
// OUT: is available
bool CStageRaceDoc::TeamsExist(CString sCode) const
{
	return TeamsGet(sCode)!=NULL;
}

// IN: the team code that needs to be retrieved
// OUT: a pointer to the matching team
const CTeam* CStageRaceDoc::TeamsGet(CString sCode) const
{
	CTeam* pTeam;
	POSITION nPos = TeamsGetStartPosition();
	while( nPos )
	{
		TeamsIterate( nPos, (const CTeam*&)pTeam );
		if( pTeam->m_code==sCode )
			return pTeam;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// EXPORT FUNCTIONS

void CStageRaceDoc::ExportScanovision()
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// We create a file exception
	CFileException objFileException;
	CStdioFile objTheFile;

	LONG er;
	CString czPath;
	CSRRegKey reg;
	er = reg.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );
	if( er == ERROR_SUCCESS )
	{
		czPath = MakePathUsable( reg.GetString( TEXT("Omega Scan'O'Vision"), TEXT("") ) );
	}

	//LSTCONC - Competitors list
		// We create the object for the document to export
		CTextOutput objOutpConc( czPath, TEXT("LstConc"), 3, this );
		// We fill the document
		ExportHelperCompetitors( &objOutpConc, 1, 1 );

		objOutpConc.Finish();

	//LSTSTYLE - List of stage styles
		if ( !objTheFile.Open( czPath+"LstStyle.txt", CFile::modeCreate |   
				  CFile::typeText | CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstStyle.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			objTheFile.WriteString( TEXT("\"idStyle\";\"Style\";\"StyleAbrév\"\n") );
			objTheFile.WriteString( TEXT("1;\"Normal half stage\";\"HST\"\n") );
			objTheFile.WriteString( TEXT("2;\"Time trial\";\"TTR\"\n") );
			objTheFile.Close();
		}

	//LSTCAT - List of individuals categories (not used)
		if ( !objTheFile.Open( czPath+"LstCat.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstCat.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			objTheFile.WriteString( TEXT("\"Catégorie\";\"AbrevCat\"\n") );
			objTheFile.Close();
		}

	//LSTLONG - List of stage lengths
		if ( !objTheFile.Open( czPath+"LstLong.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstLong.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			TCHAR buffer[10];
			int nRow=1;

			objTheFile.WriteString( TEXT("\"idLong\";\"Longueur\";\"Mlongueur\";\"Relais\"\n") );
			for( int i=1; i<=StagesFullCount(); i++ )
				for( int j=1; j<=StagesGet(i)->CountHalfStages(); j++ )
				{
					_itot( nRow++, buffer, 10 );
					objTheFile.WriteString( CString(buffer) );	//idLong
					objTheFile.WriteString( TEXT(";\"") );

					if( StagesGet( i, j )->m_stageType==ST_NORMAL )
					{
						_itot( StagesGet( i, j )->m_rounds, buffer, 10 );
						objTheFile.WriteString( CString(buffer) );
						objTheFile.WriteString( TEXT("x") );
						_itot( StagesGet( i, j )->m_distance, buffer, 10 );
						objTheFile.WriteString( CString(buffer) );
						objTheFile.WriteString( TEXT("m\";") );
						_itot( StagesGet( i, j )->m_distance * StagesGet( i, j )->m_rounds, buffer, 10 );
						objTheFile.WriteString( CString(buffer) );	//Mlongueur
					}
					else
					{
						_itot( StagesGet( i, j )->m_distance, buffer, 10 );
						objTheFile.WriteString( CString(buffer) );
						objTheFile.WriteString( TEXT("m\";") );
						objTheFile.WriteString( CString(buffer) );	//Mlongueur
					}

					objTheFile.WriteString( TEXT("\";1\n") );		//Relais
				}
			objTheFile.Close();
		}

	//LSTNAT - List of nationalities, used for teams
		if ( !objTheFile.Open( czPath+"LstNat.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstNat.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			int nRow=1;

			objTheFile.WriteString( TEXT("\"Nation\";\"AbrevNat\";\"FichierDrapeau\"\n") );

			POSITION nPos = TeamsGetStartPosition();
			while( nPos )
			{
				CString czCode;
				CTeam* pTeam;
				TeamsIterate( nPos, (const CTeam*&)pTeam );
				objTheFile.WriteString( "\""+NoQuotes(pTeam->m_name)+"\";\""+NoQuotes(pTeam->m_code)+"\";\n" );
			}

			objTheFile.Close();
		}

	//LSTTITPR - List of events, full stages/half stages
		if ( !objTheFile.Open( czPath+"LstTitPr.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstTitPr.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			TCHAR buffer[10];

			objTheFile.WriteString( TEXT("\"Event\";\"Round\";\"Titre\";\"Sponsor\"\n") );
			int i;
			for( i=1; i<=StagesFullCount(); i++ )
				for( int j=1; j<=StagesGet(i)->CountHalfStages(); j++ )
				{
					_itot( i, buffer, 10 );
					objTheFile.WriteString( CString(buffer) ); //Event
					objTheFile.WriteString( TEXT(";") );
					_itot( j, buffer, 10 );
					objTheFile.WriteString( CString(buffer) ); //Round
					objTheFile.WriteString( TEXT(";\"") );
					objTheFile.WriteString( NoQuotes( StagesGet( i, j )->m_title+TEXT(" (")+((CSettingsGeneral*)m_allsettings.GetSettings(SETT_GENERAL))->m_eventName+TEXT(")") ) ); //Titre
					objTheFile.WriteString( TEXT("\";\"StageRace ")+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()+TEXT("\"\n") ); //Sponsor
				}
			for( ; i<=StagesFullCount()+5; i++ )
			{
				_itot( i, buffer, 10 );
				objTheFile.WriteString( CString(buffer) );
				_itot( i-StagesFullCount(), buffer, 10 );
				objTheFile.WriteString( ";1;\"Test "+CString(buffer)+"\";\"StageRace "+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()+"\"\n" );
			}
			objTheFile.Close();
		}

	//LSTRACE - List of events, full stages/half stages
		if ( !objTheFile.Open( czPath+"LstRace.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstRace.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			TCHAR buffer[10];
			int nRow=1;

			objTheFile.WriteString( TEXT("\"Event\";\"Round\";\"NbHeat\";\"idLong\";\"idStyle\";\"AbrevCat\";\"Date\";\"Heure\";\"idJuge1\";\"idJuge2\"\n") );
			int i;
			for( i=1; i<=StagesFullCount(); i++ )
				for( int j=1; j<=StagesGet(i)->CountHalfStages(); j++ )
				{
					_itot( i, buffer, 10 );
					objTheFile.WriteString( CString(buffer) ); //Event
					objTheFile.WriteString( TEXT(";") );
					_itot( j, buffer, 10 );
					objTheFile.WriteString( CString(buffer) ); //Round
					objTheFile.WriteString( TEXT(";10;") ); //NbHeat
					_itot( nRow++, buffer, 10 );
					objTheFile.WriteString( CString(buffer) ); //idLong
					objTheFile.WriteString( TEXT(";") );
					if( StagesGet( i, j )->m_stageType==ST_NORMAL )
						objTheFile.WriteString( TEXT("1;") ); //idStyle
					else
						objTheFile.WriteString( TEXT("2;") ); //idStyle
					objTheFile.WriteString( TEXT(";") ); //AbrevCat
					objTheFile.WriteString( TEXT("\"-\";") ); //Date
					objTheFile.WriteString( TEXT("\"") + NoQuotes( StagesGet( i, j )->m_openingHour ) + TEXT("\";") ); //Heure
					objTheFile.WriteString( TEXT(";\n") ); //idJuge1;idJuge2
				}
			for( ; i<=StagesFullCount()+5; i++ )
			{
				_itot( i, buffer, 10 );
				objTheFile.WriteString( CString(buffer) );
				objTheFile.WriteString( TEXT(";1;5;0;;;\"-\";\"-\";\"-\";\"-\"\n") );
			}
			objTheFile.Close();
		}

	//LSTSTART - Starting list for all events/heats
		if ( !objTheFile.Open( czPath+"LstStart.txt", CFile::modeCreate |   
				  CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
		{
			MessageBox( NULL, LoadStr( IDS_MBC_7 )+"LstStart.txt", LoadStr( IDS_MBT_7 ), MB_OK );
		}
		else
		{
			TCHAR buffer[10];
			int nRow=1;

			objTheFile.WriteString( TEXT("\"Event\";\"Round\";\"Heat\";\"Lane\";\"NRelais\";\"idBib\"\n") );
			for( int i=1; i<=StagesFullCount(); i++ )
				for( int j=1; j<=StagesGet(i)->CountHalfStages(); j++ )
				{
					CArrival objArrival;
					CCompetitor objComp;

					int nLane=1;
					CHalfStage* pStage = StagesGet( i, j );
					// If this stage is a time trial, we retrieve starting order form the order list
					if ( pStage->m_stageType!=ST_NORMAL )
					{
						DWORD nState=0;
						while( pStage->m_timeTrialOrder.IterateSorted( nState, objArrival ) )
						{
							// Insert the competitor/arrival into the file
							objComp = CompetitorsGet( objArrival.m_staNo );
							if( !pStage->m_signOuts.Exist( objArrival.m_staNo ) )
							{
								for( int nHeat=1; nHeat<=10; nHeat++ )
								{
									_itot( i, buffer, 10 );
									objTheFile.WriteString( CString(buffer) );	//Event
									objTheFile.WriteString( TEXT(";") );
									_itot( j, buffer, 10 );
									objTheFile.WriteString( CString(buffer) );	//Round
									objTheFile.WriteString( TEXT(";") );
									_itot( nHeat, buffer, 10 );
									objTheFile.WriteString( CString(buffer) );	//Heat
									objTheFile.WriteString( TEXT(";") );
									_itot( nLane, buffer, 10 );
									objTheFile.WriteString( CString(buffer) );	//Lane
									objTheFile.WriteString( TEXT(";") );
 									objTheFile.WriteString( TEXT(";") );				//NRelais
									_itot( objArrival.m_staNo, buffer, 10 );
									objTheFile.WriteString( CString(buffer) );	//idBib
									objTheFile.WriteString( TEXT("\n") );
								}
								nLane++;
							}
						}
					}
					else
					{
						if ( StagesGetPrev( i, j )==NULL )
						// If a previous half stage does NOT exist, we get the main competitors list
						{
							int nMaxCount = CompetitorsCount();
							// Iterate our main competitors list
							for ( int comp=1, nSkipMap=1; // Retrieve all items once
									comp<=nMaxCount; comp++, nSkipMap++)
							{				
								while ( !CompetitorsExist( nSkipMap ) )
									nSkipMap++ ;
								objComp = CompetitorsGet( nSkipMap );
							
								// Insert the competitor/arrival into the file
								if( !pStage->m_signOuts.Exist( objComp.m_staNo ) )
								{
									for( int nHeat=1; nHeat<=10; nHeat++ )
									{
										_itot( i, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Event
										objTheFile.WriteString( TEXT(";") );
										_itot( j, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Round
										objTheFile.WriteString( TEXT(";") );
										_itot( nHeat, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Heat
										objTheFile.WriteString( TEXT(";") );
										_itot( nLane, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Lane
										objTheFile.WriteString( TEXT(";") );
										objTheFile.WriteString( TEXT(";") ); //NRelais
										_itot( objComp.m_staNo, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //idBib
										objTheFile.WriteString( TEXT("\n") );
									}
									nLane++;
								}
							};
						}
						else
						// If a previous half stage does exist, we only get the competitors
						//  that remain after the previous stage
						{
							DWORD nState=0;
							while( StagesGetPrev( i, j )->m_arrival.IterateSorted( nState, objArrival ) )
							{
								// Insert the competitor/arrival into the file
								objComp = CompetitorsGet( objArrival.m_staNo );
								if( !pStage->m_signOuts.Exist( objArrival.m_staNo ) )
								{
									for( int nHeat=1; nHeat<=10; nHeat++ )
									{
										_itot( i, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Event
										objTheFile.WriteString( TEXT(";") );
										_itot( j, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Round
										objTheFile.WriteString( TEXT(";") );
										_itot( nHeat, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Heat
										objTheFile.WriteString( TEXT(";") );
										_itot( nLane, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //Lane
										objTheFile.WriteString( TEXT(";") );
										objTheFile.WriteString( TEXT(";") ); //NRelais
										_itot( objArrival.m_staNo, buffer, 10 );
										objTheFile.WriteString( CString(buffer) ); //idBib
										objTheFile.WriteString( TEXT("\n") );
									}
									nLane++;
								}
							}
						}
					}
				}


			{// Just for scope
				int nLane=1;
				CCompetitor objComp;
				int nMaxCount = CompetitorsCount();
				// Iterate our main competitors list
				for ( int i=1, nSkipMap=1; // Retrieve all items once
						i<=nMaxCount; i++, nSkipMap++)
				{				
					while ( !CompetitorsExist( nSkipMap ) )
						nSkipMap++ ;
					objComp = CompetitorsGet( nSkipMap );
				
					// Insert the competitor/arrival into the file
					for( int nTest=(StagesFullCount())+1; nTest<=(StagesFullCount())+5; nTest++ )
						for( int nHeat=1; nHeat<=5; nHeat++ )
						{
							_itot( nTest, buffer, 10 );
							objTheFile.WriteString( CString(buffer) ); //Event
							objTheFile.WriteString( TEXT(";") );
							objTheFile.WriteString( TEXT("1;") ); //Round
							_itot( nHeat, buffer, 10 );
							objTheFile.WriteString( CString(buffer) ); //Heat
							objTheFile.WriteString( TEXT(";") );
							_itot( nLane, buffer, 10 );
							objTheFile.WriteString( CString(buffer) ); //Lane
							objTheFile.WriteString( TEXT(";") );
							objTheFile.WriteString( TEXT(";") ); //NRelais
							_itot( objComp.m_staNo, buffer, 10 );
							objTheFile.WriteString( CString(buffer) ); //idBib
							objTheFile.WriteString( TEXT("\n") );
						}
					nLane++;
				};
			}
			objTheFile.Close();
		}

}

void CStageRaceDoc::ExportFinishlynx()
{
	// We create a file exception
	CFileException objFileException;
	CStdioFile objTheFile;

	LONG er;
	CString czPath;
	CSRRegKey reg;
	er = reg.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );
	if( er == ERROR_SUCCESS )
	{
		czPath = MakePathUsable( reg.GetString( TEXT("Lynx FinishLynx"), TEXT("") ) );
	}

	if ( !objTheFile.Open( czPath+"Lynx.evt", CFile::modeCreate |   
		CFile::typeText | CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
	{
		MessageBox( NULL, LoadStr( IDS_MBC_7 )+"Lynx.evt", LoadStr( IDS_MBT_7 ), MB_OK );
	}
	else
	{
		// This will automatically display a wait cursor
		CWaitCursor objCursor;

		TCHAR buffer[10];
		int nRow=1;

		// Write the header
		objTheFile.WriteString( TEXT("; This file, 'lynx.evt', contains events and who is in them\n") );
		objTheFile.WriteString( TEXT("; This particular file has been generated by StageRace\n") );
		objTheFile.WriteString( TEXT("; based on StageRace file \"" + GetPathName() + "\"\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; Format:\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; event number, round number, heat number, event name\n") );
		objTheFile.WriteString( TEXT("; <tab, space, or comma>ID, lane, last name, first name, affiliation\n") );
		objTheFile.WriteString( TEXT("; <tab, space, or comma> .\n") );
		objTheFile.WriteString( TEXT("; <tab, space, or comma> .\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; or\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; event number, round number, heat number, event name\n") );
		objTheFile.WriteString( TEXT("; event number, round number, heat number, event name\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; Notes:\n") );
		objTheFile.WriteString( TEXT("\n") );
		objTheFile.WriteString( TEXT("; + Any line starting with a semicolon is ignored.\n") );
		objTheFile.WriteString( TEXT("; + In general, you can omit unnecessary or unknown information.\n") );
		objTheFile.WriteString( TEXT("; + To indicate no lane assignment leave the lane field blank or use a zero.\n") );
		objTheFile.WriteString( TEXT("; + To indicate no ID number you must put a zero in the ID field.\n") );
		objTheFile.WriteString( TEXT("; + If NO participants are listed after an event entry FinishLynx will\n") );
		objTheFile.WriteString( TEXT(";   attempt to locate each participant's information in the .ppl file\n") );
		objTheFile.WriteString( TEXT(";   when their ID number is entered.\n") );
		objTheFile.WriteString( TEXT("\n") );

		// Iterate all stages and half stages
		for( int i=1; i<=StagesFullCount(); i++ )
		{
			for( int j=1; j<=StagesGet(i)->CountHalfStages(); j++ )
			{
				_itot( i, buffer, 10 );
				objTheFile.WriteString( CString(buffer) ); //Event
				objTheFile.WriteString( TEXT(",") );
				_itot( j, buffer, 10 );
				objTheFile.WriteString( CString(buffer) ); //Round
				objTheFile.WriteString( TEXT(",") );
				objTheFile.WriteString( TEXT("1") ); //Heat
				objTheFile.WriteString( TEXT(",") );
				objTheFile.WriteString( NoQuotes( StagesGet( i, j )->m_title+TEXT(" (")+((CSettingsGeneral*)m_allsettings.GetSettings(SETT_GENERAL))->m_eventName+TEXT(")") ) ); //Event name
				objTheFile.WriteString( TEXT("\n") );

				CArrival objArrival;
				CCompetitor objComp;

				CHalfStage* pHalfStage = StagesGet( i, j );
				// Determine from which source the available's list has to be taken
				CStaNoObjectList* pAvail;
				if ( StagesGetPrev( i, j )==NULL )
					pAvail = &m_competitors;
				else
					pAvail = &StagesGetPrev( i, j )->m_arrival;

				const CAvailableList* pAvailList = NULL;
				if ( pHalfStage->m_stageType==ST_NORMAL )
					pAvailList = new CAvailableList( &pHalfStage->m_signOuts, pAvail );
				else
					pAvailList = new CAvailableList( &pHalfStage->m_signOuts, &pHalfStage->m_timeTrialOrder );

				// Iterate the half stage's competitor list
				DWORD nState=0;
				while( pAvailList->IterateSorted( nState, objArrival ) )
				{
					if( CompetitorsExist( objArrival.m_staNo ) )
					{
						CCompetitor objComp = CompetitorsGet(objArrival.m_staNo);

						objTheFile.WriteString( TEXT(",") ); //Indicate this to be a competitor
						_itot( objComp.m_staNo, buffer, 10 );
						objTheFile.WriteString( CString(buffer) ); //idBib
						objTheFile.WriteString( TEXT(",") );
						objTheFile.WriteString( TEXT("0") ); //Lane
						objTheFile.WriteString( TEXT(",") );
						objTheFile.WriteString( TEXT("\"") + NoQuotes( objComp.m_competitor ) + TEXT("\"") ); //Last name
						objTheFile.WriteString( TEXT(",") );
						objTheFile.WriteString( TEXT("\"-\"") ); //First name
						objTheFile.WriteString( TEXT(",") );
						if( objComp.m_pTeam )
							objTheFile.WriteString( TEXT("\"") + NoQuotes( objComp.m_pTeam->m_name ) + TEXT("\"") ); //Affiliation
						else
							objTheFile.WriteString( TEXT("\"\"") ); // Affiliation for competitor without team
						objTheFile.WriteString( TEXT("\n") );
					}
				}
			}
		}
	}
}

// IN: identifiers for the stage of which export is desired
void CStageRaceDoc::ExportChronx(int nFS, int nHS)
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );

	// We create the object for the document to export
	CTextOutput objOutp(
		MakePathUsable( reg.GetString( TEXT("AMB ChronX"), TEXT("") ) ),
		LoadStr(IDS_DIV53)+" "+CEventItem::StagesMakeIDString(nFS,nHS,this),
		2,
		this );

	// We fill the document
	ExportHelperCompetitors( &objOutp, nFS, nHS );

	objOutp.Finish();
}

// IN: identifiers for the stage of which export is desired
void CStageRaceDoc::ExportOptic(int nFS, int nHS)
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );

	// We create the object for the document to export
	CTextOutput objOutp(
		MakePathUsable( reg.GetString( TEXT("Alge OPTIc"), TEXT("") ) ),
		LoadStr(IDS_DIV53)+" "+CEventItem::StagesMakeIDString(nFS,nHS,this),
		1,
		this );

	// We fill the document
	ExportHelperCompetitors( &objOutp, nFS, nHS );

	objOutp.Finish();
}

// IN: identifiers for the stage of which export is desired
void CStageRaceDoc::ExportTTWare(int nFS, int nHS)
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );

	// We create the object for the document to export
	CTextOutput objOutp(
		MakePathUsable( reg.GetString( TEXT("Skunkware TT*Ware"), TEXT("") ) ),
		LoadStr(IDS_DIV53)+" "+CEventItem::StagesMakeIDString(nFS,nHS,this),
		4,
		this );

	// We fill the document
	ExportHelperCompetitors( &objOutp, nFS, nHS );

	objOutp.Finish();
}

// IN: a pointer to a CTextOutput object and the identifiers for a half stage
// OUT: the CTextOutput object is expanded with the competitors for the indicated half stage
void CStageRaceDoc::ExportHelperCompetitors(CTextOutput *pOutput, int nFS, int nHS)
{
	CHalfStage* pHalfStage = StagesGet(nFS,nHS);

	// Determine from which source the available's list has to be taken
	CStaNoObjectList* pAvail;
	if ( StagesGetPrev( nFS, nHS )==NULL )
		pAvail = &m_competitors;
	else
		pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

	const CAvailableList* pAvailList = NULL;
	if ( pHalfStage->m_stageType==ST_NORMAL )
		pAvailList = new CAvailableList( &pHalfStage->m_signOuts, pAvail );
	else
		pAvailList = new CAvailableList( &pHalfStage->m_signOuts, &pHalfStage->m_timeTrialOrder );

	// Iterate the half stage's competitor list
	CArrival objArrival;
	DWORD nState=0;
	while( pAvailList->IterateSorted( nState, objArrival ) )
	{
		if( CompetitorsExist( objArrival.m_staNo ) )
		{
			CCompetitor objComp = CompetitorsGet(objArrival.m_staNo);
			pOutput->Competitor( &objComp, &objArrival );
		}
	};
}

/////////////////////////////////////////////////////////////////////////////
// STAGES FUNCTIONS

// OUT: the amount of full stages
int CStageRaceDoc::StagesFullCount() const
{
	return m_fullStages.GetCount();
}

// IN: the identifier of the full stage of which the half stages count is required
// OUT: the amount of half stages of the particular full stage
int	CStageRaceDoc::StagesHalfCount(int nParentFS)
{
	return StagesGet(nParentFS)->CountHalfStages();
}

// OUT: the entire amount of half stages
int	CStageRaceDoc::StagesHalfCount()
{
	int nFS = 0;
	int cnt = 0;
	while( StagesGet( ++nFS ) )
		cnt += StagesGet( nFS )->CountHalfStages();
	return cnt;
}

// IN: the identifier of the full stage and half stage until which to count
// OUT: the amount of half stages up to and including the one pointed to
int CStageRaceDoc::StagesCountTo(int nSubjectFS, int nSubjectHS)
{
	int nFS = 0;
	int cnt = 0;
	while( StagesGet( ++nFS ) )
	{
		cnt += StagesGet( nFS )->CountHalfStages();
		if( nFS+1==nSubjectFS )
			break;
	}
	cnt += nSubjectHS;
	return cnt;
}

// IN: the new stages that has to be added
void CStageRaceDoc::StagesFullNew(CFullStage* pNewOne)
{
	Lock();

	m_fullStages.AddTail( *pNewOne );

	Unlock();
}

// IN: the new stages that has to be added
void CStageRaceDoc::StagesHalfNew(int nParentFS, CHalfStage* pNewOne)
{
	Lock();

	StagesGet(nParentFS)->m_halfStages.AddTail( *pNewOne );

	Unlock();
}

void CStageRaceDoc::StagesFullNew()
{
	if( !TestAccess() ) return;
	// Create a new stage and edit it
	CFullStage objNewOne;
	if ( objNewOne.Edit() == IDOK )
	{
		// If trialdat dialog returned IDOK, we proceed
		// Add the new stage to the project
		StagesFullNew( &objNewOne );
		
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_ADDED,
			&objNewOne, StagesFullCount() );
		UpdateAllViews( NULL, TI_FULLSTAGE, (CObject*)&UVH );
	}
}

// IN: the identifier of the full stages for which a new half stages is desired
void CStageRaceDoc::StagesHalfNew(int nParentFS)
{
	if( !TestAccess() ) return;
	// Create a new stage and edit it
	CHalfStage objNewOne;
	if ( objNewOne.Edit(StagesGet(nParentFS)) == IDOK )
	{
		// If trialdat dialog returned IDOK, we proceed
		// Add the new stage to the project
		StagesHalfNew( nParentFS, &objNewOne );
		
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_ADDED,
			&objNewOne, nParentFS, StagesHalfCount(nParentFS) );
		UpdateAllViews( NULL, TI_HALFSTAGE, (CObject*)&UVH );
	}
}

// IN: a pointer to the full stage that needs to bedited
void CStageRaceDoc::StagesFullEdit(int nFS)
{
	if( !TestAccess() ) return;

	CFullStage* pFS = StagesGet( nFS );
	if( pFS->Edit(m_hGenerateSemaphore_ChangeToDoc) == IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_CONFIGURED,
			pFS, nFS );
		UpdateAllViews( NULL, TI_FULLSTAGE, (CObject*)&UVH );
	}
}

// IN: a pointer to the half stage that needs to be edited
void CStageRaceDoc::StagesHalfEdit(int nParentFS, int nHS)
{
	if( !TestAccess() ) return;

	CFullStage* pFS = StagesGet( nParentFS );
	CHalfStage* pHS = StagesGet( nParentFS, nHS );
	if( pHS->Edit(pFS,m_hGenerateSemaphore_ChangeToDoc) == IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_CONFIGURED,
			pHS, nParentFS, nHS );
		UpdateAllViews( NULL, TI_HALFSTAGE, (CObject*)&UVH );
	}
}

// IN: an indication which type of config we want to do
void CStageRaceDoc::StagesHalfEdit(CONFIG_TYPE ct)
{
	if( !TestAccess() ) return;

	// We construct a property sheet for multiple tabs
	CPropertySheet dlgPropertySheet;
	dlgPropertySheet.m_psh.dwFlags = dlgPropertySheet.m_psh.dwFlags | PSH_NOAPPLYNOW;

	// Set an appropriate title for the sheet
	switch( ct )
	{
		case CT_HALFSTAGE:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV88 ) );
			break;
		case CT_BONUS:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV84 ) );
			break;
		case CT_SPRINT:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV85 ) );
			break;
		case CT_POINTS:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV86 ) );
			break;
		case CT_CLIMB:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV87 ) );
			break;
		case CT_MOSTAGGRESSIVE:
			dlgPropertySheet.SetTitle( LoadStr( IDS_DIV105 ) );
			break;
	}

	// Fill the sheet
	for( int nFS=1; nFS <= StagesFullCount(); nFS++ )
	{
		for( int nHS=1; nHS <= StagesHalfCount(nFS); nHS++ )
		{
			CHalfStage* pHS = StagesGet(nFS,nHS);
			CPropertyPage* pcurrent;
			switch( ct )
			{
				case CT_HALFSTAGE:
				{
					CHalfStageTrialDat* dlgHS = new CHalfStageTrialDat;
					pcurrent = (CPropertyPage*)dlgHS;
					dlgHS->m_date = StagesGet(nFS)->m_date;
					*dlgHS = (*pHS);
					break;
				}
				case CT_BONUS:
				{
					CBonusDat* dlgBonus = new CBonusDat;
					pcurrent = (CPropertyPage*)dlgBonus;
					*dlgBonus = (*pHS);
					break;
				}
				case CT_SPRINT:
				{
					CSprintDat* dlgSprint = new CSprintDat;
					pcurrent = (CPropertyPage*)dlgSprint;
					*dlgSprint = (*pHS);
					break;
				}
				case CT_POINTS:
				{
					CPointsDat* dlgPoints = new CPointsDat;
					pcurrent = (CPropertyPage*)dlgPoints;
					*dlgPoints = (*pHS);
					break;
				}
				case CT_CLIMB:
				{
					CMountainDat* dlgMountain = new CMountainDat;
					pcurrent = (CPropertyPage*)dlgMountain;
					*dlgMountain = (*pHS);
					break;
				}
				case CT_MOSTAGGRESSIVE:
				{
					CMostAggressiveDat* dlgMostAggressive = new CMostAggressiveDat;
					pcurrent = (CPropertyPage*)dlgMostAggressive;
					*dlgMostAggressive = (*pHS);
					break;
				}
			}
			// Set an appropriate title for the page
			CString titlestring(
				LoadStr(IDS_DIV40) + " " +
				CEventItem::StagesMakeIDString(nFS,nHS,this) );
			LPTSTR lpsz = new TCHAR[titlestring.GetLength()+1];
			_tcscpy(lpsz, titlestring);

			pcurrent->m_psp.pszTitle=lpsz;
			pcurrent->m_psp.dwFlags |= PSP_USETITLE;
			// Actually add the page to the sheet
			dlgPropertySheet.AddPage(pcurrent);
		}
	}

	if ( dlgPropertySheet.DoModal() == IDOK )
	{
		int i = 0;
		// Fill the sheet
		for( int nFS=1; nFS <= StagesFullCount(); nFS++ )
		{
			for( int nHS=1; nHS <= StagesHalfCount(nFS); nHS++, i++ )
			{
				CHalfStage* pHS = StagesGet(nFS,nHS);
				CPropertyPage* pcurrent = dlgPropertySheet.GetPage(i);

				Lock();

				// Store changed data
				switch( ct )
				{
					case CT_HALFSTAGE:
						*pHS = *(CHalfStageTrialDat*)pcurrent;
						break;
					case CT_BONUS:
						*pHS = *(CBonusDat*)pcurrent;
						break;
					case CT_SPRINT:
						*pHS = *(CSprintDat*)pcurrent;
						break;
					case CT_POINTS:
						*pHS = *(CPointsDat*)pcurrent;
						break;
					case CT_CLIMB:
						*pHS = *(CMountainDat*)pcurrent;
						break;
					case CT_MOSTAGGRESSIVE:
						*pHS = *(CMostAggressiveDat*)pcurrent;
						break;
				}

				Unlock();
			}
		}
		// Set the document's modified flag
		SetModifiedFlag();

		if( ct != CT_BONUS )
		{
			// Update all the views
			UpdateAllViews( NULL, TI_SETTINGS, NULL );
		}
	}
	// Clean up
	CPropertyPage* pPage;
	for( int i = 0; i<dlgPropertySheet.GetPageCount(); i++ )
	{
		pPage = dlgPropertySheet.GetPage( i );
		delete (LPTSTR)pPage->m_psp.pszTitle;
		delete pPage;
	}
}

// IN: the identifier of the full stage that needs to be retrieved
// OUT: a pointer to the matching full stage
CFullStage* CStageRaceDoc::StagesGet(int nIndex)
{
	// We suppose the index given to be in the range of available stages

	// You must give a one-base index, NOT a zero-based!!!

	// We start with a check on the existance of the requested stage
	if( m_fullStages.GetCount() < nIndex )
		return NULL;

	// We iterate the full stages list in order to find the requested stage
	POSITION hPos = m_fullStages.GetHeadPosition();
	for ( int i=1; (i<nIndex)&&hPos; i++ )
	{
		m_fullStages.GetNext( hPos );
	};
	if( hPos )
		return &m_fullStages.GetAt( hPos );
	else
		return NULL;
}

const CAvailableList* CStageRaceDoc::StagesGetAvailables(int nFSIndex, int nHSIndex)
{
	CHalfStage* pHalfStage = StagesGet( nFSIndex, nHSIndex );
	CStaNoObjectList* pAvail;
	if( StagesGetPrev( nFSIndex, nHSIndex )==NULL )
		pAvail = &m_competitors;
	else
		pAvail = &StagesGetPrev( nFSIndex, nHSIndex )->m_arrival;

	const CAvailableList* pAvailList = NULL;
	if ( pHalfStage->m_stageType == ST_NORMAL )
		pAvailList = new CAvailableList( &pHalfStage->m_signOuts, pAvail );
	else
		pAvailList = new CAvailableList( &pHalfStage->m_signOuts, &pHalfStage->m_timeTrialOrder, pAvail );

	return pAvailList;
}

// IN: the identifiers of the half stage that needs to be retrieved
// OUT: a pointer to the matching half stage
CHalfStage* CStageRaceDoc::StagesGet(int nFSIndex, int nHSIndex)
{
	// We suppose the indexes given to be in the range of available stages

	// You must give a one-base index, NOT a zero-based!!!

	// We get the requested stage
	CFullStage* aFullStage;
	aFullStage = StagesGet( nFSIndex );

	// We start with a check on the existance of the requested stage
	if( !aFullStage )
		return NULL;
	if( aFullStage->m_halfStages.GetCount() < nHSIndex )
		return NULL;

	// Within the requested stage, we iterate the half stages in
	// order to find the requested half stage
	POSITION hPos = aFullStage->m_halfStages.GetHeadPosition();
	for ( int i=1; (i<nHSIndex)&&hPos; i++ )
	{
		aFullStage->m_halfStages.GetNext( hPos );
	};
	if( hPos )
		return &aFullStage->m_halfStages.GetAt( hPos );
	else
		return NULL;
}

// IN: the identifiers of the half stage of which we need the
//  next half stage to be retrieved
// OUT: a pointer to the matching half stage
CHalfStage* CStageRaceDoc::StagesGetNext(int nFSIndex, int nHSIndex)
{
	if( nHSIndex==StagesGet(nFSIndex)->m_halfStages.GetCount() )
						// We are standing at the end of a full stage
						//  so we need to jump to the next full stage
	{
		// Iterate until we find a next full stage...
		while ( ( ++nFSIndex )<=m_fullStages.GetCount() )
		{
			// ...which consists of any half stages (full stages can be empty!)
			if( StagesGet( nFSIndex )->m_halfStages.GetCount()>0 )
				break;
		}
		// (If we don't find, we get out with nFSIndex>m_fullStages.GetCount())

		// If found, return the last first stage from this particular full stage
		if ( nFSIndex<=m_fullStages.GetCount() )
		{
			CFullStage* aFullStage;
			aFullStage = StagesGet( nFSIndex );
			return &aFullStage->m_halfStages.GetHead();
		}
		// If not found, return NULL
		else
			return NULL;
	}
	else	// Obvious, we're standing in the middle of some full stage, so we can jump
			//  to the next half stage of this full stage
	{
		return StagesGet( nFSIndex, nHSIndex+1 );
	}
}

// IN: the identifiers of the half stage of which we need the
//  previous half stage to be retrieved
// OUT: a pointer to the matching half stage
CHalfStage* CStageRaceDoc::StagesGetPrev(int nFSIndex, int nHSIndex)
{
	if( nHSIndex==1 )	// We objAre standing at the top of a full stage
						//  so we need to jump to the previous full stage
	{
		// Iterate until we find a previous full stage...
		while ( ( --nFSIndex )>0 )
		{
			// ...which consists of any half stages (full stages can be empty!)
			if( StagesGet( nFSIndex )->m_halfStages.GetCount()>0 )
				break;
		}
		// (If we don't find, we get out with nFSIndex==0)

		// If found, return the last half stage from this pobjArticulobjAr full stage
		if ( nFSIndex )
		{
			CFullStage* aFullStage;
			aFullStage = StagesGet( nFSIndex );
			return &aFullStage->m_halfStages.GetTail();
		}
		// If not found, return NULL
		else
			return NULL;
	}
	else	// Obvious, we're standing in the middle of some full stage, so we can jump
			//  to the previous half stage of this full stage
	{
		return StagesGet( nFSIndex, nHSIndex-1 );
	}
}

// IN: the identifier of the full stage that needs to be deleted
void CStageRaceDoc::StagesDelete(int nIndex)
{
	if( m_references )
	{
		// Fail if document is locked for COM
		MessageBox( NULL, LoadStr( IDS_MBC_59 ), LoadStr( IDS_MBT_59 ), MB_OK|MB_ICONERROR );
		return;
	}
	if( !TestAccess() ) return;
	if( MessageBox( NULL,
			LoadStr( IDS_MBC_35 ),
			LoadStr( IDS_MBT_35 ),
			MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
			) == IDYES )
	{
		POSITION hPos = m_fullStages.GetHeadPosition();
		for ( int i=1; i<nIndex; i++ )
		{
			m_fullStages.GetNext( hPos );
		};

		Lock();

		m_fullStages.RemoveAt( hPos );

		Unlock();

		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_DELETED );
		UpdateAllViews( NULL, TI_HALFSTAGE, (CObject*)&UVH );
	}
}

// IN: the identifiers of the half stage that needs to be deleted
void CStageRaceDoc::StagesDelete(int nFSIndex, int nHSIndex)
{
	if( m_references )
	{
		// Fail if document is locked for COM
		MessageBox( NULL, LoadStr( IDS_MBC_59 ), LoadStr( IDS_MBT_59 ), MB_OK|MB_ICONERROR );
		return;
	}
	if( !TestAccess() ) return;
	if( MessageBox( NULL,
			LoadStr( IDS_MBC_34 ),
			LoadStr( IDS_MBT_34 ),
			MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
			) == IDYES )
	{
		CFullStage* aFullStage;
		aFullStage = StagesGet( nFSIndex );

		POSITION hPos = aFullStage->m_halfStages.GetHeadPosition();
		for ( int i=1; i<nHSIndex; i++ )
		{
			aFullStage->m_halfStages.GetNext( hPos );
		};

		Lock();

		aFullStage->m_halfStages.RemoveAt( hPos );

		Unlock();

		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		CUpdateViewHint UVH( UV_DELETED );
		UpdateAllViews( NULL, TI_FULLSTAGE, (CObject*)&UVH );
	}
}

/////////////////////////////////////////////////////////////////////////////
// MESSAGE HANDLERS

void CStageRaceDoc::OnFileUpload() 
{
	Upload();	
}

void CStageRaceDoc::OnUpdateFileUpload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_allsettings.ValueGet( IDS_SETT_UPLOAD_ALLOW ) );	
}


void CStageRaceDoc::OnToolsExportscanovision() 
{
	ExportScanovision();
}

void CStageRaceDoc::OnToolsExportfinishlynx() 
{
	ExportFinishlynx();
}

/////////////////////////////////////////////////////////////////////////////
// RACE DATA INPUT

bool CStageRaceDoc::InputArrivalSet(int nFS, int nHS, WORD nStaNo, WORD nRank, DWORD nUnits)
{
	CHalfStage* pHalfStage = StagesGet(nFS, nHS);
	if( pHalfStage )
	{
		// Determine from which source the available's list has to be taken
		CStaNoObjectList* pAvail;
		if( StagesGetPrev( nFS, nHS)==NULL )
			pAvail = &m_competitors;
		else
			pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

		if(pHalfStage->InputArrivalSet(nStaNo, nRank, nUnits, pAvail))
		{
			// Update publications
			GenerateClass(PWH_THIS, nFS, nHS);

			return true;
		}
	}
	return false;
}

bool CStageRaceDoc::InputArrivalSetByTime(int nFS, int nHS, WORD nStaNo, DWORD nUnits)
{
	CHalfStage* pHalfStage = StagesGet(nFS, nHS);
	if( pHalfStage )
	{
		// Determine from which source the available's list has to be taken
		CStaNoObjectList* pAvail;
		if( StagesGetPrev( nFS, nHS)==NULL )
			pAvail = &m_competitors;
		else
			pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

		if(pHalfStage->InputArrivalSetByTime(nStaNo, nUnits, pAvail))
		{
			// Update publications
			GenerateClass(PWH_THIS, nFS, nHS);

			return true;
		}
	}
	return false;
}

bool CStageRaceDoc::InputArrivalReset(int nFS, int nHS, WORD nStaNo)
{
	CHalfStage* pHalfStage = StagesGet(nFS, nHS);
	if( pHalfStage )
		if(pHalfStage->InputArrivalReset(nStaNo))
		{
			// Update publications
			GenerateClass(PWH_THIS, nFS, nHS);

			return true;
		}

	return false;
}

void CStageRaceDoc::InputOnTimingIdle(int nFS, int nHS)
{
	CHalfStage* pHalfStage = StagesGet(nFS, nHS);
	if( pHalfStage )
		if(pHalfStage->InputOnTimingIdle())
		{
			// Update publications
			GenerateClass(PWH_THIS, nFS, nHS);
		}
}

void CStageRaceDoc::OnToolsServerProcesspending() 
{
	for( int nFS=1; nFS<=StagesFullCount(); nFS++ )
	{
		for( int nHS=1; nHS<StagesHalfCount(nFS); nHS++ )
		{
			if( StagesGet(nFS, nHS)->InputOnTimingIdle() )
				// Update publications
				GenerateClass(PWH_THIS, nFS, nHS);
		}
	}
}

void CStageRaceDoc::OnToolsServerSendteamsCode() 
{
	m_bLongTeamNamesForCOM = false;
}

void CStageRaceDoc::OnUpdateToolsServerSendteamsCode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( !m_bLongTeamNamesForCOM );
}

void CStageRaceDoc::OnToolsServerSendteamsName() 
{
	m_bLongTeamNamesForCOM = true;
}

void CStageRaceDoc::OnUpdateToolsServerSendteamsName(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bLongTeamNamesForCOM );
}

void CStageRaceDoc::InputRanking(int nFS, int nHS, char nType)
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	// Determine from which source the available's list has to be taken
	CStaNoObjectList* pAvail;
	if ( StagesGetPrev( nFS, nHS )==NULL )
		pAvail = &m_competitors;
	else
		pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

	// Run the ranking dialog for the appropriate stage
	if( pStage->InputRanking( nType, pAvail, m_allsettings.ValueGet(IDS_SETT_GNRL_INPUTACCURACY_100), &m_competitors, m_hGenerateSemaphore_ChangeToDoc )
			== IDOK )
	{
		// OVERALL CLASSIFICATION GENERATION
		if( m_bGenerateAutomatically )
			GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );

		// Set the document's modified flag
		SetModifiedFlag();
	}
}

void CStageRaceDoc::InputStartingOrder( int nFS, int nHS )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	// Determine from which source the available's list has to be taken
	CStaNoObjectList* pAvail;
	if ( StagesGetPrev( nFS, nHS )==NULL )
		// Take the main competitors list when there are no previous half stages
		pAvail = &m_competitors;
	else
	{
		// Take the arrival list from the previous half stage
		pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;
		// If there is a previous half stage in this full stage,
		// but it has no arrived competitors, we try to take
		// the arrivals list from the last half stage of the
		// previous full stage
		if( (pAvail->GetCount()==0) && (nHS>1) && (nFS>1) )
		{
			CFullStage* pFS = StagesGet( nFS-1 );
			if( pFS->CountHalfStages() )
				pAvail = &StagesGet( nFS-1, pFS->CountHalfStages() )->m_arrival;
		}
	}

	// Determine from which source the "automatic from previous
	// ... stage" has to be taken
	CDistributedClassification* pPreviousFS = NULL;
	if( nFS>1 ) pPreviousFS = new CDistributedClassification( nFS-1,
									StagesGet( nFS-1 )->CountHalfStages(),
									this );

	CDistributedClassification* pPreviousHS = NULL;
	if( nHS>1 ) pPreviousHS = new CDistributedClassification( nFS,
									nHS-1,
									this);


	// Run the ranking dialog for the appropriate stage
	if( pStage->InputStartingOrder( pAvail, &m_competitors, m_hGenerateSemaphore_ChangeToDoc,
									pPreviousHS, pPreviousFS )
			== IDOK )
	{
		// Print the result
		if( m_bGenerateAutomatically )
		{
			GenerateOrder( nFS, nHS );
			if( pStage->OrderInvolvesArrival() )
			{
				GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );
			}
		}

		// Set the document's modified flag
		SetModifiedFlag();
	}

	// Clean up after use
	if( pPreviousHS ) delete pPreviousHS;
	if( pPreviousFS ) delete pPreviousFS;
}

void CStageRaceDoc::InputSignOuts( int nFS, int nHS )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	// Determine from which source the available's list has to be taken
	CStaNoObjectList* pAvail;
	if ( StagesGetPrev( nFS, nHS )==NULL )
		pAvail = &m_competitors;
	else
		pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

	// Count the currently available amount of sign outs in this stage
	int nOld = StagesGet( nFS, nHS )->m_signOuts.GetCount();

	// Run the ranking dialog for the appropriate stage
	if( pStage->InputSignOuts( pAvail, &((CSettingsPublication*)m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages, &m_competitors, m_hGenerateSemaphore_ChangeToDoc )
			== IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		int nNew = StagesGet( nFS, nHS )->m_signOuts.GetCount();
		if( nNew && !nOld )
		{
			// If not already exists add it to the view
			CUpdateViewHint UVH( UV_ADDED,
				NULL, nFS, nHS );
			UpdateAllViews( NULL, TI_SIGNOUTS, (CObject*)&UVH );
		}
		else if( nOld && !nNew )
		{
			// If not exists anymore remove it from the view
			CUpdateViewHint UVH( UV_DELETED,
				NULL, nFS, nHS );
			UpdateAllViews( NULL, TI_SIGNOUTS, (CObject*)&UVH );
		}
	}
}

void CStageRaceDoc::InputFunctionRemovegaps( int nFS, int nHS, char nType )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	Lock();

	// Run the remove gaps function
	pStage->FunctionRemovegaps();

	Unlock();

	// OVERALL CLASSIFICATION GENERATION
	if( m_bGenerateAutomatically )
		GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );

	// Set the document's modified flag
	SetModifiedFlag();
}

void CStageRaceDoc::InputFunctionRemove1xseconds( int nFS, int nHS, char nType )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	Lock();

	// Run the remove 1/xth seconds function
	pStage->FunctionRemove1xseconds();

	Unlock();

	// OVERALL CLASSIFICATION GENERATION
	if( m_bGenerateAutomatically )
		GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );

	// Set the document's modified flag
	SetModifiedFlag();
}

void CStageRaceDoc::InputFunctionImport( int nFS, int nHS, char nType )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	// Determine from which source the available's list has to be taken
	CStaNoObjectList* pAvail;
	if ( StagesGetPrev( nFS, nHS )==NULL )
		pAvail = &m_competitors;
	else
		pAvail = &StagesGetPrev( nFS, nHS )->m_arrival;

	// Run the remove 1/xth seconds function
	if( pStage->FunctionImport(pAvail, m_hGenerateSemaphore_ChangeToDoc) )
	{
		// OVERALL CLASSIFICATION GENERATION
		if( m_bGenerateAutomatically )
			GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );

		// Set the document's modified flag
		SetModifiedFlag();
	}
}

void CStageRaceDoc::InputFunctionGroupt(int nFS, int nHS, char nType, short nSecs )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	Lock();

	// Run the group time function
	pStage->FunctionGroupt(nSecs);

	Unlock();

	// OVERALL CLASSIFICATION GENERATION
	if( m_bGenerateAutomatically )
		GenerateClass( m_bGenerateAutomatically?PWH_THIS:PWH_NOTHING, nFS, nHS );

	// Set the document's modified flag
	SetModifiedFlag();
}

void CStageRaceDoc::InputFunctionCheck( int nFS, int nHS )
{
	// Get the appropriate stage
	CHalfStage* pStage = StagesGet( nFS, nHS );

	// Run the integrity check function
	pStage->FunctionCheck();
}

/////////////////////////////////////////////////////////////////////////////
// VARIOUS

CFtpConnection* CStageRaceDoc::UploadPre() const
{
	// Check whether we're allowed to upload, if not: message and return
	if( !m_allsettings.ValueGet( IDS_SETT_UPLOAD_ALLOW ) )
	{
		MessageBox( NULL, LoadStr( IDS_MBC_37 ), LoadStr( IDS_MBT_37 ), MB_OK );
		// Return unsuccesful
		return NULL;
	}

	// Make an Internet connection
		CInternetSession* pInetSession
			= new CInternetSession( TEXT("StageRaceFTP"), 1, INTERNET_OPEN_TYPE_DIRECT );

	// Check to see if a reasonable URL has been provided
	// such as "ftp://servername/dirs" or just "servername/dirs"
		CString czHostAdd = ((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_hostAddress;
		DWORD dwServiceType;
		CString czServerName;
		CString czObject;
		INTERNET_PORT nPort;

		if (!AfxParseURL(czHostAdd, dwServiceType, czServerName, czObject, nPort))
		{
			// No good URL
			// Try adding the "ftp://" protocol
			czHostAdd = "ftp://" + czHostAdd;

			if (!AfxParseURL(czHostAdd, dwServiceType, czServerName, czObject, nPort))
			{
				// Still not a good URL
				// Stop trying
				MessageBox( NULL, LoadStr( IDS_MBC_38 ), LoadStr( IDS_MBT_38 ), MB_OK);
				// Delete the internet connection
				pInetSession->Close();
				delete pInetSession;
				// Return unsuccesful
				return NULL;
			}
		}

	// Now open an FTP connection to the server
		if ((dwServiceType == INTERNET_SERVICE_FTP) && !czServerName.IsEmpty())
		{
			CFtpConnection* pFtpConnection=NULL;
			try
			{
				// Actually open the connection
				// by mentioning servername/username/password
				pFtpConnection = pInetSession->GetFtpConnection( czServerName,
																((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_username,
																((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_password );

				// Set up the directory for the remote czFiles (no ending slash allowed)
				CString czRemoteDir = ((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_remoteDir;
				// We only work with backslashes, no slashes
				czRemoteDir.Replace( TEXT("\\"), TEXT("/") );
				// To be consistent, we remove an eventual ending slash
				if( czRemoteDir.Right(1) == TEXT("/") ) czRemoteDir.Left( czRemoteDir.GetLength()-1 );

				// Create the remote directory
				pFtpConnection->CreateDirectory( czRemoteDir );

				// See if sub directory needed too
				if( m_allsettings.ValueGet(IDS_SETT_UPLOAD_ADDFOLDER) )
				{
					czRemoteDir += TEXT("/");
					czRemoteDir += FilesTitle();
					// Create the remote subdirectory
					pFtpConnection->CreateDirectory( czRemoteDir );
				}

				// Switch to the new current directory
				pFtpConnection->SetCurrentDirectory( czRemoteDir );

				// Return succesful
				return pFtpConnection;
			}
			catch (CInternetException* pEx)
			{
				// Display the error message
				TCHAR szErr[1024];
				if (pEx->GetErrorMessage(szErr, 1024))
					MessageBox( NULL, szErr, LoadStr( IDS_DIV49 ), MB_OK );
				else
					MessageBox( NULL, LoadStr( IDS_MBC_39 ), LoadStr( IDS_MBT_39 ), MB_OK );
				// Delete the error object
				pEx->Delete();
				// Delete the internet connection
				pInetSession->Close();
				delete pInetSession;
				// Return unsuccesful
				return NULL;
			}
		}
		else
		{
			// Invalid URL for FTP
			MessageBox( NULL, LoadStr( IDS_MBC_38 ), LoadStr( IDS_MBT_38 ), MB_OK);
			// Delete the internet connection
			pInetSession->Close();
			delete pInetSession;
			// Return unsuccesful
			return NULL;
		}
}

void CStageRaceDoc::UploadPost(CFtpConnection* pFtpConnection) const
{
	if( pFtpConnection )
	{
		CInternetSession* pInetSession =
			pFtpConnection->GetSession();

		// Destroy the FTP-connection
		pFtpConnection->Close();
		delete pFtpConnection;

		if( pInetSession )
		{
			// Close the Internet connection
			pInetSession->Close();
			delete pInetSession;
		}
	}
}

void CStageRaceDoc::Upload() const
{
	CFtpConnection* pFtpConnection = UploadPre();
	if( pFtpConnection )
	{
		// This will automatically display a wait cursor
		CWaitCursor objCursor;

		// Select the files to be transferred
		CFileFind finder;
		BOOL bWorking = finder.FindFile( FilesPath()+FilesTitle()+TEXT("*.html") );

	// REPORT
		// Prepare a transfer czReport/log
		CString czReport;
		bool error = false;
		czReport = LoadStr( IDS_DIV47 )+TEXT(" ");
		czReport = czReport + ((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_hostAddress;
		czReport = czReport + TEXT(":\n\n");

	// TRANSFER
		// Transfer any file and look for the next
 		BOOL bIndexProcessed = false;
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if(pFtpConnection->PutFile(	finder.GetFilePath(),
										((CSettingsUpload*)m_allsettings.GetSettings(SETT_UPLOAD))->m_remoteDir + TEXT("/") +
										( m_allsettings.ValueGet(IDS_SETT_UPLOAD_ADDFOLDER)?(FilesTitle()+TEXT("/")):TEXT("") ) +
										finder.GetFileName() ) )
			{
				czReport = czReport + finder.GetFileName() + TEXT("\n");
			}
			else
			{
				czReport = czReport + finder.GetFileName() + TEXT(" (ERROR)\n");
				error = true;
			}
			if( m_allsettings.ValueGet( IDS_SETT_HTML_TOC_EVENTNAME )  )
				if( !bWorking && !bIndexProcessed )
				{
					if( bWorking = finder.FindFile( FilesPath()+TEXT("index.html") ) )
						if( MessageBox( NULL, LoadStr( IDS_MBC_48 ), LoadStr( IDS_MBT_48 ), MB_YESNO|MB_ICONQUESTION ) != IDYES )
							bWorking = false;
					bIndexProcessed = true;
				}
		}
	// REPORT	// Display czReport
		if( error ) czReport = czReport + TEXT("\n")+ LoadStr( IDS_DIV48 );
		MessageBox( NULL, czReport, LoadStr( IDS_DIV50 ), MB_OK );

	// CLEAN UP
		UploadPost(pFtpConnection);
	}
}

// OUT: indication whether the user is allowed to configure the document or nog
bool CStageRaceDoc::TestAccess()
{
	if( m_allsettings.ValueGet( IDS_SETT_ACCESS_FREE ) )
		return true;
	if( m_allsettings.ValueGet( IDS_SETT_ACCESS_PASSWORD ) )
	{
		CGetPwd aDlg;
		if(aDlg.DoModal()==IDOK)
			if(aDlg.m_accessPassword==((CSettingsAccess*)m_allsettings.GetSettings(SETT_ACCESS))->m_password)
			{
				return true;
			}
			else
			{
				MessageBox( NULL, LoadStr( IDS_MBC_40 ),
					LoadStr( IDS_MBT_40 ), MB_OK );
				return false;
			}
	}
	if( m_allsettings.ValueGet( IDS_SETT_ACCESS_KEY ) )
	{
			if( ((CStageRaceApp*)AfxGetApp())->m_key.HaspID()==
					((CSettingsAccess*)m_allsettings.GetSettings(SETT_ACCESS))->m_key )
			{
				return true;
			}
			else
			{
				MessageBox( NULL, LoadStr( IDS_MBC_41 )+((CSettingsAccess*)m_allsettings.GetSettings(SETT_ACCESS))->m_key,
					LoadStr( IDS_MBT_41 ), MB_OK );
				return false;
			}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// TODO

void CStageRaceDoc::OnConfigureProfilepicker() 
{
	if( m_allsettings.Profiles( !TestAccess(), m_hGenerateSemaphore_ChangeToDoc )==IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		UpdateAllViews( NULL, TI_SETTINGS, NULL );
	}
}

void CStageRaceDoc::Settings()
{
	if( !TestAccess() ) return;

	if( m_allsettings.Settings(m_hGenerateSemaphore_ChangeToDoc)==IDOK )
	{
		// Set the document's modified flag
		SetModifiedFlag();

		// Update all the views
		UpdateAllViews( NULL, TI_SETTINGS, NULL );
	}
}

void CStageRaceDoc::CommuniqueDelete(int nFS/*=0*/, int nHS/*=0*/)
{
	if( MessageBox(	NULL,
						LoadStr( IDS_MBC_33 ),
						LoadStr( IDS_MBT_33 ),
						MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
					) == IDYES )
	{
		CCommunique* pComm = CommuniqueGet(nFS, nHS);

		Lock();

		// Empty the communiqué
		pComm->Empty();

		Unlock();

		// Set the document's modified flag
		SetModifiedFlag();
		
		// Update all the views
		CUpdateViewHint UVH( UV_DELETED,
			pComm, nFS, nHS );
		UpdateAllViews( NULL, TI_COMMUNIQUE, (CObject*)&UVH );
	}
}

void CStageRaceDoc::CommuniqueEdit(int nFS/*=0*/, int nHS/*=0*/)
{
	CCommunique* pComm = CommuniqueGet(nFS, nHS);
	CEditCommunique dlgCommunique(this);
	dlgCommunique = *pComm;
	if( nHS )
	{
		// We additionally provide information through which
		// the dialog can generate team captains vehicles
		// starting order for the following day
		dlgCommunique.m_nFS = nFS;
		dlgCommunique.m_nHS = nHS;
	}
	BOOL bEmptyBefore = pComm->IsEmpty();
	if( dlgCommunique.DoModal()==IDOK )
	{
		Lock();
		*pComm = dlgCommunique;
		Unlock();
		
		if( m_bGenerateAutomatically )
			GenerateCommunique(nFS, nHS);

		// Set the document's modified flag
		SetModifiedFlag();
		
		// Update all the views
		CUpdateViewHint UVH( bEmptyBefore?UV_ADDED:UV_UPDATED,
			pComm, nFS, nHS );
		UpdateAllViews( NULL, TI_COMMUNIQUE, (CObject*)&UVH );
	}
}

CCommunique* CStageRaceDoc::CommuniqueGet(int nFS, int nHS)
{
	// Get the correct communiqué
	if( nHS )
		return &StagesGet( nFS, nHS )->m_communique;
	else
		if( nFS )
			return &StagesGet( nFS )->m_communique;
		else
			return &m_communique;
}

void CStageRaceDoc::OnUpdateToolsExportscanovision(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		!((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() &&
		StagesGet(1,1) ); // 1-1 needs to exist!
}

void CStageRaceDoc::OnUpdateToolsExportfinishlynx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		!((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() &&
		StagesGet(1,1) ); // 1-1 needs to exist!
}

void CStageRaceDoc::SetTitle(LPCTSTR lpszTitle) 
{
	CDocument::SetTitle(lpszTitle);
	((CStageRaceApp*)AfxGetApp())->ActiveDocOpen(this);
}

void CStageRaceDoc::OnCloseDocument() 
{
	if( WaitForSingleObject(m_hGenerateSemaphore_KeepDocOpen,0)==WAIT_OBJECT_0 )
	{
		CDocument::OnCloseDocument();
		((CStageRaceApp*)AfxGetApp())->ActiveDocClose(this);
		ReleaseSemaphore(m_hGenerateSemaphore_KeepDocOpen,1,NULL);
	}
	else
		MessageBeep(MB_ICONASTERISK);
}

void CStageRaceDoc::OnViewEventItemSelection() 
{
	if( !m_pEventItemSelection )
	{
		m_pEventItemSelection = new CDlgEventItemSelection(this);
		m_pEventItemSelection->Create(IDD_DLGEVENTITEMSELECTION, NULL);
	}
	else
		m_pEventItemSelection->ShowWindow(
				m_pEventItemSelection->IsWindowVisible()?SW_HIDE:SW_SHOW
			);
}

void CStageRaceDoc::OnUpdateViewEventItemSelection(CCmdUI* pCmdUI) 
{
	if( m_pEventItemSelection )
		pCmdUI->SetCheck( m_pEventItemSelection->IsWindowVisible()?1:0 );
	else
		pCmdUI->SetCheck( 0 );
}

CString CStageRaceDoc::FilesPath() const
{
	// First we set up the basic file name which
	//  we need to point to a html to display
	// We take the document file name
	CString cPath = GetPathName();
	// If the document has not been saved or does
	//  not have a disk file associated with it
	//  we just take the program directory
	if( !cPath.GetLength() )
	{
		TCHAR chBuffer[MAX_PATH];
		GetModuleFileName( NULL, chBuffer, MAX_PATH );
		cPath = CString(chBuffer);
	}
	// We strip it to the path only
	cPath = cPath.Left( cPath.ReverseFind( '\\' )+1 );

	return cPath;
}

CString CStageRaceDoc::FilesTitle() const
{
	// Our html file name is composed of the document title and the html title
	// If the title includes an extension, we get rid of that extension
	// We set up the path to which we're going to direct the presentation view
	CString cFile = GetTitle();
			// Use the pointer cast, above, in order to get our override!
	if( (cFile.Right( 4 ) == ".str") ||
		(cFile.Right( 4 ) == ".STR") )
			cFile = cFile.Left( cFile.GetLength()-4 );

	return cFile;
}

CWnd* CStageRaceDoc::GetEventItemSelectionDlg()
{
	return m_pEventItemSelection;
}

int CStageRaceDoc::GetFileVersion()
{
	return m_nFileVersion;
}

void CStageRaceDoc::PreCloseFrame(CFrameWnd *pFrame)
{
	// This is necessary because the CHtmlView that could be active
	// causes problems on destroy when Windows XP manifest is chosen
	pFrame->SetActiveView(NULL);
	CDocument::PreCloseFrame(pFrame);
}


void CStageRaceDoc::OnConfigureAllMostaggressivecl() 
{
	StagesHalfEdit(CT_MOSTAGGRESSIVE);
}

void CStageRaceDoc::OnConfigureAllBonuses() 
{
	StagesHalfEdit(CT_BONUS);
}

void CStageRaceDoc::OnConfigureAllClimbcl() 
{
	StagesHalfEdit(CT_CLIMB);
}

void CStageRaceDoc::OnConfigureAllHalfstage() 
{
	StagesHalfEdit(CT_HALFSTAGE);
}

void CStageRaceDoc::OnConfigureAllPointscl() 
{
	StagesHalfEdit(CT_POINTS);
}

void CStageRaceDoc::OnConfigureAllSprintcl() 
{
	StagesHalfEdit(CT_SPRINT);
}

void CStageRaceDoc::OnUpdateConfigureAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(StagesHalfCount()>0);
}

void CStageRaceDoc::Lock()
{
	WaitForSingleObject(m_hGenerateSemaphore_ChangeToDoc, INFINITE);
}

void CStageRaceDoc::Unlock()
{
	ReleaseSemaphore(m_hGenerateSemaphore_ChangeToDoc,1,NULL);
}

void CStageRaceDoc::OnViewMonitormode() 
{
	m_bMonitorMode = !m_bMonitorMode;
	SetMonitor();
}

void CStageRaceDoc::OnUpdateViewMonitormode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bMonitorMode );	
}

UINT CStageRaceDoc::MonitorThread(LPVOID pParam)
{
	// INITIALISATION

		CStageRaceDoc* pDoc = (CStageRaceDoc*)pParam;

/* THIS IS A PREVIOUS IMPLEMENTATION, USING FindFirstChangeNotification
WHICH GAVE PROBLEMS: IT ALREADY SIGNALED WHEN FILE STILL BEING WRITTEN
		// StageRace files
		HANDLE hPath = FindFirstChangeNotification(
			pDoc->FilesPath(),
			FALSE,
			FILE_NOTIFY_CHANGE_LAST_WRITE );

		// Other files
		CArray<CString,CString> external_folders;
		CArray<HANDLE, HANDLE > external_handles;

	// MAIN PROCESS

		MSG msg;
		bool bGo = true;

		while( bGo )
		{
			HANDLE* phHandles = new HANDLE[external_handles.GetSize()+1];
			(*phHandles)=hPath;
			for( int i=0; i<external_handles.GetSize(); i++ )
				*(phHandles+i+1)=external_handles.GetAt(i);

			DWORD waitedfor = MsgWaitForMultipleObjects(
				external_handles.GetSize()+1,
				phHandles,
				FALSE,
				INFINITE,
				QS_POSTMESSAGE );

			// Check if we need to quit
			if( PeekMessage(
					&msg,
					NULL,
					WM_QUIT,
					WM_QUIT,
					PM_REMOVE ) )
				bGo = false;
			// Check if we need to add a file to monitor
			else if( PeekMessage(
					&msg,
					NULL,
					WM_USER_ADDFILETOMONITOR,
					WM_USER_ADDFILETOMONITOR,
					PM_REMOVE ) )
			{
				CString* pfolder;
				pfolder = (CString*)msg.wParam;
				if( pfolder->ReverseFind( '\\' )!=-1 )
					*pfolder = pfolder->Left(
						pfolder->ReverseFind( '\\' )+1 );

				HANDLE hTemp = FindFirstChangeNotification(
					*pfolder,
					FALSE,
					FILE_NOTIFY_CHANGE_LAST_WRITE );

				if( hTemp==INVALID_HANDLE_VALUE )
					MessageBox( NULL, LoadStr( IDS_MBC_56 )+TEXT("\n\n(\"")+*pfolder+TEXT("\")"), LoadStr( IDS_MBT_56 ), MB_OK | MB_ICONERROR);
				else
				{
					// Add to arrays
					external_folders.Add( *pfolder );
					external_handles.Add( hTemp );
				}

				delete pfolder;
			}
			// Update views
			else
			{
				for( int i=0; i<external_handles.GetSize(); i++ )
					FindNextChangeNotification(
						external_handles.GetAt(i) );
				FindNextChangeNotification(hPath);
				Sleep(1200); // Give the file some time to be fully written
				pDoc->UpdateAllViewsThreaded( NULL, TI_TOBEDETERMINED );
			}

			delete phHandles;
		}

	// CLEANUP
		
		FindCloseChangeNotification(hPath);
		for( int i=0; i<external_handles.GetSize(); i++ )
			FindCloseChangeNotification(
				external_handles.GetAt(i) );
*/

		// StageRace files
		HANDLE hPath = CreateFile(
			pDoc->FilesPath(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED,
			NULL
		);
		if (hPath == INVALID_HANDLE_VALUE)
		{
			ASSERT(0);
			return 0; //cannot open folder
		}

		// Overlapped structure
		OVERLAPPED PollingOverlap = {0};
		PollingOverlap.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

		// Other files
		CArray<HANDLE    , HANDLE    > external_handles;
		CArray<OVERLAPPED, OVERLAPPED> external_overlappeds;

	// MAIN PROCESS

		MSG msg;
		bool bGo = true;

		while( bGo )
		{
			char buf[1024];
			DWORD nRet;
			BOOL result = ReadDirectoryChangesW(
				hPath,// handle to the directory to be watched
				&buf,// pointer to the buffer to receive the read results
				sizeof(buf),// length of lpBuffer
				FALSE,// flag for monitoring directory or directory tree
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				&nRet,// number of bytes returned
				&PollingOverlap,
				// pointer to structure needed for overlapped I/O
				NULL// pointer to completion routine
			);

			int i;
			for( i=0; i<external_handles.GetSize(); i++ )
				BOOL result = ReadDirectoryChangesW(
					external_handles.GetAt(i),// handle to the directory to be watched
					&buf,// pointer to the buffer to receive the read results
					sizeof(buf),// length of lpBuffer
					FALSE,// flag for monitoring directory or directory tree
					FILE_NOTIFY_CHANGE_LAST_WRITE,
					&nRet,// number of bytes returned
					&external_overlappeds.GetAt(i),
					// pointer to structure needed for overlapped I/O
					NULL// pointer to completion routine
				);


			HANDLE* phEvents = new HANDLE[external_overlappeds.GetSize()+1];
			(*phEvents)=PollingOverlap.hEvent;
			for( i=0; i<external_overlappeds.GetSize(); i++ )
				*(phEvents+i+1)=external_overlappeds.GetAt(i).hEvent;

			DWORD waitedfor = MsgWaitForMultipleObjects(
				external_overlappeds.GetSize()+1,
				phEvents,
				FALSE,
				INFINITE,
				QS_POSTMESSAGE );

			// Check if we need to quit
			if( PeekMessage(
					&msg,
					NULL,
					WM_QUIT,
					WM_QUIT,
					PM_REMOVE ) )
				bGo = false;
			// Check if we need to add a file to monitor
			else if( PeekMessage(
					&msg,
					NULL,
					WM_USER_ADDFILETOMONITOR,
					WM_USER_ADDFILETOMONITOR,
					PM_REMOVE ) )
			{
				CString* pfolder;
				pfolder = (CString*)msg.wParam;
				if( pfolder->ReverseFind( '\\' )!=-1 )
					*pfolder = pfolder->Left(
						pfolder->ReverseFind( '\\' )+1 );

				HANDLE hTemp = CreateFile(
					*pfolder,
					FILE_LIST_DIRECTORY,
					FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
					NULL,
					OPEN_EXISTING,
					FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED,
					NULL
				);
		
				if( hTemp==INVALID_HANDLE_VALUE )
					MessageBox( NULL, LoadStr( IDS_MBC_56 )+TEXT("\n\n(\"")+*pfolder+TEXT("\")"), LoadStr( IDS_MBT_56 ), MB_OK | MB_ICONERROR);
				else
				{
					// Overlapped structure
					OVERLAPPED PollingOverlapTemp = {0};
					PollingOverlapTemp.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

					// Add to arrays
					external_handles.Add( hTemp );
					external_overlappeds.Add( PollingOverlapTemp );					
				}

				delete pfolder;
			}
			// Update views
			else
			{
				Sleep(30); // Just to make sure
				pDoc->UpdateAllViewsThreaded( NULL, TI_TOBEDETERMINED );
			}

			delete phEvents;
		}

	// CLEANUP

		int i;
		for( i=0; i<external_overlappeds.GetSize(); i++ )
			CloseHandle(external_overlappeds.GetAt(i).hEvent);
		CloseHandle(PollingOverlap.hEvent);

		for( i=0; i<external_handles.GetSize(); i++ )
			CloseHandle(external_handles.GetAt(i));
		CloseHandle(hPath);

		return 0;
}

void CStageRaceDoc::SetMonitor()
{
	if( m_bMonitorMode )
	{
		m_pMonitor = AfxBeginThread( MonitorThread, (LPVOID)this );
	}
	else
	{
		if( m_pMonitor )
		{
			m_pMonitor->PostThreadMessage( WM_QUIT, NULL, NULL );

			DWORD exit_code;
			if( GetExitCodeThread(m_pMonitor->m_hThread,&exit_code) )
			{
				if( exit_code==STILL_ACTIVE )
					WaitForSingleObject(m_pMonitor->m_hThread, INFINITE);
			}
			m_pMonitor = NULL;
		}
	}
}

void CStageRaceDoc::OnUpdateViewAddfiletomonitor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_bMonitorMode );
}

void CStageRaceDoc::OnViewAddfiletomonitor() 
{
	if( m_bMonitorMode && m_pMonitor )
	{
		// Ask for which file to monitor
		CFileDialogWithMemory aFileDlg( TRUE, TEXT("*.html") );
		aFileDlg.m_ofn.lpstrFilter = TEXT("HTML files (*.html; *.htm)\0*.html;*.htm\0Text files (*.txt)\0*.txt\0All files (*.*)\0*.*\0\0");
		CString czBoxTitle = LoadStr( IDS_DIV101 );
		aFileDlg.m_ofn.lpstrDefExt = NULL;
		aFileDlg.m_ofn.lpstrTitle = czBoxTitle;
		aFileDlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;
		if( aFileDlg.DoModal()==IDOK )
		{
			POSITION pos = aFileDlg.GetStartPosition();
			while( pos )
			{
				AddFileToMonitor( aFileDlg.GetNextPathName(pos) );
			}
		}
	}
}

void CStageRaceDoc::AddFileToMonitor(CString file)
{
	// Add view
	CMainFrame* pMainWnd		= (CMainFrame*)AfxGetApp()->m_pMainWnd;

	// We create a new child frame
	CMDIChildWnd* pFrame		= new CMDIChildWnd();

	// We create a context describing the contents of the child frame (doc/view)
	CCreateContext objContext;
	objContext.m_pCurrentDoc	= this;
	objContext.m_pNewViewClass	= RUNTIME_CLASS( CStaticPresentationView );
	objContext.m_pNewDocTemplate= NULL;
	objContext.m_pLastView		= pMainWnd->GetActiveFrame() ? pMainWnd->GetActiveFrame()->GetActiveView() : NULL;
	objContext.m_pCurrentFrame	= pMainWnd->GetActiveFrame();

	// We load the frame as defined above
	if( pFrame->LoadFrame( IDR_MAINFRAME, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, pMainWnd, &objContext ) )
	{
		pFrame->InitialUpdateFrame( NULL, TRUE );

		// Load the external file to monitor
		((CStaticPresentationView*)pFrame->GetActiveView())
			->Navigate( file );
	}

	// Make sure the file is being monitored
	CString* pc = new CString( file );
	m_pMonitor->PostThreadMessage(
		WM_USER_ADDFILETOMONITOR,
		(WPARAM)pc,
		NULL );
}

void CStageRaceDoc::AddRef()
{
	InterlockedIncrement( &m_references );
}

void CStageRaceDoc::Release()
{
	InterlockedDecrement( &m_references );
}

BOOL CStageRaceDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument ::CanCloseFrame(pFrame);
}

BOOL CStageRaceDoc::SaveModified() 
{
	// If there are still people referencing our document,
	// we won't allow quiting it
	if( m_references )
	{
		// Fail if document is locked for COM
		if( MessageBox( NULL, LoadStr( IDS_MBC_57 ), LoadStr( IDS_MBT_57 ), MB_YESNO|MB_ICONERROR|MB_DEFBUTTON2 )==IDNO )
			return FALSE;
	}
	return CDocument::SaveModified();
}

void CStageRaceDoc::AutonumberCommuniques()
{
	CDlgAutonumberCommuniques dlg;
	// Get user confirmation and options first
	if( dlg.DoModal()==IDOK )
	{
		// Competitor lists
		AutonumberCommuniquesHelp( &m_idCompetitors, 0, 0, TI_LISTCOMPETITORS1 );
		AutonumberCommuniquesHelp( &m_idTeams, 0, 0, TI_LISTCOMPETITORS2 );

		CFullStage* pFullStage;
		// Iterate the full stages list
		for ( int nFS=1; nFS <= StagesFullCount(); nFS++ )
		{
			// Go over every full stage
			pFullStage = StagesGet( nFS );

			CHalfStage* pHalfStage;
			// Iterate the half stages list
			for ( int nHS=1; nHS <= pFullStage->CountHalfStages(); nHS++ )
			{
				// Go over every half stage (or time trial)
				pHalfStage = StagesGet( nFS, nHS );

				// Time trial starting order
				if( pHalfStage->m_stageType!=ST_NORMAL )
					AutonumberCommuniquesHelp( &pHalfStage->m_idStartList, nFS, nHS, TI_TIMETRIALORDER );

				// Updated starters lists per stage
				if( dlg.m_crossoutlists )
					AutonumberCommuniquesHelp( &pHalfStage->m_idCrossOut, nFS, nHS, TI_CROSSOUTLIST );
				if( dlg.m_signinlists )
					AutonumberCommuniquesHelp( &pHalfStage->m_idSignIn, nFS, nHS, TI_SIGNINLIST );
				if( dlg.m_stanosortedgeneral
						&& m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_GENERATETSTANOSORTEDGENERAL) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idGeneralStaNoSorted, nFS, nHS, TI_CLASSSTANOSORTEDGENERAL );

				// Stage result
				AutonumberCommuniquesHelp( &pHalfStage->m_idStage, nFS, nHS, TI_HALFSTAGE );
				if( pHalfStage->m_stageType==ST_TT_GROSS )
					AutonumberCommuniquesHelp( &pHalfStage->m_idTTArrival, nFS, nHS, TI_TTARRIVALLIST );

				// General result
				AutonumberCommuniquesHelp( &pHalfStage->m_idGeneral, nFS, nHS, TI_CLASSGENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask1stage, nFS, nHS, TI_CLASSMASK1STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask1gen, nFS, nHS, TI_CLASSMASK1GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask2stage, nFS, nHS, TI_CLASSMASK2STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask2gen, nFS, nHS, TI_CLASSMASK2GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask3stage, nFS, nHS, TI_CLASSMASK3STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask3gen, nFS, nHS, TI_CLASSMASK3GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask4stage, nFS, nHS, TI_CLASSMASK4STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask4gen, nFS, nHS, TI_CLASSMASK4GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask5stage, nFS, nHS, TI_CLASSMASK5STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask5gen, nFS, nHS, TI_CLASSMASK5GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask6stage, nFS, nHS, TI_CLASSMASK6STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask6gen, nFS, nHS, TI_CLASSMASK6GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask7stage, nFS, nHS, TI_CLASSMASK7STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask7gen, nFS, nHS, TI_CLASSMASK7GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask8stage, nFS, nHS, TI_CLASSMASK8STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask8gen, nFS, nHS, TI_CLASSMASK8GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask9stage, nFS, nHS, TI_CLASSMASK9STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask9gen, nFS, nHS, TI_CLASSMASK9GENERAL );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask10stage, nFS, nHS, TI_CLASSMASK10STAGE );
				if( m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMask10gen, nFS, nHS, TI_CLASSMASK10GENERAL );

				// Teams classification
				if( m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_GENERATE) )
					AutonumberCommuniquesHelp( &pHalfStage->m_idTeams, nFS, nHS, TI_CLASSTEAMS );

				// Other special classifications
				if( pHalfStage->m_sprintpointsCount )
					AutonumberCommuniquesHelp( &pHalfStage->m_idSprints, nFS, nHS, TI_SPRINT );
				if( pHalfStage->m_pointspointsFinish.GetCount() )
					AutonumberCommuniquesHelp( &pHalfStage->m_idPoints, nFS, nHS, TI_POINTS );
				if( pHalfStage->m_climbsorder.GetCount() )
					AutonumberCommuniquesHelp( &pHalfStage->m_idClimbs, nFS, nHS, TI_CLIMB );
				if( pHalfStage->m_mostaggressivepoints.GetCount() )
					AutonumberCommuniquesHelp( &pHalfStage->m_idMostAggressive, nFS, nHS, TI_MOSTAGGRESSIVE );

				// Half stage communique
				if( !pHalfStage->m_communique.IsEmpty() )
					AutonumberCommuniquesHelp( &pHalfStage->m_communique.m_id, nFS, nHS, TI_COMMUNIQUE );
			}

			// Full stage communique
			if( !pFullStage->m_communique.IsEmpty() )
				AutonumberCommuniquesHelp( &pFullStage->m_communique.m_id, nFS, 0, TI_COMMUNIQUE );
		}

		// Overall communique
		if( !m_communique.IsEmpty() )
			AutonumberCommuniquesHelp( &m_communique.m_id, 0, 0, TI_COMMUNIQUE );
	}
}

void CStageRaceDoc::OnEditAutonumber() 
{
	AutonumberCommuniques();	
}

void CStageRaceDoc::AutonumberCommuniquesHelp(CId *pId, int nFS, int nHS, TREEITEMS ti)
{
	unsigned short nID = 1;

	if( !pId->IsPublished() )
	{
		CUpdateViewHint UVH(
			UV_PUBLISHED,
			pId,
			nFS,
			nHS
		);
		m_pListID->PublishNextAvailable( pId, &UVH, ti );
	}
}

void CStageRaceDoc::OnUpdateEditAutonumber(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) );	
}
