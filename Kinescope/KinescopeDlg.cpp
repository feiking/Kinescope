#include "stdafx.h"
#include "Kinescope.h"
#include "KinescopeDlg.h"
#include "math.h"
#include <windowsx.h>
#include "NameDlg.h"
#include "CutDlg.h"
#include "CoalitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define HOTKEY_START		11111
#define HOTKEY_PAUSE		11112
#define HOTKEY_GRASP		11113
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
AVISTREAMINFO strhdr;
PAVIFILE pfile;
PAVISTREAM ps; 
PAVISTREAM pComStream;
int nFrames = 0; 
HRESULT hr; 
AVICOMPRESSOPTIONS pCompressOption;   
AVICOMPRESSOPTIONS FAR * opts[1] = {&pCompressOption};  

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKinescopeDlg dialog

CKinescopeDlg::CKinescopeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKinescopeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKinescopeDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Icon1 = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Icon2 = AfxGetApp()->LoadIcon(IDI_ICONSTART);
	m_Icon3 = AfxGetApp()->LoadIcon(IDI_ICONPAUSE);
}

void CKinescopeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKinescopeDlg)
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_FRAME, m_Frame);
	DDX_Control(pDX, IDC_EDIT3, m_Rate);
	DDX_Control(pDX, IDC_CHECK1, m_Cursor);
	DDX_Control(pDX, IDC_STATICPLACE, m_Place);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT2, m_Path);
	DDX_Control(pDX, IDC_EDIT1, m_Name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKinescopeDlg, CDialog)
	//{{AFX_MSG_MAP(CKinescopeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_START,OnStart)
	ON_COMMAND(ID_PAUSE,OnPause)
	ON_COMMAND(ID_STOP,OnStop)
	ON_COMMAND(ID_CUT,OnCut)
	ON_COMMAND(ID_COALITION,OnCoalition)
	ON_COMMAND(ID_TIME,OnGetTime)
	ON_COMMAND(ID_GRASP,OnGrasp)
	ON_COMMAND(ID_EXIT,OnExit)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTSELECT, OnButselect)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_MENUPLAY, OnMenuplay)
	ON_COMMAND(ID_MENUNAME, OnMenuname)
	ON_COMMAND(ID_MENUSAVE, OnMenusave)
	ON_COMMAND(ID_MENUDELETE, OnMenudelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_COMMAND(ID_MENUTIME, OnMenutime)
	ON_MESSAGE(WM_ONTRAY,OnTray)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKinescopeDlg message handlers

BOOL CKinescopeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	if(!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP   
		| CBRS_TOOLTIPS |CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		return FALSE;      
	}
	//����ͼ��
	m_ImageList.Create(32, 32, ILC_COLOR24|ILC_MASK,2,2);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONSTART)); 
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONPAUSE));  	
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONSTOP));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONCUT)); 
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONCOALITION));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONTIME)); 
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONGRASP)); 
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONEXIT));
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ImageList.Detach();
	m_ImageList2.Create(16, 16, ILC_COLOR24|ILC_MASK,2,2);
	m_ImageList2.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_List.SetImageList(&m_ImageList2,LVSIL_SMALL);
	m_ImageList2.Detach();

	m_ToolBar.SetButtons(NULL, 11); //��10����ť
	// ����ÿ�����߰�ť����
	m_ToolBar.SetButtonInfo(0, ID_START, TBSTYLE_BUTTON, 0);
	m_ToolBar.SetButtonText(0, "��ʼ");
	m_ToolBar.SetButtonInfo(1, ID_PAUSE, TBSTYLE_BUTTON, 1);
	m_ToolBar.SetButtonText(1, "��ͣ/����");
	m_ToolBar.SetButtonInfo(2, ID_STOP, TBSTYLE_BUTTON , 2);
	m_ToolBar.SetButtonText(2, "ֹͣ");
	m_ToolBar.SetButtonInfo(3, ID_SEPARATOR, TBBS_SEPARATOR , 0);
	m_ToolBar.SetButtonInfo(4, ID_CUT, TBSTYLE_BUTTON, 3);
	m_ToolBar.SetButtonText(4, "¼���ȡ");
	m_ToolBar.SetButtonInfo(5, ID_COALITION, TBSTYLE_BUTTON , 4);
	m_ToolBar.SetButtonText(5, "¼��ϳ�");
	m_ToolBar.SetButtonInfo(6, ID_TIME, TBSTYLE_BUTTON , 5);
	m_ToolBar.SetButtonText(6, "¼��ʱ��");
	m_ToolBar.SetButtonInfo(7, ID_SEPARATOR, TBBS_SEPARATOR , 0);
	m_ToolBar.SetButtonInfo(8, ID_GRASP, TBSTYLE_BUTTON , 6);
	m_ToolBar.SetButtonText(8, "��Ļץͼ");
	m_ToolBar.SetButtonInfo(9, ID_SEPARATOR, TBBS_SEPARATOR , 0);
	m_ToolBar.SetButtonInfo(10, ID_EXIT, TBSTYLE_BUTTON , 7);
	m_ToolBar.SetButtonText(10, "�˳�");
	m_ToolBar.SetSizes(CSize(40,40), CSize(32,32)); //���ð�ť�Ĵ�С
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_PAUSE,FALSE);
	m_ToolBar.GetToolBarCtrl().EnableButton(ID_STOP,FALSE);
	m_ToolBar.EnableToolTips(TRUE);

	UINT array[3]={11001,11002,11003};											//��������
	m_StatusBar.Create(this); 								//����״̬������
	m_StatusBar.SetIndicators(array,sizeof(array)/sizeof(UINT));		//������
	CRect rect;
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,array[0],0,rect.Width()*7/8); 				//���������
	m_StatusBar.SetPaneInfo(1,array[1],0,rect.Width()*1/8); 				//���������
	m_StatusBar.SetPaneText(0,"");					//��������ı�
	m_StatusBar.SetPaneText(1,"��ǰ�ļ�����0");							//��������ı�
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_Menu.LoadMenu(IDR_LISTMENU);

	RegisterHotKey(this->GetSafeHwnd(),HOTKEY_START,0x0000,0x0071);
	RegisterHotKey(this->GetSafeHwnd(),HOTKEY_PAUSE,0x0000,0x0072);
	RegisterHotKey(this->GetSafeHwnd(),HOTKEY_GRASP,0x0000,0x0073);  
	m_Once    = TRUE;
	CreateTray();

	m_IsStart = TRUE;
	m_IsPause = TRUE;
	m_IsTime  = TRUE;
	m_IsPath  = FALSE;
	
	m_Rate.SetWindowText("3");
	CRect fRect;
	m_Frame.GetClientRect(&fRect);							//����Ӵ�����ʾ����
	m_Frame.MapWindowPoints(this,fRect);
	m_fDlg = new CFrameDlg;
	m_fDlg->Create(IDD_FRAME_DIALOG,this); 		//������ģ̬�Ի���
	m_fDlg->MoveWindow(fRect);						//�ƶ��Ի���λ��
	m_fDlg->ShowWindow(SW_SHOW);					//��ʾ�Ի���
	m_Picture.SetParent(m_fDlg);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKinescopeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	if(nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKinescopeDlg::OnPaint() 
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
HCURSOR CKinescopeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKinescopeDlg::OnOK()
{
}

void CKinescopeDlg::OnStart()
{
	if(!m_IsPath)
	{
		MessageBox("��ѡ���ļ��洢λ��");
		return;
	}
	if(m_IsStart == TRUE)
	{
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_START,FALSE);
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_PAUSE,TRUE);
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_STOP,TRUE);
		ShowWindow(SW_HIDE);
		CreateTray(2);
		AVIFileInit(); 
		SetTimer(1,100,NULL);
	}
	else
	{
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_START,TRUE);
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_PAUSE,FALSE);
		m_ToolBar.GetToolBarCtrl().EnableButton(ID_STOP,FALSE);
		ShowWindow(SW_SHOW);
		KillTimer(1);
		CreateTray(1);
		AVIStreamClose(pComStream);
		AVIStreamClose(ps);
		if(pfile != NULL)
			AVIFileRelease(pfile);
		AVIFileExit();
		nFrames =0; 
		m_List.DeleteAllItems();
		SetFileList();
	}
	m_IsStart = !m_IsStart;
}

