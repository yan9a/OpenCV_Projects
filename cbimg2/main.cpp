#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", img);
    waitKey(0);
    return 0;
}



