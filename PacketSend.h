#pragma once
#include "afxwin.h"


// PacketSend 对话框

class PacketSend : public CDialogEx
{
	DECLARE_DYNAMIC(PacketSend)

public:
	PacketSend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PacketSend();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_mac;
	CButton m_ip;
	CEdit m_data;
	virtual BOOL OnInitDialog();
	CEdit m_src;
	CEdit m_dst;
	afx_msg void OnBnClickedOk();
};
