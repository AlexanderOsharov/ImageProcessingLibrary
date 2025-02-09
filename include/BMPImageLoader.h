#ifndef BMPIMAGeloader_H
#define BMPIMAGeloader_H

#include "IImageLoader.h"

class BMPImageLoader : public IImageLoader {
public:
    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override;
    bool supportsFormat(const std::string& extension) const override;
};

#endif // BMPIMAGeloader_H