#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat C = (Mat_<double>(2,2) << 0, -1, 2, 3);
    cout << "C = " << endl << " " << C << endl << endl;
	Mat D=C.mul(C);
	cout << "D = " << endl << " " << D << endl << endl;
	Mat E = D +1;
	cout << "E = " << endl << " " << E << endl << endl;

	Mat F = D/E;
	cout << "F = D / E" << endl << " " << F << endl << endl;
	//cout<<"Sum: " << sum(C)[0]<<endl;
	//Mat E = Mat::eye(2, 2, CV_64F);	

	waitKey(5000);
	return 0;
}

