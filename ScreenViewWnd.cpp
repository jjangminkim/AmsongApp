// ScreenViewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "AmsongTester.h"
#include "AmsongTesterDlg.h"
#include "ScreenViewWnd.h"
#include "ShapeManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "vfw32.lib")

using namespace Gdiplus;

//////////////////////////////////////////////////////////////////////////

class CMemDC
{
// Attributes
private:
	CDC		 _dc;
	CBitmap* _pbmpPrev;
	bool     _fbmpCreate;

// Constructions
public:
	CMemDC() 
		: _pbmpPrev(NULL), _fbmpCreate(false)
	{ }
	CMemDC(CDC *pDC, CBitmap *pBm)
		: _pbmpPrev(NULL), _fbmpCreate(false)
	{
		CreateDC(pDC, pBm);
	}
	~CMemDC() 
	{	
		DeleteDC();
	}

// Forbidden
private:
	CMemDC(const CMemDC& rother);
	CMemDC& operator = (const CMemDC& rother);

// Operations
public:
	void CreateDC(CDC* pDC, CBitmap* pBmp)
	{
		ASSERT(_pbmpPrev == NULL && _dc.m_hDC == NULL);
		_dc.CreateCompatibleDC(pDC);
		_pbmpPrev = _dc.SelectObject(pBmp);
	}
	void CreateDC(CDC* pDC, int width, int height)
	{
		ASSERT(_pbmpPrev == NULL && _dc.m_hDC == NULL);
		CBitmap* pBmp = new CBitmap();
		_fbmpCreate = true;

		_dc.CreateCompatibleDC(pDC);
		pBmp->CreateCompatibleBitmap(pDC, width, height);
		_pbmpPrev = _dc.SelectObject(pBmp);
	}
	void DeleteDC()
	{
		if (_pbmpPrev) {
			CBitmap* ptemp = _dc.SelectObject(_pbmpPrev);
			if (_fbmpCreate) {
				ptemp->DeleteObject();
				delete ptemp;
			}
			_pbmpPrev   = NULL;
			_fbmpCreate = false;
		}
		if (_dc.m_hDC) {
			_dc.DeleteDC();
		}
	}

// Implementations
public:
	CDC* operator->()    { return &_dc; }
	CDC* operator&()     { return &_dc; }
	operator HDC() const { return _dc.GetSafeHdc(); }
};

//////////////////////////////////////////////////////////////////////////

FrameQueue::FrameQueue(int max_elems)
	: _front(0)
	, _rear(0)
	, _queueSize(0)
	, _maxSize(max_elems)
{
	_lpFrameInfo = new FrameDataElement[_maxSize];
	memset(_clearBuffer, true, sizeof(_clearBuffer));
}

FrameQueue::~FrameQueue(void)
{
	SAFE_DELETE_ARRAY(_lpFrameInfo);
}

//////////////////////////////////////////////////////////////////////////

void FrameQueue::clear(void)
{
	_sync_queue.Lock();

	_front = _rear;
	_queueSize = 0;

	memset(_clearBuffer, true, sizeof(_clearBuffer));

	_sync_queue.Unlock();
}

bool FrameQueue::put(const PARAMWS_FRAMEINFO& rFrame)
{
	_sync_queue.Lock();

	int hostcam = rFrame._hostcamera;
	// put i-frame when buffer initialized
	if (_clearBuffer[hostcam] == true) {
		if (rFrame._frameType == IDIS_FRAMETYPE::I_FRAME) {
			_clearBuffer[hostcam] = false;
		}
		else {
			_sync_queue.Unlock();
			return true;
		}
	}

	// full_check
	if ((_rear + 1) % _maxSize == _front) {
		_sync_queue.Unlock();
		return false;
	}

	_lpFrameInfo[_rear].setData(rFrame, rFrame._lpBuffer);
	_rear = ++_rear % _maxSize;
	_queueSize++;

	_sync_queue.Unlock();

	return true;
}

bool FrameQueue::get(FrameDataElement& rFrame)
{
	_sync_queue.Lock();

	bool freturn = false;

	// empty_check
	if(_front == _rear) {

	}
	else {
		const FrameDataElement& rframeInfo = _lpFrameInfo[_front];
		rFrame.setData(rframeInfo._frameInfo, rframeInfo._lpImage);
		_front = ++_front % _maxSize;
		_queueSize--;
		freturn = true;
	}

	_sync_queue.Unlock();

	return freturn;
}

//////////////////////////////////////////////////////////////////////////

