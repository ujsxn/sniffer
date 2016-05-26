// ManualSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuabao.h"
#include "ManualSet.h"
#include "afxdialogex.h"


// ManualSet �Ի���

IMPLEMENT_DYNAMIC(ManualSet, CDialogEx)

ManualSet::ManualSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANUALSET, pParent)
{

}

ManualSet::~ManualSet()
{
}

void ManualSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANUAL, m_filter);
}


BEGIN_MESSAGE_MAP(ManualSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &ManualSet::OnBnClickedOk)
END_MESSAGE_MAP()


// ManualSet ��Ϣ�������


void ManualSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	theApp.m_filterset = true;
	m_filter.GetWindowTextA(theApp.filter);
	

	CDialogEx::OnOK();
}
