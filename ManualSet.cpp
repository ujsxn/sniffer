// ManualSet.cpp : 实现文件
//

#include "stdafx.h"
#include "zhuabao.h"
#include "ManualSet.h"
#include "afxdialogex.h"


// ManualSet 对话框

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


// ManualSet 消息处理程序


void ManualSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	theApp.m_filterset = true;
	m_filter.GetWindowTextA(theApp.filter);
	

	CDialogEx::OnOK();
}
