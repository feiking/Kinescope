#if !defined(AFX_NAMEDLG_H__ED6A8795_09D2_46EB_84EF_82D4143F1311__INCLUDED_)
#define AFX_NAMEDLG_H__ED6A8795_09D2_46EB_84EF_82D4143F1311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameDlg.h : header file

// CNameDlg dialog

class CNameDlg : public CDialog
{
// Construction
public:
	CNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNameDlg)
	enum { IDD = IDD_NAME_DIALOG };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNameDlg)
	virtual void OnOK();
	afx_msg void OnMenutime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEDLG_H__ED6A8795_09D2_46EB_84EF_82D4143F1311__INCLUDED_)
