#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

static double *readNumbers(const string &inputFile, int &count) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Unable to open input file: " << inputFile << '\n';
        count = 0;
        return nullptr;
    }

    string content;
    string line;
    while (getline(input, line)) {
        content += line + '\n';
    }

    double *values = nullptr;
    count = 0;
    string token;
    for (char ch : content) {
        if (ch == ',' || ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            if (!token.empty()) {
                double value = 0.0;
                istringstream iss(token);
                iss >> value;
                if (!iss.fail()) {
                    double *tmp = new double[count + 1];
                    for (int i = 0; i < count; ++i) {
                        tmp[i] = values[i];
                    }
                    tmp[count] = value;
                    delete[] values;
                    values = tmp;
                    ++count;
                }
                token.clear();
            }
            continue;
        }

        token += ch;
    }

    if (!token.empty()) {
        double value = 0.0;
        istringstream iss(token);
        iss >> value;
        if (!iss.fail()) {
            double *tmp = new double[count + 1];
            for (int i = 0; i < count; ++i) {
                tmp[i] = values[i];
            }
            tmp[count] = value;
            delete[] values;
            values = tmp;
            ++count;
        }
    }

    return values;
}

static void writeScientificResults(const string &outputFile, const double *values, int count) {
    ofstream output(outputFile);
    if (!output) {
        cerr << "Unable to open output file: " << outputFile << '\n';
        return;
    }

    output << scientific << setprecision(10);
    for (int i = 0; i < count; ++i) {
        const double value = values[i];
        if (value < -1.0 || value > 1.0) {
            continue;
        }

        output << asin(value) << '\n';
    }
}

int main() {
    const fs::path baseDir = fs::path(__FILE__).parent_path();
    const fs::path inputFile = baseDir / "input.txt";
    const fs::path outputFile = baseDir / "output.txt";

    ofstream sampleInput(inputFile);
    if (!sampleInput) {
        cerr << "Unable to create sample input file.\n";
        return 1;
    }
    sampleInput << "0.5, 0.9, -0.2, 1.2, 0.0, 2.0, -1.0, 0.75\n";
    sampleInput.close();

    int count = 0;
    double *values = readNumbers(inputFile.string(), count);
    if (values == nullptr || count == 0) {
        cerr << "No valid numbers found in input file.\n";
        delete[] values;
        return 1;
    }

    writeScientificResults(outputFile.string(), values, count);

    cout << "Processed numbers: " << count << '\n';
    cout << "Results saved to: " << outputFile.string() << '\n';

    delete[] values;
    return 0;
}
