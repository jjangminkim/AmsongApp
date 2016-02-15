
// AmsongTesterDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AmsongTester.h"
#include "AppTypes.h"
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
	, _moveGuidelineSize(1)
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
	ON_BN_CLICKED(IDC_BUTTON_LINE_APPLY, &CAmsongTesterDlg::OnBnClickedButtonLineApply)
	ON_BN_CLICKED(IDC_BUTTON_LINE_SAVE, &CAmsongTesterDlg::OnBnClickedButtonLineSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_IMAGE, &CAmsongTesterDlg::OnBnClickedButtonSaveImage)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_ALL_LEFT, &CAmsongTesterDlg::OnBnClickedButtonMoveAllLeft)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_ALL_UP, &CAmsongTesterDlg::OnBnClickedButtonMoveAllUp)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_ALL_DOWN, &CAmsongTesterDlg::OnBnClickedButtonMoveAllDown)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_ALL_RIGHT, &CAmsongTesterDlg::OnBnClickedButtonMoveAllRight)
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

    // �ϴ� AUDIO FRAME�� �����Ѵ�.
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
            eventLog = L"ALARM_IN �̺�Ʈ �߻�";
            break;
        case PARAMW_EVENTINFO::ALARM_IN_BAD:
            eventLog = L"ALARM_IN_BAD �̺�Ʈ �߻�";
            break;
        case PARAMW_EVENTINFO::MOTION:
            eventLog = L"MOTION �̺�Ʈ �߻�";
            break;
        case PARAMW_EVENTINFO::VIDEOLOSS:
            eventLog = L"VIDEOLOSS �̺�Ʈ �߻�";
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
		// alarm in event �߻���, �̹����� _imageProcessor Ŭ������ ������.
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

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	MoveWindow(0,0,1580,760);

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    _lpOwnerWnd = this;
    _fDisconnectByMe = false;
	_enableEvent = true;
	_moveGuidelineSize = 1;

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

	// ���̵������ ���� POINT ����.
	// IDC_EDIT_T1_P1_X
	CString p1_x = theApp.GetProfileString(L"AMSONG_APP", L"T1_P1_X", L"240");
	CString p1_y = theApp.GetProfileString(L"AMSONG_APP", L"T1_P1_Y", L"360");
	CString p2_x = theApp.GetProfileString(L"AMSONG_APP", L"T1_P2_X", L"1040");
	CString p2_y = theApp.GetProfileString(L"AMSONG_APP", L"T1_P2_Y", L"360");
	CString p3_x = theApp.GetProfileString(L"AMSONG_APP", L"T1_P3_X", L"640");
	CString p3_y = theApp.GetProfileString(L"AMSONG_APP", L"T1_P3_Y", L"700");
	SetDlgItemText(IDC_EDIT_T1_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_T1_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_T1_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_T1_P2_Y, p2_y);
	SetDlgItemText(IDC_EDIT_T1_P3_X, p3_x);
	SetDlgItemText(IDC_EDIT_T1_P3_Y, p3_y);

	p1_x = theApp.GetProfileString(L"AMSONG_APP", L"T2_P1_X", L"340");
	p1_y = theApp.GetProfileString(L"AMSONG_APP", L"T2_P1_Y", L"360");
	p2_x = theApp.GetProfileString(L"AMSONG_APP", L"T2_P2_X", L"940");
	p2_y = theApp.GetProfileString(L"AMSONG_APP", L"T2_P2_Y", L"360");
	p3_x = theApp.GetProfileString(L"AMSONG_APP", L"T2_P3_X", L"640");
	p3_y = theApp.GetProfileString(L"AMSONG_APP", L"T2_P3_Y", L"600");
	SetDlgItemText(IDC_EDIT_T2_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_T2_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_T2_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_T2_P2_Y, p2_y);
	SetDlgItemText(IDC_EDIT_T2_P3_X, p3_x);
	SetDlgItemText(IDC_EDIT_T2_P3_Y, p3_y);

	p1_x = theApp.GetProfileString(L"AMSONG_APP", L"T3_P1_X", L"440");
	p1_y = theApp.GetProfileString(L"AMSONG_APP", L"T3_P1_Y", L"360");
	p2_x = theApp.GetProfileString(L"AMSONG_APP", L"T3_P2_X", L"840");
	p2_y = theApp.GetProfileString(L"AMSONG_APP", L"T3_P2_Y", L"360");
	p3_x = theApp.GetProfileString(L"AMSONG_APP", L"T3_P3_X", L"640");
	p3_y = theApp.GetProfileString(L"AMSONG_APP", L"T3_P3_Y", L"500");
	SetDlgItemText(IDC_EDIT_T3_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_T3_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_T3_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_T3_P2_Y, p2_y);
	SetDlgItemText(IDC_EDIT_T3_P3_X, p3_x);
	SetDlgItemText(IDC_EDIT_T3_P3_Y, p3_y);

	p1_x = theApp.GetProfileString(L"AMSONG_APP", L"C1_P1_X", L"240");
	p1_y = theApp.GetProfileString(L"AMSONG_APP", L"C1_P1_Y", L"20");
	p2_x = theApp.GetProfileString(L"AMSONG_APP", L"C1_P2_X", L"1040");
	p2_y = theApp.GetProfileString(L"AMSONG_APP", L"C1_P2_Y", L"700");
	SetDlgItemText(IDC_EDIT_C1_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_C1_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_C1_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_C1_P2_Y, p2_y);

	p1_x = theApp.GetProfileString(L"AMSONG_APP", L"C2_P1_X", L"340");
	p1_y = theApp.GetProfileString(L"AMSONG_APP", L"C2_P1_Y", L"120");
	p2_x = theApp.GetProfileString(L"AMSONG_APP", L"C2_P2_X", L"940");
	p2_y = theApp.GetProfileString(L"AMSONG_APP", L"C2_P2_Y", L"600");
	SetDlgItemText(IDC_EDIT_C2_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_C2_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_C2_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_C2_P2_Y, p2_y);

	p1_x = theApp.GetProfileString(L"AMSONG_APP", L"C3_P1_X", L"440");
	p1_y = theApp.GetProfileString(L"AMSONG_APP", L"C3_P1_Y", L"220");
	p2_x = theApp.GetProfileString(L"AMSONG_APP", L"C3_P2_X", L"840");
	p2_y = theApp.GetProfileString(L"AMSONG_APP", L"C3_P2_Y", L"500");
	SetDlgItemText(IDC_EDIT_C3_P1_X, p1_x);
	SetDlgItemText(IDC_EDIT_C3_P1_Y, p1_y);
	SetDlgItemText(IDC_EDIT_C3_P2_X, p2_x);
	SetDlgItemText(IDC_EDIT_C3_P2_Y, p2_y);

	CRect thisRect;
	this->GetWindowRect(&thisRect);

    _screen.initialize(CRect(0, 0, 1280, 720));
	_screen.Create(IDD_DIALOG_SCREENVIEW, this);
	_screen.MoveWindow(thisRect.left + 282, 1, 1280, 720, FALSE);
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAmsongTesterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	GetDlgItem(IDC_BUTTON_LINE_APPLY)->EnableWindow(disableAll ? FALSE : !enable);
	GetDlgItem(IDC_BUTTON_LINE_SAVE)->EnableWindow(disableAll ? FALSE : !enable);
	GetDlgItem(IDC_BUTTON_SAVE_IMAGE)->EnableWindow(disableAll ? FALSE : !enable);
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

	Amsong::Point hitPoint = _imageProcessor.detectCircle();

	// ����׿� �׽�Ʈ.
	//hitPoint.x = 640;
	//hitPoint.y = 360;

	_screen.setHitPoint(hitPoint);

	if (0 != hitPoint.x && 0 != hitPoint.y) {
		COLORREF colorOfHitPoint = _imageProcessor.getColorOfPointFromReferImage(hitPoint);
		CString message;
		
		// ������ �׽�Ʈ.
		COLORREF third	= RGB(237, 249, 0);
		COLORREF second = RGB(0, 255, 6);
		COLORREF first	= RGB(255, 182, 0);
		COLORREF out	= RGB(53, 53, 53);

		if (third == colorOfHitPoint) {
			message = _T("3��Ÿ");
		}
		else if (second == colorOfHitPoint) {
			message = _T("2��Ÿ");
		}
		else if (first == colorOfHitPoint) {
			message = _T("1��Ÿ");
		}
		else if (out == colorOfHitPoint) {
			message = _T("�ƿ�");
		}
		else {
			message = _T("��Ʈ����ũ �Ǵ� ��");
		}

		insertLog(message);
	}

    if (_capturedImage) {
        delete _capturedImage;
        _capturedImage = 0;
    }
}

