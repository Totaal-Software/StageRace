// CStageRaceDoc.cpp : Implementation of CCStageRaceDoc
#include "stdafx.h"
#include "incl.h"

/////////////////////////////////////////////////////////////////////////////
// CCStageRaceDoc

STDMETHODIMP CStageRaceComDoc::GetHalfStage(int nFS, int nHS, ISRHalfStage **ppHS)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Create new half stage CoClass
		CComObject<CSRHalfStage>* pHS = NULL;
		HRESULT hr = CComObject<CSRHalfStage>::CreateInstance(&pHS);
		if( SUCCEEDED(hr) )
		{
			pHS->AddRef();
			// Initialize half stage CoClass
			hr = pHS->Init(m_pDocument, nFS, nHS);
			if (SUCCEEDED(hr))
			{
				// Query interface as requested by user
				hr = pHS->QueryInterface(ppHS);
			}
			pHS->Release();
		}
		return hr;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CStageRaceComDoc::GetCountHalfStages(int nFS, int* pnCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check integrity of pointer
		if( pnCount )
		{
			// Get pointer to the requested full stage
			CFullStage* pFS = m_pDocument->StagesGet(nFS);
			// Check if the requested full stage actually exists
			if( pFS )
			{
				*pnCount = pFS->CountHalfStages();
				return S_OK;
			}
			else
				return E_FAIL;
		}
		else
			return E_POINTER;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CStageRaceComDoc::GetCountFullStages(int* pnCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check integrity of pointer
		if( pnCount )
		{
			// Get fill stages count
			*pnCount = m_pDocument->StagesFullCount();
			return S_OK;
		}
		else
			return E_POINTER;
	}
	else
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CStageRaceComDoc::GetHalfStageName(int nFS, int nHS, BSTR* pname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check integrity of pointer
		if( pname )
		{
			// Get pointer to the requested half stage
			CHalfStage* pHS = m_pDocument->StagesGet(nFS,nHS);
			// Check if the requested half stage actually exists
			if( pHS )
			{
				m_pDocument->Lock();
				*pname = pHS->m_title.AllocSysString();
				m_pDocument->Unlock();
				
				return S_OK;
			}
			else
				return E_FAIL;
		}
		else
			return E_POINTER;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CStageRaceComDoc::CompetitorExists(unsigned short nStaNo, BOOL *bExists)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check if asked for competitor exists
		m_pDocument->Lock();
		*bExists = m_pDocument->CompetitorsExist( nStaNo );
		m_pDocument->Unlock();

		return S_OK;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CStageRaceComDoc::GetCompetitor(unsigned short nStaNo, BSTR* pname, BSTR* pteam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check integrity of pointers
		if( pname && pteam )
		{
			m_pDocument->Lock();
			// Check if asked for competitor exists
			if( m_pDocument->CompetitorsExist(nStaNo) )
			{
				// Get asked for competitor
				CCompetitor comp = m_pDocument->CompetitorsGet(nStaNo);

				// Copy strings
				*pname = comp.m_competitor.AllocSysString();
				if( comp.m_pTeam )
					if( m_pDocument->m_bLongTeamNamesForCOM )
						*pteam = comp.m_pTeam->m_name.AllocSysString();
					else
						*pteam = comp.m_pTeam->m_code.AllocSysString();
				else
					*pteam = CString("").AllocSysString();

				m_pDocument->Unlock();
				return S_OK;
			}
			else
			{
				m_pDocument->Unlock();
				return E_FAIL;
			}
		}
		else
			return E_POINTER;
	}
	else
		return E_FAIL;
}

HRESULT CStageRaceComDoc::Init(BSTR title)
{
	// THREAD SAFETY
	// This method is potentially thread UNsafe as the
	// POSITION based calls are not in one critical section

	CWinApp* pApp = &::theApp;
	// Get the first document template as we know it is the
	// one we are looking for (and the only one there anyway)
	POSITION nPos = pApp->GetFirstDocTemplatePosition();
	if( nPos )
	{
		CDocTemplate* pDocTemplate =
			pApp->GetNextDocTemplate(nPos);

		// Walk through all currently opened
		// document instances for the template
		POSITION nPos = pDocTemplate->GetFirstDocPosition();
		while( nPos )
		{
			CDocument* pDoc = pDocTemplate->GetNextDoc(nPos);

			// Increment the number of opened COM documents of this type
			((CStageRaceDoc*)pDoc)->AddRef();

			if( pDoc->IsKindOf( RUNTIME_CLASS(CStageRaceDoc) )
				&& ( ((CStageRaceDoc*)pDoc)->FilesTitle()==
						CComBSTR(title) ) )
			{
				m_pDocument = ( (CStageRaceDoc*)pDoc );
				return S_OK;
			}
		}
	}
	return E_FAIL;
}

STDMETHODIMP CStageRaceComDoc::GetFullStageName(int nFS, BSTR *pname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Check integrity of this document
	if( m_pDocument )
	{
		// Check integrity of pointer
		if( pname )
		{
			// Get pointer to the requested full stage
			CFullStage* pFS = m_pDocument->StagesGet(nFS);
			// Check if the requested full stage actually exists
			if( pFS )
			{
				m_pDocument->Lock();
				*pname = pFS->m_date.AllocSysString();
				m_pDocument->Unlock();

				return S_OK;
			}
			else
				return E_FAIL;
		}
		else
			return E_POINTER;
	}
	else
		return E_FAIL;
}
