// SRHalfStage.cpp : Implementation of CSRHalfStage
#include "stdafx.h"
#include "incl.h"

/////////////////////////////////////////////////////////////////////////////
// CSRHalfStage


HRESULT CSRHalfStage::Init(CStageRaceDoc *pDoc, int nFS, int nHS)
{
	if( pDoc )
	{
		CHalfStage* pStage = pDoc->StagesGet( nFS, nHS );
		if( pStage )
		{
			m_pDocument = pDoc;
			m_pHalfStage = pStage;
			m_nFullStage = nFS;
			m_nHalfStage = nHS;
			return S_OK;
		}
	}
	return E_FAIL;
}

STDMETHODIMP CSRHalfStage::GetStart(unsigned short nStaNo, unsigned short *pnOrder, unsigned long *pnUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	m_pHalfStage->m_timeTrialOrder.LockRead();

	// Check if exists in the first place
	if( m_pHalfStage->m_timeTrialOrder.Exist(nStaNo) )
	{
		// Retrieve
		CArrival arr = m_pHalfStage->m_timeTrialOrder.GetAt(nStaNo);

		// Return values
		if( pnOrder )
			*pnOrder = arr.m_order;
		if( pnUnits )
			*pnUnits = arr.m_unitsAtStart;

		m_pHalfStage->m_timeTrialOrder.UnlockRead();
		return S_OK;
	}

	m_pHalfStage->m_timeTrialOrder.UnlockRead();
	return E_FAIL;
}

STDMETHODIMP CSRHalfStage::EnumerateStarts(VARIANT *pStarts)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	VariantInit(pStarts);
	pStarts->vt = VT_ARRAY | VT_I2;

	// Get the starts in a temporary list
	const CAvailableList* pAvailList
		= m_pDocument->StagesGetAvailables(m_nFullStage, m_nHalfStage);

	CArrival objArr;
	CArrivalList lstArr;
	DWORD nState = 0;
	while( pAvailList->IterateSorted(nState, objArr) )
		lstArr.Insert( objArr );

	delete pAvailList;

	// Make an array of ints
	SAFEARRAY* psa;
	SAFEARRAYBOUND bounds = { lstArr.GetCount(), 0 };
	psa = SafeArrayCreate(VT_I2, 1, &bounds);

	WORD* iArray;
	SafeArrayAccessData(psa, (void**)&iArray);

	// Fill the array
	int i = 0;
	POSITION nPos = lstArr.GetStartPosition();
	while( nPos )
	{
		CArrival arr;
		lstArr.Iterate(nPos, arr);
		iArray[i++] = arr.m_staNo;
	}

	SafeArrayUnaccessData(psa);
	pStarts->parray = psa;

	return S_OK;
}

STDMETHODIMP CSRHalfStage::GetArrivalByRank(unsigned short nRank, unsigned short *pnStaNo, unsigned long *pnUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	m_pHalfStage->m_arrival.LockRead();

	CArrival arr;
	// Retrieve (and see if exists)
	if( m_pHalfStage->m_arrival.GetAtRank(nRank, &arr) )
	{
		// Return values
		if( pnStaNo )
			*pnStaNo = arr.m_staNo;
		if( pnUnits )
			*pnUnits = arr.m_units;

		m_pHalfStage->m_arrival.UnlockRead();
		return S_OK;
	}	
	m_pHalfStage->m_arrival.UnlockRead();
	return E_FAIL;
}

STDMETHODIMP CSRHalfStage::GetArrivalByStaNo(unsigned short nStaNo, unsigned short *pnRank, unsigned long *pnUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	m_pHalfStage->m_arrival.LockRead();

	// Check if exists in the first place
	if( m_pHalfStage->m_arrival.Exist(nStaNo) )
	{
		// Retrieve
		CArrival arr = m_pHalfStage->m_arrival.GetAt(nStaNo);

		// Return values
		if( pnRank )
			*pnRank = arr.m_rank;
		if( pnUnits )
			*pnUnits = arr.m_units;

		m_pHalfStage->m_arrival.UnlockRead();
		return S_OK;
	}	
	m_pHalfStage->m_arrival.UnlockRead();
	return E_FAIL;
}

STDMETHODIMP CSRHalfStage::GetArrivalByTime(unsigned long nUnits, unsigned short *pnStaNo, unsigned short *pnRank, unsigned long *pnUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	m_pHalfStage->m_arrival.LockRead();

	CArrival arr;
	// Retrieve (and see if exists)
	if( m_pHalfStage->m_arrival.GetAtTime(nUnits, &arr) )
	{
		// Return values
		if( pnStaNo )
			*pnStaNo = arr.m_staNo;
		if( pnRank )
			*pnRank = arr.m_rank;
		if( pnUnits )
			*pnUnits = arr.m_units;

		m_pHalfStage->m_arrival.UnlockRead();
		return S_OK;
	}	
	m_pHalfStage->m_arrival.UnlockRead();
	return E_FAIL;
}

STDMETHODIMP CSRHalfStage::ResetArrival(unsigned int nStaNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	if( !m_pDocument->InputArrivalReset(m_nFullStage, m_nHalfStage, nStaNo) )
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CSRHalfStage::SetArrivalByTime(unsigned short nStaNo, unsigned long nUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	if( !m_pDocument->InputArrivalSetByTime(m_nFullStage, m_nHalfStage, nStaNo, nUnits) )
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CSRHalfStage::SetArrivalByRank(unsigned short nStaNo, unsigned short nRank)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	if( !m_pDocument->InputArrivalSet(m_nFullStage, m_nHalfStage, nStaNo, nRank, 0/*zero time*/) )
		return E_FAIL;

	return E_NOTIMPL;
}

STDMETHODIMP CSRHalfStage::SetArrival(unsigned short nStaNo, unsigned short nRank, unsigned long nUnits)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	if( !m_pDocument->InputArrivalSet(m_nFullStage, m_nHalfStage, nStaNo, nRank, nUnits) )
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CSRHalfStage::SetTimingIdle()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	theApp.m_pMainWnd->PostMessage( WM_USER_MESSAGINGACTION, 0, 0 );

	m_pDocument->InputOnTimingIdle(m_nFullStage, m_nHalfStage);

	return S_OK;
}
