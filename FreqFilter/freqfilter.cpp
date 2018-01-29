//File: freqfilter.cpp
//Description: filtering in frequency domain
//WebSite: http://cool-emerald.blogspot.com
//MIT License (https://opensource.org/licenses/MIT)
//Copyright (c) 2017 Yan Naing Aye

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//Create an image of complex number type (2 channels to store 
// real part and imaginary part) from an input grayscale image
// with an optimal size for DFT
// src : single channel grayscale image input
// dst : two channel complex image output
void i2z(Mat src, Mat& dst)
{
	//get optimal size for dft
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);

	//change the image to optimal size, padding 0 values at bottom and right
	Mat im_padded;
	copyMakeBorder(src, im_padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));

	//convert the image to float type, create another one filled with zeros, 
	//and make an array of these 2 images
	Mat im_array[] = { Mat_<float>(im_padded), Mat::zeros(im_padded.size(), CV_32F) };

	//combine as a 2 channel image to represent a complex number type image
	Mat im_complex; merge(im_array, 2, im_complex);

	im_complex.copyTo(dst);//copy to destination
}

// convert a 2 channel complex image to a single channel grayscale image
// by getting magnitude, change scale, and normalize
// src : two channel complex image input
// dst : single channel grayscale image output
// LogScale : change to log scale or not
void z2i(Mat src, Mat& dst, bool LogScale = false)
{
	Mat im_tmp[2]; split(src, im_tmp);//split the complex image to 2
	Mat im_f; magnitude(im_tmp[0], im_tmp[1], im_f);//get absolute value
	if (LogScale) {
		im_f += Scalar::all(1);//make minimum 1
		log(im_f, im_f);//log scale
	}
	Mat im;
	normalize(im_f, im, 0, 255, NORM_MINMAX, CV_8U); //normalize
													 //im = Mat_<uchar>(im_f);
	im.copyTo(dst);//copy to destination
}

// rearrange the quadrants of a Fourier image
void fftshift(Mat src) {
	// make number of rows or columns even
	src = src(Rect(0, 0, src.cols & -2, src.rows & -2));
	int cx = src.cols / 2;
	int cy = src.rows / 2;
	Mat q1(src, Rect(cx, 0, cx, cy));// Top-Right
	Mat q2(src, Rect(0, 0, cx, cy));// Top-Left	
	Mat q3(src, Rect(0, cy, cx, cy));// Bottom-Left
	Mat q4(src, Rect(cx, cy, cx, cy));// Bottom-Right
	Mat tmp;
	q2.copyTo(tmp);
	q4.copyTo(q2);
	tmp.copyTo(q4);
	q1.copyTo(tmp);
	q3.copyTo(q1);
	tmp.copyTo(q3);
}

//Produce Gaussian filter in frequency domain
// height : height of the filter
// width  : width of the filter
// std    : standard deviation where intensity is 60% (like cutoff frequency )
// highpass: true=highpass, false=lowpass
Mat GaussianFilter(int height, int width, float std, bool highpass = false)
{
	Mat im_filter = Mat::ones(Size(width, height), CV_32F);
	float u, v, t;
	int k = 0;
	for (long i = 0; i < height; i++)
		for (long j = 0; j < width; j++) {
			u = i - height / 2;
			v = j - width / 2;
			t = exp(-(u*u + v*v) / (2.0*std*std));
			if (highpass) t = 1 - t;//if high pass	
			im_filter.at<float>(i, j) = t;
		}
	return im_filter;
}

//Produce Butterworth filter in frequency domain
// height : height of the filter
// width  : width of the filter
// cutoffFreq:cutoff frequency where intensity is 50%
// order  : order n
// highpass: true=highpass, false=lowpass
Mat ButterworthFilter(int height, int width, float cutoffFreq, int order, bool highpass = false)
{
	Mat im_filter = Mat::ones(Size(width, height), CV_32F);
	float u, v, t;
	int k = 0;
	for (long i = 0; i < height; i++)
		for (long j = 0; j < width; j++) {
			u = i - height / 2;
			v = j - width / 2;
			t = (u*u + v*v) / (cutoffFreq*cutoffFreq);
			if (highpass) t = 1 / t;//if high pass
			for (long k = 1; k < order; k++) t *= t;//for order n
			t = 1 / (1 + t);
			im_filter.at<float>(i, j) = t;
		}
	return im_filter;
}

//Add Gaussian noise
// src : single channel grayscale image input
// dst : single channel grayscale image output
// mean: mean
// std: standard deviation
void GaussianNoise(Mat src, Mat& dst, float mean, float std)
{
	Mat noise = Mat(src.size(), CV_32F);
	randn(noise, 0, 0.05);
	Mat im;
	normalize(src, im, 0.0, 1.0, NORM_MINMAX, CV_32F);
	im += noise;
	normalize(im, im, 0, 255, NORM_MINMAX, CV_8U); //normalize
	im.copyTo(dst);//copy to destination
}

int main(int argc, char** argv)
{
	//Get an image
	Mat image = imread("C:/opencv/lake.jpg", IMREAD_GRAYSCALE);
	if (!image.data) {
		printf("No image data \n");
		return -1;
	}
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", image);

	Mat im_complex; i2z(image, im_complex);//convert to complex type
	dft(im_complex, im_complex);//perform discrete fourier transform 

								//display Fourier spectrum
	Mat im_f; z2i(im_complex, im_f, true);//convert to grayscale
	fftshift(im_f);//shift quadrants to make the center origin
	namedWindow("Freq domain Image", WINDOW_AUTOSIZE);
	imshow("Freq domain Image", im_f);

	//Get a filter (freq domain)
	//Mat im_filter = ButterworthFilter(im_complex.rows, im_complex.cols, 50,2,true);
	Mat im_filter = GaussianFilter(im_complex.rows, im_complex.cols, 50, false);
	namedWindow("Filter", WINDOW_AUTOSIZE);
	imshow("Filter", im_filter);

	fftshift(im_filter);//shift quadrants for matching
						//multiply in freq domain (convolve in spatial domain)	
	Mat im_array[2]; split(im_complex, im_array);
	im_array[0] = im_array[0].mul(im_filter);
	im_array[1] = im_array[1].mul(im_filter);
	merge(im_array, 2, im_complex);//combine these 2 into a complex image

	dft(im_complex, im_complex, DFT_INVERSE);//perform inverse discrete fourier transform 
	Mat im_hp; z2i(im_complex, im_hp);//get grayscale
	GaussianNoise(im_hp, im_hp, 0, 0.05);//add noise
	namedWindow("Filtered Image", WINDOW_AUTOSIZE);
	imshow("Filtered Image", im_hp);

	//save the result
	imwrite("C:/opencv/blur.jpg", im_hp);
	waitKey(0);
	return 0;
}
