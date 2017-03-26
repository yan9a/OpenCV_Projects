#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv)
{
	Mat image;
	image = imread("C:/opencv/thiri.jpg",0);
	if (!image.data) {
		printf("No image data \n");
		return -1;
	}
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);

	//Create a circular mask
	int h = image.rows;
	int w = image.cols;
	Mat mask(h, w, CV_8UC1, Scalar(0, 0, 0));
	circle(mask, Point(w / 2, h / 2), h / 3, 255, -1);

	//Perform bitwise 'AND' to mask out
	Mat im2;
	bitwise_and(image, mask, im2);

	//Manipulate pixels
	for (int i=0; i < h; i++)
		for (int j=0; j < w; j++)
			if (mask.at<uchar>(i, j) == 0)
				im2.at<uchar>(i, j) = 128;

	namedWindow("Masked Image", WINDOW_AUTOSIZE);
	imshow("Masked Image", im2);

	waitKey(0);
	return 0;
}
