#include<iostream>

#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>

//threshold 代表一个阈值
//当红色像素数少于这个阈值时，返回true，认为钻圈完成
//当红色像素数超过这个阈值时，返回false，认为正在钻圈
bool colorFilter(cv::Mat &inputImage,int threshold)
{ 
	cv::Mat hsv;
	cv::cvtColor(inputImage, hsv, CV_BGR2HSV);
	//用来记录图像中红色像素的数目，初始化为图像像素总数，
	int pixel_size = hsv.rows*hsv.cols;
	hsv.at<cv::Vec3b>(0,0);
	for (int i = 0; i < hsv.rows; ++i)
	{
		for (int j = 0; j < hsv.cols; ++j)
		{ 
			//CvScalar s_hsv = cvGet2D(&hsv, i, j);//获取像素点为（j, i）点的HSV的值 
		    //opencv 的H范围是0~180，红色的H范围大概是(0~8)∪(160,180)
		    //S是饱和度，一般是大于一个值,S过低就是灰色（参考值S>80)，
		    //V是亮度，过低就是黑色，过高就是白色(参考值220>V>50)。
			//CvScalar s;
			if (!((hsv.at<cv::Vec3b>(i,j)[0]> 0 && hsv.at<cv::Vec3b>(i, j)[0] < 8) || (hsv.at<cv::Vec3b>(i, j)[0] > 160&& hsv.at<cv::Vec3b>(i,j)[0] < 180)))
			{
				hsv.at<cv::Vec3b>(i, j)[0] = 0;
				hsv.at<cv::Vec3b>(i, j)[1] = 0;
				hsv.at<cv::Vec3b>(i, j)[2] = 0;
				--pixel_size;
			}
		}
	}
	cv::Mat rgb;
	cv::cvtColor(hsv, rgb, CV_HSV2BGR);
	cv::imwrite("aft_11.jpg",rgb);
	cv::namedWindow("aft_segmentation");
	cv::imshow("aft_segmentation", rgb);
	cv::waitKey(3);
	std::cout << "红色像素数：" <<pixel_size<<std::endl;
	if (pixel_size < threshold)
		return true;
	else
		return false;
}

int main() {
	cv::Mat ori = cv::imread("11.jpg"); 
	if (ori.data) {
		cv::namedWindow("original");
		cv::imshow("original", ori);
		cv::waitKey(3);

		bool b = colorFilter(ori, 100);
			if (b)
				std::cout << "成功钻圈" << std::endl;
			else
				std::cout << "正在钻圈中" << std::endl;
		}
	 else
		std::cout << "图片未读入" << std::endl;

	cv::destroyAllWindows();

	return 0;
}
