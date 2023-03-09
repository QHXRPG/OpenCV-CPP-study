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

//打开窗口
void test4_1()
{
    cv::Mat img;
    img = cv::imread("/Users/qiuhaoxuan/CLionProjects/opencv1/dream_place.jpg");
    cv::namedWindow("t4_1",cv::WINDOW_AUTOSIZE);
    cv::imshow("t4_1",img);
    while(1)
    {
        if(cv::waitKey(10)==27)  //用cv::waitKey(int)进行键值捕捉
        {
            break;
        }
    }
    cv::destroyWindow("t4_1");
}


//使用鼠标回调完成绘制方框小程序
// my_mouse_callback()：对鼠标事件做出相应，当被调用时，会根据事件来决定自己要完成什么任务
void my_mouse_callback(int event, int x, int y, int flags, void*param);

cv::Rect box;
bool drawing_box = false;

void draw_box(cv::Mat& img, cv::Rect box)
{                                                       //cv::Scalar(0x00,0x00,0xff) : red
    cv::rectangle(img, box.tl(),box.br(), cv::Scalar(0x00,0x00,0xff));
}


void test4_2()
{
    //表示创建一个 cv::Rect 对象，该对象表示图像或视频帧中感兴趣的矩形区域，其左上角位置为 (-1,-1)，宽度和高度设置为 0。
    box = cv::Rect(-1,-1,0,0);
    cv::Mat image(200,200,CV_8UC3), temp;
    image.copyTo(temp);

    box = cv::Rect(-1,-1,0,0);
    image = cv::Scalar::all(0);
    cv::namedWindow("box example");
    cv::setMouseCallback("box example",my_mouse_callback,(void*)&image);
    for(;;)
    {
        image.copyTo(temp);
        if(drawing_box)
        {
            draw_box(temp,box);
            cv::imshow("box example",temp);
        }
        if(cv::waitKey(15)==27){break;}
    }
}

void my_mouse_callback(int event, int x, int y, int flags, void*param)
{
    cv::Mat& image = *(cv::Mat*) param;
    switch(event)
    {
        case cv::EVENT_MOUSEMOVE:
        {
            if(drawing_box)
            {
                box.width = x-box.x;
                box.height = y-box.y;
            }
        }
        break;

        case cv::EVENT_LBUTTONDOWN:
        {
            drawing_box = true;
            box = cv::Rect(x,y,0,0);
        }
        break;

        case cv::EVENT_LBUTTONUP:
        {
            drawing_box = false;
            if (box.width < 0)
            {
                box.x = box.x + box.width;
                box.width = box.width * -1;
            }
            if(box.height<0)
            {
                box.y = box.y + box.height;
                box.height = box.height * -1;
            }
            draw_box(image, box);
        }
        break;
    }
}
