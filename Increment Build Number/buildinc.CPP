// buildinc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "buildinc.h"
#include <iostream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class VersionInfo {
    public:
       VersionInfo() { major = 1; minor = 0; patch = 0; build = 0; dot = FALSE; }
       CString Format();
       BOOL parse(CString & s);
       void TimeStamp() { t = CTime::GetCurrentTime(); }
       CString FormatTimeStamp()
	  {
	   CString s;
	   s = t.Format(_T("%Y-%m-%d %H:%M:%S (%a, %d-%b)"));
	   return s;
	  }
    protected:
       BOOL dot;
       UINT major;
       UINT minor;
       UINT patch;
       enum{STATE_SPACE, STATE_NUM1, STATE_NUM2, STATE_NUM3, STATE_NUM4};
       CTime t;
    public:
	    UINT GetIncludeValue();
       UINT build;
};

/****************************************************************************
*                            VersionInfo::parse
* Inputs:
*       CString & s: Input text
* Result: BOOL
*       TRUE if successful
*	FALSE if error
* Effect: 
*       Sets the version data
****************************************************************************/

BOOL VersionInfo::parse(CString & s)
    {
     int state = STATE_SPACE;
     int nextstate = STATE_NUM1;
     UINT number;
     LPCTSTR p = s;
     while(*p)
	{ /* loop */
	 switch(state)
	    { /* state */
	     case STATE_SPACE:
		switch(*p)
		   { /* decode */
		    case _T(' '):
		       p++;
		       continue;
		    case _T('0'):
		    case _T('1'):
		    case _T('2'):
		    case _T('3'):
		    case _T('4'):
		    case _T('5'):
		    case _T('6'):
		    case _T('7'):
		    case _T('8'):
		    case _T('9'):
		       number = 0;
		       state = nextstate;
		       continue;
		   } /* decode */
	     case STATE_NUM1:
	     case STATE_NUM2:
	     case STATE_NUM3:
	     case STATE_NUM4:
		switch(*p)
		   { /* p */
		    case _T('0'):
		    case _T('1'):
		    case _T('2'):
		    case _T('3'):
		    case _T('4'):
		    case _T('5'):
		    case _T('6'):
		    case _T('7'):
		    case _T('8'):
		    case _T('9'):
		       number = number * 10 + *p - _T('0');
		       p++;
		       continue;
		    case _T('.'):
		       dot = TRUE;
		       // FALLS THRU
		    case _T(','):
		       switch(state)
			  { /* next state */
			   case STATE_NUM1:
			      major = number;
			      nextstate = STATE_NUM2;
			      break;
			   case STATE_NUM2:
			      minor = number;
			      nextstate = STATE_NUM3;
			      break;
			   case STATE_NUM3:
			      patch = number;
			      nextstate = STATE_NUM4;
			      break;
			   default:
			      cout << _T("BuildInc: Syntax error: unexpected character (2) '") << *p << _T("'\n");
			      return FALSE;
			  } /* next state */
		       state = STATE_SPACE;
		       p++;	
		       continue;
		    case _T('\t'):
		    case _T('\n'):
		       if(state != STATE_NUM4)
			  { /* illegal terminator */
			   cout << _T("BuildInc: Syntax error: unexpected character (3) '\\t' or '\\n'\n");
			   return FALSE;
			  } /* illegal terminator */
		       build = number;
		       return TRUE;
		    default:
		       cout << _T("BuildInc: Syntax error: unexpected character (4) '") << *p << _T("'\n");
		       return FALSE;
		   } /* p */
	     default:
		cout << _T("BuildInc: Syntax error: unexpected state '") << state << _T("'\n");
		return FALSE;
	    } /* state */
	} /* loop */
     cout << _T("BuildInc: Syntax error: unexpected end-of-string\n");
     return FALSE;
    } // VersionInfo::parse

/****************************************************************************
*                            VersionInfo::Format
* Result: CString
*       Formatting CString for the version, of the form
*		0, 0, 0, 0
****************************************************************************/

CString VersionInfo::Format()
    {
     CString s;
     if(dot)
	s.Format(_T("%d.%d.%d.%d"), major, minor, patch, build);
     else
	s.Format(_T("%d, %d, %d, %d"), major, minor, patch, build);
     return s;
    } // VersionInfo::Format

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;


// Added by StageRace

