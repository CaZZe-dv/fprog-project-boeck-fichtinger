#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <functional>

namespace FileWriter {
    const std::function<void(const std::string&, const std::vector<std::string>&)> writeFile =
        [](const std::string& fileName, const std::vector<std::string>& words) {
            std::ofstream file(fileName);
            if (!file) throw std::runtime_error("Could not open file: " + fileName);
            for (const auto& word : words) {
                file << word << "\n";
            }
        };
}