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