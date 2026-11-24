// Оператори керування в C та C++ задають порядок виконання програми:
// послідовність команд, розгалуження та цикли.
// У C розгалуження реалізують трьома способами: if/else, switch та умовним
// оператором ?:; кожен спосіб доречний для різних умов і структури вибору.
// У C++ цикли for, while та do-while повторюють блок команд; for зручний для
// лічильника, while перевіряє умову перед ітерацією, а do-while — після неї.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {

constexpr int kMaxTerms = 10000;
constexpr double kPi = 3.14159265358979323846;

double reduce_angle(double angle) {
    double reduced = std::fmod(angle, 2.0 * kPi);
    if (reduced > kPi) {
        reduced -= 2.0 * kPi;
    } else if (reduced < -kPi) {
        reduced += 2.0 * kPi;
    }
    return reduced;
}

double sin_approx(double angle, double epsilon) {
    const double x = reduce_angle(angle);
    double term = x;
    double sum = term;

    for (int n = 0; n < kMaxTerms; ++n) {
        const double a = static_cast<double>(2 * n + 2);
        const double b = static_cast<double>(2 * n + 3);
        const double next_term = term * (-x * x) / (a * b);

        if (std::abs(next_term) < epsilon) {
            return sum;
        }

        sum += next_term;
        term = next_term;
    }

    throw std::runtime_error("ERROR: sin Taylor series did not converge.");
}

double sh_approx(double x, double epsilon) {
    // sinh is not periodic, so reducing x modulo 2*pi would change its value.
    double term = x;
    double sum = term;

    for (int n = 0; n < kMaxTerms; ++n) {
        const double a = static_cast<double>(2 * n + 2);
        const double b = static_cast<double>(2 * n + 3);
        const double next_term = term * (x * x) / (a * b);

        if (!std::isfinite(next_term) || !std::isfinite(sum + next_term)) {
            throw std::overflow_error("ERROR: sinh approximation overflowed.");
        }
        if (std::abs(next_term) < epsilon) {
            return sum;
        }

        sum += next_term;
        term = next_term;
    }

    throw std::runtime_error("ERROR: sinh Taylor series did not converge.");
}

bool read_finite(const char* prompt, double& value) {
    std::cout << prompt;
    if (!(std::cin >> value) || !std::isfinite(value)) {
        std::cerr << "ERROR: expected a finite number.\n";
        return false;
    }
    return true;
}

}  // namespace

int main() {
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);

    double angle = 0.0;
    double sin_epsilon = 0.0;
    if (!read_finite("Task 1 - angle in radians: ", angle) ||
        !read_finite("Task 1 - epsilon (epsilon > 0): ", sin_epsilon)) {
        return 1;
    }
    if (sin_epsilon <= 0.0) {
        std::cerr << "ERROR: epsilon must be greater than 0.\n";
        return 1;
    }

    double x = 0.0;
    double sinh_epsilon = 0.0;
    if (!read_finite("Task 2 - x: ", x) ||
        !read_finite("Task 2 - epsilon (1e-12 <= epsilon <= 1e-3): ",
                     sinh_epsilon)) {
        return 1;
    }
    if (sinh_epsilon < 1e-12 || sinh_epsilon > 1e-3) {
        std::cerr << "ERROR: task 2 epsilon must be in [1e-12, 1e-3].\n";
        return 1;
    }

    try {
        const double sine = sin_approx(angle, sin_epsilon);
        std::cout << "sin approximation = " << sine << '\n';

        const double approximation = sh_approx(x, sinh_epsilon);
        const double reference = std::sinh(x);
        if (!std::isfinite(reference)) {
            std::cerr << "ERROR: std::sinh(x) is outside the representable range.\n";
            return 1;
        }
        std::cout << "sinh approximation = " << approximation << '\n'
                  << "std::sinh(x) = " << reference << '\n'
                  << "absolute error = " << std::abs(approximation - reference)
                  << '\n';
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}