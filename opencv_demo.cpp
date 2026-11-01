#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
//读取照片
    string path = "/home/sakilunshu/桌面/test_cmake/Resources/test.jpg";
    Mat image = imread(path);
    
    if (image.empty()) {
        cout << "图片读取失败，请检查路径: " << path << endl;
        return -1;
    }

//转灰度图
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    int grayNonZero = countNonZero(grayImage);
    cout << "灰度图非零像素点数量: " << grayNonZero << endl;

//二值化图
    Mat binaryImage;
    threshold(grayImage, binaryImage, 127, 255, THRESH_BINARY);

//计算二值化图的非零像素点数量
    int binaryNonZero = countNonZero(binaryImage);
    int totalPixels = binaryImage.rows * binaryImage.cols;
    cout << "二值化图总像素点数量: " << totalPixels << endl;
    cout << "二值化图非零像素点数量: " << binaryNonZero << endl;

//保存新图像文件
    string savePath = "/home/sakilunshu/桌面/test_cmake/Resources/result_binary.jpg";
    imwrite(savePath, binaryImage);
    cout << "二值化图像已保存到: " << savePath << endl;

//显示结果
    imshow("Original Image", image);
    imshow("Gray Image", grayImage);
    imshow("Binary Image", binaryImage);

    imwrite("/home/sakilunshu/桌面/test_cmake/Resources/result_gray.jpg", grayImage);
    cout << "灰度图像已保存到: " << "/home/sakilunshu/桌面/test_cmake/Resources/result_gray.jpg" << endl;

    cout << "按任意键退出..." << endl;
    waitKey(0);
    return 0;
}