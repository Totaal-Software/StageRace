// An Internet Explorer Style Options Panel
// Copyright (c) 2000 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#include "stdafx.h"
#include "OptionsPanel.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************/
/* Constructor */
/***************/

COptionsPanel::COptionsPanel()
{
// not initialized yet

	m_bInited=FALSE;
}


/**************/
/* Destructor */
/**************/

COptionsPanel::~COptionsPanel()
{
}


/***************/
/* Message Map */
/***************/

BEGIN_MESSAGE_MAP(COptionsPanel, CButton)
	//{{AFX_MSG_MAP(COptionsPanel)
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*****************/
/* WM_ERASEBKGND */
/*****************/

BOOL COptionsPanel::OnEraseBkgnd(CDC *pDC)
{	
	CRect rect;

// get the client area

	GetClientRect(rect);

// draw the border

	pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHIGHLIGHT));
	rect.DeflateRect(1,1);
	pDC->Draw3dRect(rect,GetSysColor(COLOR_3DDKSHADOW),GetSysColor(COLOR_BTNFACE));

// fill the background

	rect.DeflateRect(1,1);
	if(IsWindow(m_wndVertScroll) && m_wndVertScroll.IsWindowVisible())
		rect.right-=GetSystemMetrics(SM_CXVSCROLL);

	pDC->FillSolidRect(rect,GetSysColor(COLOR_WINDOW));

	return TRUE;
}


/******************/
/* Draw the panel */
/******************/

void COptionsPanel::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC *pDC=CDC::FromHandle(lpDIS->hDC);
	std::vector<CItem>::const_iterator it;
	CRect rcClient;

// check if initialized yet

	if(!m_bInited)
	{
		Initialize(pDC);
		m_bInited=TRUE;
	}

// set up the DC

	pDC->SetBkMode(TRANSPARENT);

// get an adjusted client rect that excludes the borders

	GetAdjustedClientRect(rcClient);
	pDC->IntersectClipRect(rcClient);

// check if drawing everything

	if(lpDIS->itemAction & ODA_DRAWENTIRE)
	{
	// draw groups

		for(it=m_Items.begin();it!=m_Items.end() && it->m_rcItem.bottom<rcClient.bottom;it++)
			DrawSingleItem(pDC,*it,rcClient);
	}

// check if drawing the focus

	if(lpDIS->itemAction & ODA_FOCUS)
		if(m_pFocus)
			DrawSingleItem(pDC,*m_pFocus,rcClient);
}


/**********************/
/* Draw a single item */
/**********************/

void COptionsPanel::DrawSingleItem(CDC *pDC,const CItem& item,const CRect& rcClient)
{
	if(item.m_rcItem.bottom>=rcClient.bottom || item.m_rcItem.top<rcClient.top)
		return;

	switch(item.m_Type)
	{
		case CItem::typeGroup:
			DrawGroup(pDC,item,rcClient);
			break;

		case CItem::typeCheck:
			DrawCheck(pDC,item,rcClient);
			break;

		case CItem::typeRadio:
			DrawRadio(pDC,item,rcClient);
			break;
	}
}


/****************/
/* Draw a group */
/****************/

