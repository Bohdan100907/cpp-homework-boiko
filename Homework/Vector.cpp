#include "Vector.h"

#include <cstring>
#include <stdexcept>

Vector::Vector(int size) : elements(nullptr), size(size) {
    if (size < 0) {
        throw std::invalid_argument("Rozmir ne moze buty vid'emnym");
    }

    if (size > 0) {
        elements = new double[size]{};
    }
}

Vector::Vector(const Vector& other)
    : elements(nullptr), size(other.size) {
    if (size > 0) {
        elements = new double[size];
        std::memcpy(elements, other.elements,
                    static_cast<std::size_t>(size) * sizeof(double));
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        double* newElements =
            other.size > 0 ? new double[other.size] : nullptr;

        if (newElements != nullptr) {
            std::memcpy(newElements, other.elements,
                        static_cast<std::size_t>(other.size) *
                            sizeof(double));
        }

        delete[] elements;
        elements = newElements;
        size = other.size;
    }
    return *this;
}

Vector::~Vector() {
    delete[] elements;
}

int Vector::getSize() const {
    return size;
}

double Vector::getElement(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Nomer elementa za mezhamy vektora");
    }
    return elements[index];
}

void Vector::setElement(int index, double value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Nomer elementa za mezhamy vektora");
    }
    elements[index] = value;
}

double& Vector::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Nomer elementa za mezhamy vektora");
    }
    return elements[index];
}

const double& Vector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Nomer elementa za mezhamy vektora");
    }
    return elements[index];
}

bool Vector::scalarProduct(const Vector& other, double& result) const {
    if (size != other.size) {
        return false;
    }

    result = 0.0;
    for (int i = 0; i < size; ++i) {
        result += elements[i] * other.elements[i];
    }
    return true;
}

Vector Vector::multiply(const Vector& other) const {
    if (size == 0 || other.size == 0) {
        return Vector();
    }

    Vector result(size + other.size - 1);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            result.elements[i + j] += elements[i] * other.elements[j];
        }
    }
    return result;
}

bool Vector::writeToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }

    file << size << '\n';
    for (int i = 0; i < size; ++i) {
        file << elements[i];
        if (i + 1 < size) {
            file << ' ';
        }
    }
    return static_cast<bool>(file);
}

bool Vector::readFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }

    int newSize;
    file >> newSize;
    if (!file || newSize < 0) {
        return false;
    }

    Vector temporary(newSize);
    for (int i = 0; i < newSize; ++i) {
        file >> temporary.elements[i];
    }

    if (!file) {
        return false;
    }

    *this = temporary;
    return true;
}

std::istream& operator>>(std::istream& input, Vector& vector) {
    for (int i = 0; i < vector.size; ++i) {
        input >> vector.elements[i];
    }
    return input;
}

std::ostream& operator<<(std::ostream& output, const Vector& vector) {
    for (int i = 0; i < vector.size; ++i) {
        if (i > 0) {
            output << ' ';
        }
        output << vector.elements[i];
    }
    return output;
}
