
// zhuabao.h : zhuabao Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#define WM_GETDATA 1111


// CzhuabaoApp:
// �йش����ʵ�֣������ zhuabao.cpp
//

class CzhuabaoApp : public CWinApp
{
public:
	CzhuabaoApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	pcap_t *adhandle;			// ���ݰ�ץȡ
	pcap_dumper_t *dumpfile;	// �������߰�

	CString m_tempDumpFilePath;	// dump��Ϣ�ݴ浽����ļ���
	u_int netmask;				// �����豸������
	CString filter;				// �������� ʹ��string һ�����б���
								// ���ʹ��char *����һ������

	volatile bool m_run;		// ץȡ�߳��Ƿ�������
	volatile bool m_filterset;	// �Ƿ������˹�������
	CWinThread	*loopthread;	//ץȡ���ݰ����߳�

	CArray<CString> m_packettime;		// ���ݰ�ץȡ��ʱ�䣨���Ķ��ĸ�ʽ��
	CArray<pcap_pkthdr> m_packetheader;	// ���ݰ�ͷ
	CArray<u_char *> m_packetlist;		// ���ݰ�
	volatile int m_listcount;			// �����б��б�������ݰ�����
										// ������ view�б��ӳ��
	
	// ����ͳ��
	volatile int m_ipcount;
	volatile int m_arpcount;
	volatile int m_rarapcount;


	
	afx_msg void OnAppAbout();
	
	DECLARE_MESSAGE_MAP()
	
	
	
};

extern CzhuabaoApp theApp;
