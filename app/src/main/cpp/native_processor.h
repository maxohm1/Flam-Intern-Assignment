#ifndef NATIVE_PROCESSOR_H
#define NATIVE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class NativeProcessor {
public:
    // Apply Canny edge detection
    static Mat applyCannyEdge(const Mat& input, double threshold1 = 50, double threshold2 = 150);
    
    // Convert to grayscale
    static Mat convertToGrayscale(const Mat& input);
    
    // Invert colors
    static Mat invertColors(const Mat& input);
    
    // Apply Gaussian blur
    static Mat applyGaussianBlur(const Mat& input, int kernelSize = 5);
};

#endif // NATIVE_PROCESSOR_H

