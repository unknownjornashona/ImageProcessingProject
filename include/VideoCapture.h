#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoCapture {
public:
    void captureVideo(const std::string& outputDir, int imageCount);
};

#endif // VIDEOCAPTURE_H
