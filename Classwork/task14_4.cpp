#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Unable to open input.txt\n";
        return 1;
    }

    std::string text(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());

    std::vector<std::string> tags;
    std::size_t position = 0;

    while (position < text.size()) {
        std::size_t opening = text.find('<', position);
        if (opening == std::string::npos) {
            break;
        }

        std::size_t closing = text.find('>', opening + 1);
        if (closing == std::string::npos) {
            break;
        }

        std::string tag = text.substr(opening + 1, closing - opening - 1);
        if (tag == "td" || tag == "/td") {
            tags.push_back(tag);
        }

        position = closing + 1;
    }

    int depth = 0;
    bool valid = true;

    for (const std::string& tag : tags) {
        if (tag == "td") {
            ++depth;
        } else {
            --depth;
        }

        if (depth < 0) {
            valid = false;
            break;
        }
    }

    if (depth != 0) {
        valid = false;
    }

    std::ofstream output("output.txt", std::ios::trunc);
    if (!output) {
        std::cerr << "Unable to open output.txt\n";
        return 1;
    }

    output << (valid ? "Correct" : "Incorrect") << '\n';
    std::cout << (valid ? "Correct" : "Incorrect") << '\n';
    return 0;
}