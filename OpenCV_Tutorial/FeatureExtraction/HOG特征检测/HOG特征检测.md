# HOG特征检测

## 1 HOG特征检测介绍

大概的意思是基于直方图在寻找图像的特征.实现的大概过程如下:

- 灰度图像转换
- 梯度计算
- 分网格的梯度方向直方图
- 描述述子
- 块描述子归一化
- **特征数据与检测窗口**
- **匹配方法**

后面两步先不进行理解.主要先完成前面的特征提取操作.得到特征以后可以使用机器学习的方法进行分类,得到最终的结果.

### 1.1 灰度转换

![1536157776117](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/1536157776117.png)

### 1.2 梯度计算

![1536158650495](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/gradient.png)

### 1.3 分网格的梯度方向直方图

![1536157948450](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/grid.png)

### 1.4 块描述子

![1536158297258](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/R_HOG.png)

### 1.5 块描述子归一化

![1536158444619](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/L2.png)

### 1.6 特征数据与检测窗口

![1536158556329](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/feature_detetion.png)



## 2 代码演示

HOG+SVM实现行人检测.API:

![1536159012770](/home/datah/Desktop/GitHub/OpenCV/OpenCV_Tutorial/FeatureExtraction/HOG特征检测/image/API.png)

代码实现:

```
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
        Mat src = imread("D:/vcprojects/images/HOGV.png");
        if (src.empty()) {
                printf("could not load image...\n");
                return -1;
        }
        namedWindow("input image", CV_WINDOW_AUTOSIZE);
        imshow("input image", src);

        /*Mat dst, dst_gray;
        resize(src, dst, Size(64, 128));
        cvtColor(dst, dst_gray, COLOR_BGR2GRAY);
        HOGDescriptor detector(Size(64, 128), Size(16, 16), Size(8, 8), Size(8, 8), 9);

        vector<float> descriptors;
        vector<Point> locations;
        detector.compute(dst_gray, descriptors, Size(0, 0), Size(0, 0), locations);
        printf("number of HOG descriptors : %d", descriptors.size());
        */
        HOGDescriptor hog = HOGDescriptor();
        hog.setSVMDetector(hog.getDefaultPeopleDetector());

        vector<Rect> foundLocations;
        hog.detectMultiScale(src, foundLocations, 0, Size(8, 8), Size(32, 32), 1.05, 2);
        Mat result = src.clone();
        for (size_t t = 0; t < foundLocations.size(); t++) {
                rectangle(result, foundLocations[t], Scalar(0, 0, 255), 2, 8, 0);
        }
        namedWindow("HOG SVM Detector Demo", CV_WINDOW_AUTOSIZE);
        imshow("HOG SVM Detector Demo", result);

        waitKey(0);
        return 0;
}
~                                                     
```

