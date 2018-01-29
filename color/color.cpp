 //File: color.cpp
 //Description: Selective Color Modification
 //WebSite: http://cool-emerald.blogspot.com
 //MIT License (https://opensource.org/licenses/MIT)
 //Copyright (c) 2017 Yan Naing Aye

 #include <stdio.h>
 #include <opencv2/opencv.hpp>
 using namespace cv;
 int main(int argc, char** argv)
 {
 Mat image;
 image = imread("C:/opencv/lane.jpg", 1);
 if (!image.data) {
 printf("No image data \n");
 return -1;
 }
 namedWindow("Original Image", WINDOW_AUTOSIZE);
 imshow("Original Image", image);
 
 //Convert to hsv
 Mat hsv;
 cvtColor(image, hsv, COLOR_BGR2HSV);
 
 //select pixels
 //the range of H channel is 0-179.
 //blue at 240 deg corresponds to 120 in H channel
 Mat bw;
 inRange(hsv, Scalar(80, 0, 0), Scalar(140, 255, 255), bw);
 namedWindow("Mask", WINDOW_AUTOSIZE);
 imshow("Mask", bw);
 
 //Manipulate pixels
 for (int i = 0; i < image.rows; i++)
 for (int j = 0; j < image.cols; j++)
 if (bw.at<uchar>(i, j) > 128)
 hsv.at<Vec3b>(i, j)[0] = (hsv.at<Vec3b>(i, j)[0] + 120) % 180;
 
 //Convert to bgr
 Mat im2;
 cvtColor(hsv, im2, COLOR_HSV2BGR);
 
 namedWindow("Modified Image", WINDOW_AUTOSIZE);
 imshow("Modified Image", im2);
 
 waitKey(0);
 return 0;
 }
