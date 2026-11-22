#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>
#include <vector>

const std::size_t BLACK_BOX_CAPACITY = 100;

template <typename T>
class BlackBox {
private:
    std::vector<T> elements;

public:
    BlackBox() : elements() {
        elements.reserve(BLACK_BOX_CAPACITY);
    }

    template <typename N>
    BlackBox(const T* array, N size) : elements() {
        elements.reserve(BLACK_BOX_CAPACITY);
        if (array == nullptr) {
            return;
        }

        std::size_t count = static_cast<std::size_t>(size);
        if (count > BLACK_BOX_CAPACITY) {
            count = BLACK_BOX_CAPACITY;
        }

        elements.insert(elements.end(), array, array + count);
    }

    BlackBox(std::initializer_list<T> values) : elements() {
        elements.reserve(BLACK_BOX_CAPACITY);
        std::size_t count = values.size();
        if (count > BLACK_BOX_CAPACITY) {
            count = BLACK_BOX_CAPACITY;
        }

        auto it = values.begin();
        elements.insert(elements.end(), it, it + count);
    }

    bool push(const T& value) {
        if (elements.size() >= BLACK_BOX_CAPACITY) {
            return false;
        }

        elements.push_back(value);
        return true;
    }

    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("BlackBox is empty");
        }

        std::size_t index = static_cast<std::size_t>(std::rand()) % elements.size();
        T result = elements[index];
        elements[index] = elements.back();
        elements.pop_back();
        return result;
    }

    void chop() {
        elements.clear();
    }

    std::size_t size() const {
        return elements.size();
    }

    bool empty() const {
        return elements.empty();
    }
};
