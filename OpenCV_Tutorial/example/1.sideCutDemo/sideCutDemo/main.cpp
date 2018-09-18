#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

Mat src, gray_src, dst;

const char* output_win = "Final Result";
int threshold_value = 100;
int max_level = 255;

void FindROI(int,void*);

int main(int argc,char** argv) {

	src = imread("C:/Users/DataH/Desktop/GitHub/OpenCV/OpenCV_Tutorial/example/1.sideCutDemo/image/test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}

	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	namedWindow(output_win,CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold", output_win, &threshold_value, max_level, FindROI);
	FindROI(0, 0);



	waitKey(0);
	return 0;
}


void FindROI(int,void*) {
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	Mat canny_output;

	Canny(gray_src,canny_output,threshold_value,threshold_value*2,3,false);

}