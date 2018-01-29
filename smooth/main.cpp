#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
//Read original image
Mat image;
image = imread("C:/opencv/star.jpg",0);
if (!image.data) {
printf("No image data \n");
return -1;
}
namedWindow("Original Image", WINDOW_AUTOSIZE);
imshow("Original Image", image);

//Box filter
Mat im_box;
boxFilter(image, im_box, -1, Size(7, 7), Point(-1, -1), true, BORDER_DEFAULT);
namedWindow("Box filter", WINDOW_AUTOSIZE);
imshow("Box filter", im_box);

//Gaussian filter
Mat im_gaussian;
GaussianBlur(image, im_gaussian, Size(7, 7), 0, 0);
namedWindow("Gaussian filter", WINDOW_AUTOSIZE);
imshow("Gaussian filter", im_gaussian);

//Median filter
Mat im_median;
medianBlur(image, im_median, 7);
namedWindow("Median filter", WINDOW_AUTOSIZE);
imshow("Median filter", im_median);
waitKey(0);
return 0;
}
