using namespace std;
#include "public.h"

int main()
{
	cv::Mat frame;
	cv::Mat output;

	//ѡ��򿪵���Ƶ�ļ�
	TCHAR szFileName[1024] = { 0 };
	OPENFILENAME openFileName = { 0 };
	openFileName.lStructSize = sizeof(OPENFILENAME);
	openFileName.nMaxFile = MAX_PATH;
	openFileName.nFilterIndex = 1;
	openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFileName.lpstrFilter = TEXT("��Ƶ�ļ�(*.avi)\0*.avi\0�����ļ�(*.*)\0*.*\0\0");
	openFileName.lpstrFile = szFileName;
	if (GetOpenFileName(&openFileName))
	{
		//std::cout<<"��������Ŀ¼�ɹ�"<<std::endl;
		InputFile = LPTSTRtoSTR(openFileName.lpstrFile);
		//std::cout<<PublicTime<<std::endl;
	}
	else
	{
		std::cout << "ȡ����ƵժҪ" << std::endl;
		return -1;
	}


	cv::VideoCapture capture;
	capture.open(InputFile);
	if (!capture.isOpened())
	{
		std::cout << "ԭ��Ƶ��ʧ��" << std::endl;
		return -1;
	}
	else
		std::cout << "ԭ��Ƶ�򿪳ɹ�" << std::endl;

	int fps = capture.get(CV_CAP_PROP_FPS);	//ԭ��Ƶ��֡�� 
	int delay = 1000 / fps;						//ԭ��Ƶÿ֮֡�����ʱ
	PublicFps = fps;
	std::cout<<"fps="<<fps<<"\t delay="<<delay<<std::endl;

	width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	SmallHeight = float(height) / float(RN) + 0.5;
	SmallWeight = float(width) / float(CN) + 0.5;
	cout << width << " " << height << endl;
	cout << SmallWeight << " " << SmallHeight << endl;
	
	stringstream ss;
	ss<<"�Ƿ�Ҫ��С��Ƶ��ͼ��\n��ǰ��Ƶͼ���СΪ("<<width;
	std::string str=ss.str();
	std::cout<<str<<endl;
	int result = MessageBox(NULL,TEXT("�Ƿ�Ҫ��С��Ƶ��ͼ��\n��ǰ��Ƶͼ���СΪ("),TEXT("ϵͳ"),MB_ICONINFORMATION|MB_YESNO);
	
	result = IDNO;
	if (width > 1000 || height > 1000)
		result = IDYES;
	switch (result)
	{
	case IDYES:			//ѡ����ȷ��
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


	//ѡ�񱣴�Ĺ���Ŀ¼
	openFileName.lpstrFilter = TEXT("��Ƶ�ļ�(*.avi)\0*.avi\0�����ļ�(*.*)\0*.*\0\0");
	cout << "���ڱ����ժҪ" << endl;
	openFileName.lpstrTitle = TEXT("��ժҪ����Ϊ");
	if (GetSaveFileName(&openFileName))
	{
		OutputFile1 = LPTSTRtoSTR(openFileName.lpstrFile);
	}
	else
	{
		std::cout << "ȡ����ƵժҪ" << std::endl;
		return -1;
	} 
	cv::VideoWriter writer;
	writer.open(OutputFile1, CV_FOURCC('M', 'J', 'P', 'G'), fps/2, cv::Size(width, height), true);
}