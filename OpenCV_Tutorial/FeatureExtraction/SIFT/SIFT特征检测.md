## SIFT特征检测(课程笔记)

## 1 SIFT特征检测介绍

- 建立尺度空间,寻找极值
- 关键点定位(寻找关键点准确位置与删除弱边缘)
- 关键点方向指定
- 关键点描述子

## 2 实现步骤 

### 2.1 建立尺度,寻找极值

- 构建图像高斯金字塔,求取DOG,发现最大与最小值在每一级
- 构建的图像高斯金字塔,每一层根据sigma的值不同,可以分为几个等级,最少有4个

### 2.2 关键点定位 

- 我们在像素级别获得了极值点的位置,但是更准确的值应该在亚像素位置,如何得到这个过程称为关键点(准确/精准)定位
- 删除边缘-通过hassian矩阵特征值实现,小于阈值自动放弃

### 2.3 关键点方向指定

- 求得每一层对应的图像梯度,根据给定的窗口大小计算每个高斯权重,sigma=scale*1.5,0~360之间建立36个直方图Bins
- 找最高峰对应的Bin,大于max*80%的都保留
- 这样就实现了旋转不变性,提高匹配时候的稳定性
- 大约有15%的关键点会有多个方向

### 2.4 关键点描述子

- 拟合多项式插值寻找最大Peak
- 得到描述子=4\*4\*8=128

通过获取到以上的特征以后就可以取做匹配了.SIFT算是一个比较准确的算法.

## 3 代码演示

使用到xfeatures2d::SIFT::create()函数.

代码实现:

```
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
        Mat src = imread("D:/vcprojects/images/test.png", IMREAD_GRAYSCALE);
        if (src.empty()) {
                printf("could not load image...\n");
                return -1;
        }
        namedWindow("input image", CV_WINDOW_AUTOSIZE);
        imshow("input image", src);

        int numFeatures = 400;
        Ptr<SIFT> detector = SIFT::create(numFeatures);
        vector<KeyPoint> keypoints;
        detector->detect(src, keypoints, Mat());
        printf("Total KeyPoints : %d\n", keypoints.size());

        Mat keypoint_img;
        drawKeypoints(src, keypoints, keypoint_img, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
        namedWindow("SIFT KeyPoints", CV_WINDOW_AUTOSIZE);
        imshow("SIFT KeyPoints", keypoint_img);

        waitKey(0);
        return 0;
}

```



## 参考文献

- 贾志刚课件







