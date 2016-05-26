
// MainFrm.cpp : CMainFrame 类的实现
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"

#include "zhuabao.h"
#include "MainFrm.h"


#include "AdapterChoose.h"
#include "PROTOSET.h"
#include "ManualSet.h"
#include "Hub.h"
#include "PacketSend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

// 抓包线程
UINT startloop(LPVOID param)
{

	pcap_pkthdr header;
	const u_char *pkt_data_old = (u_char *)"old data";
	const u_char *pkt_data;
	u_char *save_data;

	struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;

	// 抓取到的数据包是这样的：
	// 这一次的数据包在调用next之后就没了（可能）应该是按静态存放的
	// 所以这边开堆区另外存放数据包以永久保存

	while (theApp.m_run)
	{
		pkt_data = pcap_next(theApp.adhandle, &header);

		if (pkt_data == NULL)
			/* 超时或错误 */
			continue;

		// 这边获取到的数据包内容可能就不变
		// 可能winpcap 的这个函数有问题
		if (memcmp(pkt_data, pkt_data_old, sizeof(pkt_data) == 0))
		{
			AfxOutputDebugString("same\n");
			continue;
		}
		pkt_data_old = pkt_data;

		local_tv_sec = header.ts.tv_sec;	// 秒
		ltime = localtime(&local_tv_sec);	// 转换为本地时间
		strftime(timestr, sizeof timestr, "%H:%M:%S", ltime); //设置时间格式
		

		// 把数据包放入列表
		// 下面开堆 保存到堆区里面
		save_data = new u_char[header.len];
		memcpy(save_data, pkt_data, header.len);

		// 保存到zhuabao中的列表
		theApp.m_packetlist.Add(save_data);
		theApp.m_packettime.Add(timestr);
		theApp.m_packetheader.Add(header);
		
		// 保存到文件中
		pcap_dump((u_char *)theApp.dumpfile, &header, pkt_data);

		// 发消息来更新显示
		PostMessage(*theApp.m_pMainWnd, WM_GETDATA, NULL, NULL);
	}

	// 关闭pcap
	pcap_close(theApp.adhandle);

	return 111;

}

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_START, &CMainFrame::OnStart)
	ON_COMMAND(ID_END, &CMainFrame::OnEnd)
	ON_MESSAGE(WM_GETDATA, &CMainFrame::OnGetData)
	ON_COMMAND(ID_PROTO, &CMainFrame::OnProto)
	ON_COMMAND(ID_SAVE, &CMainFrame::OnSave)
	ON_COMMAND(ID_SHOW, &CMainFrame::OnShow)
	ON_COMMAND(ID_MANUAL, &CMainFrame::OnManual)
	ON_COMMAND(ID_SEND, &CMainFrame::OnSend)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	// 默认窗口时wsoverlappedwindow 包括
	cs.style = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnStart()
{
	// 用户点击了启动菜单按钮：应该弹出对话框让用户选择网卡
	CAdapterChoose d;
	if (d.DoModal() == IDOK)
	{
		struct bpf_program fcode;

		// 先设置过滤条件再启动
		if (theApp.m_filterset)
		{
			//compile the filter
			if (pcap_compile(theApp.adhandle, &fcode, theApp.filter.GetBuffer(), 1, theApp.netmask) < 0)
			{
				AfxMessageBox("编译过滤条件失败！");
			}

			//set the filter
			if (pcap_setfilter(theApp.adhandle, &fcode) < 0)
			{
				AfxMessageBox("设置过滤条件失败！");
			}

		}

		theApp.dumpfile = pcap_dump_open(theApp.adhandle, theApp.m_tempDumpFilePath);
		theApp.m_run = true;
		theApp.loopthread = AfxBeginThread(startloop, "1");

		CMenu *mmenu = GetMenu();
		// 不能使菜单失效 只得删除了菜单项
		//mmenu->EnableMenuItem(ID_START,  MF_DISABLED | MF_GRAYED);
		mmenu->DeleteMenu(ID_START, MF_BYCOMMAND);

	}

}

