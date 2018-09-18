#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main(int argc, char** aggv) {
	char input_win[] = "input image";

	char watershed_win[] = "watershed segmentation demo";
	Mat src = imread("C:/Users/DataH/Desktop/GitHub/OpenCV/OpenCV_Tutorial/OpenCV-Basic/34.图像分割综合例子/image/test_image.png");
	
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}

	namedWindow(input_win, CV_WINDOW_AUTOSIZE);
	imshow(input_win, src);

	// 1.change the background
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255)) {
				src.at<Vec3b>(row, col)[0] = 0;
				src.at<Vec3b>(row, col)[1] = 0;
				src.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	namedWindow("background output", CV_WINDOW_AUTOSIZE);
	imshow("background output", src);

	// 2.sharp(锐化，为下一步二值化做准备，提高对比度)
	// create kernel
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	// make it more sharp
	Mat imgLaplance;
	Mat sharp = src;
	filter2D(sharp, imgLaplance, CV_32F, kernel, Point(-1, -1), 0);
	src.convertTo(sharp, CV_32F);
	Mat imgResult = sharp - imgLaplance;
	// show
	imgResult.convertTo(imgResult, CV_8UC3);
	imgLaplance.convertTo(imgLaplance, CV_8UC3);
	namedWindow("sharp result", CV_WINDOW_AUTOSIZE);
	imshow("sharp result", imgResult);

	// 3.conver to binary
	Mat binImg;
	cvtColor(imgResult, binImg, CV_BGR2GRAY);
	threshold(binImg,binImg,40,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
	imshow("Binary Image", binImg);

	// 4.distance tranformation
	Mat distImg;
	distanceTransform(binImg, distImg, CV_DIST_L1, 3,5);
	// 5.再次进行二值化，得到标记
	normalize(distImg, distImg, 0, 1., NORM_MINMAX);
	imshow("distance image", distImg);
	// 6.try to get marker(使用阈值的方式保留距离大于0.4的值)
	threshold(distImg, distImg, 0.2, 1,CV_THRESH_BINARY);
	// 7.腐蚀
	Mat k1 = Mat::ones(13,13,CV_8UC1);
	erode(distImg, distImg, k1, Point(-1, -1));
	imshow("distance binary image", distImg);

	// 通过以上的结果得出来之后一个个点事一样的，这时候我们需要给它们进行编号
	// marker(进行标记之前要把图像转换成八位的)
	Mat dist_8u;
	distImg.convertTo(dist_8u, CV_8U);
	// find contours 
	vector<vector<Point>> contours;
	findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	
	// create markers image
	Mat markers = Mat::zeros(src.size(), CV_32SC1);
	// draw markers 
	for (size_t i = 0; i < contours.size(); i++) {
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1),-1);
	}
	
	// draw background circle
	circle(markers, Point(5, 5),3,CV_RGB(255, 255, 255), -1);
	imshow("markers demo", markers * 1000);

	// perform watershed
	watershed(src, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	// 取反
	bitwise_not(mark, mark, Mat());
	imshow("watershed image",mark);

	// 以上得到的结果得到不同的灰度区域，一下就是对这些灰度区域进行不同的着色

	// generate random color
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++) {
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	// fill with color and display final result
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	for (int row = 0; row < markers.rows; row++) {
		for (int col = 0; col < markers.cols; col++) {
			int index = markers.at<int>(row, col);
			if (index > 0 && index <= static_cast<int>(contours.size())) {
				dst.at<Vec3b>(row, col) = colors[index - 1];
			}
			else {
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("Final Result", dst);


	waitKey(0);
	return 0;
}