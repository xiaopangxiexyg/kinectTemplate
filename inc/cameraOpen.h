 /*
 * @Author: xiaopangxiexyg 2926143694@qq.com
 * @Date: 2024-01-08 15:26:26
 * @LastEditors: xiaopangxiexyg 2926143694@qq.com
 * @LastEditTime: 2024-01-08 16:37:38
 * @FilePath: /kinectRecognition_v3/inc/cameraOpen.h
 * @Description: 欲戴王冠，必承其重
 * Copyright (c) 2024 by XieYingge email: 2926143694@qq.com, All Rights Reserved.
 */
#ifndef CAMERAOPEN_H_
#define CAMERAOPEN_H_

#include <iostream>

#include <chrono>
//Kinect DK
#include <k4a/k4a.hpp>
#include <k4a/k4atypes.h>
// #include "inc/util.h"
//OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/dictionary.hpp>

// 宏
// 方便控制是否 std::cout 信息
#define DEBUG_std_cout 1
/*
1 主循环计时
2 show cv_rgbImage cv_depthImage

*/

struct Circle
{
    double circularity;
    std::vector<std::vector<cv::Point>> contours;
};

// Run
void run();
// Update
void update();
// 抠出前景
void getCircle();
// 计算圆形度
double calculateCircularity(const std::vector<cv::Point>& contour);
// Detect
char getColor(); // TODO:传入参数类型可能要改
// Distance
float howFar(); // 参数类型和返回值类型
// transformation of coordinates
float transCoordinates(); // 参数类型和返回值类型

/*垃圾代码缓冲区*/
void filteredByColor();

void initialize(uint32_t &device_count, k4a::device &device, k4a_device_configuration_t &config, k4a::capture &capture);
// Finalize
void finalize(k4a::device &device);   

cv::Point3f rgbPixel2RGB(const k4a_calibration_t *calibration,const cv::Point2f center,float depth);

#endif // _KINECTCLASS_