#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

void createStudentsFile(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file) {
        std::cout << "Ne vdalosia vidkryty fail.\n";
        std::exit(1);
    }

    int count;
    std::cout << "Vvedit kilkist studentiv: ";
    std::cin >> count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < count; ++i) {
        std::string surname;
        int course;
        std::string grades;

        std::cout << "Prizvyshche kurs otsinky: ";
        std::getline(std::cin, grades);

        std::istringstream input(grades);
        input >> surname >> course;
        if (!input) {
            std::cout << "Nevirnyi format zapysu.\n";
            std::exit(1);
        }

        file << surname << ' ' << course;
        int grade;
        while (input >> grade) {
            file << ' ' << grade;
        }
        file << '\n';
    }
}

std::string findBestStudent(const std::string& fileName,
                            double& average) {
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Ne vdalosia vidkryty fail.\n";
        std::exit(1);
    }

    std::string result;
    std::string surname;
    int course;
    std::string line;
    average = -1.0;

    while (std::getline(file, line)) {
        std::istringstream input(line);
        input >> surname >> course;

        int grade;
        int sum = 0;
        int count = 0;

        while (input >> grade) {
            sum += grade;
            ++count;
        }

        if (count > 0) {
            double currentAverage =
                static_cast<double>(sum) / count;
            if (currentAverage > average) {
                average = currentAverage;
                result = surname;
            }
        }
    }

    return result;
}

int main() {
    const std::string fileName = "students.txt";
    createStudentsFile(fileName);

    double average;
    std::string surname =
        findBestStudent(fileName, average);

    if (surname.empty()) {
        std::cout << "Nemae studentiv z otsinkamy.\n";
    } else {
        std::cout << "Najkrashchyi serednii bal: "
                  << surname << " ("
                  << std::fixed << std::setprecision(2)
                  << average << ")\n";
    }

    return 0;
}