// DlgEventItemSelection.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEventItemSelection dialog


BEGIN_EVENTSINK_MAP(CDlgEventItemSelection::CPrintWebBrowser, CWebBrowser2)
	ON_EVENT_REFLECT(CDlgEventItemSelection::CPrintWebBrowser, 104 /* DownloadComplete */, CDlgEventItemSelection::CPrintWebBrowser::OnDownloadComplete, VTS_NONE)
END_EVENTSINK_MAP()

IMPLEMENT_DYNAMIC(CDlgEventItemSelection, cdxCDynamicDialog)

void CDlgEventItemSelection::CPrintWebBrowser::OnDownloadComplete()
{
	CString cURL = GetLocationURL();
	if( cURL.GetLength() )
	{
		while( m_nCopies-- )
			ExecWB( OLECMDID_PRINT, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL );
//	delete this;
	}
}

CDlgEventItemSelection::CDlgEventItemSelection(const CStageRaceDoc* pDoc)
	: cdxCDynamicDialog(CDlgEventItemSelection::IDD, NULL)
{
	m_pDoc = pDoc;
	m_bExclude = false;
	ActivateAutoPos( "Print preparation" );
	//{{AFX_DATA_INIT(CDlgEventItemSelection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgEventItemSelection::DoDataExchange(CDataExchange* pDX)
{
	cdxCDynamicDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEventItemSelection)
	DDX_Control(pDX, IDC_EVENTITEMS, m_ctrlList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgEventItemSelection, cdxCDynamicDialog)
	//{{AFX_MSG_MAP(CDlgEventItemSelection)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EVENTITEMS, OnItemchangedEventItemSelection)
	ON_EN_CHANGE(IDC_COPIES, OnChangeCopies)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_COPYTO, OnCopy)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_BN_CLICKED(IDC_MAIL, OnMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEventItemSelection message handlers

BOOL CDlgEventItemSelection::OnInitDialog() 
{
	// Make the move handle disappear for this one
	cdxCDynamicWndEx ::m_nFlags &= ~flSizeIcon;

	cdxCDynamicDialog::OnInitDialog();
	AddSzControl(IDC_EVENTITEMS, mdResize, mdResize);
	AddSzControl(IDC_STATIC_TOTALCOPIES, mdNone, mdRepos);
	AddSzControl(IDC_STATIC_COPIES, mdNone, mdRepos);
	AddSzControl(IDC_SPINNER_TOTALCOPIES, mdNone, mdRepos);
	AddSzControl(IDC_SPINNER_COPIES, mdNone, mdRepos);
	AddSzControl(IDC_TOTALCOPIES, mdNone, mdRepos);
	AddSzControl(IDC_COPIES, mdNone, mdRepos);
	AddSzControl(IDC_CLEAR, mdRepos, mdRepos);
	AddSzControl(IDC_COPYTO, mdRelativeResize, mdRepos);
	AddSzControl(IDC_MAIL, mdRelativeResize, mdRepos);
	AddSzControl(IDC_PRINT, mdRelativeRepos, mdRepos);
	AddSzControl(IDC_UPLOAD, mdRelativeRepos, mdRepos);

	// Set listview styles
	m_ctrlList.SetExtendedStyle((LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP)&~LVS_EX_GRIDLINES);

	// Add columns
	m_ctrlList.InsertColumn(0, LoadStr( IDS_DIV71 ),  LVCFMT_LEFT, 180, 0);
	m_ctrlList.InsertColumn(1, LoadStr( IDS_DIV72 )+TEXT("/")+LoadStr( IDS_DIV73 ), LVCFMT_RIGHT,  30, 1);
	m_ctrlList.InsertColumn(2, LoadStr( IDS_DIV74 ), LVCFMT_RIGHT,  50, 3);

	// Create image lists
	m_imageList.Create( IDB_TREE, 20, 1, RGB(255,0,255) );

	// Connect image lists
	m_ctrlList.SetImageList( &m_imageList, LVSIL_SMALL );

	SetDlgItemText( IDC_TOTALCOPIES, TEXT("1") );
	OnItemchangedEventItemSelection(NULL, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CDlgEventItemSelection::~CDlgEventItemSelection()
{
	POSITION nPos = m_mapPrintItems.GetStartPosition();
	while( nPos )
	{
		CPrintItem* p;
		m_mapPrintItems.GetNextAssoc(nPos, p, p);
		delete p;
	}
	m_mapPrintItems.RemoveAll();
}

BOOL CDlgEventItemSelection::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_DELETE )
	{
		OnClear();
		return TRUE;
	}
	if( pMsg->message == WM_USER_DRAGGEDEVENTITEM )
	{
		if( (CStageRaceDoc*)pMsg->wParam == m_pDoc )
		{
			Add( (CEventItem*)pMsg->lParam );
			BringWindowToTop();
		}
		else
		{
			delete (CEventItem*)pMsg->lParam;
			MessageBox( LoadStr( IDS_MBC_54 ), LoadStr( IDS_MBT_54 ), MB_OK );
		}
		return TRUE;
	}
	return cdxCDynamicDialog::PreTranslateMessage(pMsg);
}

void CDlgEventItemSelection::Add(CEventItem *pEI)
{
	// Search for existing
	POSITION pos = m_mapPrintItems.GetStartPosition();
	while( pos )
	{
		CPrintItem* p;
		m_mapPrintItems.GetNextAssoc(pos, p, p);
		if( *(p->m_pEventItem)==*pEI )
		{
			p->m_nCopies++;
			// Draw it again
			DrawPrintItem( p );
			// Remove the event item since we're already have one
			delete pEI;

			return;
		}
	}

	// If no existing we make a new one
	CPrintItem* pPI = new CPrintItem( pEI, 1 );
	// Add to array
	m_mapPrintItems.SetAt( pPI, pPI );
	// Draw in view
	DrawPrintItem( pPI );
}

void CDlgEventItemSelection::DrawPrintItem(CPrintItem *pPI, int nItem/*=-1*/)
{
	// If called without an item no. being given
	// make sure it doesn't yet exist
	if( nItem == -1 )
		nItem = ClearPrintItem( pPI );

	TCHAR czBuffer[10];

	//Change nItem if '-1'
	if(nItem==-1) nItem = m_ctrlList.GetItemCount();

	//Add to ListControl
	nItem = m_ctrlList.InsertItem(nItem,
		pPI->m_pEventItem->ComposeFileTitle(),
		pPI->m_pEventItem->IconFromItem() );

	//Stage ID
	if( pPI->m_pEventItem->m_nFullStage )
	{
		m_ctrlList.SetItemText(nItem, 1, pPI->m_pEventItem->StagesMakeIDString());
	}

	//Copies
	_itot( pPI->m_nCopies, czBuffer, 10 );
	m_ctrlList.SetItemText(nItem, 2, czBuffer);
	
	//Set the item data
	m_ctrlList.SetItemData(nItem, (DWORD)pPI);

	//Make sure it's visible
	m_ctrlList.SetSelectionMark( nItem );
}

int CDlgEventItemSelection::ClearPrintItem(CPrintItem *pPI)
{
	// Look for an old view item with the same StaNo and remove it
	// Just iterate the whole list control, looking for our item
	for( int i=0; i< m_ctrlList.GetItemCount(); i++ )
		if (m_ctrlList.GetItemData(i) == (DWORD)pPI )
		{
			m_ctrlList.DeleteItem( i );
			OnItemchangedEventItemSelection(NULL, NULL);
			return i;
		}
	return -1;
}

void CDlgEventItemSelection::OnItemchangedEventItemSelection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( pResult ) *pResult = 0;
	if( m_ctrlList.GetSelectedCount()==1 )
	{
		// Get the selected item
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		// Get the matching print item
		CPrintItem* pPI = (CPrintItem*)m_ctrlList.GetItemData( nItem );
		TCHAR czBuffer[10];
		// Get the copies and display them
		_itot( pPI->m_nCopies, czBuffer, 10 );
		m_bExclude = true;
		SetDlgItemText( IDC_COPIES, czBuffer );
		m_bExclude = false;
		// Enable the copies controls
		GetDlgItem( IDC_COPIES )->EnableWindow(true);
		GetDlgItem( IDC_SPINNER_COPIES )->EnableWindow(true);
		GetDlgItem( IDC_CLEAR )->EnableWindow(true);
	}
	else
	{
		if( m_ctrlList.GetSelectedCount()==0 )
			GetDlgItem( IDC_CLEAR )->EnableWindow(false);
		else
			GetDlgItem( IDC_CLEAR )->EnableWindow(true);
		GetDlgItem( IDC_COPIES )->EnableWindow(false);
		GetDlgItem( IDC_SPINNER_COPIES )->EnableWindow(false);
	}
	// Enable/disable the print button
	GetDlgItem( IDC_COPYTO )->EnableWindow( m_ctrlList.GetItemCount()>0 );
	GetDlgItem( IDC_MAIL )->EnableWindow( m_ctrlList.GetItemCount()>0 );
	GetDlgItem( IDC_PRINT )->EnableWindow( m_ctrlList.GetItemCount()>0 );
	GetDlgItem( IDC_UPLOAD )->EnableWindow( m_ctrlList.GetItemCount()>0 );
}

