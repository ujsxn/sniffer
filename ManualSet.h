#pragma once
#include "afxwin.h"


// ManualSet 对话框

class ManualSet : public CDialogEx
{
	DECLARE_DYNAMIC(ManualSet)

public:
	ManualSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManualSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANUALSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_filter;
	afx_msg void OnBnClickedOk();
};
