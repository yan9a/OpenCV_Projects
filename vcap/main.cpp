#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;
std::string to_string(int i)
{
std::stringstream ss;
ss << i;
return ss.str();
}
int main(int argc, char** argv)
{
//VideoCapture cap(0);//Default camera
VideoCapture cap("/home/yan/sensor.mp4");//open video file
//VideoCapture cap("c:/opencv/sensor.mp4"); //open video file
if (!cap.isOpened()) {
printf("Video is not opened. \n");
return -1;
}
else {
printf("Video is opened. \n");
}

union { int v; char c[5]; } uEx;
uEx.v = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
uEx.c[4] = '\0';
printf("Codec: %s \n",uEx.c);

Size S = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
printf("Frame size: %d x %d \n",S.width,S.height);

double rate = cap.get(CV_CAP_PROP_FPS);//Frame rate
printf("Frame rate: %f \n", rate);
int dperiod = 1000 / rate;

int c = cap.get(CV_CAP_PROP_FRAME_COUNT);
printf("Frame count: %d \n", c);
namedWindow("Frame", 1);

int ex = CV_FOURCC('M', 'J', 'P', 'G');
//int ex = CV_FOURCC('X', 'V', 'I', 'D');//https://www.xvid.com/
//int ex = -1;//pop up window to choose
//const string vpath="c:/opencv/vdowr.avi";
const string vpath="/home/yan/vdowr.avi";
VideoWriter outputVideo(vpath, ex , rate, S, true);
if (!outputVideo.isOpened())
{
cout << "Could not open the output video to write."<< endl;
waitKey(5000);
return -1;
}

long ms,p;
Mat frame,img;
string str;
for (int i = 0;; i++) {
if (!cap.read(frame)) break;
p = cap.get(CV_CAP_PROP_POS_FRAMES);
//printf("Frame: %ld \n", p);
ms = cap.get(CV_CAP_PROP_POS_MSEC);
str = to_string(ms) + " ms";
rectangle(frame, Point(10, 10), Point(200, 60), CV_RGB(255, 0,0), CV_FILLED);
putText(frame, str, Point(25, 45),FONT_HERSHEY_PLAIN,2.0, CV_RGB(0, 255, 0), 2.0);
outputVideo << frame;
imshow("Frame", frame);
if (waitKey(dperiod) == 27) break; //if 'Esc' key is pressed
}
cap.release();
outputVideo.release();
//waitKey(5000);
return 0;
}
