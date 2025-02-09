#ifndef SVGrasterizer_H
#define SVGrasterizer_H

#include "IImageLoader.h"

class SVGRasterizer : public IImageLoader {
public:
    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override;
    bool supportsFormat(const std::string& extension) const override;
};

#endif // SVGrasterizer_H