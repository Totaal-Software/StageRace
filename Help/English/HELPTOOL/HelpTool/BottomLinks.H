#if !defined(AFX_BOTTOMLINKS_H__3034C557_71FD_4FBC_A2BC_C657EA8F48DC__INCLUDED_)
#define AFX_BOTTOMLINKS_H__3034C557_71FD_4FBC_A2BC_C657EA8F48DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BottomLinks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBottomLinks DAO recordset

class CBottomLinks : public CDaoRecordset
{
public:
	CString GetBottomLinks(CString TopicFile, CString beforeeach, CString aftereach);
	CBottomLinks(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBottomLinks)

// Field/Param Data
	//{{AFX_FIELD(CBottomLinks, CDaoRecordset)
	CString	m_TopicFile;
	CString	m_BottomLink;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBottomLinks)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOTTOMLINKS_H__3034C557_71FD_4FBC_A2BC_C657EA8F48DC__INCLUDED_)
