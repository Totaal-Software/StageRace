// Hyperlink.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#define TOOLTIP_ID 1

/////////////////////////////////////////////////////////////////////////////
// CHyperlink

CHyperlink::CHyperlink()
{
	m_crLinkColor      = RGB(0, 0, 238);     // Blue
	m_crVisitedColor   = RGB(85, 26, 139);   // Purple
	m_bVisited          = FALSE;              // Hasn't been visited yet.
	m_bUnderline        = TRUE;               // Underline the link?
	m_bAdjustToFit      = TRUE;               // Resize the window to fit the text?
	m_strURL.Empty();
}

CHyperlink::~CHyperlink()
{
	if ((HFONT)m_Font)
		m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CHyperlink, CStatic)
	//{{AFX_MSG_MAP(CHyperlink)
	ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperlink message handlers

BOOL CHyperlink::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg);
	return CStatic::PreTranslateMessage(pMsg);
}

HBRUSH CHyperlink::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);

	// Set the approriate color
	if (m_bVisited)
		pDC->SetTextColor(m_crVisitedColor);
	else
		pDC->SetTextColor(m_crLinkColor);

	// Set underline font if required
	if (m_bUnderline) {

		if (!(HFONT)m_Font) {			// Create font only once.
			LOGFONT lf;
			GetFont()->GetLogFont(&lf);
			lf.lfUnderline = TRUE;
			m_Font.CreateFontIndirect(&lf);
		}

		pDC->SelectObject(&m_Font);
	}

	// transparent text.
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

BOOL CHyperlink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	::SetCursor(m_hLinkCursor);
	return TRUE;
}

void CHyperlink::PreSubclassWindow() 
{
	// We want to get mouse clicks via STN_CLICKED
	DWORD dwStyle = GetStyle();
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY);
	
	// Set the URL as the window text
	if (m_strURL.IsEmpty())
		GetWindowText(m_strURL);

	// Check that the window text isn't empty. If it is, set it as the URL.
	CString strWndText;
	GetWindowText(strWndText);
	if (strWndText.IsEmpty()) {
		ASSERT(!m_strURL.IsEmpty());
		SetWindowText(m_strURL);
	}

	// Adjust size of window to fit URL if necessary
	PositionWindow();		

	// Load up the hyperlink cursor
	m_hLinkCursor = LoadCursor( NULL, MAKEINTRESOURCE(32649) );
	if( !m_hLinkCursor )
		m_hLinkCursor = LoadCursor( NULL, IDC_CROSS );

	// Create the tooltip
	CRect rect; 
	GetClientRect(rect);
	m_ToolTip.Create(this);
	m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);

	CStatic::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CHyperlink operations

void CHyperlink::SetURL(CString strURL)
{
	m_strURL = strURL;
	PositionWindow();
	m_ToolTip.UpdateTipText(strURL, this, TOOLTIP_ID);
}

void CHyperlink::SetColors(COLORREF crLinkColor, COLORREF crVisitedColor) 
{ 
	m_crLinkColor    = crLinkColor; 
	m_crVisitedColor = crVisitedColor; 
	Invalidate(); 
}

void CHyperlink::SetVisited(BOOL bVisited /* = TRUE */) 
{ 
	m_bVisited = bVisited; 
	Invalidate(); 
}

void CHyperlink::SetUnderline(BOOL bUnderline /* = TRUE */)
{
	m_bUnderline = bUnderline; 
	Invalidate(); 
}

void CHyperlink::SetAutoSize(BOOL bAutoSize /* = TRUE */)
{
	m_bAdjustToFit = bAutoSize;
	PositionWindow();
}


