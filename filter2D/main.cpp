#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
//Read original image
Mat image;
image = imread("C:/opencv/grove.jpg",1);
//image = imread("/home/yan/grove.jpg",1);
if (!image.data) {
printf("No image data \n");
return -1;
}
namedWindow("Original Image", WINDOW_AUTOSIZE);
imshow("Original Image", image);

//create kernel
Mat kernel;
int kernel_size = 9;
kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);

//filter2D filter
Mat im_filter;
filter2D(image, im_filter, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
namedWindow("filter2D", WINDOW_AUTOSIZE);
imshow("filter2D", im_filter);
waitKey(0);
return 0;
}
