#ifndef _APP_TYPES_H
#define _APP_TYPES_H

#if _MSC_VER > 1000
#pragma once
#endif

namespace Amsong {

	typedef struct Point {
		Point() : x(0), y(0) {}
		Point(int x_, int y_) : x(x_), y(y_) {}
		int x;
		int y;
	} Point;

	typedef struct Triangle {
		Triangle() {}
		Triangle(Point topLeft_, Point topRight_, Point bottomCenter_)
			: topLeft(topLeft_)
			, topRight(topRight_)
			, bottomCenter(bottomCenter_) {}
		Point topLeft;
		Point topRight;
		Point bottomCenter;
	} Triangle;

}	// namespace Amsong

#endif  // _APP_TYPES_H