bool CameraView::ptInRect(const POINT& rpt) const 
{
	return (_rctCamera.PtInRect(rpt) == TRUE);
}

void CameraView::resetCamera()
{
	_strCaption  = _T("");
	_cameraState = CameraView::DISABLED;
}

//////////////////////////////////////////////////////////////////////////

CScreenViewWnd::CScreenViewWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenViewWnd::IDD, pParent)
{
	_hDrawDib        = NULL;
	_hScreenThread   = NULL;
	_fScreenThread   = false;

	_countCamera     = 1;
	_countLiveCamera = __min(_countCamera, 16);
	_selectCamera    = -1;
	_imageBuffer     = new BYTE[MAX_FRAME_SIZE];
	_fuse1x1Mode     = false;
	_fuseAspectRatio = false;

    _imageHeight = 0;
    _imageWidth  = 0;
}

CScreenViewWnd::~CScreenViewWnd()
{
	if (_bmpCanvas.GetSafeHandle()) {
		_bmpCanvas.DeleteObject();
	}
	if (_fontText.GetSafeHandle()) {
		_fontText.DeleteObject();
	}
	if (_bmpReferCanvas.GetSafeHandle()) {
		_bmpReferCanvas.DeleteObject();
	}

	SAFE_DELETE_ARRAY(_cameraView);
	SAFE_DELETE_ARRAY(_imageBuffer);
}

void CScreenViewWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CScreenViewWnd, CDialog)

BEGIN_MESSAGE_MAP(CScreenViewWnd, CDialog)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

BOOL CScreenViewWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowPos(NULL, 0, 0, _rectScreen.Width(), _rectScreen.Height(),
				 SWP_NOMOVE | SWP_NOREDRAW);

	GetClientRect(_rectClient);

	_hDrawDib = ::DrawDibOpen();
	_bmpCanvas.CreateCompatibleBitmap(&CClientDC(this),
									  _rectScreen.Width(),
									  _rectScreen.Height());
	_bmpReferCanvas.CreateCompatibleBitmap(&CClientDC(this),
										   _rectScreen.Width(),
										   _rectScreen.Height());

	memset(&_bmpInfohead, 0x00, sizeof(_bmpInfohead));
	_bmpInfohead.biSize          = sizeof(_bmpInfohead);
	_bmpInfohead.biPlanes        = 1;
	_bmpInfohead.biBitCount      = 32;
	_bmpInfohead.biCompression   = BI_RGB;
	_bmpInfohead.biXPelsPerMeter = 0;
	_bmpInfohead.biYPelsPerMeter = 0;
	_bmpInfohead.biClrUsed       = 0;
	_bmpInfohead.biClrImportant	 = 0;

	LOGFONT logFont;
	CFont* lpFont = GetFont();
	lpFont->GetLogFont(&logFont);
	logFont.lfWeight  = FW_SEMIBOLD;
	logFont.lfQuality = NONANTIALIASED_QUALITY;
	_fontText.CreateFontIndirect(&logFont);

	initScreenThread();

	for (int i = 0; i < _countCamera; i++) {
		updateStatus(i);
	}

	return TRUE;
}

void CScreenViewWnd::OnDestroy() 
{
	CDialog::OnDestroy();

	_sync_drawing.Lock();

	if (IsRunningThread()) {
		exitScreenThread();
	}

	if (_bmpCanvas.GetSafeHandle()) {
		_bmpCanvas.DeleteObject();
	}
	if (_bmpReferCanvas.GetSafeHandle()) {
		_bmpReferCanvas.DeleteObject();
	}

	::DrawDibClose(_hDrawDib);

	_sync_drawing.Unlock();
}

