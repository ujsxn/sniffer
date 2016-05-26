
// zhuabao.cpp : ����Ӧ�ó��������Ϊ��
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


// CzhuabaoApp ����

CzhuabaoApp::CzhuabaoApp()
{
	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("zhuabao.ujsxn.1"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CzhuabaoApp ����

CzhuabaoApp theApp;


// CzhuabaoApp ��ʼ��

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

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();


	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE , NULL,
		NULL);


	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CzhuabaoApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ

	m_run = false;
	// Ӧ�õ��߳̽���
	::WaitForSingleObject(loopthread->m_hThread, 10000);

	// �����б���Ķ�����Ӧ��delete��
	for (int i = 0; i < m_listcount; i++)
	{
		delete m_packetlist[i];
	}

	return CWinApp::ExitInstance();
}

// CzhuabaoApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CzhuabaoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CzhuabaoApp ��Ϣ�������



