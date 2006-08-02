// Correction.h: interface for the CCorrection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRECTION_H__F62D26D2_F1B7_4E98_9CCB_914CBF60051D__INCLUDED_)
#define AFX_CORRECTION_H__F62D26D2_F1B7_4E98_9CCB_914CBF60051D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCorrection : public CStaNoObject
{
public:
	unsigned short m_bonus;
	unsigned short m_penalty;

	CCorrection();
	CCorrection(const CCorrection &aCorr);
	CCorrection& operator =(const CCorrection &aCorr);
	CCorrection& operator =(const CArrival &aArr);

	void Serialize(CArchive & ar);
};

#endif // !defined(AFX_CORRECTION_H__F62D26D2_F1B7_4E98_9CCB_914CBF60051D__INCLUDED_)
