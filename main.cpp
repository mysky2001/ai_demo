#include <opencv2/opencv.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
//using namespace cv;

cv::VideoCapture capture;
int g_frame_pos = 0, g_run = 0 , g_runMode = 1;
#define PLAY_NAME "sky ²¥·ÅÆ÷"
#define TRACKBAR_NAME "trackbar"

void TrackBarCallback(int pos, void *)
{
	capture.set(CV_CAP_PROP_POS_FRAMES, pos);
	if (!g_runMode)
	{
		g_run = 0;
	}
	g_runMode = 0;
}

int main()
{

#if 0
	int frameCount = 0;
	cv::namedWindow(PLAY_NAME ,cv::WINDOW_NORMAL);

	capture.open("D:\\bootvideo.mp4");

	if (!capture.isOpened())
		return 0;

	frameCount = capture.get(cv::CAP_PROP_FRAME_COUNT);

	int framefps = capture.get(cv::CAP_PROP_FPS);

	cout << "fps = " << framefps << endl;
	cv::createTrackbar(TRACKBAR_NAME ,PLAY_NAME ,&g_frame_pos , frameCount , TrackBarCallback);
	cv::Mat frame;
	for (;;)
	{
		if (!g_run)
		{
			capture >> frame;
			if (frame.empty())
				break;
			int curryPos = capture.get(cv::CAP_PROP_POS_FRAMES);
			g_runMode = 1;
			cv::setTrackbarPos(TRACKBAR_NAME, PLAY_NAME, curryPos);
			cv::imshow(PLAY_NAME , frame);
			//g_run -= 1;
		}
		char c = (char)cv::waitKey(25);
		if (c == 's')
		{
			g_run = 1;
		}
		if (c == 'r')
		{
			g_run = -1;
		}
		if (c == 27)
			break;
	}
#endif

	cv::Mat image ,image1 ,image2 , image3;
	image = cv::imread("D:\\test.jpg");

	cv::namedWindow("show picture", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("show picture1", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("show picture2", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("show picture3", cv::WINDOW_AUTOSIZE);

	cv::GaussianBlur(image , image1 , cv::Size(5 ,5),3 ,3);
	cv::GaussianBlur(image1, image1, cv::Size(5, 5), 3, 3);

	cv::pyrDown(image , image2);

	cv::Canny(image, image3, 10, 100, 3, true);

	cv::imshow("show picture",image);
	cv::imshow("show picture1", image1);
	cv::imshow("show picture2", image2);
	cv::imshow("show picture3", image3);

	cv::Canny(image3 , image , 10 , 100 , 3 , true);
	int x = 16, y = 32;
	cv::Vec3b intensity = image3.at<cv::Vec3b>(y ,x);
	uchar blue = intensity[0];
	uchar green = intensity[1];
	uchar red = intensity[2];

	cout << "(blue , green , red)" << (unsigned int)blue << "," << (unsigned int)green << "," << (unsigned int)red << endl;

	cv::waitKey(0);
	return 0;
}