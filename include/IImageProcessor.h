#ifndef IIMAGEPROCESSOR_H
#define IIMAGEPROCESSOR_H

#include "Image.h"

class IImageProcessor {
public:
    virtual ~IImageProcessor() = default;

    virtual void process(Image& image) const = 0;
};

#endif // IIMAGEPROCESSOR_H