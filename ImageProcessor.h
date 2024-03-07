#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    static void connectedComponentLabeling(const cv::Mat& inputImage, cv::Mat& labeledImage);
    static void translateRegion(cv::Mat& image, cv::Rect region, cv::Point offset);
};

#endif 