void CKinescopeDlg::OnPause()
{
	if(m_IsPause == TRUE)
	{
		KillTimer(1);
		CreateTray(3);
	}
	else
	{
		CreateTray(2);
		SetTimer(1,100,NULL);
	}
	m_IsPause = !m_IsPause;
}

void CKinescopeDlg::OnStop()
{
	OnStart();
}

void CKinescopeDlg::OnCut()
{
	int pos = m_List.GetSelectionMark();
	CString name = m_List.GetItemText(pos,0);
	name += ".avi";
	CString path,oname;
	m_Path.GetWindowText(path);
	oname = path + "\\" + name;
	CCutDlg dlg;
	dlg.m_Name = oname;
	dlg.m_FrameNum = m_FrameNum;
	dlg.DoModal();
}

void CKinescopeDlg::OnCoalition()
{
	CCoalitionDlg dlg;
	dlg.DoModal();
}

void CKinescopeDlg::OnGetTime()
{
	OnMenutime();
}

void CKinescopeDlg::OnGrasp()
{
	
	if(!m_IsPath)
	{
		MessageBox("��ѡ���ļ��洢λ��");
		return;
	}
	CDC* pDeskDC =  GetDesktopWindow()->GetDC();		//��ȡ���滭������
	CRect rc;
	GetDesktopWindow()->GetClientRect(rc);				//��ȡ��Ļ�Ŀͻ�����
	CDC  memDC;											//����һ���ڴ滭��
	memDC.CreateCompatibleDC(pDeskDC);					//����һ�����ݵĻ���
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDeskDC,rc.Width(),rc.Height());	//��������λͼ
	memDC.SelectObject(&bmp);							//ѡ��λͼ����	
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);
	
	if(m_Cursor.GetCheck())
	{
		CPoint point;
		GetCursorPos(&point);
		HICON hicon = (HICON)GetCursor();
		memDC.DrawIcon(point,hicon);
	}

	DWORD size=bitmap.bmWidthBytes*bitmap.bmHeight;
	LPSTR lpData=(LPSTR)GlobalAllocPtr(GPTR,size);
	int panelsize  = 0;									//��¼��ɫ���С
	if(bitmap.bmBitsPixel<16)							//�ж��Ƿ�Ϊ���ɫλͼ
		panelsize = pow(2,bitmap.bmBitsPixel*sizeof(RGBQUAD));
	BITMAPINFOHEADER *pBInfo = (BITMAPINFOHEADER*)LocalAlloc(LPTR,
		sizeof(BITMAPINFO)+panelsize);
	pBInfo->biBitCount       = bitmap.bmBitsPixel;
	pBInfo->biClrImportant   = 0;
	pBInfo->biCompression    = 0;
	pBInfo->biHeight         = bitmap.bmHeight;
	pBInfo->biPlanes         = bitmap.bmPlanes;
	pBInfo->biSize           = sizeof(BITMAPINFO);
	pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;
	pBInfo->biWidth          = bitmap.bmWidth;
	pBInfo->biXPelsPerMeter  = 0;
	pBInfo->biYPelsPerMeter  = 0;

	GetDIBits(memDC.m_hDC,bmp,0,pBInfo->biHeight,lpData,
		(BITMAPINFO*)pBInfo,DIB_RGB_COLORS);

	CString path,name,m_number;
	m_Path.GetWindowText(path);
	CTime time = CTime::GetCurrentTime();

	name = path+"\\"+time.Format("%Y%m%d%H%M%S")+".bmp";
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType      = ((WORD)('M'<< 8)|'B');
	bfh.bfSize      = 54+size;
	bfh.bfOffBits   = 54;
	CFile file;
	if(file.Open(name,CFile::modeCreate|CFile::modeWrite))
	{
		file.WriteHuge(&bfh,sizeof(BITMAPFILEHEADER));
		file.WriteHuge(pBInfo,sizeof(BITMAPINFOHEADER));
		file.WriteHuge(lpData,size);
		file.Close();
	}
}

