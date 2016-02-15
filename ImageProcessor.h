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

	// _capturedImage���� circle�� ã�´�.
	//	- return value : ã�� circle�� center, (0,0)�̸� ã�� ����.
	Amsong::Point detectCircle();

	// refer image������ point�� ������ ã���� �Ѵ�.
	COLORREF getColorOfPointFromReferImage(Amsong::Point hitPoint);
};



#endif  // _IMAGE_PROCESSOR_H