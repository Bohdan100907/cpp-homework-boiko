#include "Vector.h"
#include <iostream>

int main() {
    int firstSize;
    int secondSize;

    std::cout << "Vvedit kilkist elementiv pershoho vektora: ";
    std::cin >> firstSize;

    std::cout << "Vvedit kilkist elementiv druhoho vektora: ";
    std::cin >> secondSize;

    if (firstSize <= 0 || secondSize <= 0) {
        std::cout << "Rozmir vektora povynen buty dodatnym.\n";
        return 0;
    }

    Vector first(firstSize);
    Vector second(secondSize);

    std::cout << "Vvedit pershyi vektor:\n";
    std::cin >> first;

    std::cout << "Vvedit druhyi vektor:\n";
    std::cin >> second;

    double scalar;
    if (first.scalarProduct(second, scalar)) {
        std::cout << "Skalyarnyi dobutok: " << scalar << '\n';
    } else {
        std::cout << "Skalyarnyi dobutok nemozhlyvyi: rizni rozmiry.\n";
    }

    Vector product = first.multiply(second);
    std::cout << "Dobutok koefitsiientiv: " << product << '\n';

    if (!product.writeToFile("result.txt")) {
        std::cout << "Ne vdalosia vidkryty result.txt\n";
        return 1;
    }

    Vector fromFile(product.getSize());
    if (!fromFile.readFromFile("result.txt")) {
        std::cout << "Ne vdalosia prochytaty result.txt\n";
        return 1;
    }

    std::cout << "Prochytano z result.txt: " << fromFile << '\n';
    return 0;
}
