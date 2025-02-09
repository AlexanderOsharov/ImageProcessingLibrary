#ifndef TIFFIMAGeloader_H
#define TIFFIMAGeloader_H

#include "IImageLoader.h"

class TIFFImageLoader : public IImageLoader {
public:
    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override;
    bool supportsFormat(const std::string& extension) const override;
};

#endif // TIFFIMAGeloader_H