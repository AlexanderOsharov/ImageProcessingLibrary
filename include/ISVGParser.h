#ifndef ISVGPARSER_H
#define ISVGPARSER_H

#include "IImageLoader.h"
#include <string>

class ISVGParser : public IImageLoader {
public:
    virtual ~ISVGParser() = default;

    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override = 0;
};

#endif // ISVGPARSER_H