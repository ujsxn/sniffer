#pragma once
#include "afxwin.h"


// Hub �Ի���

class Hub : public CDialogEx
{
	DECLARE_DYNAMIC(Hub)

public:
	Hub(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Hub();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_hub;
	virtual BOOL OnInitDialog();
};
