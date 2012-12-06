///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Edwin Engelen (from www.codeguru.com)
// Primary date: 21-02-2000
// Filename: TransparentImage.h
// Description: Makes an image transparent
//
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 21-02-2000	EE	Delivered as is
//
#if !defined(AFX_TRANSPARENTIMAGE_H__DAFA8E6A_D011_48F8_8DB4_B23F16FF663A__INCLUDED_)
#define AFX_TRANSPARENTIMAGE_H__DAFA8E6A_D011_48F8_8DB4_B23F16FF663A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTransparentImage window

class CTransparentImage : public CStatic
{
// Construction
public:
	CTransparentImage();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentImage)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTransparentcolor( COLORREF c );
	virtual ~CTransparentImage();

	// Generated message map functions
protected:
	COLORREF m_transparentcolor;
	//{{AFX_MSG(CTransparentImage)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTIMAGE_H__DAFA8E6A_D011_48F8_8DB4_B23F16FF663A__INCLUDED_)
