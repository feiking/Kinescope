#include "stdafx.h"
#include "Kinescope.h"
#include "CutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CCutDlg dialog

CCutDlg::CCutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCutDlg)
	m_Rate = 0;
	//}}AFX_DATA_INIT
}


void CCutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCutDlg)
	DDX_Control(pDX, IDC_STATICFRAME, m_Frame);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT1, m_Rate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCutDlg, CDialog)
	//{{AFX_MSG_MAP(CCutDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTPREVIOUS, OnButprevious)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTNEXT, OnButnext)
	ON_BN_CLICKED(IDC_BUTSTART, OnButstart)
	ON_BN_CLICKED(IDC_BUTSTOP, OnButstop)
	ON_BN_CLICKED(IDC_BUTGOTO, OnButgoto)
	ON_BN_CLICKED(IDC_BUTCUT, OnButcut)
	ON_BN_CLICKED(IDC_BUTEXIT, OnButexit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCutDlg message handlers

void CCutDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnSysCommand(nID, lParam);
	if(nID == SC_MAXIMIZE)
	{
		SetControlRect();
		CreateFrameDialog();
	}
	if(nID == SC_RESTORE)
	{
		SetControlRect();
		CreateFrameDialog();
	}
}

void CCutDlg::SetControlRect()
{
	CRect rect,rc;
	GetClientRect(rect);
	GetDlgItem(IDC_BUTGOTO)->GetClientRect(rc);
	GetDlgItem(IDC_STATICFRAME)->MoveWindow(0,0,rect.Width(),rect.Height()-50);
	GetDlgItem(IDC_STATICRATE)->MoveWindow(10,rect.bottom-30,100,20);
	GetDlgItem(IDC_EDIT1)->MoveWindow(120,rect.bottom-32,40,17);
	GetDlgItem(IDC_BUTGOTO)->MoveWindow(170,rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTPREVIOUS)->MoveWindow(190+rc.Width(),rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTNEXT)->MoveWindow(200+rc.Width()*2,rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTSTART)->MoveWindow(210+rc.Width()*3,rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTSTOP)->MoveWindow(220+rc.Width()*4,rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTCUT)->MoveWindow(230+rc.Width()*5,rect.bottom-33,rc.Width(),rc.Height());
	GetDlgItem(IDC_BUTEXIT)->MoveWindow(240+rc.Width()*6,rect.bottom-33,rc.Width(),rc.Height());
}

BOOL CCutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CreateFrameDialog();
	SetControlRect();
	ShowBmp();
	CString rate;
	rate.Format("总帧数：%d",m_FrameNum);
	GetDlgItem(IDC_STATICRATE)->SetWindowText(rate);
	m_Rate = 1;
	m_Start = 0;
	m_Stop = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCutDlg::ShowBmp(int frame)
{
	CRect bmprect;
	m_Picture.GetClientRect(&bmprect);
	m_Picture.MoveWindow(0,0,bmprect.Width(),bmprect.Height());

	PAVISTREAM ps; 
	PAVIFILE pfile;
	AVIFileInit();											//初始化AVIFile函数库
	HRESULT hRet;										//定义结果变量
	hRet =  AVIFileOpen(&pfile,m_Name,OF_READ, NULL);	//打开源文件
	if (hRet != 0)											//判断文件是否打开成功
	{
		MessageBox("打开源文件错误","提示");					//弹出错误提示
		return;
	}
	
	AVIFILEINFO pfinfo;
	AVIFileInfo(pfile,&pfinfo,sizeof(AVIFILEINFO)); 
	AVIFileGetStream(pfile, &ps, streamtypeVIDEO, 0 );	//获取视频流
	//获取流信息
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(ps,&streaminfo,sizeof(AVISTREAMINFO));
	PGETFRAME pFrame;									//定义帧接口对象
	pFrame=AVIStreamGetFrameOpen(ps,NULL);			//在流中打开帧
	LPBITMAPINFOHEADER bih;
	bih = (LPBITMAPINFOHEADER) AVIStreamGetFrame(pFrame, frame); 

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
	lpbuff=(BYTE *)AVIStreamGetFrame(pFrame,frame); 
	lpbuff+=40;  

	CClientDC dc(this);  //生成一个与当前窗口相关的CClientDC
	HBITMAP m_hBitmap;
	//生成DIBitmap数据
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
		m_fDlg->ScrollWindow(xpos,0); //恢复窗口的水平滚动区域
	int ypos = m_fDlg->GetScrollPos(SB_VERT);
	if (ypos != 0)
		m_fDlg->ScrollWindow(0,ypos); //恢复窗口的垂直滚动区域
	
	SCROLLINFO vinfo;	
	vinfo.cbSize = sizeof(vinfo);
	vinfo.fMask = SIF_ALL;
	vinfo.nPage = bmp.bmHeight/10;
	vinfo.nMax= bmp.bmHeight-rect.Height()+bmp.bmHeight/10;
	vinfo.nMin = 0;
	vinfo.nTrackPos = 0;
	vinfo.nPos = 0;	
	//设置垂直滚动条信息
	m_fDlg->SetScrollInfo(SB_VERT,&vinfo);

	vinfo.fMask = SIF_ALL;
	vinfo.nPage = bmp.bmWidth/10;
	vinfo.nMax= bmp.bmWidth-rect.Width()+bmp.bmWidth/10;
	vinfo.nMin = 0;
	vinfo.nPos  = 0;
	vinfo.nTrackPos = 0;
	vinfo.cbSize = sizeof(vinfo);
	//设置水平滚动条信息
	m_fDlg->SetScrollInfo(SB_HORZ,&vinfo);
	if(pfile != NULL)
		AVIFileRelease(pfile);
	AVIFileExit();
}

