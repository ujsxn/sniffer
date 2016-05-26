
// zhuabao.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "zhuabao.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CzhuabaoApp

BEGIN_MESSAGE_MAP(CzhuabaoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CzhuabaoApp::OnAppAbout)
END_MESSAGE_MAP()


// CzhuabaoApp 构造

CzhuabaoApp::CzhuabaoApp()
{
	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("zhuabao.ujsxn.1"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CzhuabaoApp 对象

CzhuabaoApp theApp;


// CzhuabaoApp 初始化

BOOL CzhuabaoApp::InitInstance()
{
	CWinApp::InitInstance();

	adhandle = NULL;

	m_run = false;

	m_listcount = 0;

	char buf[1024];
	GetCurrentDirectory(sizeof(buf), buf);
	m_tempDumpFilePath.Format("%s\\tmp.pcap", buf);

	m_ipcount = 0;
	m_arpcount = 0;
	m_rarapcount = 0;

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();


	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE , NULL,
		NULL);


	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CzhuabaoApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源

	m_run = false;
	// 应该等线程结束
	::WaitForSingleObject(loopthread->m_hThread, 10000);

	// 数据列表里的东西都应该delete掉
	for (int i = 0; i < m_listcount; i++)
	{
		delete m_packetlist[i];
	}

	return CWinApp::ExitInstance();
}

// CzhuabaoApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CzhuabaoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CzhuabaoApp 消息处理程序



