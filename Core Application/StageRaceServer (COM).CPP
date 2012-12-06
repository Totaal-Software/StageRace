// StageRaceServer.cpp : Implementation of CStageRaceServer
#include "stdafx.h"
#include "incl.h"

/////////////////////////////////////////////////////////////////////////////
// CStageRaceServer


STDMETHODIMP CStageRaceServer::EnumerateDocuments(VARIANT *pDocs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// THREAD SAFETY
	// This method is potentially thread UNsafe as the
	// POSITION based calls are not in one critical section

	CArray<CString,CString> temp;

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

			if( pDoc->IsKindOf( RUNTIME_CLASS(CStageRaceDoc) ) )
				// Add the title to the temporarely array
				temp.Add(
					((CStageRaceDoc*)pDoc)->FilesTitle() );
		}
	}


	VariantInit(pDocs);
	pDocs->vt = VT_ARRAY | VT_BSTR;

	// Make an array of BSTR's
	SAFEARRAY* psa;
	SAFEARRAYBOUND bounds = { temp.GetSize(), 0 };
	psa = SafeArrayCreate(VT_BSTR, 1, &bounds);

	BSTR* bstrArray;
	SafeArrayAccessData(psa, (void**)&bstrArray);
	
	// Fill the array
	for( int i=0; i<temp.GetSize(); i++ )
	{
		CString c = temp.GetAt(i);
		bstrArray[i] = c.AllocSysString();
	}

	SafeArrayUnaccessData(psa);
	pDocs->parray = psa;

	return S_OK;
}

STDMETHODIMP CStageRaceServer::SendMessage(BSTR user, BSTR message)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	CWinApp* pApp = &::theApp;
	pApp->m_pMainWnd->PostMessage( WM_USER_COM_OPERATORMESSAGE,
		(WPARAM)new CString(message), (LPARAM)new CString(user) );

	return S_OK;
}

STDMETHODIMP CStageRaceServer::GetDocument(BSTR title, IStageRaceDoc **ppDoc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	// Create new half stage CoClass
	CComObject<CStageRaceComDoc>* pDoc = NULL;
	HRESULT hr = CComObject<CStageRaceComDoc>::CreateInstance(&pDoc);
	if( SUCCEEDED(hr) )
	{
		pDoc->AddRef();
		// Initialize document CoClass
		hr = pDoc->Init(title);
		if (SUCCEEDED(hr))
		{
			// Query interface as requested by user
			hr = pDoc->QueryInterface(ppDoc);
		}
		pDoc->Release();
	}
	return hr;

	return S_OK;
}

STDMETHODIMP CStageRaceServer::GetActiveDocName(BSTR *pTitle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	CStageRaceApp* pApp = &::theApp;
	if( pApp->ActiveDocGet() )
		*pTitle = pApp->ActiveDocGet()->FilesTitle().AllocSysString();
	else
		return E_FAIL;

	return S_OK;
}
