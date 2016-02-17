#ifndef _APP_TYPES_H
#define _APP_TYPES_H

#if _MSC_VER > 1000
#pragma once
#endif

namespace Amsong {

    const CString APP_NAME = _T("AMSONG_APP");

	// COLOR DEFINES
	const COLORREF COLOR_THIRD_BASE  = RGB(237, 249, 0);
	const COLORREF COLOR_SECOND_BASE = RGB(0, 255, 6);
	const COLORREF COLOR_FIRST_BASE	 = RGB(255, 182, 0);
	const COLORREF COLOR_OUT         = RGB(53, 53, 53);

    // COLOR DEFINES WITH GDI+
    const Gdiplus::Color CLR_THIRD_BASE  = Gdiplus::Color(255, 204, 51, 51);
    const Gdiplus::Color CLR_SECOND_BASE = Gdiplus::Color(255, 0, 255, 6);
    const Gdiplus::Color CLR_FIRST_BASE  = Gdiplus::Color(255, 255, 153, 51);
    const Gdiplus::Color CLR_HOMERUN     = Gdiplus::Color(255, 0, 204, 255);
    const Gdiplus::Color CLR_STRIKE      = Gdiplus::Color(255, 237, 249, 0);
    const Gdiplus::Color CLR_BALL        = Gdiplus::Color(255, 204, 102, 255);
    const Gdiplus::Color CLR_HP          = Gdiplus::Color(255, 51, 0, 51);
    const Gdiplus::Color CLR_OUT         = Gdiplus::Color(255, 51, 255, 204);

}	// namespace Amsong

#endif  // _APP_TYPES_H