BOOL CScreenViewWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rctClip;
	CMemDC MemDC;
	MemDC.CreateDC(pDC, &_bmpCanvas);

	pDC->GetClipBox(rctClip);
	pDC->BitBlt(rctClip.left, rctClip.top,
				rctClip.Width(), rctClip.Height(),
				&MemDC,
				rctClip.left, rctClip.top,
				SRCCOPY);

	return TRUE;
}
void CScreenViewWnd::saveImage(TCHAR* path)
{
    BITMAP bm;
    GetObject(_bmpCanvas, sizeof(bm), &bm);

    int pixel = bm.bmBitsPixel/8;
    int bitmapsize = bm.bmWidth * bm.bmHeight * pixel;
    BYTE *pBitmaps = (BYTE*)new BYTE[bitmapsize];
    BYTE *pImg = pBitmaps;
    _bmpCanvas.GetBitmapBits(bitmapsize, pBitmaps);
    USES_CONVERSION;
    FILE *fp = fopen(T2A(path), "w+b");
    if (fp){
          BITMAPFILEHEADER bfh;
          BITMAPCOREHEADER bch;
          memset(&bfh,0,sizeof(bfh));
          memcpy(&bfh.bfType,"BM",2);
          bfh.bfOffBits=sizeof(bch)+sizeof(bfh);
          bfh.bfSize = sizeof(bfh)+sizeof(bch)+bm.bmWidth*(bm.bmHeight)*3;
          memset(&bch,0,sizeof(bch));
          bch.bcSize=sizeof(bch);
          bch.bcPlanes=1;
          bch.bcBitCount=24;
          bch.bcWidth=static_cast<WORD>(bm.bmWidth);
          bch.bcHeight=static_cast<WORD>(bm.bmHeight);
          fwrite(&bfh, 1, sizeof(bfh), fp);
          fwrite(&bch, 1, sizeof(bch), fp);
          for (int i=0;i<bm.bmHeight;i++) {
              pImg = pBitmaps + (bm.bmHeight-1-i)*bm.bmWidthBytes;
              for (int j=0;j<bm.bmWidth;j++) {
                  fwrite(pImg, 1, 3, fp);
                  pImg+=pixel;
                //fwrite(pImg, 1, m_nWidth*m_nHeight*3, fp);
              };
          };
        fclose(fp);
     };
     if (pBitmaps) {
         delete pBitmaps;
     }
     return;
}

void CScreenViewWnd::saveOriginalImage(TCHAR* path)
{
    int pixel = 4;  // 픽셀당 바이트.
    int bitmapsize = _imageWidth * _imageHeight * pixel;
    BYTE *pBitmaps = (BYTE*)new BYTE[bitmapsize];
    memcpy(pBitmaps, _imageBuffer, bitmapsize);
    BYTE *pImg = pBitmaps;
    USES_CONVERSION;
    FILE *fp = fopen(T2A(path), "w+b");
    if (fp){
          BITMAPFILEHEADER bfh;
          BITMAPCOREHEADER bch;
          memset(&bfh,0,sizeof(bfh));
          memcpy(&bfh.bfType,"BM",2);
          bfh.bfOffBits=sizeof(bch)+sizeof(bfh);
          bfh.bfSize = sizeof(bfh)+sizeof(bch)+_imageWidth*(_imageHeight)*3;
          memset(&bch,0,sizeof(bch));
          bch.bcSize=sizeof(bch);
          bch.bcPlanes=1;
          bch.bcBitCount=24;
          bch.bcWidth=_imageWidth;
          bch.bcHeight=_imageHeight;
          fwrite(&bfh, 1, sizeof(bfh), fp);
          fwrite(&bch, 1, sizeof(bch), fp);
          for (int i=0;i<_imageHeight;i++) {
              pImg = pBitmaps + (_imageHeight-1-i)*_imageWidth*pixel;
              for (int j=0;j<_imageWidth;j++) {
                  fwrite(pImg, 1, 3, fp);
                  pImg+=pixel;
                //fwrite(pImg, 1, m_nWidth*m_nHeight*3, fp);
              };
          };
        fclose(fp);
     };
     if (pBitmaps) {
         delete pBitmaps;
     }
     return;
}

void CScreenViewWnd::saveReferImage(TCHAR* path)
{
    drawReferImage();

    BITMAP bm;
    GetObject(_bmpReferCanvas, sizeof(bm), &bm);

    int pixel = bm.bmBitsPixel/8;
    int bitmapsize = bm.bmWidth * bm.bmHeight * pixel;
    BYTE *pBitmaps = (BYTE*)new BYTE[bitmapsize];
    BYTE *pImg = pBitmaps;
    _bmpReferCanvas.GetBitmapBits(bitmapsize, pBitmaps);
    USES_CONVERSION;
    FILE *fp = fopen(T2A(path), "w+b");
    if (fp){
          BITMAPFILEHEADER bfh;
          BITMAPCOREHEADER bch;
          memset(&bfh,0,sizeof(bfh));
          memcpy(&bfh.bfType,"BM",2);
          bfh.bfOffBits=sizeof(bch)+sizeof(bfh);
          bfh.bfSize = sizeof(bfh)+sizeof(bch)+bm.bmWidth*(bm.bmHeight)*3;
          memset(&bch,0,sizeof(bch));
          bch.bcSize=sizeof(bch);
          bch.bcPlanes=1;
          bch.bcBitCount=24;
          bch.bcWidth=static_cast<WORD>(bm.bmWidth);
          bch.bcHeight=static_cast<WORD>(bm.bmHeight);
          fwrite(&bfh, 1, sizeof(bfh), fp);
          fwrite(&bch, 1, sizeof(bch), fp);
          for (int i=0;i<bm.bmHeight;i++) {
              pImg = pBitmaps + (bm.bmHeight-1-i)*bm.bmWidthBytes;
              for (int j=0;j<bm.bmWidth;j++) {
                  fwrite(pImg, 1, 3, fp);
                  pImg+=pixel;
                //fwrite(pImg, 1, m_nWidth*m_nHeight*3, fp);
              };
          };
        fclose(fp);
     };
     if (pBitmaps) {
         delete pBitmaps;
     }
     return;
}

