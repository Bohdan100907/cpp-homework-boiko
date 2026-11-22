#pragma once

#include <fstream>
#include <iostream>

class Vector {
private:
    double* elements;
    int size;

public:
    explicit Vector(int size = 0);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    int getSize() const;
    double getElement(int index) const;
    void setElement(int index, double value);

    double& operator[](int index);
    const double& operator[](int index) const;

    bool scalarProduct(const Vector& other, double& result) const;
    Vector multiply(const Vector& other) const;

    bool writeToFile(const char* filename) const;
    bool readFromFile(const char* filename);

    friend std::istream& operator>>(std::istream& input, Vector& vector);
    friend std::ostream& operator<<(std::ostream& output,
                                    const Vector& vector);
};
