#include "stdafx.h"
#include "Kinescope.h"
#include "CoalitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoalitionDlg dialog


CCoalitionDlg::CCoalitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoalitionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoalitionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCoalitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoalitionDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoalitionDlg, CDialog)
	//{{AFX_MSG_MAP(CCoalitionDlg)
	ON_BN_CLICKED(IDC_BUTADD, OnButadd)
	ON_BN_CLICKED(IDC_BUTCOALITION, OnButcoalition)
	ON_BN_CLICKED(IDC_BUTDEL, OnButdel)
	ON_BN_CLICKED(IDC_BUTCLEAR, OnButclear)
	ON_BN_CLICKED(IDC_BUTUP, OnButup)
	ON_BN_CLICKED(IDC_BUTDOWN, OnButdown)
	ON_BN_CLICKED(IDC_BUTEXIT, OnButexit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoalitionDlg message handlers

void CCoalitionDlg::OnButadd() 
{
	// TODO: Add your control notification handler code here
	if(m_List.GetCount()==10)
	{
		MessageBox("一次只能合成10个文件");
		return;
	}
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"(*.avi)|*.avi| |",AfxGetMainWnd());
	CString strPath;
	if(dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if(strPath.Right(4) != ".avi")
			strPath += ".avi";
	}
	m_List.InsertString(m_List.GetCount(),strPath);
}

void CCoalitionDlg::OnButcoalition() 
{
	// TODO: Add your control notification handler code here
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
	PAVISTREAM pstream[20]; 
	PAVISTREAM pComStream;
	AVISTREAMINFO strhdr;
	PAVIFILE pfile[20];
	HRESULT hr; 
	int m_Start=0,m_Stop=0;
	PAVIFILE pfileto;
	AVICOMPRESSOPTIONS pCompressOption;   
	AVICOMPRESSOPTIONS FAR * opts[1] = {&pCompressOption};  
	int nFrames = 0;
	AVIFileInit();											//初始化AVIFile函数库
	CString m_Name;
	m_List.GetText(0,m_Name);
	AVIFileOpen(&pfile[0],m_Name,OF_READ, NULL);	//打开源文件
	AVIFILEINFO pfinfo;
	AVIFileInfo(pfile[0],&pfinfo,sizeof(AVIFILEINFO)); 
	AVIFileGetStream(pfile[0], &pstream[0], streamtypeVIDEO, 0 );	//获取视频流
	//获取流信息
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(pstream[0],&streaminfo,sizeof(AVISTREAMINFO));
	PGETFRAME pFrame;									//定义帧接口对象
	pFrame=AVIStreamGetFrameOpen(pstream[0],NULL);			//在流中打开帧
	m_Start = AVIStreamStart(pstream[0]);					//获取流的起始帧
	m_Stop = AVIStreamLength(pstream[0]);				//获取流的帧长度
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


	AVIFileOpen(&pfileto,strPath,OF_WRITE | OF_CREATE,NULL);
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
	if(hr!=AVIERR_OK)
			{
				MessageBox("1");
				return;
			}
	for(int n=0;n<m_List.GetCount();n++)
	{
		if(n!=0)
		{
			m_List.GetText(n,m_Name);
			AVIFileOpen(&pfile[n],m_Name,OF_READ, NULL);	//打开源文件
			AVIFileInfo(pfile[n],&pfinfo,sizeof(AVIFILEINFO)); 
			AVIFileGetStream(pfile[n], &pstream[n], streamtypeVIDEO, 0 );	//获取视频流
			//获取流信息
			AVIStreamInfo(pstream[n],&streaminfo,sizeof(AVISTREAMINFO));
			pFrame=AVIStreamGetFrameOpen(pstream[n],NULL);			//在流中打开帧
			m_Start = AVIStreamStart(pstream[n]);					//获取流的起始帧
			m_Stop = AVIStreamLength(pstream[n]);				//获取流的帧长度
		}
		for(int i=m_Start;i<m_Stop;i++)
		{
			BYTE* pDIB=new BYTE[(((pfinfo.dwWidth*Header.bmiHeader.biBitCount)+31)/8)*pfinfo.dwHeight];
			BYTE* lpbuff; 
			lpbuff=pDIB;  
			lpbuff=(BYTE *)AVIStreamGetFrame(pFrame,i); 
			lpbuff+=40;

			hr = AVIStreamWrite(pComStream,nFrames ,1,(LPBYTE)lpbuff,
				(((pfinfo.dwWidth*Header.bmiHeader.biBitCount)+31)/8)*pfinfo.dwHeight
				,AVIIF_KEYFRAME,NULL,NULL);
			if(hr!=AVIERR_OK)
			{
				MessageBox("");
				return;
			}
			nFrames++;
			delete[] pDIB;
		}
		AVIStreamGetFrameClose(pFrame);
		AVIStreamClose(pstream[n]);
		if(pfile[0] != NULL)
			AVIFileRelease(pfile[n]);
	}
	
	AVIStreamClose(pComStream);
	AVIStreamClose(ps);
	if(pfileto != NULL)
		AVIFileRelease(pfileto);
	AVIFileExit();
	MessageBox("完成合成！");
}

void CCoalitionDlg::OnButdel() 
{
	// TODO: Add your control notification handler code here
	int pos = m_List.GetCurSel();
	if(pos < 0)
	{
		MessageBox("请选择要去除的文件！");
		return;
	}
	m_List.DeleteString(pos);
}

void CCoalitionDlg::OnButclear() 
{
	// TODO: Add your control notification handler code here
	m_List.ResetContent();
}

void CCoalitionDlg::OnButup() 
{
	// TODO: Add your control notification handler code here
	int pos = m_List.GetCurSel();
	if(pos < 0)
	{
		MessageBox("请选择要去除的文件！");
		return;
	}
	if(pos == 0)
	{
		MessageBox("已经是最上边了！");
		return;
	}
	CString text;
	m_List.GetText(pos-1,text);
	m_List.DeleteString(pos-1);
	m_List.InsertString(pos,text);
}

void CCoalitionDlg::OnButdown() 
{
	// TODO: Add your control notification handler code here
	int pos = m_List.GetCurSel();
	if(pos < 0)
	{
		MessageBox("请选择要去除的文件！");
		return;
	}
	if(pos == m_List.GetCount()-1)
	{
		MessageBox("已经是最下边了！");
		return;
	}
	CString text;
	m_List.GetText(pos+1,text);
	m_List.DeleteString(pos+1);
	m_List.InsertString(pos,text);
}

void CCoalitionDlg::OnButexit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
