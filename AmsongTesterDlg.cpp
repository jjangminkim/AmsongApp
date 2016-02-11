
// AmsongTesterDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AmsongTester.h"
#include "AmsongTesterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialog {
    public:
	    CAboutDlg();

	    enum { IDD = IDD_ABOUTBOX };

	protected:
	    virtual void DoDataExchange(CDataExchange* pDX);

    protected:
	    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CAmsongTesterDlg* CAmsongTesterDlg::_lpOwnerWnd = NULL;

CAmsongTesterDlg::CAmsongTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAmsongTesterDlg::IDD, pParent)
    , _fDisconnectByMe(false)
    , _appStatus(APP_STATUS_DISCONNECTED)
	, _captureDelayedMilisec(0)
	, _eventOccurredTick(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    _watchHandle = IDISHNULL;
}

void CAmsongTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_LOG, _logList);
}

BEGIN_MESSAGE_MAP(CAmsongTesterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
    ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CAmsongTesterDlg::OnBnClickedButtonConnect)
    ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CAmsongTesterDlg::OnBnClickedButtonDisconnect)
    ON_BN_CLICKED(IDC_BUTTON_GEN_EVENT, &CAmsongTesterDlg::OnBnClickedButtonGenEvent)
    ON_MESSAGE(UM_WATCH_CONNECTED, OnWatchConnected)
	ON_MESSAGE(UM_WATCH_DISCONNECTED, OnWatchDisConnected)
	ON_MESSAGE(UM_WATCH_STATUSLOADED, OnWatchStatusLoaded)
    ON_MESSAGE(UM_WATCH_DEVICESTATUSLOADED, OnWatchDeviceStatusLoaded)
	ON_MESSAGE(UM_WATCH_EVENTLOADED, OnWatchEventLoaded)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE_EVENT, &CAmsongTesterDlg::OnBnClickedButtonEnableEvent)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CAmsongTesterDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()

// watchSDK callback function ///////////////////////////////////////////////
void IDISCALLBACK watch_onConnected(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
	CAmsongTesterDlg& rOwner = *CAmsongTesterDlg::_lpOwnerWnd;

    int channel = static_cast<int>(wParam);

    ::PostMessage(rOwner.GetSafeHwnd(), UM_WATCH_CONNECTED, static_cast<WPARAM>(channel), 0);
}

void IDISCALLBACK watch_onDisconnected(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
    CAmsongTesterDlg& rOwner = *CAmsongTesterDlg::_lpOwnerWnd;
	
	int channel    = static_cast<int>(wParam);
	
    LPPARAM_DISCONNECT lpDisconn = (LPPARAM_DISCONNECT)lParam;
    int whydisconn = static_cast<int>(lpDisconn->_reason);

	if (rOwner._fDisconnectByMe == false) {
		Sleep(0);
	}

	::PostMessage(rOwner.GetSafeHwnd(), UM_WATCH_DISCONNECTED, static_cast<WPARAM>(channel), static_cast<LPARAM>(whydisconn));
}

void IDISCALLBACK watch_frameLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
    CAmsongTesterDlg& rOwner = *CAmsongTesterDlg::_lpOwnerWnd;

	LPPARAMWS_FRAMEINFO lpParams = reinterpret_cast<LPPARAMWS_FRAMEINFO>(lParam);
	ASSERT(sizeof(PARAMWS_FRAMEINFO) == lpParams->_dwSize);

    // offset to actual frame data
    int offset = ::watch_getFrameDataOffset(hWatch, (int)wParam, lpParams->_lpBuffer);

	// for IDR;
	if (rOwner._screen.getCameraState(lpParams->_hostcamera) == CameraView::NO_VIDEO) {
		rOwner._screen.setCameraState(lpParams->_hostcamera, CameraView::ENABLED);
	}

    // 일단 AUDIO FRAME은 무시한다.
    /*
    if (lpParams->_frameType == IDIS_FRAMETYPE::AUDIO_FRAME && lpParams->_hostcamera == rOwner._selectedAudioCamera - 1) {
        const int bufMax = 4096;
        BYTE buffer[bufMax];
        memset(buffer, 0, bufMax);
        int decodedLen;
        PARAMW_AUDIOINFO audioInfo;
        rOwner._watcher.decodeAudioFrame(hWatch, (int)wParam, lpParams, buffer, bufMax, &decodedLen, &audioInfo);
        rOwner._watcher.playAudioFrame(hWatch, (int)wParam, lpParams);
    }
    else {
    */
	    while (rOwner._screen.putLoadedFrame(*lpParams) == false) {
		    if (rOwner._screen.isUseSingleMode())
		    if (lpParams->_frameType == IDIS_FRAMETYPE::X_FRAME ||
			    lpParams->_decoder == IDIS_DECODERTYPE::MJPEG) {
			    break;
		    }

		    Sleep(10);
	    }
    //}

	Sleep(0); // for prevention piggy loop.
}

