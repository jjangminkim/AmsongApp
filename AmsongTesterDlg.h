#ifndef _AMSONG_TESTER_DLG_H
#define _AMSONG_TESTER_DLG_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "WatchSDK_Sample.h"
#include "ScreenViewWnd.h"
#include "ImageProcessor.h"

class CAmsongTesterDlg : public CDialog {
public:
    CAmsongTesterDlg(CWnd* pParent = NULL);

    enum { IDD = IDD_AMSONGTESTER_DIALOG };

    enum {
        APP_STATUS_DISCONNECTED  = 0,
        APP_STATUS_CONNECTING,
        APP_STATUS_CONNECTED,
        APP_STATUS_DISCONNECTING,
    };

protected:
    WatchSDK_Class _watcher;
    IDISHWATCH     _watchHandle;
    CScreenViewWnd _screen;

    ImageProcessor _imageProcessor;
    BYTE*          _capturedImage;

    int            _channel;
    unsigned int   _dvrAuthority;
	bool		   _enableEvent;

    CString _remoteAddress;
    CString _remoteId;
    CString _remotePassword;
    int     _remotePort;

    bool _fDisconnectByMe;
    unsigned char _appStatus;

	unsigned int _captureDelayedMilisec;
	unsigned int _eventOccurredTick;

    CListBox _logList;

private:
	int _moveGuidelineSize;

	Amsong::Triangle _bigTriangle;
	Amsong::Triangle _middleTriangle;
	Amsong::Triangle _smallTriangle;

	CRect _pie1;
	CRect _pie2;
	CRect _pie3;

public:
	static CAmsongTesterDlg* _lpOwnerWnd;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

protected:
    void setAppStatus(unsigned char appStatus);
    void insertLog(const CString& logMessage);
    void captureImage();
	void insertObjects();
	void saveObjects();

	void setPointToEditBox();
	void moveAllGuidelineshorizontally(int steps);
	void moveAllGuidelinesVertically(int steps);

public:
    afx_msg void OnBnClickedButtonConnect();
    afx_msg void OnBnClickedButtonDisconnect();
    afx_msg void OnBnClickedButtonGenEvent();
	afx_msg void OnBnClickedButtonEnableEvent();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonLineApply();
	afx_msg void OnBnClickedButtonLineSave();
	afx_msg void OnBnClickedButtonSaveImage();

    afx_msg LRESULT OnWatchConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWatchDisConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWatchStatusLoaded(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnWatchDeviceStatusLoaded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWatchEventLoaded(WPARAM wParam, LPARAM lParam);

public:
    friend void IDISCALLBACK watch_onConnected(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);
	friend void IDISCALLBACK watch_onDisconnected(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);
	friend void IDISCALLBACK watch_frameLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);
	friend void IDISCALLBACK watch_eventLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);
	friend void IDISCALLBACK watch_statusLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);
    friend void IDISCALLBACK watch_deviceStatusLoaded(IDISHWATCH hWatch, IDISWPARAM wParam, IDISLPARAM lParam);

	afx_msg void OnBnClickedButtonMoveAllLeft();
	afx_msg void OnBnClickedButtonMoveAllUp();
	afx_msg void OnBnClickedButtonMoveAllDown();
	afx_msg void OnBnClickedButtonMoveAllRight();
};

#endif  // _AMSONG_TESTER_DLG_H
