#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool isSeparator(char symbol) {
    return std::isspace(static_cast<unsigned char>(symbol)) ||
           symbol == ',' || symbol == '.' ||
           symbol == '!' || symbol == '?';
}

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Unable to open input.txt\n";
        return 1;
    }

    std::vector<std::string> words;
    std::string word;
    char symbol;

    while (input.get(symbol)) {
        if (isSeparator(symbol)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += symbol;
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    std::ofstream output("output.txt", std::ios::trunc);
    if (!output) {
        std::cerr << "Unable to open output.txt\n";
        return 1;
    }

    for (std::size_t i = 0; i < words.size(); ++i) {
        if (i > 0) {
            output << ' ';
        }
        for (std::size_t j = words[i].size(); j > 0; --j) {
            output << words[i][j - 1];
        }
    }

    output << '\n';
    std::cout << "Done.\n";
    return 0;
}