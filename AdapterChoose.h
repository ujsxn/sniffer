#pragma once
#include "afxwin.h"


// CAdapterChoose �Ի���

class CAdapterChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CAdapterChoose)

public:
	CAdapterChoose(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdapterChoose();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADAPTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	pcap_if_t *alldevs;		// �����豸�б�

	CListBox m_adapterlist;	// ��ʾ�����б�

	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedOk();
};
