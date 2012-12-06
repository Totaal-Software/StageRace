// IdUseList.cpp: implementation of the CIdUseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

CIdUseList::CIdUseList(CStageRaceDoc* pDoc)
{
	m_pDoc = pDoc;
}

// in: the identifier integer of a publication
// out: if this identifier is listed
BOOL CIdUseList::Published(unsigned short nId)
{
	CId* pObjId=NULL;
	return Lookup( nId, pObjId );
}

// in: a pointer to the identifier of a publication
// out: if this identifier is listed
BOOL CIdUseList::Published(CId *pId)
{
	CId* pObjId=NULL;
	Lookup( pId->m_nId, pObjId );
	return (pObjId==pId);
}

// in: a pointer to the identifier of a publication and
//		variables for conveniently updating views
// out: if this identifier could be added to the list
//		thus that it wasn't listed already
//		thus that it wasn't zero
// NOTE: Publishing in the IdUseList does not really mean
//		actual publication or not, as well that a view class
//		has registered this particular identifier as being
//		published
//		Actual publication is tracked by the individual CId's
BOOL CIdUseList::Publish(CId *pId,
	CUpdateViewHint* pUVH/*=NULL*/, TREEITEMS ti/*=TI_UNKNOWN*/)
{
	if( Published( pId->m_nId ) )
		return false;
	if( pId->m_nId==0 ) // We require a non-zero value
		return false;
	pId->m_bPublished=true;
	SetAt( pId->m_nId, pId );
	
	m_pDoc->SetModifiedFlag();
	if( pUVH )
	{
		m_pDoc->UpdateAllViews( NULL, ti, (CObject*)pUVH );
	}
	
	return true;
}

void CIdUseList::PublishNextAvailable(CId *pId,
	CUpdateViewHint* pUVH/*=NULL*/, TREEITEMS ti/*=TI_UNKNOWN*/)
{
	unsigned short nId = 1;
 	// Get the next ID that is available
 	while( Published( nId ) )
 	{
 		nId++;
 		if( nId==0 ) return;	// Very unlikely, but
 								// just to prevent hangups
 	}

	if( !pId->IsPublished() )
	{
		// Publish!
		pId->m_nId = nId;
		Publish( pId, pUVH, ti );
	}
}

// in: a pointer to the identifier of a publication
// out: if this identifier could be removed from the list
//		thus that it was listed already
//		thus that it wasn't zero
BOOL CIdUseList::UnPublish(unsigned short nId,
	CUpdateViewHint* pUVH/*=NULL*/, TREEITEMS ti/*=TI_UNKNOWN*/)
{
	CId* pObjId=NULL;
	if( !Lookup( nId, pObjId ) )
		return false;
	if( pObjId==NULL )
		return false;
	pObjId->m_bPublished=false;
	
	if( !RemoveKey( nId ) )
		return false;

	m_pDoc->SetModifiedFlag();
	if( pUVH )
	{
		m_pDoc->UpdateAllViews( NULL, ti, (CObject*)pUVH );
	}

	return true;
}

void CIdUseList::Register(CId *pId)
{
	if( pId->m_bPublished
			&& pId->m_nId )
		SetAt( pId->m_nId, pId );
}
