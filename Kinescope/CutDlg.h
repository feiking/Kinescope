#if !defined(AFX_CUTDLG_H__9FC4C9EE_E60D_4C0D_A81B_6916C29AF9CC__INCLUDED_)
#define AFX_CUTDLG_H__9FC4C9EE_E60D_4C0D_A81B_6916C29AF9CC__INCLUDED_
#include "FrameDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CCutDlg dialog

class CCutDlg : public CDialog
{
// Construction
public:
	void CreateFrameDialog();
	void ShowBmp(int frame = 0);
	void SetControlRect();
	CCutDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_Name;
	long m_FrameNum;
	HBITMAP m_hBitmap;
	CFrameDlg* m_fDlg;
	int m_Start;
	int m_Stop;

// Dialog Data
	//{{AFX_DATA(CCutDlg)
	enum { IDD = IDD_CUT_DIALOG };
	CStatic	m_Frame;
	CStatic	m_Picture;
	int		m_Rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCutDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnButprevious();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButnext();
	afx_msg void OnButstart();
	afx_msg void OnButstop();
	afx_msg void OnButgoto();
	afx_msg void OnButcut();
	afx_msg void OnButexit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTDLG_H__9FC4C9EE_E60D_4C0D_A81B_6916C29AF9CC__INCLUDED_)
