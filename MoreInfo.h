#pragma once
#include "afxwin.h"


// MoreInfo �Ի���

class MoreInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MoreInfo)

public:
	MoreInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MoreInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOREINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_protocal;		// ��ʾЭ������
	CStatic m_pakettime;	// ��ʾ���ݰ���ȡʱ��
	CEdit m_moreinfo;		// ��ʾ���ݰ�����
	CEdit m_moreinfo16;		// ��16������ʾ���ݰ�����

	u_char *data;			// ���ݰ�
	CString time;			// ���ݰ�ץȡʱ��
	int len;				// ���ݰ�����
	virtual BOOL OnInitDialog();
	
	
};
