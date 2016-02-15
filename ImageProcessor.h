#ifndef _IMAGE_PROCESSOR_H
#define _IMAGE_PROCESSOR_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <opencv2/opencv.hpp>
#include "AppTypes.h"

class ImageProcessor {
public:
    ImageProcessor();

private:
    cv::Mat _cpaturedImage;

public:
    void setCapturedImage(BYTE* _data, int size, int width, int height, bool isTest = false);

	// _capturedImage에서 circle을 찾는다.
	//	- return value : 찾은 circle의 center, (0,0)이면 찾지 못함.
	Amsong::Point detectCircle();

	// refer image에서의 point의 색상을 찾도록 한다.
	COLORREF getColorOfPointFromReferImage(Amsong::Point hitPoint);
};



#endif  // _IMAGE_PROCESSOR_H