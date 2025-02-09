#ifndef STBIMAGeloader_H
#define STBIMAGeloader_H

#include "IImageLoader.h"

class StbImageLoader : public IImageLoader {
public:
    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override;
    bool supportsFormat(const std::string& extension) const override;
};

#endif // STBIMAGeloader_H