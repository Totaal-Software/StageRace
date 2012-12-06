// StaticPresentationView.h: interface for the CStaticPresentationView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICPRESENTATIONVIEW_H__EA3445E4_410D_4904_8F00_9808C2908012__INCLUDED_)
#define AFX_STATICPRESENTATIONVIEW_H__EA3445E4_410D_4904_8F00_9808C2908012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaticPresentationView : public CPresentationView  
{
	DECLARE_DYNCREATE( CStaticPresentationView )
public:

private:
	STDMETHOD(ShowContextMenu)(unsigned long,struct tagPOINT *,struct IUnknown *,struct IDispatch *);
};

#endif // !defined(AFX_STATICPRESENTATIONVIEW_H__EA3445E4_410D_4904_8F00_9808C2908012__INCLUDED_)
