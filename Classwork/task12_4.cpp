#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int* m = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> m[i];
    }

    ifstream input("input.txt");
    ofstream output("output.txt");

    output << fixed << setprecision(6);
    for (int i = 0; i < n; ++i)
    {
        double x;
        input >> x;
        output << pow(x, m[i]) << '\n';
    }

    input.close();
    output.close();
    delete[] m;

    return 0;
}