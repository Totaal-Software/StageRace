// TextOutput.h: interface for the CTextOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTOUTPUT_H__559EEDB8_6393_4E3E_86B8_90E06FE2332B__INCLUDED_)
#define AFX_TEXTOUTPUT_H__559EEDB8_6393_4E3E_86B8_90E06FE2332B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTextOutput  
{
public:
	void SkunkwareTTWare( CCompetitor *aComp, CArrival* aArr );
	void Competitor( CCompetitor* aComp, CArrival* aArr=NULL );
	int m_type;
	void Finish();
	void AlgeOpticFormat( CCompetitor* aComp );
	void AmbChronxFormat( CCompetitor* aComp );
	void OmegaScanOVisionFormat(CCompetitor *aComp);
	CStageRaceDoc* m_pDocument;
	CString m_title;
	bool m_openSuccess;
	CStdioFile m_objTheFile;
	CTextOutput(CString czPath, CString czDocTitle, int nType, CStageRaceDoc *pTheDoc);
	virtual ~CTextOutput();

};

#endif // !defined(AFX_TEXTOUTPUT_H__559EEDB8_6393_4E3E_86B8_90E06FE2332B__INCLUDED_)
