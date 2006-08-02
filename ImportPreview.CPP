// ImportPreview.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportPreview dialog


CImportPreview::CImportPreview(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_IMPORT_PREVIEW, CImportPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportPreview)
	m_headerSize = 0;
	m_staNoEnd = 0;
	m_staNoStart = 0;
	m_timeEnd = 0;
	m_timeStart = 0;
	m_rankEnd = 0;
	m_rankStart = 0;
	m_importType = 0;
	m_decimals = 0;
	m_rank = FALSE;
	m_rankCol = 0;
	m_separation = 0;
	m_staNoCol = 0;
	m_timeCol = 0;
	m_timeNotation = 0;
	m_separator = 0;
	m_event = 0;
	m_heat = 0;
	m_round = 0;
	//}}AFX_DATA_INIT

	m_cfRank.dwMask = CFM_COLOR | CFM_UNDERLINE;
	m_cfRank.crTextColor = RGB( 255,0,0 );
	m_cfRank.dwEffects = CFE_UNDERLINE;
	m_cfRank.cbSize = sizeof( m_cfRank );

	m_cfStaNo.dwMask = CFM_COLOR | CFM_UNDERLINE;
	m_cfStaNo.crTextColor = RGB( 0,255,0 );
	m_cfStaNo.dwEffects = CFE_UNDERLINE;
	m_cfStaNo.cbSize = sizeof( m_cfStaNo );

	m_cfTime.dwMask = CFM_COLOR | CFM_UNDERLINE;
	m_cfTime.crTextColor = RGB( 0,0,255 );
	m_cfTime.dwEffects = CFE_UNDERLINE;
	m_cfTime.cbSize = sizeof( m_cfTime );

	// Don't allow WM_CHANGE handling during initialisation
	m_changeHandled = true;

	// Set default values
	m_importType   = 0;
	m_event        = 1;
	m_round        = 1;
	m_heat         = 1;
	m_headerSize   = 12;
	m_decimals     = 4;
	m_rank         = false;
	m_rankStart    = 1;
	m_rankEnd      = 4;
	m_rankCol      = 1;
	m_staNoStart   = 5;
	m_staNoEnd     = 11;
	m_staNoCol     = 2;
	m_timeStart    = 14;
	m_timeEnd      = 24;
	m_timeCol      = 10;
	m_separation   = 0;
	m_timeNotation = 0;
	m_separator	   = 0;

	//Restore the selections for this dialog
	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
	if( er == ERROR_SUCCESS )
	{
		m_importType	= reg.GetDWord( TEXT("Import type"), m_importType );
		m_event			= reg.GetDWord( TEXT("Event"), m_event );
		m_round			= reg.GetDWord( TEXT("Round"), m_round );
		m_heat			= reg.GetDWord( TEXT("Heat"), m_heat );
		m_headerSize	= reg.GetDWord( TEXT("Header size"), m_headerSize );
		m_decimals		= reg.GetDWord( TEXT("Decimals"), m_decimals );
		m_rank			= reg.GetBool ( TEXT("Generate rankings"), m_rank!=0 )?TRUE:FALSE;
		m_rankStart		= reg.GetDWord( TEXT("Rank start"), m_rankStart );
		m_rankEnd		= reg.GetDWord( TEXT("Rank end"), m_rankEnd );
		m_rankCol		= reg.GetDWord( TEXT("Rank column"), m_rankCol );
		m_staNoStart	= reg.GetDWord( TEXT("StaNo start"), m_staNoStart );
		m_staNoEnd		= reg.GetDWord( TEXT("StaNo end"), m_staNoEnd );
		m_staNoCol		= reg.GetDWord( TEXT("StaNo column"), m_staNoCol );
		m_timeStart		= reg.GetDWord( TEXT("Time start"), m_timeStart );
		m_timeEnd		= reg.GetDWord( TEXT("Time end"), m_timeEnd );
		m_timeCol		= reg.GetDWord( TEXT("Time column"), m_timeCol );
		m_separation	= reg.GetDWord( TEXT("Separation type"), m_separation );
		m_timeNotation	= reg.GetDWord( TEXT("Time notation"), m_timeNotation );
		m_separator		= reg.GetDWord( TEXT("Separator"), m_separator );
	}
}


