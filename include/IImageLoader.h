#ifndef IIMAGELoader_H
#define IIMAGELoader_H

#include <string>
#include <vector>

class IImageLoader {
public:
    virtual ~IImageLoader() = default;

    // Загружает изображение из файла
    virtual bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const = 0;

    // Проверяет, поддерживает ли этот загрузчик указанный формат
    virtual bool supportsFormat(const std::string& extension) const = 0;
};

#endif // IIMAGELoader_H