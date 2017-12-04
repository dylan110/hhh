using namespace std;
#include "public.h"

int main()
{
	cv::Mat frame;
	cv::Mat output;

	//选择打开的视频文件
	TCHAR szFileName[1024] = { 0 };
	OPENFILENAME openFileName = { 0 };
	openFileName.lStructSize = sizeof(OPENFILENAME);
	openFileName.nMaxFile = MAX_PATH;
	openFileName.nFilterIndex = 1;
	openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFileName.lpstrFilter = TEXT("视频文件(*.avi)\0*.avi\0所有文件(*.*)\0*.*\0\0");
	openFileName.lpstrFile = szFileName;
	if (GetOpenFileName(&openFileName))
	{
		//std::cout<<"现在输入目录成功"<<std::endl;
		InputFile = LPTSTRtoSTR(openFileName.lpstrFile);
		//std::cout<<PublicTime<<std::endl;
	}
	else
	{
		std::cout << "取消视频摘要" << std::endl;
		return -1;
	}


	cv::VideoCapture capture;
	capture.open(InputFile);
	if (!capture.isOpened())
	{
		std::cout << "原视频打开失败" << std::endl;
		return -1;
	}
	else
		std::cout << "原视频打开成功" << std::endl;

	int fps = capture.get(CV_CAP_PROP_FPS);	//原视频的帧率 
	int delay = 1000 / fps;						//原视频每帧之间的延时
	PublicFps = fps;
	std::cout<<"fps="<<fps<<"\t delay="<<delay<<std::endl;

	width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	SmallHeight = float(height) / float(RN) + 0.5;
	SmallWeight = float(width) / float(CN) + 0.5;
	cout << width << " " << height << endl;
	cout << SmallWeight << " " << SmallHeight << endl;
	
	stringstream ss;
	ss<<"是否要缩小视频的图像\n当前视频图像大小为("<<width;
	std::string str=ss.str();
	std::cout<<str<<endl;
	int result = MessageBox(NULL,TEXT("是否要缩小视频的图像\n当前视频图像大小为("),TEXT("系统"),MB_ICONINFORMATION|MB_YESNO);
	
	result = IDNO;
	if (width > 1000 || height > 1000)
		result = IDYES;
	switch (result)
	{
	case IDYES:			//选择了确定
	{
		ispyrDown = true;
		threshold = 40;
		width /= 2;
		height /= 2;
		//std::cout<<"yes"<<std::endl;
		break;
	}
	case IDNO:
	{
		ispyrDown = false;
		threshold = 20;
		//std::cout<<"No"<<std::endl;
		break;
	}
	}


	//选择保存的工作目录
	openFileName.lpstrFilter = TEXT("视频文件(*.avi)\0*.avi\0所有文件(*.*)\0*.*\0\0");
	cout << "正在保存简单摘要" << endl;
	openFileName.lpstrTitle = TEXT("简单摘要保存为");
	if (GetSaveFileName(&openFileName))
	{
		OutputFile1 = LPTSTRtoSTR(openFileName.lpstrFile);
	}
	else
	{
		std::cout << "取消视频摘要" << std::endl;
		return -1;
	} 
	cv::VideoWriter writer;
	writer.open(OutputFile1, CV_FOURCC('M', 'J', 'P', 'G'), fps/2, cv::Size(width, height), true);
}