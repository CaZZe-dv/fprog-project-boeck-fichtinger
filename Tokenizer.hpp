
#pragma once

#include <string>
#include <vector>
#include <regex>
#include <functional>

namespace Tokenizer {
    const std::function<std::vector<std::string>(const std::string&)> tokenize = [](const std::string& text) {
        std::regex wordRegex("[a-zA-Z]+");
        auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
        auto wordsEnd = std::sregex_iterator();

        std::vector<std::string> words;
        std::transform(wordsBegin, wordsEnd, std::back_inserter(words), [](const std::smatch& match) {
            return match.str();
        });
        return words;
    };
}