void CScreenViewWnd::cpatureImage(BYTE* data, int size)
{
    memcpy(data, _imageBuffer, size);
}

void CScreenViewWnd::OnPaint()
{
	CRect rctClip, rctClient, rctDraw;
	{
		CPaintDC dc(this);
		dc.GetClipBox(rctClip);
	}

	GetClientRect(rctClient);

	rctClip.InflateRect(100, 100);
	rctDraw.IntersectRect(rctClip, rctClient);

	ASSERT(_bmpCanvas.GetSafeHandle() != NULL);

	CDC* pDC = GetDC();
	CMemDC MemDC;
	MemDC.CreateDC(pDC, &_bmpCanvas);

	_sync_drawing.Lock();

	if (_fuse1x1Mode == false) {
		COLORREF clrBorder;
		for (int i = 0; i < _countCamera; i++) {
			if (!_cameraView[i].is_visible()) {
				continue;
			}
			clrBorder = (_selectCamera == i) ? RGB(0, 255, 0) : RGB(255, 255, 255);
			MemDC->Draw3dRect(_cameraView[i].rect(), clrBorder, clrBorder);
		}
	}
 	else {
		MemDC->Draw3dRect(_cameraView[_selectCamera].rect(),
						  RGB(0, 255, 0), RGB(0, 255, 0));
	}

	_sync_drawing.Unlock();

	pDC->BitBlt(rctDraw.left, rctDraw.top,
				 rctDraw.Width(), rctDraw.Height(),
				 &MemDC,
				 rctDraw.left, rctDraw.top,
				 SRCCOPY);

	ReleaseDC(pDC);
	pDC = NULL;
}

void CScreenViewWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	int selcamera = findCameraByPoint(point);
	if (valid_camera(selcamera)) {
		if (selcamera != _selectCamera) {
			_selectCamera = selcamera;
			Invalidate(FALSE);
		}
	}

	CWnd* pParent = GetParent();
	if (pParent != NULL &&
		pParent->GetSafeHwnd()) {
		pParent->PostMessage(UM_SELECTED_CAMERA, static_cast<WPARAM>(_selectCamera));
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CScreenViewWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDblClk(nFlags, point);

	if (!valid_camera(_selectCamera)) {
		return;
	}

	_sync_drawing.Lock();

	_frameQueue.clear();	// frame_buffer clear

	CClientDC dc(this);
	CMemDC MemDC;
	MemDC.CreateDC(&dc, &_bmpCanvas);
	MemDC->FillSolidRect(_rectScreen, RGB(0, 0, 0));
	MemDC.DeleteDC();

	UINT32 cameraList = 0;
	if (_fuse1x1Mode == false) {
		// 1x1 mode setting
		_fuse1x1Mode = true;
		setScreenLayout(ScreenFormatter::LAYOUT_1X1, _selectCamera, _rectScreen);

		// watch for only selected camera
		cameraList |= 1 << _selectCamera;
	}
	else {
		_fuse1x1Mode = false;

		setScreenLayout(_countLiveCamera);

		for (int i = 0; i < _countLiveCamera; ++i) {
			CameraView& rcamera = _cameraView[i];
			if (rcamera.is_visible()) {
				cameraList |= 1 << i;
			}
		}
	}

	_sync_drawing.Unlock();

	CWnd* lpParent = GetParent();
	if (lpParent != NULL &&
		lpParent->GetSafeHwnd()) {
		lpParent->PostMessage(UM_SCREEN_DBLCLICK,
							  static_cast<WPARAM>(cameraList),
							  static_cast<LPARAM>(MAX_CAMERA_COUNTS));
	}

	Invalidate(FALSE);
}

