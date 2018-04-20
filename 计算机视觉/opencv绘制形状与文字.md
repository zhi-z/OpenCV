# opencv绘制形状与文字



```
/*
	绘制形状与文字		
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
Mat bgImage;
const char* drawdemo_win = "draw shapes and text demo";
void MyLines();
void MyRectangle();
void MyEllipse();
void MyCircle();
void MyPolygon();
void RandomLineDemo();

int main(int argc, char** argv) {
	bgImage = imread("D:/vcprojects/images/test1.png");
	if (!bgImage.data) {
		printf("could not load image...\n");
		return -1;
	}
	//MyLines();
	//MyRectangle();
	//MyEllipse();
	//MyCircle();
	//MyPolygon();

	//绘制文字         文字            那个点           字体                     缩放                      
	//putText(bgImage, "Hello OpenCV", Point(300, 300), CV_FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 23, 200), 3, 8);
	//namedWindow(drawdemo_win, CV_WINDOW_AUTOSIZE);
	//imshow(drawdemo_win, bgImage);

	MyPolygon();
	waitKey(0);
	return 0;
}

//绘制线条
void MyLines() {
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 400;
	p2.y = 400;
	Scalar color = Scalar(0, 0, 255);
	line(bgImage, p1, p2, color, 1, LINE_AA);  //LINE_AA是反锯齿
}


//画矩形
void MyRectangle() {
	//            前两个参数为起始位置，后两个为宽高
	Rect rect = Rect(200, 100, 300, 300);
	Scalar color = Scalar(255, 0, 0);
	rectangle(bgImage, rect, color, 2, LINE_8);
}

//绘制椭圆
void MyEllipse() {
	Scalar color = Scalar(0, 255, 0);   
//			背景     椭圆的中心                               椭圆半径                             位置角度  范围角度  颜色    线条                          
	ellipse(bgImage, Point(bgImage.cols / 2, bgImage.rows / 2), Size(bgImage.cols / 4, bgImage.rows / 8), 90, 0, 360, color, 2, LINE_8);
}

//绘制圆
void MyCircle() {
	Scalar color = Scalar(0, 255, 255);
	//圆心
	Point center = Point(bgImage.cols / 2, bgImage.rows / 2);
	//     背景     圆心    半径  颜色  
	circle(bgImage, center, 150, color, 2, 8);
}


//画多边形
void MyPolygon() {
	Point pts[1][5];
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(100, 100);

	const Point* ppts[] = { pts[0] };
	int npt[] = { 5 };
	Scalar color = Scalar(255, 12, 255);

	fillPoly(bgImage, ppts, npt, 1, color, 8);
}


//随机线
void RandomLineDemo() {
	//生成随机数
	RNG rng(12345);
	Point pt1;
	Point pt2;                    
	Mat bg = Mat::zeros(bgImage.size(), bgImage.type());
	namedWindow("random line demo", CV_WINDOW_AUTOSIZE);
	for (int i = 0; i < 100000; i++) {
		//随机生成两个点
		//                 范围0到bgImage.cols
		pt1.x = rng.uniform(0, bgImage.cols);
		pt2.x = rng.uniform(0, bgImage.cols);
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);
		//生成随机颜色
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (waitKey(50) > 0) {
			break;
		}
		line(bg, pt1, pt2, color, 1, 8);
		imshow("random line demo", bg);
	}
}





```

