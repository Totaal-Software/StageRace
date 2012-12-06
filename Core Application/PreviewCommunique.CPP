// PreviewCommunique.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewCommunique dialog


CPreviewCommunique::CPreviewCommunique(CWnd* pParent, const CStageRaceDoc* pDoc)
	: CDialog(CPreviewCommunique::IDD, pParent)
{
	m_pDoc = pDoc;
	m_ready = false;
	Create(IDD_COMMUNIQUEPREVIEW, pParent);
	//{{AFX_DATA_INIT(CPreviewCommunique)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CPreviewCommunique::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewCommunique)
	DDX_Control(pDX, IDC_BROWSER, m_browser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPreviewCommunique, CDialog)
	//{{AFX_MSG_MAP(CPreviewCommunique)
	ON_BN_CLICKED(IDOK,OnClose)
	ON_BN_CLICKED(IDCANCEL,OnClose) 
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewCommunique message handlers

void CPreviewCommunique::SetContents(CCommunique* pComm/*=NULL*/)
{
	if( pComm )
		m_communique = *pComm;
	if( !m_ready )
	{
		m_browser.Navigate( TEXT("about:blank"), 0, 0, 0, 0 );
		return;
	}

	HRESULT hr;

	// Get the browser
	IWebBrowser2* pBrowserApp;
	LPUNKNOWN lpUnk = m_browser.GetControlUnknown();
	hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**)&pBrowserApp);
	if(FAILED(hr)) return;
	
	// Get the browser contents
	LPDISPATCH lpDispatch;
	hr = pBrowserApp->get_Document(&lpDispatch);
	if(FAILED(hr)) return;
	if(!lpDispatch) return;

	// Get the html document
	IHTMLDocument3* pHtmlDoc;
	hr = lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc);
	if(FAILED(hr)) return;

	// Get the body element
	IHTMLElement *pBodyElement;
	hr = pHtmlDoc->get_documentElement(&pBodyElement);
	if(FAILED(hr)) return;

	// Put content to body element
	CString c = CHtmlDoc::CommuniqueStatic(&m_communique, m_pDoc);
	pBodyElement->put_innerHTML(c.AllocSysString());
}

BEGIN_EVENTSINK_MAP(CPreviewCommunique, CDialog)
    //{{AFX_EVENTSINK_MAP(CPreviewCommunique)
	ON_EVENT(CPreviewCommunique, IDC_BROWSER, 259 /* DocumentComplete */, OnDocumentCompleteBrowser, VTS_DISPATCH VTS_PVARIANT)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPreviewCommunique::OnDocumentCompleteBrowser(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	m_ready = true;

	// Set the contents	
	SetContents();	

	// Add the style information
	if( m_pDoc )
	{
		HRESULT hr;
		// Get the browser
		IWebBrowser2* pBrowserApp;
		LPUNKNOWN lpUnk = m_browser.GetControlUnknown();
		hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**)&pBrowserApp);
		if(FAILED(hr)) return;
		
		// Get the browser contents
		LPDISPATCH lpDispatch;
		hr = pBrowserApp->get_Document(&lpDispatch);
		if(FAILED(hr)) return;
		if(!lpDispatch) return;

		// Get the html document
		IHTMLDocument2* pHtmlDoc;
		hr = lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc);
		if(FAILED(hr)) return;

		if( ((CSettingsHTML*)m_pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_STYLE_EXTERNAL ) )
		{
			// External style sheet
				// Create a new style sheet within the (empty) document
				IHTMLStyleSheet* pStyle;
				hr = pHtmlDoc->createStyleSheet( ((CSettingsHTML*)m_pDoc->m_allsettings.GetSettings(SETT_HTML))->m_styleSheet.AllocSysString(), 0, &pStyle );
				if(FAILED(hr)) return;
		}
		else
		{
			// StageRace style info
				// Create a new style sheet within the (empty) document
				IHTMLStyleSheet* pStyle;
				hr = pHtmlDoc->createStyleSheet( NULL, 0, &pStyle );
				if(FAILED(hr)) return;

				// Set the style sheet accordingly to our settings
				pStyle->put_cssText( CHtmlDoc::GetStylePart(m_pDoc).AllocSysString() );
				if(FAILED(hr)) return;
		}
	}
}

BOOL CPreviewCommunique::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Make sure the parent is not maximized
	// it's not nice while displaying this dialog
	GetParent()->ShowWindow( SW_RESTORE );
	// Show this dialog just on the right of
	// the parent
	CRect rect;
	GetParent()->GetWindowRect( &rect );
	SetWindowPos( 0, rect.right-10, rect.top,
		max(200,GetSystemMetrics(SM_CXFULLSCREEN)-rect.right+45),
		rect.Height(), SWP_NOZORDER );

	return FALSE; // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreviewCommunique::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if( IsWindow(m_browser.GetSafeHwnd()) )
		m_browser.SetWindowPos( 0, 0, 0, cx, cy, SWP_NOMOVE );
}

void CPreviewCommunique::OnClose() 
{
	ShowWindow( SW_HIDE );
}

CPreviewCommunique::~CPreviewCommunique()
{
	DestroyWindow();
}
