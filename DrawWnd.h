#pragma once

#define PEN_MODE	1
#define LINE_MODE	2
#define RECT_MODE	3

// DrawWnd

class DrawWnd : public CWnd
{
	DECLARE_DYNAMIC(DrawWnd)
private:
	char m_is_clicked = 0;
	CPoint m_prev_point;
	CImage m_image, m_temp_image; // MemoryDC 용
	CDC m_image_dc, m_temp_dc;

	char m_draw_type = 1; // 1-> 연필, 2-> 선, 3-> 사각형
	CPen m_my_pen;

public:
	DrawWnd();
	virtual ~DrawWnd();

	void SetDrawType(char a_type)
	{
		m_draw_type = a_type;
	}

	void SetPenStyle(COLORREF a_color)
	{
		m_my_pen.DeleteObject();	// 기존 펜은 지우고
		m_my_pen.CreatePen(PS_SOLID, 1, a_color);	// 새로 생성
	}



protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


