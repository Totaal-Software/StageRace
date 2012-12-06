// EditTeam.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditTeam dialog

CEditTeam::CEditTeam(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_TEAM, CEditTeam::IDD, pParent)
{

	m_pTeam = NULL;

	//{{AFX_DATA_INIT(CEditTeam)
	m_szCode = _T("");
	m_szCountry = _T("");
	m_szManager = _T("");
	m_szName = _T("");
	//}}AFX_DATA_INIT
}

void CEditTeam::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTeam)
	DDX_Text(pDX, IDC_CODE, m_szCode);
	DDV_MaxChars(pDX, m_szCode, 3);
	DDX_Text(pDX, IDC_COUNTRY, m_szCountry);
	DDX_Text(pDX, IDC_MANAGER, m_szManager);
	DDX_Text(pDX, IDC_NAME, m_szName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditTeam, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CEditTeam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTeam message handlers

CEditTeam& CEditTeam::operator=(const CEditTeam& aTeam)
{
	this->m_szCode = aTeam.m_szCode;
	this->m_szName = aTeam.m_szName;
	this->m_szManager = aTeam.m_szManager;
	this->m_szCountry = aTeam.m_szCountry;

	return *this;
}

CEditTeam& CEditTeam::operator =(const CTeam& aTeam)
{
	this->m_szCode = aTeam.m_code;
	this->m_szName = aTeam.m_name;
	this->m_szManager = aTeam.m_manager;
	this->m_szCountry = aTeam.m_country;

	return *this;
}

BOOL CEditTeam::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	// Set the maximum number of characters
	((CEdit*)GetDlgItem(IDC_CODE))->SetLimitText(3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditTeam::OnOK() 
{
	UpdateData();

	// If nothing filled in, throw an error
	if(m_szCode.IsEmpty() && m_szName.IsEmpty())
	{
		MessageBox( LoadStr( IDS_MBC_5 ), LoadStr( IDS_MBT_5 ), MB_OK | MB_ICONINFORMATION);
		((CEdit*)GetDlgItem(IDC_CODE))->SetFocus();
		return;
	}

	// If nothing filled in for team code, fill with team name
	if(m_szCode.IsEmpty())
	{
		m_szCode = m_szName;
		m_szCode.Remove(' ');
		m_szCode = m_szCode.Left(3);
		m_szCode.MakeUpper();
		UpdateData(FALSE);
	}

	// Check whether the 'Code' has been entered
	if(!m_szCode.IsEmpty())
	{
		//Check whether the 'Code' is unique
		if(m_pStageRaceDoc->TeamsExist(m_szCode))
		{
			if(m_pStageRaceDoc->TeamsGet( m_szCode )!=m_pTeam)
			{
				//The code was found and it was from a different team
				//Cancel this team with the same code
				MessageBox( LoadStr( IDS_MBC_62 ), LoadStr( IDS_MBT_62 ), MB_OK | MB_ICONINFORMATION);
				((CEdit*)GetDlgItem(IDC_CODE))->SetFocus();
				return;
			}
		}
	}
	else
		return;

	//It's now all ok
	CStageRaceWnd<CDialog>::OnOK();
}

BOOL CEditTeam::UpdateData(BOOL bSaveAndValidate/*=TRUE*/)
{
	if( !CStageRaceWnd<CDialog>::UpdateData(bSaveAndValidate) )
		return false;

	m_szCode.TrimLeft();
	m_szCode.TrimRight();
	m_szName.TrimLeft();
	m_szName.TrimRight();
	return true;
}
