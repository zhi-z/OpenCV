# Canny边缘检测

## 1.Canny算法介绍

1986年提出的

## 2.Canny 五步

2.1 高斯滤波（GaussianBlur)

2.2 灰度变换（cvtColor）

2.3 计算梯度（Sobel/Scharr)

2.4 非最大信号抑制

2.4 高低阈值输出二值化图像（把高于或低于阈值的值去掉）

常见的高低阈值比一般为2:1或者3:1

## 3.Canny API

3.1 c++ API

一般用L1做归一化。

3.2 python API

```
edge = cv2.Canny(image, threshold1, threshold2[, edges[, apertureSize[, L2gradient ]]]) 
```

edge  --  函数返回 一副二值图（黑白），其中包含检测出来的边缘
image --   需要处理的原图像，该图像必须为单通道的灰度图
threshold1  --  阈值1

threshold2  --  阈值2

 threshold2  是较大的阈值，用于检测图像中明显的边缘，但一般情况下检测的效果不会那么完美，边缘检测出来是断断续续的。所以这时候用较小的 threshold1  （第一个阈值）用于将这些间断的边缘连接起来。

apertureSize  --  Sobel 算子的大小。

L2gradient   --  一个布尔值，如果为 True ,刚使用更精确的 L2 范数进行计算（即两个方向的倒数的平方和再开放）， False 将使用L1 范数（直接将两个方向导数的绝对值相加）。



一般抑制越大，保留的边缘越小。