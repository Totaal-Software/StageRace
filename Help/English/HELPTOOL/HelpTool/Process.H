// Process.h: interface for the Process class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESS_H__E7ED0E6F_8994_4D32_9F46_6A5F6E6DEE87__INCLUDED_)
#define AFX_PROCESS_H__E7ED0E6F_8994_4D32_9F46_6A5F6E6DEE87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Process  
{
public:
	static void Go( CString source, CString targethtml, CString targetdoc, CString include );

protected:
	static CString m_index;
	static CString m_bottomlinkshead;
	static CString m_bottomlinksfoot;
	static CString m_head;
	static CString m_foot;
	static CString m_beforeEachLink;
	static CString m_afterEachLink;
	static CString HtmlProcessing(CString str, CString TopicFile);
	static CString DocProcessing(CString str, CString TopicFile);
};

#endif // !defined(AFX_PROCESS_H__E7ED0E6F_8994_4D32_9F46_6A5F6E6DEE87__INCLUDED_)