void COptionsPanel::DrawGroup(CDC *pDC,const CItem& group,const CRect& rcClient)
{
	int		offset;
	CRect rect;

// draw the background rectangle

	DrawBackRect(pDC,group,rcClient);

// draw the image

	m_ImageList.Draw(pDC,group.m_nImage,CPoint(group.m_rcItem.left,group.m_rcItem.top),ILD_TRANSPARENT);

// select the correct font

	if((group.m_dwFlags & groupBold)!=0)
	{
		offset=m_BoldFontOffset;
		pDC->SelectObject(&m_BoldFont);
	}
	else
	{
		offset=m_NormalFontOffset;
		pDC->SelectObject(&m_NormalFont);
	}

// draw the text

	rect=group.m_rcItem;
	rect.left+=20;
	rect.top+=offset;
	rect.IntersectRect(rect,rcClient);

	pDC->SetTextColor(GetSysColor(m_pFocus==&group && GetFocus()==this ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
	pDC->DrawText(group.m_strText,rect,DT_TOP | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
}


/****************/
/* Draw a check */
/****************/

void COptionsPanel::DrawCheck(CDC *pDC,const CItem& check,const CRect& rcClient)
{
	DrawCheckOrRadio(pDC,check,0,1,rcClient);
}


/****************/
/* Draw a radio */
/****************/

void COptionsPanel::DrawRadio(CDC *pDC,const CItem& radio,const CRect& rcClient)
{
	DrawCheckOrRadio(pDC,radio,2,3,rcClient);
}


/***************************/
/* Draw a check or a radio */
/***************************/

void COptionsPanel::DrawCheckOrRadio(CDC *pDC,const CItem& button,const int nChecked,const int nClear,const CRect& rcClient)
{
	int		nImage,offset;
	CRect rect;

// draw the background rectangle

	DrawBackRect(pDC,button,rcClient);

// draw the image

	nImage=(button.m_dwFlags & itemChecked) ? nChecked : nClear;
	m_InternalImageList.Draw(pDC,nImage,CPoint(button.m_rcItem.left,button.m_rcItem.top),ILD_TRANSPARENT);

// draw the text

	if((button.m_dwFlags & itemBold)!=0)
	{
		offset=m_BoldFontOffset;
		pDC->SelectObject(&m_BoldFont);
	}
	else
	{
		offset=m_NormalFontOffset;
		pDC->SelectObject(&m_NormalFont);
	}

	rect=button.m_rcItem;
	rect.left+=20;
	rect.top+=offset;
	rect.IntersectRect(rect,rcClient);

	pDC->SetTextColor(GetSysColor(m_pFocus==&button && GetFocus()==this ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
	pDC->DrawText(button.m_strText,rect,DT_TOP | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
}


/************************/
/* Draw background rect */
/************************/

void COptionsPanel::DrawBackRect(CDC *pDC,const CItem& item,const CRect& rcClient)
{
	COLORREF crBack;
	CRect		 rect;
	BOOL		 bGotFocus;

// erase the icon area

	rect=item.m_rcItem;
	rect.right=rect.left+16;
	pDC->FillSolidRect(rect,GetSysColor(COLOR_WINDOW));

// get the background color

	bGotFocus=GetFocus()==this;
	crBack=GetSysColor(&item==m_pFocus && bGotFocus ? COLOR_HIGHLIGHT : COLOR_WINDOW);

// draw it

	rect=item.m_rcItem;
	rect.left+=18;
	rect.right+=2;

// draw it

	pDC->FillSolidRect(rect,crBack);
	
// draw the focus

	if(&item==m_pFocus && bGotFocus)
	{
		pDC->SelectStockObject(NULL_BRUSH);

		pDC->SelectObject(&m_BackPen);
		pDC->Rectangle(rect);

		pDC->SelectObject(&m_FocusPen);
		pDC->Rectangle(rect);
	}
}


/**************************/
/* Initialize the control */
/**************************/

void COptionsPanel::Initialize(CDC *pDC)
{
	CFont   *pFont;
	LOGFONT  lf;
	LOGBRUSH lb;
	CRect		 rcClient,rcScroll;

// reset top and focus index

	m_Top=0;
	m_pFocus=m_Items.size() ? &m_Items[0] : NULL;

// load the internal image list

	m_InternalImageList.Create(IDB_OPTIONS_PANEL_IMAGES,13,1,RGB(255,0,255));

// create the pens

	lb.lbColor=GetSysColor(COLOR_GRAYTEXT);
	lb.lbStyle=BS_SOLID;
	
	m_FocusPen.CreatePen(PS_COSMETIC | PS_ALTERNATE,1,&lb,0,NULL);
	m_BackPen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_WINDOW));

// get the default font

	pFont=CFont::FromHandle(reinterpret_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT)));
	pFont->GetLogFont(&lf);

// create normal and bold fonts

	m_NormalFont.CreateFontIndirect(&lf);

	lf.lfWeight=FW_BOLD;
	m_BoldFont.CreateFontIndirect(&lf);

// get the font vertical offsets into the item rectangle

	GetFontOffset(pDC,m_NormalFont,m_NormalFontOffset);
	GetFontOffset(pDC,m_BoldFont,m_BoldFontOffset);

// calculate the rectangles occupied by the items

	CalculateItemRects(pDC);

// create a vertical scrollbar

	GetClientRect(rcClient);

	rcScroll=rcClient;
	rcScroll.right-=2;
	rcScroll.left=rcScroll.right-GetSystemMetrics(SM_CXVSCROLL);
	rcScroll.top+=2;
	rcScroll.bottom-=2;

	m_wndVertScroll.Create(WS_CHILD | SBS_VERT,rcScroll,this,idVertScroll);

// set up the scrollbars

	SetupScrollBars();
}


/***********************/
/* Get the font offset */
/***********************/

void COptionsPanel::GetFontOffset(CDC *pDC,CFont& font,int& offset) const
{
	TEXTMETRIC tm;
	CFont			*pOldFont;

	pOldFont=pDC->SelectObject(&font);
	pDC->GetTextMetrics(&tm);

// font height must not be >16

	ASSERT(tm.tmHeight<=16);
	offset=(16-tm.tmHeight)/2;

	pDC->SelectObject(pOldFont);
}


/****************************/
/* Calculate the item rects */
/****************************/

void COptionsPanel::CalculateItemRects(CDC *pDC)
{
	std::vector<CItem>::iterator it;
	int nDC,top;

// initialize the top

	top=2;

// save the DC attributes

	nDC=pDC->SaveDC();

// calculate the rects

	for(it=m_Items.begin();it!=m_Items.end();it++)
		CalculateOneItemRect(pDC,*it,top);

// restore the DC

	pDC->RestoreDC(nDC);
}


/********************************/
/* Calculate a single item rect */
/********************************/

void COptionsPanel::CalculateOneItemRect(CDC *pDC,CItem& item,int& top)
{
	CSize size;

// select the correct font

	if((item.m_Type==CItem::typeGroup && (item.m_dwFlags & groupBold)!=0) || (item.m_Type!=CItem::typeGroup && (item.m_dwFlags & itemBold)!=0))
		pDC->SelectObject(&m_BoldFont);
	else
		pDC->SelectObject(&m_NormalFont);
	
// measure the item

	size=pDC->GetTextExtent(item.m_strText);

// set up the position
	
	item.m_rcItem.left=2+(20*item.m_nLevel);
	item.m_rcItem.top=top-(m_Top*16);
	item.m_rcItem.right=item.m_rcItem.left+size.cx+20;
	item.m_rcItem.bottom=item.m_rcItem.top+16;

// update the position

	top+=16;
}


/************************/
/* Setup the scrollbars */
/************************/

void COptionsPanel::SetupScrollBars(void)
{
	SCROLLINFO si;
	CRect			 rcClient;

// get the client rect

	GetAdjustedClientRect(rcClient);

// set the vertical scroll range

	si.cbSize=sizeof(si);
	si.fMask=SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nPos=m_Top;
	si.nPage=rcClient.Height()/16;
	si.nMin=0;
	si.nMax=m_Items.size()-1;

	m_wndVertScroll.SetScrollInfo(&si);

// set the visibility of the scroll bar

	m_wndVertScroll.ShowWindow(m_Items.size()>si.nPage ? SW_SHOW : SW_HIDE);
}


/*********************/
/* Set an image list */
/*********************/

void COptionsPanel::SetImageList(CImageList& list)
{
// create our list from the one supplied

	VERIFY(m_ImageList.Create(&list));
}


/*******************/
/* Add a new group */
/*******************/

void COptionsPanel::AddGroup(const CString& strText,const DWORD dwFlags,const int nLevel,const int nImage)
{
	CItem item;

	item.m_Type=CItem::typeGroup;
	item.m_dwFlags=dwFlags;
	item.m_nID=0;
	item.m_nLevel=nLevel;
	item.m_nImage=nImage;
	item.m_strText=strText;

	m_Items.push_back(item);
}

void COptionsPanel::AddGroup(const UINT resID,const DWORD dwFlags,const int nLevel,const int nImage)
{
	CString strText;

	strText.LoadString(resID);
	AddGroup(strText,dwFlags,nLevel,nImage);
}


/*******************/
/* Add a check box */
/*******************/

void COptionsPanel::AddCheck(const CString& strText,const DWORD dwFlags,const int nLevel,const int nID)
{
	AddCheckOrRadio(CItem::typeCheck,strText,dwFlags,nLevel,nID);
}

void COptionsPanel::AddCheck(const UINT resID,const DWORD dwFlags,const int nLevel)
{
	CString strText;

	strText.LoadString(resID);
	AddCheckOrRadio(CItem::typeCheck,strText,dwFlags,nLevel,resID);
}


/**********************/
/* Add a radio button */
/**********************/

void COptionsPanel::AddRadio(const CString& strText,const DWORD dwFlags,const int nLevel,const int nID)
{
	AddCheckOrRadio(CItem::typeRadio,strText,dwFlags,nLevel,nID);
}

void COptionsPanel::AddRadio(const UINT resID,const DWORD dwFlags,const int nLevel)
{
	CString strText;

	strText.LoadString(resID);
	AddCheckOrRadio(CItem::typeRadio,strText,dwFlags,nLevel,resID);
}


/****************/
/* Add a button */
/****************/

void COptionsPanel::AddCheckOrRadio(const CItem::eType type,const CString& strText,const DWORD dwFlags,const int nLevel,const int nID)
{
	CItem item;

	item.m_Type=type;
	item.m_dwFlags=dwFlags;
	item.m_nID=nID;
	item.m_nLevel=nLevel;
	item.m_strText=strText;

	m_Items.push_back(item);
}


/***********************/
/* Get the check state */
/***********************/

BOOL COptionsPanel::GetCheckState(const int nID) const
{
	std::vector<CItem>::const_iterator it;

	for(it=m_Items.begin();it!=m_Items.end();it++)
		if(it->m_nID==nID)
			return (it->m_dwFlags & itemChecked)!=0;

	return FALSE;
}


/***********************/
/* Set the check state */
/***********************/

BOOL COptionsPanel::SetCheckState(const int nID,const BOOL bChecked)
{
	std::vector<CItem>::iterator it;

	for(it=m_Items.begin();it!=m_Items.end();it++)
	{
		if(it->m_nID==nID)
		{
			if(bChecked)
				it->m_dwFlags|=itemChecked;
			else
				it->m_dwFlags&=~itemChecked;

			return TRUE;
		}
	}

	return FALSE;
}


/*****************************/
/* CItem default constructor */
/*****************************/

COptionsPanel::CItem::CItem()
{
}


/**************************/
/* CItem copy constructor */
/**************************/

COptionsPanel::CItem::CItem(const CItem& src)
{
	Assign(src);
}


/********************/
/* CItem = operator */
/********************/

COptionsPanel::CItem& COptionsPanel::CItem::operator=(const CItem& src)
{
	Assign(src);
	return *this;
}


/****************/
/* CItem assign */
/****************/

void COptionsPanel::CItem::Assign(const CItem& src)
{
	m_Type=src.m_Type;
	m_dwFlags=src.m_dwFlags;
	m_nID=src.m_nID;
	m_nLevel=src.m_nLevel;
	m_rcItem=src.m_rcItem;
	m_strText=src.m_strText;
	m_nImage=src.m_nImage;
}


/**************/
/* WM_VSCROLL */
/**************/

void COptionsPanel::OnVScroll(UINT nSBCode,UINT nPos,CScrollBar *pScrollBar)
{
	int		newtop,perpage;
	CRect rcClient;

// get the # of items per page

	GetAdjustedClientRect(rcClient);
	perpage=rcClient.Height()/16;

// get the scroll position

	switch(nSBCode)
	{
		case SB_BOTTOM:
			newtop=m_Items.size()-1;
			break;

		case SB_TOP:
			newtop=0;
			break;

		case SB_LINEDOWN:
			newtop=m_Top+1;
			break;

		case SB_LINEUP:
			newtop=m_Top-1;
			break;
	
		case SB_PAGEDOWN:
			newtop=m_Top+perpage;
			break;

		case SB_PAGEUP:
			newtop=m_Top-perpage;
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			newtop=nPos;
			break;

		default:
			return;
	}

// constrain the new position

	newtop=max(0,min((int)m_Items.size()-perpage,newtop));

// set the new position

	if(newtop!=m_Top)
	{
	// displace the items

		DisplaceItemRects((m_Top-newtop)*16);

	// scroll the window

		rcClient.bottom=rcClient.top+(perpage*16);
		ScrollWindow(0,(m_Top-newtop)*16,rcClient,rcClient);

	// set the scroll bars

		m_Top=newtop;
		SetupScrollBars();
	}
}


/***********************/
/* Displace item rects */
/***********************/

void COptionsPanel::DisplaceItemRects(const int disp)
{
	std::vector<CItem>::iterator it;

	for(it=m_Items.begin();it!=m_Items.end();it++)
	{
		it->m_rcItem.top+=disp;
		it->m_rcItem.bottom+=disp;
	}
}


/**************/
/* BN_CLICKED */
/**************/

void COptionsPanel::OnClicked() 
{
	CItem	*pItem;

// get the item at the cursor position

	if((pItem=GetItemAtCursor())==NULL)
		return;

// select the item

	SelectItem(pItem);
}


/******************/
/* Select an item */
/******************/

void COptionsPanel::SelectItem(CItem *pItem)
{
	CItem		 *pLastFocus;
	CClientDC dc(this);
	CRect			rcClient;

// get an adjusted client rect

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

// toggle the state if required

	ToggleState(&dc,pItem,rcClient);

	if(m_pFocus!=pItem)
	{
	// deselect the focussed item

		pLastFocus=m_pFocus;
		m_pFocus=pItem;

		if(pLastFocus)
			DrawSingleItem(&dc,*pLastFocus,rcClient);

	// select the new item

		DrawSingleItem(&dc,*m_pFocus,rcClient);
	}
}


/*************************/
/* Toggle selected state */
/*************************/

void COptionsPanel::ToggleState(CDC *pDC,CItem *pItem,const CRect& rcClient)
{
	std::vector<CItem>::iterator it;

	if(pItem->m_Type==CItem::typeCheck)
	{
	// toggle-select the item

		pItem->m_dwFlags^=itemChecked;
		DrawSingleItem(pDC,*pItem,rcClient);
	
	// notify the parent

		NotifyParentSelChange(*pItem);
	}
	else if(pItem->m_Type==CItem::typeRadio)
	{
		if((pItem->m_dwFlags & itemChecked)==0)
		{
		// get an iterator for this item

			it=GetIterator(pItem);
			
		// step back to the first radio in the group

			for(;it!=m_Items.begin() && it->m_Type==CItem::typeRadio;it--);
			if(/*it!=m_Items.begin() &&*/ it->m_Type!=CItem::typeRadio)
				it++;

		// deselect all adjacent radios

			for(;it!=m_Items.end() && it->m_Type==CItem::typeRadio;it++)
			{
				if(&(*it)!=pItem && (it->m_dwFlags & itemChecked)!=0)
				{
					it->m_dwFlags&=~itemChecked;
					DrawSingleItem(pDC,*it,rcClient);
					NotifyParentSelChange(*it);
				}
			}

		// select the chosen item
			
			pItem->m_dwFlags|=itemChecked;
			DrawSingleItem(pDC,*pItem,rcClient);
			NotifyParentSelChange(*pItem);
		}
	}
}


/*******************************/
/* Get an iterator for an item */
/*******************************/

std::vector<COptionsPanel::CItem>::iterator COptionsPanel::GetIterator(CItem *pItem)
{
	std::vector<CItem>::iterator it;

	for(it=m_Items.begin();it!=m_Items.end();it++)
		if(&(*it)==pItem)
			break;

	return it;
}


/******************************/
/* Get the item at the cursor */
/******************************/

COptionsPanel::CItem *COptionsPanel::GetItemAtCursor(void)
{
	CPoint p;
	CRect rcClient;
	int perpage;
	std::vector<CItem>::iterator it;

// get the cursor position

	GetCursorPos(&p);
	ScreenToClient(&p);

// get the item under the click position

	for(it=m_Items.begin();it!=m_Items.end();it++)
		if(it->m_rcItem.PtInRect(p))
			break;

// check for end

	if(it==m_Items.end())
		return NULL;

// check for not visible

	GetAdjustedClientRect(rcClient);
	perpage=rcClient.Height()/16;
	rcClient.bottom=rcClient.top+(perpage*16);

	if(it->m_rcItem.top>=rcClient.bottom || it->m_rcItem.top<rcClient.top)
		return NULL;

	return &(*it);
}


/*******************************/
/* Get an adjusted client rect */
/*******************************/

void COptionsPanel::GetAdjustedClientRect(CRect& rcClient) const
{
	GetClientRect(rcClient);
	rcClient.DeflateRect(2,2);

// exclude the scrollbar, if present

	if(m_wndVertScroll.IsWindowVisible())
		rcClient.right-=GetSystemMetrics(SM_CXVSCROLL);
}


/*****************/
/* WM_MOUSEWHEEL */
/*****************/

BOOL COptionsPanel::OnMouseWheel(UINT nFlags,short zDelta,CPoint pt) 
{	
	OnVScroll(SB_THUMBPOSITION,m_Top-zDelta/WHEEL_DELTA,NULL);
	return TRUE;
}


/*****************/
/* WM_GETDLGCODE */
/*****************/

UINT COptionsPanel::OnGetDlgCode() 
{
// want the arrow keys

	return DLGC_WANTARROWS;
}


/**************/
/* WM_KEYDOWN */
/**************/

void COptionsPanel::OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags)
{
	BOOL bControl;

// get the control key state

	bControl=(GetKeyState(VK_CONTROL) & 0x8000)!=0;

	switch(nChar)
	{
		case VK_UP:
			if(bControl)
				OnVScroll(SB_LINEUP,0,NULL);
			else
				CursorUp();
			break;

		case VK_DOWN:
			if(bControl)
				OnVScroll(SB_LINEDOWN,0,NULL);
			else
				CursorDown();
			break;

		case VK_PRIOR:
			PageUp();
			break;

		case VK_NEXT:
			PageDown();
			break;

		case VK_SPACE:
			if(m_pFocus)
				SelectItem(m_pFocus);
			break;

		case VK_END:
			CursorEnd();
			break;

		case VK_HOME:
			CursorHome();
			break;

		default:
			CButton::OnKeyDown(nChar,nRepCnt,nFlags);
			break;
	}
}


/*************/
/* Cursor up */
/*************/

void COptionsPanel::CursorUp(void)
{
	CRect			rcClient;
	int				cursor;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[0])
		return;

// check for first visible item

	cursor=GetIterator(m_pFocus)-m_Items.begin();

	if(m_Top==cursor)
		OnVScroll(SB_LINEUP,0,NULL);

// move the cursor up

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[cursor-1];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,cursor-1);
}


