// TransparentImage.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentImage

CTransparentImage::CTransparentImage()
{
	m_transparentcolor = RGB( 255, 0, 255 );
}

CTransparentImage::~CTransparentImage()
{
}


BEGIN_MESSAGE_MAP(CTransparentImage, CStatic)
	//{{AFX_MSG_MAP(CTransparentImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentImage message handlers

void CTransparentImage::OnPaint() 
{
	HBITMAP l_hbmpBitmap = GetBitmap() ;

	if( l_hbmpBitmap == NULL )
	{
		Default() ;

		return ;
	}

	CPaintDC l_PaintDC( this ) ;

	////////////////////////////////////////////////////////////////////////////
	// Prepare everything for drawing
	////////////////////////////////////////////////////////////////////////////

	CRect l_rcClient ;

	GetClientRect( &l_rcClient ) ;

	CDC		 l_BufferDC ;
			 l_BufferDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_BufferBitmap ;
			 l_BufferBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
	CBitmap* l_pOldBufferBitmap = l_BufferDC.SelectObject( &l_BufferBitmap ) ;
	CDC		 l_MaskDC ;
			 l_MaskDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_MaskBitmap ;
			 l_MaskBitmap.CreateBitmap( l_rcClient.Width(), l_rcClient.Height(), 1, 1, NULL ) ;
	CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ;

	#define ROP4_TRANSPARENTBLIT		0xCCAA0020
	#define SRCMASK						0x00220326

	////////////////////////////////////////////////////////////////////////////
	// Fill with transparent color
	////////////////////////////////////////////////////////////////////////////

	l_BufferDC.FillSolidRect( &l_rcClient, m_transparentcolor ) ;

	////////////////////////////////////////////////////////////////////////////
	// Blit the bitmap to the buffer
	////////////////////////////////////////////////////////////////////////////

	CDC		 l_MemoryDC ;
			 l_MemoryDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( l_hbmpBitmap ) ) ;

	l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCCOPY ) ;

	l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ;

	////////////////////////////////////////////////////////////////////////////
	// Create the mask.
	////////////////////////////////////////////////////////////////////////////

	COLORREF l_crOldBack = l_BufferDC.SetBkColor( m_transparentcolor ) ;

	l_MaskDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCCOPY ) ;

	l_BufferDC.SetBkColor( l_crOldBack ) ;

	////////////////////////////////////////////////////////////////////////////
	// Draw the bitmap transparently now, since not all devices support this
	// and Windows 98 does not (duh?), if this fails, we do it the long way.
	////////////////////////////////////////////////////////////////////////////

	if( ! l_PaintDC.MaskBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, l_MaskBitmap, 0, 0, ROP4_TRANSPARENTBLIT ) )
	{
		CDC		 l_CopyDC ;
				 l_CopyDC.CreateCompatibleDC( &l_PaintDC ) ;
		CBitmap  l_CopyBitmap ;
				 l_CopyBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
		CBitmap* l_pOldCopyBitmap = l_CopyDC.SelectObject( &l_CopyBitmap ) ;

		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_PaintDC,  0, 0, SRCCOPY  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCAND   ) ;
		l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCMASK  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCPAINT ) ;
		l_PaintDC.BitBlt(  0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_CopyDC,   0, 0, SRCCOPY  ) ;

		l_CopyDC.SelectObject( l_pOldCopyBitmap ) ;
	}

	////////////////////////////////////////////////////////////////////////////
	// Clean up.
	////////////////////////////////////////////////////////////////////////////

	l_MaskDC.SelectObject( l_pOldMaskBitmap ) ;
	l_BufferDC.SelectObject( l_pOldBufferBitmap ) ;
}

void CTransparentImage::SetTransparentcolor(COLORREF c)
{
	m_transparentcolor = c;
}
