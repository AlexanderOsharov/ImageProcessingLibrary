#ifndef IMAGELOADERFACTORY_H
#define IMAGELOADERFACTORY_H

#include "IImageLoader.h"
#include <string>

class ImageLoaderFactory {
public:
    static IImageLoader* createLoader(const std::string& extension);
};

#endif // IMAGELOADERFACTORY_H