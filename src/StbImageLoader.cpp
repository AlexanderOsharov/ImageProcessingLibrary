#include "StbImageLoader.h"
#include "third_party/stb_image.h"

bool StbImageLoader::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    int channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (!data) return false;

    pixels.clear();
    pixels.resize(height, std::vector<int>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            if (channels == 3) { // RGB
                pixels[y][x] = (data[index] << 16) | (data[index + 1] << 8) | data[index + 2];
            } else if (channels == 1) { // Grayscale
                pixels[y][x] = data[index];
            }
        }
    }

    stbi_image_free(data);
    return true;
}

bool StbImageLoader::supportsFormat(const std::string& extension) const {
    return extension == "jpg" || extension == "jpeg" ||
           extension == "png" || extension == "bmp" ||
           extension == "tga" || extension == "gif"; // Добавляем поддержку GIF
}