#include "stdafx.h"
#include "zhuabao.h"
#include "ChildView.h"
#include "MoreInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_LBN_DBLCLK(IDC_PACKETLIST, OnListBoxDoubleClik)
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

// ���ʹ��on paint���岻�� ֻ��Ҫ���һ���ؼ�
// �����и�init oncreate֮��� ������
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (m_messagelist)
	{
	}
	else
	{
		CRect c;
		GetClientRect(c);
		m_messagelist.Create(LBS_STANDARD, c, this, IDC_PACKETLIST);
		m_messagelist.ShowWindow(SW_SHOWNORMAL);
	}
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}

void CChildView::OnListBoxDoubleClik()
{
	// ��ȡ˫��ѡ�е����ݰ�
	int sel = m_messagelist.GetCurSel();
	int i = m_messagelist.GetItemData(sel);


	MoreInfo m;
	m.data = theApp.m_packetlist[i];
	m.time = theApp.m_packettime[i];
	m.len = theApp.m_packetheader[i].len;
	m.DoModal();

}