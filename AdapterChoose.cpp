// AdapterChoose.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuabao.h"
#include "AdapterChoose.h"
#include "afxdialogex.h"


// CAdapterChoose 对话框

IMPLEMENT_DYNAMIC(CAdapterChoose, CDialogEx)

CAdapterChoose::CAdapterChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADAPTER, pParent)
{

}

CAdapterChoose::~CAdapterChoose()
{
}

void CAdapterChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADAPTERLIST, m_adapterlist);
}


BEGIN_MESSAGE_MAP(CAdapterChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdapterChoose::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdapterChoose 消息处理程序


BOOL CAdapterChoose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//1 先获取网卡列表

	char errbuf[PCAP_ERRBUF_SIZE + 1];
	pcap_if_t *d;


	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{

		AfxTrace("Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	//2 添加到listbox中
	for (d = alldevs; d; d = d->next)
	{
		CString s(d->name);
		s += CString(d->description);
		m_adapterlist.AddString(s);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CAdapterChoose::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int i, inum;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *d;
	

	inum = m_adapterlist.GetCurSel();
	// 当前选定的项的从零开始的索引，如果项目当前未选择，它是 LB_ERR(-1)
	// 如果没有选择网卡则选定的是第一个网卡

	// 得到选择的网卡
	for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);
	
	// 设置netmask
	if (d->addresses != NULL)
		theApp.netmask = ((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		theApp.netmask = 0xffffff;

	// 启动该网卡
	if ((theApp.adhandle = pcap_open_live(d->name,	// 设备名称
		65536,			// 设置捕获分段大小
						// 65536 保证最大的分段也可以捕获到
		0,				// 混杂模式
		1000,			// 超时时间
		errbuf			
	)) == NULL)
	{
		AfxTrace("Unable to open the adapter.");
		pcap_freealldevs(alldevs);
		exit(1);
	}

	pcap_freealldevs(alldevs);

	CDialogEx::OnOK();
}
