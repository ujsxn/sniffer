// Hub.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuabao.h"
#include "Hub.h"
#include "afxdialogex.h"


// Hub �Ի���

IMPLEMENT_DYNAMIC(Hub, CDialogEx)

Hub::Hub(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HUB, pParent)
{

}

Hub::~Hub()
{
}

void Hub::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HUB, m_hub);
}


BEGIN_MESSAGE_MAP(Hub, CDialogEx)
END_MESSAGE_MAP()


// Hub ��Ϣ�������


BOOL Hub::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ��ʾͳ������
	CString s;
	s += "IP:	";
	s.AppendFormat("%d", theApp.m_ipcount);
	
	s += "	ARP:	";
	s.AppendFormat("%d", theApp.m_arpcount);
	
	s += "	RARP:	";
	s.AppendFormat("%d", theApp.m_rarapcount);

	m_hub.SetWindowTextA(s);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
