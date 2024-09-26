#ifndef TARGETTRACKER_H
#define TARGETTRACKER_H

#include <opencv2/opencv.hpp>
#include "KalmanFilter.h"
#include "TensorFlowModel.h"
#include "SerialPort.h"

class TargetTracker {
private:
    std::vector<cv::Point> tracked_targets;
    KalmanFilter kf;
    TensorFlowModel model;
    SerialPort serial;

public:
    TargetTracker(const char* model_path, const std::string& port, unsigned int baud_rate);
    void preprocessData(cv::Mat& frame);
    void trackTargets(const std::vector<cv::Point>& targets);
    void saveToCSV(const std::string& filename);
    void sendDataToSensor(const std::vector<cv::Point>& targets);
    void run();
};

#endif // TARGETTRACKER_H
