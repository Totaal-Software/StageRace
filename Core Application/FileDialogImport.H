#if !defined(AFX_FILEDIALOGIMPORT_H__FD839510_0493_42D2_9331_9913DC719B62__INCLUDED_)
#define AFX_FILEDIALOGIMPORT_H__FD839510_0493_42D2_9331_9913DC719B62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDialogImport.h: interface for the CFileDialogImport class.
//

/////////////////////////////////////////////////////////////////////////////
// CFileDialogImport dialog

class CFileDialogImport : public CFileDialogWithMemory  
{
public:
	int DoModal();
	CFileDialogImport(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	bool GetSuppressPreview() { return m_buttonSuppressPreview.m_suppressPreview; }
	void SetSuppressPreview(bool b) { m_buttonSuppressPreview.m_suppressPreview = b; }
protected:
	class CMySubClassWnd : public CButton
	{
		friend CFileDialogImport;
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMySubClassWnd)
		//}}AFX_VIRTUAL
		DECLARE_MESSAGE_MAP()
	protected:
		void OnButtonSuppressPreview();
		bool m_suppressPreview;
	} m_buttonSuppressPreview;
 
	//{{AFX_MSG(CFileDialogImport)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_FILEDIALOGIMPORT_H__FD839510_0493_42D2_9331_9913DC719B62__INCLUDED_)
