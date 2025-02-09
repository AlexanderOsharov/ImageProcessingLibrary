#include "SimpleSVGParser.h"
#include <fstream>
#include <sstream>
#include <cmath>

bool SimpleSVGParser::load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    int canvasWidth = 0, canvasHeight = 0;
    bool hasCanvas = false;

    while (std::getline(file, line)) {
        if (line.find("<svg") != std::string::npos) {
            auto attributes = parseAttributes(line);
            canvasWidth = std::stoi(attributes.at("width"));
            canvasHeight = std::stoi(attributes.at("height"));
            hasCanvas = true;
        } else if (line.find("<rect") != std::string::npos) {
            auto attributes = parseAttributes(line);
            parseRect(attributes, pixels);
        } else if (line.find("<line") != std::string::npos) {
            auto attributes = parseAttributes(line);
            parseLine(attributes, pixels);
        } else if (line.find("<ellipse") != std::string::npos) {
            auto attributes = parseAttributes(line);
            parseEllipse(attributes, pixels);
        }
    }

    if (!hasCanvas) return false;

    width = canvasWidth;
    height = canvasHeight;
    pixels.resize(height, std::vector<int>(width, 0)); // Инициализация чёрного холста
    return true;
}

void SimpleSVGParser::parseRect(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const {
    int x = std::stoi(attributes.at("x"));
    int y = std::stoi(attributes.at("y"));
    int width = std::stoi(attributes.at("width"));
    int height = std::stoi(attributes.at("height"));
    int color = std::stoi(attributes.at("fill"));

    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            if (i >= 0 && i < pixels.size() && j >= 0 && j < pixels[0].size()) {
                pixels[i][j] = color;
            }
        }
    }
}

void SimpleSVGParser::parseLine(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const {
    int x1 = std::stoi(attributes.at("x1"));
    int y1 = std::stoi(attributes.at("y1"));
    int x2 = std::stoi(attributes.at("x2"));
    int y2 = std::stoi(attributes.at("y2"));
    int color = std::stoi(attributes.at("stroke"));

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x1 >= 0 && x1 < pixels[0].size() && y1 >= 0 && y1 < pixels.size()) {
            pixels[y1][x1] = color;
        }

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void SimpleSVGParser::parseEllipse(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const {
    int cx = std::stoi(attributes.at("cx"));
    int cy = std::stoi(attributes.at("cy"));
    int rx = std::stoi(attributes.at("rx"));
    int ry = std::stoi(attributes.at("ry"));
    int color = std::stoi(attributes.at("fill"));

    float error = 0;
    int x = 0;
    int y = ry;

    while (x <= y) {
        if (cx + x >= 0 && cx + x < pixels[0].size() && cy + y >= 0 && cy + y < pixels.size()) {
            pixels[cy + y][cx + x] = color;
            pixels[cy - y][cx + x] = color;
            pixels[cy + y][cx - x] = color;
            pixels[cy - y][cx - x] = color;
        }

        error += (2 * x + 1) * (ry * ry);
        if (error >= 0) {
            y--;
            error -= (2 * y - 1) * (rx * rx);
        }
        x++;
    }
}

std::unordered_map<std::string, std::string> SimpleSVGParser::parseAttributes(const std::string& line) const {
    std::unordered_map<std::string, std::string> attributes;
    std::stringstream ss(line);
    std::string token;

    while (ss >> token) {
        size_t equalsPos = token.find('=');
        if (equalsPos != std::string::npos) {
            std::string key = token.substr(0, equalsPos);
            std::string value = token.substr(equalsPos + 2, token.size() - equalsPos - 3); // Удаляем кавычки
            attributes[key] = value;
        }
    }

    return attributes;
}