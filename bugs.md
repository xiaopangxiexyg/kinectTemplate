<!--
 * @Author: xiaopangxiexyg 2926143694@qq.com
 * @Date: 2024-01-08 16:25:46
 * @LastEditors: xiaopangxiexyg 2926143694@qq.com
 * @LastEditTime: 2024-01-08 16:27:54
 * @FilePath: /kinectRecognition_v3/bugs.md
 * @Description: 欲戴王冠，必承其重
 * Copyright (c) 2024 by XieYingge email: 2926143694@qq.com, All Rights Reserved.
-->
# 

## Azure Kinect

[error] [t=45724] /__w/1/s/extern/Azure-Kinect-Sensor-SDK/src/capturesync/capturesync.c (142): replace_sample(). capturesync_drop, releasing capture early due to full queue TS:   2368511 type:Color
深度信息处理太慢，深度流跟不上彩色流导致RGB队满，github上普遍说是供电问题或者硬件问题，建议更新固件，但是我觉得是GPU没用上
