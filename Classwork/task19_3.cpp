#include <iostream>
#include <list>
#include <iterator>
#include <cstddef>

class Rational {
private:
    int numerator;
    int denominator;

public:
    Rational(int numeratorValue = 0, int denominatorValue = 1)
        : numerator(numeratorValue), denominator(denominatorValue) {
    }

    Rational operator+(const Rational& other) const {
        return Rational(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    Rational operator-(const Rational& other) const {
        return Rational(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    Rational operator*(const Rational& other) const {
        return Rational(numerator * other.numerator,
                        denominator * other.denominator);
    }

    Rational operator-() const {
        return Rational(-numerator, denominator);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Rational& value) {
        return stream << value.numerator << '/' << value.denominator;
    }
};

template <typename T>
class Polynomial {
private:
    std::list<T> coefficients;

public:
    void add(const T& value) {
        coefficients.push_back(value);
    }

    Polynomial add(const Polynomial& other) const {
        Polynomial result;
        auto first = coefficients.begin();
        auto second = other.coefficients.begin();

        while (first != coefficients.end() && second != other.coefficients.end()) {
            result.coefficients.push_back(*first + *second);
            ++first;
            ++second;
        }

        while (first != coefficients.end()) {
            result.coefficients.push_back(*first);
            ++first;
        }

        while (second != other.coefficients.end()) {
            result.coefficients.push_back(*second);
            ++second;
        }

        return result;
    }

    Polynomial subtract(const Polynomial& other) const {
        Polynomial result;
        auto first = coefficients.begin();
        auto second = other.coefficients.begin();

        while (first != coefficients.end() && second != other.coefficients.end()) {
            result.coefficients.push_back(*first - *second);
            ++first;
            ++second;
        }

        while (first != coefficients.end()) {
            result.coefficients.push_back(*first);
            ++first;
        }

        while (second != other.coefficients.end()) {
            result.coefficients.push_back(-(*second));
            ++second;
        }

        return result;
    }

    Polynomial multiply(const Polynomial& other) const {
        Polynomial result;

        for (std::size_t i = 0; i <= coefficients.size() + other.coefficients.size(); ++i) {
            result.coefficients.push_back(T());
        }

        auto first = coefficients.begin();
        std::size_t i = 0;

        while (first != coefficients.end()) {
            auto second = other.coefficients.begin();
            std::size_t j = 0;

            while (second != other.coefficients.end()) {
                auto position = result.coefficients.begin();
                std::advance(position, i + j);
                *position = *position + (*first) * (*second);
                ++second;
                ++j;
            }

            ++first;
            ++i;
        }

        return result;
    }

    T valueAt(T x) const {
        T result = T();

        for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
            result = result * x + *it;
        }

        return result;
    }

    void print() const {
        for (const T& coefficient : coefficients) {
            std::cout << coefficient << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    Polynomial<int> first;
    first.add(1);
    first.add(2);
    first.add(3);

    Polynomial<int> second;
    second.add(4);
    second.add(5);

    Polynomial<int> sum = first.add(second);
    sum.print();

    Polynomial<int> difference = first.subtract(second);
    difference.print();
    first.multiply(second).print();
    std::cout << first.valueAt(2) << '\n';

    return 0;
}
