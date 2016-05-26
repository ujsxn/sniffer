#pragma once
#include "afxwin.h"


// Hub 对话框

class Hub : public CDialogEx
{
	DECLARE_DYNAMIC(Hub)

public:
	Hub(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Hub();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_hub;
	virtual BOOL OnInitDialog();
};
