// Time.h: interface for the CStageTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIME_H__99177722_6884_11D3_ADAA_0040954019F4__INCLUDED_)
#define AFX_TIME_H__99177722_6884_11D3_ADAA_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CStageTime : public CObject
{
public:
	CString GetFormattedSemicolons();
	CString GetFormattedWide();
	CString GetFormattedAlllefttrimmed();
	CString GetFormattedLefttrimmed();
	CString GetFormatted();
	CStageTime( DWORD units );
	CStageTime( CString hours, CString minutes, CString seconds, CString thousandth );
	static DWORD GetUnits( CString hours, CString minutes, CString seconds, CString thousandth );
	DWORD GetUnits() const { return m_units; };
	CString GetThousandth() const { return m_thousandth; };
	CString GetSeconds() const { return m_seconds; };
	CString GetMinutes() const { return m_minutes; };
	CString GetHours() const { return m_hours; };
private:
	DWORD m_units;
	CString m_thousandth;
	CString m_seconds;
	CString m_minutes;
	CString m_hours;
};

#endif // !defined(AFX_TIME_H__99177722_6884_11D3_ADAA_0040954019F4__INCLUDED_)
