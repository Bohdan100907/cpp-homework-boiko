#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>

class Point {
private:
    double x;
    double y;
    static int count;

public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {
        ++count;
    }

    Point(const Point& other) : x(other.x), y(other.y) {
        ++count;
    }

    ~Point() {
        --count;
    }

    void input() {
        std::cout << "Enter coordinates x y: ";
        std::cin >> x >> y;
    }

    void print(int number) const {
        std::cout << "Vertex " << number << ": (" << x << ", " << y << ")\n";
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    static int getCount() {
        return count;
    }
};

int Point::count = 0;

bool wantsToContinue() {
    std::string answer;
    std::cout << "Enter vertex? (Yes/No): ";
    std::cin >> answer;

    for (char& symbol : answer) {
        symbol = static_cast<char>(std::tolower(
            static_cast<unsigned char>(symbol)));
    }

    return answer == "yes" || answer == "y" ||
           answer == "tak" || answer == "1";
}

int main() {
    std::vector<Point> vertices;

    while (wantsToContinue()) {
        Point point;
        point.input();
        vertices.push_back(point);
        point.print(static_cast<int>(vertices.size()));
    }

    std::cout << "Number of vertices: " << vertices.size() << '\n';

    if (vertices.empty()) {
        std::cout << "Perimeter: 0\n";
        return 0;
    }

    double perimeter = 0.0;
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        const Point& first = vertices[i];
        const Point& second = vertices[(i + 1) % vertices.size()];

        const double dx = second.getX() - first.getX();
        const double dy = second.getY() - first.getY();
        perimeter += std::sqrt(dx * dx + dy * dy);
    }

    std::cout << "Perimeter: " << perimeter << '\n';
    std::cout << "Current Point objects: " << Point::getCount() << '\n';
    return 0;
}