void IDISCALLBACK watch_eventLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
    CAmsongTesterDlg& rOwner = *CAmsongTesterDlg::_lpOwnerWnd;

	LPPARAMW_EVENTINFO lpEventInfo = reinterpret_cast<LPPARAMW_EVENTINFO>(lParam);
	ASSERT(lpEventInfo->_dwSize == sizeof(PARAMW_EVENTINFO));

    CString eventLog;

    switch (lpEventInfo->_evtType) {
        case PARAMW_EVENTINFO::ALARM_IN :
            eventLog = L"ALARM_IN 이벤트 발생";
            break;
        case PARAMW_EVENTINFO::ALARM_IN_BAD:
            eventLog = L"ALARM_IN_BAD 이벤트 발생";
            break;
        case PARAMW_EVENTINFO::MOTION:
            eventLog = L"MOTION 이벤트 발생";
            break;
        case PARAMW_EVENTINFO::VIDEOLOSS:
            eventLog = L"VIDEOLOSS 이벤트 발생";
            break;
        default:
            break;
    }

    if (L"" != eventLog) {
		eventLog.AppendFormat(L"(Msec:%d)", lpEventInfo->_tmMsec);
        rOwner.insertLog(eventLog);
    }

	bool enabledType = PARAMW_EVENTINFO::ALARM_IN == lpEventInfo->_evtType ||
					   PARAMW_EVENTINFO::MOTION == lpEventInfo->_evtType;

	if (rOwner._enableEvent && enabledType) {
		// alarm in event 발생시, 이미지를 _imageProcessor 클래스로 보낸다.
		::PostMessage(rOwner.GetSafeHwnd(), UM_WATCH_EVENTLOADED, 0, 0);
		//rOwner.captureImage();
	}
}

void IDISCALLBACK watch_statusLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
}

void IDISCALLBACK watch_deviceStatusLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam)
{
    CAmsongTesterDlg& rOwner = *CAmsongTesterDlg::_lpOwnerWnd;

    LPPARAMW_NETDEVICESTATUS lpParams = reinterpret_cast<LPPARAMW_NETDEVICESTATUS>(lParam);
    ASSERT(lpParams->_dwSize == sizeof(PARAMW_NETDEVICESTATUS));

    int  channel = static_cast<int>(wParam);
    int  nstatus;
    int  camera_status = CameraView::DISABLED;
    bool fisCovertView = rOwner._watcher.isAuthorityCovertView(hWatch, channel);
    unsigned char cameraCount = 0;

    rOwner._watcher.getProductInfo(hWatch, channel, QUERY_CAMERA_COUNT, &cameraCount, sizeof(cameraCount));

    for (int i = 0; i < cameraCount; i++) {
        nstatus = lpParams->_cameraStatus[i];
        camera_status = CameraView::DISABLED;

        switch (nstatus) {
            case PARAMW_NETDEVICESTATUS::VIDEOLOSS : 
                camera_status = CameraView::NO_VIDEO;
                break;
            case PARAMW_NETDEVICESTATUS::INACTIVE :
                camera_status = CameraView::DISABLED;
                break;
            case PARAMW_NETDEVICESTATUS::ACTIVE :
                camera_status = CameraView::ENABLED;
                break;
            case PARAMW_NETDEVICESTATUS::NOTCONNECTED :
                camera_status = CameraView::NOT_CONNECTED;
                break;
            case PARAMW_NETDEVICESTATUS::MULTISTREAM :
                camera_status = CameraView::ENABLED;
                break;
            default :
                camera_status = CameraView::DISABLED;
                break;
        }

        if (fisCovertView == false) {
            switch (lpParams->_cameraCovertLevel[i]) {
                case PARAMW_NETDEVICESTATUS::COVERT1 :
                    camera_status = CameraView::COVERT_LEVEL1;
                    break;
                case PARAMW_NETDEVICESTATUS::COVERT2 :
                    camera_status = CameraView::COVERT_LEVEL2;
                    break;
            }
        }

        rOwner._screen.setCameraState(i, camera_status);
        rOwner._screen.setCameraTitle(i, lpParams->_szCameraDescription[i]);
    }

    ::PostMessage(rOwner.GetSafeHwnd(), UM_WATCH_DEVICESTATUSLOADED, static_cast<WPARAM>(hWatch), static_cast<LPARAM>(channel));
}

