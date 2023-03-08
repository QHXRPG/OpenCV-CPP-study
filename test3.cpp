//
// Created by 邱浩轩 on 2023/3/8.
//

#include "test3.h"
#include "opencv2//opencv.hpp"
#include "iostream"
#include "vector"

using namespace std;

//压缩图像并保存
void test3_1()
{
    cv::Mat img = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    vector<uchar> buf;
    vector<int> params{cv::IMWRITE_JPEG_QUALITY,80}; // JPEG格式的压缩质量为80%
    cv::imencode(".jpg",img,buf,params);
    cv::Mat img2 = cv::imdecode(buf,cv::IMREAD_COLOR);  //再用imdecode解码得到Mat格式的数据
    cv::imwrite("buf1.jpg",img2);  //保存
}

//获取视频的编码     cv::CAP_PROP_FOURCC:FourCC标识符是一种用于识别视频编解码器的代码，通常由四个大写字母组成。
void test3_2()
{
    cv::VideoCapture cap("/Users/qiuhaoxuan/CLionProjects/opencv1/基础图像处理/IMG_2445.MOV");
    unsigned f = (unsigned) cap.get(cv::CAP_PROP_FOURCC);
    char fourcc[] = {(char)f,(char)(f>>8),(char)(f>>16),(char)(f>>24),'\0'};
    for(int i=0;i<4;i++)
    {
        cout<<fourcc[i]<<endl;
    }
}