BOOL writeincludefile(LPCTSTR includefile, VersionInfo & version)
    {
     TRY
	{ /* try */
	 CFile input(includefile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	 DWORD length = input.GetLength();
	 CString text;
	 if(length != 0)
	    { /* read existing */
	     LPTSTR p = text.GetBuffer(length + 1);
	     input.Read(p, length);
	     p[length] = _T('\0');
	     text.ReleaseBuffer();

		 if( atoi( text.Mid(32) )==version.GetIncludeValue() )
		 {
			return TRUE;
		 }
	    } /* read existing */
	 else
	    { /* empty */
	     // Version number is 1, 0, 0, 0
	    } /* empty */

	 char czBuffer[25];
	 _itoa( version.GetIncludeValue(), czBuffer, 10 );
	 text = "#define AUTOINCREMENTEDVERSIONNO "+(CString)czBuffer;

	 input.SeekToBegin();
	 input.Write((LPCTSTR)text, text.GetLength());
	 input.Close();
	 return TRUE;
	} /* try */
     CATCH(CFileException, e)
	   e->Delete();
           std::cout << _T("BuildInc: CFileException opening ") << includefile << _T("\n");
           return FALSE;
     END_CATCH

    } // incver

// End added


/****************************************************************************
*                                   incver
* Inputs:
*       LPCTSTR verfile: Version file
*	VersionInfo & version: Version object to update
* Result: BOOL
*       TRUE if successful
*	FALSE if error
* Effect: 
*       Increments the version number and pushes it onto the file
* Notes:
*	Version syntax is
*	[0-9]+, [0-9]+, [0-9]+, [0-9]+\n
*
*	For example, if the file starts out as
*	1, 0, 0, 0
*	The new value in the file is
*	1, 0, 0, 1\tTIMESTAMP
*	1, 0, 0, 0
*
*	If the file does not exist, or is empty, the version starts out
*	as 1, 0, 0, 0
****************************************************************************/

BOOL incver(LPCTSTR verfile, VersionInfo & version)
    {
     TRY
	{ /* try */
	 CFile input(verfile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	 DWORD length = input.GetLength();
	 CString text;
	 if(length != 0)
	    { /* read existing */
	     LPTSTR p = text.GetBuffer(length + 1);
	     input.Read(p, length);
	     p[length] = _T('\0');
	     text.ReleaseBuffer();
	     if(!version.parse(text))
		return FALSE;
	     version.build++;
	    } /* read existing */
	 else
	    { /* empty */
	     // Version number is 1, 0, 0, 0
	    } /* empty */
	 CString result;
	 result = version.Format();
	 version.TimeStamp();

	 result += _T("\t");
	 result += version.FormatTimeStamp();
	 result += _T("\r\n");

	 text = result + text;
	 input.SeekToBegin();
	 input.Write((LPCTSTR)text, text.GetLength());
	 input.Close();
	 return TRUE;
	} /* try */
     CATCH(CFileException, e)
	   e->Delete();
           std::cout << _T("BuildInc: CFileException opening ") << verfile << _T("\n");
           return FALSE;
     END_CATCH

    } // incver

/****************************************************************************
*                                  updateRC
* Inputs:
*       LPCTSTR rc: RC file name
*	VersionInfo & version: Version number info
* Result: BOOL
*       TRUE if successful
*	FALSE if error
* Effect: 
*       Updates the file version numbers in the .RC file
*	The current .rc file is saved as .rc.NNNN where NNNN is the
*	current build number less one. If a file .MMMM where .MMMM == .NNNN-10
*	exists, it is deleted
* Notes:
*	 FILEVERSION 2,0,0,0
*        VALUE "FileVersion", "2, 0, 0, 0\0"
****************************************************************************/

BOOL updateRC(LPCTSTR rc, VersionInfo & version)
    {
     CString ext;
     UINT line = 0;
     ext.Format(_T(".%04d"), version.build - 1);
     CString oldest;
     oldest.Format(_T(".%04d"), version.build - 10);
     // If version.oldest exists, delete it

     //----------------------------------------------------------------
     // Delete the oldest archive file
     //----------------------------------------------------------------
     CString file = rc;
     file += oldest;
     if(!::DeleteFile(file))
	{ /* failed */
	 DWORD err = ::GetLastError();
	 if(err != ERROR_FILE_NOT_FOUND)
	    { /* failed */
	     std::cout << _T("BuildInc: Oldest file delete '") << (LPCTSTR)file << _T("' failed, error code ") << err << _T("\n");
	     // do not abort, keep running
	    } /* failed */
	} /* failed */

     //----------------------------------------------------------------
     // Rename the input file to the saved version
     // something.rc => something.rc.NNNN
     //----------------------------------------------------------------
     TRY
	{ /* try rename */
	 file = rc;
	 file += ext;
	 CFile::Rename(rc, file);
	} /* try rename */
     CATCH(CFileException, e)
	{ /* rename failed */
	 std::cout << _T("BuildInc: Rename of '") << rc << _T("' to '") << (LPCTSTR)file << _T("' failed\n");
         e->Delete();
	 return FALSE;
	} /* rename failed */
     END_CATCH
	   
     //----------------------------------------------------------------
     // Now copy the renamed (.rc.NNNN) file to the new (.rc) file	   
     //----------------------------------------------------------------
     TRY
	{ /* try */
	 CStdioFile input(file, CFile::modeRead);
	 CStdioFile output(rc, CFile::modeCreate | CFile::modeWrite);
	 CString s;

	 while(input.ReadString(s))
	    { /* process line */
	     line++;
	     int offset = s.Find(_T("PRODUCTVERSION"));
	     if(offset >= 0)
		{ /* found PRODUCTVERSION */
		 CString indent(_T(' '), offset);
		 output.WriteString(indent);
		 output.WriteString(_T("PRODUCTVERSION "));
		 output.WriteString(version.Format());
		 output.WriteString(_T("\n"));
		 continue;
		} /* found PRODUCTVERSION */
	     offset = s.Find(_T("VALUE \"ProductVersion\""));
	     if(offset >= 0)
		{ /* found string */
		 CString indent(_T(' '), offset);
		 output.WriteString(indent);
		 output.WriteString(_T("VALUE \"ProductVersion\", \""));
		 output.WriteString(version.Format());
		 output.WriteString(_T("\\0\"\n"));
		 continue;
		} /* found string */
	     offset = s.Find(_T("FILEVERSION"));
	     if(offset >= 0)
		{ /* found FILEVERSION */
		 CString indent(_T(' '), offset);
		 output.WriteString(indent);
		 output.WriteString(_T("FILEVERSION "));
		 output.WriteString(version.Format());
		 output.WriteString(_T("\n"));
		 continue;
		} /* found FILEVERSION */
	     offset = s.Find(_T("VALUE \"FileVersion\""));
	     if(offset >= 0)
		{ /* found string */
		 CString indent(_T(' '), offset);
		 output.WriteString(indent);
		 output.WriteString(_T("VALUE \"FileVersion\", \""));
		 output.WriteString(version.Format());
		 output.WriteString(_T("\\0\"\n"));
		 continue;
		} /* found string */
	     output.WriteString(s);
	     output.WriteString(_T("\n"));
	    } /* process line */
	 input.Close();
	 output.Close();
	 return TRUE;
	} /* try */
     CATCH(CFileException, e)
	{ /* catch */
	 std::cout << _T("BuildInc: Error rewriting .rc file '") << rc << _T("'; rename old file '") << file << _T("' back\n");
	 if(!::DeleteFile(rc))
	    { /* failed to delete */
	     std::cout << _T("BuildInc: Error deleting erroneous .rc file\n");
	    } /* failed to delete */
	 else
	    { /* deleted */
	     if(::CopyFile(file, rc, FALSE))
		{ /* copy failed */
		 std::cout << _T("BuildInc: Error recopying archived .rc file\n");
		} /* copy failed */
	     else
		{ /* copy successful */
		 std::cout << _T("BuildInc: Sucessfully restored '") << rc << _T("'\n");
		} /* copy successful */
	    } /* deleted */
	 return FALSE;
	} /* catch */
     END_CATCH
    } // updateRC

/****************************************************************************
*                                   _tmain
* Inputs:
*       int argc:
*	TCHAR * argv[]:
*	TCHAR * envp[]:
* Result: int
*       0 if success
*	>0 if error
* Effect: 
*       Updates the version file
* Notes:
*	Usage is
*		buildinc version.ver project.rc
*
****************************************************************************/

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
	    std::cout << _T("BuildInc: Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
	 // Syntax
	 // The version file can have any name and contains only the string
	 // (my editor likes the name version.ver)
	 // The version.ver file must have a first line which is the version number
	 // The first line must have syntax
	 // [0-9]+, [0-9]+, [0-9]+, [0-9]+\n
	 // Upon completion, the contents of the file are replaced with contents
	 // of the form of the above, with the version number incremented, and
	 // the second and subsequent lines which are the build history
	 // [0-9]+, [0-9]+, [0-9]+, [0-9]+\tTIMESTAMP\n
	 // The first and second lines are duplicates except for the timestamp
	 if(argc != 3)
	    { /* error */
	     CString s;
	     s.Format(_T("%s: Requires two arguments"), argv[0]);
	     std::cout << (LPCTSTR)s;

		 return 1;
	    } /* error */

	 VersionInfo version;
	 
	 if(!incver(argv[1], version))
	    return 1;

	 if(!writeincludefile("versionno.h", version))
	    return 1;

	 if(!updateRC(argv[2], version))
	    return 1;

	 CString s;
	 s.Format(_T("****Build %s\n"), version.Format());
	 std::cout << _T("****Build ") << (LPCTSTR)version.Format() << _T("\n");
	}

	return nRetCode;
}

UINT VersionInfo::GetIncludeValue()
{
	return major*100*10 + minor*100 + patch;
}