void CKinescopeDlg::OnExit()
{
	CDialog::OnCancel();
}

BOOL CKinescopeDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID =pNMHDR->idFrom; //��ȡ��������ťID
    if(nID)
    {
		nID = m_ToolBar.CommandToIndex(nID); //����ID��ȡ��ť����
		if(nID != -1)
		{
			m_ToolBar.GetButtonText(nID,m_ToolText);				 //��ȡ�������ı�
			pTTT->lpszText = m_ToolText.GetBuffer(m_ToolText.GetLength()); //������ʾ��Ϣ�ı�
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
     }
     return(FALSE);
}


void CKinescopeDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_IsTime)
	{
		m_IsTime = FALSE;
		CDC* pDeskDC =  GetDesktopWindow()->GetDC();		//��ȡ���滭������
		CRect rc;
		GetDesktopWindow()->GetClientRect(rc);				//��ȡ��Ļ�Ŀͻ�����

		CDC  memDC;											//����һ���ڴ滭��
		memDC.CreateCompatibleDC(pDeskDC);					//����һ�����ݵĻ���
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDeskDC,rc.Width(),rc.Height());	//��������λͼ
		memDC.SelectObject(&bmp);							//ѡ��λͼ����	
		BITMAP bitmap;
		bmp.GetBitmap(&bitmap);
		memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);

		if(m_Cursor.GetCheck())
		{
			CPoint point;
			GetCursorPos(&point);
			HICON hicon = (HICON)GetCursor();
			memDC.DrawIcon(point,hicon);
		}

		DWORD size=bitmap.bmWidthBytes*bitmap.bmHeight;

		BYTE* lpData = new BYTE[size];

		int panelsize  = 0;									//��¼��ɫ���С
		if(bitmap.bmBitsPixel<16)							//�ж��Ƿ�Ϊ���ɫλͼ
			panelsize = pow(2,bitmap.bmBitsPixel*sizeof(RGBQUAD));

		BITMAPINFOHEADER *pBInfo = new BITMAPINFOHEADER;
		pBInfo->biBitCount       = bitmap.bmBitsPixel;
		pBInfo->biClrImportant   = 0;
		pBInfo->biCompression    = 0;
		pBInfo->biHeight         = bitmap.bmHeight;
		pBInfo->biPlanes         = bitmap.bmPlanes;
		pBInfo->biSize           = sizeof(BITMAPINFOHEADER);
		pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;
		pBInfo->biWidth          = bitmap.bmWidth;
		pBInfo->biXPelsPerMeter  = 0;
		pBInfo->biYPelsPerMeter  = 0;
		BITMAPINFO bInfo;
		bInfo.bmiHeader = *pBInfo;
		GetDIBits(memDC.m_hDC,bmp,0,pBInfo->biHeight,lpData,&bInfo,DIB_RGB_COLORS);

		if(nFrames == 0)
		{
			CString rate,name,path;
			m_Name.GetWindowText(name);
			m_Path.GetWindowText(path);
			if(path.Right(1) != "\\")
				path = path + "\\";
			m_Rate.GetWindowText(rate);
			AVIFileOpen(&pfile,path+name+".avi",OF_WRITE | OF_CREATE,NULL);
			memset(&strhdr, 0, sizeof(strhdr));
			strhdr.fccType    = streamtypeVIDEO;
			strhdr.fccHandler = 0;
			strhdr.dwScale    = 1;
			strhdr.dwRate     = atoi(rate);
			strhdr.dwSuggestedBufferSize = pBInfo->biSizeImage;
			SetRect(&strhdr.rcFrame,0,0,pBInfo->biWidth,pBInfo->biHeight);
			hr = AVIFileCreateStream(pfile,&ps,&strhdr); 

			opts[0]->fccType = streamtypeVIDEO;
			opts[0]->fccHandler = mmioStringToFOURCC("MSVC", 0);
			opts[0]->dwQuality = 7500;
			opts[0]->dwBytesPerSecond = 0;
			opts[0]->dwFlags = AVICOMPRESSF_VALID || AVICOMPRESSF_KEYFRAMES;
			opts[0]->lpFormat = 0;
			opts[0]->cbFormat = 0;
			opts[0]->dwInterleaveEvery = 0;

			AVIMakeCompressedStream(&pComStream,ps,&pCompressOption,NULL); 
			AVIStreamSetFormat(pComStream,0,pBInfo,sizeof(BITMAPINFOHEADER));
		}


		hr = AVIStreamWrite(pComStream,nFrames ,1,(LPBYTE)lpData,
			pBInfo->biSizeImage,AVIIF_KEYFRAME,NULL,NULL);
		nFrames++;
		
		delete []lpData;
		delete pBInfo ;	
		m_IsTime = TRUE;

	}
	CDialog::OnTimer(nIDEvent);
}

