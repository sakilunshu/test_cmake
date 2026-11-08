#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(){
    //读取照片
    string test = "/home/sakilunshu/桌面/test_cmake/Resources/test2.jpg";
    Mat image = imread(test);
    if(image.empty()){
        cout << "图片读取失败，请检查路径: " << test << endl;
        return -1;
    }

    //转换到hsv色彩空间
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    //颜色阈值分割
    Mat mask;
    Scalar lowerBound(80, 100, 150);
    Scalar upperBound(130, 255, 255);

    //使用 inRange函数进行颜色分割
    inRange(hsv, lowerBound, upperBound, mask);

    //形态学操作
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(mask, mask, MORPH_OPEN, kernel);
    imshow("Mask",mask);

    //寻找轮廓
    vector<vector<Point>> contours;//轮廓集合
    vector<RotatedRect> light_bars;//灯条集合
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);   

    Mat result_img = image.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        //计算面积
        double area = contourArea(contours[i]);
        //不要不符合面积要求的轮廓
        if (area > 10 && area < 5000){
            RotatedRect rect = minAreaRect(contours[i]);//带旋转角度的框
            //求最小外接矩形
            float width = rect.size.width;
            float height = rect.size.height;

            float short_side = min(width, height);
            float long_side = max(width, height);

            float ratio = long_side / short_side;

            float area = width * height;

            cout << "Area: " << area << ", Width: " << width << ", Height: " << height << ", Ratio: " << ratio << endl;

            //长宽比过滤
            if (ratio > 2.0 && ratio < 10.0){
                //如果满足条件，绘制轮廓
                light_bars.push_back(rect);

                Point2f rect_points[4];
                rect.points(rect_points);

                //用醒目的颜色把轮廓画出来
                for (int j = 0; j < 4; j++) {
                    line(result_img, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 255, 0), 2);
                }
            }
        }    
    }

    //外层循环，代表第一个灯条
    for (size_t i = 0;i< light_bars.size();i++){
        //内层循环，代表第二个灯条
        for (size_t j = i+1;j < light_bars.size();j++){
            RotatedRect bar1 = light_bars[i];
            RotatedRect bar2 = light_bars[j];

            float h1 = max(bar1.size.width,bar1.size.height);
            float h2 = max(bar2.size.width,bar2.size.height);

            float height_diff = abs(h1 - h2);

            Point2f center1 = bar1.center;
            Point2f center2 = bar2.center;

            float x_diff = abs(center1.x - center2.x);
            float y_diff = abs(center1.y - center2.y);


            if (height_diff < 20 && x_diff < 200 && y_diff < x_diff * 0.5){
                //如果满足条件，绘制连接线
                line(result_img, center1, center2, Scalar(0, 0, 255), 2);

                Point2f armor_center = (center1 + center2) / 2;

                int roi_width = x_diff;
                int roi_height = max(h1, h2) * 1.2;

                int roi_x = armor_center.x - roi_width / 2;
                int roi_y = armor_center.y - roi_height / 2;

                roi_x = max(0, roi_x);
                roi_y = max(0, roi_y);
                roi_width = min(result_img.cols - roi_x, roi_width);
                roi_height = min(result_img.rows - roi_y, roi_height);

                Rect armor_rect(roi_x, roi_y, roi_width, roi_height);

                Mat roi_img = result_img(armor_rect);

                cv::imshow("Armor ROI", roi_img);
                cv::imwrite("Armor_roi.jpg", roi_img);
            }
        }
        
    }

    cv::imshow("Original", image);
    cv::imshow("Result - Light Bars",result_img);
    cv::imshow("HSV Mask", mask);

    waitKey(0);
    return 0;
}