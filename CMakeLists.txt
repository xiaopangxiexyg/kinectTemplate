cmake_minimum_required( VERSION 3.12)

include_directories(.)

project(camera)
# add_definitions(-std = c++11)

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_BUILD_TYPE Debug)
set(OpenCV_DIR "usr/local/bin")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/workspace)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

#GPU
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
# 如果你是不同显卡，请设置为显卡对应的号码参考这里：https://developer.nvidia.com/zh-cn/cuda-gpus#compute
set(CUDA_GEN_CODE "-gencode=arch=compute_86,code=sm_86")

set(CUDA_DIR     "/usr/local/cuda")

# 需要与cuda、tensorRT配对
set(CUDNN_DIR    "/usr/local/cuda")

find_package( k4a REQUIRED )
find_package( OpenCV REQUIRED )
# find_package(CUDA REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRE}
    /usr/include
    ${PROJECT_SOURCE_DIR}/src
    # ${CUDA_DIR}/include
    # ${CUDNN_DIR}/include
    )

    # link_directories(
    #     ${CUDA_DIR}/lib64
    #     ${CUDNN_DIR}/lib
    # )

# 把所有的cpp文件都添加到这里来
aux_source_directory(./src DIR_SRCS)
add_executable( camera ${DIR_SRCS})    

target_link_libraries(camera ${OpenCV_LIBS})
target_link_libraries(camera k4a::k4a)
# target_link_libraries(camera cuda cublas cudart cudnn)