#pragma once
#include "afxwin.h"


// PacketSend �Ի���

class PacketSend : public CDialogEx
{
	DECLARE_DYNAMIC(PacketSend)

public:
	PacketSend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PacketSend();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
