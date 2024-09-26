#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <opencv2/opencv.hpp>

class KalmanFilter {
private:
    cv::KalmanFilter kf;
    cv::Mat state;

public:
    KalmanFilter();
    void predict();
    void update(const cv::Mat& measurement);
    cv::Mat getState() const;
};

#endif // KALMANFILTER_H
