// ListSignOuts.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListSignOuts dialog



CListSignOuts::CListSignOuts(	const CAvailableList* pListAvailable,
								const CSignOutList* pListSignOuts,
								const CMultiLanguage::REQUIREDLANGUAGES* pLang,
								const CCompetitorList* pListCompetitor/*=NULL*/
							)
							: CAllListPages(
								CHelp::HLP_DLG_LSTP_SO,
								CListSignOuts::IDD,
								NULL,
								pListAvailable,
								NULL )
{
	m_ctrlSignOutList.AddCompetitorSource( pListCompetitor );
	m_listSignOuts = *pListSignOuts;
	m_pLang = pLang;
	//{{AFX_DATA_INIT(CListSignOuts)
	//}}AFX_DATA_INIT
}


void CListSignOuts::DoDataExchange(CDataExchange* pDX)
{
	CAllListPages::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListSignOuts)
	DDX_Control(pDX, IDC_SIGNOUTS_LISTSIGNOUTS, m_ctrlSignOutList);
	DDX_Control(pDX, IDC_SIGNOUTS_STANO, m_staNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListSignOuts, CAllListPages)
	//{{AFX_MSG_MAP(CListSignOuts)
	ON_BN_CLICKED(IDC_SIGNOUTS_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SIGNOUTS_DELETE, OnDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SIGNOUTS_LISTSIGNOUTS, OnItemchangedSignoutsListsignouts)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListSignOuts message handlers

