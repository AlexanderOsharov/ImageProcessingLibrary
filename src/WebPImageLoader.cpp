#include "WebPImageLoader.h"
#include <webp/decode.h> // Подключаем libwebp

bool WebPImageLoader::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    uint8_t* decoded = WebPDecodeRGB(buffer.data(), fileSize, &width, &height);
    if (!decoded) return false;

    pixels.resize(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;
            pixels[y][x] = (decoded[index + 0] << 16) | (decoded[index + 1] << 8) | decoded[index + 2];
        }
    }

    WebPFree(decoded);
    return true;
}

bool WebPImageLoader::supportsFormat(const std::string& extension) const {
    return extension == "webp";
}