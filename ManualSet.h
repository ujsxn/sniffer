#pragma once
#include "afxwin.h"


// ManualSet �Ի���

class ManualSet : public CDialogEx
{
	DECLARE_DYNAMIC(ManualSet)

public:
	ManualSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManualSet();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANUALSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_filter;
	afx_msg void OnBnClickedOk();
};
