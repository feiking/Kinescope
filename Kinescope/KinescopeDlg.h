// KinescopeDlg.h : header file

#if !defined(AFX_KINESCOPEDLG_H__7018469F_ABB6_4939_BCF7_10258C78A2C5__INCLUDED_)
#define AFX_KINESCOPEDLG_H__7018469F_ABB6_4939_BCF7_10258C78A2C5__INCLUDED_
#include "FrameDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKinescopeDlg dialog

class CKinescopeDlg : public CDialog
{
// Construction
public:
	void CreateTray(int state = 1);//设置系统托盘
	void SetFileName();			//设置文件名
	void SetFileList();			//设置文件列表
	void GetResidualPlace();	//获得磁盘剩余空间
	virtual void OnOK();
	CKinescopeDlg(CWnd* pParent = NULL);	// standard constructor

	CToolBar m_ToolBar;			//工具栏
	CStatusBar m_StatusBar;		//状态栏
	CMenu m_Menu;				//菜单
	BOOL m_IsStart;				//是否为开始录像
	BOOL m_IsPause;				//是否为暂停
	BOOL m_IsTime;				//是否保存完一帧
	BOOL m_IsPath;				//是否选择了存储路径
	CString m_ToolText;			//工具栏提示
	BOOL m_Once;				//添加托盘图标
	HICON m_Icon1;				//普通状态托盘图标
	HICON m_Icon2;				//录像状态托盘图标
	HICON m_Icon3;				//暂停状态托盘图标
	CImageList m_ImageList;		//工具栏图像列表
	CImageList m_ImageList2;	//列表控件图像列表
	CFrameDlg* m_fDlg;			//显示图片对话框
	long m_FrameNum;			//录像文件帧数
// Dialog Data
	//{{AFX_DATA(CKinescopeDlg)
	enum { IDD = IDD_KINESCOPE_DIALOG };
	CStatic	m_Picture;
	CStatic	m_Frame;
	CEdit	m_Rate;
	CButton	m_Cursor;
	CStatic	m_Place;
	CListCtrl	m_List;
	CEdit	m_Path;
	CEdit	m_Name;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKinescopeDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKinescopeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnCut();
	afx_msg void OnCoalition();
	afx_msg void OnGetTime();
	afx_msg void OnGrasp();
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButselect();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuplay();
	afx_msg void OnMenuname();
	afx_msg void OnMenusave();
	afx_msg void OnMenudelete();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMenutime();
	afx_msg void OnTray(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnChangeEdit3();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KINESCOPEDLG_H__7018469F_ABB6_4939_BCF7_10258C78A2C5__INCLUDED_)
