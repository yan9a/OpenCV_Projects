#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
Mat image;
image = imread("C:/opencv/MyanmarMap6.PNG", IMREAD_GRAYSCALE);
if (!image.data) { printf("No image data \n"); return -1; }
namedWindow("Display Image", WINDOW_AUTOSIZE);
imshow("Display Image", image);
double latNorth = 28.55;
double latSouth = 9.84;
double logEast = 101.17;
double logWest = 92.17;
double sxi = 0, syi = 0;//for image
double slat = 0, slog = 0;//for latitude and longitude
double cslat = 0, cslog = 0;//with compensation for 
// Universal Transverse Mercator (UTM) coordinate system
double si = 0;
double ilat, jlog;
double ci = 0;//compensated intensity
double sci = 0;//summation of ci
const double PI = 2 * acos(0.0);//get PI
//Manipulate pixels
long h = image.rows;
long w = image.cols;
long ithreshold = 138;
for (long i = 0; i < h; i++)
for (long j = 0; j < w; j++)
if (image.at<uchar>(i, j) > ithreshold) {
si += 1;//uniform pixel intensity
sxi += j;
syi += i;
ilat = latNorth - (latNorth - latSouth)*double(i) / double(h - 1);
jlog = logWest + (logEast - logWest)*double(j) / double(w - 1);
slog += jlog;
slat += ilat;
ci = cos(ilat*PI / 180.0);
sci += ci;
cslog += jlog*ci;
cslat += ilat*ci;
}

//image centroid
double cx = sxi / si;
double cy = syi / si;

//latitude and longitude centroid
double lat = slat / si;
double log = slog / si;

//compensated latitude and longitude centroid
double clat = cslat / sci;
double clog = cslog / sci;

printf("Centroid row col: [ %f , %f ] for image pixels. \n", cx, cy);
printf("Centroid lat log: [ %f , %f ] \n", lat, log);
printf("Centroid lat log: [ %f , %f ] after compensation for Mercator projection.\n", clat, clog);
waitKey(0);
return 0;
}
