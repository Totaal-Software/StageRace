// TimeEdit.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeEdit

CTimeEdit::CTimeEdit()
{
	m_pTime = NULL;
}

CTimeEdit::~CTimeEdit()
{
	if( m_pTime ) delete m_pTime;
}


BEGIN_MESSAGE_MAP(CTimeEdit, CmEdit)
	//{{AFX_MSG_MAP(CTimeEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeEdit message handlers

void CTimeEdit::OnChange() 
{
	if( m_pTime )
	{
		delete m_pTime;
	}
	CString temp;
	GetWindowText(temp);
	temp.Remove( '(' );
	temp.Remove( ')' );
	temp += "000";
	if( temp.Find(TEXT("h "))==-1 ) temp = "h " + temp;
	m_pTime = new CStageTime(
			temp.Left(m_nSizeHours),
			temp.Mid(m_nSizeHours+2,2),
			temp.Mid(m_nSizeHours+6,2),
			temp.Mid(m_nSizeHours+10,3).Left(3)
		);
}

DWORD CTimeEdit::GetTime()
{
	OnChange();
	return m_pTime?m_pTime->GetUnits():0;
}

void CTimeEdit::Init(unsigned short nSizeT/*=3*/, unsigned short nSizeH/*=1*/, bool bBrackets/*=false*/)
{
	m_nSizeHours = nSizeH;

	// Set the prompt char to the zero no.
	SetPromptChar("0");

	// Compose the string
	CString c;
	// Number of hour digits
	for( int i=1; i<=nSizeH; i++ )
		c += "[0-9]";
	if( nSizeH )
		c += "h ";
	c += "[0-5][0-9]' [0-5][0-9]\"";
	// Add space before possible ms digits
	if( nSizeT )
	{
		c += " ";
		// Brackets for hiding
		if( bBrackets )
			c += "(";
	}
	// Number of ms digits
	for( int i=1; i<=nSizeT; i++ )
		c += "[0-9]";
	// Brackets for hiding
	if( nSizeT && bBrackets )
		c += ")";
	// Actually initialise
	CmEdit::Init( c );
}

void CTimeEdit::SetTime(DWORD t)
{
	CStageTime st(t);
	SetData(
			st.GetHours().Right( m_nSizeHours ) +
			st.GetMinutes() +
			st.GetSeconds() +
			st.GetThousandth()
		);
}