void CDlgEventItemSelection::OnChangeCopies() 
{
	if( this->IsWindow() )
		if( !m_bExclude && m_ctrlList.GetSelectedCount()==1 )
		{
			// Get the selected item
			POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			// Get the matching print item
			CPrintItem* pPI = (CPrintItem*)m_ctrlList.GetItemData( nItem );
			// Store the new number of copies
			CString cBuffer;
			GetDlgItemText( IDC_COPIES, cBuffer );
			pPI->m_nCopies = _ttoi( cBuffer );
			// Draw it again
			DrawPrintItem( pPI );
			// And select it
			m_ctrlList.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
		}
}

void CDlgEventItemSelection::OnClear() 
{
	if( m_ctrlList.GetSelectedCount()>=1 )
	{
		// Get the selected item
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		while( pos )
		{
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			// Get the matching print item
			CPrintItem* pPI = (CPrintItem*)m_ctrlList.GetItemData( nItem );
			// Clear the view of the item
			ClearPrintItem( pPI );
			// Remove the print item
			m_mapPrintItems.RemoveKey( pPI );
			delete pPI;
			// Make the iterating work
			pos = m_ctrlList.GetFirstSelectedItemPosition();
		}
	}
}

void CDlgEventItemSelection::OnPrint()
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	int nTotalCopies = GetDlgItemInt( IDC_TOTALCOPIES );
	int i = 0;
	// Iterate all items that need printing
	POSITION nPos = m_mapPrintItems.GetStartPosition();
	while( nPos )
	{
		// Get every item that needs printing
		CPrintItem* p;
		m_mapPrintItems.GetNextAssoc( nPos, p, p );

		if( p->m_pEventItem->IsPublicationAvailable() )
		{
			// Make a new print web browser that
			// is going to handle the printing
			// of one print item
			CPrintWebBrowser* pwb = new CPrintWebBrowser( p->m_nCopies * nTotalCopies );
			pwb->Create( NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_PRINTBROWSER+i++ );
			pwb->SetSilent(true);
			pwb->Navigate( p->m_pEventItem->ComposeFileNamePath(), 0, 0, 0, 0 );
		}
	}
}

