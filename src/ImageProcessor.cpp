#include "ImageProcessor.h"
#include "Image.h"

void ImageProcessor::applyGrayscale(Image& image) {
    auto& pixels = image.getPixels();
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            int r = (pixel >> 16) & 0xFF;
            int g = (pixel >> 8) & 0xFF;
            int b = pixel & 0xFF;

            // Конвертация в градации серого
            int gray = static_cast<int>(0.299f * r + 0.587f * g + 0.114f * b);
            pixel = (gray << 16) | (gray << 8) | gray;
        }
    }
}

void ImageProcessor::resize(Image& image, int newWidth, int newHeight) {
    int oldWidth = image.getWidth();
    int oldHeight = image.getHeight();
    const auto& oldPixels = image.getPixels();

    std::vector<std::vector<int>> newPixels(newHeight, std::vector<int>(newWidth));

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            float oldX = static_cast<float>(x) / newWidth * oldWidth;
            float oldY = static_cast<float>(y) / newHeight * oldHeight;

            int newX = static_cast<int>(oldX);
            int newY = static_cast<int>(oldY);

            if (newX >= 0 && newX < oldWidth && newY >= 0 && newY < oldHeight) {
                newPixels[y][x] = oldPixels[newY][newX];
            } else {
                newPixels[y][x] = 0; // Black
            }
        }
    }

    image.setPixels(newPixels);
}

void ImageProcessor::adjustBrightness(Image& image, int brightness) {
    auto& pixels = image.getPixels();
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            int r = (pixel >> 16) & 0xFF;
            int g = (pixel >> 8) & 0xFF;
            int b = pixel & 0xFF;

            r = std::clamp(r + brightness, 0, 255);
            g = std::clamp(g + brightness, 0, 255);
            b = std::clamp(b + brightness, 0, 255);

            pixel = (r << 16) | (g << 8) | b;
        }
    }
}