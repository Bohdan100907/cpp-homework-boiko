#include <initializer_list>
#include <iostream>
#include <cstddef>
#include <vector>


template <typename T>
class Array {
private:
    std::vector<T> data;

public:
    Array() = default;

    explicit Array(std::size_t size) : data(size) {}

    Array(std::initializer_list<T> values) : data(values) {}

    std::size_t size() const {
        return data.size();
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    void insertionSort() {
        for (std::size_t i = 1; i < data.size(); ++i) {
            T key = data[i];
            std::size_t j = i;

            while (j > 0 && data[j - 1] > key) {
                data[j] = data[j - 1];
                --j;
            }

            data[j] = key;
        }
    }

    void print() const {
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << (i + 1 == data.size() ? '\n' : ' ');
        }
    }
};

int main() {
    std::size_t n;
    std::cin >> n;

    Array<double> array(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    array.insertionSort();
    array.print();

    return 0;
}
