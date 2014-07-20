#if !defined(AFX_COALITIONDLG_H__356E1E97_8E91_4137_A201_E0DE1CECF370__INCLUDED_)
#define AFX_COALITIONDLG_H__356E1E97_8E91_4137_A201_E0DE1CECF370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoalitionDlg.h : header file

/////////////////////////////////////////////////////////////////////////////
// CCoalitionDlg dialog

class CCoalitionDlg : public CDialog
{
// Construction
public:
	CCoalitionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoalitionDlg)
	enum { IDD = IDD_COALITION_DIALOG };
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoalitionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoalitionDlg)
	afx_msg void OnButadd();
	afx_msg void OnButcoalition();
	afx_msg void OnButdel();
	afx_msg void OnButclear();
	afx_msg void OnButup();
	afx_msg void OnButdown();
	afx_msg void OnButexit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COALITIONDLG_H__356E1E97_8E91_4137_A201_E0DE1CECF370__INCLUDED_)
