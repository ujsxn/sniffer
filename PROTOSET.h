#pragma once
#include "afxwin.h"


// PROTOSET �Ի���

class ProtoSet : public CDialogEx
{
	DECLARE_DYNAMIC(ProtoSet)

public:
	ProtoSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProtoSet();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOSET };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_filterlist;
};
