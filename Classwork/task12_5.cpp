#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    output << fixed << setprecision(3);

    unsigned long long number;
    while (input >> number)
    {
        output << sqrt(static_cast<long double>(number)) << '\n';
    }

    input.close();
    output.close();

    return 0;
}