
// AmsongTester.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

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
// �� Ŭ������ ������ ���ؼ��� AmsongTester.cpp�� �����Ͻʽÿ�.
//

class CAmsongTesterApp : public CWinApp
{
public:
	CAmsongTesterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAmsongTesterApp theApp;