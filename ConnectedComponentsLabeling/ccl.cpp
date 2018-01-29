#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
//Read original image
Mat src;
src = imread("C:/opencv/ka_ori.jpg", 0);
if (!src.data) { printf("No image data \n"); return -1; }

// scale - to make it convenient to print out and see
Mat ims; resize(src, ims, Size(16, 8));
Mat imb; threshold(ims, imb, 128, 255, CV_8U);// make binary

namedWindow("Original Image", WINDOW_AUTOSIZE);
imshow("Original Image", imb);
cout << "Original" << endl << imb << endl << endl;

//Connected components
Mat imr; int N=connectedComponents(imb, imr);
cout << "CCL" << endl << imr << endl << endl;
cout<<"Number of components: "<< N-1 << endl;// 0 is background

//Connected components with stats
Mat cc, sts, ctd; N=connectedComponentsWithStats(imb, cc, sts, ctd, 8);

//get area column except background	
Mat A(sts, Rect(CC_STAT_AREA, 1, 1, sts.rows - 1));

// Localizing the biggest component
double minVal, maxVal;
Point minLoc, maxLoc;
minMaxLoc(A, &minVal, &maxVal, &minLoc, &maxLoc);
printf("Max area is %lf at label %d .\n", maxVal, (maxLoc.y + 1));

printf("Centroid of the biggest component: [%f,%f] \n", ctd.at<double>(maxLoc.y + 1, 0), ctd.at<double>(maxLoc.y + 1, 1));

waitKey(0);
return 0;
}
