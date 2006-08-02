// DlgCleanupCompetitors.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanupCompetitors dialog


CDlgCleanupCompetitors::CDlgCleanupCompetitors(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_TTORDER_INTERVAL, CDlgCleanupCompetitors::IDD)
{
	//{{AFX_DATA_INIT(CDlgCleanupCompetitors)
	m_CopyUCIToCountry = FALSE;
	m_RemoveSpacesAround = FALSE;
	m_RemoveRepeatedSpaces = FALSE;
	m_CleanupCommas = FALSE;
	m_CapitalizeBeforeComma = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgCleanupCompetitors::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCleanupCompetitors)
	DDX_Check(pDX, IDC_COPYUCITOCOUNTRY, m_CopyUCIToCountry);
	DDX_Check(pDX, IDC_REMOVESPACESAROUND, m_RemoveSpacesAround);
	DDX_Check(pDX, IDC_REMOVEREPEATEDSPACES, m_RemoveRepeatedSpaces);
	DDX_Check(pDX, IDC_CLEANUPCOMMAS, m_CleanupCommas);
	DDX_Check(pDX, IDC_CAPITALIZEBEFORECOMMA, m_CapitalizeBeforeComma);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCleanupCompetitors, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgCleanupCompetitors)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanupCompetitors message handlers

int CDlgCleanupCompetitors::DoModal()
{
	if( CStageRaceWnd<CDialog>::DoModal()==IDOK )
	{
		return (CLEANUPCOMPETITORS)
			(m_RemoveRepeatedSpaces?CLC_REMOVEREPEATEDSPACES:0) |
			(m_RemoveSpacesAround?CLC_REMOVESPACESAROUND:0) |
			(m_CopyUCIToCountry?CLC_COPYUCITOCOUNTRY:0) |
			(m_CapitalizeBeforeComma?CLC_CAPITALIZEBEFORECOMMA:0) |
			(m_CleanupCommas?CLC_CLEANUPCOMMAS:0);
	}
	else
		return (CLEANUPCOMPETITORS)CLC_NONE;
}
