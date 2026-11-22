#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Polynomial {
private:
    std::vector<double> coefficients;

public:
    Polynomial(std::size_t degree = 0) : coefficients(degree + 1, 0.0) {}

    Polynomial(const std::vector<double>& values)
        : coefficients(values) {}

    Polynomial(const Polynomial&) = default;
    Polynomial& operator=(const Polynomial&) = default;

    double& operator[](std::size_t index) {
        return coefficients[index];
    }

    const double& operator[](std::size_t index) const {
        return coefficients[index];
    }

    std::size_t size() const {
        return coefficients.size();
    }

    void input() {
        std::cout << "Enter " << coefficients.size()
                  << " coefficients: ";
        for (double& coefficient : coefficients) {
            std::cin >> coefficient;
        }
    }

    void print() const {
        for (std::size_t i = coefficients.size(); i > 0; --i) {
            std::size_t degree = i - 1;
            if (degree == coefficients.size() - 1) {
                std::cout << coefficients[degree];
            } else {
                std::cout << " " << coefficients[degree];
            }
            std::cout << " * x^" << degree;
        }
        std::cout << '\n';
    }

    Polynomial operator-(const Polynomial& other) const {
        std::size_t size = std::max(coefficients.size(), other.coefficients.size());
        std::vector<double> result(size, 0.0);

        for (std::size_t i = 0; i < size; ++i) {
            double left = i < coefficients.size() ? coefficients[i] : 0.0;
            double right = i < other.coefficients.size() ? other.coefficients[i] : 0.0;
            result[i] = left - right;
        }

        return Polynomial(result);
    }

    void writeBinary(const std::string& filename) const {
        std::ofstream output(filename, std::ios::binary);
        std::size_t size = coefficients.size();
        output.write(reinterpret_cast<const char*>(&size), sizeof(size));
        output.write(reinterpret_cast<const char*>(coefficients.data()),
                     static_cast<std::streamsize>(size * sizeof(double)));
    }

    void readBinary(const std::string& filename) {
        std::ifstream input(filename, std::ios::binary);
        std::size_t size = 0;
        input.read(reinterpret_cast<char*>(&size), sizeof(size));
        coefficients.resize(size);
        input.read(reinterpret_cast<char*>(coefficients.data()),
                   static_cast<std::streamsize>(size * sizeof(double)));
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const Polynomial& polynomial) {
        for (std::size_t i = 0; i < polynomial.coefficients.size(); ++i) {
            if (i > 0) {
                output << ' ';
            }
            output << polynomial.coefficients[i];
        }
        return output;
    }

    friend std::istream& operator>>(std::istream& input,
                                    Polynomial& polynomial) {
        for (double& coefficient : polynomial.coefficients) {
            input >> coefficient;
        }
        return input;
    }
};

int main() {
    Polynomial first(2);
    first.input();

    Polynomial second = first;
    std::cout << "Copy: " << second << '\n';

    second[0] = 1.0;
    second[1] = 2.0;
    second[2] = 3.0;

    Polynomial difference = first - second;
    std::cout << "Difference: " << difference << '\n';

    difference.writeBinary("polynomial.bin");

    Polynomial restored;
    restored.readBinary("polynomial.bin");
    std::cout << "Read from binary file: " << restored << '\n';

    return 0;
}