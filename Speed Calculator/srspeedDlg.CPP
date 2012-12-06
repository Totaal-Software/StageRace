// srspeedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrspeedDlg dialog

CSrspeedDlg::CSrspeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrspeedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrspeedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSrspeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrspeedDlg)
	DDX_Control(pDX, IDC_TIME, m_time);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrspeedDlg, CDialog)
	//{{AFX_MSG_MAP(CSrspeedDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_DISTANCE, OnChange)
	ON_EN_UPDATE(IDC_TIME, OnChange)
	ON_BN_CLICKED(IDC_MPH, OnMph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrspeedDlg message handlers

BOOL CSrspeedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_time.Init(3,2);
	((CEdit*) GetDlgItem( IDC_DISTANCE ))->SetLimitText(7);

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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSrspeedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.m_name = "StageRace Speed Calculator";
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
void CSrspeedDlg::OnPaint() 
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
HCURSOR CSrspeedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSrspeedDlg::DoCalc()
{
	CString czDistance;
	GetDlgItemText( IDC_DISTANCE, czDistance );

	bool bMPH = IsDlgButtonChecked( IDC_MPH )>0;

	int i = atoi( czDistance );
	SetDlgItemText(
			IDC_SPEED,
			CStageSpeed::GetSpeed( i, m_time.GetTime(), true, bMPH, "\r\n" )
		);
}

void CSrspeedDlg::OnChange() 
{

	SetDlgItemText(
		IDC_MILES,
		CStageCalc::CommaValue(
			CStageDistance::ToMiles(GetDlgItemInt( IDC_DISTANCE ))
		));
	DoCalc();
}


BOOL CSrspeedDlg::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		// a)
		// Check whether the return key has been pressed
		if (pMsg->wParam==VK_RETURN)
			return TRUE;
		// b)
		// Check whether the escape key has been pressed
		if (pMsg->wParam==VK_ESCAPE)
			return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}


void CSrspeedDlg::OnMph() 
{
	bool bMPH = IsDlgButtonChecked( IDC_MPH )>0;
	GetDlgItem(IDC_MILES)->ShowWindow(
		bMPH?SW_SHOW:SW_HIDE );
	GetDlgItem(IDC_MILES_STATIC)->ShowWindow(
		bMPH?SW_SHOW:SW_HIDE );
	OnChange();
}