//////////////////////////////////////////////////////////////////////////

void CScreenViewWnd::initialize(const CRect& rctbound /*= CRect(0, 0, 640, 480)*/)
{
	ASSERT(rctbound.IsRectEmpty() == FALSE && 
		rctbound.IsRectNull() == FALSE);

	_hDecoder = _decoders.initialize(_countCamera);	// decoder_sdk initialize
	ASSERT(_hDecoder != IDISHNULL);

	_fmtScreen.create(_countCamera);

	_rectScreen  = rctbound;
	_rectScreen.OffsetRect(-_rectScreen.left, -_rectScreen.top);
	_cameraView = new CameraView[_countCamera];

	setScreenLayout(ScreenFormatter::LAYOUT_4X4, 0, rctbound);
}

void CScreenViewWnd::shutdown()
{
	exitScreenThread();
	
	_decoders.finalize(_hDecoder);	// decoder_sdk finalize
}

//////////////////////////////////////////////////////////////////////////

void CScreenViewWnd::drawImage(int camera,
							   LPBYTE pImage,
							   const CSize& size,
							   SDK_TIME_T time)
{
	CameraView& rcamView = _cameraView[camera];

	_sync_drawing.Lock();

	if (!rcamView.is_visible() ||
		!rcamView.is_enable()) {
		_sync_drawing.Unlock();
		return;
	}

	_bmpInfohead.biWidth     = size.cx;
	_bmpInfohead.biHeight    = size.cy;
	_bmpInfohead.biSizeImage = size.cx * size.cy * _bmpInfohead.biBitCount >> 3;

	CDC* pDC = GetDC();

	if ((size.cx > 0) && (size.cy > 0)) {

		CMemDC MemDC;
		ASSERT(_bmpCanvas.m_hObject);
		MemDC.CreateDC(pDC, &_bmpCanvas);

		CRect rctDest = rcamView.rect();

		CRect rctImage = rctDest;
		if (_fuseAspectRatio) {
			imageAspectRatio(size.cx, size.cy, rctImage, rctImage);
			if (rcamView.rectImage() != rctImage) {
				MemDC->FillSolidRect(rctDest, RGB(0, 0, 0));
			}
			else {
				const int letter_t = rctImage.top    - rctDest.top;
				const int letter_b = rctDest.bottom - rctImage.bottom;
				const int letter_l = rctImage.left   - rctDest.left;
				const int letter_r = rctDest.right  - rctImage.right;

				if (letter_t > 1 || letter_b > 1 ||
					letter_l > 1 || letter_r > 1) {
					if (letter_t > 0) {
						MemDC->FillSolidRect(rctDest.left + 1, rctDest.top,
									rctDest.Width() - 2, letter_t,
									RGB(0, 0, 0));
					}
					if (letter_b > 0) {
						MemDC->FillSolidRect(rctDest.left + 1, rctImage.bottom,
									rctDest.Width() - 2, letter_b,
									RGB(0, 0, 0));
					}
					if (letter_l > 0) {
						MemDC->FillSolidRect(rctDest.left + 1, rctImage.top,
									letter_l, rctImage.Height(), 
									RGB(0, 0, 0));
					}
					if (letter_r > 0) {
						MemDC->FillSolidRect(rctImage.right, rctImage.top,
									letter_r, rctImage.Height(),
									RGB(0, 0, 0));
					}
				}
			}
		}

		rcamView.setRectImage(rctImage);

		::DrawDibDraw(_hDrawDib, MemDC,
					  rctImage.left, rctImage.top,
					  rctImage.Width(), rctImage.Height(),
					  &_bmpInfohead,
					  pImage,
					  0, 0,
					  size.cx, size.cy,
					  0);

		drawReferLines(&MemDC);

		CRect rctOSD = rctDest;
		rctOSD.DeflateRect(5, 2, 5, 3);

		CTime tmFrame(time);
		CString strTime = (rctOSD.Width() < 140) ?
							tmFrame.Format(_T("%H:%M:%S")) :
							tmFrame.Format(_T("%y-%m-%d %H:%M:%S"));

		CString strTitle = getCameraTitle(camera);

		/*
		CFont* lpFontPrev = MemDC->SelectObject(&_fontText);
		drawText(&MemDC, strTitle, rctOSD, DT_TOP | DT_LEFT | DT_SINGLELINE);
		drawText(&MemDC, strTime,  rctOSD, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
		MemDC->SelectObject(lpFontPrev);
		*/

		COLORREF clrBorder = (_selectCamera == camera) ?
					RGB(0, 255, 0) : RGB(255, 255, 255);

		MemDC->Draw3dRect(rctDest, clrBorder, clrBorder);

		pDC->BitBlt(rctDest.left, rctDest.top,
					rctDest.Width(), rctDest.Height(),
					&MemDC,
					rctDest.left, rctDest.top,
					SRCCOPY);
	}

	ReleaseDC(pDC);

	_sync_drawing.Unlock();
}

