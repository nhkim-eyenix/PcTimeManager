
// TimeSchedulerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TimeScheduler.h"
#include "TimeSchedulerDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#pragma comment( lib, "advapi32.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimeSchedulerDlg dialog



CTimeSchedulerDlg::CTimeSchedulerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMESCHEDULER_DIALOG, pParent)
	, m_edit_time_min(30)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeSchedulerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIME, m_edit_time_min);
}

BEGIN_MESSAGE_MAP(CTimeSchedulerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SET, &CTimeSchedulerDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CTimeSchedulerDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CTimeSchedulerDlg message handlers

BOOL CTimeSchedulerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimeSchedulerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimeSchedulerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimeSchedulerDlg::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	MySystemShutdown(3000);
}

void CTimeSchedulerDlg::OnBnClickedButtonCancel()
{
	PreventSystemShutdown();
}


BOOL CTimeSchedulerDlg::MySystemShutdown(DWORD time)
{
	LPTSTR lpMsg = L"ShutDown";
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 

	BOOL fResult;               // system shutdown flag 

	// Get the current process token handle so we can get shutdown 
	// privilege. 

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	// Get the LUID for shutdown privilege. 

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	// Cannot test the return value of AdjustTokenPrivileges. 

	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	// Display the shutdown dialog box and start the countdown. 

#if 0
	fResult = InitiateSystemShutdown(
		NULL,    // shut down local computer 
		lpMsg,   // message for user
		time,      // time-out period, in seconds 
		FALSE,   // ask user to close apps 
		TRUE);   // reboot after shutdown 

	if (!fResult)
		return FALSE;
#endif 0
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
		SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
		SHTDN_REASON_MINOR_UPGRADE |
		SHTDN_REASON_FLAG_PLANNED))
		return FALSE;

	// Disable shutdown privilege. 

	tkp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	return TRUE;
}




BOOL CTimeSchedulerDlg::PreventSystemShutdown()
{
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 

	// Get the current process token handle  so we can get shutdown 
	// privilege. 

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	// Get the LUID for shutdown privilege. 

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get shutdown privilege for this process. 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;

	// Prevent the system from shutting down. 

	if (!AbortSystemShutdown(NULL))
		return FALSE;

	// Disable shutdown privilege. 

	tkp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	return TRUE;
}