void CImportPreview::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportPreview)
	DDX_Text(pDX, IDC_ARRIVALIMPORTHEADERSIZE, m_headerSize);
	DDX_Text(pDX, IDC_ARRIVALIMPORTSTANOEND, m_staNoEnd);
	DDX_Text(pDX, IDC_ARRIVALIMPORTSTANOSTART, m_staNoStart);
	DDX_Text(pDX, IDC_ARRIVALIMPORTTIMEEND, m_timeEnd);
	DDX_Text(pDX, IDC_ARRIVALIMPORTTIMESTART, m_timeStart);
	DDX_Text(pDX, IDC_ARRIVALIMPORTRANKEND, m_rankEnd);
	DDX_Text(pDX, IDC_ARRIVALIMPORTRANKSTART, m_rankStart);
	DDX_Radio(pDX, IDC_ARRIVALIMPORTTYPE, m_importType);
	DDX_Text(pDX, IDC_ARRIVALIMPORTDECIMALS, m_decimals);
	DDV_MinMaxInt(pDX, m_decimals, 0, 5);
	DDX_Check(pDX, IDC_ARRIVALIMPORTRANK, m_rank);
	DDX_Text(pDX, IDC_ARRIVALIMPORTRANKCOL, m_rankCol);
	DDX_Radio(pDX, IDC_ARRIVALIMPORTSEPARATION, m_separation);
	DDX_Text(pDX, IDC_ARRIVALIMPORTSTANOCOL, m_staNoCol);
	DDX_Text(pDX, IDC_ARRIVALIMPORTTIMECOL, m_timeCol);
	DDX_Radio(pDX, IDC_ARRIVALIMPORTTIMENOTATION, m_timeNotation);
	DDX_CBIndex(pDX, IDC_ARRIVALIMPORTSEPARATOR, m_separator);
	DDX_Text(pDX, IDC_ARRIVALIMPORT_EVENT, m_event);
	DDX_Text(pDX, IDC_ARRIVALIMPORT_HEAT, m_heat);
	DDX_Text(pDX, IDC_ARRIVALIMPORT_ROUND, m_round);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportPreview, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CImportPreview)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTSTANOEND, OnChangeArrivalimportstanoend)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTSTANOSTART, OnChangeArrivalimportstanostart)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTTIMEEND, OnChangeArrivalimporttimeend)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTTIMESTART, OnChangeArrivalimporttimestart)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTHEADERSIZE, OnChangeArrivalimportheadersize)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTRANKEND, OnChangeArrivalimportrankend)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTRANKSTART, OnChangeArrivalimportrankstart)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTTYPE, OnArrivalimporttype)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTTYPE1, OnArrivalimporttype1)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTSEPARATION1, OnArrivalimportseparation1)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTSEPARATION, OnArrivalimportseparation)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTRANKCOL, OnChangeArrivalimportrankcol)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTSTANOCOL, OnChangeArrivalimportstanocol)
	ON_EN_CHANGE(IDC_ARRIVALIMPORTTIMECOL, OnChangeArrivalimporttimecol)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTALGEOPTIC, OnArrivalimportalgeoptic)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTOMEGACL, OnArrivalimportomegacl)
	ON_CBN_SELCHANGE(IDC_ARRIVALIMPORTSEPARATOR, OnSelchangeArrivalimportseparator)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTAMBCHRONX, OnArrivalimportambchronx)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTLYNXFINISHLYNX, OnArrivalimportlynxfinishlynx)
	ON_BN_CLICKED(IDC_ARRIVALIMPORTSKUNKWARETTWARE, OnArrivalimportskunkwarettware)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportPreview message handlers

