#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
//Read original image
Mat image;
image = imread("C:/opencv/ka_ori.jpg", 0);
//image = imread("/home/yan/ka_ori.jpg", 0);
if (!image.data) {
printf("No image data \n");
return -1;
}
namedWindow("Original Image", WINDOW_AUTOSIZE);
imshow("Original Image", image);

Mat e_struc = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));

//erosion
Mat im_e;
erode(image, im_e, e_struc);
namedWindow("Erosion", WINDOW_AUTOSIZE);
imshow("Erosion", im_e);

//dilation
Mat im_d;
dilate(image, im_d, e_struc);
namedWindow("Dilation", WINDOW_AUTOSIZE);
imshow("Dilation", im_d);

//opening
Mat im_o;
morphologyEx(image, im_o, MORPH_OPEN, e_struc);
namedWindow("Opening", WINDOW_AUTOSIZE);
imshow("Opening", im_o);

//closing
Mat im_c;
morphologyEx(image, im_c, MORPH_CLOSE, e_struc);
namedWindow("Closing", WINDOW_AUTOSIZE);
imshow("Closing", im_c);

//opening and closing to remove noise
Mat im_r;
morphologyEx(image, im_o, MORPH_OPEN, e_struc);
morphologyEx(im_o, im_r, MORPH_CLOSE, e_struc);
namedWindow("Remove noise", WINDOW_AUTOSIZE);
imshow("Remove noise", im_r);

//gradient
Mat g_struc = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
Mat im_g;
morphologyEx(image, im_g, MORPH_GRADIENT, g_struc);
namedWindow("Gradient", WINDOW_AUTOSIZE);
imshow("Gradient", im_g);

waitKey(0);
return 0;
}
