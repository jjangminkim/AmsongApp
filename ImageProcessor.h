#ifndef _IMAGE_PROCESSOR_H
#define _IMAGE_PROCESSOR_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    ImageProcessor();

private:
    cv::Mat _cpaturedImage;

public:
    void setCapturedImage(BYTE* _data, int size, int width, int height, bool isTest = false);
};



#endif  // _IMAGE_PROCESSOR_H