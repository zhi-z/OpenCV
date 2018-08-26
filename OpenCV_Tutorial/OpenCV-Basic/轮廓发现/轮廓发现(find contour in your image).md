# 轮廓发现(find contour in your image)

## 1 概述

轮廓发现是基于图像边缘提取基础寻找对象轮廓的方法.所以边缘提取的阈值选定会影响最终发现结果.

## 2 Opencv API

- findContours发现轮廓
- drawContours绘制轮廓

## 3 演示过程(Opencv Python实现)

- 输入图像转换为灰度图像ctColor
- 使用Canny进行边缘提取,得到二值化图像
- 使用fandContours寻找轮廓
- 使用drawContors绘制轮廓

