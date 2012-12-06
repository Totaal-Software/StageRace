// srcalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrcalcDlg dialog

CSrcalcDlg::CSrcalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrcalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrcalcDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSrcalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrcalcDlg)
	DDX_Control(pDX, IDC_RES1, m_res1);
	DDX_Control(pDX, IDC_INP3, m_inp3);
	DDX_Control(pDX, IDC_INP2, m_inp2);
	DDX_Control(pDX, IDC_INP1, m_inp1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrcalcDlg, CDialog)
	//{{AFX_MSG_MAP(CSrcalcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_MINUS, OnMinus)
	ON_BN_CLICKED(IDC_PLUS, OnPlus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrcalcDlg message handlers

BOOL CSrcalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_inp1.Init( 3, 2 );
	m_inp2.Init( 3, 2 );
	m_inp3.Init( 3, 2 );
	m_res1.Init( 3, 2 );
	m_afterClear = true;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSrcalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.m_name = "StageRace Time Calculator";
		dlgAbout.m_version = "2.00 bèta";
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSrcalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSrcalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSrcalcDlg::OnClear()
{
	m_inp1.SetReadOnly( false );
	m_inp2.SetReadOnly( false );
	m_inp3.SetReadOnly( true  );

	m_inp1.SetTime( 0 );
	m_inp2.SetTime( 0 );
	m_inp3.SetTime( 0 );
	m_res1.SetTime( 0 );
	m_inp1.SetFocus();
	SetDlgItemText( IDC_OPERATION, "+/-" );

	m_afterClear = true;
}

void CSrcalcDlg::OnMinus() 
{
	DoCalc( false );
}

void CSrcalcDlg::OnPlus() 
{
	DoCalc( true );
}

void CSrcalcDlg::DoCalc(bool bPlus)
{
	// TODO: Add your control notification handler code here
	if( !m_afterClear )
	{
		m_inp1.SetTime( m_res1.GetTime() );
		m_inp2.SetTime( m_inp3.GetTime() );
		m_inp3.SetTime( 0 );
	}
	else
		m_afterClear = false;

	CString czResult;
	if( bPlus )
	{
		m_res1.SetTime( m_inp1.GetTime() + m_inp2.GetTime() );
		SetDlgItemText( IDC_OPERATION, "+" );
	}
	else
	{
		m_res1.SetTime( abs((long) (m_inp1.GetTime() - m_inp2.GetTime()) ) );
		SetDlgItemText( IDC_OPERATION, "-" );
	}

	m_inp1.SetReadOnly( true  );
	m_inp2.SetReadOnly( true  );
	m_inp3.SetReadOnly( false );
	m_inp3.SetFocus();
}

BOOL CSrcalcDlg::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		// a)
		// Check whether the return key has been pressed
		if (pMsg->wParam==VK_RETURN)
		{
			DoCalc(true);
			return TRUE;
		}
		// b)
		// Check whether the escape key has been pressed
		if (pMsg->wParam==VK_ESCAPE)
		{
			OnClear();
			return TRUE;
		}
		// c)
		// Check whether the plus key has been pressed
		if ( (pMsg->wParam==VK_ADD) || (pMsg->wParam==0xbb) )
		{
			DoCalc(true);
			return TRUE;
		}
		// d)
		// Check whether the minus key has been pressed
		if ( (pMsg->wParam==VK_SUBTRACT) || (pMsg->wParam==0xbd) )
		{
			DoCalc(false);
			return TRUE;
		}
		// Note: for c and d the main keyboard's key
		// and the numerical keypad's key are given
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
