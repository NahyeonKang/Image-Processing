#include "preprocess.h"
#include "correct_angle.h""
#include "detectlip.h"
#include "histo.h"
#include <opencv2/imgproc/types_c.h>
#include <cstdlib>
RNG rng(12345);
string name = "w앤해서웨이";

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	Mat image = imread(format("%s.jpg", name), IMREAD_COLOR);
	CV_Assert(image.data);
	Mat gray = preprocessing(image);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;
	vector<Rect> sub_obj, sub_obj2, sub_obj3;

	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));

	if (faces.size() > 0)
	{
		float i = 1.15;
		while (true) {

			eyes_cascade.detectMultiScale(gray(faces[0]), eyes, i, 7, 0, Size(25, 20));

			if (eyes.size() == 2) {
				eyes_center.push_back(calc_center(eyes[0] + faces[0].tl()));
				eyes_center.push_back(calc_center(eyes[1] + faces[0].tl()));

				Point2d face_center = calc_center(faces[0]); // 얼굴 중심 좌표 계산
				Mat rot_mat = calc_rotMap(face_center, eyes_center); // 얼굴 중심좌표와 눈 중심좌표로 얼굴 기울기의 회전행렬 반환
				// 회전행렬로 회전변환을 수행하여 기울기를 보정하고, 눈 좌표도 회전변환을 적용하여 다시 계산
				Mat correct_img = correct_image(image, rot_mat, eyes_center);

				sub_obj.push_back(detect_brow(eyes_center[0], eyes_center[1], faces[0]));

				Mat dstimage = Mat::zeros(correct_img(sub_obj[0]).rows, correct_img(sub_obj[0]).cols, CV_8UC3);
				Mat cannyimage;
				Canny(correct_img(sub_obj[0]), cannyimage, 10, 100);

				vector<vector<Point>> contours;
				vector<Vec4i> hierarchy;
				findContours(cannyimage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

				double count = 0;
				for (int i = 0; i < contours.size(); i++)
				{
					count += 1;
					Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
					drawContours(dstimage, contours, i, color, 2, 8, hierarchy, 0, Point());

				}

				detect_hair(face_center, faces[0], sub_obj2);
				sub_obj2.push_back(detect_mustache(face_center, faces[0]));
				
				Mat masks[4], hists[4];
				make_masks(sub_obj2, correct_img.size(), masks);
				calc_histos(correct_img, sub_obj2, hists, masks);
				double criteria2 = compareHist(hists[2], hists[3], CV_COMP_CORREL);

				cv::rectangle(correct_img, sub_obj2[2], cv::Scalar(255, 0, 0), 2);
				cv::rectangle(correct_img, sub_obj2[3], cv::Scalar(255, 0, 0), 2);

				cv::Mat img1, img2, mustache, cmustache, dstimage2;
				sub_obj3.push_back(detect_beard(face_center, faces[0]));
				sub_obj3.push_back(detect_mustache(face_center, faces[0]));
				sub_obj3.push_back(detect_cheek(face_center, faces[0]));
				sub_obj3.push_back(detect_forehead(face_center, faces[0]));
						
				correct_img(sub_obj3[0]).copyTo(img1);
				correct_img(sub_obj3[1]).copyTo(img2);

				cv::cvtColor(img1, img1, cv::COLOR_BGR2GRAY);
				cv::cvtColor(img2, img2, cv::COLOR_BGR2GRAY);

				cv::threshold(img1, img1, 125, 255, cv::THRESH_BINARY);
				cv::threshold(img2, img2, 125, 255, cv::THRESH_BINARY);

				cv::resize(img2, img2, img1.size());
				cv::vconcat(img1, img2, mustache);

				std::vector<std::vector<cv::Point>> contours2;
				std::vector<cv::Vec4i> hierarchy2;

				findContours(mustache, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

				double count2 = 0;
				for (int i = 0; i < contours2.size(); i++)
				{
					count2 += 1;
					cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
					drawContours(dstimage2, contours2, i, color, 2, 8, hierarchy2, 0, cv::Point());

				}

				double score = criteria2 * -100 + count2;
				string text = "None";
				if (score > 10)
				{
					text = "MAN";
				}
				else
				{
					if (count > 35)
					{
						text = "MAN";
					}
					else
					{
						text = "WOMAN";
					}
				}
				text = format("%s.jpg: ", name) + text;
				int font = FONT_HERSHEY_TRIPLEX;
				imshow("correct_img", correct_img);
				putText(image, text, Point(12, 31), font, 0.7, Scalar(0, 0, 0), 2);
				putText(image, text, Point(10, 30), font, 0.7, Scalar(0, 255, 0), 1);
				cout << text << format(" - 수염점수: %4.2f, 눈썹점수: %4.2f", score, count);
				
				waitKey();
				break;
			}
			i += 0.05;
			if (i > 10) break;
		}
	}
	waitKey();
	return 0;
}