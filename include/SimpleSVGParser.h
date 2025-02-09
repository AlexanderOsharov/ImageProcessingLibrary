#ifndef SIMPLESVGPARSER_H
#define SIMPLESVGPARSER_H

#include "ISVGParser.h"
#include <string>
#include <vector>
#include <unordered_map>

class SimpleSVGParser : public ISVGParser {
public:
    bool load(const std::string& filename, int& width, int& height, std::vector<std::vector<int>>& pixels) const override;

private:
    void parseRect(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const;
    void parseLine(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const;
    void parseEllipse(const std::unordered_map<std::string, std::string>& attributes, std::vector<std::vector<int>>& pixels) const;

    std::unordered_map<std::string, std::string> parseAttributes(const std::string& line) const;
};

#endif // SIMPLESVGPARSER_H