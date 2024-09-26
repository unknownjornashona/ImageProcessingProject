#include "ImageProcessor.h"
#include <fstream>

void ImageProcessor::toGray(cv::Mat& image) {
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

void ImageProcessor::extractRGBChannels(const cv::Mat& image, cv::Mat& rChannel, cv::Mat& gChannel, cv::Mat& bChannel) {
    std::vector<cv::Mat> channels;
    cv::split(image, channels);
    bChannel = channels[0]; // Blue channel
    gChannel = channels[1]; // Green channel
    rChannel = channels[2]; // Red channel
}

void ImageProcessor::edgeDetection(const cv::Mat& image, cv::Mat& edges) {
    cv::Canny(image, edges, 100, 200); // 使用 Canny 算法进行边缘检测
}

void ImageProcessor::detectObjects(const cv::Mat& image, std::vector<std::string>& detectedClasses, std::vector<cv::Rect>& boxes) {
    // 读取模型文件
    std::string modelConfiguration = "yolov3.cfg"; // YOLO配置文件路径
    std::string modelWeights = "yolov3.weights"; // YOLO权重文件路径
    cv::dnn::Net net = cv::dnn::readNetFromDarknet(modelConfiguration, modelWeights);
    
    // 将输入图像转换为 Blob 格式
    cv::Mat blob;
    cv::dnn::blobFromImage(image, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(), true, false);
    
    // 设置网络输入，并执行前向传播
    net.setInput(blob);
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    // 处理检测结果
    float confThreshold = 0.5; // 置信度阈值
    for (const auto& output : outputs) {
        for (int i = 0; i < output.rows; ++i) {
            const auto* data = output.ptr<float>(i);
            float confidence = data[4]; // 置信度
            if (confidence >= confThreshold) {
                int classId = static_cast<int>(data[5]);
                int x = static_cast<int>(data[0] * image.cols);
                int y = static_cast<int>(data[1] * image.rows);
                int width = static_cast<int>(data[2] * image.cols);
                int height = static_cast<int>(data[3] * image.rows);
                boxes.emplace_back(x, y, width, height);
                detectedClasses.emplace_back(std::to_string(classId)); // 此处可以优化为映射到实际类别名
            }
        }
    }
}

void ImageProcessor::markRegions(cv::Mat& image, const std::vector<cv::Rect>& regions, const std::string& label) {
    for (const auto& rect : regions) {
        cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 2); // 用红色标记
        cv::putText(image, label, cv::Point(rect.x, rect.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
    }
}

void ImageProcessor::generateReport(const std::vector<std::string>& detectedClasses, const std::string& outputFile) {
    std::ofstream report(outputFile);
    if (report.is_open()) {
        report << "Detected Objects Report\n";
        report << "========================\n";

        for (const auto& clazz : detectedClasses) {
            report << clazz << "\n"; // 输出每个检测到的类
        }

        report.close();
    }
}


bool ImageProcessor::detectEvent(const cv::Mat& currentFrame, const cv::Mat& previousFrame) {
    // Convert to grayscale
    cv::Mat grayCurrent, grayPrevious;
    cv::cvtColor(currentFrame, grayCurrent, cv::COLOR_BGR2GRAY);
    cv::cvtColor(previousFrame, grayPrevious, cv::COLOR_BGR2GRAY);

    // Calculate the absolute difference
    cv::Mat diff;
    cv::absdiff(grayCurrent, grayPrevious, diff);

    // Threshold the difference
    cv::Mat thresh;
    cv::threshold(diff, thresh, 30, 255, cv::THRESH_BINARY);

    // Count non-zero pixels to determine if an event has occurred
    int nonZeroCount = cv::countNonZero(thresh);
    return nonZeroCount > 1000; // 可调节阈值以检测事件
}
