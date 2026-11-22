#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double sumOfVectorNorms(int n, int d) {
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        std::vector<double> vector(d);
        double squares = 0.0;

        for (int j = 0; j < d; ++j) {
            std::cin >> vector[j];
            squares += vector[j] * vector[j];
        }

        sum += std::sqrt(squares);
    }

    return sum;
}

int main() {
    int n;
    int d;

    std::cin >> n >> d;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << sumOfVectorNorms(n, d) << '\n';

    return 0;
}
