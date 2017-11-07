#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/core/core.hpp"
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char * argv())
{
	//读入视频  
	//VideoCapture capture("CarLights2.avi");  
	//VideoCapture capture(0);
	VideoCapture capture("F:\\video.avi");
	//namedWindow("camera",WINDOW_AUTOSIZE);  
	//namedWindow("moving area",WINDOW_AUTOSIZE);  
	Mat tempframe, currentframe, previousframe;
	Mat frame;
	int framenum = 0;
	//读取一帧处理  
	while (true)
	{
		if (!capture.isOpened())
		{
			cout << "read video failure" << endl;
			return -1;
		}
		//tempframe = capture.read(frame);  


		capture >> frame;
		tempframe = frame;
		framenum++;
		if (framenum == 1)
		{
			cvtColor(tempframe, previousframe, CV_BGR2GRAY);
		}
		if (framenum >= 2)
		{
			Mat currentframe1, currentframe2, currentframe3, currentframe4;
			cvtColor(tempframe, currentframe, CV_BGR2GRAY);//转化为单通道灰度图，此时currentFrame已经存了tempFrame的内容   
			absdiff(currentframe, previousframe, currentframe);//做差求绝对值    
			threshold(currentframe, currentframe, 20, 255.0, CV_THRESH_BINARY);
			dilate(currentframe, currentframe, Mat());//膨胀  
			erode(currentframe, currentframe, Mat());//腐蚀  

													 //显示图像    
			imshow("camera", tempframe);
			imshow("moving area", currentframe);

		}
		//把当前帧保存作为下一次处理的前一帧    
		//cvtColor(tempframe, previousframe, CV_BGR2GRAY);  
		waitKey(1);
	}//end while    
}