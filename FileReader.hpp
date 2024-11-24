#pragma once

#include <string>
#include <fstream>
#include <functional>

namespace FileReader {
    const std::function<std::string(const std::string&)> readFile = [](const std::string& fileName) -> std::string {
        std::ifstream file(fileName);
        if (!file) throw std::runtime_error("Could not open file: " + fileName);
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    };
}