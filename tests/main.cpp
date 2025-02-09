#include <iostream>
#include "Image.h"
#include "ImageLoaderFactory.h"

int main() {
    std::string filename = "input.svg"; // Можно заменить на любой поддерживаемый формат
    std::string outputFilename = "output.png";

    // Определение формата по расширению
    std::string extension = filename.substr(filename.find_last_of(".") + 1);

    // Создание загрузчика
    IImageLoader* loader = ImageLoaderFactory::createLoader(extension);
    if (!loader) {
        std::cerr << "Unsupported image format" << std::endl;
        return 1;
    }

    Image image;
    int width, height;
    std::vector<std::vector<int>> pixels;

    if (!loader->load(filename, width, height, pixels)) {
        std::cerr << "Failed to load image" << std::endl;
        delete loader;
        return 1;
    }

    image.setPixels(pixels);

    if (!image.save(outputFilename)) {
        std::cerr << "Failed to save image" << std::endl;
        delete loader;
        return 1;
    }

    std::cout << "Image processed successfully!" << std::endl;
    delete loader;
    return 0;
}