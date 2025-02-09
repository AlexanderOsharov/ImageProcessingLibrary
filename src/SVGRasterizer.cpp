#include "SVGRasterizer.h"
#include <rsvg.h>
#include <cairo.h>
#include <fstream>

bool SVGRasterizer::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    // Загрузка SVG файла
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    // Создание контекста RSVG
    RsvgHandle* handle = rsvg_handle_new_from_data(buffer.data(), fileSize, nullptr);
    if (!handle) return false;

    // Получение размеров SVG
    double svgWidth, svgHeight;
    rsvg_handle_get_dimensions(handle, &svgWidth, &svgHeight);
    width = static_cast<int>(svgWidth);
    height = static_cast<int>(svgHeight);

    // Создание Cairo поверхности
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
    cairo_t* cr = cairo_create(surface);

    // Отрисовка SVG на Cairo поверхности
    rsvg_handle_render_cairo(handle, cr);

    // Чтение пикселей из Cairo поверхности
    unsigned char* data = cairo_image_surface_get_data(surface);
    pixels.resize(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 4; // RGBA
            int r = data[index];
            int g = data[index + 1];
            int b = data[index + 2];
            pixels[y][x] = (r << 16) | (g << 8) | b;
        }
    }

    // Очистка ресурсов
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    g_object_unref(handle);

    return true;
}

bool SVGRasterizer::supportsFormat(const std::string& extension) const {
    return extension == "svg";
}