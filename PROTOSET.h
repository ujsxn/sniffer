#pragma once
#include "afxwin.h"


// PROTOSET 对话框

class ProtoSet : public CDialogEx
{
	DECLARE_DYNAMIC(ProtoSet)

public:
	ProtoSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProtoSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOSET };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_filterlist;
};