bool CScreenViewWnd::drawText(CDC *pDC,
							  LPCTSTR lpszText,
							  const CRect& rctDraw,
							  UINT nFormat,
							  COLORREF clrText,
							  COLORREF clrBack)
{
	ASSERT(pDC != NULL);
	if (pDC->GetSafeHdc() == NULL) return false;

	COLORREF oldColor = pDC->GetTextColor();
	int      oldBkMod = pDC->SetBkMode(TRANSPARENT);

	CRect rect = rctDraw;
	pDC->SetTextColor(clrBack);
	rect.OffsetRect(-1, -1); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect( 1,  0); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect( 1,  0); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect( 0,  1); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect( 0,  1); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect(-1,  0); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect(-1,  0); pDC->DrawText(lpszText, rect, nFormat);
	rect.OffsetRect( 0, -1); pDC->DrawText(lpszText, rect, nFormat);

	pDC->SetTextColor(clrText);
	rect.OffsetRect( 1,  0); pDC->DrawText(lpszText, rect, nFormat);

	pDC->SetBkMode(oldBkMod);
	pDC->SetTextColor(oldColor);

	return true;
}

bool CScreenViewWnd::drawReferLines(CDC *pDC)
{
    if (_shapeManager) {
        Gdiplus::Graphics graphics(*pDC);
        _shapeManager->drawAllShapes(&graphics);
    }

	return true;
}

bool CScreenViewWnd::drawReferImage()
{
    CDC* parentDC = GetDC();

    CMemDC MemDC;
	ASSERT(_bmpReferCanvas.m_hObject);
	MemDC.CreateDC(parentDC, &_bmpReferCanvas);

    CDC* pDC = &MemDC;
    pDC->PatBlt(0, 0, _imageWidth, _imageHeight, WHITENESS);

    if (_shapeManager) {
        Gdiplus::Graphics graphics(*pDC);
        _shapeManager->fillAllShapes(&graphics);
    }
  
	return true;
}

void CScreenViewWnd::imageAspectRatio(int cx, int cy, const CRect& rctin, CRect& rctout)
{
	// consider image half mode
	if ((cy << 1) < cx) cy <<= 1;

	CPoint ptcenter = rctin.CenterPoint();

	int destw = rctin.Width();
	int desth = rctin.Height();

	float xratio = 0.0F;
	float yratio = 0.0F;

	int newcx = destw;
	int newcy = desth;

	xratio = static_cast<float>(cx) / static_cast<float>(destw);
	yratio = static_cast<float>(cy) / static_cast<float>(desth);

	newcy = static_cast<int>(static_cast<float>(cy) / xratio);

	if (newcy > desth) {
		newcx = static_cast<int>(static_cast<float>(cx) / yratio);
		newcy = desth;
	}
	else {
		if (cx >= destw) {
			newcx = destw;
		}
		else {
			newcx = static_cast<int>(static_cast<float>(cx) / xratio);
		}
	}

	int newx = ptcenter.x - (newcx >> 1);
	int newy = ptcenter.y - (newcy >> 1);

	rctout.SetRect(newx, newy, newx + newcx, newy + newcy);
}

