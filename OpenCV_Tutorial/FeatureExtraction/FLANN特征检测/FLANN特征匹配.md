# FLANN特征匹配

## 1 简介

是一种快速的特征匹配,在高维的图像中匹配的速度非常快.具体的说他是一个库,是Opencv把它拿过来了.

通过特征检测,特征提取.然后通过特征计算得到特征描述子,然后就一与对象进行比对.相对与BF做比较,速度更快.

![1536380392078](image/flann.png)

## 2 代码演示

 一般计算的时候用汉明距离,而不用欧氏距离,一般欧氏距离计算的比较多.

```
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main(int argc, char** argv) {
        Mat img1 = imread("D:/vcprojects/images/box.png", IMREAD_GRAYSCALE);
        Mat img2 = imread("D:/vcprojects/images/box_in_scene.png", IMREAD_GRAYSCALE);
        if (!img1.data || !img2.data) {
                return -1;
        }
        imshow("object image", img1);
        imshow("object in scene", img2);

        // surf featurs extraction
        int minHessian = 400;
        Ptr<SURF> detector = SURF::create(minHessian);
        vector<KeyPoint> keypoints_obj;
        vector<KeyPoint> keypoints_scene;
        Mat descriptor_obj, descriptor_scene;
        detector->detectAndCompute(img1, Mat(), keypoints_obj, descriptor_obj);
        detector->detectAndCompute(img2, Mat(), keypoints_scene, descriptor_scene);

        // matching
        FlannBasedMatcher matcher;
        vector<DMatch> matches;
        matcher.match(descriptor_obj, descriptor_scene, matches);

        // find good matched points
        double minDist = 1000;
        double maxDist = 0;
        for (int i = 0; i < descriptor_obj.rows; i++) {
                double dist = matches[i].distance;
                if (dist > maxDist) {
                        maxDist = dist;
                }
                if (dist < minDist) {
                        minDist = dist;
                }
        }
        printf("max distance : %f\n", maxDist);
        printf("min distance : %f\n", minDist);
        vector<DMatch> goodMatches;
        for (int i = 0; i < descriptor_obj.rows; i++) {
                double dist = matches[i].distance;
                if (dist < max(3 * minDist, 0.02)) {
                        goodMatches.push_back(matches[i]);
                }
        }

        Mat matchesImg;
        drawMatches(img1, keypoints_obj, img2, keypoints_scene, goodMatches, matchesImg, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
        );
        imshow("Flann Matching Result", matchesImg);

        waitKey(0);
        return 0;
}
                      
```

