#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    double x;
    double y;

    cin >> x >> y;

    const double result = pow(x, y);

    cout << fixed << setprecision(6) << result << '\n';
    cout << scientific << setprecision(6) << result << '\n';

    return 0;
}