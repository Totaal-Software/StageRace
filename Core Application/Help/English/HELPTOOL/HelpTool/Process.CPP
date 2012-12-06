// Process.cpp: implementation of the Process class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HelpTool.h"
#include "BottomLinks.h"
#include "HeaderConversion.h"
#include "Process.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString Process::m_index;
CString Process::m_bottomlinkshead;
CString Process::m_bottomlinksfoot;
CString Process::m_head;
CString Process::m_foot;
CString Process::m_beforeEachLink;
CString Process::m_afterEachLink;

void Process::Go(CString source, CString targethtml, CString targetdoc, CString include)
{
	m_index = "";
	// Set up the base path that we will be working from
	char czPath[MAX_PATH];
	GetModuleFileName( NULL, czPath, MAX_PATH );
	czPath[((CString)czPath).ReverseFind( '\\' )+1] = '\0';
	source		= ((CString)czPath)+source;
	targethtml	= ((CString)czPath)+targethtml;
	targetdoc	= ((CString)czPath)+targetdoc;
	include		= ((CString)czPath)+include;

	// Fill some variables
	{
		CFile file;
		if( file.Open( include+"\\beforeEachLink.txt", CFile::modeRead ) )
		{
			LPTSTR p = m_beforeEachLink.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_beforeEachLink.ReleaseBuffer();
			file.Close();
		}
	}
	{
		CFile file;
		if( file.Open( include+"\\afterEachLink.txt", CFile::modeRead ) )
		{
			LPTSTR p = m_afterEachLink.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_afterEachLink.ReleaseBuffer();
			file.Close();
		}
	}
	{
		CFile file;
		if( file.Open( include+"\\bottomlinkshead.html", CFile::modeRead ) )
		{
			LPTSTR p = m_bottomlinkshead.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_bottomlinkshead.ReleaseBuffer();
			file.Close();
		}
	}
	{
		CFile file;
		if( file.Open( include+"\\bottomlinksfoot.html", CFile::modeRead ) )
		{
			LPTSTR p = m_bottomlinksfoot.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_bottomlinksfoot.ReleaseBuffer();
			file.Close();
		}
	}
	{
		CFile file;
		if( file.Open( include+"\\head.html", CFile::modeRead ) )
		{
			LPTSTR p = m_head.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_head.ReleaseBuffer();
			file.Close();
		}
	}
	{
		CFile file;
		if( file.Open( include+"\\foot.html", CFile::modeRead ) )
		{
			LPTSTR p = m_foot.GetBuffer( file.GetLength() + 1 );
			file.Read( p, file.GetLength() );
			p[file.GetLength()] = _T('\0');
			m_foot.ReleaseBuffer();
			file.Close();
		}
	}


	// Select the files to be transferred
	CFileFind finder;
	BOOL bWorking = finder.FindFile( source+"\\*.htm*" );

	int nCounter=0;

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		finder.GetFileName();

		if( finder.GetFileName().Left(1)!="_" )
		{

			// Create file handler
			CFile importFile; 
			CFileException fileException;
			CString sourcecontents;
			// Read source file
			try
			{
				if( importFile.Open( source+"\\"+finder.GetFileName(), CFile::modeRead|CFile::shareDenyNone, &fileException ) )
				{
					LPTSTR p = sourcecontents.GetBuffer( importFile.GetLength() + 1 );
					importFile.Read( p, importFile.GetLength() );
					p[importFile.GetLength()] = _T('\0');
					sourcecontents.ReleaseBuffer();
					importFile.Close();
				}
				else
					MessageBox( NULL,
						"Cannot open: "+source+finder.GetFileName(),
						"Cannot open",
						MB_OK|MB_ICONEXCLAMATION );
			}
			catch(...)
			{
				MessageBox( NULL,
					"Cannot process: "+source+finder.GetFileName(),
					"Cannot process",
					MB_OK|MB_ICONEXCLAMATION );
			}

			// Remove the script tag in the beginning
			sourcecontents = sourcecontents.Mid( sourcecontents.Find( ">" )+1 );

			// Write report
			Report( "\tProcessing ["+finder.GetFileName()+"]" );

			// Setup target file name
			CString cFileName = finder.GetFileName();
			cFileName = cFileName.Mid( cFileName.ReverseFind( '\\' ) );

			// Write target html file
			CString cHtml;
			cHtml = HtmlProcessing( sourcecontents, finder.GetFileTitle() );

			CFile exportFileHtml( targethtml+"\\"+cFileName, CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive );

			exportFileHtml.SeekToBegin();
			exportFileHtml.Write( cHtml, cHtml.GetLength());
			exportFileHtml.Close();

			// Write target document file
			CString cDoc;
			cDoc = DocProcessing( sourcecontents, finder.GetFileTitle() );

			CFile exportFileDoc( targetdoc+"\\"+cFileName, CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive );

			exportFileDoc.SeekToBegin();
			exportFileDoc.Write( cDoc, cDoc.GetLength());
			exportFileDoc.Close();

			nCounter++;
		}
	}
	if( nCounter && m_index.GetLength() )
	{
		CFile exportFileDoc( "index.hhk_", CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive );

		exportFileDoc.SeekToBegin();
		exportFileDoc.Write( m_index, m_index.GetLength());
		exportFileDoc.Close();
	}
	char czBuffer[10];
	_itoa( nCounter, czBuffer, 10 );
	if( nCounter )
		Report( "Done processing "+(CString)czBuffer+" files" );
	else
		Report( "No files processed" );
}

