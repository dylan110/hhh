#pragma once
#include "memory.h"
#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/core/core.hpp"
#include <string>
#include <Windows.h>
#include "cv.h"
#include "highgui.h"
#include "memory.h"

//把图像分为的行列数
#define RN 30	
#define CN 50

//#define WAITTIME 100		//等待时间

cv::Mat BackGround;				//贴图用的背景图
bool backisinit[RN][CN] = { false };//背景图该块时候初始化

//double learningRate = 0.01;		//背景累加中的学习率
int threshold = 20;				//前景提取的阈值

bool ispyrDown = false;			//是否被缩小了
int SmallHeight;				//每个小矩形的高
int SmallWeight;				//每个小矩形的宽
int width;
int height;

int result;					//对话框返回的值
bool CAP = false;				//是否捕捉到简单摘要中
int frame_number = -1;		//当前帧数
int PublicFrame;			//要写在画面上的时间
int PublicFps;				//系统fps
std::string PublicTime;			//要画的时间串

								//输入的监控文件路径
std::string InputFile = "F:1.avi";
//	"D:\\文档\\视频\\1.mp4";
//	"D:\\文档\\视频\\2.mp4";

//输出的监控文件路径
std::string OutputFile1 = "F:put.avi";
std::string OutputFile2;


struct Foreground_Border	//前景边框
{
	bool bor[RN][CN];		//画面的二维数组，指定该区域是否被选定
	Foreground_Border* next;
};

std::string GetStr(LPTSTR value)
{
	std::string str("");
	while (*value)
	{
		str += *value;
		value++;
	}
	return str;
}

std::string LPTSTRtoSTR(LPTSTR value)
{
	char* ansiRemoteHost = new char[1024];
	memset(ansiRemoteHost, 0, 1024);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, value, 1024, ansiRemoteHost, 1024, NULL, NULL);
	return std::string(ansiRemoteHost);
}
