#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

namespace TextProcessor {

    // Lambda to read a file and return its content as a string.
    const auto readFile = [](const std::string& filePath) -> std::string {
        std::ifstream file(filePath);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }
        std::ostringstream content;
        content << file.rdbuf();
        return content.str();
    };

    const auto tokenizeText = [](const std::string& text) -> std::vector<std::string> {
        if (text.empty()) {
            return {};
        }

        // Updated to exclude numbers and tokenize
        auto isDelimiter = [](char c) { return !std::isalnum(c) || std::isdigit(c); };

        std::vector<std::string> tokens;
        auto it = text.begin();

        while (it != text.end()) {
            auto start = std::find_if_not(it, text.end(), isDelimiter);
            auto end = std::find_if(start, text.end(), isDelimiter);

            if (start != text.end()) {
                std::string token(start, end);
                
                // Convert the token to lowercase
                std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });

                tokens.push_back(token);
            }

            it = end;
        }

        return tokens;
    };

    const auto writeSortedWords = [](const std::vector<std::string>& words,
                                    const std::string& filePath) -> std::vector<std::string> {
        std::ofstream file(filePath);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::for_each(words.begin(), words.end(), [&file](const std::string& word) {
            file << word << "\n";
        });

        return words;
    };
} // namespace TextProcessor
