// PROTOSET.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuabao.h"
#include "PROTOSET.h"
#include "afxdialogex.h"

CString protolsit[] = 
{
	"ip",
	"ip and tcp",
	"ip and udp",
	"arp",
	"rarp",
	NULL
};


// PROTOSET 对话框

IMPLEMENT_DYNAMIC(ProtoSet, CDialogEx)

ProtoSet::ProtoSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROTOSET, pParent)
{

}

ProtoSet::~ProtoSet()
{
}

void ProtoSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROTOLIST, m_filterlist);
}


BEGIN_MESSAGE_MAP(ProtoSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProtoSet::OnBnClickedOk)
END_MESSAGE_MAP()


// PROTOSET 消息处理程序


void ProtoSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_filterlist.GetCurSel();
	if (i != LB_ERR)
	{
		// 这边没办法先硬编码了
		i = 5 - i - 1;
		theApp.m_filterset = true;
		theApp.filter = protolsit[i];

	}
	CDialogEx::OnOK();
}


BOOL ProtoSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	for (int i=0;i<5;i++)
	{
		m_filterlist.InsertString(0,protolsit[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
