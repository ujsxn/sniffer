
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include "Include\pcap.h"	// winpcap

typedef struct MAC_FRAME_HEADER
{
	u_char m_cDstMacAddress[6];    //Ŀ��mac��ַ
	u_char m_cSrcMacAddress[6];    //Դmac��ַ 
	u_short m_cType; //��һ��Э�飬0x0800����IP ��0806����ARP ��8035����RARP
}mac_header; //14�ֽ�

typedef struct ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	proto;  // Protocol ��1��ʾICMP ��2��ʾIGMP�� 6��ʾTCP�� 17��ʾUDP
	u_short crc;			// Header checksum
	u_long	saddr;		// Source address
	u_long	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}ip_header;

typedef struct arp_header
{
	unsigned short arp_hrd;    // 0001ʹ��MAC
	unsigned short arp_pro;    // ʹ�� IPΪ0800
	unsigned char arp_hln;	   // ���� ʹ����MACΪ��6
	unsigned char arp_pln;     // ���� ʹ��IP��ַ��4
	unsigned short arp_op;     // ����� Ӧ�����0x0001��0x0002

	unsigned char arp_sha[6];  // Դ�����ַ
	unsigned long arp_spa;     // Դ�����ַ
	unsigned char arp_tha[6];  // Ŀ�������ַ
	unsigned long arp_tpa;     // Ŀ�������ַ
}arp_header;	//28

typedef struct udp_header {
	u_short sport;          // Դ�˿�
	u_short dport;          // Ŀ�Ķ˿�
	u_short len;            // ���ݰ�����
	u_short crc;            // У���
}udp_header;

typedef struct TCP_HEADER
{
	u_short m_sSourPort;        // Դ�˿ں�16bit
	u_short m_sDestPort;        // Ŀ�Ķ˿ں�16bit
	unsigned int m_uiSequNum;		  // ���к�32bit
	unsigned int m_uiAcknowledgeNum;  // ȷ�Ϻ�32bit
	short m_sHeaderLenAndFlag;
	// ǰ4λ��TCPͷ���ȣ���6λ����������6λ����־λ
	short m_sWindowSize;      // ���ڴ�С16bit
	short m_sCheckSum;        // �����16bit
	short m_surgentPointer;   // ��������ƫ����16bit
}tcp_header;









