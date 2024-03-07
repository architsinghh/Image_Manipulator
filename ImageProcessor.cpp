#include "ImageProcessor.h"
#include <vector>

using namespace cv;
using namespace std;

void ImageProcessor::connectedComponentLabeling(const Mat& input, Mat& output) {
    Mat gray, binary;
    
    //convert to grayscale if needed
    if (input.channels() == 3) {
        cvtColor(input, gray, COLOR_BGR2GRAY);
    } else {
        gray = input;
    }

    //threshold to create a binary image
    threshold(gray, binary, 127, 255, THRESH_BINARY);

    //perform connected component labeling
    Mat labels;
    int nLabels = connectedComponents(binary, labels, 8, CV_32S);

    //filter small components
    Mat filteredLabels = Mat::zeros(labels.size(), CV_32S);
    int minComponentSize = 500; //minimum size of a component
    for (int label = 1; label < nLabels; ++label) {
        Mat component = (labels == label);
        int componentSize = countNonZero(component);
        if (componentSize > minComponentSize) {
            filteredLabels.setTo(label, component);
        }
    }

    //normalize the labels to [0, 255] for better visualization
    Mat labelImage;
    filteredLabels.convertTo(labelImage, CV_8U, 255.0 / (nLabels - 1));

    //apply a color map for cleaner visualization
    applyColorMap(labelImage, output, COLORMAP_JET);
}

void ImageProcessor::translateRegion(Mat& image, Rect region, Point offset) {
    Mat regionCopy = image(region).clone();
    regionCopy.copyTo(image(Rect(region.x + offset.x, region.y + offset.y, region.width, region.height)));
    rectangle(image, region, Scalar(0, 0, 255), 2);
}
