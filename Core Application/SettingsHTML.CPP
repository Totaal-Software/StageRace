// SettingsHTML.cpp: implementation of the CSettingsHTML class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingsHTML::CSettingsHTML()
{
	ValueAdd( IDS_SETT_HTML_TOC,
				CSettings::CSetting::GROUP, false, 0, 1 );
	ValueAdd( IDS_SETT_HTML_TOC_EVENTNAME,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_HTML_TOC );
	ValueAdd( IDS_SETT_HTML_TOC_INDEXHTML,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_HTML_TOC );

	ValueAdd( IDS_SETT_HTML_STYLE,
				CSettings::CSetting::GROUP, false, 0, 13 );
	ValueAdd( IDS_SETT_HTML_STYLE_INTERNAL,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_HTML_STYLE );
	ValueAdd( IDS_SETT_HTML_STYLE_EXTERNAL,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_HTML_STYLE );

	ValueAdd( IDS_SETT_HTML_FONT,
				CSettings::CSetting::GROUP, false, 0, 19 );
	ValueAdd( IDS_SETT_HTML_FONT_TIMES,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_HTML_FONT );
	ValueAdd( IDS_SETT_HTML_FONT_ARIAL,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_HTML_FONT );
	ValueAdd( IDS_SETT_HTML_UCIFIXEDWIDTH,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_HTML_FONT );

	ValueAdd( IDS_SETT_HTML_FONTSIZE,
				CSettings::CSetting::GROUP, false, 0, 20 );
	ValueAdd( IDS_SETT_HTML_FONTSIZE_ABS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_HTML_FONTSIZE );
	ValueAdd( IDS_SETT_HTML_FONTSIZE_PROC,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_HTML_FONTSIZE );

	ValueAdd( IDS_SETT_HTML_DUMMY,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_HTML_DUMMY_PRINT,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_HTML_DUMMY );

	ValueAdd( IDS_SETT_HTML_HYPERLINKS,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_HTML_HYPERLINKS_USE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_HTML_HYPERLINKS );

	ValueAdd( IDS_SETT_HTML_UNICODE,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_HTML_UNICODE_ENCODEUNICODE,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_HTML_UNICODE );
	ValueAdd( IDS_SETT_HTML_UNICODE_PRINTUNICODE,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_HTML_UNICODE );

	ValueAdd( IDS_SETT_HTML_CUSTOMONEACHPAGE,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_HTML_CUSTOMONEACHPAGE_TOP,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_HTML_CUSTOMONEACHPAGE );
	ValueAdd( IDS_SETT_HTML_CUSTOMONEACHPAGE_BOTTOM,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_HTML_CUSTOMONEACHPAGE );

	m_bgColor		= "White";
	m_bodyColor		= "Black";
	m_descriptColor	= "Gray";
	m_titleColor	= "Blue";
	m_fontsize		= 100;
	m_columnspacing	= 0;
}

CSettingsHTML::CSettingsHTML(CSettingsHTML *pSettings)
{
	CSettingsHTML();
	*this = *pSettings;
}

CPageSettings* CSettingsHTML::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsHTML();
	// Make a copy of this settings
	CSettingsHTML*	pCopy = new CSettingsHTML();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsHTML::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsHTML* s1	= (CSettingsHTML*)&s;
	m_eventLogo			= s1->m_eventLogo;
	m_styleSheet		= s1->m_styleSheet;
	m_titleColor		= s1->m_titleColor;
	m_descriptColor		= s1->m_descriptColor;
	m_bodyColor			= s1->m_bodyColor;
	m_bgColor			= s1->m_bgColor;
	m_customHTMLTop		= s1->m_customHTMLTop;
	m_customHTMLBottom	= s1->m_customHTMLBottom;
	m_fontsize			= s1->m_fontsize;
	m_columnspacing		= s1->m_columnspacing;

	return *this;
}

void CSettingsHTML::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsStoring())
	{
			ar <<  m_eventLogo << m_styleSheet << m_titleColor <<
				m_descriptColor << m_bodyColor << m_bgColor <<
				m_customHTMLTop << m_customHTMLBottom << m_fontsize <<
				m_columnspacing;
	}
	else
	{
		if( *(int*)(ar.m_pDocument) >= 3000 )
		{
			ar >>  m_eventLogo >> m_styleSheet >> m_titleColor >>
				m_descriptColor >> m_bodyColor >> m_bgColor >>
				m_customHTMLTop >> m_customHTMLBottom >> m_fontsize >>
				m_columnspacing;
		}
		else
		{
			ar >>  m_eventLogo >> m_styleSheet >> m_titleColor >>
				m_descriptColor >> m_bodyColor >> m_bgColor;

			ValueSet( IDS_SETT_HTML_FONTSIZE_PROC, false );
			ValueSet( IDS_SETT_HTML_FONTSIZE_ABS , true );
		}
	}
}
