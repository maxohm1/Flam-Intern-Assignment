cmake_minimum_required(VERSION 3.22.1)

project("opencv_processor")

set(CMAKE_CXX_STANDARD 14)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add native library
add_library(
        opencv_processor
        SHARED
        native_processor.cpp
        jni_bridge.cpp
)

# Link libraries
target_link_libraries(
        opencv_processor
        ${OpenCV_LIBS}
        android
        log
        jnigraphics
)

