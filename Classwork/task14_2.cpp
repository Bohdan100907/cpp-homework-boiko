#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool startsWithDerOrDas(const std::string& word) {
    if (word.size() < 3) {
        return false;
    }

    std::string prefix = word.substr(0, 3);
    for (char& symbol : prefix) {
        symbol = static_cast<char>(std::tolower(
            static_cast<unsigned char>(symbol)));
    }

    return prefix == "der" || prefix == "das";
}

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Unable to open input.txt\n";
        return 1;
    }

    std::vector<std::string> selected;
    std::vector<std::string> remaining;
    std::string word;
    char symbol;

    while (input.get(symbol)) {
        if (std::isalpha(static_cast<unsigned char>(symbol))) {
            word += symbol;
        } else {
            if (!word.empty()) {
                if (startsWithDerOrDas(word)) {
                    selected.push_back(word);
                } else {
                    remaining.push_back(word);
                }
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        if (startsWithDerOrDas(word)) {
            selected.push_back(word);
        } else {
            remaining.push_back(word);
        }
    }

    std::ofstream output("output.txt", std::ios::trunc);
    if (!output) {
        std::cerr << "Unable to open output.txt\n";
        return 1;
    }

    bool first = true;
    for (const std::string& item : selected) {
        if (!first) {
            output << ' ';
        }
        output << item;
        first = false;
    }

    for (const std::string& item : remaining) {
        if (!first) {
            output << ' ';
        }
        output << item;
        first = false;
    }

    std::cout << "Done.\n";
    return 0;
}