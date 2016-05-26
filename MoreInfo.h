#pragma once
#include "afxwin.h"


// MoreInfo 对话框

class MoreInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MoreInfo)

public:
	MoreInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MoreInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOREINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_protocal;		// 显示协议类型
	CStatic m_pakettime;	// 显示数据包获取时间
	CEdit m_moreinfo;		// 显示数据包内容
	CEdit m_moreinfo16;		// 按16进制显示数据包内容

	u_char *data;			// 数据包
	CString time;			// 数据包抓取时间
	int len;				// 数据包长度
	virtual BOOL OnInitDialog();
	
	
};
