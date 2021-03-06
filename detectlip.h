#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Rect detect_lip(Point2d face_center, Rect face) {

	// 입술 중심
	Point2d lip_center = face_center + Point2d(0, face.height * 0.30);
	// 정해진 크기 - 평행이동 거리
	Point2d gap_size(face.width * 0.18, face.height * 0.1);

	// 왼쪽 위로 평행이동
	Point lip_start = lip_center - gap_size;
	// 오른쪽 아래로 평행이동
	Point lip_end = lip_center + gap_size;

	return Rect(lip_start, lip_end);
}
cv::Rect detect_forehead(cv::Point2d face_center, cv::Rect face)
{
	cv::Point2d forehead_center = face_center - cv::Point2d(0, face.height * 0.4);
	cv::Point2d gap_size(face.width * 0.4, face.height * 0.1);

	cv::Point forehead_start = forehead_center - gap_size;
	cv::Point forehead_end = forehead_center + gap_size;

	return cv::Rect(forehead_start, forehead_end);
}

cv::Rect detect_mustache(cv::Point2d face_center, cv::Rect face)
{
	cv::Point2d lip_center = face_center + cv::Point2d(face.width * 0.01, face.height * 0.23);
	cv::Point2d gap_size(face.width * 0.2, face.height * 0.03);

	cv::Point lip_start = lip_center - gap_size;
	cv::Point lip_end = lip_center + gap_size;

	return cv::Rect(lip_start, lip_end);
}

cv::Rect detect_brow(cv::Point2d eye_center1, cv::Point2d eye_center2, cv::Rect face)
{
	cv::Point2d brow_center = (eye_center1 + eye_center2) * 0.5 - cv::Point2d(0, face.height * 0.1);
	cv::Point2d gap_size(face.width * 0.3, face.height * 0.05);

	cv::Point brow_start = brow_center - gap_size;
	cv::Point brow_end = brow_center + gap_size;

	return cv::Rect(brow_start, brow_end);
}
cv::Rect detect_beard(cv::Point2d face_center, cv::Rect face) // 아랫수염
{
	cv::Point2d lip_center = face_center + cv::Point2d(0, face.height * 0.46);
	cv::Point2d gap_size(face.width * 0.1, face.height * 0.03);

	cv::Point lip_start = lip_center - gap_size;
	cv::Point lip_end = lip_center + gap_size;

	return cv::Rect(lip_start, lip_end);
}
cv::Rect detect_cheek(cv::Point2d face_center, cv::Rect face) // 볼
{
	cv::Point2d lip_center = face_center + cv::Point2d(face.width * 0.2, face.height * 0.1);
	cv::Point2d gap_size(face.width * 0.07, face.height * 0.07);

	cv::Point lip_start = lip_center - gap_size;
	cv::Point lip_end = lip_center + gap_size;

	return cv::Rect(lip_start, lip_end);
}
void detect_hair(Point2d face_center, Rect face, vector<Rect>& hair_rect)
{
	cv::Point2d lip_center = face_center + cv::Point2d(face.width * 0.2, face.height * 0.1);
	cv::Point2d gap_size1(face.width * 0.1, face.height * 0.1);

	cv::Point lip_start = lip_center - gap_size1;
	cv::Point lip_end = lip_center + gap_size1;

	cv::Rect hair(lip_start, lip_end);

	Point2d mustache = face_center + cv::Point2d(face.width * 0.01, face.height * 0.23);
	Point2d gap_size(face.width * 0.2, face.height * 0.03);
	Point mus_start = mustache - gap_size;
	Point mus_end = mustache + gap_size;

	Rect mus(mus_start, mus_end);

	Point2d beard_center = face_center + cv::Point2d(0, face.height * 0.46);
	Point2d gap_size2(face.width * 0.1, face.height * 0.03);
	Point brd_start = beard_center - gap_size2;
	Point brd_end = beard_center + gap_size2;

	Rect brd(brd_start, brd_end);

	hair_rect.push_back(mus);
	hair_rect.push_back(brd);
	hair_rect.push_back(hair);
}