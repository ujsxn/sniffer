// MoreInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuabao.h"
#include "MoreInfo.h"
#include "afxdialogex.h"

// MoreInfo �Ի���

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


// MoreInfo ��Ϣ�������


BOOL MoreInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 

	// �������ݰ�ץȡʱ��
	m_pakettime.SetWindowTextA(time);

	// ��ʾ���ݵ�16������ʽ
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

	// �ж�Э������
	mac_header machead;
	ip_header iphead;
	
	CString s; // ����moreinfo�ؼ�����ʾ
	CString show; // ������ЩЭ��Ŀؼ�����ʾ

	memcpy(&machead, data, 14);
	u_short type = ntohs(machead.m_cType);
	
	switch (type)
	{
	case 0x0800:
			
		m_protocal.SetWindowTextA("IP"); 
		memcpy(&iphead, data+14, sizeof(iphead));
		int ip_len;
		ip_len = (iphead.ver_ihl & 0xf) * 4;
		// �жϾ���Э��
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
		m_protocal.SetWindowTextA("δ֪Э��");
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}
