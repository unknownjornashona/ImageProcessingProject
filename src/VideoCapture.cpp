#include "VideoCapture.h"
#include "ImageProcessor.h"
#include <filesystem>
#include <iostream>

void VideoCapture::captureVideo(const std::string& outputDir, int imageCount) {
    cv::VideoCapture cap(0); // 打开默认摄像头
    if (!cap.isOpened()) {
        throw std::runtime_error("Could not open the camera");
    }

    cv::Mat frame, previousFrame;
    std::vector<std::string> detectedClasses;
    std::vector<cv::Rect> boxes;

    std::filesystem::create_directory(outputDir); // 创建输出目录

    // 初始化之前的帧
    cap >> previousFrame; 

    for (int i = 0; i < imageCount; ++i) {
        cap >> frame; // 捕捉一帧
        if (frame.empty()) break; // 检查是否捕捉到帧

        // 对当前帧进行目标检测
        ImageProcessor::detectObjects(frame, detectedClasses, boxes);

        // 检测事件
        if (ImageProcessor::detectEvent(frame, previousFrame)) {
            std::cout << "Event detected: Potential attack or firefight!" << std::endl;
            // 在这里可以连接告警系统，比如发送邮件或触发其他机制
            // sendAlert("Event detected!");
        }

        // 更新之前的帧
        previousFrame = frame.clone();

        // 保存处理后的图像
        std::string imageFilename = outputDir + "/image_" + std::to_string(i) + ".png";
        cv::imwrite(imageFilename, frame); // 保存图像

        // 生成报告
        std::string reportFilename = outputDir + "/report.txt";
        ImageProcessor::generateReport(detectedClasses, reportFilename);

        // 显示图像
        cv::imshow("Detected Objects", frame);
        
        // 短暂延迟，以便显示图像
        cv::waitKey(100); // 可调整的延迟
        std::cout << "Saved: " << imageFilename << std::endl;
    }

    cap.release();
    cv::destroyAllWindows();
}
