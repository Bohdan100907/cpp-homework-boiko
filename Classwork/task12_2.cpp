#include <iostream>
#include <vector>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<unsigned long long> numbers(n);
    unsigned long long sum = 0;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> numbers[i];
        sum += numbers[i];
    }

    cout << sum << '\n';

    return 0;
}