void CDlgEventItemSelection::OnUpload() 
{
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	CFtpConnection* pFtpConnection
		= m_pDoc->UploadPre();

	if( pFtpConnection )
	{
	// REPORT
		// Prepare a transfer czReport/log
		CString czReport;
		bool error = false;
		czReport = LoadStr( IDS_DIV47 )+" ";
		czReport = czReport + ((CSettingsUpload*)m_pDoc->m_allsettings.GetSettings(SETT_UPLOAD))->m_hostAddress;
		czReport = czReport + ":\n\n";

	// Iterate all items that need printing
		POSITION nPos = m_mapPrintItems.GetStartPosition();
		while( nPos )
		{
			// Get every item that needs printing
			CPrintItem* p;
			m_mapPrintItems.GetNextAssoc( nPos, p, p );

			if( p->m_pEventItem->IsPublicationAvailable() )
			{

				if( (p->m_pEventItem->m_tiConcerning==TI_ROOT)
						&& (m_pDoc->m_allsettings.ValueGet(IDS_SETT_HTML_TOC_INDEXHTML))
						&& (MessageBox(LoadStr( IDS_MBC_48 ), LoadStr( IDS_MBT_48 ), MB_YESNO|MB_ICONQUESTION) != IDYES)
					)
				{
					// It is a index.html which is not supposed to be uploaded
					// on end-user choice
					czReport = czReport + LoadStr( IDS_DIV75 ) + "\n";
				}
				else
				{
					// Upload every event item
					if(pFtpConnection->PutFile(	p->m_pEventItem->ComposeFileNamePath(),
												p->m_pEventItem->ComposeFileName() ) )
					{
						czReport = czReport + p->m_pEventItem->ComposeFileName() + "\n";
					}
					else
					{
						czReport = czReport + p->m_pEventItem->ComposeFileName() + " (ERROR)\n";
						error = true;
					}
				}
			}
		}

	// REPORT	// Display czReport
		if( error ) czReport = czReport + "\n"+ LoadStr( IDS_DIV48 );
		MessageBox( czReport, LoadStr( IDS_DIV50 ), MB_OK );

	// CLEAN UP
		m_pDoc->UploadPost(pFtpConnection);
	}
}

