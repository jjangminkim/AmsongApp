
#include "stdafx.h"
#include "ImageProcessor.h"


ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::setCapturedImage(BYTE* _data, int size, int width, int height)
{
    cv::Mat cpaturedImage(height, width, CV_8UC4, _data);
    _cpaturedImage = cpaturedImage.clone();

    cv::imwrite("cvimage.bmp", _cpaturedImage);
}