/////////////////////////////////////////////////////////////////////////////

BOOL CAmsongTesterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
    _lpOwnerWnd = this;
    _fDisconnectByMe = false;
	_enableEvent = true;

    // Init Controls
    setAppStatus(APP_STATUS_DISCONNECTED);

	CString delayTime;

    _remoteAddress = theApp.GetProfileString(L"AMSONG_APP", L"RemoteAddress", L"");
    _remoteId = theApp.GetProfileString(L"AMSONG_APP", L"RemoteId", L"admin");
	delayTime = theApp.GetProfileString(L"AMSONG_APP", L"CaptureDelay", L"50");

    SetDlgItemText(IDC_EDIT_REMOTE_ADDR, _remoteAddress);
    SetDlgItemText(IDC_EDIT_REMOTE_ID, _remoteId);
    SetDlgItemText(IDC_EDIT_REMOTE_PASSWORD, _remotePassword);
	SetDlgItemText(IDC_EDIT_DELAY, delayTime);

    _screen.initialize(CRect(0, 0, 500, 280));
	_screen.Create(IDD_DIALOG_SCREENVIEW, this);
	_screen.MoveWindow(1, 1, 500, 280, FALSE);
	_screen.ShowWindow(SW_SHOW);

    // Init Watcher.
    _watchHandle = _watcher.initialize();

	_watcher.startup(_watchHandle, 16);
    _watcher.startupAudio(16, GetSafeHwnd());

	_watcher.registerCallback(_watchHandle, CALLBACK_WATCH::ONCONNECTED,        watch_onConnected);
	_watcher.registerCallback(_watchHandle, CALLBACK_WATCH::ONDISCONNECTED,     watch_onDisconnected);
	_watcher.registerCallback(_watchHandle, CALLBACK_WATCH::FRAMELOADED,        watch_frameLoaded);
	_watcher.registerCallback(_watchHandle, CALLBACK_WATCH::EVENTLOADED,        watch_eventLoaded);
	_watcher.registerCallback(_watchHandle, CALLBACK_WATCH::STATUSLOADED,       watch_statusLoaded);
    _watcher.registerCallback(_watchHandle, CALLBACK_WATCH::DEVICESTATUSLOADED, watch_deviceStatusLoaded);

    _capturedImage = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAmsongTesterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAmsongTesterDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

