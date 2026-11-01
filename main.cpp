#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 创建一个纯黑色的图片 (宽 400，高 300)
    cv::Mat img(300, 400, CV_8UC3, cv::Scalar(0, 0, 0));
    
    // 在图片上画一个绿色的圆
    cv::circle(img, cv::Point(200, 150), 50, cv::Scalar(0, 255, 0), -1);
    
    // 保存图片到 build 目录下
    cv::imwrite("opencv_test.jpg", img);
    
    std::cout << "OpenCV 运行成功！图片已生成！" << std::endl;
    return 0;
}