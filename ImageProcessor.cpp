
#include "stdafx.h"
#include "ImageProcessor.h"



#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>



//#include "opencv2/imgcodecs.hpp"

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


		IplImage *dstImage;

		dstImage = cvCreateImage(cvSize(1024,1024), IPL_DEPTH_8U,3);
		cvSet(dstImage,CV_RGB(255,255,255));

		//cvRectangle(dstImage, cvPoint(100,100), cvPoint(400,400), CV_RGB(255,0,0));
		
		cvLine(dstImage,cvPoint(112,500),cvPoint(512,900),CV_RGB(0,0,0));
		cvLine(dstImage,cvPoint(912,500),cvPoint(512,900),CV_RGB(0,0,0));
		
		cvLine(dstImage,cvPoint(212,500),cvPoint(512,800),CV_RGB(0,0,0));
		cvLine(dstImage,cvPoint(812,500),cvPoint(512,800),CV_RGB(0,0,0));
		
		cvLine(dstImage,cvPoint(312,500),cvPoint(512,700),CV_RGB(0,0,0));
		cvLine(dstImage,cvPoint(712,500),cvPoint(512,700),CV_RGB(0,0,0));
		
		cvLine(dstImage,cvPoint(112,500),cvPoint(912,500),CV_RGB(0,0,0));
		
		
		cvEllipse(dstImage, cvPoint(512,500), cvSize(100,100), 0,180,360, CV_RGB(0,0,255));
		cvEllipse(dstImage, cvPoint(512,500), cvSize(200,200), 0,180,360, CV_RGB(0,0,255));
		cvEllipse(dstImage, cvPoint(512,500), cvSize(300,300), 0,180,360, CV_RGB(0,0,255));
		cvEllipse(dstImage, cvPoint(512,500), cvSize(400,400), 0,180,360, CV_RGB(0,0,255));



		
		cvNamedWindow("Drawing Graphcs", CV_WINDOW_AUTOSIZE);
		cvShowImage("Drawing Graphics", dstImage);


		cvWaitKey(0);
		cvDestroyAllWindows();
		cvReleaseImage(&dstImage);

	





		return;
	}

	











	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*
	// sobel detection 추가 부분	
	cv::Mat src, src_gray;
	cv::Mat grad;
	
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	// 추가 부분 1끝
	
	cv::Mat cpaturedImage(height, width, CV_8UC4, _data);
    _cpaturedImage = cpaturedImage.clone();



	cv::Mat first = cv::imread("first.bmp");
	cv::Mat second = cv::imread("second.bmp");
	cv::Mat third = cv::imread("third.bmp");
	cv::Mat homerun = cv::imread("homerun.bmp");
	cv::Mat strike = cv::imread("strike.bmp");


    cv::imwrite("cvimage2.bmp", _cpaturedImage); // capture되는 이미지

	//imshow("test", _cpaturedImage);
	
	
	
		
	cv::Mat img1 = cv::imread("map.bmp"); // 암송판 이미지
	cv::Mat img2 = cv::imread("map_test2.bmp");// 타겟 이미지

	cv::Mat src_img = cv::imread("cvimage2.bmp");

	//imshow("result",src_img);

    cv::Mat dst_img, gray;
	dst_img = src_img.clone();

	//cv::cvtColor(src_img, work_img, CV_BGR2GRAY);	 
	//cv::GaussianBlur(work_img, work_img, cv::Size(11,11), 2, 2);

	//imshow("working",work_img);



	// 에지디텍


	

	cv::GaussianBlur( src_img, src, Size(3,3), 0, 0, BORDER_DEFAULT );
	cv::cvtColor( src, src_gray, CV_BGR2GRAY );

	
	
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;
	
	
	cv::Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_x, abs_grad_x );


	cv::Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
    cv::convertScaleAbs( grad_y, abs_grad_y );

	cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

	dst_img = grad;


	//imshow( "edge detection", grad );
	
	
	//에지디텍 끝
	

	// 원검출
	
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(dst_img, circles, CV_HOUGH_GRADIENT, 1, 300, 100, 80);

	std::vector<cv::Vec3f>::iterator it = circles.begin();
	for(; it!=circles.end(); ++it) 
	{
		cv::Point center(cv::saturate_cast<int>((*it)[0]), cv::saturate_cast<int>((*it)[1]));

		int radius = cv::saturate_cast<int>((*it)[2]);

		cv::circle(dst_img, center, radius, cv::Scalar(255,255,255), 2);
	}
	
