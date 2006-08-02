#if !defined(AFX_HEADERCONVERSION_H__E0D4C64F_C07C_42A2_8AB2_9F601A228209__INCLUDED_)
#define AFX_HEADERCONVERSION_H__E0D4C64F_C07C_42A2_8AB2_9F601A228209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderConversion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeaderConversion DAO recordset

class CHeaderConversion : public CDaoRecordset
{
public:
	int GetHeaderLevel( CString TopicFile );
	CHeaderConversion(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHeaderConversion)

// Field/Param Data
	//{{AFX_FIELD(CHeaderConversion, CDaoRecordset)
	CString	m_TopicFile;
	long	m_HeaderLevel;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderConversion)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual CString GetDefaultSQL();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCONVERSION_H__E0D4C64F_C07C_42A2_8AB2_9F601A228209__INCLUDED_)
