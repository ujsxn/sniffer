
// zhuabao.h : zhuabao 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#define WM_GETDATA 1111


// CzhuabaoApp:
// 有关此类的实现，请参阅 zhuabao.cpp
//

class CzhuabaoApp : public CWinApp
{
public:
	CzhuabaoApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	pcap_t *adhandle;			// 数据包抓取
	pcap_dumper_t *dumpfile;	// 用于离线包

	CString m_tempDumpFilePath;	// dump信息暂存到这个文件中
	u_int netmask;				// 网卡设备的掩码
	CString filter;				// 过滤条件 使用string 一定会有保存
								// 最初使用char *存在一定问题

	volatile bool m_run;		// 抓取线程是否在运行
	volatile bool m_filterset;	// 是否设置了过滤条件
	CWinThread	*loopthread;	//抓取数据包的线程

	CArray<CString> m_packettime;		// 数据包抓取的时间（可阅读的格式）
	CArray<pcap_pkthdr> m_packetheader;	// 数据包头
	CArray<u_char *> m_packetlist;		// 数据包
	volatile int m_listcount;			// 保存列表中保存的数据包个数
										// 另用于 view列表的映射
	
	// 用于统计
	volatile int m_ipcount;
	volatile int m_arpcount;
	volatile int m_rarapcount;


	
	afx_msg void OnAppAbout();
	
	DECLARE_MESSAGE_MAP()
	
	
	
};

extern CzhuabaoApp theApp;
