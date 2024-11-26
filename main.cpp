#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <memory>
#include "TextProcessor.h"
#include "RedBlackTree.h"
std::string readTextFile(const std::string& filePath) {
    return TextProcessor::readFile(filePath);
}
std::vector<std::string> tokenizeText(const std::string& text) {
    return TextProcessor::tokenizeText(text);
}
RedBlackTree<std::string> insertWordsIntoTree(const std::vector<std::string>& words) {
    RedBlackTree<std::string> tree;
    std::for_each(words.begin(), words.end(), [&tree](const std::string& word) {
        tree = tree.insert(word);  // Insert each word immutably
    });
    return tree;
}
void writeSortedWordsToFile(const std::vector<std::string>& sortedWords, const std::string& filePath) {
    TextProcessor::writeSortedWords(sortedWords, filePath);
}
int main() {
    try {
        std::string filePath = "war_and_peace.txt";
        std::string content = readTextFile(filePath);
        std::vector<std::string> words = tokenizeText(content);
        RedBlackTree<std::string> tree = insertWordsIntoTree(words);
        std::vector<std::string> sortedWords = tree.getSortedWords();
        writeSortedWordsToFile(sortedWords, "output.txt");
        std::cout << "Sorted words have been written to 'output.txt'.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