void CHyperlink::PositionWindow()
{
	CRect rect;

	if (!m_bAdjustToFit) 
		return;

	// Get the current window position
	GetWindowRect(rect);

	CWnd* pParent = GetParent();
	if (pParent)
		pParent->ScreenToClient(rect);

	// Get the size of the window text
	CString strWndText;
	GetWindowText(strWndText);

	CDC* pDC = GetDC();
	CSize Extent = pDC->GetTextExtent(strWndText);
	ReleaseDC(pDC);

	// Get the text justification via the window style
	DWORD dwStyle = GetStyle();

	// Recalc the window size and position based on the text justification
	if (dwStyle & SS_CENTERIMAGE)
		rect.DeflateRect(0, (rect.Height() - Extent.cy) / 2);
	else
		rect.bottom = rect.top + Extent.cy;

	if (dwStyle & SS_CENTER)   
		rect.DeflateRect((rect.Width() - Extent.cx) / 2, 0);
	else if (dwStyle & SS_RIGHT) 
		rect.left  = rect.right - Extent.cx;
	else // SS_LEFT = 0, so we can't test for it explicitly 
		rect.right = rect.left + Extent.cx;

	// Move the window
	SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
// CHyperlink implementation

void CHyperlink::OnClicked()
{
	CString url;
	url = m_strURL;
	
	//Check e-mail address
	if(url.Find('@')>=0)
		url="mailto:" + url;

	int result = (int)GotoURL(url, SW_SHOW);
	m_bVisited = (result > HINSTANCE_ERROR);
	if (!m_bVisited)
		ShowError(result);
	else 
		SetVisited();						// Repaint to show visited color
}

LONG CHyperlink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS) {
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		lstrcpy(retdata,data);
		RegCloseKey(hkey);
	}

    return retval;
}

void CHyperlink::ShowError(int nError)
{
	CString str;
	switch (nError) {
		case 0:                       str = "the operating system is out of memory or resources"; break;
		case SE_ERR_PNF:              str = "the specified path was not found"; break;
		case SE_ERR_FNF:              str = "the specified file was not found"; break;
		case ERROR_BAD_FORMAT:        str = "the .EXE file is invalid (non-Win32 .EXE or error in .EXE image)"; break;
		case SE_ERR_ACCESSDENIED:     str = "the operating system denied access to the specified file"; break;
		case SE_ERR_ASSOCINCOMPLETE:  str = "the filename association is incomplete or invalid"; break;
		case SE_ERR_DDEBUSY:          str = "the DDE transaction could not be completed because other DDE transactions\nwere being processed"; break;
		case SE_ERR_DDEFAIL:          str = "the DDE transaction failed"; break;
		case SE_ERR_DDETIMEOUT:       str = "the DDE transaction could not be completed because the request timed out"; break;
		case SE_ERR_DLLNOTFOUND:      str = "the specified dynamic-link library was not found"; break;
		case SE_ERR_NOASSOC:          str = "there is no application associated with the given filename extension"; break;
		case SE_ERR_OOM:              str = "there was not enough memory to complete the operation"; break;
		case SE_ERR_SHARE:            str = "a sharing violation occurred ";
		default:                      str.Format(TEXT("unknown error (%d) occurred."), nError); break;
	}
	MessageBox( LoadStr( IDS_MBC_8 )+str, LoadStr( IDS_MBT_8 ), MB_ICONEXCLAMATION | MB_OK);
}

HINSTANCE CHyperlink::GotoURL(LPCTSTR url, int showcmd)
{
	TCHAR key[MAX_PATH + MAX_PATH];

	// First try ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

	// If it failed, get the .htm regkey and lookup the program
	if ((UINT)result <= HINSTANCE_ERROR) {

		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
			lstrcat(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) {                       // No quotes found
					pos = _tcsstr(key, _T("%1"));       // Check for %1, without quotes 
					if (pos == NULL)                   // No parameter at all...
						pos = key+lstrlen(key)-1;
					else
						*pos = '\0';                 // Remove the parameter
				}
				else
					*pos = '\0';                       // Remove the parameter

				lstrcat(pos, _T(" "));
				lstrcat(pos, url);

				// Create a process with the application and document we want
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				memset (&si, 0, sizeof (si));
				si.cb = sizeof(si);
				si.wShowWindow = SW_SHOW;

				CreateProcess(
							NULL,
							CString(key).GetBuffer(0),
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS,
							NULL,
							NULL,
							&si,
							&pi
						);
				result = (HINSTANCE)pi.hThread;
			}
		}
	}

	return result;
}

CString CHyperlink::GetURL()
{
	return m_strURL;
}

COLORREF CHyperlink::GetLinkColor()
{
	return m_crLinkColor;
}

COLORREF CHyperlink::GetVisitedColor()
{
	return m_crVisitedColor;
}

BOOL CHyperlink::GetVisited()
{
	return m_bVisited;
}

void CHyperlink::SetLinkCursor(HCURSOR hCursor)
{
	m_hLinkCursor = hCursor;
}

BOOL CHyperlink::GetUnderline()
{
	return m_bUnderline;
}

BOOL CHyperlink::GetAutoSize()
{
	return m_bAdjustToFit;
}
