// PROTOSET.cpp : ʵ���ļ�
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


// PROTOSET �Ի���

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


// PROTOSET ��Ϣ�������


void ProtoSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_filterlist.GetCurSel();
	if (i != LB_ERR)
	{
		// ���û�취��Ӳ������
		i = 5 - i - 1;
		theApp.m_filterset = true;
		theApp.filter = protolsit[i];

	}
	CDialogEx::OnOK();
}


BOOL ProtoSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	
	for (int i=0;i<5;i++)
	{
		m_filterlist.InsertString(0,protolsit[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
