// PacketSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuabao.h"
#include "PacketSend.h"
#include "afxdialogex.h"


// PacketSend �Ի���

IMPLEMENT_DYNAMIC(PacketSend, CDialogEx)

PacketSend::PacketSend(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEND, pParent)
{

}

PacketSend::~PacketSend()
{
}

void PacketSend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAC, m_mac);
	DDX_Control(pDX, IDC_IP, m_ip);
	DDX_Control(pDX, IDC_DATA, m_data);
	DDX_Control(pDX, IDC_SRC, m_src);
	DDX_Control(pDX, IDC_DEST, m_dst);
}


BEGIN_MESSAGE_MAP(PacketSend, CDialogEx)
	ON_BN_CLICKED(IDOK, &PacketSend::OnBnClickedOk)
END_MESSAGE_MAP()


// PacketSend ��Ϣ�������


BOOL PacketSend::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_src.SetWindowTextA("Դ��ַ");
	m_dst.SetWindowTextA("Ŀ�ĵ�ַ");
	m_data.SetWindowTextA("����");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void PacketSend::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	u_char packet[100];

	
	CString src;
	CString dst;
	CString data;
	m_src.GetWindowTextA(src);
	
	m_dst.GetWindowTextA(dst);
	
	for (int i=0; i < 6; i++)
	{
		src.GetBuffer()[i] -= '0';
		dst.GetBuffer()[i] -= '0';
	}

	m_data.GetWindowTextA(data);

	
	if (m_mac.GetCheck())
	{
		memcpy(packet, dst.GetBuffer(), 6);
		memcpy(packet + 6, src.GetBuffer(), 6);
		memcpy(packet + 12, data.GetBuffer(), 88);
		if (pcap_sendpacket(theApp.adhandle, packet, 100) != 0)
		{
			AfxMessageBox("����ʧ��!");
		}
	}

	CDialogEx::OnOK();
}
