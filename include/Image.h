#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

class Image {
public:
    Image();
    ~Image();

    bool load(const std::string& filename);
    bool save(const std::string& filename) const;

    void setPixels(const std::vector<std::vector<int>>& pixels);
    const std::vector<std::vector<int>>& getPixels() const;

    int getWidth() const;
    int getHeight() const;

private:
    int m_width;
    int m_height;
    std::vector<std::vector<int>> m_pixels; // RGB или градации серого
};

#endif // IMAGE_H