void CCutDlg::CreateFrameDialog()
{
	CRect fRect;
	m_Frame.GetClientRect(&fRect);							//获得子窗体显示区域
	m_Frame.MapWindowPoints(this,fRect);
	m_fDlg = new CFrameDlg;
	m_fDlg->Create(IDD_FRAME_DIALOG,this); 		//创建非模态对话框
	m_fDlg->MoveWindow(fRect);						//移动对话框位置
	m_fDlg->ShowWindow(SW_SHOW);					//显示对话框
	m_Picture.SetParent(m_fDlg);
}

void CCutDlg::OnButprevious() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Rate == 1)
	{
		MessageBox("已经是第一帧了");
		return;
	}
	m_Rate--;
	ShowBmp(m_Rate);
	UpdateData(FALSE);
}

void CCutDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Rate > m_FrameNum)
	{
		MessageBox("不能大于总帧数");
		m_Rate = 1;
		UpdateData(FALSE);
	}
}

void CCutDlg::OnButnext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Rate == m_FrameNum)
	{
		MessageBox("已经是最后一帧了");
		return;
	}
	m_Rate++;
	ShowBmp(m_Rate);
	UpdateData(FALSE);
}


void CCutDlg::OnButstart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Start = m_Rate;
	MessageBox("定义头");
}

void CCutDlg::OnButstop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Stop = m_Rate;
	MessageBox("定义尾");
}

void CCutDlg::OnButgoto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ShowBmp(m_Rate);
}

void CCutDlg::OnButcut() 
{
	// TODO: Add your control notification handler code here
	if(m_Start == 0)
	{
		MessageBox("没有定义文件头");
		return;
	}
	if(m_Stop == 0)
	{
		MessageBox("没有定义文件尾");
		return;
	}
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"(*.avi)|*.avi| |",AfxGetMainWnd());
	CString strPath,strText="";
	if(dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if(strPath.Right(4) != ".avi")
			strPath += ".avi";
	}
	PAVISTREAM ps; 
	PAVISTREAM pComStream;
	AVISTREAMINFO strhdr;
	PAVIFILE pfile;
	HRESULT hr; 

	PAVIFILE pfileto;
	AVICOMPRESSOPTIONS pCompressOption;   
	AVICOMPRESSOPTIONS FAR * opts[1] = {&pCompressOption};  
	int nFrames = 0;
	AVIFileInit();											//初始化AVIFile函数库
	AVIFileOpen(&pfile,m_Name,OF_READ, NULL);	//打开源文件
	AVIFILEINFO pfinfo;
	AVIFileInfo(pfile,&pfinfo,sizeof(AVIFILEINFO)); 
	AVIFileGetStream(pfile, &ps, streamtypeVIDEO, 0 );	//获取视频流
	//获取流信息
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(ps,&streaminfo,sizeof(AVISTREAMINFO));
	PGETFRAME pFrame;									//定义帧接口对象
	pFrame=AVIStreamGetFrameOpen(ps,NULL);			//在流中打开帧
	LPBITMAPINFOHEADER bih;
	bih = (LPBITMAPINFOHEADER) AVIStreamGetFrame(pFrame, 0); 
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


	AVIFileOpen(&pfileto,strPath,OF_WRITE | OF_CREATE,NULL);//"C:\\ab.avi"
	memset(&strhdr, 0, sizeof(strhdr));
	strhdr.fccType    = streamtypeVIDEO;
	strhdr.fccHandler = 0;
	strhdr.dwScale    = 1;
	strhdr.dwRate     = (int)pfinfo.dwRate/pfinfo.dwScale;
	strhdr.dwSuggestedBufferSize = Header.bmiHeader.biSizeImage;
	SetRect(&strhdr.rcFrame,0,0,Header.bmiHeader.biWidth,Header.bmiHeader.biHeight);
	AVIFileCreateStream(pfileto,&ps,&strhdr); 

	opts[0]->fccType = streamtypeVIDEO;
	opts[0]->fccHandler = mmioStringToFOURCC("MSVC", 0);
	opts[0]->dwQuality = 7500;
	opts[0]->dwBytesPerSecond = 0;
	opts[0]->dwFlags = AVICOMPRESSF_VALID || AVICOMPRESSF_KEYFRAMES;
	opts[0]->lpFormat = 0;
	opts[0]->cbFormat = 0;
	opts[0]->dwInterleaveEvery = 0;

	AVIMakeCompressedStream(&pComStream,ps,&pCompressOption,NULL); 
	hr = AVIStreamSetFormat(pComStream,0,&Header.bmiHeader,sizeof(BITMAPINFOHEADER));
	for(int i=m_Start-1;i<m_Stop-1;i++)
	{
		BYTE* pDIB=new BYTE[(((pfinfo.dwWidth*Header.bmiHeader.biBitCount)+31)/8)*pfinfo.dwHeight];
		BYTE* lpbuff; 
		lpbuff=pDIB;  
		lpbuff=(BYTE *)AVIStreamGetFrame(pFrame,i); 
		lpbuff+=40;

		hr = AVIStreamWrite(pComStream,nFrames ,1,(LPBYTE)lpbuff,
			(((pfinfo.dwWidth*Header.bmiHeader.biBitCount)+31)/8)*pfinfo.dwHeight
			,AVIIF_KEYFRAME,NULL,NULL);
		nFrames++;
		delete[] pDIB;
	}
	AVIStreamGetFrameClose(pFrame);
	AVIStreamClose(pComStream);
	AVIStreamClose(ps);
	if(pfile != NULL)
		AVIFileRelease(pfile);
	if(pfileto != NULL)
		AVIFileRelease(pfileto);
	AVIFileExit();
	m_Start = 0;
	m_Stop = 0;
	MessageBox("完成截取！");
}

void CCutDlg::OnButexit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
