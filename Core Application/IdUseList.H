// IdUseList.h: interface for the CIdUseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDUSELIST_H__51D5EB02_F460_4DD3_98AD_9C2F1EF5ABD2__INCLUDED_)
#define AFX_IDUSELIST_H__51D5EB02_F460_4DD3_98AD_9C2F1EF5ABD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIdUseList : protected CMap<unsigned short, unsigned short&, CId*, CId*>
{
public:
	void Register(CId *pId);
	CIdUseList(CStageRaceDoc* pDoc);
	BOOL Published(CId *pId);
	BOOL Published(unsigned short nId);

	void PublishNextAvailable(CId *pId,
		CUpdateViewHint* pUVH=NULL, TREEITEMS ti=TI_UNKNOWN);
	BOOL Publish  (CId *pId,
		CUpdateViewHint* pUVH=NULL, TREEITEMS ti=TI_UNKNOWN);
	BOOL UnPublish(unsigned short nId,
		CUpdateViewHint* pUVH=NULL, TREEITEMS ti=TI_UNKNOWN);
protected:
	CStageRaceDoc* m_pDoc;
private:
	CIdUseList() {};
};

#endif // !defined(AFX_IDUSELIST_H__51D5EB02_F460_4DD3_98AD_9C2F1EF5ABD2__INCLUDED_)
