///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: HtmlDoc.h
// Description: Interface file for the CHtmlDoc class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLDOC_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_HTMLDOC_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum PUB_PARTS
{
	PP_UNKNOWN,
	PP_FIRSTTEN,
	PP_FIRSTFIVE,
	PP_PROPERTIES,
	PP_MAINCONTENT,
	PP_STATS,
	PP_SIGNATURE,
	PP_TIMESTAMP
};

class CTextDoc;
class CHtmlDoc : public CPublication
{
public:
	void EndColumns();
	void NextColumn();
	void StartColumns();
	static void MakeDummy(CEventItem, unsigned short nId);
	static CString GetStylePart(const CStageRaceDoc* pDoc);
	static CString CommuniqueStatic(CCommunique* pComm, const CStageRaceDoc *pDoc);
	static bool IsUnsafe( unsigned char cCompare );
	static CString EncodeURL( CString cURL );
	void TocRow( int nIndent, CString cContent, const CId* objId=NULL, CString cNo="" );
	void Toc();
	CHtmlDoc( CEventItem ei );
	virtual ~CHtmlDoc();
	void Legenda( PUBLI_BODYCOLUMNS columns[] );
	void CrossOut( int nCompetitors[10], int nCrossedOut[10], CTeam* pTeam );
	void SayText( PUBLI_BODYCOLUMNS columns[], CString czText );
	void Break( PUBLI_BODYCOLUMNS columns[] );
	void SaySprint( PUBLI_BODYCOLUMNS columns[], int nSprint );
	int m_nPrintedRules;
	void TeamHeader(PUBLI_BODYCOLUMNS columns[], CTeam* pTeam);
	void TeamFooter(PUBLI_BODYCOLUMNS columns[], CTeam* pTeam);
	long m_championTime;
	void Communique(CCommunique* pComm);
	void Competitor( PUBLI_BODYCOLUMNS columns[], WORD nComp, CArrival* pRank=NULL, CSignOut* pSignOut=NULL, bool bDraw=true, bool bBold=false, bool bSuppressGap=false );
	void Finish();
	void Header(unsigned short nId);
	void Footer(PUBLI_BODYCOLUMNS columns[]=NULL, CSignOutList* pSignOuts=NULL, int nNumberNotStarted=-1, int nNumberStarters=-1, int nNumberLeft=-1, CString czDroppedOut="", CString czCutOff="");
	void LabelEnd( PUB_PARTS = PP_UNKNOWN );
	void Label( PUB_PARTS = PP_UNKNOWN, bool bBegin = true );

protected:
	CTextDoc* m_ptextdoc;
	bool m_b2ByteFile;
	void WriteString(CString c);
	static CString CalculateFontSize( int nSize, const CStageRaceDoc* pDoc );
	int m_unknownlabelcounter;
	void Properties( PUBLI_PROPERTIES props[], CObject* pObj=NULL );
	void StartCompetitorsTable(PUBLI_BODYCOLUMNS columns[]);
	void ColumnTitle( CString title, int nColSpan = 1 );
	void ColumnItem( CString title, int nColSpan = 1 );
	void Property(CString caption);
	void Property(CString caption, CString property);
	void Property(CString caption, int property);
	CString UnQuote( CString s );

	bool m_competitorsStarted;

	bool m_openSuccess;

	void HtmlFooter();
	void HtmlHeader();
	void ColumnTitles( PUBLI_BODYCOLUMNS columns[] );
	void SignOuts(PUBLI_BODYCOLUMNS columns[], CSignOutList* pSignOuts);
	CStdioFile m_output;
private:
	bool m_bEvaluation;
};

#endif // !defined(AFX_HTMLDOC_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_)