void CKinescopeDlg::OnButselect() 
{
	// TODO: Add your control notification handler code here
	CString ReturnPach;								//�ַ�������
	TCHAR szPath[_MAX_PATH];                       	//����·������
	BROWSEINFO bi;                                  	// BROWSEINFO�ṹ����
	bi.hwndOwner    = NULL;                          	//HWND���
	bi.pidlRoot       = NULL;                          	//Ĭ��ֵΪNULL
	bi.lpszTitle       = _T("�ļ�����Ի���");          	//�Ի������
	bi.pszDisplayName = szPath;                         //ѡ���ļ���·��
	bi.ulFlags        = BIF_RETURNONLYFSDIRS;       //���
	bi.lpfn           = NULL;                          	//Ĭ��ֵΪNULL
	bi.lParam         = NULL;                          	//�ص���Ϣ
	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);  	//��ʾ�ļ�����Ի���
	if(pItemIDList)
	{
		if(SHGetPathFromIDList(pItemIDList,szPath)) 		//�ж��Ƿ����ļ���·��
			ReturnPach = szPath;					//����ļ���·��
		m_IsPath = TRUE;
	}
	else
	{
		ReturnPach = ""; 							//�ļ���·��Ϊ��
	}
	m_Path.SetWindowText(ReturnPach);				//��ʾ�ļ���·��
	m_List.DeleteAllItems();
	GetResidualPlace();
	SetFileList();
}

