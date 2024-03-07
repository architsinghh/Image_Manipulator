#include <iostream>
#include "ImageProcessor.h"

using namespace cv;
using namespace std;

int main() {
    string imagePath = "test_image.png"; //image file path
    Mat image = imread(imagePath);
    if (image.empty()) {
        cout << "Error: Image not found!" << endl;
        return -1;
    }

    //connected-component labeling
    Mat labeledImage;
    ImageProcessor::connectedComponentLabeling(image, labeledImage);
    imshow("Connected Components", labeledImage);

    //user input for region and offset
    int x, y, width, height;
    int dx, dy;

    cout << "Enter the top-left corner coordinates of the region (x, y): ";
    cin >> x >> y;
    cout << "Enter the width and height of the region: ";
    cin >> width >> height;
    cout << "Enter the translation offset (dx, dy): ";
    cin >> dx >> dy;

    //define the region and offset
    Rect region(x, y, width, height);
    Point offset(dx, dy);

    //region translation
    ImageProcessor::translateRegion(image, region, offset);
    imshow("Translated Region", image);

    //save translated region image
    imwrite("output_translated_region_user_input.png", image);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