/***************/
/* Cursor down */
/***************/

void COptionsPanel::CursorDown(void)
{
	CRect			rcClient;
	int				perpage,cursor;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[m_Items.size()-1])
		return;

// check for last visible item

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	perpage=rcClient.Height()/16;
	cursor=GetIterator(m_pFocus)-m_Items.begin();

	if(m_Top+perpage-1==cursor)
		OnVScroll(SB_LINEDOWN,0,NULL);

// move the cursor down

	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[cursor+1];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,cursor+1);
}


/***********/
/* Page up */
/***********/

void COptionsPanel::PageUp(void)
{
	CRect			rcClient;
	int				cursor,perpage,newpos;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[0])
		return;

// get items per page and cursor pos

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	perpage=rcClient.Height()/16;
	cursor=GetIterator(m_pFocus)-m_Items.begin();

// move the cursor up

	newpos=max(0,min((int)m_Items.size()-1,cursor-perpage+1));
	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[newpos];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,newpos);
}


/*************/
/* Page down */
/*************/

void COptionsPanel::PageDown(void)
{
	CRect			rcClient;
	int				cursor,perpage,newpos;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[m_Items.size()-1])
		return;

// get items per page and cursor pos

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	perpage=rcClient.Height()/16;
	cursor=GetIterator(m_pFocus)-m_Items.begin();

