#include "ResizeProcessor.h"
#include "Image.h"

ResizeProcessor::ResizeProcessor(int newWidth, int newHeight)
    : m_newWidth(newWidth), m_newHeight(newHeight) {}

void ResizeProcessor::process(Image& image) const {
    const auto& pixels = image.getPixels();
    int oldWidth = image.getWidth();
    int oldHeight = image.getHeight();

    std::vector<std::vector<int>> newPixels(m_newHeight, std::vector<int>(m_newWidth));

    for (int y = 0; y < m_newHeight; ++y) {
        for (int x = 0; x < m_newWidth; ++x) {
            float oldX = static_cast<float>(x) / m_newWidth * oldWidth;
            float oldY = static_cast<float>(y) / m_newHeight * oldHeight;

            int newX = static_cast<int>(oldX);
            int newY = static_cast<int>(oldY);

            if (newX >= 0 && newX < oldWidth && newY >= 0 && newY < oldHeight) {
                newPixels[y][x] = pixels[newY][newX];
            } else {
                newPixels[y][x] = 0; // Black
            }
        }
    }

    image.setPixels(newPixels);
}