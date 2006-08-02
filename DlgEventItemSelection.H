#if !defined(AFX_DLGEventItemSelection_H__9CC81F38_6821_4328_BCAB_0F5D99EA72F7__INCLUDED_)
#define AFX_DLGEventItemSelection_H__9CC81F38_6821_4328_BCAB_0F5D99EA72F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEventItemSelection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEventItemSelection dialog

class CDlgEventItemSelection : public cdxCDynamicDialog
{
	class CPrintWebBrowser : public CWebBrowser2  
	{
		DECLARE_EVENTSINK_MAP()
		protected:
			void OnDownloadComplete();
			char m_nCopies;
		public:
			CPrintWebBrowser(int nCopies)
			{
				m_nCopies = nCopies;
			}
// Moved to .cpp because of compiler errors
//			BEGIN_EVENTSINK_MAP(CPrintWebBrowser, CWebBrowser2)
//				ON_EVENT_REFLECT(CPrintWebBrowser, 104 /* DownloadComplete */, OnDownloadComplete, VTS_NONE)
//			END_EVENTSINK_MAP()
	};
	class CPrintItem
	{
		public:
			CEventItem* m_pEventItem;
			WORD m_nCopies;
			CPrintItem( CEventItem* pEI, WORD n )
			{
				m_pEventItem = pEI;
				m_nCopies = n;
			}
			virtual ~CPrintItem()
			{
				delete m_pEventItem;
			}
	};

	DECLARE_DYNAMIC(CDlgEventItemSelection)
// Construction
public:
	void Add( CEventItem* pEI );
	virtual ~CDlgEventItemSelection();
	CDlgEventItemSelection(const CStageRaceDoc* pDoc);   // standard constructor

protected:
// Dialog Data
	//{{AFX_DATA(CDlgEventItemSelection)
	enum { IDD = IDD_DLGEVENTITEMSELECTION };
	CListCtrl	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEventItemSelection)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnCopy();
	bool m_bExclude;
	int ClearPrintItem( CPrintItem* pPI );
	CImageList m_imageList;
	void DrawPrintItem( CPrintItem* pPI, int nItem=-1 );
	const CStageRaceDoc* m_pDoc;
	CTypedPtrMap<CMapPtrToPtr,CPrintItem*,CPrintItem*> m_mapPrintItems;

	// Generated message map functions
	//{{AFX_MSG(CDlgEventItemSelection)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedEventItemSelection(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeCopies();
	afx_msg void OnPrint();
	afx_msg void OnClear();
	afx_msg void OnUpload();
	afx_msg void OnMail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEventItemSelection_H__9CC81F38_6821_4328_BCAB_0F5D99EA72F7__INCLUDED_)
