////////////////////////////////////////////////////////////////
// MSDN - August 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably 
// Windows NT too.
#pragma once

//////////////////
// CDocManagerEx - extension to CDocManager that uses CFileOpenEx.
class CDocManagerEx : public CDocManager
{
public:
   CDocManagerEx();
   ~CDocManagerEx();

   // override for open/save dialog
   virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
       DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);

protected:
   // new function to create the file open dialog
   virtual CFileDialog* OnCreateFileDialog(BOOL bOpenFileDialog);

   DECLARE_DYNAMIC(CDocManagerEx)
};
