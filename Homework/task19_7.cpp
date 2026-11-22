#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstddef>

struct Cell {
    int x;
    int y;
    long double distance;
};

struct GreaterDistance {
    bool operator()(const Cell& left, const Cell& right) const {
        if (left.distance != right.distance) {
            return left.distance > right.distance;
        }
        if (left.y != right.y) {
            return left.y > right.y;
        }
        return left.x > right.x;
    }
};

int main() {
    long double cx;
    long double cy;
    long double radius;

    std::cout << "Vvedit centralni koordynaty ta radius: ";
    std::cin >> cx >> cy >> radius;

    if (!std::cin || radius <= 0) {
        std::cout << "Nevirni vkhidni dani" << std::endl;
        return 1;
    }

    std::priority_queue<Cell, std::vector<Cell>, GreaterDistance> cells;

    int left = static_cast<int>(std::floor(cx - radius));
    int right = static_cast<int>(std::ceil(cx + radius));
    int bottom = static_cast<int>(std::floor(cy - radius));
    int top = static_cast<int>(std::ceil(cy + radius));

    for (int x = left; x <= right - 1; ++x) {
        for (int y = bottom; y <= top - 1; ++y) {
            const long double cornersX[4] = {
                static_cast<long double>(x),
                static_cast<long double>(x) + 1.0L,
                static_cast<long double>(x),
                static_cast<long double>(x) + 1.0L
            };
            const long double cornersY[4] = {
                static_cast<long double>(y),
                static_cast<long double>(y),
                static_cast<long double>(y) + 1.0L,
                static_cast<long double>(y) + 1.0L
            };

            bool inside = true;
            for (std::size_t i = 0; i < 4; ++i) {
                long double dx = cornersX[i] - cx;
                long double dy = cornersY[i] - cy;
                if (dx * dx + dy * dy > radius * radius) {
                    inside = false;
                    break;
                }
            }

            if (inside) {
                long double dx = (x + 0.5L) - cx;
                long double dy = (y + 0.5L) - cy;
                cells.push({x, y, dx * dx + dy * dy});
            }
        }
    }

    std::ofstream output("cells.txt");
    if (!output) {
        std::cout << "Ne vdalosia vidkryty fail cells.txt" << std::endl;
        return 1;
    }

    while (!cells.empty()) {
        const Cell cell = cells.top();
        cells.pop();
        output << cell.x << ' ' << cell.y << '\n';
    }

    return 0;
}
