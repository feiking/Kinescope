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
	void CreateTray(int state = 1);//����ϵͳ����
	void SetFileName();			//�����ļ���
	void SetFileList();			//�����ļ��б�
	void GetResidualPlace();	//��ô���ʣ��ռ�
	virtual void OnOK();
	CKinescopeDlg(CWnd* pParent = NULL);	// standard constructor

	CToolBar m_ToolBar;			//������
	CStatusBar m_StatusBar;		//״̬��
	CMenu m_Menu;				//�˵�
	BOOL m_IsStart;				//�Ƿ�Ϊ��ʼ¼��
	BOOL m_IsPause;				//�Ƿ�Ϊ��ͣ
	BOOL m_IsTime;				//�Ƿ񱣴���һ֡
	BOOL m_IsPath;				//�Ƿ�ѡ���˴洢·��
	CString m_ToolText;			//��������ʾ
	BOOL m_Once;				//�������ͼ��
	HICON m_Icon1;				//��ͨ״̬����ͼ��
	HICON m_Icon2;				//¼��״̬����ͼ��
	HICON m_Icon3;				//��ͣ״̬����ͼ��
	CImageList m_ImageList;		//������ͼ���б�
	CImageList m_ImageList2;	//�б�ؼ�ͼ���б�
	CFrameDlg* m_fDlg;			//��ʾͼƬ�Ի���
	long m_FrameNum;			//¼���ļ�֡��
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