//	cv::namedWindow("HoughCircles", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("HoughCircles", grad);
	
	
	//원 검출 끝

	*/




////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
/*	
	cvtColor(src_img, gray, CV_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 100, 100, 50 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle( src_img, center, 3, Scalar(0,255,0), -1, 8, 0 );
         // draw the circle outline
         circle( src_img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    namedWindow( "circles", 1 );
    imshow( "circles", src_img );
	
	
	*/
	











	// 코너찾기


	/*

	IplImage *srcImage;
	srcImage = cvLoadImage("cornerTest.bmp",CV_LOAD_IMAGE_GRAYSCALE);


	IplImage *dstImage = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,3);

	IplImage *corners = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F,1);

	cvPreCornerDetect(srcImage, corners, 3);

	cvAbs(corners, corners);
	cvThreshold(corners, corners, 0.01, 0, CV_THRESH_TOZERO);
	cvCvtColor(srcImage,dstImage, CV_GRAY2BGR);

	double fValue;
	double maxValue;

	int x, y;
	int m, n;
	bool bChange;

	int nSize = 3;
	int nCornerCount = 0;

	for(y=nSize; y<corners->height-nSize; y++)
		for( x=nSize; x<corners->width-nSize; x++)
		{
			bChange = false;;
			maxValue = cvGetReal2D(corners, y, x);
			for( n=y-nSize; n<=y+nSize; n++)
				for(m=x-nSize; m<=x+nSize;m++)
				{
					if(m==x && n==y)
						continue;
					fValue = cvGetReal2D(corners, n, m);
					if(fValue >= maxValue)
					{
						bChange = true;
						break;
					}
				}
			if(!bChange)
			{
				nCornerCount++;
				printf("corners(%d,%d)=%f\n",x,y,maxValue);
				cvCircle(dstImage, cvPoint(x,y), 5, CV_RGB(255,0,0),2);
			}

		}


		cvNamedWindow("dstImage", CV_WINDOW_AUTOSIZE);
		cvShowImage("dstImage",dstImage);



		cv::waitKey(0);
		cvDestroyAllWindows();
		cvReleaseImage(&corners);
		cvReleaseImage(&srcImage);
		cvReleaseImage(&dstImage);
		


		*/



	// 코너 찾기 




	/*
	// ##### 원 검출 Code #####
	
	
	cv::GaussianBlur(img2, img2, cv::Size(5,5), 1.5);
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(img2, circles, CV_HOUGH_GRADIENT, 
		 1,   // 누적기 해상도(영상크기/2)
		10,  // 두 원 간의 최소 거리
		200, // 캐니 최대 경계값
		20, // 투표 최소 개수
		4, 15); // 최소와 최대 반지름

	img2= cv::imread("map_test2.jpg",0);
	std::vector<cv::Vec3f>::const_iterator itc= circles.begin();
	while (itc!=circles.end()) {
		cv::circle(img2, 
		cv::Point((*itc)[0], (*itc)[1]), // 원 중심
		(*itc)[2],  // 원 반지름
		cv::Scalar(255), // 컬러 
		2);    // 두께
		++itc; 
	}
	
	
	cv::imshow("Detected Circles",img2);
	
	*/

	// ##### 원 검출 Code #####


	/*
	cv::GaussianBlur( img2, img2, Size(3,3), 0, 0, BORDER_DEFAULT );
	
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(img2, circles, CV_HOUGH_GRADIENT, 
	2,   // 누적기 해상도(영상크기/2)
	50,  // 두 원 간의 최소 거리
	200, // 캐니 최대 경계값
	100, // 투표 최소 개수
	125, 100); // 최소와 최대 반지름
	
	
	
	//imshow("gray",src_gray); image= cv::imread("chariot.jpg",0);
	
	img2 = cv::imread("map_test2.bmp",0);
	std::vector<cv::Vec3f>::const_iterator itc= circles.begin();
	
	while (itc!=circles.end()) {
		cv::circle(img2, 
		cv::Point((*itc)[0], (*itc)[1]), // 원 중심
		(*itc)[2],  // 원 반지름
		cv::Scalar(255), // 컬러 
	    2);    // 두께
		++itc; 
	}
	*/



