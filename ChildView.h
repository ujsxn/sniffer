
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();
	virtual ~CChildView();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg void OnListBoxDoubleClik();	// ��˫���б��е���Ŀ�����ϸ��Ϣ
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_messagelist;	// ��ʾץȡ�������ݰ�
};

