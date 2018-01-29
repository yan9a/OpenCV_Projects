#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
int match_method;

void MatchingMethod(int, void*)
{
// Source image to display with rectangle overlay
Mat img_display;
img.copyTo(img_display);

// Do the Matching and Normalize
matchTemplate(img, templ, result, match_method);
normalize(result, result, 0, 1, NORM_MINMAX);

// Localizing the best match with minMaxLoc
double minVal, maxVal;
Point minLoc, maxLoc, matchLoc;
minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. 
// For all the other methods, the higher the better
if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED) { matchLoc = minLoc; }
else { matchLoc = maxLoc; }

// Show me what you got
Point matchLoc2(matchLoc.x + templ.cols, matchLoc.y + templ.rows);
rectangle(img_display, matchLoc, matchLoc2, Scalar::all(0), 2, 8, 0);
rectangle(result, matchLoc, matchLoc2, Scalar::all(0), 2, 8, 0);
imshow("Source", img_display);
imshow("Result", result);
}

int main()
{
/// Load image and template
img = imread("c:/opencv/stand.jpg");
templ = imread("c:/opencv/template.jpg");

/// Create windows
namedWindow("Source", CV_WINDOW_AUTOSIZE);
namedWindow("Result", CV_WINDOW_AUTOSIZE);
namedWindow("Template", CV_WINDOW_AUTOSIZE);
imshow("Template", templ);
/// Create Trackbar
createTrackbar("Method: ", "Source", &match_method, 5, MatchingMethod);
MatchingMethod(0, 0);

waitKey(0);
return 0;
}
