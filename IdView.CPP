// IdView.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIdView

IMPLEMENT_DYNCREATE(CIdView, CFormView)

CIdView::CIdView()
	: CFormView(CIdView::IDD)
{
	m_pId = NULL;
	//{{AFX_DATA_INIT(CIdView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CIdView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIdView)
	DDX_Control(pDX, IDC_ID, m_ctrlId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIdView, CFormView)
	//{{AFX_MSG_MAP(CIdView)
	ON_NOTIFY(UDN_DELTAPOS, IDC_IDSPIN, OnDeltaposIdspin)
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_PUBLISH_PLUS, OnEditPublishPlus)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PUBLISH_PLUS, OnUpdateEditPublishPlus)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PUBLISH_MINUS, OnUpdateEditPublishMinus)
	ON_COMMAND(ID_EDIT_PUBLISH_MINUS, OnEditPublishMinus)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdView diagnostics

#ifdef _DEBUG
void CIdView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIdView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIdView message handlers

void CIdView::Disable()
{
	((CSplitterWndFixed*)GetParent())->SetRowInfo(0,1,1);
	((CSplitterWndFixed*)GetParent())->RecalcLayout();
	((CWnd*)GetDlgItem(IDC_IDSPIN))->ShowWindow( false );
	((CWnd*)GetDlgItem(IDC_ID))->ShowWindow( false );
	((CWnd*)GetDlgItem(IDC_COMNR))->ShowWindow( false );
}

void CIdView::Enable()
{
	((CSplitterWndFixed*)GetParent())->SetRowInfo(0,31,31);
	((CSplitterWndFixed*)GetParent())->RecalcLayout();
	((CWnd*)GetDlgItem(IDC_IDSPIN))->ShowWindow( true );
	((CWnd*)GetDlgItem(IDC_ID))->ShowWindow( true );
	((CWnd*)GetDlgItem(IDC_COMNR))->ShowWindow( true );
}

void CIdView::OnDeltaposIdspin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();

	if( m_pId )
	{
		if( pNMUpDown->iDelta < 0 ) //UP
		{
			while( pDoc->m_pListID->Published( ++(m_pId->m_nId) ) );
		}
		else //DOWN
		{
			m_pId->m_nId--;
			while( pDoc->m_pListID->Published( m_pId->m_nId ) )
				m_pId->m_nId--;
		}
	}
	GetParentFrame()->SendMessage( WM_COMMAND, ID_NEXT_PANE );

	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);

	*pResult = 0;
}

void CIdView::SetBar()
{
	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();
	if( pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
	{
		Enable();
		if( m_pId )
		{
			unsigned short nID = m_pId->m_nId;
 
 			if( nID )
 			{
 				TCHAR cBuffer[10];
 				_itot( nID, cBuffer, 10 );
 
 				if( pDoc->m_pListID->Published( m_pId ) )
 				{// Red
 					m_ctrlId.SetTextColor( RGB( 255,255,255 ) );
 					m_ctrlId.SetBkColor  ( RGB( 255, 96, 96 ) );
 					DisableButton();
 				}
 				else
				if( pDoc->m_pListID->Published( m_pId->m_nId ) )
				{// Yellow
 					m_ctrlId.SetTextColor( RGB(   0,  0,  0 ) );
 					m_ctrlId.SetBkColor  ( RGB( 255,255, 96 ) );
 					EnableButton();
				}
				else
 				{// Green
 					m_ctrlId.SetTextColor( RGB(   0,  0,  0 ) );
 					m_ctrlId.SetBkColor  ( RGB(  96,255, 96 ) );
 					EnableButton();
 				}
 
 				m_ctrlId.SetWindowText( CString(cBuffer) );
 			}
 			else
 			{
 				// Green
 				m_ctrlId.SetTextColor( RGB(   0,  0,  0 ) );
 				m_ctrlId.SetBkColor  ( RGB(  96,255, 96 ) );
 
 				// Empty
 				m_ctrlId.SetWindowText( TEXT("-") );
 				EnableButton();
 			}
		}
		else
		{
 			// Gray
			m_ctrlId.SetTextColor( RGB(   0,   0,   0 ) );
			m_ctrlId.SetBkColor  ( RGB( 214, 211, 206 ) );
 
 			// Empty
 			m_ctrlId.SetWindowText( TEXT("-") );
			DisableButton();
		}
	}
	else
		Disable();
}

void CIdView::OnSize(UINT nType, int cx, int cy) 
{
	// No default call, because we don't want scroll bars
	// CFormView::OnSize(nType, cx, cy);
}

void CIdView::DisableButton()
{
	((CWnd*)GetDlgItem(IDC_IDSPIN))->EnableWindow( false );
}

void CIdView::EnableButton()
{
	((CWnd*)GetDlgItem(IDC_IDSPIN))->EnableWindow( true );
}
	

void CIdView::Set(CId *pId)
{
	m_pId = pId;
	SetBar();
}

void CIdView::Reset()
{
	m_pId = NULL;
	SetBar();
}

void CIdView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{	
	CUpdateViewHint* pUVH = (CUpdateViewHint*)pHint;
	if( pUVH && (pUVH->GetReason()==UV_DELETED) )
	{
		// This prevents from updating if data already long gone
		ASSERT(m_pId);
		m_pId = NULL;
	}
	if( IsWindow(m_hWnd) )
		if( IsWindow(m_ctrlId.m_hWnd) )
 			SetBar();
}

CId* CIdView::Get()
{
	return m_pId;
}

void CIdView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	Reset();
}

void CIdView::OnUpdateEditPublishPlus(CCmdUI* pCmdUI) 
{
	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();
	pCmdUI->Enable( (m_pId!=0) && !pDoc->m_pListID->Published( m_pId ) );
}

void CIdView::OnUpdateEditPublishMinus(CCmdUI* pCmdUI) 
{
	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();
	pCmdUI->Enable( (m_pId!=0) && !pDoc->m_pListID->Published( m_pId ) );
}

void CIdView::OnEditPublishMinus() 
{
	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();
	m_pId->m_nId--;
	while( pDoc->m_pListID->Published( m_pId->m_nId ) )
		m_pId->m_nId--;

	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);
}

void CIdView::OnEditPublishPlus() 
{
	CStageRaceDoc* pDoc = (CStageRaceDoc*) GetDocument();
	while( pDoc->m_pListID->Published( ++(m_pId->m_nId) ) );

	GetDocument()->SetModifiedFlag();
	GetDocument()->UpdateAllViews(NULL);
}

void CIdView::OnSetFocus(CWnd* pOldWnd) 
{
	CFormView::OnSetFocus(pOldWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion( (CStageRaceDoc*)GetDocument() );
}

void CIdView::OnKillFocus(CWnd* pNewWnd) 
{
	CFormView::OnKillFocus(pNewWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion(NULL);
}

