#include <iostream>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::queue<double> arrivals;
    for (int i = 0; i < n; ++i) {
        double time;
        std::cin >> time;
        arrivals.push(time);
    }

    double freeTime = 0.0;
    double greatestWaiting = -1.0;
    int greatestCustomer = 0;

    for (int i = 1; i <= n; ++i) {
        double arrival = arrivals.front();
        arrivals.pop();
        double waiting = std::max(0.0, freeTime - arrival);
        freeTime = std::max(arrival, freeTime) + 1;

        std::cout << waiting;
        if (i < n) std::cout << ' ';

        if (waiting > greatestWaiting) {
            greatestWaiting = waiting;
            greatestCustomer = i;
        }
    }

    if (n > 0) std::cout << '\n' << greatestCustomer << '\n';
    return 0;
}
