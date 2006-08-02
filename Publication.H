// Publication.h: interface for the CPublication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICATION_H__EA37FE7D_765D_4EE8_A33C_17281C8C122D__INCLUDED_)
#define AFX_PUBLICATION_H__EA37FE7D_765D_4EE8_A33C_17281C8C122D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPublication  
{
public:
	virtual void Header(unsigned short) = 0;
	CPublication();
	virtual ~CPublication();

protected:
	DWORD m_previousGap;
	CEventItem m_ei;
	const CStageRaceDoc* m_pDocument;
};

#endif // !defined(AFX_PUBLICATION_H__EA37FE7D_765D_4EE8_A33C_17281C8C122D__INCLUDED_)
