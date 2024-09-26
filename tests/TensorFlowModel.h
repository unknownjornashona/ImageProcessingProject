#ifndef TENSORFLOWMODEL_H
#define TENSORFLOWMODEL_H

#include <opencv2/opencv.hpp>
#include <tensorflow/lite/model.h>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/kernels/register.h>
#include <tensorflow/lite/optional_debug_tools.h>
#include <memory>
#include <vector>

class TensorFlowModel {
private:
    std::unique_ptr<tflite::Interpreter> interpreter;

public:
    TensorFlowModel(const char* model_path);
    std::vector<cv::Point> detect(const cv::Mat& frame);
};

#endif // TENSORFLOWMODEL_H
