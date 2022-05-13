
// TimeScheduler.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "TimeScheduler.h"
#include "TimeSchedulerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimeSchedulerApp

BEGIN_MESSAGE_MAP(CTimeSchedulerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTimeSchedulerApp construction

CTimeSchedulerApp::CTimeSchedulerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTimeSchedulerApp object

CTimeSchedulerApp theApp;


// CTimeSchedulerApp initialization

BOOL CTimeSchedulerApp::InitInstance()
{
	CWinApp::InitInstance();

	CTimeSchedulerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}