void CAmsongTesterDlg::insertObjects()
{
	CString p1_x;
	CString p1_y;
	CString p2_x;
	CString p2_y;
	CString p3_x;
	CString p3_y;
	GetDlgItemText(IDC_EDIT_T1_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T1_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T1_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T1_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T1_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T1_P3_Y, p3_y);
	_bigTriangle = Amsong::Triangle(
		Amsong::Point(_ttoi(p1_x), _ttoi(p1_y)),
		Amsong::Point(_ttoi(p2_x), _ttoi(p2_y)),
		Amsong::Point(_ttoi(p3_x), _ttoi(p3_y)));

	GetDlgItemText(IDC_EDIT_T2_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T2_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T2_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T2_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T2_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T2_P3_Y, p3_y);
	_middleTriangle = Amsong::Triangle(
		Amsong::Point(_ttoi(p1_x), _ttoi(p1_y)),
		Amsong::Point(_ttoi(p2_x), _ttoi(p2_y)),
		Amsong::Point(_ttoi(p3_x), _ttoi(p3_y)));

	GetDlgItemText(IDC_EDIT_T3_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T3_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T3_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T3_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T3_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T3_P3_Y, p3_y);
	_smallTriangle = Amsong::Triangle(
		Amsong::Point(_ttoi(p1_x), _ttoi(p1_y)),
		Amsong::Point(_ttoi(p2_x), _ttoi(p2_y)),
		Amsong::Point(_ttoi(p3_x), _ttoi(p3_y)));

	GetDlgItemText(IDC_EDIT_C1_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C1_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C1_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C1_P2_Y, p2_y);
	_pie1 = CRect(_ttoi(p1_x), _ttoi(p1_y), _ttoi(p2_x), _ttoi(p2_y));

	GetDlgItemText(IDC_EDIT_C2_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C2_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C2_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C2_P2_Y, p2_y);
	_pie2 = CRect(_ttoi(p1_x), _ttoi(p1_y), _ttoi(p2_x), _ttoi(p2_y));

	GetDlgItemText(IDC_EDIT_C3_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C3_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C3_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C3_P2_Y, p2_y);
	_pie3 = CRect(_ttoi(p1_x), _ttoi(p1_y), _ttoi(p2_x), _ttoi(p2_y));

	_screen.setBigTriangle(_bigTriangle);
	_screen.setMiddleTriangle(_middleTriangle);
	_screen.setSmallTriangle(_smallTriangle);
	_screen.setPies(_pie1, _pie2, _pie3);
}

