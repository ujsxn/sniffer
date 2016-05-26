#pragma once
#include "afxwin.h"


// CAdapterChoose 对话框

class CAdapterChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CAdapterChoose)

public:
	CAdapterChoose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdapterChoose();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADAPTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	pcap_if_t *alldevs;		// 网卡设备列表

	CListBox m_adapterlist;	// 显示网卡列表

	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedOk();
};
