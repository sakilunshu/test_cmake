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

    //获取图片宽度和高度
    int width = image.cols;
    int height = image.rows;
    cout << "图片宽度: " << width << ", 高度: " << height << endl;

    //定义ROI区域
    int cropWidth = 300;
    int cropHeight = 200;
    int startX = (width - cropWidth) / 2; 
    int startY = (height - cropHeight) / 2; 

    if(cropWidth > width || cropHeight > height) {
        cout << "裁剪区域超出图片范围，请调整裁剪尺寸。" << endl;
        return -1;
    }

    Rect roi(startX, startY, cropWidth, cropHeight);

    //裁剪图片
    Mat croppedImage = image(roi).clone();

    //保存裁剪后的图片
    string savePath = "/home/sakilunshu/桌面/test_cmake/Resources/cropped_image.jpg";
    imwrite(savePath, croppedImage);
    cout << "裁剪后的图片已保存到: " << savePath << endl;   

    //显示结果
    imshow("Original Image", image);
    imshow("Cropped Image", croppedImage);
    waitKey(0); 
    return 0;
}