void CKinescopeDlg::GetResidualPlace()
{
	ULARGE_INTEGER totalsize;
	ULARGE_INTEGER freesize;
	ULARGE_INTEGER availablesize;
	CString str,temp,path;
	m_Path.GetWindowText(path);
	str = path.Left(3);
	::GetDiskFreeSpaceEx(str,&totalsize,&freesize,&availablesize);
	temp.Format("%ldM",totalsize.QuadPart/1024/1024);
	m_Place.SetWindowText("ʣ��ռ䣺"+temp);
	if(totalsize.QuadPart/1024/1024 < 300)
	{
		MessageBox("ʣ��ռ䲻��300M�����������");
	}
}

void CKinescopeDlg::SetFileList()
{
	CString path;
	m_Path.GetWindowText(path);
	CFileFind file;
	if(path.Right(1) != "\\")
		path +="\\*.avi";
	else
		path +="*.avi";
	BOOL bf;
	bf = file.FindFile(path);
	int i=0;
	while(bf)
	{
		bf = file.FindNextFile();
		CString fileName;
		fileName = file.GetFileName();
		m_List.InsertItem(i,fileName.Left(fileName.GetLength()-4),0);
		i++;
	}
	SetFileName();
	CString str;
	str.Format("%d",i);
	m_StatusBar.SetPaneText(1,"��ǰ�ļ�����"+str);		//��������ı�
}

void CKinescopeDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int pos = m_List.GetSelectionMark();
	CPoint point;
	GetCursorPos(&point);
	CMenu* pPopup = m_Menu.GetSubMenu(0);
	CRect rc;
	rc.top = point.x;
	rc.left = point.y;
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		rc.top,rc.left,this,&rc);
	*pResult = 0;
}

void CKinescopeDlg::OnMenuplay() 
{
	// TODO: Add your command handler code here
	int pos = m_List.GetSelectionMark();
	CString name = m_List.GetItemText(pos,0);
	name += ".avi";
	CString path,oname;
	m_Path.GetWindowText(path);
	oname = path + "\\" + name;
	::ShellExecute(NULL,"open",oname,"","",SW_SHOW);//����AVI�ļ�
}

