#include "stdafx.h"
#include "ImageProcessor.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>			// c library..
#include <opencv/highgui.h>		// c library..

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

ImageProcessor::ImageProcessor()
{
}

void ImageProcessor::setCapturedImage(BYTE* _data, int size, int width, int height, bool isTest)
{
	if (isTest) {
		// 테스트 영역.
		return;
	}

	// BMP Image를 Mat 타입으로 변환.
	Mat cpaturedImage(height, width, CV_8UC4, _data);
    _cpaturedImage = cpaturedImage.clone();
	flip(_cpaturedImage, _cpaturedImage, 0);
}

Gdiplus::Point ImageProcessor::detectCircle()
{
	// detect circle.
	IplImage* iplImage_img = new IplImage(_cpaturedImage);

	// color space
	CvSize cvSize = cvGetSize(iplImage_img);
	IplImage *hsv = cvCreateImage(cvSize, IPL_DEPTH_8U, 3);
	cvCvtColor(iplImage_img, hsv, CV_BGR2HSV);

	Mat temp(hsv);
	//imshow("test1", temp);

	// masks
	CvMat* mask = cvCreateMat(cvSize.height, cvSize.width, CV_8UC1);
	// color filter, B, G, R 순으로 해야 함.
	//cvInRangeS(hsv, cvScalar(15, 60, 255, 0),
	//                cvScalar(30, 186, 255, 0), mask);
	// 주황색 탁구공
	/*cvInRangeS(hsv, cvScalar(12, 60, 249, 0),
	                cvScalar(30, 186, 255, 0), mask);*/
	cvInRangeS(hsv, cvScalar(0, 140, 170, 0),
	                cvScalar(30, 180, 240, 0), mask);
	// 테니스공은 다시 찾아보자.
	//cvInRangeS(hsv, cvScalar(43, 114, 141, 0),
	//                cvScalar(38, 84, 100, 0), mask);
	cvReleaseImage(&hsv);

	Mat masked(mask);
	//imshow("test2", masked);

	// morphological operations
	Mat se21 = getStructuringElement(MORPH_RECT, Size(21, 21), Point(10, 10));
	Mat se11 = getStructuringElement(MORPH_RECT, Size(11, 11), Point(5, 5));
	morphologyEx(masked, masked, MORPH_CLOSE, se21);
	morphologyEx(masked, masked, MORPH_OPEN, se11);

	//imshow("test3", masked);

	// Hough transform
	/* Copy mask into a grayscale image */
	CvMat filtered = masked;
	IplImage *hough_in = cvCreateImage(cvSize, 8, 1);
	cvCopy(&filtered, hough_in, NULL);
    cvSmooth(hough_in, hough_in, CV_GAUSSIAN, 15, 15, 0, 0);

	//Mat tempg(hough_in);
	//imshow("gaussian", tempg);

	/* Run the Hough function */
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *circles = cvHoughCircles(hough_in, storage,
		CV_HOUGH_GRADIENT, 4, cvSize.height/10, 100, 40, 0, 0);

	// output
	int i;
	Gdiplus::Point centerOfCircle;
	for (i = 0; i < circles->total; i++) {
		float *p = (float*)cvGetSeqElem(circles, i);
		CvPoint center = cvPoint(cvRound(p[0]),cvRound(p[1]));
		CvScalar val = cvGet2D(&filtered, center.y, center.x);
		if (val.val[0] < 1) {
			continue;
		}
		cvCircle(iplImage_img, center, 3, CV_RGB(0,255,0), -1, CV_AA, 0);
		cvCircle(iplImage_img, center, cvRound(p[2]), CV_RGB(255,0,0), 3, CV_AA, 0);
		cvCircle(&filtered, center, 3, CV_RGB(0,255,0), -1, CV_AA, 0);
		cvCircle(&filtered, center, cvRound(p[2]), CV_RGB(255,0,0), 3, CV_AA, 0);

		centerOfCircle.X = center.x;
		centerOfCircle.Y = center.y;
	}

	Mat res(iplImage_img);
	//imshow("result", res);

	cvReleaseMemStorage(&storage);

	return centerOfCircle;
}

Gdiplus::Color ImageProcessor::getColorOfPointFromReferImage(Gdiplus::Point hitPoint)
{
	Mat referImage = imread("ReferImage.bmp");
	IplImage* iplReferImage = new IplImage(referImage);

	unsigned char red, green, blue;
	red = green = blue = 0;

	int index = (hitPoint.Y * iplReferImage->widthStep) + (hitPoint.X * 3);
	red = iplReferImage->imageData[index + 2];
	green = iplReferImage->imageData[index + 1];
	blue = iplReferImage->imageData[index];
    Gdiplus::Color color = Gdiplus::Color(255, red, green, blue);

	return color;
}
