#include "TargetTracker.h"
#include <fstream>
#include <iomanip> // For std::setprecision

TargetTracker::TargetTracker(const char* model_path, const std::string& port, unsigned int baud_rate)
    : model(model_path), serial(port, baud_rate) {}

void TargetTracker::preprocessData(cv::Mat& frame) {
    cv::GaussianBlur(frame, frame, cv::Size(5, 5), 0);
}

void TargetTracker::trackTargets(const std::vector<cv::Point>& targets) {
    for (const auto& target : targets) {
        cv::Mat measurement = (cv::Mat_<float>(2, 1) << target.x, target.y);
        kf.predict();
        kf.update(measurement);
    }
}

void TargetTracker::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& target : tracked_targets) {
        file << target.x << ',' << target.y << '\n';
    }
    file.close();
}

void TargetTracker::sendDataToSensor(const std::vector<cv::Point>& targets) {
    for (const auto& target : targets) {
        // 构建特定格式的数据包
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2); // 设置小数精度
        // 假设头部是 "TGT" 并假设格式为 "TGT <x> <y> <CHECKSUM>"
        double target_x = static_cast<double>(target.x);
        double target_y = static_cast<double>(target.y);
        double checksum = target_x + target_y; // 简化的校验和计算
        // 构建数据包
        std::string data_packet = "TGT " + oss.str() + std::to_string(target_x) + " "
                                  + oss.str() + std::to_string(target_y) + " "
                                  + std::to_string(checksum) + "\n"; // 数据包以换行符结束
        serial.sendData(data_packet);
    }
}

void TargetTracker::run() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture." << std::endl;
        return;
    }

    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Failed to grab frame." << std::endl;
            break;
        }

        preprocessData(frame);
        std::vector<cv::Point> targets = model.detect(frame);
        trackTargets(targets);
        sendDataToSensor(targets);

        for (const auto& target : targets) {
            cv::circle(frame, target, 5, cv::Scalar(0, 255, 0), -1);
        }

        cv::imshow("Target Tracking", frame);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    saveToCSV("tracked_targets.csv");
    cap.release();
    cv::destroyAllWindows();
}
