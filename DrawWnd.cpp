// DrawWnd.cpp: 구현 파일
//

#include "pch.h"
#include "PaintTool.h"
#include "DrawWnd.h"


// DrawWnd

IMPLEMENT_DYNAMIC(DrawWnd, CWnd)

DrawWnd::DrawWnd() : m_my_pen(PS_SOLID, 1, RGB(0, 0, 0))
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
	ON_WM_DESTROY()
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
	if (m_is_clicked)
	{
		if (m_draw_type == LINE_MODE)
		{
			CDC* p_image_dc = CDC::FromHandle(m_image.GetDC());
			
			p_image_dc->MoveTo(m_prev_point); // 
			p_image_dc->LineTo(point); // 
			m_image.ReleaseDC();
		}
		else if (m_draw_type == RECT_MODE)
		{
			CDC* p_image_dc = CDC::FromHandle(m_image.GetDC());
			CGdiObject* p_old_brush = p_image_dc->SelectStockObject(NULL_BRUSH);
			p_image_dc->Rectangle(m_prev_point.x, m_prev_point.y, point.x, point.y);
			p_image_dc->SelectObject(p_old_brush);
			m_image.ReleaseDC();
		}
		
		m_is_clicked = 0;
		ReleaseCapture(); // Mouse 메시지의 선점권을 해지한다.
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void DrawWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked)
	{
		CClientDC dc(this);
		if (m_draw_type == PEN_MODE)
		{
			HDC h_image_dc = m_image.GetDC();
			CDC* p_image_dc = CDC::FromHandle(h_image_dc);

			CPen* p_old_pen = p_image_dc->SelectObject(&m_my_pen);
			p_image_dc->MoveTo(m_prev_point); // 이전 위치 (시작)
			p_image_dc->LineTo(point); // 마지막 위치 (끝)
			p_image_dc->SelectObject(p_old_pen);

			m_prev_point = point; // 현재 점을 이전 점으로 업데이트

			m_image.ReleaseDC();

			m_image.Draw(dc, 0, 0);
		}
		else if (m_draw_type == LINE_MODE)
		{
			// 잔상 제거를 위해 리셋 + 직접 dc를 사용해서 그림 그려줌
			m_image.Draw(dc, 0, 0);

			dc.MoveTo(m_prev_point); // 이전 위치 (시작)
			dc.LineTo(point); // 마지막 위치 (끝)
		}
		else if (m_draw_type == RECT_MODE)
		{
			CDC* p_temp_dc = CDC::FromHandle(m_temp_image.GetDC());

			m_image.Draw(*p_temp_dc, 0, 0);

			CGdiObject *p_old_brush = p_temp_dc->SelectStockObject(NULL_BRUSH);
			p_temp_dc->Rectangle(m_prev_point.x, m_prev_point.y, point.x, point.y);
			p_temp_dc->SelectObject(p_old_brush);

			m_temp_image.ReleaseDC();
			m_temp_image.Draw(dc, 0, 0);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}




int DrawWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	CRect r;
	GetClientRect(r);

	m_image.Create(r.Width(), r.Height(), 32);
	m_temp_image.Create(r.Width(), r.Height(), 32);

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


void DrawWnd::OnDestroy()
{
	CWnd::OnDestroy();

	m_my_pen.DeleteObject();
}