// move the cursor down

	newpos=max(0,min((int)m_Items.size()-1,cursor+perpage-1));
	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[newpos];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,newpos);
}


/***************/
/* Cursor home */
/***************/

void COptionsPanel::CursorHome(void)
{
	CRect			rcClient;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[0])
		return;

// move the cursor home

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[0];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,0);
}


/**************/
/* Cursor end */
/**************/

void COptionsPanel::CursorEnd(void)
{
	CRect			rcClient;
	CItem		 *pLastFocus;
	CClientDC dc(this);

// check for nothing to do

	if(!m_Items.size() || m_pFocus==NULL || m_pFocus==&m_Items[m_Items.size()-1])
		return;

// move the cursor home

	GetAdjustedClientRect(rcClient);
	dc.IntersectClipRect(rcClient);

	pLastFocus=m_pFocus;
	m_pFocus=&m_Items[m_Items.size()-1];

	DrawSingleItem(&dc,*pLastFocus,rcClient);
	DrawSingleItem(&dc,*m_pFocus,rcClient);

// ensure item is visible

	EnsureVisible(rcClient,m_Items.size()-1);
}


/*****************************/
/* Ensure an item is visible */
/*****************************/

void COptionsPanel::EnsureVisible(const CRect& rcClient,const int nItem)
{
	int nLast,perpage,newtop;

// get last visible and return if we can't do anything

	perpage=rcClient.Height()/16;
	if((nLast=m_Top+perpage-1)<m_Top)
		return;

// check for nothing to do

	if(nItem>=m_Top && nItem<=nLast)
		return;

// move in the appropriate direction

	if(nItem<m_Top)
		newtop=nItem;
	else if(nItem>nLast)
		newtop=nItem-perpage+1;

	DisplaceItemRects((m_Top-newtop)*16);
	m_Top=newtop;
	SetupScrollBars();
	InvalidateRect(NULL);
}


