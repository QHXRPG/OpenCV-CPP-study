//
// Created by 邱浩轩 on 2023/3/3.
//

#include "opencv2/opencv.hpp"
#include "iostream"
#include "fstream"
using namespace std;
//显示图像
void test1()
{
    cv::Mat img = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/1.png",-1);
    cv::namedWindow("example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("example1", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

//显示视频
void test2()
{
    cv::namedWindow("example2",cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open("/Users/qiuhaoxuan/CLionProjects/opencv1/基础图像处理/IMG_2445.MOV");
    cv::Mat frame;
    while(1)
    {
        cap>>frame;
        if(frame.empty()){ break;}
        cv::imshow("example2", frame);
        if(cv::waitKey(33)>=0){ break;}
    }
}


//添加进度条
//单步模式：一张一张图片播放，或几张几张图片播放
//连续播放模式：以视频形式播放图片
int g_slider_position = 0;  //存储滑动条的位置
int g_run =1, g_dontset=0;  //  g_run >0:停止之前程序播放多少张图片   g_run <0:连续视频播放
cv::VideoCapture g_cap;
void onTrackbarSlide(int pos, void *)  //用户调整滑动条的时候执行的回调函数，传入一个pos表示当前位置
{
    // cv::CAP_PROP_POS_FRAMES：指示我们想要帧集合的读取位置
    g_cap.set(cv::CAP_PROP_POS_FRAMES,pos);  //使进度条移动到我们希望的位置
    if(!g_dontset)
    {
        g_run=1;
    }
    g_dontset = 0;
}
void test3()
{
    cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
    g_cap.open("/Users/qiuhaoxuan/CLionProjects/opencv1/基础图像处理/IMG_2445.MOV");
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);  //总帧数
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);  //视频的高
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);  //视频的宽
    cout<< "video has" <<frames<<"frames of dimension(" << tmpw<< "," <<tmph << "),"<< endl;
    cv::createTrackbar("position", "Example3", &g_slider_position,
                       frames, onTrackbarSlide); //创建一个滑动条，这个滑动条名称：position
                                                                 //在Example3窗口放置这个滑动条，
                                                                 //滑动条的位置为&g_slider_position
                                                                 //移动时触发回调函数onTrackbarSlide()
    cv::Mat frame;
    while(1)
    {
        if(g_run!=0)
        {
            g_cap >> frame;
            if(frame.empty()){break;}
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);   //获取在视频中的当前位置
            g_dontset = 1;  //使下一个滑动条的回调函数不会让我们进入单步模式
            cv::setTrackbarPos("position","Example3",current_pos);  //更新滑动块在滑动条上的位置以便显示给用户
            cv::imshow("Example3",frame);
            g_run  = g_run-1; //让我们保持单步模式或者依据用户设置让视频正常播放
            cout<<g_run<<endl;
        }
        char c=(char) cv::waitKey(10);
        if(c == 's')
        {
            g_run = 1;
            cout<<"单步,run=" <<g_run<<endl;
        }
        if(c == 'r')
        {
            g_run = -1;
            cout<<"run mode, run="<< g_run<<endl;
        }
        if(c == 27)
        {
            break;
        }
    }
}


//加载图片并且在显示之前平滑处理图片
void test4()
{
    cv::namedWindow("Example4_in",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example4_out",cv::WINDOW_AUTOSIZE);
    cv::Mat img = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    cv::imshow("Example4_in",img);
    cv::Mat out;
    cv::GaussianBlur(img,out,cv::Size(5,5),3,3);
    cv::GaussianBlur(out,out,cv::Size(5,5),3,3);
    cv::imshow("Example4_out",out);
    cv::waitKey(0);
}


//使用cv::pyrDown()创建一个新的图像， 宽高为原始图像的一半
void test5()
{
    cv::Mat img1,img2;
    cv::namedWindow("Example1",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example2",cv::WINDOW_AUTOSIZE);
    cv::Mat img;
    img1=cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    cv::imshow("Example1",img1);
    cv::pyrDown(img1,img2);  //创建一个新的图像img2， 宽高为原始图像img1的一半
    cv::imshow("Example2",img2);
    cv::waitKey(0);
}

//Canny边缘检测器输出一个单通道的灰度图像
void test6()
{
    cv::Mat img_rgb, img_gry, img_canny;
    cv::namedWindow("Example_gry",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example_canny",cv::WINDOW_AUTOSIZE);
    img_rgb = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    cv::cvtColor(img_rgb,img_gry,cv::COLOR_BGR2GRAY);

    cv::Canny(img_gry,img_canny,30,100,3, true);
    cv::imshow("Example_gry",img_gry);
    cv::imshow("Example_canny",img_canny);
    cv::waitKey(0);
}

//在一个简单图像处理流程中结合图像金字塔操作和Canny边缘检测器，结合test5和test6
void test7()
{
    cv::Mat img_rgb, img_gry, img_canny, img_pyr, img_pyr2;
    cv::namedWindow("Example_gry",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img_pyr",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img_pyr2",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example_canny",cv::WINDOW_AUTOSIZE);
    img_rgb = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    cv::cvtColor(img_rgb,img_gry,cv::COLOR_BGR2GRAY);

    cv::pyrDown(img_gry, img_pyr);
    cv::pyrDown(img_pyr, img_pyr2);
    cv::Canny(img_pyr2,img_canny,10,100,3, true);
    cv::imshow("Example_gry",img_gry);
    cv::imshow("img_pyr",img_pyr);
    cv::imshow("img_pyr2",img_pyr2);
    cv::imshow("Example_canny",img_canny);
    cv::waitKey(0);
}

//读写test7中的像素值
void test8()
{
    cv::Mat img_rgb, img_gry, img_canny, img_pyr, img_pyr2;
    img_rgb = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/IMG_0988.jpeg");
    int x=16,y=32;
    cv::Vec3b intensisty = img_rgb.at< cv::Vec3b >(y,x);
    uchar blue = intensisty[0];
    uchar green = intensisty[1];
    uchar red = intensisty[2];
    cout<<(unsigned int)blue<<endl;
    cout<<(unsigned int)green<<endl;
    cout<<(unsigned int)red<<endl;
}

//连接摄像头
void test9()
{
    cv::namedWindow("Example9",cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(0);
    cv:: Mat frame;
    while(1)
    {
        cap>>frame;
        cv::imshow("Example9",frame);
        char c = (char)cv::waitKey(30);
        if(c==27)
        { break;}
    }
}

