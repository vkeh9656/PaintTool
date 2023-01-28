
// PaintToolDlg.h: 헤더 파일
//

#pragma once
#include "DrawWnd.h"

// CPaintToolDlg 대화 상자
class CPaintToolDlg : public CDialogEx
{
private:
	DrawWnd m_draw_wnd;


// 생성입니다.
public:
	CPaintToolDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
