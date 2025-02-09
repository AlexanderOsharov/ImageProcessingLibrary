#include "GrayscaleProcessor.h"
#include "Image.h"

void GrayscaleProcessor::process(Image& image) const {
    const auto& pixels = image.getPixels();
    std::vector<std::vector<int>> newPixels(pixels.size(), std::vector<int>(pixels[0].size()));

    for (size_t y = 0; y < pixels.size(); ++y) {
        for (size_t x = 0; x < pixels[y].size(); ++x) {
            int pixel = pixels[y][x];
            int r = (pixel >> 16) & 0xFF;
            int g = (pixel >> 8) & 0xFF;
            int b = pixel & 0xFF;

            int gray = static_cast<int>(0.299f * r + 0.587f * g + 0.114f * b);
            newPixels[y][x] = gray;
        }
    }

    image.setPixels(newPixels);
}