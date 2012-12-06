// BottomLinks.cpp : implementation file
//

#include "stdafx.h"
#include "HelpTool.h"
#include "BottomLinks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBottomLinks

IMPLEMENT_DYNAMIC(CBottomLinks, CDaoRecordset)

CBottomLinks::CBottomLinks(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBottomLinks)
	m_TopicFile = _T("");
	m_BottomLink = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CBottomLinks::GetDefaultDBName()
{
	return _T("D:\\Projects\\StageRace\\trunk\\Help\\English\\helptool\\helpenglish.mdb");
}

CString CBottomLinks::GetDefaultSQL()
{
	return _T("[BottomLinks]");
}

void CBottomLinks::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBottomLinks)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[TopicFile]"), m_TopicFile);
	DFX_Text(pFX, _T("[BottomLink]"), m_BottomLink);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBottomLinks diagnostics

#ifdef _DEBUG
void CBottomLinks::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CBottomLinks::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CString CBottomLinks::GetBottomLinks(CString TopicFile, CString beforeeach, CString aftereach)
{
	if( !IsOpen() )
		Open();

	// Establish a query resulting in all the available languages 
	CDaoQueryDef Query( m_pDatabase );
	Query.Create();
	Query.SetSQL("SELECT * FROM BottomLinks WHERE TopicFile = '"+TopicFile+"';");

	Close();
	Open( &Query );

	// Walk through the resulting recordset
	if( GetRecordCount() )
	{
		MoveFirst();
		CString cBottomLinks;
		while( !IsEOF() )
		{
			cBottomLinks += beforeeach + m_BottomLink + aftereach;
			MoveNext();
		}
		return cBottomLinks;
	}
	else
		return "";
}