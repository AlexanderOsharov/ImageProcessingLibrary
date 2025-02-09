#include <iostream>
#include "Image.h"
#include "GrayscaleProcessor.h"
#include "ResizeProcessor.h"

int main() {
    Image image;
    if (!image.load("input.jpg")) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    GrayscaleProcessor grayscaleProcessor;
    grayscaleProcessor.process(image);

    ResizeProcessor resizeProcessor(512, 512);
    resizeProcessor.process(image);

    if (!image.save("output.png")) {
        std::cerr << "Failed to save image" << std::endl;
        return 1;
    }

    std::cout << "Image processed successfully!" << std::endl;
    return 0;
}