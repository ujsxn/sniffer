
// ChildView.h : CChildView 类的接口
//


#pragma once

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();
	virtual ~CChildView();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg void OnListBoxDoubleClik();	// 在双击列表中的项目后打开详细信息
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_messagelist;	// 显示抓取到的数据包
};