#include <mapi.h>
#define MAX_ATTACHMENTS 32
void CDlgEventItemSelection::OnMail() 
{
	// Code taken from http://win32programming.tripod.com/Win32tips06.html#4
	if( m_mapPrintItems.GetCount() )
	{
		// MAPI Funtions are not exported, hence one cannot do "Static" Link.
		// so "Dynamically" load the MAPI32 dll, map the address of the API
		// & use it.

		// Load MAPI library.
		HINSTANCE hMapilib = LoadLibrary( TEXT("MAPI32.DLL") );

		// Map the address of MAPISendMail API.
		LPMAPISENDMAIL lpfnMAPISendMail =
			(LPMAPISENDMAIL)GetProcAddress( hMapilib, "MAPISendMail" );

		// Create the Mail Message
		MapiMessage MailMsg;
		MapiRecipDesc MailSendTo;
		char Attachments[MAX_ATTACHMENTS][MAX_PATH];
		MapiFileDesc MailAttachments[MAX_ATTACHMENTS];

		ZeroMemory( &MailAttachments, sizeof(MapiFileDesc) );
		
		MailSendTo.ulReserved				= 0;
		MailSendTo.ulRecipClass				= MAPI_TO;
		MailSendTo.lpszName					= NULL;
		MailSendTo.lpszAddress				= NULL;
		MailSendTo.ulEIDSize				= 0;
		MailSendTo.lpEntryID				= NULL;
		
		CString cSubject = ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName;
		CString cNote = ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName+"\r\n";
			cNote += ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle+"\r\n";
			cNote += "\r\n";
			cNote += "\r\n";
			cNote += AssembleStr( TEXT("Organiser"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+":\r\n";
			cNote += "  "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_organiser+"\r\n";
			cNote += AssembleStr( TEXT("Location"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+":\r\n";
			cNote += "  "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_location+"\r\n";
			cNote += AssembleStr( TEXT("Date"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+":\r\n";
			cNote += "  "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_dates+"\r\n";
			cNote += AssembleStr( TEXT("Category"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+":\r\n";
			cNote += "  "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_category+"\r\n";
			cNote += "\r\n";
			cNote += "\r\n";
			cNote += ((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyName+"\r\n";
			cNote += ((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL+"\r\n";
			cNote += "__________________________________________\r\n";
			cNote += "  StageRace "+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()+"\r\n";
			cNote += "  http://www.stagerace.com";

		char* pconverted1, * pconverted2;
		int need;

		need = WideCharToMultiByte( CP_ACP, 0, cSubject, -1, NULL, 0, NULL, NULL );
		pconverted1 = new char[need];
		if( pconverted1 )
			WideCharToMultiByte( CP_ACP, 0, cSubject, -1, pconverted1, need, NULL, NULL );
		MailMsg.lpszSubject					= pconverted1;

		need = WideCharToMultiByte( CP_ACP, 0, cNote, -1, NULL, 0, NULL, NULL );
		pconverted2 = new char[need];
		if( pconverted2 )
			WideCharToMultiByte( CP_ACP, 0, cNote, -1, pconverted2, need, NULL, NULL );
		MailMsg.lpszNoteText				= pconverted2;

		MailMsg.ulReserved					= 0;			//Always 0
		MailMsg.lpszMessageType				= NULL;
		MailMsg.lpszDateReceived			= NULL;
		MailMsg.lpszConversationID			= NULL;
		MailMsg.flFlags						= 0l;
		MailMsg.lpOriginator				= NULL;			//Mail Sender's Info
		MailMsg.nRecipCount					= 0;
		MailMsg.lpRecips					= NULL;			//Details of recipiant.

		// Iterate all items that need sending
		POSITION nPos = m_mapPrintItems.GetStartPosition();
		int n = 0;
		while( nPos && (n<MAX_ATTACHMENTS) )
		{
			// Get every item that needs sending
			CPrintItem* p;
			m_mapPrintItems.GetNextAssoc( nPos, p, p );
			if( p->m_pEventItem->IsPublicationAvailable() )
			{
				WideCharToMultiByte( CP_ACP, 0, p->m_pEventItem->ComposeFileNamePath(), -1, Attachments[n], MAX_PATH, NULL, NULL );
				MailAttachments[n].lpszPathName	= Attachments[n];

				MailAttachments[n].ulReserved	= 0;
				MailAttachments[n].flFlags		= 0;
				MailAttachments[n].nPosition	= -1;
				MailAttachments[n].lpFileType	= NULL;
				MailAttachments[n].lpszFileName	= NULL;
				n++;
			}
		}
		MailMsg.nFileCount					= n;					//# of attachments
		MailMsg.lpFiles						= &MailAttachments[0];	//Details of Attachments

		// Send mail
		ULONG Error = lpfnMAPISendMail( 0, NULL, &MailMsg, MAPI_LOGON_UI|MAPI_DIALOG, 0 );

		// Unload MAPI lib
		FreeLibrary(hMapilib);

		if( pconverted1 ) delete pconverted1;
		if( pconverted2 ) delete pconverted2;

		if( Error==SUCCESS_SUCCESS )
		{
			return;
		}
	}
	MessageBox(LoadStr( IDS_MBC_61 ), LoadStr( IDS_MBT_61 ), MB_OK);
}

void CDlgEventItemSelection::OnCopy()
{
	BROWSEINFO lpbi;

	lpbi.hwndOwner = this->m_hWnd;
	lpbi.pidlRoot = NULL;
	
	TCHAR szDisplayName[MAX_PATH];
	lpbi.pszDisplayName = szDisplayName;
	
	CString cHeader = LoadStr( IDS_DIV90 );
	lpbi.lpszTitle = cHeader;
    
	lpbi.ulFlags = BIF_EDITBOX|BIF_RETURNONLYFSDIRS|BIF_RETURNONLYFSDIRS|BIF_RETURNFSANCESTORS;
	lpbi.lpfn = NULL;

	LPITEMIDLIST pSelectedItem;
	pSelectedItem = SHBrowseForFolder( &lpbi );

	TCHAR czSelectedItem[MAX_PATH];
	if( SHGetPathFromIDList( pSelectedItem, czSelectedItem ) )
	{
		// Iterate all items that need copying
		POSITION nPos = m_mapPrintItems.GetStartPosition();
		while( nPos )
		{
			// Get every item that needs copying
			CPrintItem* p;
			m_mapPrintItems.GetNextAssoc( nPos, p, p );
			if( p->m_pEventItem->IsPublicationAvailable() )
			{
				// Copy files that exist
				if( !CopyFile(
						p->m_pEventItem->ComposeFileNamePath(),
						czSelectedItem+p->m_pEventItem->ComposeFileName(),
						false ) )
				{
					// Show an error message when the copying fails
					LPVOID lpMessage;
					if( FormatMessage(
							FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							GetLastError(),
							0,
							(LPTSTR)&lpMessage,
							0,
							NULL ) )
					{
						MessageBox( LoadStr( IDS_MBC_55 )
								+"\n\n"
								+p->m_pEventItem->ComposeFileName()
								+"\n\n"
								+CString((LPCTSTR)lpMessage),
							LoadStr( IDS_MBT_55 ), MB_OK );
					}
					else
					{
						MessageBox( LoadStr( IDS_MBC_55 ),
							LoadStr( IDS_MBT_55 ), MB_OK );
					}
					// Abort further copying
					return;
				}
			}
		}
	}
}