CString Process::DocProcessing(CString str, CString TopicFile)
{
	CHeaderConversion hc;
	int i = hc.GetHeaderLevel( TopicFile );
	if( i )
	{
		Report( "\t\tLeveling changed for "+TopicFile );
		for( int level=6-i; level; level-- )
		{
			CString fnd1, fnd2;
			CString rep1, rep2;
			char czBuffer[3];
			_itoa( level, czBuffer, 10 );
			fnd1 = "<H"+(CString)czBuffer;
			fnd2 = "</H"+(CString)czBuffer;
			_itoa( level+i, czBuffer, 10 );
			rep1 = "<H"+(CString)czBuffer;
			rep2 = "</H"+(CString)czBuffer;

			str.Replace( fnd1, rep1 );
			str.Replace( fnd2, rep2 );

			fnd1.MakeLower();
			fnd2.MakeLower();
			rep1.MakeLower();
			rep2.MakeLower();

			str.Replace( fnd1, rep1 );
			str.Replace( fnd2, rep2 );
		}
	}
	// Remove hyperlinks
	int n;
	while( (n=str.Find("<A"))>0 )
	{
		str = str.Mid(0, n) + str.Mid(n+str.Mid(n).Find(">")+1);
	}
	while( (n=str.Find("</A"))>0 )
	{
		str = str.Mid(0, n) + str.Mid(n+str.Mid(n).Find(">")+1);
	}
	while( (n=str.Find("<a"))>0 )
	{
		str = str.Mid(0, n) + str.Mid(n+str.Mid(n).Find(">")+1);
	}
	while( (n=str.Find("</a"))>0 )
	{
		str = str.Mid(0, n) + str.Mid(n+str.Mid(n).Find(">")+1);
	}
	// Add image subscripts/captions
	n = 0;
	while( (n=str.Find("<IMG",n))>0 )
	{
		CString subscr = str.Mid(n,str.Mid(n).Find(">")+1);
		if( subscr.Find("ALT=")>0 )
		{
			subscr = subscr.Mid( subscr.Find("ALT=")+4 );
			if( subscr[0]=='\"' ) subscr = subscr.Mid(1);
			subscr = subscr.Mid( 0, subscr.Find('\"') );
			subscr = "<P CLASS=\"caption\">"+subscr+"</P>";

			str = str.Mid(0, n+str.Mid(n).Find(">")+1) +subscr+ str.Mid(n+str.Mid(n).Find(">")+1);
		}
		n++;
	}
	return "<HTML><BODY>"+str+"</HTML></BODY>";
}

CString Process::HtmlProcessing(CString str, CString TopicFile)
{
	CBottomLinks bl;
	CString links = bl.GetBottomLinks( TopicFile, m_beforeEachLink, m_afterEachLink );

	CString firstheader;
	int opener = str.Find( ">", str.Find( "<H" ) )+1;
	int closer = str.Find( "<", opener );
	firstheader = str.Mid( opener, closer-opener );
	if( firstheader.GetLength() )
	{
		firstheader.Remove( '\n' );
		firstheader.Remove( '\r' );
		firstheader.Replace( "  ", " " );
		firstheader.TrimLeft();
		firstheader.TrimRight();
		CString continued = m_head.Mid( m_head.Find( "<TITLE>" )+7, 50 );
		continued.TrimLeft();
		if( continued.Left(7)!="</TITLE" )
			firstheader+=" - ";
	}

	CString firstheaderLC = firstheader;
	firstheaderLC.MakeLower();

	m_index += 
	"       <LI> <OBJECT type=\"text/sitemap\">\r\n" +
	(CString)"       <param name=\"Name\" value=\""+firstheaderLC+(CString)"\">\r\n" +
	(CString)"       <param name=\"Name\" value=\""+(CString)firstheader+(CString)"\">\r\n" +
	(CString)"       <param name=\"Local\" value=\""+TopicFile+(CString)".html\">\r\n		</OBJECT>\r\n";


	CString head;
	head = m_head.Mid( 0, m_head.Find( "<TITLE>" )+7 );
	head += firstheader;
	head += m_head.Mid( m_head.Find( "<TITLE>" )+7 );

	if( links.GetLength() )
	{
		str =
			head +
			str +
			m_bottomlinkshead +
			links +
			m_bottomlinksfoot +
			m_foot;
	}
	else
	{
		str =
			head +
			str +
			m_foot;
	}
	return str;
}

