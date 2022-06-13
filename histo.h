#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 선택된 영역만 히스토그램 계산
void draw_ellipse(cv::Mat& image, Rect2d obj, Scalar color, int thickness, float ratio)
{
	Point2d center = obj.tl() + (Point2d)obj.size() * 0.5; // 타원 중심
	Size2d size = (Size2d)obj.size() * 0.45; // 타원 크기
	ellipse(image, center, size, 0, 0, 360, color, thickness);

}

void calc_histo(const cv::Mat& img, cv::Mat& hist, Vec3i bins, Vec3f range, cv::Mat mask)
{
	int dims = 1; // 히스토그램 차원 수 
	int channels[] = { 0 }; // 채널 목록
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };



	calcHist(&img, 1, channels, mask, hist, dims, histSize, ranges);

}

// 마스크의 검은색 부분은 빈도를 계산하지 않는다
void calc_histos(cv::Mat correct_img, vector<Rect> sub_obj, Mat hists[4], Mat masks[4])
{
	Vec3i bins(64, 64, 64); // 히스토그램 계급 개수
	Vec3f ranges(256, 256, 256); // 각 채널 화소 범위

	for (int i = 0; i < (int)sub_obj.size(); i++) {
		Mat sub;
		cvtColor(correct_img(sub_obj[i]), sub, COLOR_BGR2GRAY);
		calc_histo(sub, hists[i], bins, ranges, masks[i]); // 히스토그램 계산
		// imshow(format("mask[%d]", i), masks[i]); // 마스크 영상 출력
		waitKey();
	}
}

void make_masks(vector<Rect> sub_obj, Size org_size, cv::Mat mask[4])
{
	cv::Mat base_mask(org_size, CV_8U, Scalar(255)); // 기본 마스크

	mask[0] = base_mask(sub_obj[0]);
	mask[1] = base_mask(sub_obj[1]);
	mask[3] = base_mask(sub_obj[3]);
	mask[2] = base_mask(sub_obj[2]);
}