BOOL CListSignOuts::OnInitDialog() 
{
	CAllListPages::OnInitDialog();
	
	m_ctrlSignOutList.Init();

	// Make resizable
	AddSzControl(IDC_SIGNOUTS_LISTSIGNOUTS, mdResize, mdResize);

	AddSzControl(IDC_SIGNOUTS_LABELSTANO, mdNone, mdRepos);
	AddSzControl(IDC_SIGNOUTS_LABELREASON, mdNone, mdRepos);

	AddSzControl(IDC_SIGNOUTS_STANO, mdNone, mdRepos);
	AddSzControl(IDC_SIGNOUTS_REASON, mdResize, mdRepos);

	AddSzControl(IDC_SIGNOUTS_ADD, mdRepos, mdRepos);
	AddSzControl(IDC_SIGNOUTS_DELETE, mdRepos, mdRepos);

	// Make validation of entered StaNo possible
	m_staNo.AddStaNoObjectList( &m_listAvailable );

	// Set the edit box StaNo to default zero
	m_staNo.SetWindowText( TEXT("0") );
	
	// Fill the list boxes with availables/arrivals
	m_ctrlSignOutList.DrawList( &m_listSignOuts );

	// Retrieve the recent list of sign outs from the registry
	RestoreReasons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListSignOuts::OnAdd() 
{
	CSignOut objNew;
	CString chTemp;
	CComboBox* pctrlReason = (CComboBox*)GetDlgItem(IDC_SIGNOUTS_REASON);

	// Test whether the entered value is allowed, only zero is not allowed so far
	if( m_staNo.Exist() )
	{
		// If the new sign out consists of a proper StaNo, we proceed
		// We first put the additional data into the CSignOut object
		objNew.m_staNo = m_staNo.GetValue();
		((CEdit*)GetDlgItem( IDC_SIGNOUTS_REASON ))->GetWindowText( objNew.m_reasonOfSignOut );

		if( objNew.m_reasonOfSignOut.GetLength() )
		{
			// We insert it in the view
			m_ctrlSignOutList.Draw( &objNew );

			// We insert the sign out in the data
			m_listSignOuts.Insert( objNew );	

			// Add the entered reason to the combobox
			{
				CString szReasonFromList;
				CString szReasonEntered;
				pctrlReason->GetWindowText(szReasonEntered);
				bool bIsAdded=false;
				if(szReasonEntered.GetLength()>0)
					for(int i=0; i<pctrlReason->GetCount() && !bIsAdded; i++)
					{
						pctrlReason->GetLBText(i, szReasonFromList);
						if(!szReasonFromList.CompareNoCase(szReasonEntered))
						{
							pctrlReason->SetItemData(i, ++m_nLastUseValue);
							bIsAdded=true;
						}				
					}
				if(!bIsAdded)
				{
					//It's not is the list, so add a new item
					int nIndex = pctrlReason->AddString(szReasonEntered);
					pctrlReason->SetItemData(nIndex, ++m_nLastUseValue);
				}
			}
		}
	}
}

void CListSignOuts::OnDelete() 
{
	m_listSignOuts.Remove( m_ctrlSignOutList.GetSelected() );
	m_ctrlSignOutList.Clear( m_ctrlSignOutList.GetSelected() );
}

// Stores the recent list of sign outs from the registry
void CListSignOuts::StoreReasons()
{
	//ItemData explanation
	//--------------------
	//Each time a reason is sign out is added the reason is added to the combo box.
	//The ItemData of the combobox item contains a number. The higher the number the
	//more recent the reason.
	
	CComboBox* pctrlReasons = (CComboBox*)GetDlgItem(IDC_SIGNOUTS_REASON);
	
	int i;
	
	struct REASON_LIST
	{
		CString szReason;
		long lItemData;
	} ToBeStored[10]; //Maximum number of reasons to be stored is 10

	// Set all dwItemData's to -1. This indicates it's empty
	for(i=0; i<10; i++)
		ToBeStored[i].lItemData=-1;
	
	// Iterate through the list
	for(int nIndex=0; nIndex<pctrlReasons->GetCount(); nIndex++)
	{
		bool bIsReady=false;

		//Get the itemData
		DWORD dwItemData = pctrlReasons->GetItemData(nIndex);

		//Check for available/empty storage
		for(i=0; i<10 && !bIsReady; i++)
		{
			if(ToBeStored[i].lItemData==-1)
			{
				ToBeStored[i].lItemData = dwItemData;
				pctrlReasons->GetLBText(nIndex, ToBeStored[i].szReason);
				bIsReady=true;
			}	
		}

		//If not yet ready then search for the lowest lItemData
		if(!bIsReady)
		{
			long lLowest=-1;
			int nArrayIndex=-1;
			for(i=0; i<10; i++)
			{
				if(ToBeStored[i].lItemData<lLowest || lLowest==-1)
				{
					lLowest=ToBeStored[i].lItemData;
					nArrayIndex=i;
				}	
			}
			//And if the lowest is lower than the current combobox item than overwrite
			if(lLowest < (long)dwItemData)
			{
				ToBeStored[nArrayIndex].lItemData = dwItemData;
				pctrlReasons->GetLBText(nIndex, ToBeStored[nArrayIndex].szReason);
				bIsReady=true;				
			}
		}
	}

	LONG er;
	CSRRegKey reg;
	er = reg.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Sign outs reasons") );
	if( er == ERROR_SUCCESS )
	{
		// Now it's time to store the collected data in the registry
		for(i=0; i<10; i++)
		{
			char index[2];
			index[1]='\0';
			if(ToBeStored[i].lItemData!=-1)
			{
				index[0] = '0' + i;
				reg.SetString( CString(index), ToBeStored[i].szReason );
			}
		}
	}
}

// Retrieves the recent list of sign outs from the registry
void CListSignOuts::RestoreReasons()
{
	CComboBox* pctrlReasons = (CComboBox*)GetDlgItem(IDC_SIGNOUTS_REASON);
	pctrlReasons->Clear();

	CString cReason;
	int nItemIndex;
	bool bAddedSomething = false;
	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Sign outs reasons") );
	if( er == ERROR_SUCCESS )
	{
		char index[2];
		index[1]='\0';

		// Do this ten times at maximum
		for(int i=0; i<10; i++)
		{
			index[0] = '0' + i;
			// Get every string from the registry
			cReason = reg.GetString( CString(index), TEXT("") );

			// If the obtained string is not empty...
			if( !cReason.IsEmpty() )
			{
				// ... add it to the combo box
				nItemIndex=pctrlReasons->AddString(cReason);
				pctrlReasons->SetItemData(nItemIndex, 0);
				bAddedSomething = true;
			}
		}
	}
	if( (er!=ERROR_SUCCESS) || !bAddedSomething )
	{
		// Something went wrong or there are no values available
		// Add default values to the combobox
		nItemIndex = pctrlReasons->AddString( AssembleStr( TEXT("ReasonNotSgn"), TEXT(" - "), m_pLang ) );
		pctrlReasons->SetItemData(nItemIndex, 0);
		nItemIndex = pctrlReasons->AddString( AssembleStr( TEXT("ReasonInjury"), TEXT(" - "), m_pLang ) );
		pctrlReasons->SetItemData(nItemIndex, 0);
		nItemIndex = pctrlReasons->AddString( AssembleStr( TEXT("ReasonSick"), TEXT(" - "), m_pLang ) );
		pctrlReasons->SetItemData(nItemIndex, 0);
		nItemIndex = pctrlReasons->AddString( AssembleStr( TEXT("ReasonDisqlf"), TEXT(" - "), m_pLang ) );
		pctrlReasons->SetItemData(nItemIndex, 0);
	}
}

void CListSignOuts::OnOK() 
{
	// Store the recent list of sign outs from to registry
	StoreReasons();
	
	CAllListPages::OnOK();
}

void CListSignOuts::OnItemchangedSignoutsListsignouts(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( m_ctrlSignOutList.GetSelectedCount() )
	{
		CSignOut aSignOut = m_listSignOuts.GetAt( m_ctrlSignOutList.GetSelected() );
		m_staNo.SetValue( aSignOut.m_staNo );
		GetDlgItem( IDC_SIGNOUTS_REASON )->SetWindowText( aSignOut.m_reasonOfSignOut );
	}
	
	*pResult = 0;
}

BOOL CListSignOuts::PreTranslateMessage(MSG *pMsg)
{
	// Check for [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_RETURN )
	{
		OnAdd();

		return TRUE;
	};
	
	return CAllListPages::PreTranslateMessage(pMsg);
}
