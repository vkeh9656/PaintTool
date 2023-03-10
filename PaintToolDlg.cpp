
// PaintToolDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PaintTool.h"
#include "PaintToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintToolDlg 대화 상자



CPaintToolDlg::CPaintToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINTTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaintToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEN_RADIO, m_pen_radio);
	DDX_Control(pDX, IDC_LINE_RADIO, m_line_radio);
	DDX_Control(pDX, IDC_RECT_RADIO, m_rect_radio);
}

BEGIN_MESSAGE_MAP(CPaintToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PEN_RADIO, &CPaintToolDlg::OnBnClickedPenRadio)
	ON_BN_CLICKED(IDC_LINE_RADIO, &CPaintToolDlg::OnBnClickedLineRadio)
	ON_BN_CLICKED(IDC_RECT_RADIO, &CPaintToolDlg::OnBnClickedRectRadio)
	ON_LBN_SELCHANGE(IDC_COLOR_LIST, &CPaintToolDlg::OnLbnSelchangeColorList)
END_MESSAGE_MAP()


// CPaintToolDlg 메시지 처리기

BOOL CPaintToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_pen_radio.SetCheck(1); // 연필 그리기가 선택된 상태로 시작

	CRect r;
	GetDlgItem(IDC_DRAW_RECT)->GetWindowRect(r);
	ScreenToClient(r);

	m_draw_wnd.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, r, this, 25000);

	// 표준 20가지 색상 목록
	COLORREF color_table[20] = {
		RGB(0,0,0), RGB(0,0,255), RGB(0,255,0), RGB(0,255,255), RGB(255,0,0),
		RGB(255,0,255), RGB(255,255,0), RGB(255,255,255), RGB(0,0,128),
		RGB(0,128,0), RGB(0,128,128), RGB(128,0,0), RGB(128,0,128),
		RGB(128,128,0), RGB(128,128,128), RGB(192,192,192), RGB(192,220,192),
		RGB(166,202,240), RGB(255,251,240), RGB(160,160,164)
	};


	m_color_list.SubclassDlgItem(IDC_COLOR_LIST, this);
	m_color_list.SetColumnWidth(25);	// ListBox 항목의 폭을 25로 설정
	m_color_list.SetItemHeight(0, 25);	// ListBox 항목의 높이를 25로 설정

	
	for (int i = 0; i < 20; i++)
	{
		m_color_list.InsertString(i, L"");
		m_color_list.SetItemData(i, color_table[i]);
	}

	m_color_list.SetCurSel(0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPaintToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPaintToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPaintToolDlg::OnBnClickedPenRadio()
{
	m_draw_wnd.SetDrawType(PEN_MODE);
}

void CPaintToolDlg::OnBnClickedLineRadio()
{
	m_draw_wnd.SetDrawType(LINE_MODE);
}

void CPaintToolDlg::OnBnClickedRectRadio()
{
	m_draw_wnd.SetDrawType(RECT_MODE);
}


void CPaintToolDlg::OnLbnSelchangeColorList()
{
	int index = m_color_list.GetCurSel();
	if (LB_ERR != index) // 안전 코드
	{
		m_draw_wnd.SetPenStyle(m_color_list.GetItemData(index));
	}
}
