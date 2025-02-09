#include "TIFFImageLoader.h"
#include <fstream>
#include <cstdint>

bool TIFFImageLoader::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    // Реализация загрузки TIFF
    // Это достаточно сложный формат, поэтому лучше использовать стороннюю библиотеку, например, libtiff
    return false; // Пока не реализовано
}

bool TIFFImageLoader::supportsFormat(const std::string& extension) const {
    return extension == "tiff" || extension == "tif";
}