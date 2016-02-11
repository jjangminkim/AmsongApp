// ScreenViewWnd.h : header file
//

#ifndef _SCREENVIEW_WINDOW_H_
#define _SCREENVIEW_WINDOW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vfw.h>
#include "IDIS_Define.h"
#include "DecoderSDK_Sample.h"
#include "ScreenFormatter.h"
#include "AppTypes.h"

//////////////////////////////////////////////////////////////////////////

const int MAX_CAMERA_COUNTS = 36;
const int MAX_FRAME_SIZE    = IDIS_FRAMETYPE::MAX_SIZE_CX * IDIS_FRAMETYPE::MAX_SIZE_CY * 4; // 32bit

//////////////////////////////////////////////////////////////////////////

class CameraView
{
// Attributes
private:
	CRect		_rctCamera;		// camera rect
	CRect		_rctImage;		// image  rect
	CString		_strCaption;	// camera caption
	int			_cameraState;	// camera status
	bool		_fisVisible;

// Constructions
public:
	CameraView(void)
		: _strCaption(_T(""))
		, _cameraState(DISABLED)
	{

	}

	enum _camera_status {
		STATUS_NONE = -1,
		NO_VIDEO,
		DISABLED,
		ENABLED,
		NOT_CONNECTED,
		COVERT_LEVEL1,
		COVERT_LEVEL2 
	};

// Operations
public:
	void setRect(const CRect& rect)			{ _rctCamera = rect; _fisVisible = true; }
	void setRectImage(const CRect& rect)	{ _rctImage  = rect; }
	void setState(int status)				{ _cameraState = status; }
	void setTitle(LPCWSTR lpszTitle)		{ _strCaption = lpszTitle; }
	void setVisible(bool fvisible)			{ _fisVisible = fvisible; }

	const CRect& rect(void)			const	{ return _rctCamera; }
	const CRect& rectImage(void)	const	{ return _rctImage; }
	int  status(void)				const	{ return _cameraState; }
	LPCTSTR title(void)				const	{ return _strCaption; }
	bool is_visible(void)			const	{ return _fisVisible; }
	bool is_enable(void)			const	{ return _cameraState == ENABLED ? true : false; }
	bool ptInRect(const POINT& rpt)	const;
	void resetCamera(void);
};

//////////////////////////////////////////////////////////////////////////

class FrameQueue
{
public:
	class FrameDataElement
	{
	// Attributes
	public:
		PARAMWS_FRAMEINFO _frameInfo;
		LPBYTE            _lpImage;
		UINT			  _sizeofBuffer;

		enum { 
			THRESHOLD_FRAME_SIZE = 256 * 1024,	// 256 KBytes
			BUFFER_EXTRA_SPACE   = 1024			// 1024 Bytes
		};

	// Constructions
	public:
		FrameDataElement(void);
		~FrameDataElement(void);

	// Operations
	public:
		void setData(const PARAMWS_FRAMEINFO& rFrame, LPBYTE lpBuffer);
	};

// Constructions
public:
	FrameQueue(int MaxSize = 512);
	~FrameQueue(void);

// Attributes
private:
	FrameDataElement* _lpFrameInfo;
	bool _clearBuffer[MAX_CAMERA_COUNTS];

	int _front;
	int _rear;
	int _queueSize;
	int _maxSize;

	mutable CCriticalSection _sync_queue;

// Operations
public:
	void clear(void);
	bool put(const PARAMWS_FRAMEINFO& rFrame);
	bool get(FrameDataElement& rFrameInfo);
	int	 getSize(void) const { return _queueSize; }
};

//////////////////////////////////////////////////////////////////////////

inline FrameQueue::FrameDataElement::FrameDataElement()
	: _sizeofBuffer(THRESHOLD_FRAME_SIZE)
{
	_lpImage = new BYTE[_sizeofBuffer];
}

inline FrameQueue::FrameDataElement::~FrameDataElement()
{
	SAFE_DELETE_ARRAY(_lpImage);
}

inline void FrameQueue::FrameDataElement::setData(const PARAMWS_FRAMEINFO& rFrame, LPBYTE lpBuffer)
{
	_frameInfo = rFrame;

	const UINT sizeofFrame = rFrame._szBuffer;
	if (sizeofFrame + BUFFER_EXTRA_SPACE > _sizeofBuffer) {
		_sizeofBuffer = sizeofFrame;
		SAFE_DELETE_ARRAY(_lpImage);
		_lpImage = new BYTE[_sizeofBuffer + BUFFER_EXTRA_SPACE];
	}

	memcpy(_lpImage, lpBuffer, sizeofFrame);
}

//////////////////////////////////////////////////////////////////////////

class CScreenViewWnd : public CDialog
{
	DECLARE_DYNAMIC(CScreenViewWnd)

// Constructions
public:
	CScreenViewWnd(CWnd* pParent = NULL);
	virtual ~CScreenViewWnd(void);

	enum { IDD = IDD_DIALOG_SCREENVIEW };

// Attributes
private:
	DecoderSDK_Class	_decoders;
	IDISHDECODER		_hDecoder;
	HDRAWDIB			_hDrawDib;
	CBitmap				_bmpCanvas;
	BITMAPINFOHEADER	_bmpInfohead;
	CCriticalSection	_sync_drawing;

