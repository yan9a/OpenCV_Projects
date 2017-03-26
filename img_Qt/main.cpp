#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv )
{
    Mat image,bw_img;
    image = imread( "/home/yan/lena.jpg", 1 );
    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Original Image", WINDOW_AUTOSIZE );
    imshow("Original Image", image);
    cvtColor(image, bw_img, COLOR_BGR2GRAY);
    namedWindow("BW Image", WINDOW_AUTOSIZE );
    imshow("BW Image", bw_img);
    waitKey(0);
    return 0;
}
