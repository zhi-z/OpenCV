#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

/*
 本例子要学会使用指针获取像素点，然后对像素点进行赋值。
*/
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("C:/Users/DataH/Desktop/GitHub/OpenCV/OpenCV_Tutorial/OpenCV-Basic/2.矩阵的掩膜操作/image/2.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	/*
	int cols = (src.cols-1) * src.channels();
	int offsetx = src.channels();
	int rows = src.rows;

	dst = Mat::zeros(src.size(), src.type());
	for (int row = 1; row < (rows - 1); row++) {
		const uchar* previous = src.ptr<uchar>(row - 1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row + 1);
		uchar* output = dst.ptr<uchar>(row);
		for (int col = offsetx; col < cols; col++) {
			output[col] = saturate_cast<uchar>(5 * current[col] - (current[col- offsetx] + current[col+ offsetx] + previous[col] + next[col]));
		}
	}
	*/
	// 这个函数用于计算执行的时间
	double t = getTickCount();
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, dst, src.depth(), kernel);
	double timeconsume = (getTickCount() - t) / getTickFrequency();
	printf("tim consume %.2f\n", timeconsume);

	namedWindow("contrast image demo", CV_WINDOW_AUTOSIZE);
	imshow("contrast image demo", dst);

	waitKey(0);
	return 0;
}