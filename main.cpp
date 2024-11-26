#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <memory>
#include "TextProcessor.h"  // Include the TextProcessor namespace
#include "RedBlackTree.h"   // Include the RedBlackTree class

// Function to read the text file and return its content as a string.
std::string readTextFile(const std::string& filePath) {
    return TextProcessor::readFile(filePath);
}

// Function to tokenize the text into words, removing non-alphanumeric characters.
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

// Function to write the sorted words to a file.
void writeSortedWordsToFile(const std::vector<std::string>& sortedWords, const std::string& filePath) {
    TextProcessor::writeSortedWords(sortedWords, filePath);
}

int main() {
    try {
        // Step 1: Read the file content
        std::string filePath = "war_and_peace.txt";  // Adjust to the correct file path
        std::string content = readTextFile(filePath);
        
        // Step 2: Tokenize the content into words
        std::vector<std::string> words = tokenizeText(content);
        
        // Step 3: Insert each unique word into the Red-Black Tree
        RedBlackTree<std::string> tree = insertWordsIntoTree(words);
        
        // Step 4: Get the sorted words by traversing the tree
        std::vector<std::string> sortedWords = tree.getSortedWords();
        
        // Step 5: Write the sorted words to an output file
        writeSortedWordsToFile(sortedWords, "output.txt");
        
        std::cout << "Sorted words have been written to 'output.txt'.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
