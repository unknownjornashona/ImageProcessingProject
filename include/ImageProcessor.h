#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class ImageProcessor {
public:
    static void toGray(cv::Mat& image);
    static void extractRGBChannels(const cv::Mat& image, cv::Mat& rChannel, cv::Mat& gChannel, cv::Mat& bChannel);
    static void edgeDetection(const cv::Mat& image, cv::Mat& edges);
    static void detectObjects(const cv::Mat& image, std::vector<std::string>& detectedClasses, std::vector<cv::Rect>& boxes);
    static void markRegions(cv::Mat& image, const std::vector<cv::Rect>& regions, const std::string& label);
    static void generateReport(const std::vector<std::string>& detectedClasses, const std::string& outputFile);
    static bool detectEvent(const cv::Mat& currentFrame, const cv::Mat& previousFrame);
};

#endif // IMAGEPROCESSOR_H
