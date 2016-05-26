
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public: 
	CStatusBar	m_wndStatusBar;	//状态栏
	CChildView	m_wndView;		//视图
	

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);

	// 处理传来的数据包
	afx_msg LRESULT OnGetData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnStart();
	afx_msg void OnEnd();
	afx_msg void OnProto();
	afx_msg void OnSave();
	afx_msg void OnShow();
	afx_msg void OnManual();
	afx_msg void OnSend();
};


