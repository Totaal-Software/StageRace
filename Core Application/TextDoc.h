///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: TextDoc.h
// Description: Interface file for the CTextDoc class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TextDoc_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_TextDoc_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTextDoc : public CPublication
{
public:
	bool IsFileOpened();
	void EndColumns();
	void NextColumn();
	void StartColumns();
	static void MakeDummy(CEventItem, unsigned short nId);
	CTextDoc( CEventItem ei );
	void Legenda( PUBLI_BODYCOLUMNS columns[] );
	void SayText( PUBLI_BODYCOLUMNS columns[], CString czText );
	void Break( PUBLI_BODYCOLUMNS columns[] );
	int m_nPrintedRules;
	void TeamHeader(PUBLI_BODYCOLUMNS columns[], CTeam* pTeam);
	void TeamFooter(PUBLI_BODYCOLUMNS columns[], CTeam* pTeam);
	long m_championTime;
	void Competitor( PUBLI_BODYCOLUMNS columns[], WORD nComp, CArrival* pRank=NULL, CSignOut* pSignOut=NULL, bool bDraw=true, bool bBold=false, bool bSuppressGap=false );
	void Finish();
	void Header(unsigned short nId);
	void Footer(PUBLI_BODYCOLUMNS columns[]=NULL, CSignOutList* pSignOuts=NULL, int nNumberNotStarted=-1, int nNumberStarters=-1, int nNumberLeft=-1, CString czDroppedOut="", CString czCutOff="");

protected:
	void WriteString(CString c);
	void WriteStringColumnQuote(CString c = TEXT(""));
	void WriteStringColumn(CString c = TEXT(""));
	void WriteStringLine(CString c = TEXT(""));
	void WriteStringLineComment(CString c = TEXT(""));
	int m_unknownlabelcounter;
	void Properties( PUBLI_PROPERTIES props[], CObject* pObj=NULL );
	void StartCompetitorsTable(PUBLI_BODYCOLUMNS columns[]);
	void ColumnTitle( CString title );
	void ColumnItem( CString title );
	void Property(CString caption);
	void Property(CString caption, CString property);
	void Property(CString caption, int property);
	CString UnQuote( CString s );

	bool m_competitorsStarted;

	bool m_openSuccess;

	void ColumnTitles( PUBLI_BODYCOLUMNS columns[] );
	void SignOuts(PUBLI_BODYCOLUMNS columns[], CSignOutList* pSignOuts);
	CStdioFile m_output;
private:
	bool m_bEvaluation;
};

#endif // !defined(AFX_TextDoc_H__E8EBF702_B198_11D3_92DA_0040954019F4__INCLUDED_)