void CKinescopeDlg::OnMenuname() 
{
	// TODO: Add your command handler code here
	CNameDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		int pos = m_List.GetSelectionMark();
		CString name = m_List.GetItemText(pos,0);
		name += ".avi";
		CString path,oname,nname;
		m_Path.GetWindowText(path);
		oname = path + "\\" + name;
		nname = dlg.m_Name;
		path += ("\\" + nname + ".avi");
		rename(oname,path);
		m_List.DeleteAllItems();
		SetFileList();
	}
}

void CKinescopeDlg::OnMenusave() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"(*.avi)|*.avi| |",AfxGetMainWnd());
	CString strPath,strText="";
	if(dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if(strPath.Right(4) != ".avi")
			strPath += ".avi";
		int pos = m_List.GetSelectionMark();
		CString name = m_List.GetItemText(pos,0);
		name += ".avi";
		CString path,oname;
		m_Path.GetWindowText(path);
		oname = path + "\\" + name;
		if(CopyFile(oname,strPath,FALSE))
			MessageBox("�������");
	}
	
}

void CKinescopeDlg::OnMenudelete() 
{
	// TODO: Add your command handler code here
	int pos = m_List.GetSelectionMark();
	CString name = m_List.GetItemText(pos,0);
	name += ".avi";
	CString path,oname;
	m_Path.GetWindowText(path);
	if(path.Right(1) != "\\")
		path +="\\";
	oname = path + name;
	DeleteFile(oname);
	GetResidualPlace();
	m_List.DeleteAllItems();
	SetFileList();
}

void CKinescopeDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int pos = m_List.GetSelectionMark();
	CString name = m_List.GetItemText(pos,0);
	name += ".avi";
	CString path,oname;
	m_Path.GetWindowText(path);
	oname = path + "\\" + name;
	::ShellExecute(NULL,"open",oname,"","",SW_SHOW);//����AVI�ļ�
	*pResult = 0;
}

void CKinescopeDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	if(HOTKEY_START == (int)wParam)
	{
		OnStart();
	}
	if(HOTKEY_PAUSE == (int)wParam)
	{
		OnPause();
	}
	if(HOTKEY_GRASP == (int)wParam)
	{
		OnGrasp();
	}
}

BOOL CKinescopeDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	UnregisterHotKey(m_hWnd,HOTKEY_START);
	UnregisterHotKey(m_hWnd,HOTKEY_PAUSE);
	UnregisterHotKey(m_hWnd,HOTKEY_GRASP);
	return CDialog::DestroyWindow();
}

void CKinescopeDlg::OnMenutime() 
{
	// TODO: Add your command handler code here
	CString path,name,oname;
	int sum=0;
	m_Path.GetWindowText(path);
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	while(pos != NULL)
	{
		int nItem = m_List.GetNextSelectedItem(pos);
		name = m_List.GetItemText(nItem,0);
		name += ".avi";
		oname = path + "\\" + name;
		AVIFileInit();											//��ʼ��avi�ļ�
		AVIFileOpen(&pfile,oname,OF_READ, NULL);	//��Դ�ļ�
		AVIFILEINFO pfinfo;
		AVIFileInfo(pfile,&pfinfo,sizeof(AVIFILEINFO));
		sum += pfinfo.dwLength/(pfinfo.dwRate/pfinfo.dwScale);
		if(pfile != NULL)
			AVIFileRelease(pfile);
		AVIFileExit();
	}
	int min,sec;
	CString str;
	if(sum/60 > 0)
	{
		min = sum/60;
		sec = sum%60;
		str.Format("%d��%d��",min,sec);
	}
	else
		str.Format("%d��",sum);
	MessageBox(str);
}

void CKinescopeDlg::SetFileName()
{
	int count = m_List.GetItemCount();
	int flag=0;
	CString strName;
	int i=1;
	while(1)
	{
		strName.Format("¼��%d",i);
		for(int j=0;j<count;j++)
		{
			if(strName != m_List.GetItemText(j,0))
				flag++;
		}
		if(flag==count)
		{
			goto end;
		}
		i++;
		flag = 0;
	}
end:	strName.Format("¼��%d",i);
	m_Name.SetWindowText(strName);
}

