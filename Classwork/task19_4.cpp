#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    int m;

    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::sort(matrix.begin(), matrix.end(), [](const std::vector<int>& first,
                                               const std::vector<int>& second) {
        int firstMaximum = *std::max_element(first.begin(), first.end());
        int secondMaximum = *std::max_element(second.begin(), second.end());
        return firstMaximum > secondMaximum;
    });

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j];
            if (j + 1 < m) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}
