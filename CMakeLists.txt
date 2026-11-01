cmake_minimum_required(VERSION 3.10)
project(OpenCVProject)

# 查找系统中的 OpenCV 库
find_package(OpenCV REQUIRED)

# 编译 ROIcut.cpp 生成 opencv_test
add_executable(opencv_test  ROIcut.cpp)

# 链接 OpenCV 的库文件
target_link_libraries(opencv_test ${OpenCV_LIBS})

add_executable(opencv_test ROIcut.cpp) 