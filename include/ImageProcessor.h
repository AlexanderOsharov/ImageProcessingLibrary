#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "Image.h"
#include <string>

class ImageProcessor {
public:
    static void applyGrayscale(Image& image);
    static void resize(Image& image, int newWidth, int newHeight);
    static void adjustBrightness(Image& image, int brightness);
};

#endif // IMAGEPROCESSOR_H