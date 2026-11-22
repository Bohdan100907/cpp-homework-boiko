#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

class Rational {
private:
    long long nominator;
    long long denominator;

    void normalize() {
        if (denominator == 0) {
            std::cerr << "Denominator cannot be zero.\n";
            std::exit(1);
        }
        if (denominator < 0) {
            nominator = -nominator;
            denominator = -denominator;
        }

        const long long divisor =
            std::gcd(std::llabs(nominator), denominator);
        nominator /= divisor;
        denominator /= divisor;
    }

public:
    Rational(long long nominator = 0, long long denominator = 1)
        : nominator(nominator), denominator(denominator) {
        normalize();
    }

    Rational(const Rational&) = default;

    long long getNominator() const {
        return nominator;
    }

    long long getDenominator() const {
        return denominator;
    }

    double toDouble() const {
        return static_cast<double>(nominator) /
               static_cast<double>(denominator);
    }

    Rational& operator+=(const Rational& other) {
        nominator =
            nominator * other.denominator +
            other.nominator * denominator;
        denominator *= other.denominator;
        normalize();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        nominator *= other.nominator;
        denominator *= other.denominator;
        normalize();
        return *this;
    }

    friend Rational operator+(Rational left, const Rational& right) {
        left += right;
        return left;
    }

    friend Rational operator*(Rational left, const Rational& right) {
        left *= right;
        return left;
    }

    friend bool operator<(const Rational& left, const Rational& right) {
        return left.nominator * right.denominator <
               right.nominator * left.denominator;
    }

    friend bool operator==(const Rational& left, const Rational& right) {
        return left.nominator == right.nominator &&
               left.denominator == right.denominator;
    }

    friend std::istream& operator>>(std::istream& input, Rational& number) {
        char slash;
        long long denominator;
        input >> number.nominator >> slash >> denominator;
        if (!input || slash != '/') {
            input.setstate(std::ios::failbit);
            return input;
        }
        number.denominator = denominator;
        number.normalize();
        return input;
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const Rational& number) {
        output << number.nominator;
        if (number.denominator != 1) {
            output << '/' << number.denominator;
        }
        return output;
    }
};

int main() {
    std::size_t size;
    std::cout << "Enter the number of rational numbers: ";
    std::cin >> size;
    if (!std::cin || size == 0) {
        std::cerr << "The array must contain at least one number.\n";
        return 1;
    }

    std::vector<Rational> numbers(size);
    std::cout << "Enter numbers in the form a/b: ";
    for (Rational& number : numbers) {
        if (!(std::cin >> number)) {
            std::cerr << "Invalid input.\n";
            return 1;
        }
    }

    Rational minimum = numbers.front();
    for (const Rational& number : numbers) {
        if (number < minimum) {
            minimum = number;
        }
    }
    std::cout << "Minimum rational number: " << minimum << '\n';

    constexpr double precision = 0.01;
    Rational sum;
    for (long long n = 1;; ++n) {
        Rational term(n % 2 == 1 ? 1 : -1, n * n);
        sum += term;

        if (std::fabs(term.toDouble()) < precision) {
            break;
        }
    }

    const double piSquareOver12 =
        std::acos(-1.0) * std::acos(-1.0) / 12.0;
    std::cout << "Alternating-series sum: " << sum
              << " (" << sum.toDouble() << ")\n";
    std::cout << "Expected pi^2/12: " << piSquareOver12 << '\n';
    std::cout << "Absolute error: "
              << std::fabs(sum.toDouble() - piSquareOver12) << '\n';

    return 0;
}