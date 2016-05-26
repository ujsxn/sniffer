// AdapterChoose.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "zhuabao.h"
#include "AdapterChoose.h"
#include "afxdialogex.h"


// CAdapterChoose �Ի���

IMPLEMENT_DYNAMIC(CAdapterChoose, CDialogEx)

CAdapterChoose::CAdapterChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADAPTER, pParent)
{

}

CAdapterChoose::~CAdapterChoose()
{
}

void CAdapterChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADAPTERLIST, m_adapterlist);
}


BEGIN_MESSAGE_MAP(CAdapterChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdapterChoose::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdapterChoose ��Ϣ�������


BOOL CAdapterChoose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//1 �Ȼ�ȡ�����б�

	char errbuf[PCAP_ERRBUF_SIZE + 1];
	pcap_if_t *d;


	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{

		AfxTrace("Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	//2 ��ӵ�listbox��
	for (d = alldevs; d; d = d->next)
	{
		CString s(d->name);
		s += CString(d->description);
		m_adapterlist.AddString(s);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CAdapterChoose::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, inum;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *d;
	

	inum = m_adapterlist.GetCurSel();
	// ��ǰѡ������Ĵ��㿪ʼ�������������Ŀ��ǰδѡ������ LB_ERR(-1)
	// ���û��ѡ��������ѡ�����ǵ�һ������

	// �õ�ѡ�������
	for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);
	
	// ����netmask
	if (d->addresses != NULL)
		theApp.netmask = ((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		theApp.netmask = 0xffffff;

	// ����������
	if ((theApp.adhandle = pcap_open_live(d->name,	// �豸����
		65536,			// ���ò���ֶδ�С
						// 65536 ��֤���ķֶ�Ҳ���Բ���
		0,				// ����ģʽ
		1000,			// ��ʱʱ��
		errbuf			
	)) == NULL)
	{
		AfxTrace("Unable to open the adapter.");
		pcap_freealldevs(alldevs);
		exit(1);
	}

	pcap_freealldevs(alldevs);

	CDialogEx::OnOK();
}
