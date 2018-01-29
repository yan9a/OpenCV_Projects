#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	/// Load image and template
	Mat img = imread("c:/opencv/stand.jpg",0);
	namedWindow("Source", CV_WINDOW_AUTOSIZE);
	imshow("Source", img);
	// Detect Harris Corners
	Mat cornerStrength;
	cornerHarris(img,cornerStrength,3,3,0.01);
	normalize(cornerStrength, cornerStrength, 0, 255, NORM_MINMAX, CV_8U);
	namedWindow("Corner Strength",CV_WINDOW_AUTOSIZE);
	imshow("Corner Strength", cornerStrength);
	// threshold the corner strengths
	Mat harrisCorners;
	threshold(cornerStrength, harrisCorners,24, 255, cv::THRESH_BINARY);
	namedWindow("Corners", CV_WINDOW_AUTOSIZE);
	imshow("Corners", harrisCorners);
	waitKey(0);
	return 0;
}

