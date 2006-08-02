// HeaderConversion.cpp : implementation file
//

#include "stdafx.h"
#include "HelpTool.h"
#include "HeaderConversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderConversion

IMPLEMENT_DYNAMIC(CHeaderConversion, CDaoRecordset)

CHeaderConversion::CHeaderConversion(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHeaderConversion)
	m_TopicFile = _T("");
	m_HeaderLevel = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CHeaderConversion::GetDefaultDBName()
{
	return _T("D:\\Projects\\StageRace 2005\\Help\\English\\helptool\\helpenglish.mdb");
}

void CHeaderConversion::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHeaderConversion)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[TopicFile]"), m_TopicFile);
	DFX_Long(pFX, _T("[HeaderLevel]"), m_HeaderLevel);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderConversion diagnostics

#ifdef _DEBUG
void CHeaderConversion::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CHeaderConversion::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

int CHeaderConversion::GetHeaderLevel(CString TopicFile)
{
	if( !IsOpen() )
		Open();

	// Establish a query resulting in all the available languages 
	CDaoQueryDef Query( m_pDatabase );
	Query.Create();
	Query.SetSQL("SELECT * FROM HeaderConversion WHERE TopicFile = '"+TopicFile+"';");

	Close();
	Open( &Query );

	// Walk through the resulting recordset
	if( GetRecordCount() )
	{
		MoveFirst();
		return m_HeaderLevel;
	}
	else
		return 0;
}

CString CHeaderConversion::GetDefaultSQL() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return _T("[HeaderConversion]");
}
