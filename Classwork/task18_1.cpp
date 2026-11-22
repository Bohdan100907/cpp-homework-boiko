#include <iostream>
#include <string>

class Rational {
private:
    int numerator;
    int denominator;

public:
    Rational(int numeratorValue, int denominatorValue)
        : numerator(numeratorValue), denominator(denominatorValue) {
    }

    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Rational& number) {
        return stream << number.numerator << '/' << number.denominator;
    }
};

template <typename T>
T maximum(const T& first, const T& second) {
    return first > second ? first : second;
}

int main() {
    std::cout << maximum(10, 25) << '\n';
    std::cout << maximum(3.5, 2.1) << '\n';

    std::string firstString = "apple";
    std::string secondString = "banana";
    std::cout << maximum(firstString, secondString) << '\n';

    Rational firstFraction(3, 4);
    Rational secondFraction(2, 3);
    std::cout << maximum(firstFraction, secondFraction) << '\n';

    return 0;
}
