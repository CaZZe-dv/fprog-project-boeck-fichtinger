#include <iostream>
#include <vector>
#include <set>
#include "FileReader.hpp"
#include "Tokenizer.hpp"
#include "FileWriter.hpp"

int main() {
    try {
        // Read the file
        auto content = FileReader::readFile("WarAndPeace.txt");

        // Tokenize words
        auto words = Tokenizer::tokenize(content);

        // Here belongs the red black tree implementation

        // Write sorted words to file
        //FileWriter::writeFile("output.txt", sortedWords);

        std::cout << "Processing complete. Output written to 'output.txt'.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
