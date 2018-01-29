#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

Mat src, src_gray, dst;
int threshold_value = 128;
int threshold_type = 0;
int const max_BINARY_value = 255;
void Threshold_changed(int, void*);
const char* window_name = "Thresholding";

int main()
{
//src = imread("/home/yan/ka.jpg", IMREAD_COLOR);
src = imread("c:/opencv/ka.jpg", IMREAD_COLOR);
if (src.empty()) { return -1;}

namedWindow("Original", WINDOW_AUTOSIZE);
imshow("Original",src);

cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
namedWindow(window_name,WINDOW_NORMAL); // Create a window to display results

// Create Trackbar to choose type of Threshold
//Type: 0= Binary, 1= Binary Inverted,  
// 2= Truncate, 3= To Zero, 4= To Zero Inverted,
// 5= Adaptive threshold using ADAPTIVE_THRESH_GAUSSIAN_C
int const max_type = 5;
createTrackbar("Type", 
window_name, //window for trackbar
&threshold_type, // value to be updated according to trackbar
max_type, //range
Threshold_changed);//function to be called everytime trackbar is changed

// Create Trackbar to choose Threshold value
int const max_value = 255;
createTrackbar("Value",
window_name, &threshold_value,
max_value, Threshold_changed); 

Threshold_changed(0, 0); // Call the function to initialize

//loop until 'Esc' key is pressed
for (;;) {
char c = (char)waitKey(20);
if (c == 27) { break;}
}

//save the resulting binary image
imwrite("c:/opencv/ka_binary.jpg",dst);
return 0;
}
void Threshold_changed(int, void*)
{
if (threshold_type == 5) {
adaptiveThreshold(src_gray, dst, max_BINARY_value, 
ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
}
else {
threshold(src_gray, dst, threshold_value, 
max_BINARY_value, threshold_type);
}
imshow(window_name, dst);
}