void CScreenViewWnd::updateStatus(int camera)
{
	if (GetSafeHwnd() == NULL) {
		return;
	}

	_sync_drawing.Lock();

	if (_fuse1x1Mode == true &&
		_selectCamera != camera) {
		_sync_drawing.Unlock();
		return;
	}

	if (!_cameraView[camera].is_visible()) {
		_sync_drawing.Unlock();
		return;
	}

	int camstatus = getCameraState(camera);

	CClientDC dc(this);
	CMemDC MemDC;
	MemDC.CreateDC(&dc, &_bmpCanvas);

	const CRect& rctcamera = _cameraView[camera].rect();
	if (camstatus != CameraView::ENABLED) {
		MemDC->FillSolidRect(rctcamera, (camstatus == CameraView::NO_VIDEO) ? RGB(0, 0, 255) : RGB(0, 0, 0));
	}

	CString strStatus = _T("");
	switch (camstatus)	{
		case CameraView::NO_VIDEO :
			strStatus = _T("No Video");
			break;
		case CameraView::NOT_CONNECTED:
			strStatus = _T("Not Connected");
			break;
		case CameraView::COVERT_LEVEL1 :
			strStatus = _T("Covert");
			break;
		case CameraView::COVERT_LEVEL2 :
			strStatus = _T("");
			break;
	}

	CRect rctosd = rctcamera;
	rctosd.DeflateRect(5, 2, 5, 3);

	CFont* lpFontPrev = MemDC->SelectObject(&_fontText);
	drawText(&MemDC, strStatus, rctosd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawText(&MemDC, getCameraTitle(camera), rctosd, DT_LEFT | DT_TOP | DT_SINGLELINE);
	MemDC->SelectObject(lpFontPrev);

	MemDC->Draw3dRect(rctcamera, RGB(255, 255, 255), RGB(255, 255, 255));

	dc.BitBlt(rctcamera.left, rctcamera.top,
			  rctcamera.Width(), rctcamera.Height(),
			  &MemDC,
			  rctcamera.left, rctcamera.top,
			  SRCCOPY);

	_sync_drawing.Unlock();
}

int CScreenViewWnd::findCameraByPoint(const CPoint& rpoint)
{
	int camera = -1;
	for (int i = 0; i < _countCamera; i++) {
		// check camera rect
		if (_cameraView[i].is_visible())
		if (_cameraView[i].ptInRect(rpoint)) {
			camera = i;
			break;
		}
	}
	return camera;
}

void CScreenViewWnd::setScreenLayout(int typeLayout, int start, const CRect& rctBound)
{
	_sync_drawing.Lock();

	_fmtScreen.reckonLayout(typeLayout, start, rctBound);

	const ScreenFormatter::TypeRectArray& rarray = _fmtScreen.getRectArray();

	for (int i = 0; i < rarray.GetCount(); i++) {
		const ScreenFormatter::CameraRect& rnode = rarray.GetAt(i);
		CameraView& rcamView = _cameraView[i];

		if (rnode._fvisible) {
			rcamView.setVisible(true);
			rcamView.setRect(rnode._rect);
		}
		else {
			rcamView.setVisible(false);
		}
	}

	_fuse1x1Mode = (typeLayout == ScreenFormatter::LAYOUT_1X1);

	for (int i = 0; i < _countCamera; ++i) {
		CameraView& rcamera = _cameraView[i];
		if (rcamera.is_visible()) {
			updateStatus(i);
		}
	}

	_sync_drawing.Unlock();
}

void CScreenViewWnd::setScreenLayout(int countofCamera)
{
	int typeofLayout = _fmtScreen.getLayoutForCameraCount(countofCamera);
	setScreenLayout(typeofLayout, 0, _rectScreen);
}

void CScreenViewWnd::setCameraState(int camera, int status)
{
	if (!valid_camera(camera)) return;

	int prev_status = getCameraState(camera);
	if (prev_status != status) {
		_cameraView[camera].setState(status);
		updateStatus(camera);
	}
}

void CScreenViewWnd::setCameraTitle(int camera, LPCSTR lpszTitle)
{
	if (!valid_camera(camera) ||
		lpszTitle == NULL) return;

	USES_CONVERSION;
	CString strTitle = A2T(lpszTitle);
	setCameraTitle(camera, strTitle);
}

void CScreenViewWnd::setCameraTitle(int camera, LPCWSTR lpszTitle)
{
	if (!valid_camera(camera) ||
		lpszTitle == NULL) return;
	
	if (_cameraView[camera].title() != lpszTitle) {
		_cameraView[camera].setTitle(lpszTitle);
		updateStatus(camera);
	}
}

void CScreenViewWnd::setCountLiveCamera(int countofCamera)
{
	_countLiveCamera = __min(countofCamera, _countCamera);
}

void CScreenViewWnd::setUseAspectRatio(bool factivate)
{
	_fuseAspectRatio = factivate;
}

void CScreenViewWnd::clearScreen()
{
	_sync_drawing.Lock();

	for (int i = 0; i < _countCamera; i++) {
		_cameraView[i].resetCamera();
	}

	_selectCamera = -1;
	_countLiveCamera = __min(_countCamera, 16);

	CDC* pDC = GetDC();
	CMemDC MemDC;
	MemDC.CreateDC(pDC, &_bmpCanvas);
	MemDC->FillSolidRect(_rectScreen, RGB(0, 0, 0));
	MemDC.DeleteDC();
	ReleaseDC(pDC);

	_sync_drawing.Unlock();

	Invalidate(TRUE);
}

void CScreenViewWnd::setDeInterlaceFilter(int typeofFilter)
{
	_decoders.setDeInterlaceFilter(_hDecoder, typeofFilter);
}

//////////////////////////////////////////////////////////////////////////

/*
 * To gain fast screen display, use yuv420 mode.
 */

DWORD CScreenViewWnd::screenThread(void)
{
	FrameQueue::FrameDataElement frameInfo;

	while (_fScreenThread) {

		if (_frameQueue.get(frameInfo)) {

			const PARAMWS_FRAMEINFO& rframe = frameInfo._frameInfo;

			static PARAMD_DECODERS decoder_params;
			decoder_params._dwSize = sizeof(PARAMD_DECODERS);
			decoder_params._lpCompData   = const_cast<LPBYTE>(frameInfo._lpImage);
			decoder_params._lpCompSize   = rframe._szBuffer;
			decoder_params._camId        = rframe._hostcamera;
			decoder_params._imgFormat    = IDIS_COLORFORMAT::IDIS_RGB32;
			decoder_params._lpDecompData = _imageBuffer;
			decoder_params._imgWidth     = rframe._cxImage;
			decoder_params._imgHeight    = rframe._cyImage;
			decoder_params._decoderType  = rframe._decoder;
			decoder_params._byFrameType  = rframe._frameType;
			decoder_params._byField      = rframe._byField;
			decoder_params._byVolHeader  = rframe._fvolHeader;

			bool fsuccess = _decoders.doDecompress(_hDecoder, reinterpret_cast<LPBYTE>(&decoder_params), DECODEMODE_WATCH);

			::SwitchToThread();	// for prevention piggy loop.
			if (fsuccess &&
				rframe._fDisplay == IDISTRUE) {
                _imageHeight = decoder_params._imgHeight;
                _imageWidth  = decoder_params._imgWidth;
				drawImage(rframe._hostcamera,
						  _imageBuffer,
						  CSize(decoder_params._imgWidth, decoder_params._imgHeight),
						  rframe._tmTime);
				::Sleep(0);
                //::OutputDebugString(L"Decoding Success\n");
			}
            else {
                //::OutputDebugString(L"Decoding Failed\n");
            }
		}
		else {
			// buffer is empty...
			::Sleep(1);
		}
	}

	return 0;
}

DWORD CScreenViewWnd::screenThreadProc(LPVOID lpParam)
{
	CScreenViewWnd* lpScreenView = reinterpret_cast<CScreenViewWnd*>(lpParam);
	return lpScreenView->screenThread();
}

//////////////////////////////////////////////////////////////////////////

bool CScreenViewWnd::initScreenThread()
{
	if (_hScreenThread != NULL) exitScreenThread();

	bool freturn = false;

	_hScreenThread = ::CreateThread(NULL,
									0,
									screenThreadProc,
									this,
									CREATE_SUSPENDED,
									NULL);

	if (_hScreenThread != NULL) {
		_fScreenThread = true;
		SetThreadPriority(_hScreenThread, THREAD_PRIORITY_ABOVE_NORMAL);
		ResumeThread(_hScreenThread);
		freturn = true;
	}

	return freturn;
}

bool CScreenViewWnd::exitScreenThread()
{
	DWORD dwReturn = WAIT_OBJECT_0;

	if(IsRunningThread() == TRUE) {
		_fScreenThread = false;
	
		/* waiting 200ms for thread exit */
		dwReturn = WaitForSingleObject(_hScreenThread, 200);
		if (dwReturn == WAIT_TIMEOUT) {
			TerminateThread(_hScreenThread, 1);
		}
	}

	if(_hScreenThread != NULL) {
		CloseHandle(_hScreenThread);
		_hScreenThread = NULL;
	}

	return (dwReturn == WAIT_OBJECT_0) ? true : false;
}

bool CScreenViewWnd::IsRunningThread()
{
	if(_hScreenThread == NULL) return FALSE;

	/* check thread_activation */
	DWORD dwReturn = 0;
	GetExitCodeThread(_hScreenThread, &dwReturn);

	return (dwReturn == STILL_ACTIVE) ? true : false;
}
