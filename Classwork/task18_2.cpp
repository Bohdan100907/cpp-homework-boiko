#include <iostream>
#include <stack>

template <typename T>
std::size_t readAndSum(T& result) {
    std::stack<T> numbers;
    T value;

    while (std::cin >> value && value != 0) {
        numbers.push(value);
    }

    result = T{};
    std::size_t count = numbers.size();

    while (!numbers.empty()) {
        result = result + numbers.top();
        numbers.pop();
    }

    return count;
}

int main() {
    int integerSum;
    std::size_t integerCount = readAndSum(integerSum);
    std::cout << integerCount << ' ' << integerSum << '\n';

    double doubleSum;
    std::cin.clear();
    std::cout << "Vvedit double chysla: ";
    std::size_t doubleCount = readAndSum(doubleSum);
    std::cout << doubleCount << ' ' << doubleSum << '\n';

    return 0;
}