/*

	// ##### edge detection Code #####
	
	cv::GaussianBlur( img2, src, Size(3,3), 0, 0, BORDER_DEFAULT );
	cv::cvtColor( src, src_gray, CV_BGR2GRAY );

	
	
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;
	
	
	cv::Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_x, abs_grad_x );


	cv::Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
    cv::convertScaleAbs( grad_y, abs_grad_y );

	cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

	imshow( "edge detection", grad );
	
	// ##### edge detection Code #####








	*/




	//cv::imshow("Detected Circles",img2);

	//imshow("second",img2);

	/*
	int n1 = img1.rows;
	int n2 = img1.cols;
		
	int x_max=0;
	int x_min=1280;
	int y_max=0;
	int y_min=720;

	for(int rows =0; rows < n1; ++rows)  // x좌표
		{
			//uchar* data1 = img1.ptr<uchar>(rows);
			//uchar* data2 = img2.ptr<uchar>(rows);

			cv::Vec3b* pixel = img1.ptr<cv::Vec3b>(rows);
			cv::Vec3b* pixel2 = img2.ptr<cv::Vec3b>(rows);
			//cv::Vec3b* pixel3 = img2.ptr<cv::Vec3b>(rows);
			
			for (int cols=0; cols <n2 ; ++cols)  // y좌표
			{
				
				pixel[cols][2] = pixel[cols][2]-pixel2[cols][2];
				pixel[cols][1] = pixel[cols][1]-pixel2[cols][1];
				pixel[cols][0] = pixel[cols][0]-pixel2[cols][0];	

			

				
				if(pixel[cols][2] < 20 ||  pixel[cols][1] < 20 || pixel[cols][0] < 20)
				{	
					pixel[cols][2]=0;
					pixel[cols][1]=0;
					pixel[cols][0]=0;
				
				
					if(x_max < cols)
						x_max = cols;

					if(x_min > cols)
						x_min = cols;

					if(y_max < rows)
						y_max = rows;

					if(y_min > rows)
						y_min = rows;
								
				}
				
				else
				{
				
					
					pixel[cols][2]=255;
					pixel[cols][1]=255;
					pixel[cols][0]=255;
				
				
				}
				
				
		
			
			}
		}
	
		
		
		std::cout<<"x_max :"<<x_max;
		std::cout<<"\nx_min :"<<x_min;
		std::cout<<"\n\ny_max :"<<y_max;
		std::cout<<"\ny_min :"<<y_min;


		std::cout<<"\n\n\nx = :"<<(x_min+x_max)/2;
		std::cout<<"\ny = :"<<(y_min+y_max)/2;


		

		int x_val = (x_min+x_max)/2;
		int y_val = (y_min+y_max)/2;
		*/

/*
		if((0<x_val)&&(x_val<640))
			if((0<y_val)&&(y_val<360))
				cv::imshow(std::string("result"),second);

		if((0<x_val)&&(x_val<640))
			if((360<y_val)&&(y_val<720))
				cv::imshow(std::string("result"),first);

		if((640<x_val)&&(x_val<1280))
			if((0<y_val)&&(y_val<360))
				cv::imshow(std::string("result"),third);

		if((640<x_val)&&(x_val<1280))
			if((360<y_val)&&(y_val<720))
				cv::imshow(std::string("result"),homerun);

	*/	
		//cv::imshow(std::string("result"),img1);
		
		cv::waitKey(0);


		



}																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																