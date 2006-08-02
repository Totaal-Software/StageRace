////////////////////////////////////////////////////////////////
// MSDN -- August 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// CDocManagerEx overrides one function in CDocManager, namely
// DoPromptFileName, to use some other file dialog than the default one.
//
// To use this class, just add the line
//    m_pDocManager = new CDocManagerEx;
// to your app's InitInstance function,
// before you add any document templates.
#include "stdafx.h"
#include <afxpriv.h>
#include "DocManagerEx.h"
#include "FileDialogWithMemory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

AFX_STATIC void AFXAPI _AfxAppendFilterSuffix(CString& filter,
   OPENFILENAME& ofn, CDocTemplate* pTemplate, CString* pstrDefaultExt);

IMPLEMENT_DYNAMIC(CDocManagerEx, CDocManager)

CDocManagerEx::CDocManagerEx()
{
}

CDocManagerEx::~CDocManagerEx()
{
}

//////////////////
// New function to create the file dialog. Override to create some different
// kind of CFileDialog if you want. Default creates a CFileDialog
CFileDialog* CDocManagerEx::OnCreateFileDialog(BOOL bOpenFileDialog)
{
   TRACE(_T("CDocManagerEx::OnCreateFileDialog\n"));
   return new CFileDialogWithMemory(bOpenFileDialog);
}

//////////////////
// This function is copied from MFC's docmgr.cpp, with
// one minor modification to use OnCreateFileDialog.
BOOL CDocManagerEx::DoPromptFileName(CString& fileName, UINT nIDSTitle,
   DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
   CFileDialog* pDlg = OnCreateFileDialog(bOpenFileDialog);
   ASSERT(pDlg);
   CFileDialog& dlgFile = *pDlg;
   
   CString title;
   VERIFY(title.LoadString(nIDSTitle));

   dlgFile.m_ofn.Flags |= lFlags;

   CString strFilter;
   CString strDefault;
   if (pTemplate != NULL)
   {
      ASSERT_VALID(pTemplate);
      _AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
   }
   else
   {
      // Do for all doc template
      POSITION pos = m_templateList.GetHeadPosition();
      BOOL bFirst = TRUE;
      while (pos != NULL)
      {
         CDocTemplate* pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
         _AfxAppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
            bFirst ? &strDefault : NULL);
         bFirst = FALSE;
      }
   }

   // Append the "*.*" all files filter
   CString allFilter;
   VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
   strFilter += allFilter;
   strFilter += (TCHAR)'\0';   // Next string please
   strFilter += _T("*.*");
   strFilter += (TCHAR)'\0';   // Last string
   dlgFile.m_ofn.nMaxCustFilter++;

   dlgFile.m_ofn.lpstrFilter = strFilter;
   dlgFile.m_ofn.lpstrTitle = title;
   dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

   int nResult = dlgFile.DoModal();
   fileName.ReleaseBuffer();

   delete pDlg;

   return nResult == IDOK;
}

//////////////////
// This function is copied verbatim from MFC's docmgr.cpp
// Required here because it's a static funcition.
AFX_STATIC void AFXAPI _AfxAppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
   CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
   ASSERT_VALID(pTemplate);
   ASSERT_KINDOF(CDocTemplate, pTemplate);

   CString strFilterExt, strFilterName;
   if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
    !strFilterExt.IsEmpty() &&
    pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
    !strFilterName.IsEmpty())
   {
      // a file based document template - add to filter list
      ASSERT(strFilterExt[0] == '.');
      if (pstrDefaultExt != NULL)
      {
         // set the default extension
         *pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
         ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
         ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
      }

      // add to filter
      filter += strFilterName;
      ASSERT(!filter.IsEmpty());  // must have a file type name
      filter += (TCHAR)'\0';  // next string please
      filter += (TCHAR)'*';
      filter += strFilterExt;
      filter += (TCHAR)'\0';  // next string please
      ofn.nMaxCustFilter++;
   }
}