#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include "native_processor.h"
#include <opencv2/opencv.hpp>

#define LOG_TAG "JNI_Bridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace cv;

// Helper function to convert Android Bitmap to OpenCV Mat
Mat bitmapToMat(JNIEnv* env, jobject bitmap) {
    AndroidBitmapInfo info;
    void* pixels = nullptr;
    
    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        LOGE("Failed to get bitmap info");
        return Mat();
    }
    
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888");
        return Mat();
    }
    
    if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
        LOGE("Failed to lock pixels");
        return Mat();
    }
    
    Mat mat(info.height, info.width, CV_8UC4, pixels);
    Mat result = mat.clone();
    
    AndroidBitmap_unlockPixels(env, bitmap);
    
    return result;
}

// Helper function to convert OpenCV Mat to Android Bitmap
void matToBitmap(JNIEnv* env, const Mat& mat, jobject bitmap) {
    AndroidBitmapInfo info;
    void* pixels = nullptr;
    
    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        LOGE("Failed to get bitmap info");
        return;
    }
    
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888");
        return;
    }
    
    if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
        LOGE("Failed to lock pixels");
        return;
    }
    
    Mat temp(info.height, info.width, CV_8UC4, pixels);
    
    if (mat.type() == CV_8UC4) {
        mat.copyTo(temp);
    } else if (mat.type() == CV_8UC3) {
        cvtColor(mat, temp, COLOR_RGB2RGBA);
    } else if (mat.type() == CV_8UC1) {
        cvtColor(mat, temp, COLOR_GRAY2RGBA);
    }
    
    AndroidBitmap_unlockPixels(env, bitmap);
}

extern "C" {

JNIEXPORT void JNICALL
Java_max_ohm_flaminternassignment_jni_OpenCVProcessor_applyCannyEdge(
        JNIEnv* env,
        jobject /* this */,
        jobject inputBitmap,
        jobject outputBitmap) {
    
    LOGI("Applying Canny edge detection");
    
    Mat inputMat = bitmapToMat(env, inputBitmap);
    if (inputMat.empty()) {
        LOGE("Input Mat is empty");
        return;
    }
    
    Mat outputMat = NativeProcessor::applyCannyEdge(inputMat);
    matToBitmap(env, outputMat, outputBitmap);
}

JNIEXPORT void JNICALL
Java_max_ohm_flaminternassignment_jni_OpenCVProcessor_convertToGrayscale(
        JNIEnv* env,
        jobject /* this */,
        jobject inputBitmap,
        jobject outputBitmap) {
    
    LOGI("Converting to grayscale");
    
    Mat inputMat = bitmapToMat(env, inputBitmap);
    if (inputMat.empty()) {
        LOGE("Input Mat is empty");
        return;
    }
    
    Mat outputMat = NativeProcessor::convertToGrayscale(inputMat);
    matToBitmap(env, outputMat, outputBitmap);
}

JNIEXPORT void JNICALL
Java_max_ohm_flaminternassignment_jni_OpenCVProcessor_invertColors(
        JNIEnv* env,
        jobject /* this */,
        jobject inputBitmap,
        jobject outputBitmap) {
    
    LOGI("Inverting colors");
    
    Mat inputMat = bitmapToMat(env, inputBitmap);
    if (inputMat.empty()) {
        LOGE("Input Mat is empty");
        return;
    }
    
    Mat outputMat = NativeProcessor::invertColors(inputMat);
    matToBitmap(env, outputMat, outputBitmap);
}

JNIEXPORT jstring JNICALL
Java_max_ohm_flaminternassignment_jni_OpenCVProcessor_getOpenCVVersion(
        JNIEnv* env,
        jobject /* this */) {
    
    std::string version = CV_VERSION;
    return env->NewStringUTF(version.c_str());
}

} // extern "C"