BOOL CImportPreview::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	if( m_importType==0 )
		OnArrivalimporttype();
	else
		OnArrivalimporttype1();

	// Format the contents in order to have at least 100 characters minimum per line
	m_contents = m_contents + TEXT("\r\n");
	int nOffset = m_contents.Find( TEXT("\r\n") );

	while( nOffset >= 0 )
	{
		m_contents = m_contents.Left( nOffset )
			+ "                                                                                                    "
			+ m_contents.Mid( nOffset );
		nOffset += 102;
		nOffset = m_contents.Find( TEXT("\r\n"), nOffset );
	}

	// Make pointers to the edits
	CRichEditCtrl* pHeader  = (CRichEditCtrl*) GetDlgItem( IDC_ARRIVALIMPORTHEADER );
	CRichEditCtrl* pPreview = (CRichEditCtrl*) GetDlgItem( IDC_ARRIVALIMPORTPREVIEW );

	// Set the whole edit to the default font
	CFont objFont;
	objFont.CreateFont( 8, 0, 0, 0, 0, false, false, NULL, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("Courier"));
	pHeader ->SetFont( &objFont );
	pPreview->SetFont( &objFont );

	// Tab stops

		// Get the current (default) tab stop settings
		PARAFORMAT pfParagraph;
		pPreview->GetParaFormat( pfParagraph );

		// Allow tab stops and set the number
		pfParagraph.dwMask = pfParagraph.dwMask | PFM_TABSTOPS;
		pfParagraph.cTabCount=9;

		// Calculate the space per character
		// note: 8 is character width with selected font
		//       1440 twips = inch
		float fCharTwips = (float)(8*1440)/(pPreview->GetDC()->GetDeviceCaps(LOGPIXELSX));

		// Fill the tab stop positions
		int nPos = 0;
		pfParagraph.rgxTabs[ 0] = (int)((nPos+= 4)*fCharTwips); // BIB          // These are Alge-Timing
		pfParagraph.rgxTabs[ 1] = (int)((nPos+= 4)*fCharTwips); // LANE         // file properties
		pfParagraph.rgxTabs[ 2] = (int)((nPos+= 2)*fCharTwips); // LASTNAME
		pfParagraph.rgxTabs[ 3] = (int)((nPos+=13)*fCharTwips); // FIRSTNAME
		pfParagraph.rgxTabs[ 4] = (int)((nPos+=13)*fCharTwips); // CLUB
		pfParagraph.rgxTabs[ 5] = (int)((nPos+=25)*fCharTwips); // AGE
		pfParagraph.rgxTabs[ 6] = (int)((nPos+= 5)*fCharTwips); // STRING_TIME
		pfParagraph.rgxTabs[ 7] = (int)((nPos+=14)*fCharTwips); // BMPPOS
		pfParagraph.rgxTabs[ 8] = (int)((nPos+= 9)*fCharTwips); // INT_TIME
		pfParagraph.rgxTabs[ 9] = (int)((nPos+= 9)*fCharTwips); // PICNUM

		pHeader->SetParaFormat( pfParagraph );
		pPreview->SetParaFormat( pfParagraph );

	// Initialisation ends here, so we can allow WM_CHANGE handling
	m_changeHandled = false;

	UpdatePreview();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportPreview::OnChangeArrivalimportrankstart() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->GetWindowText( cBuffer );
		m_rankStart = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_rankStart > 79 ) m_rankStart = 79;
 		if( m_rankEnd <= m_rankStart ) m_rankEnd = m_rankStart+1;

		TCHAR czBuffer[10];
		_itot( m_rankStart, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->SetWindowText( CString(czBuffer) );
		_itot( m_rankEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimportrankend() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->GetWindowText( cBuffer );
		m_rankEnd = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
 		if( m_rankEnd <= m_rankStart ) m_rankEnd = m_rankStart+1;
		if( m_rankEnd > 100 ) m_rankEnd = 100;

		TCHAR czBuffer[10];
		_itot( m_rankEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimportstanostart() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->GetWindowText( cBuffer );
		m_staNoStart = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_staNoStart > 79 ) m_staNoStart = 79;
 		if( m_staNoEnd <= m_staNoStart ) m_staNoEnd = m_staNoStart+1;

		TCHAR czBuffer[10];
		_itot( m_staNoStart, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->SetWindowText( CString(czBuffer) );
		_itot( m_staNoEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimportstanoend() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->GetWindowText( cBuffer );
		m_staNoEnd = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
 		if( m_staNoEnd <= m_staNoStart ) m_staNoEnd = m_staNoStart+1;
		if( m_staNoEnd > 100 ) m_staNoEnd = 100;

		TCHAR czBuffer[10];
		_itot( m_staNoEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimporttimestart() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->GetWindowText( cBuffer );
		m_timeStart = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_timeStart > 79 ) m_timeStart = 79;
 		if( m_timeEnd <= m_timeStart ) m_timeEnd = m_timeStart+1;

		TCHAR czBuffer[10];
		_itot( m_timeStart, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->SetWindowText( CString(czBuffer) );
		_itot( m_timeEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimporttimeend() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->GetWindowText( cBuffer );
		m_timeEnd = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
 		if( m_timeEnd <= m_timeStart ) m_timeEnd = m_timeStart+1;
		if( m_timeEnd > 100 ) m_timeEnd = 100;

		TCHAR czBuffer[10];
		_itot( m_timeEnd, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::UpdatePreview()
{
	// Make pointers to the edits
	CRichEditCtrl* pHeader  = (CRichEditCtrl*) GetDlgItem( IDC_ARRIVALIMPORTHEADER );
	CRichEditCtrl* pPreview = (CRichEditCtrl*) GetDlgItem( IDC_ARRIVALIMPORTPREVIEW );
	int i;

	// We fill the header and display panes with the appropriate contents
	CString czHeader;
	CString czPreview = m_contents + "\r\n";

	for( i=m_headerSize; i>0; i-- )
	{
		int nOffset = czPreview.Find( TEXT("\r\n") );
		if( nOffset>0 ) // if Find==0
		{
			nOffset += 2; // Because of \r\n
			// We take the last two lines of the header to display in the header pane
			if( i<=2 )
				czHeader += czPreview.Left( nOffset );
			// We remove all the header lines for the string to display in the preview pane
			czPreview = czPreview.Mid( nOffset );
		}
		else
			i=0; //exit
	}
	if( m_headerSize==1 ) // To bottom align the header
		czHeader = "                                                                                \r\n" + czHeader;

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADER  ))->SetWindowText( czHeader );

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTPREVIEW ))->SetWindowText( czPreview+"  " );

	// Set the whole edit back to the default font
	CFont objFont;
	objFont.CreateFont( 8, 0, 0, 0, 0, false, false, NULL, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("Courier"));
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADER ))->SetFont( &objFont );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTPREVIEW ))->SetFont( &objFont );

 	// Make sure we can use the members of this dialog
	UpdateData();


	if( m_separation==0 )
	{
		// Set the formatting of the Rank column
		// For the header
		for( i=1; i>=0; i-- )
		{
			if( m_rankStart>0 )
				pHeader->SetSel( pHeader->LineIndex( i )+m_rankStart-1, pHeader->LineIndex( i )+m_rankEnd );
			else
				pHeader->SetSel( pHeader->LineIndex( i ), pHeader->LineIndex( i )+m_rankEnd );
			pHeader->SetSelectionCharFormat( m_cfRank );
		}
		// For the preview
		for( i=7; i>=0; i-- )
		{
			if( m_rankStart>0 )
				pPreview->SetSel( pPreview->LineIndex( i )+m_rankStart-1, pPreview->LineIndex( i )+m_rankEnd );
			else
				pPreview->SetSel( pPreview->LineIndex( i ), pPreview->LineIndex( i )+m_rankEnd );
			pPreview->SetSelectionCharFormat( m_cfRank );
		}

		// Set the formatting of the StaNo column
		// For the header
		for( i=1; i>=0; i-- )
		{
			if( m_staNoStart>0 )
				pHeader->SetSel( pHeader->LineIndex( i )+m_staNoStart-1, pHeader->LineIndex( i )+m_staNoEnd );
			else
				pHeader->SetSel( pHeader->LineIndex( i ), pHeader->LineIndex( i )+m_staNoEnd );
			pHeader->SetSelectionCharFormat( m_cfStaNo );
		}
		// For the preview
		for( i=7; i>=0; i-- )
		{
			if( m_staNoStart>0 )
				pPreview->SetSel( pPreview->LineIndex( i )+m_staNoStart-1, pPreview->LineIndex( i )+m_staNoEnd );
			else
				pPreview->SetSel( pPreview->LineIndex( i ), pPreview->LineIndex( i )+m_staNoEnd );
			pPreview->SetSelectionCharFormat( m_cfStaNo );
		}

		// Set the formatting of the Time column
		// For the header
		for( i=1; i>=0; i-- )
		{
			if( m_timeStart>0 )
				pHeader->SetSel( pHeader->LineIndex( i )+m_timeStart-1, pHeader->LineIndex( i )+m_timeEnd );
			else
				pHeader->SetSel( pHeader->LineIndex( i ), pHeader->LineIndex( i )+m_timeEnd );
			pHeader->SetSelectionCharFormat( m_cfTime );
		}
		// For the preview
		for( i=7; i>=0; i-- )
		{
			if( m_timeStart>0 )
				pPreview->SetSel( pPreview->LineIndex( i )+m_timeStart-1, pPreview->LineIndex( i )+m_timeEnd );
			else
				pPreview->SetSel( pPreview->LineIndex( i ), pPreview->LineIndex( i )+m_timeEnd );
			pPreview->SetSelectionCharFormat( m_cfTime );
		}
	}
	else
	{
		TCHAR cSeparator;
		switch( m_separator )
		{
			case 0:  cSeparator = '\t'; break;
			case 1:  cSeparator = ',' ; break;
			case 2:  cSeparator = ';' ; break;
			case 3:  cSeparator = '|' ; break;
			case 4:  cSeparator = '%' ; break;
			case 5:  cSeparator = '/' ; break;
			default: cSeparator = '\t'; break;
		}

		CString cLine;
		int nOffset, nStart;

		// Walk thru all nine lines that we're showing, whether
		// it being preview area or header
		// Note that 0-7 is for the preview and 8-9 is for the header
		for( i=9; i>=0; i-- )
		{
			// Get the line we're gonna work on
			((i/8)?pHeader:pPreview)->GetLine( i%8, cLine.GetBuffer(149), 149 );
			cLine.ReleaseBuffer();
			nOffset = 0;
			// Walk through all columns that might be required to highlight
			for( int j=0; j<=max(m_rankCol, max(m_staNoCol, m_timeCol)); j++ )
			{
				nStart=0;
				// See if there are quotes in here
				if( cLine.Find('\"')!=-1 )
				{
					// If the quotes are preceeding the next separator
					// we need to ignore the separator
					if( cLine.Find('\"')<cLine.Find(cSeparator) )
					{
						nStart = cLine.Find('\"')+1;
						nStart = cLine.Find('\"', nStart);
					}
				}

				// Select the particular piece of text in this line
				((i/8)?pHeader:pPreview)->SetSel(
					((i/8)?pHeader:pPreview)->LineIndex( i%8 )+nOffset,
					((i/8)?pHeader:pPreview)->LineIndex( i%8 )+nOffset+cLine.Find( cSeparator, nStart )+1 );

				// See if this column is one of our designated columns
				// If so, we highlight the columns
				if(j==m_rankCol)	((i/8)?pHeader:pPreview)->SetSelectionCharFormat( m_cfRank  );
				if(j==m_staNoCol)	((i/8)?pHeader:pPreview)->SetSelectionCharFormat( m_cfStaNo );
				if(j==m_timeCol)	((i/8)?pHeader:pPreview)->SetSelectionCharFormat( m_cfTime  );

				// Move on and remove what we've already used
				nOffset += cLine.Find( cSeparator, nStart )+1;
				cLine = cLine.Mid( cLine.Find( cSeparator, nStart )+1 );

				// Make sure to stop when we're done, preventing dirty leftovers
				if( cLine.Find( cSeparator )==-1 )
					break;
			}
		}
	}
	pHeader->SetSel(0,0);
	pPreview->SetSel(0,0);
}

