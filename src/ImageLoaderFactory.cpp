#include "ImageLoaderFactory.h"
#include "StbImageLoader.h"
#include "SimpleSVGParser.h"
#include "BMPImageLoader.h"

IImageLoader* ImageLoaderFactory::createLoader(const std::string& extension) {
    if (extension == "bmp") {
        return new BMPImageLoader();
    } else if (extension == "svg") {
        return new SimpleSVGParser(); // Наш новый SVG-парсер
    } else if (extension == "jpg" || extension == "jpeg" ||
               extension == "png" || extension == "tga" ||
               extension == "gif") {
        return new StbImageLoader();
    }
    return nullptr;
}