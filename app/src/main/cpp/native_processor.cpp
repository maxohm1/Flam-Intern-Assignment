#include "native_processor.h"
#include <android/log.h>

#define LOG_TAG "NativeProcessor"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

Mat NativeProcessor::applyCannyEdge(const Mat& input, double threshold1, double threshold2) {
    Mat gray, edges;
    
    try {
        if (input.channels() == 4) {
            cvtColor(input, gray, COLOR_RGBA2GRAY);
        } else if (input.channels() == 3) {
            cvtColor(input, gray, COLOR_RGB2GRAY);
        } else {
            gray = input.clone();
        }
        
        // Apply Gaussian blur to reduce noise
        GaussianBlur(gray, gray, Size(5, 5), 1.5);
        
        // Apply Canny edge detection
        Canny(gray, edges, threshold1, threshold2);
        
        // Convert back to RGBA for display
        Mat result;
        cvtColor(edges, result, COLOR_GRAY2RGBA);
        
        LOGI("Canny edge detection applied successfully");
        return result;
    } catch (const Exception& e) {
        LOGE("Error in applyCannyEdge: %s", e.what());
        return input.clone();
    }
}

Mat NativeProcessor::convertToGrayscale(const Mat& input) {
    Mat gray, result;
    
    try {
        if (input.channels() == 4) {
            cvtColor(input, gray, COLOR_RGBA2GRAY);
        } else if (input.channels() == 3) {
            cvtColor(input, gray, COLOR_RGB2GRAY);
        } else {
            gray = input.clone();
        }
        
        // Convert back to RGBA
        cvtColor(gray, result, COLOR_GRAY2RGBA);
        
        LOGI("Grayscale conversion applied");
        return result;
    } catch (const Exception& e) {
        LOGE("Error in convertToGrayscale: %s", e.what());
        return input.clone();
    }
}

Mat NativeProcessor::invertColors(const Mat& input) {
    Mat result;
    
    try {
        bitwise_not(input, result);
        LOGI("Color inversion applied");
        return result;
    } catch (const Exception& e) {
        LOGE("Error in invertColors: %s", e.what());
        return input.clone();
    }
}

Mat NativeProcessor::applyGaussianBlur(const Mat& input, int kernelSize) {
    Mat result;
    
    try {
        if (kernelSize % 2 == 0) {
            kernelSize += 1;
        }
        
        GaussianBlur(input, result, Size(kernelSize, kernelSize), 0);
        LOGI("Gaussian blur applied with kernel size %d", kernelSize);
        return result;
    } catch (const Exception& e) {
        LOGE("Error in applyGaussianBlur: %s", e.what());
        return input.clone();
    }
}