/*******************************************/
/* notify the parent of a selection change */
/*******************************************/

void COptionsPanel::NotifyParentSelChange(const CItem& item) const
{
	NMOPTIONSPANEL nm;

// fill in the common header

	nm.hdr.hwndFrom=GetSafeHwnd();
	nm.hdr.idFrom=GetDlgCtrlID();
	nm.hdr.code=OPN_SELCHANGE;

// fill in the rest

	nm.idButton=item.m_nID;
	nm.bSelected=(item.m_dwFlags & itemChecked)!=0;

// send the message

	GetParent()->SendMessage(WM_NOTIFY,nm.hdr.idFrom,(LPARAM)&nm);
}


/***********/
/* WM_SIZE */
/***********/

void COptionsPanel::OnSize(UINT nType,int cx,int cy)
{
	CRect rcClient;

// ensure we are created

	if(!IsWindow(GetSafeHwnd()))
		return;

	// Added by Totaal Software
	if(!IsWindow(m_wndVertScroll.GetSafeHwnd()))
		return;

// move the scrollbar

	GetClientRect(rcClient);
	m_wndVertScroll.SetWindowPos(NULL,rcClient.right-2-GetSystemMetrics(SM_CXVSCROLL),rcClient.top+2,GetSystemMetrics(SM_CXVSCROLL),rcClient.Height()-2,SWP_NOZORDER);
	SetupScrollBars();
}
