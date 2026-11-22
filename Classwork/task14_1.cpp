

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main() {
    std::ifstream input("input.txt");
    if (!input) {
        std::cerr << "Unable to open input.txt\n";
        return 1;
    }

    std::string expression;
    std::getline(input, expression);
    input.close();

    long long result = 0;
    char operation = '+';
    std::size_t index = 0;
    bool hasNumber = false;

    while (index < expression.size()) {
        if (expression[index] == ' ' ||
            expression[index] == '\t' ||
            expression[index] == '\r' ||
            expression[index] == '\n') {
            ++index;
            continue;
        }

        if (expression[index] == '+' || expression[index] == '-') {
            if (!hasNumber) {
                if (expression[index] == '-') {
                    operation = '-';
                } else {
                    operation = '+';
                }
            } else {
                operation = expression[index];
            }
            ++index;
            continue;
        }

        if (expression[index] < '0' || expression[index] > '9') {
            std::cerr << "Invalid expression\n";
            return 1;
        }

        long long number = 0;
        bool overflow = false;

        while (index < expression.size() &&
               expression[index] >= '0' &&
               expression[index] <= '9') {
            int digit = expression[index] - '0';
            if (number > (9223372036854775807LL - digit) / 10) {
                overflow = true;
                break;
            }
            number = number * 10 + digit;
            ++index;
        }

        if (overflow) {
            std::cerr << "Integer overflow\n";
            return 1;
        }

        if (!hasNumber) {
            result = (operation == '-') ? -number : number;
            hasNumber = true;
        } else {
            if (operation == '+') {
                if (number > std::numeric_limits<long long>::max() - result) {
                    std::cerr << "Integer overflow\n";
                    return 1;
                }
                result += number;
            } else {
                if (result < std::numeric_limits<long long>::min() + number) {
                    std::cerr << "Integer overflow\n";
                    return 1;
                }
                result -= number;
            }
        }
    }

    if (!hasNumber) {
        std::cerr << "Expression does not contain a number\n";
        return 1;
    }

    std::ofstream output("output.txt", std::ios::trunc);
    if (!output) {
        std::cerr << "Unable to open output.txt\n";
        return 1;
    }

    output << result << '\n';
    std::cout << result << '\n';
    return 0;
}
