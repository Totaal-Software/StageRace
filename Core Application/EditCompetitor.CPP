// Competitor.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCompetitor dialog

CEditCompetitor::CEditCompetitor(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_COMP, CEditCompetitor::IDD, pParent)
{
	m_pTeam = NULL;
	m_rememberedStaNo = 0;

	//{{AFX_DATA_INIT(CEditCompetitor)
	m_category = _T("");
	m_competitor = _T("");
	m_license = _T("");
	m_mask1 = FALSE;
	m_mask2 = FALSE;
	m_mask3 = FALSE;
	m_mask4 = FALSE;
	m_mask5 = FALSE;
	m_mask6 = FALSE;
	m_mask7 = FALSE;
	m_mask8 = FALSE;
	m_mask9 = FALSE;
	m_mask10 = FALSE;
	m_UCICode = _T("");
	m_staNo = 0;
	m_countryCode = _T("");
	//}}AFX_DATA_INIT
}


void CEditCompetitor::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditCompetitor)
	DDX_Text(pDX, IDC_CATEGORY, m_category);
	DDV_MaxChars(pDX, m_category, 11);
	DDX_Text(pDX, IDC_COMPETITOR, m_competitor);
	DDV_MaxChars(pDX, m_competitor, 50);
	DDX_Text(pDX, IDC_LICENSE, m_license);
	DDV_MaxChars(pDX, m_license, 11);
	DDX_Check(pDX, IDC_MASK1, m_mask1);
	DDX_Check(pDX, IDC_MASK2, m_mask2);
	DDX_Check(pDX, IDC_MASK3, m_mask3);
	DDX_Check(pDX, IDC_MASK4, m_mask4);
	DDX_Check(pDX, IDC_MASK5, m_mask5);
	DDX_Check(pDX, IDC_MASK6, m_mask6);
	DDX_Check(pDX, IDC_MASK7, m_mask7);
	DDX_Check(pDX, IDC_MASK8, m_mask8);
	DDX_Check(pDX, IDC_MASK9, m_mask9);
	DDX_Check(pDX, IDC_MASK10, m_mask10);
	DDX_Text(pDX, IDC_UCICODE, m_UCICode);
	DDV_MaxChars(pDX, m_UCICode, 11);
	DDX_Text(pDX, IDC_STANO, m_staNo);
	DDX_Text(pDX, IDC_COUNTRYCODE, m_countryCode);
	DDV_MaxChars(pDX, m_countryCode, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditCompetitor, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CEditCompetitor)
	ON_CBN_SELCHANGE(IDC_TEAM, OnSelchangeTeam)
	ON_BN_CLICKED(IDC_NEWTEAM, OnNewteam)
	ON_EN_CHANGE(IDC_STANO, OnChangeStano)
	ON_BN_CLICKED(IDC_STANO_NONACTIVE, OnStanoNonactive)
	ON_BN_CLICKED(IDC_STANO_ACTIVE, OnStanoActive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditCompetitor message handlers

CEditCompetitor& CEditCompetitor::operator=(const CEditCompetitor& aComp)
{
	this->m_staNo = aComp.m_staNo;
	this->m_competitor = aComp.m_competitor;
	this->m_pTeam = aComp.m_pTeam;
	this->m_countryCode = aComp.m_countryCode;
	this->m_UCICode = aComp.m_UCICode;
	this->m_license = aComp.m_license;
	this->m_category = aComp.m_category;
	this->m_mask1 = aComp.m_mask1;
	this->m_mask2 = aComp.m_mask2;
	this->m_mask3 = aComp.m_mask3;
	this->m_mask4 = aComp.m_mask4;
	this->m_mask5 = aComp.m_mask5;
	this->m_mask6 = aComp.m_mask6;
	this->m_mask7 = aComp.m_mask7;
	this->m_mask8 = aComp.m_mask8;
	this->m_mask9 = aComp.m_mask9;
	this->m_mask10 = aComp.m_mask10;
	return *this;
}

CEditCompetitor& CEditCompetitor::operator =(const CCompetitor & aComp)
{
	this->m_staNo = aComp.m_staNo;
	this->m_competitor = aComp.m_competitor;
	this->m_pTeam = aComp.m_pTeam;
	this->m_countryCode = aComp.m_countryCode;
	this->m_UCICode = aComp.m_UCICode;
	this->m_license = aComp.m_license;
	this->m_category = aComp.m_category;
	this->m_mask1 = aComp.m_mask1;
	this->m_mask2 = aComp.m_mask2;
	this->m_mask3 = aComp.m_mask3;
	this->m_mask4 = aComp.m_mask4;
	this->m_mask5 = aComp.m_mask5;
	this->m_mask6 = aComp.m_mask6;
	this->m_mask7 = aComp.m_mask7;
	this->m_mask8 = aComp.m_mask8;
	this->m_mask9 = aComp.m_mask9;
	this->m_mask10 = aComp.m_mask10;
	return *this;
}

BOOL CEditCompetitor::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	int nIndex;
	CComboBox* ctrlCombo = (CComboBox*)GetDlgItem(IDC_TEAM);
	ctrlCombo->Clear();
	CTeam* pTeam = NULL;

	//Populate the combo-box with teams
		//Add empty string to select no team
			nIndex = ctrlCombo->AddString(TEXT("-"));
			ctrlCombo->SetItemData(nIndex, 0);

		//Add the whole list of teams
		POSITION hPos;
		CString szKey;
		pTeam = NULL;
		hPos = m_pStageRaceDoc->TeamsGetStartPosition();
		while(hPos)
		{
			//Get the team pointer
			m_pStageRaceDoc->TeamsIterate(hPos, (const CTeam*&)pTeam);
			//Add the team to the list
			CString tempTeam;
			tempTeam = pTeam->m_code + " " + pTeam->m_name;
			nIndex = ctrlCombo->AddString(tempTeam);
			ctrlCombo->SetItemData(nIndex, (DWORD)pTeam);
		}
	
	//Select the right team
	int nIndexToSelect = -1;
	for(int i=0;i < ctrlCombo->GetCount(); i++)
	{
		if(m_pTeam==(CTeam*)(ctrlCombo->GetItemData(i)))
		{
			nIndexToSelect = i;
			break;
		}
	}
	if(nIndexToSelect==-1)
	{
		MessageBox( LoadStr( IDS_MBC_1 ), LoadStr( IDS_MBT_1 ), MB_OK | MB_ICONWARNING);
		nIndexToSelect = 0;
		m_pTeam = 0;
	}
	ctrlCombo->SetCurSel(nIndexToSelect);
	
	//Show only used masks
	((CEdit*)GetDlgItem(IDC_MASK1))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1));
	((CEdit*)GetDlgItem(IDC_MASK2))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2));
	((CEdit*)GetDlgItem(IDC_MASK3))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3));
	((CEdit*)GetDlgItem(IDC_MASK4))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4));
	((CEdit*)GetDlgItem(IDC_MASK5))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5));
	((CEdit*)GetDlgItem(IDC_MASK6))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6));
	((CEdit*)GetDlgItem(IDC_MASK7))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7));
	((CEdit*)GetDlgItem(IDC_MASK8))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8));
	((CEdit*)GetDlgItem(IDC_MASK9))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9));
	((CEdit*)GetDlgItem(IDC_MASK10))->ShowWindow(m_pStageRaceDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10));

	//Adjust the mask texts
	((CEdit*)GetDlgItem(IDC_MASK1))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1==""?LoadStr(IDS_DIV98)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1+" ("+LoadStr(IDS_DIV98)+")");
	((CEdit*)GetDlgItem(IDC_MASK2))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2==""?LoadStr(IDS_DIV99)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2+" ("+LoadStr(IDS_DIV99)+")");
	((CEdit*)GetDlgItem(IDC_MASK3))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3==""?LoadStr(IDS_DIV100)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3+" ("+LoadStr(IDS_DIV100)+")");
	((CEdit*)GetDlgItem(IDC_MASK4))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4==""?LoadStr(IDS_DIV106)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4+" ("+LoadStr(IDS_DIV106)+")");
	((CEdit*)GetDlgItem(IDC_MASK5))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5==""?LoadStr(IDS_DIV107)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5+" ("+LoadStr(IDS_DIV107)+")");
	((CEdit*)GetDlgItem(IDC_MASK6))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6==""?LoadStr(IDS_DIV108)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6+" ("+LoadStr(IDS_DIV108)+")");
	((CEdit*)GetDlgItem(IDC_MASK7))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7==""?LoadStr(IDS_DIV109)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7+" ("+LoadStr(IDS_DIV109)+")");
	((CEdit*)GetDlgItem(IDC_MASK8))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8==""?LoadStr(IDS_DIV110)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8+" ("+LoadStr(IDS_DIV110)+")");
	((CEdit*)GetDlgItem(IDC_MASK9))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9==""?LoadStr(IDS_DIV111)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9+" ("+LoadStr(IDS_DIV111)+")");
	((CEdit*)GetDlgItem(IDC_MASK10))->SetWindowText(
		((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10==""?LoadStr(IDS_DIV112)
			:((CSettingsGeneral*)m_pStageRaceDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10+" ("+LoadStr(IDS_DIV112)+")");

	//Make the radio buttons properly reflect the sort of StaNo
	OnChangeStano();

	//Remember the current StaNo
	m_oldStaNo = m_staNo;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditCompetitor::OnSelchangeTeam() 
{
	CComboBox* ctrlCombo = (CComboBox*)GetDlgItem(IDC_TEAM);
	m_pTeam = (CTeam*)ctrlCombo->GetItemData(ctrlCombo->GetCurSel());
}

void CEditCompetitor::OnOK() 
{
	//Check whether the 'StaNo' is unique
	UpdateData();
	if(m_staNo!=m_oldStaNo)
	{
		TCHAR buf[10];
		int nStaNo;
		((CEdit*)GetDlgItem(IDC_STANO))->GetWindowText(buf, 10);
		nStaNo = _ttoi(buf);
		if(m_pStageRaceDoc->CompetitorsExist(nStaNo)
			&& nStaNo)
		{
			//The StaNo was found
			//Cancel this competitor with the same code
			MessageBox( LoadStr( IDS_MBC_4 ), LoadStr( IDS_MBT_4 ), MB_OK | MB_ICONINFORMATION);
			((CEdit*)GetDlgItem(IDC_STANO))->SetFocus();
			return;
		}
	}

	//It's now all ok
	CStageRaceWnd<CDialog>::OnOK();
}

void CEditCompetitor::OnNewteam() 
{
	CTeam* pNewTeam = NULL;
	((CStageRaceDoc*)m_pStageRaceDoc)->TeamsNew(FALSE, &pNewTeam);
	if( pNewTeam )
	{
		//Assign the new team to this competitor
		m_pTeam = pNewTeam;
		//Add the team to the dropdown list
		CComboBox* ctrlCombo = (CComboBox*)GetDlgItem(IDC_TEAM);
			// Add the string
			CString tempTeam;
			tempTeam = m_pTeam->m_code + " " + m_pTeam->m_name;
			int nIndex = ctrlCombo->AddString(tempTeam);
			// Set the item data
			ctrlCombo->SetItemData(nIndex, (DWORD)m_pTeam);
			// Set it to be the current selection
			ctrlCombo->SetCurSel(nIndex);
	}
}

void CEditCompetitor::OnChangeStano() 
{
	CString cStaNo;
	GetDlgItemText( IDC_STANO, cStaNo );
	//Make sure the StaNo is within range
	if( _ttoi( cStaNo )>=65536 )
	{
		SetDlgItemText( IDC_STANO, TEXT("65535") );
		((CEdit*)GetDlgItem(IDC_STANO))->SetSel(cStaNo.GetLength(), -1);
	}
	//Make the radio buttons properly reflect the sort of StaNo
	if( _ttoi( cStaNo )>0 )
	{
		GetDlgItem( IDC_STANO_ACTIVE )->EnableWindow();
		m_rememberedStaNo = _ttoi( cStaNo );

		((CButton*)GetDlgItem( IDC_STANO_NONACTIVE ))->SetCheck( false );
		((CButton*)GetDlgItem( IDC_STANO_ACTIVE ))->SetCheck( true );
	}
	else // StaNo==0
	{
		if( !m_rememberedStaNo )
			GetDlgItem( IDC_STANO_ACTIVE )->EnableWindow(false);

		((CButton*)GetDlgItem( IDC_STANO_NONACTIVE ))->SetCheck( true );
		((CButton*)GetDlgItem( IDC_STANO_ACTIVE ))->SetCheck( false );
	}
}

void CEditCompetitor::OnStanoNonactive() 
{
	SetDlgItemText( IDC_STANO, TEXT("0") );
}

void CEditCompetitor::OnStanoActive() 
{
	TCHAR czBuffer[10];
	_itot( m_rememberedStaNo, czBuffer, 10 );
	SetDlgItemText( IDC_STANO, czBuffer );
}
