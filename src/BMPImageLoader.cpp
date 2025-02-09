#include "BMPImageLoader.h"
#include <fstream>
#include <cstdint>

bool BMPImageLoader::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    uint16_t fileType;
    file.read(reinterpret_cast<char*>(&fileType), sizeof(fileType));
    if (fileType != 0x4D42) return false; // Not a BMP file

    uint32_t fileSize, offset, dibHeaderSize, imageWidth, imageHeight;
    uint16_t reserved1, reserved2, planes;
    uint8_t bitsPerPixel;

    file.read(reinterpret_cast<char*>(&reserved1), sizeof(reserved1));
    file.read(reinterpret_cast<char*>(&reserved2), sizeof(reserved2));
    file.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
    file.seekg(10, std::ios::beg);
    file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

    file.seekg(14, std::ios::beg);
    file.read(reinterpret_cast<char*>(&dibHeaderSize), sizeof(dibHeaderSize));
    file.read(reinterpret_cast<char*>(&imageWidth), sizeof(imageWidth));
    file.read(reinterpret_cast<char*>(&imageHeight), sizeof(imageHeight));
    file.read(reinterpret_cast<char*>(&planes), sizeof(planes));
    file.read(reinterpret_cast<char*>(&bitsPerPixel), sizeof(bitsPerPixel));

    if (bitsPerPixel != 24) return false; // Only 24-bit BMP supported

    width = imageWidth;
    height = imageHeight;
    pixels.resize(height, std::vector<int>(width));

    file.seekg(offset, std::ios::beg);
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            unsigned char b, g, r;
            file.read(reinterpret_cast<char*>(&b), sizeof(b));
            file.read(reinterpret_cast<char*>(&g), sizeof(g));
            file.read(reinterpret_cast<char*>(&r), sizeof(r));
            pixels[y][x] = (r << 16) | (g << 8) | b;
        }
        // Skip padding bytes
        file.seekg((4 - ((width * 3) % 4)) % 4, std::ios::cur);
    }

    return true;
}

bool BMPImageLoader::supportsFormat(const std::string& extension) const {
    return extension == "bmp";
}