void CKinescopeDlg::CreateTray(int state)
{
	//���ϵͳ����
	char lpszTip[256];
	strcpy(lpszTip,"��Ļ¼��");
	NOTIFYICONDATA data;
	data.cbSize = sizeof(NOTIFYICONDATA);
	data.hWnd   = m_hWnd;
	lstrcpyn(data.szTip,lpszTip,sizeof(lpszTip));
	data.uCallbackMessage = WM_ONTRAY;
	data.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	data.uID              = IDR_MAINFRAME;	
	if(state == 1)
	{
		if(m_Once)
		{
			data.hIcon = m_Icon1;	
			Shell_NotifyIcon(NIM_ADD,&data);
			m_Once = FALSE;
		}
		else
		{
			data.hIcon = m_Icon1;	
			Shell_NotifyIcon(NIM_MODIFY,&data);
		}
	}
	else if(state == 2)
	{
		data.hIcon = m_Icon2;	
		Shell_NotifyIcon(NIM_MODIFY,&data);
	}
	else if(state == 3)
	{
		data.hIcon = m_Icon3;	
		Shell_NotifyIcon(NIM_MODIFY,&data);
	}
}

void CKinescopeDlg::OnTray(WPARAM wParam, LPARAM lParam)
{
	if(lParam == WM_LBUTTONDBLCLK)     //˫�����
	{
		ShowWindow(SW_RESTORE);    //�ָ����ڵ���ʾ
	}
}

void CKinescopeDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//ɾ��ϵͳ����
	NOTIFYICONDATA data;
	data.cbSize = sizeof(NOTIFYICONDATA);
	data.hWnd   = m_hWnd;
	data.hIcon  = m_Icon1;
	Shell_NotifyIcon(NIM_DELETE,&data);
	CDialog::OnClose();
}

void CKinescopeDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString rate;
	m_Rate.GetWindowText(rate);
	if(atoi(rate)<1 || atoi(rate)>10)
	{
		MessageBox("������һ��1��5֮�������");
		m_Rate.SetWindowText("3");
	}
}

void CKinescopeDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CRect bmprect;
	m_Picture.GetClientRect(&bmprect);
	m_Picture.MoveWindow(0,0,bmprect.Width(),bmprect.Height());


	int pos = m_List.GetSelectionMark();
	CString name = m_List.GetItemText(pos,0);
	name += ".avi";
	CString path,oname;
	m_Path.GetWindowText(path);
	oname = path + "\\" + name;
	AVIFileInit();											//��ʼ��AVIFile������
	HRESULT hRet;										//����������
	hRet =  AVIFileOpen(&pfile,oname,OF_READ, NULL);	//��Դ�ļ�
	if (hRet != 0)											//�ж��ļ��Ƿ�򿪳ɹ�
	{
		MessageBox("��Դ�ļ�����","��ʾ");					//����������ʾ
		return;
	}
	AVIFILEINFO pfinfo;
	AVIFileInfo(pfile,&pfinfo,sizeof(AVIFILEINFO)); 
	AVIFileGetStream(pfile, &ps, streamtypeVIDEO, 0 );	//��ȡ��Ƶ��
	long StartFrame = AVIStreamStart(ps);					//��ȡ������ʼ֡
	m_FrameNum   = AVIStreamLength(ps);				//��ȡ����֡����

	//��ȡ����Ϣ
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(ps,&streaminfo,sizeof(AVISTREAMINFO));
	PGETFRAME pFrame;									//����֡�ӿڶ���
	pFrame=AVIStreamGetFrameOpen(ps,NULL);			//�����д�֡
	LPBITMAPINFOHEADER bih;
	bih = (LPBITMAPINFOHEADER) AVIStreamGetFrame(pFrame, StartFrame); 

	BITMAPINFO Header;
	memset(&Header,0,sizeof(BITMAPINFOHEADER));  
	Header.bmiHeader.biBitCount=bih->biBitCount ;  
	Header.bmiHeader.biSize  =  sizeof(BITMAPINFOHEADER);  
 	Header.bmiHeader.biWidth  =  pfinfo.dwWidth;  
	Header.bmiHeader.biHeight  =  pfinfo.dwHeight;  
	Header.bmiHeader.biPlanes  =bih->biPlanes; 
	Header.bmiHeader.biCompression  =BI_RGB;  
	Header.bmiHeader.biXPelsPerMeter  =  0;  
	Header.bmiHeader.biYPelsPerMeter  =  0;
	
	BITMAPFILEHEADER stFileHdr;
	stFileHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	stFileHdr.bfSize=sizeof(BITMAPFILEHEADER);
	stFileHdr.bfType= ((WORD)('M'<< 8)|'B');

	BYTE* pDIB=new BYTE[(((pfinfo.dwWidth*Header.bmiHeader.biBitCount)+31)/8)*pfinfo.dwHeight];
	BYTE* lpbuff; 
	lpbuff=pDIB;  
	lpbuff=(BYTE *)AVIStreamGetFrame(pFrame,StartFrame); 
	lpbuff+=40;  

	CClientDC dc(this);  //����һ���뵱ǰ������ص�CClientDC
	HBITMAP m_hBitmap;
	//����DIBitmap����
	m_hBitmap = CreateDIBitmap(dc.m_hDC,&Header.bmiHeader,CBM_INIT,lpbuff,&Header,DIB_RGB_COLORS);
	delete[] pDIB;

	AVIStreamGetFrameClose(pFrame);
	if (m_hBitmap != NULL)
	{
		m_Picture.SetBitmap(m_hBitmap);
		m_Picture.UpdateData();
	}	
	BITMAP bmp;
	GetObject(m_hBitmap,sizeof(bmp),&bmp);
	CRect rect;
	m_fDlg->GetClientRect(rect);	
	int xpos = m_fDlg->GetScrollPos(SB_HORZ);
	if (xpos != 0)
		m_fDlg->ScrollWindow(xpos,0); //�ָ����ڵ�ˮƽ��������
	int ypos = m_fDlg->GetScrollPos(SB_VERT);
	if (ypos != 0)
		m_fDlg->ScrollWindow(0,ypos); //�ָ����ڵĴ�ֱ��������
	
	SCROLLINFO vinfo;	
	vinfo.cbSize = sizeof(vinfo);
	vinfo.fMask = SIF_ALL;
	vinfo.nPage = bmp.bmHeight/10;
	vinfo.nMax= bmp.bmHeight-rect.Height()+bmp.bmHeight/10;
	vinfo.nMin = 0;
	vinfo.nTrackPos = 0;
	vinfo.nPos = 0;	
	//���ô�ֱ��������Ϣ
	m_fDlg->SetScrollInfo(SB_VERT,&vinfo);

	vinfo.fMask = SIF_ALL;
	vinfo.nPage = bmp.bmWidth/10;
	vinfo.nMax= bmp.bmWidth-rect.Width()+bmp.bmWidth/10;
	vinfo.nMin = 0;
	vinfo.nPos  = 0;
	vinfo.nTrackPos = 0;
	vinfo.cbSize = sizeof(vinfo);
	//����ˮƽ��������Ϣ
	m_fDlg->SetScrollInfo(SB_HORZ,&vinfo);


	CFileStatus status;
	CFile::GetStatus(oname,status);
	CString str;
	str.Format("��֡����%d,�ٶȣ�%d֡/��,ʱ�䣺%d��,��ȣ�%d,�߶ȣ�%d,�ļ���С��%dK,¼��ʱ�䣺%s",
		pfinfo.dwLength,pfinfo.dwRate/pfinfo.dwScale,pfinfo.dwLength/(pfinfo.dwRate/pfinfo.dwScale),
		pfinfo.dwWidth,pfinfo.dwHeight,status.m_size/1024,status.m_ctime.Format("%Y��%m��%d�� %H:%M:%S"));
	m_StatusBar.SetPaneText(0,str);					//��������ı�
	AVIStreamClose(ps);
	if(pfile != NULL)
		AVIFileRelease(pfile);
	AVIFileExit();
	*pResult = 0;
}
