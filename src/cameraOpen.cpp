/*
 * @Author: xiaopangxiexyg 2926143694@qq.com
 * @Date: 2024-01-08 15:26:17
 * @LastEditors: xiaopangxiexyg 2926143694@qq.com
 * @LastEditTime: 2024-01-08 16:32:02
 * @FilePath: /kinectRecognition_v3/src/cameraOpen.cpp
 * @Description: 欲戴王冠，必承其重
 * Copyright (c) 2024 by XieYingge email: 2926143694@qq.com, All Rights Reserved.
 */
#include "inc/cameraOpen.h"

void initialize(uint32_t &device_count, k4a::device &device, k4a_device_configuration_t &config, k4a::capture &capture)
{
    // 发现已连接的设备数
    device_count = k4a::device::get_installed_count();
    if (device_count == 0)
    {
        std::cout << "Error: no K4A devices found. " << std::endl;
        return;
    }
    else
    {
        std::cout << "Found " << device_count << " connected devices. " << std::endl;
    }

    // 打开（默认）设备
    device = k4a::device::open(K4A_DEVICE_DEFAULT);
    std::cout << "Done: open device. " << std::endl;

    // 配置并启动设备
    config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
    config.camera_fps = K4A_FRAMES_PER_SECOND_15;
    config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32; // A是alpha，具有alpha纹理格式的颜色
    config.color_resolution = K4A_COLOR_RESOLUTION_720P; // 1280x720
    config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;    // 640x576
    // config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;// 512x512
    config.synchronized_images_only = true; // ensures that depth and color images are both available in the capture
    device.start_cameras(&config);
    std::cout << "Done: start camera." << std::endl;
    device.start_imu();
    std::cout << "Done: start imu." << std::endl;

    // 稳定化
    int iAuto = 0; // 用来稳定，类似自动曝光
    while (iAuto < 30)
    {
        if (device.get_capture(&capture))
            iAuto++;
    }
}

void finalize(k4a::device &device)
{
    // Stop Cameras
    device.stop_cameras();
    // Close Device
    device.close();
    // Close Window
    cv::destroyAllWindows();
}

