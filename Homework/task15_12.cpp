#include <iostream>
#include <fstream>
using namespace std;

class Vector
{
private:
    double* elements;
    int size;

public:
    // Конструктор
    Vector(int n)
    {
        size = n;
        elements = new double[size];

        for (int i = 0; i < size; i++)
            elements[i] = 0;
    }

    // Конструктор копіювання
    Vector(const Vector& other)
    {
        size = other.size;
        elements = new double[size];

        for (int i = 0; i < size; i++)
            elements[i] = other.elements[i];
    }

    // Деструктор
    ~Vector()
    {
        delete[] elements;
    }

    void setElement(int index, double value)
    {
        if (index >= 0 && index < size)
            elements[index] = value;
    }

    double getElement(int index)
    {
        if (index >= 0 && index < size)
            return elements[index];

        return 0;
    }

    int getSize()
    {
        return size;
    }

    // Скалярний добуток
    bool scalarProduct(const Vector& other, double& result)
    {
        if (size != other.size)
            return false;

        result = 0;

        for (int i = 0; i < size; i++)
            result += elements[i] * other.elements[i];

        return true;
    }

    // Добуток векторів-коефіцієнтів поліномів
    Vector multiply(const Vector& other)
    {
        Vector result(size + other.size - 1);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < other.size; j++)
            {
                result.elements[i + j] += elements[i] * other.elements[j];
            }
        }

        return result;
    }

    void writeToFile(const char* filename)
    {
        ofstream file(filename);

        if (!file)
        {
            cout << "Не вдалося відкрити файл!" << endl;
            return;
        }

        for (int i = 0; i < size; i++)
            file << elements[i] << " ";

        file.close();
    }
};

int main()
{
    int m, n;

    cout << "Введіть степінь першого полінома m: ";
    cin >> m;

    cout << "Введіть степінь другого полінома n: ";
    cin >> n;

    if (m < 0 || n < 0)
    {
        cout << "Степені не можуть бути від'ємними!" << endl;
        return 0;
    }

    Vector a(m + 1);
    Vector b(n + 1);

    cout << "Введіть коефіцієнти першого вектора:" << endl;
    for (int i = 0; i <= m; i++)
    {
        double x;
        cin >> x;
        a.setElement(i, x);
    }

    cout << "Введіть коефіцієнти другого вектора:" << endl;
    for (int i = 0; i <= n; i++)
    {
        double x;
        cin >> x;
        b.setElement(i, x);
    }

    double scalar;

    if (a.scalarProduct(b, scalar))
        cout << "Скалярний добуток: " << scalar << endl;
    else
        cout << "Скалярний добуток неможливий: розміри векторів різні." << endl;

    Vector result = a.multiply(b);
    result.writeToFile("result.txt");

    cout << "Вектор добутку записано у файл result.txt" << endl;

    return 0;
}
