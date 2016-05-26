// MoreInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuabao.h"
#include "MoreInfo.h"
#include "afxdialogex.h"

// MoreInfo 对话框

IMPLEMENT_DYNAMIC(MoreInfo, CDialogEx)

MoreInfo::MoreInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOREINFO, pParent)
{

}

MoreInfo::~MoreInfo()
{
}

void MoreInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROTOCAL, m_protocal);
	DDX_Control(pDX, IDC_PACKETTIME, m_pakettime);
	DDX_Control(pDX, IDC_MOREINFO, m_moreinfo);
	DDX_Control(pDX, IDC_MOREINFO16, m_moreinfo16);
}


BEGIN_MESSAGE_MAP(MoreInfo, CDialogEx)
END_MESSAGE_MAP()


// MoreInfo 消息处理程序


BOOL MoreInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	 

	// 设置数据包抓取时间
	m_pakettime.SetWindowTextA(time);

	// 显示数据的16进制形式
	CString s16;
	for (int i = 0; i < len; i++)
	{
		if (i % 20 == 0)
		{
			s16.Append("\r\n");
		}

		if (isprint(data[i]))
		{
			s16.AppendFormat("%02x", data[i]);
		}
		else
		{
			s16.AppendFormat("%02x", 0);
		}
	}
	m_moreinfo16.SetWindowTextA(s16);

	// 判断协议类型
	mac_header machead;
	ip_header iphead;
	
	CString s; // 用于moreinfo控件的显示
	CString show; // 用于有些协议的控件的显示

	memcpy(&machead, data, 14);
	u_short type = ntohs(machead.m_cType);
	
	switch (type)
	{
	case 0x0800:
			
		m_protocal.SetWindowTextA("IP"); 
		memcpy(&iphead, data+14, sizeof(iphead));
		int ip_len;
		ip_len = (iphead.ver_ihl & 0xf) * 4;
		// 判断具体协议
		switch (iphead.proto)
		{
		case 1:
			
			m_protocal.SetWindowTextA("ICMP");
			
			for (int i = 14; i < len; i++)
			{
				if (i % 40 == 0)
				{
					s.Append("\r\n");
				}
				if (isprint(data[i]))
				{
					s.AppendFormat("%c", data[i]);
				}
				else
				{
					s.AppendFormat("%c", '.');
				}

			}
			m_moreinfo.SetWindowTextA(s); 
			
			break;
		case 6:
			tcp_header t;
			
			memcpy(&t, data + 14 + ip_len, sizeof(tcp_header));
			u_short tsport;
			tsport = ntohs(t.m_sSourPort);
			u_short tdport;
			tdport = ntohs(t.m_sDestPort);

			show += "tcp: ";
			show.AppendFormat("%u", tsport);
			show += "->";
			show.AppendFormat("%u", tdport);

			

			for (int i = 14; i < len; i++)
			{
				if (i % 40 == 0)
				{
					s.Append("\r\n");
				}
				if (isprint(data[i]))
				{
					s.AppendFormat("%c", data[i]);
				}
				else
				{
					s.AppendFormat("%c", '.');
				}

			}
			m_protocal.SetWindowTextA(show);
			m_moreinfo.SetWindowTextA(s);
			break;
		case 17:
			
			udp_header u;
			
			memcpy(&u, data + 14 + ip_len,sizeof(udp_header));
			u_short sport;
			sport = ntohs(u.sport);
			u_short dport;
			dport = ntohs(u.dport);

			show += "UDP: ";
			show.AppendFormat("%u", sport);
			show += "->";
			show.AppendFormat("%u", dport);

			for (int i = 14; i < len; i++)
			{
				if (i % 40 == 0)
				{
					s.Append("\r\n");
				}
				if (isprint(data[i]))
				{
					s.AppendFormat("%c", data[i]);
				}
				else
				{
					s.AppendFormat("%c", '.');
				}

			}


			m_protocal.SetWindowTextA(show);
			m_moreinfo.SetWindowTextA(s);	
			break;
		default:
			for (int i = 14; i < len; i++)
			{
				if (i % 40 == 0)
				{
					s.Append("\r\n");
				}
				if (isprint(data[i]))
				{
					s.AppendFormat("%c", data[i]);
				}
				else
				{
					s.AppendFormat("%c", '.');
				}

			}

			m_moreinfo.SetWindowTextA(s);
			break;
		}

		break;
	case 0x0806:
		m_protocal.SetWindowTextA("ARP"); 

		for (int i = 14; i < len; i++)
		{
			if (i % 40 == 0)
			{
				s.Append("\r\n");
			}
			if (isprint(data[i]))
			{
				s.AppendFormat("%c", data[i]);
			}
			else
			{
				s.AppendFormat("%c", '.');
			}

		}

		m_moreinfo.SetWindowTextA(s);
		break;
	case 0x8035:
		m_protocal.SetWindowTextA("RARP");
		for (int i = 14; i < len; i++)
		{
			if (i % 40 == 0)
			{
				s.Append("\r\n");
			}
			if (isprint(data[i]))
			{
				s.AppendFormat("%c", data[i]);
			}
			else
			{
				s.AppendFormat("%c", '.');
			}

		}

		m_moreinfo.SetWindowTextA(s);
		break;
	default:
		m_protocal.SetWindowTextA("未知协议");
		for (int i = 14; i < len; i++)
		{
			if (i % 40 == 0)
			{
				s.Append("\r\n");
			}
			if (isprint(data[i]))
			{
				s.AppendFormat("%c", data[i]);
			}
			else
			{
				s.AppendFormat("%c", '.');
			}

		}

		m_moreinfo.SetWindowTextA(s);
		break;
	}
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
