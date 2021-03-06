# Harris角点检测(Python实现)

## 1. 简介

 角点是图像很重要的特征,对图像图形的理解和分析有很重要的作用。角点在保留图像图形重要特征的同时,可以有效地减少信息的数据量,使其信息的含量很高,有效地提高了计算的速度,有利于图像的可靠匹配,使得实时处理成为可能。角点在三维场景重建运动估计，目标跟踪、目标识别、图像配准与匹配等计算机视觉领域起着非常重要的作用。在现实世界中，角点对应于物体的拐角，道路的十字路口、丁字路口等。

## 2. Harris角点检测基本原理

 人眼对角点的识别通常是在一个局部的小区域或小窗口完成的。**如果在各个方向上移动这个特征的小窗口，窗口内区域的灰度发生了较大的变化，那么就认为在窗口内遇到了角点。**如果这个特定的窗口在图像各个方向上移动时，窗口内图像的灰度没有发生变化，那么窗口内就不存在角点；如果窗口在某一个方向移动时，窗口内图像的灰度发生了较大的变化，而在另一些方向上没有发生变化，那么，窗口内的图像可能就是一条直线的线段。

对于过多的理论这里不再多说，下面也提供了一篇比较详细的理论知识．

## 3. OpenCV API与代码演示

代码详见[ipynb文件](https://github.com/zhi-z/OpenCV/blob/master/OpenCV_Tutorial/FeatureExtraction/CornerDetection/harris/Harris.ipynb).

## 参考文献

- [Harris角点检测](https://www.cnblogs.com/king-lps/p/6375424.html)