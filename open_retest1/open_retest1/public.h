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

//��ͼ���Ϊ��������
#define RN 30	
#define CN 50

//#define WAITTIME 100		//�ȴ�ʱ��

cv::Mat BackGround;				//��ͼ�õı���ͼ
bool backisinit[RN][CN] = { false };//����ͼ�ÿ�ʱ���ʼ��

//double learningRate = 0.01;		//�����ۼ��е�ѧϰ��
int threshold = 20;				//ǰ����ȡ����ֵ

bool ispyrDown = false;			//�Ƿ���С��
int SmallHeight;				//ÿ��С���εĸ�
int SmallWeight;				//ÿ��С���εĿ�
int width;
int height;

int result;					//�Ի��򷵻ص�ֵ
bool CAP = false;				//�Ƿ�׽����ժҪ��
int frame_number = -1;		//��ǰ֡��
int PublicFrame;			//Ҫд�ڻ����ϵ�ʱ��
int PublicFps;				//ϵͳfps
std::string PublicTime;			//Ҫ����ʱ�䴮

								//����ļ���ļ�·��
std::string InputFile = "F:1.avi";
//	"D:\\�ĵ�\\��Ƶ\\1.mp4";
//	"D:\\�ĵ�\\��Ƶ\\2.mp4";

//����ļ���ļ�·��
std::string OutputFile1 = "F:put.avi";
std::string OutputFile2;


struct Foreground_Border	//ǰ���߿�
{
	bool bor[RN][CN];		//����Ķ�ά���飬ָ���������Ƿ�ѡ��
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
