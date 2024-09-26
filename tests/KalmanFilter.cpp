#include "KalmanFilter.h"

KalmanFilter::KalmanFilter() {
    kf.init(4, 2, 0);
    kf.transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, 1, 0,
                                                     0, 1, 0, 1,
                                                     0, 0, 1, 0,
                                                     0, 0, 0, 1);
    kf.measurementMatrix = (cv::Mat_<float>(2, 4) << 1, 0, 0, 0,
                                                       0, 1, 0, 0);
    kf.processNoiseCov = cv::Mat::eye(4, 4, CV_32F) * 0.01;
    kf.measurementNoiseCov = cv::Mat::eye(2, 2, CV_32F) * 5;
    state = cv::Mat::zeros(4, 1, CV_32F);
}

void KalmanFilter::predict() {
    state = kf.predict();
}

void KalmanFilter::update(const cv::Mat& measurement) {
    kf.correct(measurement);
}

cv::Mat KalmanFilter::getState() const {
    return state;
}
