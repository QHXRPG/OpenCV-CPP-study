//
// Created by 邱浩轩 on 2023/3/8.
//
#include "opencv2/opencv.hpp"
#include "iostream"
using namespace std;

//创建一个矩阵
void test2_1()
{
    cv::Mat m(3,10,CV_32FC3,
              cv::Scalar(0.0f,2.0f,1.0f));
    cv::Mat n(7,10,CV_32FC3,
              cv::Scalar(0.0f,2.0f,1.0f));
    m=n;
    cout<<m<<endl;
}

//独立获取数组元素
void test2_2()
{
    //单通道
    cv::Mat m = cv::Mat::eye(10,10,CV_32FC1); //对角阵
    std::printf("Element (2,3) is %f\n",m.at<float>(2,3));
    std::printf("Element (3,3) is %f\n",m.at<float>(3,3));
    cout<<m<<endl;

    //多通道
    cv::Mat m2 = cv::Mat::eye(10,10,CV_32FC2);
    std::printf("Element (3,3) is (%f,%f)\n",m.at<cv::Vec2f>(3,3)[0], m.at<cv::Vec2f>(3,3)[1]);
    cout<<m<<endl;


}

//复数矩阵
void test2_3()
{
    cv::Mat_<std::complex<float>> complex_mat(3, 3);
    complex_mat(0, 0) = std::complex<float>(1.0f, 2.0f);
    complex_mat(0, 1) = std::complex<float>(2.0f, 3.0f);
    complex_mat(0, 2) = std::complex<float>(3.0f, 4.0f);
    complex_mat(1, 0) = std::complex<float>(4.0f, 5.0f);
    complex_mat(1, 1) = std::complex<float>(5.0f, 6.0f);
    complex_mat(1, 2) = std::complex<float>(6.0f, 7.0f);
    complex_mat(2, 0) = std::complex<float>(7.0f, 8.0f);
    complex_mat(2, 1) = std::complex<float>(8.0f, 9.0f);
    complex_mat(2, 2) = std::complex<float>(9.0f, 10.0f);
    std::cout << complex_mat << std::endl;
    std::printf("Element (1,0) is %f + i%f\n",
                complex_mat.at<cv::Complexf>(1,0).re,complex_mat.at<cv::Complexf>(1,0).im);
    std::printf("Element (2,0) is %f + i%f\n",
                complex_mat.at<cv::Complexf>(2,0).re,complex_mat.at<cv::Complexf>(2,0).im);
    std::printf("Element (1,1) is %f + i%f\n",
                complex_mat.at<cv::Complexf>(1,1).re,complex_mat.at<cv::Complexf>(1,1).im);
    std::printf("Element (2,1) is %f + i%f\n",
                complex_mat.at<cv::Complexf>(2,1).re,complex_mat.at<cv::Complexf>(2,1).im);
}

