
// MainFrm.cpp : CMainFrame ���ʵ��
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

// ץ���߳�
UINT startloop(LPVOID param)
{

	pcap_pkthdr header;
	const u_char *pkt_data_old = (u_char *)"old data";
	const u_char *pkt_data;
	u_char *save_data;

	struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;

	// ץȡ�������ݰ��������ģ�
	// ��һ�ε����ݰ��ڵ���next֮���û�ˣ����ܣ�Ӧ���ǰ���̬��ŵ�
	// ������߿��������������ݰ������ñ���

	while (theApp.m_run)
	{
		pkt_data = pcap_next(theApp.adhandle, &header);

		if (pkt_data == NULL)
			/* ��ʱ����� */
			continue;

		// ��߻�ȡ�������ݰ����ݿ��ܾͲ���
		// ����winpcap ���������������
		if (memcmp(pkt_data, pkt_data_old, sizeof(pkt_data) == 0))
		{
			AfxOutputDebugString("same\n");
			continue;
		}
		pkt_data_old = pkt_data;

		local_tv_sec = header.ts.tv_sec;	// ��
		ltime = localtime(&local_tv_sec);	// ת��Ϊ����ʱ��
		strftime(timestr, sizeof timestr, "%H:%M:%S", ltime); //����ʱ���ʽ
		

		// �����ݰ������б�
		// ���濪�� ���浽��������
		save_data = new u_char[header.len];
		memcpy(save_data, pkt_data, header.len);

		// ���浽zhuabao�е��б�
		theApp.m_packetlist.Add(save_data);
		theApp.m_packettime.Add(timestr);
		theApp.m_packetheader.Add(header);
		
		// ���浽�ļ���
		pcap_dump((u_char *)theApp.dumpfile, &header, pkt_data);

		// ����Ϣ��������ʾ
		PostMessage(*theApp.m_pMainWnd, WM_GETDATA, NULL, NULL);
	}

	// �ر�pcap
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	// Ĭ�ϴ���ʱwsoverlappedwindow ����
	cs.style = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnStart()
{
	// �û�����������˵���ť��Ӧ�õ����Ի������û�ѡ������
	CAdapterChoose d;
	if (d.DoModal() == IDOK)
	{
		struct bpf_program fcode;

		// �����ù�������������
		if (theApp.m_filterset)
		{
			//compile the filter
			if (pcap_compile(theApp.adhandle, &fcode, theApp.filter.GetBuffer(), 1, theApp.netmask) < 0)
			{
				AfxMessageBox("�����������ʧ�ܣ�");
			}

			//set the filter
			if (pcap_setfilter(theApp.adhandle, &fcode) < 0)
			{
				AfxMessageBox("���ù�������ʧ�ܣ�");
			}

		}

		theApp.dumpfile = pcap_dump_open(theApp.adhandle, theApp.m_tempDumpFilePath);
		theApp.m_run = true;
		theApp.loopthread = AfxBeginThread(startloop, "1");

		CMenu *mmenu = GetMenu();
		// ����ʹ�˵�ʧЧ ֻ��ɾ���˲˵���
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
		// ע��inet_ntoaֱ�ӽ��������ֽڶˡ���ת��

		// ��ʾIP��ַ
		in_addr ipadd;
		ipadd.S_un.S_addr = (ip.saddr);
		s += inet_ntoa(ipadd);
		s += "->";
		ipadd.S_un.S_addr = (ip.daddr);
		s += inet_ntoa(ipadd);

		// ������
		theApp.m_ipcount++;
		break;
	case 0x0806:
		arp_header arp;
		memcpy(&arp, data + 14, sizeof(arp_header));

		short type;
		type = ntohs(arp.arp_op);
		if (type == 1)
		{
			s += " ARP �����";
		}
		else if (type == 2)
		{
			s += " ARP Ӧ���";
		}

		// ������
		theApp.m_arpcount++;
		break;
	case 0x8035:
		arp_header rarp;
		memcpy(&rarp, data + 14, sizeof(arp_header));

		short rtype;
		rtype = ntohs(rarp.arp_op);
		if (rtype == 1)
		{
			s += " RARP �����";
		}
		else if (rtype == 2)
		{
			s += " RARP Ӧ���";
		}

		// ������
		theApp.m_rarapcount++;
		break;
	default:
		s += " δ֪Э��: ";
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
	// TODO: �ڴ���������������

	if (theApp.m_run)
	{
		theApp.m_run = false;	// ֱ�����ü���

		AfxMessageBox(_T("end"));
		CMenu *mmenu = GetMenu();
		mmenu->InsertMenuA(ID_END, MF_BYCOMMAND, ID_START, "����");
	}
}

void CMainFrame::OnProto()
{
	// TODO: �ڴ���������������

	// ��߻��ǵ���һ���Ի�����ѡ��Э��
	ProtoSet p;
	p.DoModal();

}

void CMainFrame::OnSave()
{
	// TODO: �ڴ���������������

	// �ı�ץ������ ץ����ʱ���Ҫ���� �ȱ��浽temp��
	// �û���Ҫ�����ļ�ʱ����һ��

	CString filename;
	CFileDialog dlg(false,"pcap","* .pcap");
	dlg.DoModal();
	filename = dlg.GetPathName();
	
	// ���Ǹ���ʱ�ļ������ݸ��Ƶ�����ļ���
	if (CopyFile(theApp.m_tempDumpFilePath, filename, true))
	{
		AfxMessageBox("�ѱ���");
	}
	else
	{
		AfxMessageBox("�������");
	}
	

}

void CMainFrame::OnShow()
{
	// TODO: �ڴ���������������
	Hub h;
	h.DoModal();

}

void CMainFrame::OnManual()
{
	// TODO: �ڴ���������������
	ManualSet d;
	d.DoModal();

}


void CMainFrame::OnSend()
{
	// TODO: �ڴ���������������
	PacketSend d;
	d.DoModal();
}
