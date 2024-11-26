#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "RedBlackTree.h"
#include "TextProcessor.h"
#include <fstream>

TEST_CASE("Red-Black Tree Operations") {
    RedBlackTree<int> tree;
    SUBCASE("Insert values into tree") {
        tree = tree.insert(10);
        tree = tree.insert(20);
        tree = tree.insert(5);
        tree = tree.insert(15);
        tree = tree.insert(25);
        auto sortedWords = tree.getSortedWords();
        CHECK(sortedWords == std::vector<int>{5, 10, 15, 20, 25});
    }
    SUBCASE("Red-Black Tree Validation") {
        tree = tree.insert(10);
        tree = tree.insert(20);
        tree = tree.insert(30);
        tree = tree.insert(15);
        tree = tree.insert(5);
        CHECK(tree.validate() == true);
    }
    SUBCASE("Insert duplicate values") {
        tree = tree.insert(10);
        tree = tree.insert(20);
        tree = tree.insert(10);
        auto sortedWords = tree.getSortedWords();
        CHECK(sortedWords == std::vector<int>{10, 20});
    }
    SUBCASE("Insert and validate large number of elements") {
        for (int i = 0; i < 1000; ++i) {
            tree = tree.insert(i);
        }
        CHECK(tree.validate() == true);
    }
    SUBCASE("Insert and check balanced tree") {
        tree = tree.insert(10);
        tree = tree.insert(5);
        tree = tree.insert(15);
        tree = tree.insert(3);
        tree = tree.insert(7);
        CHECK(tree.validate() == true);
    }
}
TEST_CASE("TextProcessor - File Reading, Tokenization, and Writing") {
    SUBCASE("Tokenize a string") {
        std::string text = "Hello, world! This is a test.";
        auto tokens = TextProcessor::tokenizeText(text);
        CHECK(tokens == std::vector<std::string>{"hello", "world", "this", "is", "a", "test"});
    }
    SUBCASE("Read non-existent file") {
        CHECK_THROWS_AS(TextProcessor::readFile("non_existent_file.txt"), std::runtime_error);
    }
    SUBCASE("Tokenize an empty string") {
        std::string emptyText = "";
        auto tokens = TextProcessor::tokenizeText(emptyText);
        CHECK(tokens.empty());
    }
    SUBCASE("Tokenize string with punctuation") {
        std::string textWithPunctuation = "Hello, world! Welcome to C++.";
        auto tokens = TextProcessor::tokenizeText(textWithPunctuation);
        CHECK(tokens == std::vector<std::string>{"hello", "world", "welcome", "to", "c"});
    }
}
TEST_CASE("Combined Red-Black Tree and TextProcessor Tests") {
    SUBCASE("Red-Black Tree insert and TextProcessor tokenization") {
        RedBlackTree<int> tree;
        tree = tree.insert(10);
        tree = tree.insert(20);
        tree = tree.insert(5);
        auto sortedWords = tree.getSortedWords();
        CHECK(sortedWords == std::vector<int>{5, 10, 20});
        std::string text = "This is a test.";
        auto tokens = TextProcessor::tokenizeText(text);
        CHECK(tokens == std::vector<std::string>{"this", "is", "a", "test"});
    }
    SUBCASE("TextProcessor writing to file and Red-Black Tree validation") {
        std::vector<std::string> words = {"apple", "orange", "banana"};
        std::string tempFilePath = "sorted_words_combined.txt";
        TextProcessor::writeSortedWords(words, tempFilePath);
        RedBlackTree<int> tree;
        tree = tree.insert(10);
        tree = tree.insert(20);
        tree = tree.insert(30);
        CHECK(tree.validate() == true);
    }
}
