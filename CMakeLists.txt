cmake_minimum_required(VERSION 3.10)
project(ImageProcessingLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем stb_image
include_directories(third_party)

add_library(ImageProcessing STATIC src/Image.cpp src/ImageProcessor.cpp)
target_include_directories(ImageProcessing PUBLIC include)