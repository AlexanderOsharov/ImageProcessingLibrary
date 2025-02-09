#include "Image.h"
#include "third_party/stb_image.h"
#include "third_party/stb_image_write.h"

Image::Image() : m_width(0), m_height(0) {}

Image::~Image() {}

bool Image::load(const std::string& filename) {
    int channels;
    unsigned char* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 0);

    if (!data) {
        return false;
    }

    m_pixels.clear();
    m_pixels.resize(m_height, std::vector<int>(m_width));

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            int index = (y * m_width + x) * channels;
            if (channels == 3) { // RGB
                m_pixels[y][x] = (data[index] << 16) | (data[index + 1] << 8) | data[index + 2];
            } else if (channels == 1) { // Grayscale
                m_pixels[y][x] = data[index];
            }
        }
    }

    stbi_image_free(data);
    return true;
}

bool Image::save(const std::string& filename) const {
    std::vector<unsigned char> buffer;
    buffer.reserve(m_width * m_height * 3);

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            int pixel = m_pixels[y][x];
            buffer.push_back((pixel >> 16) & 0xFF); // R
            buffer.push_back((pixel >> 8) & 0xFF);  // G
            buffer.push_back(pixel & 0xFF);         // B
        }
    }

    if (filename.find(".png") != std::string::npos) {
        stbi_write_png(filename.c_str(), m_width, m_height, 3, buffer.data(), 0);
    } else if (filename.find(".jpg") != std::string::npos) {
        stbi_write_jpg(filename.c_str(), m_width, m_height, 3, buffer.data(), 100);
    } else {
        return false;
    }

    return true;
}

void Image::setPixels(const std::vector<std::vector<int>>& pixels) {
    m_pixels = pixels;
    m_width = pixels[0].size();
    m_height = pixels.size();
}

const std::vector<std::vector<int>>& Image::getPixels() const {
    return m_pixels;
}

int Image::getWidth() const {
    return m_width;
}

int Image::getHeight() const {
    return m_height;
}