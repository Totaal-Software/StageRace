#ifndef __CmEdit_h__
#define __CmEdit_h__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define  MAX_CHARS  256

class CmEdit : public CEdit
{
	class CmEditChar
	{
	public:    
		CmEditChar() { m_bStaticChar = false; }
		CmEditChar(CString strChars)
		{
			m_strValids = strChars;
			m_bStaticChar = false;
		}
		CmEditChar(CString strChars, bool bStaticChar)
		{
			m_strValids = strChars;
			m_bStaticChar = bStaticChar;
		}
    
		CString m_strValids;
		CString m_strData;
		bool    m_bStaticChar;
	};

public:
	CmEdit();
	virtual ~CmEdit();

    bool    Init(CString strMask, CString strInitialData = "");
    bool    SetPromptChar(CString strPromptChar);

    CString GetData();
	void SetData(const CString& data);

	//{{AFX_VIRTUAL(CmEdit)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	LRESULT Cut(WPARAM, LPARAM);
	void Cut();
	LRESULT Paste(WPARAM, LPARAM);
	void Paste();
	LRESULT Delete(WPARAM, LPARAM);
	void Delete();
    bool            m_bInit;
    CString         m_strPrompt;
    CmEditChar*     m_Char[MAX_CHARS];
    int             m_iNumChars;
    int             m_iCurrentChar;
    bool            m_bShiftDown;

    bool    Parse(const CString& strMask);
    bool    SetValidChars(const CString& strMask);
    CString GetRange(CString szLow, CString szHigh);
    //CString GetText(bool bDataOnly = false);
    //CString GetData() { return GetText(true); }
    int     FindNextChar(int iStartPos, bool bStatic, bool bForward);

    //{{AFX_MSG(CmEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
    DECLARE_DYNCREATE(CmEdit)

};

void AFXAPI DDX_CmEdit(CDataExchange* pDX, int nIDC, CmEdit& rControl, CString& data);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