void CImportPreview::OnChangeArrivalimportheadersize() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->GetWindowText( cBuffer );
		m_headerSize = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_headerSize > 50 )
			m_headerSize = 50;

		TCHAR czBuffer[10];
		_itot( m_headerSize, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
	
}

void CImportPreview::OnOK() 
{
	UpdateData();

	//Save the selections from this dialog
	//Restore the selections for this dialog
	LONG er;
	CString czPath;
	CSRRegKey reg;
	er = reg.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
	if( er == ERROR_SUCCESS )
	{
		reg.SetDWord( TEXT("Import type"), m_importType );
		reg.SetDWord( TEXT("Event"), m_event );
		reg.SetDWord( TEXT("Round"), m_round );
		reg.SetDWord( TEXT("Heat"), m_heat );
		reg.SetDWord( TEXT("Header size"), m_headerSize );
		reg.SetDWord( TEXT("Decimals"), m_decimals );
		reg.SetBool ( TEXT("Generate rankings"), m_rank!=0 );
		reg.SetDWord( TEXT("Rank start"), m_rankStart );
		reg.SetDWord( TEXT("Rank end"), m_rankEnd );
		reg.SetDWord( TEXT("Rank column"), m_rankCol );
		reg.SetDWord( TEXT("StaNo start"), m_staNoStart );
		reg.SetDWord( TEXT("StaNo end"), m_staNoEnd );
		reg.SetDWord( TEXT("StaNo column"), m_staNoCol );
		reg.SetDWord( TEXT("Time start"), m_timeStart );
		reg.SetDWord( TEXT("Time end"), m_timeEnd );
		reg.SetDWord( TEXT("Time column"), m_timeCol );
		reg.SetDWord( TEXT("Separation type"), m_separation );
		reg.SetDWord( TEXT("Time notation"), m_timeNotation );
		reg.SetDWord( TEXT("Separator"), m_separator );
	}

	CStageRaceWnd<CDialog>::OnOK();
}

