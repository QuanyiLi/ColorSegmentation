#include<iostream>

#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>

//threshold ����һ����ֵ
//����ɫ���������������ֵʱ������true����Ϊ��Ȧ���
//����ɫ���������������ֵʱ������false����Ϊ������Ȧ
bool colorFilter(cv::Mat &inputImage,int threshold)
{ 
	cv::Mat hsv;
	cv::cvtColor(inputImage, hsv, CV_BGR2HSV);
	//������¼ͼ���к�ɫ���ص���Ŀ����ʼ��Ϊͼ������������
	int pixel_size = hsv.rows*hsv.cols;
	hsv.at<cv::Vec3b>(0,0);
	for (int i = 0; i < hsv.rows; ++i)
	{
		for (int j = 0; j < hsv.cols; ++j)
		{ 
			//CvScalar s_hsv = cvGet2D(&hsv, i, j);//��ȡ���ص�Ϊ��j, i�����HSV��ֵ 
		    //opencv ��H��Χ��0~180����ɫ��H��Χ�����(0~8)��(160,180)
		    //S�Ǳ��Ͷȣ�һ���Ǵ���һ��ֵ,S���;��ǻ�ɫ���ο�ֵS>80)��
		    //V�����ȣ����;��Ǻ�ɫ�����߾��ǰ�ɫ(�ο�ֵ220>V>50)��
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
	std::cout << "��ɫ��������" <<pixel_size<<std::endl;
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
				std::cout << "�ɹ���Ȧ" << std::endl;
			else
				std::cout << "������Ȧ��" << std::endl;
		}
	 else
		std::cout << "ͼƬδ����" << std::endl;

	cv::destroyAllWindows();

	return 0;
}
