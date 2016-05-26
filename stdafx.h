
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include "Include\pcap.h"	// winpcap

typedef struct MAC_FRAME_HEADER
{
	u_char m_cDstMacAddress[6];    //目的mac地址
	u_char m_cSrcMacAddress[6];    //源mac地址 
	u_short m_cType; //上一层协议，0x0800代表IP ，0806代表ARP ，8035代表RARP
}mac_header; //14字节

typedef struct ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	proto;  // Protocol ，1表示ICMP ，2表示IGMP， 6表示TCP， 17表示UDP
	u_short crc;			// Header checksum
	u_long	saddr;		// Source address
	u_long	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}ip_header;

typedef struct arp_header
{
	unsigned short arp_hrd;    // 0001使用MAC
	unsigned short arp_pro;    // 使用 IP为0800
	unsigned char arp_hln;	   // 长度 使用了MAC为：6
	unsigned char arp_pln;     // 长度 使用IP地址：4
	unsigned short arp_op;     // 请求包 应答包：0x0001和0x0002

	unsigned char arp_sha[6];  // 源物理地址
	unsigned long arp_spa;     // 源网络地址
	unsigned char arp_tha[6];  // 目的物理地址
	unsigned long arp_tpa;     // 目的网络地址
}arp_header;	//28

typedef struct udp_header {
	u_short sport;          // 源端口
	u_short dport;          // 目的端口
	u_short len;            // 数据包长度
	u_short crc;            // 校验和
}udp_header;

typedef struct TCP_HEADER
{
	u_short m_sSourPort;        // 源端口号16bit
	u_short m_sDestPort;        // 目的端口号16bit
	unsigned int m_uiSequNum;		  // 序列号32bit
	unsigned int m_uiAcknowledgeNum;  // 确认号32bit
	short m_sHeaderLenAndFlag;
	// 前4位：TCP头长度；中6位：保留；后6位：标志位
	short m_sWindowSize;      // 窗口大小16bit
	short m_sCheckSum;        // 检验和16bit
	short m_surgentPointer;   // 紧急数据偏移量16bit
}tcp_header;









