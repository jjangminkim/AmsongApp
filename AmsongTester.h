
// AmsongTester.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

//////////////////////////////////////////////////////////////////////

#define UM_WATCH_CONNECTED			(WM_USER + 100)
#define UM_WATCH_DISCONNECTED		(WM_USER + 101)
#define UM_WATCH_EVENTLOADED        (WM_USER + 102)
#define UM_WATCH_STATUSLOADED		(WM_USER + 103)
#define UM_WATCH_DEVICESTATUSLOADED (WM_USER + 104)
#define UM_SELECTED_CAMERA			(WM_USER + 200)
#define UM_SCREEN_DBLCLICK			(WM_USER + 201)

//////////////////////////////////////////////////////////////////////

// CAmsongTesterApp:
// 이 클래스의 구현에 대해서는 AmsongTester.cpp을 참조하십시오.
//

class CAmsongTesterApp : public CWinApp
{
public:
	CAmsongTesterApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CAmsongTesterApp theApp;