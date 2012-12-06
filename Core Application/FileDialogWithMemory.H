#if !defined(AFX_FILEDIALOGWITHMEMORY_H__3BA4E971_78DC_498C_977D_E0B9497CB406__INCLUDED_)
#define AFX_FILEDIALOGWITHMEMORY_H__3BA4E971_78DC_498C_977D_E0B9497CB406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDialogWithMemory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDialogWithMemory dialog

class CFileDialogWithMemory : public CFileDialog
{
public:
	int DoModal();
	CFileDialogWithMemory(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	class CMySubClassWnd : public CButton
	{
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMySubClassWnd)
		//}}AFX_VIRTUAL
		DECLARE_MESSAGE_MAP()
	protected:
		void OnButtonWorkDir();
	} m_buttonWorkDir;

    class CDlgOuter : public CCommonDialog
    {
    public:
        CDlgOuter() : CCommonDialog(NULL)
        {
        }
    } m_dlgOuter;

    virtual void PreInitDialog();
	//{{AFX_MSG(CFileDialogWithMemory)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDIALOGWITHMEMORY_H__3BA4E971_78DC_498C_977D_E0B9497CB406__INCLUDED_)
