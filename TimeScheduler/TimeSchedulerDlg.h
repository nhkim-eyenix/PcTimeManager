
// TimeSchedulerDlg.h : header file
//

#pragma once


// CTimeSchedulerDlg dialog
class CTimeSchedulerDlg : public CDialogEx
{
// Construction
public:
	CTimeSchedulerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMESCHEDULER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonCancel();

	BOOL MySystemShutdown(DWORD time);
	BOOL PreventSystemShutdown();
	CEdit m_edit_time;
	int m_edit_time_min;
};
