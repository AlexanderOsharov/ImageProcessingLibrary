#ifndef RESIZEPROCESSOR_H
#define RESIZEPROCESSOR_H

#include "IImageProcessor.h"

class ResizeProcessor : public IImageProcessor {
public:
    ResizeProcessor(int newWidth, int newHeight);

    void process(Image& image) const override;

private:
    int m_newWidth;
    int m_newHeight;
};

#endif // RESIZEPROCESSOR_H