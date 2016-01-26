// ScreenFormatter.h : header file
//

#ifndef _SCREENVIEW_LAYOUT_FORMATTER_H_
#define _SCREENVIEW_LAYOUT_FORMATTER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////

class ScreenFormatter
{
// Constructions
public:
	ScreenFormatter(void)
		: _countofCamera(0)
		, _maxLayout(LAYOUT_6X6)
	{
		/* nothing */
	}
	explicit ScreenFormatter(int countofCamera)
	{
		create(countofCamera);
	}
	~ScreenFormatter(void)
	{
		/* nothing */
	}

	enum TypeofLayout {
		LAYOUT_UNDEFINED = -1,
		LAYOUT_1X1 = 0,
		LAYOUT_2X2,
		LAYOUT_3X3,
		LAYOUT_4X3,
		LAYOUT_4X4,
		LAYOUT_4X5,
		LAYOUT_5X5,
		LAYOUT_6X6,
		LAYOUT_MAX_DUMMY
	};

	class CameraRect
	{
	// Constructions
	public:
		CameraRect(void)
			: _rect(0, 0, 0, 0)
			, _fvisible(false)
		{
			/* nothing */
		}
		~CameraRect(void)
		{
			/* nothing */
		}

	// Attributes
	public:
		CRect	_rect;
		bool	_fvisible;

	// Operations
	public:
		void setVisible(bool fvisiable)	{ _fvisible = fvisiable; }
		void setRect(const CRect& rect)	{ _rect  = rect; }

		bool getVisible(void) const		{ return _fvisible; }
		CRect getRect(void) const		{ return _rect; }
	};

	typedef CArray<CameraRect, CameraRect&> TypeRectArray;

// Attributes
protected:
	TypeRectArray	_arrayRect;
	int				_countofCamera;
	int				_layout;
	int				_maxLayout;

public:
	const TypeRectArray& getRectArray(void) const	{ return _arrayRect; }
	int  getCurrentLayout(void) const				{ return _layout; }
	bool isUseLayout1x1(void) const					{ return _layout == LAYOUT_1X1; }

// Operations
public:
	void create(int countofCamera);
	void cleanup(void);

	int  getMaxLayout(int layout) const;
	int  getCameraPerLayout(int layout) const;
	int  getRows(int layout) const;
	int  getCols(int layout) const;
	bool isValidLayout(int layout) const;

	int  getLayoutForCameraCount(int countofCamera) const;
	int  reckonLayout(int layout, int leftTopCamera, const CRect& rctScreen);
};

//////////////////////////////////////////////////////////////////////////

inline bool ScreenFormatter::isValidLayout(int layout) const
{
	return (layout <  LAYOUT_1X1 ||
			layout >= LAYOUT_MAX_DUMMY) ? false : true;
}

inline int ScreenFormatter::getMaxLayout(int layout) const
{
	if (layout >= LAYOUT_6X6) {
		return LAYOUT_6X6;
	}

	return (_countofCamera < getRows(layout) * getCols(layout)) ?
			getMaxLayout(layout - 1) : layout;
}

inline int ScreenFormatter::getCameraPerLayout(int layout) const
{
	int camera = 0;
	switch (layout) {
		case LAYOUT_1X1: camera = 1;  break;
		case LAYOUT_2X2: camera = 4;  break;
		case LAYOUT_3X3: camera = 9;  break;
		case LAYOUT_4X3: camera = 12; break;
		case LAYOUT_4X4: camera = 16; break;
		case LAYOUT_4X5: camera = 20; break;
		case LAYOUT_5X5: camera = 25; break;
		case LAYOUT_6X6: camera = 36; break;
		default:
			ASSERT(FALSE);
			break;
	}
	return camera;
}

inline int ScreenFormatter::getRows(int layout) const 
{
	int row = 0;
	switch (layout) {
		case LAYOUT_1X1: row = 1; break;
		case LAYOUT_2X2: row = 2; break;
		case LAYOUT_3X3: row = 3; break;
		case LAYOUT_4X3: row = 4; break;
		case LAYOUT_4X4: row = 4; break;
		case LAYOUT_4X5: row = 5; break;
		case LAYOUT_5X5: row = 5; break;
		case LAYOUT_6X6: row = 6; break;
		default:
			ASSERT(FALSE);
			break;
	}
	return row;
}

inline int ScreenFormatter::getCols(int layout) const 
{
	int col = 0;
	switch (layout) {
		case LAYOUT_1X1: col = 1; break;
		case LAYOUT_2X2: col = 2; break;
		case LAYOUT_3X3: col = 3; break;
		case LAYOUT_4X3: col = 3; break;
		case LAYOUT_4X4: col = 4; break;
		case LAYOUT_4X5: col = 4; break;
		case LAYOUT_5X5: col = 5; break;
		case LAYOUT_6X6: col = 6; break;
		default:
			ASSERT(FALSE);
			break;
	}
	return col;
}

//////////////////////////////////////////////////////////////////////////

#endif // !_SCREENVIEW_LAYOUT_FORMATTER_H_
