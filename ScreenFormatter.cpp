// ScreenFormatter.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenFormatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

void ScreenFormatter::create(int countofCamera)
{
	ASSERT(countofCamera > 0);

	cleanup();

	_countofCamera = countofCamera;
	_maxLayout     = getLayoutForCameraCount(countofCamera);
	_arrayRect.SetSize(countofCamera);
}

void ScreenFormatter::cleanup(void)
{
	_arrayRect.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

int  ScreenFormatter::getLayoutForCameraCount(int countofCamera) const
{
	if (countofCamera > _countofCamera) {
		countofCamera = _countofCamera;
	}
	int typeLayout = _maxLayout;
	for (int i = 0; i < LAYOUT_MAX_DUMMY; i++) {
		const int count = getCameraPerLayout(i);
		if (countofCamera <= count) {
			typeLayout = i;
			break;
		}
	}
	if (typeLayout > _maxLayout) {
		typeLayout = _maxLayout;
	}
	return typeLayout;
}

int  ScreenFormatter::reckonLayout(int layout, int leftTopCamera, const CRect& rctScreen)
{
	if (layout >= LAYOUT_MAX_DUMMY ||
		layout < LAYOUT_1X1) {
		layout = LAYOUT_1X1;
	}

	_layout = getMaxLayout(layout);

	int ROW = getRows(_layout);
	int COL = getCols(_layout);
	const int W = rctScreen.Width() / COL;
	const int H = rctScreen.Height() / ROW;
	const int PAGE = ROW * COL;

	int row, col, right, bottom, index;

	CRect objRect[64];

	for (row = 0; row < ROW; row++) {
		for (col = 0; col < COL; col++) {
			right  = (col < COL-1) ? rctScreen.left + (col + 1) * W : rctScreen.right;
			bottom = (row < ROW-1) ? rctScreen.top + (row + 1) * H : rctScreen.bottom;
			index  = row * COL + col;
			objRect[index].SetRect(rctScreen.left + col * W, rctScreen.top + row * H, right, bottom);
		}
	}

	int startCamera = (_countofCamera == getCameraPerLayout(_layout)) ? 0 : leftTopCamera;
	int cameraCount = ROW * COL;
	int rectIndex = 0;
	for (int i = startCamera; rectIndex < _countofCamera; i++) {
		if (i >= _countofCamera) {
			i = 0;
		}
		if (rectIndex >= cameraCount) {
			_arrayRect[i].setVisible(false);
			rectIndex++;
			continue;
		}
		_arrayRect[i].setVisible(true);
		_arrayRect[i].setRect(objRect[rectIndex]);
		rectIndex++;
	}

	return _layout;
}
