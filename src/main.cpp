#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImageProcessor.h"
#include "VideoCapture.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <output_directory> <image_count>" << std::endl;
        return 1;
    }

    std::string outputDir = argv[1];
    int imageCount = std::stoi(argv[2]);

    VideoCapture vc;
    vc.captureVideo(outputDir, imageCount);
    return 0;
}
