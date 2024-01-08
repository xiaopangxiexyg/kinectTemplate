/*
 * @Author: xiaopangxiexyg 2926143694@qq.com
 * @Date: 2024-01-08 15:30:53
 * @LastEditors: xiaopangxiexyg 2926143694@qq.com
 * @LastEditTime: 2024-01-08 16:34:55
 * @FilePath: /kinectRecognition_v3/src/main.cpp
 * @Description: 欲戴王冠，必承其重
 * Copyright (c) 2024 by XieYingge email: 2926143694@qq.com, All Rights Reserved.
 */
#include "inc/myMath.h"
#include "inc/cameraOpen.h"

uint32_t device_count;
k4a::device device;
k4a_device_configuration_t config;
k4a::capture capture;
k4a::image rgbImage;
k4a::image depthImage;
// k4a::image irImage;
k4a::image transformed_depthImage;
k4a::calibration k4aCalibration;
k4a::transformation k4aTransformation;
// CV
cv::Mat cv_rgbImage;
// cv::Mat cv_hsvImage;
// cv::Mat cv_hsvImageMarked;
cv::Mat cv_depthImage;
// cv::Mat cv_grayImage;
// cv::Mat blur_laplace;
// cv::Mat erodeElement;
// cv::Mat dilateElement;
// cv::Mat filledImage; // circleMask
std::vector<std::vector<cv::Point>> selectedContours;    

// 开摄像头，深度图对准到RGB，转CV数据结构
void run()
{
    // 初始化，内参，转换矩阵
    initialize(device_count, device, config, capture);
    k4aCalibration = device.get_calibration(config.depth_mode, config.color_resolution);
    k4aTransformation = k4a::transformation(k4aCalibration);
    // main loop
    while(true)
    {
        // main loop duration
        auto start = std::chrono::system_clock::now();
        if (device.get_capture(&capture, std::chrono::milliseconds(100))) 
        {
            // 1. 从摄像头读取图像，转CV数据结构
            rgbImage = capture.get_color_image();
            depthImage = capture.get_depth_image();
            cv_rgbImage = cv::Mat(rgbImage.get_height_pixels(), rgbImage.get_width_pixels(), CV_8UC4, (void*)rgbImage.get_buffer());
            cv::cvtColor(cv_rgbImage,cv_rgbImage,cv::COLOR_BGRA2BGR);
            /*深度图读取并转化，此段有用不能删*/
            // 将深度图变形为彩色相机的几何形状来生成的,生成的变换深度图为彩色图像的每个像素提供相应的深度读数,实时性差的罪魁祸首
            transformed_depthImage = k4aTransformation.depth_image_to_color_camera(depthImage);                
            cv_depthImage = cv::Mat(transformed_depthImage.get_height_pixels(), transformed_depthImage.get_width_pixels(), CV_16U, 
                            (void*)transformed_depthImage.get_buffer(), static_cast<size_t>(transformed_depthImage.get_stride_bytes()));
            // cv_depthImage.convertTo(cv_depthImage, CV_8U, 1);

            # if DEBUG_std_cout == 2
                std::cout << "Size of rgb image is: " << cv_rgbImage.size 
                        << "  channels of rgb image is: "<< cv_rgbImage.channels() << std::endl;
                std::cout << "Size of depth image is: " << cv_depthImage.size 
                        << "  channels of depth image is: "<< cv_depthImage.channels() << std::endl;
                cv::Mat depth_show;
                cv_depthImage.convertTo(depth_show, CV_8U, 1);
                cv::imshow("color", cv_rgbImage);
                cv::imshow("depth", depth_show);       // 校准之后慢到家了k4aCalibration 
            # endif
            // if结束，毁尸灭迹
            // 用到的
            cv_rgbImage.release();
            cv_depthImage.release();
            // cv_grayImage.release();
            // blur_laplace.release(); // TEST:没有用到但是释放是否会引起错误
            // filledImage.release();
            // std::vector<std::vector<cv::Point>>().swap(selectedContours);
            // cv_hsvImage.release();
            // cv_hsvImageMarked.release();
            // 不知道该不该释放的
            // erodeElement.release();
            // dilateElement.release(); // 释放已释放的内存会导致段错误
            // 几次因为没有释放新定义的cv::Mat而报错了！

            capture.reset();
            if(cv::waitKey(1) == 27)
                break;
        }
        // while结束，计时结束
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        # if DEBUG_std_cout == 1
            std::cout << double(duration.count()) * std::chrono::microseconds::period::num /
                        std::chrono::microseconds::period::den
                    << "s" << std::endl;       
        # endif
    }
    // run()结束，释放，关闭设备
    // 释放，关闭设备
    rgbImage.reset();
    depthImage.reset();
    // capture.reset();
    finalize(device);
    
}



int main( int argc, char* argv[] )
{
    try{
        run();
    }
    catch( const k4a::error& error ){
        std::cout << error.what() << std::endl;
    }

    return 0;
}