void CImportPreview::OnArrivalimporttype() 
{
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_EVENT ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_ROUND ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_HEAT ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANK ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->EnableWindow( false );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->EnableWindow( false );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->EnableWindow( false );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->EnableWindow( false );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->EnableWindow( false );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->EnableWindow( false );
	m_importType=0;
}

void CImportPreview::OnArrivalimporttype1() 
{
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_EVENT ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_ROUND ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORT_HEAT ))->EnableWindow( false );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANK ))->EnableWindow( true );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->EnableWindow( m_separation==1 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->EnableWindow( m_separation==1 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->EnableWindow( m_separation==0 );
 	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->EnableWindow( m_separation==1 );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->EnableWindow( true );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->EnableWindow( true );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->EnableWindow( true );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->EnableWindow( true );
	((CWnd*) GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->EnableWindow( m_separation==1 );
	m_importType=1;
}

void CImportPreview::OnArrivalimportseparation1() 
{
	m_changeHandled = true;

	m_separation=1;
	OnArrivalimporttype1();
	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnArrivalimportseparation() 
{
	m_changeHandled = true;

	m_separation=0;
	OnArrivalimporttype1();
	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnChangeArrivalimportrankcol() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->GetWindowText( cBuffer );
		m_rankCol = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_rankCol > 30 ) m_rankCol = 30;

		TCHAR czBuffer[10];
		_itot( m_rankCol, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimportstanocol() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->GetWindowText( cBuffer );
		m_staNoCol = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_staNoCol > 30 ) m_staNoCol = 30;

		TCHAR czBuffer[10];
		_itot( m_staNoCol, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnChangeArrivalimporttimecol() 
{
	if( !m_changeHandled )
	{
		m_changeHandled = true;

		CString cBuffer;
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->GetWindowText( cBuffer );
		m_timeCol = _ttoi( cBuffer );

		int nStartChar, nEndChar;
		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->GetSel( nStartChar, nEndChar );
		if( !nStartChar && !nEndChar )
			nEndChar = -1;
		// Validation
		if( m_timeCol > 30 ) m_timeCol = 30;

		TCHAR czBuffer[10];
		_itot( m_timeCol, czBuffer, 10 );
		((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetWindowText( CString(czBuffer) );

		((CEdit*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetSel( nStartChar, nEndChar );

		UpdatePreview();

		m_changeHandled = false;
	}
}

void CImportPreview::OnArrivalimportalgeoptic() 
{
	m_changeHandled = true;

	m_rankCol=0;
	m_staNoCol=1;
	m_timeCol=9;

	m_decimals=3;
	m_headerSize=0;
	
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetWindowText( TEXT("0") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetWindowText( TEXT("1") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetWindowText( TEXT("9") );

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->SetWindowText( TEXT("3") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( TEXT("0") );
	
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTRANK ))->SetCheck( m_rank=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->SetCheck( !(m_separation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->SetCheck( m_separation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->SetCheck( !(m_timeNotation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->SetCheck( m_timeNotation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE ))->SetCheck( !(m_importType=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE1 ))->SetCheck( m_importType=1 );

	((CComboBox*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->SetCurSel( 0 );

	OnArrivalimporttype1();

	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnArrivalimportambchronx() 
{
	m_changeHandled = true;

	m_rankCol=0;
	m_staNoCol=1;
	m_timeCol=4;

	m_decimals=3;
	m_headerSize=0;

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetWindowText( TEXT("0") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetWindowText( TEXT("1") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetWindowText( TEXT("4") );
	
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->SetWindowText( TEXT("3") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( TEXT("0") );
	
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTRANK ))->SetCheck( m_rank=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->SetCheck( !(m_separation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->SetCheck( m_separation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->SetCheck( !(m_timeNotation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->SetCheck( m_timeNotation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE ))->SetCheck( !(m_importType=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE1 ))->SetCheck( m_importType=1 );

	((CComboBox*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->SetCurSel( 1 );

	OnArrivalimporttype1();

	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnArrivalimportlynxfinishlynx() 
{
	m_changeHandled = true;

	m_rankCol=0;
	m_staNoCol=1;
	m_timeCol=6;

	m_decimals=1;
	m_headerSize=1;

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetWindowText( TEXT("0") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetWindowText( TEXT("1") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetWindowText( TEXT("6") );
	
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->SetWindowText( TEXT("1") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( TEXT("1") );
	
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTRANK ))->SetCheck( m_rank=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->SetCheck( !(m_separation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->SetCheck( m_separation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->SetCheck( !(m_timeNotation=0) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->SetCheck( m_timeNotation=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE ))->SetCheck( !(m_importType=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE1 ))->SetCheck( m_importType=1 );

	((CComboBox*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->SetCurSel( 1 );

	OnArrivalimporttype1();

	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnArrivalimportskunkwarettware() 
{
	m_changeHandled = true;

	m_rankCol=0;
	m_staNoCol=2;
	m_timeCol=9;

	m_decimals=2;
	m_headerSize=0;

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKCOL ))->SetWindowText( TEXT("0") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOCOL ))->SetWindowText( TEXT("2") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMECOL ))->SetWindowText( TEXT("9") );
	
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->SetWindowText( TEXT("2") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( TEXT("0") );
	
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTRANK ))->SetCheck( m_rank=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->SetCheck( !(m_separation=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->SetCheck( m_separation=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->SetCheck( !(m_timeNotation=0) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->SetCheck( m_timeNotation=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE ))->SetCheck( !(m_importType=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE1 ))->SetCheck( m_importType=1 );

	((CComboBox*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->SetCurSel( 1 );

	OnArrivalimporttype1();

	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnArrivalimportomegacl() 
{
	m_changeHandled = true;

	m_rankStart=0;
	m_staNoStart=6;
	m_timeStart=29;
	m_rankEnd=3;
	m_staNoEnd=11;
	m_timeEnd=40;

	m_decimals=3;
	m_headerSize=12;

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKSTART ))->SetWindowText( TEXT("0") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOSTART ))->SetWindowText( TEXT("6") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMESTART ))->SetWindowText( TEXT("29") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTRANKEND ))->SetWindowText( TEXT("3") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTSTANOEND ))->SetWindowText( TEXT("11") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTTIMEEND ))->SetWindowText( TEXT("40") );

	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTDECIMALS ))->SetWindowText( TEXT("3") );
	((CWnd*)GetDlgItem( IDC_ARRIVALIMPORTHEADERSIZE ))->SetWindowText( TEXT("12") );
	
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTRANK ))->SetCheck( m_rank=1 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION ))->SetCheck( !(m_separation=0) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATION1 ))->SetCheck( m_separation=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION ))->SetCheck( !(m_timeNotation=0) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTIMENOTATION1 ))->SetCheck( m_timeNotation=0 );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE ))->SetCheck( !(m_importType=1) );
	((CButton*)GetDlgItem( IDC_ARRIVALIMPORTTYPE1 ))->SetCheck( m_importType=1 );

	OnArrivalimporttype1();

	UpdatePreview();

	m_changeHandled = false;
}

void CImportPreview::OnSelchangeArrivalimportseparator() 
{
	m_separator = ((CComboBox*)GetDlgItem( IDC_ARRIVALIMPORTSEPARATOR ))->GetCurSel();
	UpdatePreview();
}