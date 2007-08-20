// PresentationTextView.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPresentationTextView

IMPLEMENT_DYNCREATE(CPresentationTextView, CRichEditView)

CPresentationTextView::CPresentationTextView()
{
}

CPresentationTextView::~CPresentationTextView()
{
}


BEGIN_MESSAGE_MAP(CPresentationTextView, CRichEditView)
	//{{AFX_MSG_MAP(CPresentationTextView)
	ON_COMMAND(ID_NEXT_PANE, OnNextPane)
	ON_COMMAND(ID_PREV_PANE, OnNextPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPresentationTextView drawing

void CPresentationTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPresentationTextView diagnostics

#ifdef _DEBUG
void CPresentationTextView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CPresentationTextView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPresentationTextView message handlers

void CPresentationTextView::OnNextPane()
{
	// Delicate business beyond this point
	// We order the split frame that somewhere is
	//  the parent of this class to switch the active pane
	((CChildFrame*)
		((CSplitterWnd*)GetParent())
			->GetParent())
				->SetActivePaneTreeViewMain();
}

bool CPresentationTextView::Navigate(CEventItem* pEI)
{
	if( pEI->IsPublicationAvailable() )
	{
		CString strFile = pEI->ComposeFileNamePathCSV();

		CString strText;

		// Byte-order mark goes at the begining of the UNICODE file
		_TCHAR bom;
		UINT ret;

		CFile* pFile = new CFile();
		if( !pFile->Open( strFile, CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary ) )
		{
			return false;
		}
		ret = pFile->Read( &bom, sizeof(_TCHAR) );
		pFile->Close();
		if( pFile )
		{
			delete pFile;
		}
		if( ret=0 )
		{
			return false;
		}

		// If we are reading UNICODE file
		if ( bom == _TCHAR(0xFEFF ) )
		{
			// Reading buffer
			_TCHAR buffer[1024];

			CFile* pFile = new CFile();
			if( !pFile->Open( strFile, CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary ) )
			{
				return false;
			}

			// Strip off the BOM again
			int i = pFile->Read( &bom, sizeof(_TCHAR) );

			UINT ret;
			while( ret = pFile->Read( buffer, sizeof(buffer) ) )
			{
				buffer[ret/2] = _T('\0');
				strText += buffer;
			}

			pFile->Close();
			if( pFile )
			{
				delete pFile;
			}
		}
		else
		// If we are reading ANSI file
		{
			CStdioFile* pStdioFile = new CStdioFile();
			pStdioFile->Open( strFile, CFile::modeRead );
			pStdioFile->ReadString( strText );
			pStdioFile->Close();
			if( pStdioFile )
			{
				delete pFile;
			}
		}

		// Only show if proper length
		if( strText.GetLength() )
		{
			LockWindowUpdate();

			CString title = pEI->ComposeTocTitle() + TEXT("\n");
			CString subtitle = pEI->ComposeFileNameCSV() + TEXT("\n") + TEXT("\n");

			strText = TEXT("\n") + title + subtitle + strText;

			CRichEditCtrl& edit = GetRichEditCtrl();

			// Put on screen
			edit.SetWindowText(strText);

			// Layout of title lines

			edit.SetSel(1, title.GetLength());
			edit.SetSelectionCharFormat(m_cf1);

			edit.SetSel(title.GetLength()+1, title.GetLength()+subtitle.GetLength()-1);
			edit.SetSelectionCharFormat(m_cf2);

			edit.SetSel(0, 0);

			UnlockWindowUpdate();

			return true;
		}
	}
	return false;
}

void CPresentationTextView::OnInitialUpdate() 
{
	CRichEditView::OnInitialUpdate();

	m_font.CreateFont( 16, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, TMPF_TRUETYPE|FF_MODERN, NULL);
	SetFont(&m_font);

	CRichEditCtrl& edit = GetRichEditCtrl();
	edit.SetReadOnly();

	memset(&m_cf1, '\0', sizeof(m_cf1));
	m_cf1.cbSize = sizeof(m_cf1);
	m_cf1.dwMask |= CFM_SIZE;
	m_cf1.dwMask |= CFM_FACE; 
	m_cf1.dwMask |= CFM_COLOR;
	m_cf1.dwMask |= CFM_BOLD;
	m_cf1.dwEffects |= CFE_BOLD;
	m_cf1.yHeight = 400;
	m_cf1.crTextColor = RGB(0,0,128);
	m_cf1.bPitchAndFamily = TMPF_TRUETYPE|FF_ROMAN;

	memset(&m_cf2, '\0', sizeof(m_cf2));
	m_cf2.cbSize = sizeof(m_cf2);
	m_cf2.dwMask |= CFM_SIZE;
	m_cf2.dwMask |= CFM_FACE; 
	m_cf2.dwMask |= CFM_COLOR;
	m_cf2.yHeight = 250;
	m_cf2.crTextColor = RGB(128,0,0);
	m_cf2.bPitchAndFamily = TMPF_TRUETYPE|FF_ROMAN;
}
