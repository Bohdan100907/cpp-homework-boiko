#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    cout << string(n * 8 - 1, '+') << '\n';

    for (int i = 1; i <= n; ++i)
    {
        cout << setw(8) << i;
    }
    cout << '\n';

    cout << string(n * 8 - 1, '+') << '\n';

    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; ++i)
    {
        double root = sqrt(static_cast<double>(i));
        int integerRoot = static_cast<int>(root);

        if (integerRoot * integerRoot == i)
        {
            cout << setw(8) << integerRoot;
        }
        else
        {
            cout << setw(8) << root;
        }
    }
    cout << '\n';

    cout << string(n * 8 - 1, '+') << '\n';

    return 0;
}