void CAmsongTesterDlg::saveObjects()
{
	CString p1_x;
	CString p1_y;
	CString p2_x;
	CString p2_y;
	CString p3_x;
	CString p3_y;

	GetDlgItemText(IDC_EDIT_T1_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T1_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T1_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T1_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T1_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T1_P3_Y, p3_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P2_Y", p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P3_X", p3_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T1_P3_Y", p3_y);

	GetDlgItemText(IDC_EDIT_T2_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T2_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T2_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T2_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T2_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T2_P3_Y, p3_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P2_Y", p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P3_X", p3_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T2_P3_Y", p3_y);
	
	GetDlgItemText(IDC_EDIT_T3_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_T3_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_T3_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_T3_P2_Y, p2_y);
	GetDlgItemText(IDC_EDIT_T3_P3_X, p3_x);
	GetDlgItemText(IDC_EDIT_T3_P3_Y, p3_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P2_Y", p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P3_X", p3_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"T3_P3_Y", p3_y);

	GetDlgItemText(IDC_EDIT_C1_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C1_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C1_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C1_P2_Y, p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C1_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C1_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C1_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C1_P2_Y", p2_y);
	
	GetDlgItemText(IDC_EDIT_C2_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C2_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C2_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C2_P2_Y, p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C2_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C2_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C2_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C2_P2_Y", p2_y);
	
	GetDlgItemText(IDC_EDIT_C3_P1_X, p1_x);
	GetDlgItemText(IDC_EDIT_C3_P1_Y, p1_y);
	GetDlgItemText(IDC_EDIT_C3_P2_X, p2_x);
	GetDlgItemText(IDC_EDIT_C3_P2_Y, p2_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C3_P1_X", p1_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C3_P1_Y", p1_y);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C3_P2_X", p2_x);
	theApp.WriteProfileStringW(L"AMSONG_APP", L"C3_P2_Y", p2_y);
}

void CAmsongTesterDlg::setPointToEditBox()
{
	CString temp;
	temp.Format(_T("%d"), _bigTriangle.topLeft.x);
	SetDlgItemText(IDC_EDIT_T1_P1_X, temp);
	temp.Format(_T("%d"), _bigTriangle.topLeft.y);
	SetDlgItemText(IDC_EDIT_T1_P1_Y, temp);
	temp.Format(_T("%d"), _bigTriangle.topRight.x);
	SetDlgItemText(IDC_EDIT_T1_P2_X, temp);
	temp.Format(_T("%d"), _bigTriangle.topRight.y);
	SetDlgItemText(IDC_EDIT_T1_P2_Y, temp);
	temp.Format(_T("%d"), _bigTriangle.bottomCenter.x);
	SetDlgItemText(IDC_EDIT_T1_P3_X, temp);
	temp.Format(_T("%d"), _bigTriangle.bottomCenter.y);
	SetDlgItemText(IDC_EDIT_T1_P3_Y, temp);

	temp.Format(_T("%d"), _middleTriangle.topLeft.x);
	SetDlgItemText(IDC_EDIT_T2_P1_X, temp);
	temp.Format(_T("%d"), _middleTriangle.topLeft.y);
	SetDlgItemText(IDC_EDIT_T2_P1_Y, temp);
	temp.Format(_T("%d"), _middleTriangle.topRight.x);
	SetDlgItemText(IDC_EDIT_T2_P2_X, temp);
	temp.Format(_T("%d"), _middleTriangle.topRight.y);
	SetDlgItemText(IDC_EDIT_T2_P2_Y, temp);
	temp.Format(_T("%d"), _middleTriangle.bottomCenter.x);
	SetDlgItemText(IDC_EDIT_T2_P3_X, temp);
	temp.Format(_T("%d"), _middleTriangle.bottomCenter.y);
	SetDlgItemText(IDC_EDIT_T2_P3_Y, temp);

	temp.Format(_T("%d"), _smallTriangle.topLeft.x);
	SetDlgItemText(IDC_EDIT_T3_P1_X, temp);
	temp.Format(_T("%d"), _smallTriangle.topLeft.y);
	SetDlgItemText(IDC_EDIT_T3_P1_Y, temp);
	temp.Format(_T("%d"), _smallTriangle.topRight.x);
	SetDlgItemText(IDC_EDIT_T3_P2_X, temp);
	temp.Format(_T("%d"), _smallTriangle.topRight.y);
	SetDlgItemText(IDC_EDIT_T3_P2_Y, temp);
	temp.Format(_T("%d"), _smallTriangle.bottomCenter.x);
	SetDlgItemText(IDC_EDIT_T3_P3_X, temp);
	temp.Format(_T("%d"), _smallTriangle.bottomCenter.y);
	SetDlgItemText(IDC_EDIT_T3_P3_Y, temp);

	temp.Format(_T("%d"), _pie1.left);
	SetDlgItemText(IDC_EDIT_C1_P1_X, temp);
	temp.Format(_T("%d"), _pie1.top);
	SetDlgItemText(IDC_EDIT_C1_P1_Y, temp);
	temp.Format(_T("%d"), _pie1.right);
	SetDlgItemText(IDC_EDIT_C1_P2_X, temp);
	temp.Format(_T("%d"), _pie1.bottom);
	SetDlgItemText(IDC_EDIT_C1_P2_Y, temp);

	temp.Format(_T("%d"), _pie2.left);
	SetDlgItemText(IDC_EDIT_C2_P1_X, temp);
	temp.Format(_T("%d"), _pie2.top);
	SetDlgItemText(IDC_EDIT_C2_P1_Y, temp);
	temp.Format(_T("%d"), _pie2.right);
	SetDlgItemText(IDC_EDIT_C2_P2_X, temp);
	temp.Format(_T("%d"), _pie2.bottom);
	SetDlgItemText(IDC_EDIT_C2_P2_Y, temp);

	temp.Format(_T("%d"), _pie3.left);
	SetDlgItemText(IDC_EDIT_C3_P1_X, temp);
	temp.Format(_T("%d"), _pie3.top);
	SetDlgItemText(IDC_EDIT_C3_P1_Y, temp);
	temp.Format(_T("%d"), _pie3.right);
	SetDlgItemText(IDC_EDIT_C3_P2_X, temp);
	temp.Format(_T("%d"), _pie3.bottom);
	SetDlgItemText(IDC_EDIT_C3_P2_Y, temp);
}

void CAmsongTesterDlg::moveAllGuidelineshorizontally(int steps)
{
	_bigTriangle.bottomCenter.x += steps;
	_bigTriangle.topLeft.x += steps;
	_bigTriangle.topRight.x += steps;

	_middleTriangle.bottomCenter.x += steps;
	_middleTriangle.topLeft.x += steps;
	_middleTriangle.topRight.x += steps;

	_smallTriangle.bottomCenter.x += steps;
	_smallTriangle.topLeft.x += steps;
	_smallTriangle.topRight.x += steps;

	_pie1.left += steps;
	_pie1.right += steps;
	_pie2.left += steps;
	_pie2.right += steps;
	_pie3.left += steps;
	_pie3.right += steps;

	setPointToEditBox();

	_screen.setBigTriangle(_bigTriangle);
	_screen.setMiddleTriangle(_middleTriangle);
	_screen.setSmallTriangle(_smallTriangle);
	_screen.setPies(_pie1, _pie2, _pie3);
}

void CAmsongTesterDlg::moveAllGuidelinesVertically(int steps)
{
	_bigTriangle.bottomCenter.y += steps;
	_bigTriangle.topLeft.y += steps;
	_bigTriangle.topRight.y += steps;

	_middleTriangle.bottomCenter.y += steps;
	_middleTriangle.topLeft.y += steps;
	_middleTriangle.topRight.y += steps;

	_smallTriangle.bottomCenter.y += steps;
	_smallTriangle.topLeft.y += steps;
	_smallTriangle.topRight.y += steps;

	_pie1.top += steps;
	_pie1.bottom += steps;
	_pie2.top += steps;
	_pie2.bottom += steps;
	_pie3.top += steps;
	_pie3.bottom += steps;

	setPointToEditBox();

	_screen.setBigTriangle(_bigTriangle);
	_screen.setMiddleTriangle(_middleTriangle);
	_screen.setSmallTriangle(_smallTriangle);
	_screen.setPies(_pie1, _pie2, _pie3);
}

void CAmsongTesterDlg::OnBnClickedButtonConnect()
{
    _remotePort = 8016;

    CString log = L"���� �õ�";
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

    CString log = L"���� ���� �õ�";
    insertLog(log);

    if (!_watcher.isValidChannel(_channel)) {
        return;
    }

	_fDisconnectByMe = true;
	_watcher.disconnect(_watchHandle, _channel);
}

void CAmsongTesterDlg::OnBnClickedButtonGenEvent()
{
    // TODO: �ش� �������� �̹��� ĸ��. (�̺�Ʈ�� �߻��Ѱ� ó�� �Ѵ�.)
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

    CString log = L"���� �Ϸ�";
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
        log.Format(L"���� ���� �Ϸ� (����: %s)", strReason);
    }
    else {
        log.Format(L"������ ������ (����: %s)", strReason);
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
	log.Format(L"�̺�Ʈ�߻� tick: %d", _eventOccurredTick);
    insertLog(log);

	CString str;
	GetDlgItemText(IDC_EDIT_DELAY, str);
	_captureDelayedMilisec = _ttoi(str);

	unsigned int _currentTick = GetTickCount();

	while ((_currentTick - _eventOccurredTick) < _captureDelayedMilisec) {
		// wait...
		_currentTick = GetTickCount();
	}

	log.Format(L"�̹���ĸ�� tick: %d", GetTickCount());
    insertLog(log);

	captureImage();

	return 0L;
}

void CAmsongTesterDlg::OnBnClickedButtonEnableEvent()
{
	_enableEvent = !_enableEvent;

	CString buttonTitle;
	if (_enableEvent) {
		buttonTitle = L"�̺�Ʈ ���� OFF";
	}
	else {
		buttonTitle = L"�̺�Ʈ ���� ON";
	}
	SetDlgItemText(IDC_BUTTON_ENABLE_EVENT, buttonTitle);
}

void CAmsongTesterDlg::OnBnClickedButtonTest()
{
	_imageProcessor.setCapturedImage(0, 0, 0, 0, true);
}

void CAmsongTesterDlg::OnBnClickedButtonLineApply()
{
	insertObjects();
}

void CAmsongTesterDlg::OnBnClickedButtonLineSave()
{
	saveObjects();
}

void CAmsongTesterDlg::OnBnClickedButtonSaveImage()
{
	_screen.saveImage(_T("savedImage.bmp"));
}


void CAmsongTesterDlg::OnBnClickedButtonMoveAllLeft()
{
	moveAllGuidelineshorizontally(_moveGuidelineSize * (-1));
}


void CAmsongTesterDlg::OnBnClickedButtonMoveAllUp()
{
	moveAllGuidelinesVertically(_moveGuidelineSize * (-1));
}


void CAmsongTesterDlg::OnBnClickedButtonMoveAllDown()
{
	moveAllGuidelinesVertically(_moveGuidelineSize);
}


void CAmsongTesterDlg::OnBnClickedButtonMoveAllRight()
{
	moveAllGuidelineshorizontally(_moveGuidelineSize);
}