afx_msg LRESULT CMainFrame::OnGetData(WPARAM wParam, LPARAM lParam)
{
	
	CString time = theApp.m_packettime.GetAt(theApp.m_listcount);
	u_char *data = theApp.m_packetlist.GetAt(theApp.m_listcount);
	
	CString s(time);

	mac_header mac;
	memcpy(&mac, data, sizeof(mac_header));
	switch (ntohs(mac.m_cType))
	{
	case 0x0800:
		ip_header ip;
		memcpy(&ip, data + 14, sizeof(ip_header));
		s += " IP ";
		// 注意inet_ntoa直接接收网络字节端　别转换

		// 显示IP地址
		in_addr ipadd;
		ipadd.S_un.S_addr = (ip.saddr);
		s += inet_ntoa(ipadd);
		s += "->";
		ipadd.S_un.S_addr = (ip.daddr);
		s += inet_ntoa(ipadd);

		// 计数器
		theApp.m_ipcount++;
		break;
	case 0x0806:
		arp_header arp;
		memcpy(&arp, data + 14, sizeof(arp_header));

		short type;
		type = ntohs(arp.arp_op);
		if (type == 1)
		{
			s += " ARP 请求包";
		}
		else if (type == 2)
		{
			s += " ARP 应答包";
		}

		// 计数器
		theApp.m_arpcount++;
		break;
	case 0x8035:
		arp_header rarp;
		memcpy(&rarp, data + 14, sizeof(arp_header));

		short rtype;
		rtype = ntohs(rarp.arp_op);
		if (rtype == 1)
		{
			s += " RARP 请求包";
		}
		else if (rtype == 2)
		{
			s += " RARP 应答包";
		}

		// 计数器
		theApp.m_rarapcount++;
		break;
	default:
		s += " 未知协议: ";
		char macstrsrc[100];
		char macstrdst[100];

		sprintf(macstrsrc, "%02x-%02x-%02x-%02x-%02x-%02x",
			mac.m_cSrcMacAddress[0], mac.m_cSrcMacAddress[1], mac.m_cSrcMacAddress[2], mac.m_cSrcMacAddress[3], mac.m_cSrcMacAddress[4], mac.m_cSrcMacAddress[5]);
		s += macstrsrc;
		s += "->";
		sprintf(macstrdst, "%02x-%02x-%02x-%02x-%02x-%02x",
			mac.m_cDstMacAddress[0], mac.m_cDstMacAddress[1], mac.m_cDstMacAddress[2], mac.m_cDstMacAddress[3], mac.m_cDstMacAddress[4], mac.m_cDstMacAddress[5]);
		s += macstrdst;
		break;
	}

	m_wndView.m_messagelist.InsertString(0, s);
	m_wndView.m_messagelist.SetItemData(0, theApp.m_listcount);
	theApp.m_listcount++;

	return 0;
}

void CMainFrame::OnEnd()
{
	// TODO: 在此添加命令处理程序代码

	if (theApp.m_run)
	{
		theApp.m_run = false;	// 直接设置即可

		AfxMessageBox(_T("end"));
		CMenu *mmenu = GetMenu();
		mmenu->InsertMenuA(ID_END, MF_BYCOMMAND, ID_START, "启动");
	}
}

void CMainFrame::OnProto()
{
	// TODO: 在此添加命令处理程序代码

	// 这边还是弹出一个对话框来选择协议
	ProtoSet p;
	p.DoModal();

}

void CMainFrame::OnSave()
{
	// TODO: 在此添加命令处理程序代码

	// 改变抓包策略 抓包的时候就要保存 先保存到temp中
	// 用户需要保存文件时复制一份

	CString filename;
	CFileDialog dlg(false,"pcap","* .pcap");
	dlg.DoModal();
	filename = dlg.GetPathName();
	
	// 把那个临时文件的内容复制到这个文件中
	if (CopyFile(theApp.m_tempDumpFilePath, filename, true))
	{
		AfxMessageBox("已保存");
	}
	else
	{
		AfxMessageBox("保存出错！");
	}
	

}

void CMainFrame::OnShow()
{
	// TODO: 在此添加命令处理程序代码
	Hub h;
	h.DoModal();

}

void CMainFrame::OnManual()
{
	// TODO: 在此添加命令处理程序代码
	ManualSet d;
	d.DoModal();

}


void CMainFrame::OnSend()
{
	// TODO: 在此添加命令处理程序代码
	PacketSend d;
	d.DoModal();
}
