// Hub.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuabao.h"
#include "Hub.h"
#include "afxdialogex.h"


// Hub 对话框

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


// Hub 消息处理程序


BOOL Hub::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 显示统计数据
	CString s;
	s += "IP:	";
	s.AppendFormat("%d", theApp.m_ipcount);
	
	s += "	ARP:	";
	s.AppendFormat("%d", theApp.m_arpcount);
	
	s += "	RARP:	";
	s.AppendFormat("%d", theApp.m_rarapcount);

	m_hub.SetWindowTextA(s);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
