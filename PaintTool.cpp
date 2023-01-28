
// PaintTool.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "PaintTool.h"
#include "PaintToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintToolApp

BEGIN_MESSAGE_MAP(CPaintToolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPaintToolApp 생성

CPaintToolApp::CPaintToolApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CPaintToolApp 개체입니다.

CPaintToolApp theApp;


// CPaintToolApp 초기화

BOOL CPaintToolApp::InitInstance()
{
	CWinApp::InitInstance();

	CPaintToolDlg dlg;
	dlg.DoModal();
	
	return FALSE;
}

