//
// Created by 邱浩轩 on 2023/2/24.
//
#include "iostream"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void test_0()
{
    Mat img = imread("/Users/qiuhaoxuan/CLionProjects/opencv1/dream_place.jpg");
    if (!img.data) {
        std::cout << "Image not loaded";
    }
    imshow("img",img);
    waitKey(0);
}

//椒盐噪声
Mat add_np_noise(Mat img, float m)
{
    Mat noise ;
}