	FrameQueue			_frameQueue;
	CameraView*			_cameraView;
	ScreenFormatter		_fmtScreen;

	LPBYTE				_imageBuffer;
	CRect				_rectClient;
	CRect				_rectScreen;
	CFont				_fontText;
    int                 _imageHeight;
    int                 _imageWidth;

	int					_selectCamera;
	int					_countCamera;
	int					_countLiveCamera;
	bool				_fuse1x1Mode;
	bool				_fuseAspectRatio;

	Triangle _bigTriangle;
	Triangle _middleTriangle;
	Triangle _smallTriangle;

	CRect _pie1;
	CRect _pie2;
	CRect _pie3;
	CRect _pie4;

// Getter, Setter
public:
    int imageWidth()  { return _imageWidth;  }
    int imageHeight() { return _imageHeight; }
    int imageSize()   { return _imageWidth * _imageHeight * 4; }

	void setBigTriangle(const Triangle& triangle) { _bigTriangle = triangle; }
	void setMiddleTriangle(const Triangle& triangle) { _middleTriangle = triangle; }
	void setSmallTriangle(const Triangle& triangle) { _smallTriangle = triangle; }
	void setPies(const CRect& pie1, const CRect& pie2, const CRect& pie3, const CRect& pie4);

// Operations
public:
	void initialize(const CRect& rctbound = CRect(0, 0, 640, 480));
	void shutdown(void);

	void drawImage(int camera,
						LPBYTE lpImage,
						const CSize& size,
						SDK_TIME_T time);

	bool drawText(CDC *lpDC,
						LPCTSTR lpszText,
						const CRect& rctDraw,
						UINT nFormat,
						COLORREF clrText = RGB(255, 255, 255),
						COLORREF clrBack = RGB(0, 0, 0));
	bool drawObjects(CDC *pDC);

	void imageAspectRatio(int cx, int cy, const CRect& rctin, CRect& rctout);
    void saveImage(TCHAR* path);
    void saveOriginalImage(TCHAR* path);
    void cpatureImage(BYTE* data, int size);

	void updateStatus(int camera);

	int  findCameraByPoint(const CPoint& rpoint);

	void setScreenLayout(int countofCamera);
	void setScreenLayout(int typeLayout, int start, const CRect& rctBound);

	void setCameraState(int camera, int status);
	void setCameraTitle(int camera, LPCSTR  lpszTitle);
	void setCameraTitle(int camera, LPCWSTR lpszTitle);

	void setCountLiveCamera(int countofCamera);
	void setUseAspectRatio(bool factivate);

	int  getSelectedCamera(void) const;
	int  getCameraState(int camera) const;
	LPCTSTR getCameraTitle(int camera) const;
	bool isUseSingleMode(void) const;
	bool isUseAspectRatio(void) const;

	void clearScreen(void);

	void setDeInterlaceFilter(int typeofFilter);

	bool putLoadedFrame(const PARAMWS_FRAMEINFO& rFrame);

protected:
	bool valid_camera(int camera) const;

// ThreadFunc
public:
	HANDLE _hScreenThread;
	bool   _fScreenThread;

	bool initScreenThread(void);
	bool exitScreenThread(void);
	bool IsRunningThread(void);

	DWORD screenThread(void);
	static DWORD WINAPI screenThreadProc(LPVOID lpParam);

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////

inline void CScreenViewWnd::setPies(const CRect& pie1, const CRect& pie2, const CRect& pie3, const CRect& pie4)
{
	_pie1 = pie1;
	_pie2 = pie2;
	_pie3 = pie3;
	_pie4 = pie4;
}

inline bool CScreenViewWnd::putLoadedFrame(const PARAMWS_FRAMEINFO& rFrame)
{
	/* Length of buffer need extra space.
	   Since decoder may use extra space, frame buffer
	   need more 1024 bytes at least.
	   Recommendable buffer size is _szBuffer + (1024 or over). */

	return _frameQueue.put(rFrame);
}

inline bool CScreenViewWnd::valid_camera(int camera) const
{ 
	return (camera < 0 ||
			camera >= _countCamera) ? false : true;
}

inline int  CScreenViewWnd::getSelectedCamera(void) const
{ 
	return _selectCamera; 
}

inline int  CScreenViewWnd::getCameraState(int camera) const
{
	return valid_camera(camera) ? 
		_cameraView[camera].status() : CameraView::STATUS_NONE;
}

inline LPCTSTR CScreenViewWnd::getCameraTitle(int camera) const
{
	return valid_camera(camera) ? 
		_cameraView[camera].title() : _T("");
}

inline bool CScreenViewWnd::isUseSingleMode(void) const
{ 
	return _fuse1x1Mode; 
}

inline bool CScreenViewWnd::isUseAspectRatio(void) const
{
	return _fuseAspectRatio;
}

//////////////////////////////////////////////////////////////////////////

#endif	// !_SCREENVIEW_WINDOW_H_
