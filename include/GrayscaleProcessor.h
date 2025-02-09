#ifndef GRAYSCALEPROCESSOR_H
#define GRAYSCALEPROCESSOR_H

#include "IImageProcessor.h"

class GrayscaleProcessor : public IImageProcessor {
public:
    void process(Image& image) const override;
};

#endif // GRAYSCALEPROCESSOR_H