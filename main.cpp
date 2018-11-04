#include <stdio.h>
#include <iostream>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include <opencv2/video/background_segm.hpp>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace cv;
#define STAGE_WIDTH 720
#define STAGE_HEIGHT 640
const float CAR_WIDTH_RATIO = 0.2;
const float CAR_HEIGHT_RATIO = 0.19;

static void onMouse(int event, int x, int y, int, void *ptr) {
	cv::Point* r = (cv::Point*) ptr;
	if (event == cv::EVENT_LBUTTONDOWN) {
		*r = cv::Point(x, y);
	}
}

static void trackbar_cb(int value, void *ptr) {
	if (value > 0) {
		int *r = (int*) ptr;
		*r = value;
	}
//	printf("trackbar: %d\n", value);
}

int main(int argc, char **argv) {

	Mat stage(STAGE_HEIGHT, STAGE_WIDTH, CV_8UC3, Scalar(0, 0, 0));

	line(stage, Point(0, 0.2 * STAGE_HEIGHT),
			Point(STAGE_WIDTH, 0.2 * STAGE_HEIGHT), Scalar(255, 0, 0));

	rectangle(stage, Point(0.35 * STAGE_WIDTH, 0.2 * STAGE_HEIGHT),
			Point(0.65 * STAGE_WIDTH, STAGE_HEIGHT), Scalar(255, 0, 0));

	Point new_parcel_center = Point(0, 0);
	Rect new_parcel = Rect(Point(0, 0), Point(10, 10));
	Point target_car_point = Point(STAGE_WIDTH, 0);
	Rect target_car = Rect(target_car_point,
			Point(target_car_point.x + STAGE_WIDTH * CAR_WIDTH_RATIO, target_car_point.y + STAGE_HEIGHT * CAR_HEIGHT_RATIO));
	float car_speed = 1.5 / 1.5 * STAGE_WIDTH / 10; // m/s translate to pix / s
	namedWindow("Lab");
	cv::setMouseCallback("Lab", onMouse, &new_parcel_center);
	int replay_speed = 100;	// In millisecond
	cv::createTrackbar("ReplaySpeed", "Lab", &replay_speed, 1000, trackbar_cb,
			&replay_speed);

	int run = 1;
	Mat current_frame;
	while (run) {
		current_frame = stage.clone();
		int key = waitKey(10);
		if (key == 'q') {
			run = 0;
		}
		target_car_point.x = target_car_point.x - car_speed * replay_speed / 1000.0;
		if(target_car_point.x < 0){
			target_car_point.x = STAGE_WIDTH;
		}
		Rect target_car = Rect(target_car_point,
				Point(target_car_point.x + STAGE_WIDTH * CAR_WIDTH_RATIO, target_car_point.y + STAGE_HEIGHT * CAR_HEIGHT_RATIO));
		rectangle(current_frame, target_car, Scalar(255, 0, 0));

		imshow("Lab", current_frame);

	}

	waitKey(0);

	return 0;
}