void CAmsongTesterDlg::OnDestroy()
{
    CDialog::OnDestroy();

    theApp.WriteProfileStringW(L"AMSONG_APP", L"RemoteAddress", _remoteAddress);
    theApp.WriteProfileStringW(L"AMSONG_APP", L"RemoteId", _remoteId);
	//theApp.WriteProfileStringW(L"AMSONG_APP", L"RemoteId", _remoteId);

    if (_watcher.isValidChannel(_channel) &&
		_watcher.isConnected(_watchHandle, _channel)) {
		_watcher.disconnect(_watchHandle, _channel);
		Sleep(200);
	}

	_watcher.cleanup(_watchHandle);
	_watcher.finalize(_watchHandle);

    _screen.shutdown();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAmsongTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAmsongTesterDlg::setAppStatus(unsigned char appStatus)
{
    _appStatus = appStatus;

    BOOL enable = TRUE;
    bool disableAll = false;
    if (APP_STATUS_CONNECTED == _appStatus) {
        enable = FALSE;
    }
    else if (APP_STATUS_CONNECTING == _appStatus ||
        APP_STATUS_DISCONNECTING == _appStatus) {
        disableAll = true;
    }

    GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(disableAll ? FALSE : enable);
    GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(disableAll ? FALSE : !enable);
    GetDlgItem(IDC_BUTTON_GEN_EVENT)->EnableWindow(disableAll ? FALSE : !enable);
	GetDlgItem(IDC_BUTTON_ENABLE_EVENT)->EnableWindow(disableAll ? FALSE : !enable);
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(disableAll ? FALSE : !enable);
    GetDlgItem(IDC_EDIT_REMOTE_ADDR)->EnableWindow(disableAll ? FALSE : enable);
    GetDlgItem(IDC_EDIT_REMOTE_ID)->EnableWindow(disableAll ? FALSE : enable);
    GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(disableAll ? FALSE : enable);
    GetDlgItem(IDC_EDIT_REMOTE_PASSWORD)->EnableWindow(disableAll ? FALSE : enable);
}

void CAmsongTesterDlg::insertLog(const CString& logMessage)
{
    int itemCount = _logList.GetCount();
    if (LB_ERR != itemCount) {
        _logList.InsertString(itemCount, logMessage);
        _logList.SendMessage(WM_VSCROLL, SB_BOTTOM);
    }
}

void CAmsongTesterDlg::captureImage()
{
    int imageWidth = _screen.imageWidth();
    int imageHeight = _screen.imageHeight();
    int imageSize = _screen.imageSize();
    if (!_capturedImage) {
        _capturedImage = (BYTE*)(new BYTE[imageSize]);
    }

    _screen.cpatureImage(_capturedImage, imageSize);
    _imageProcessor.setCapturedImage(_capturedImage, imageSize, imageWidth, imageHeight);

    if (_capturedImage) {
        delete _capturedImage;
        _capturedImage = 0;
    }
}

void CAmsongTesterDlg::OnBnClickedButtonConnect()
{
    _remotePort = 8016;

    CString log = L"접속 시도";
    insertLog(log);

    GetDlgItemText(IDC_EDIT_REMOTE_ADDR, _remoteAddress);
    GetDlgItemText(IDC_EDIT_REMOTE_ID, _remoteId);
    GetDlgItemText(IDC_EDIT_REMOTE_PASSWORD, _remotePassword);

    _channel = _watcher.connect(_watchHandle, L"AmSong", _remoteAddress, _remoteId, _remotePassword, _remotePort);
    _fDisconnectByMe = false;

    setAppStatus(APP_STATUS_CONNECTING);
}

void CAmsongTesterDlg::OnBnClickedButtonDisconnect()
{
    setAppStatus(APP_STATUS_DISCONNECTING);

    CString log = L"접속 끊기 시도";
    insertLog(log);

    if (!_watcher.isValidChannel(_channel)) {
        return;
    }

	_fDisconnectByMe = true;
	_watcher.disconnect(_watchHandle, _channel);
}

void CAmsongTesterDlg::OnBnClickedButtonGenEvent()
{
    // TODO: 해당 시점에서 이미지 캡쳐. (이벤트가 발생한것 처럼 한다.)
    //_screen.saveImage(L"test.bmp");
    //_screen.saveOriginalImage(L"test2.bmp");
    captureImage();
}

LRESULT CAmsongTesterDlg::OnWatchConnected(WPARAM wParam, LPARAM lParam)
{
    int channel = static_cast<int>(wParam);

    if (channel != _channel) {
        return 1L;
    }

    _screen.setCountLiveCamera(1);
	_screen.setScreenLayout(1);

	int select_camera = _screen.getSelectedCamera();

	BYTE setcamList[MAX_SYS_CAMERA32];
	if (_screen.isUseSingleMode() &&
		select_camera != -1) {
		setcamList[select_camera] = 1;
	} else {
		memset(setcamList, 1, sizeof(setcamList));
	}
    _watcher.setCameraList(_watchHandle, channel, setcamList, 1);

    _screen.Invalidate(FALSE);

    setAppStatus(APP_STATUS_CONNECTED);

    CString log = L"접속 완료";
    insertLog(log);

    return 0L;
}

LRESULT CAmsongTesterDlg::OnWatchDisConnected(WPARAM wParam, LPARAM lParam)
{
    int channel       = static_cast<int>(wParam);
	int whydisconnect = static_cast<int>(lParam);

    setAppStatus(APP_STATUS_DISCONNECTED);

    _screen.clearScreen();

    CString strReason = _watcher.getReasonDisconnected(whydisconnect);
    CString log;
    if (_fDisconnectByMe) {
        log.Format(L"접속 끊기 완료 (이유: %s)", strReason);
    }
    else {
        log.Format(L"접속이 끊어짐 (이유: %s)", strReason);
    }
    insertLog(log);

    return 0L;
}

LRESULT CAmsongTesterDlg::OnWatchStatusLoaded(WPARAM wParam, LPARAM lParam)
{
    return 0L;
}

LRESULT CAmsongTesterDlg::OnWatchDeviceStatusLoaded(WPARAM wParam, LPARAM lParam)
{
    IDISHWATCH hWatch = static_cast<IDISHWATCH>(wParam);
    int channel       = static_cast<int>(lParam);
    int select_camera = _screen.getSelectedCamera();

    // user_authority check ///////////////////////////////

    _dvrAuthority = _watcher.checkAuthority(_watchHandle, channel);

    bool fenable_setcolor = (_dvrAuthority & IDIS_USERAUTHORITY::AUTHORITY_COLOR_CONTROL) != 0;
    bool fenable_alarmout = (_dvrAuthority & IDIS_USERAUTHORITY::AUTHORITY_ALARM_OUT_CONTROL) != 0;
    bool fenable_ctrlptz  = (_dvrAuthority & IDIS_USERAUTHORITY::AUTHORITY_PTZ_CONTROL) != 0;

    int nUsePTZ = PARAMW_PTZCOMMAND::TYPE_USE_PTZ_NONE;
    int selected_camera = _screen.getSelectedCamera();
    if (selected_camera >= 0 &&
        selected_camera < MAX_CAMERA_COUNTS) {
            if (fenable_ctrlptz == true) {
                nUsePTZ = _watcher.getUsePTZEx(_watchHandle, channel, selected_camera);
            }
    }

    if (select_camera != -1) {
        //_dlgCtrlColor.setEnable(fenable_setcolor);
        //_dlgCtrlSetPTZ.setEnable(nUsePTZ, channel);
    }

    //_dlgCtrlAlarmOut.setEnable(fenable_alarmout);

    if (fenable_alarmout) {
        if (_watcher.isConnectedIDR(_watchHandle, channel) != true) {
            // may secure alarmout's count at CALLBACK_WATCH::IDRSTATUSLOADED callback.
            int countofalarmout = _watcher.getCountAlarmOut(hWatch, channel);
            //_dlgCtrlAlarmOut.setMaxAlarmOuts(countofalarmout);
        }
    }

    return 1L;
}

LRESULT CAmsongTesterDlg::OnWatchEventLoaded(WPARAM wParam, LPARAM lParam)
{
	_eventOccurredTick = GetTickCount();

	CString log;
	log.Format(L"이벤트발생 tick: %d", _eventOccurredTick);
    insertLog(log);

	CString str;
	GetDlgItemText(IDC_EDIT_DELAY, str);
	_captureDelayedMilisec = _ttoi(str);

	unsigned int _currentTick = GetTickCount();

	while ((_currentTick - _eventOccurredTick) < _captureDelayedMilisec) {
		// wait...
		_currentTick = GetTickCount();
	}

	log.Format(L"이미지캡쳐 tick: %d", GetTickCount());
    insertLog(log);

	captureImage();

	return 0L;
}


void CAmsongTesterDlg::OnBnClickedButtonEnableEvent()
{
	_enableEvent = !_enableEvent;

	CString buttonTitle;
	if (_enableEvent) {
		buttonTitle = L"이벤트 감지 OFF";
	}
	else {
		buttonTitle = L"이벤트 감지 ON";
	}
	SetDlgItemText(IDC_BUTTON_ENABLE_EVENT, buttonTitle);
}


void CAmsongTesterDlg::OnBnClickedButtonTest()
{
	_imageProcessor.setCapturedImage(0, 0, 0, 0, true);
}
