#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

static bool sameLetter(char ch, char target) {
    ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    target = static_cast<char>(tolower(static_cast<unsigned char>(target)));
    return ch == target;
}

int main() {
    char letter = 0;
    cout << "Enter a Latin letter: ";
    cin >> letter;

    ifstream input("input.txt");
    if (!input) {
        cerr << "Unable to open input file.\n";
        return 1;
    }

    ofstream output("output.txt", ios::trunc);
    if (!output) {
        cerr << "Unable to open output file.\n";
        return 1;
    }

    string word;
    bool hasWritten = false;

    while (input) {
        char ch = 0;
        input.get(ch);

        if (isalpha(static_cast<unsigned char>(ch))) {
            word += ch;
        } else {
            if (!word.empty()) {
                if (sameLetter(word[0], letter)) {
                    if (hasWritten) {
                        output << ' ';
                    }
                    output << word;
                    hasWritten = true;
                }
                word.clear();
            }
        }
    }

    if (!word.empty() && sameLetter(word[0], letter)) {
        if (hasWritten) {
            output << ' ';
        }
        output << word;
    }

    cout << "Done.\n";
    return 0;
}
