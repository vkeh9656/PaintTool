// DrawWnd.cpp: 구현 파일
//

#include "pch.h"
#include "PaintTool.h"
#include "DrawWnd.h"


// DrawWnd

IMPLEMENT_DYNAMIC(DrawWnd, CWnd)

DrawWnd::DrawWnd()
{

}

DrawWnd::~DrawWnd()
{
}


BEGIN_MESSAGE_MAP(DrawWnd, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// DrawWnd 메시지 처리기

void DrawWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_is_clicked = 1;
	m_prev_point = point;

	SetCapture(); // Mouse 메시지의 선점권을 갖고간다.
	CWnd::OnLButtonDown(nFlags, point);
}


void DrawWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_is_clicked = 0;

	ReleaseCapture(); // Mouse 메시지의 선점권을 해지한다.
	CWnd::OnLButtonUp(nFlags, point);
}


void DrawWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked)
	{
		CClientDC dc(this);

		HDC h_image_dc = m_image.GetDC();
		CDC* p_image_dc = CDC::FromHandle(h_image_dc);

		p_image_dc->MoveTo(m_prev_point); // 이전 위치 (시작)
		p_image_dc->LineTo(point); // 마지막 위치 (끝)

		m_image.ReleaseDC();

		m_image.Draw(dc, 0, 0);
		m_prev_point = point;
	}

	CWnd::OnMouseMove(nFlags, point);
}




int DrawWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	CRect r;
	GetClientRect(r);

	m_image.Create(r.Width(), r.Height(), 32);
	
	HDC h_image_dc = m_image.GetDC();
	CDC* p_image_dc = CDC::FromHandle(h_image_dc);
	p_image_dc->Rectangle(r);
	m_image.ReleaseDC();

	return 0;
}


void DrawWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	m_image.Draw(dc, 0, 0);
}
