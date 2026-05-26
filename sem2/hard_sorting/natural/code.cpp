#include <iostream>
#include <fstream>

using namespace std;

const int N = 10;

int divideFile(const char* inputName, const char* firstName, const char* secondName) {
    ifstream input(inputName);
    ofstream first(firstName);
    ofstream second(secondName);

    if (!input.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int last, now;
    int count = 1;
    bool inFirst = true;

    input >> last;
    first << last << " ";

    while (input >> now) {
        if (now < last) {
            count++;
            inFirst = !inFirst;
        }

        if (inFirst) first << now << " ";
        else second << now << " ";

        last = now;
    }

    input.close();
    first.close();
    second.close();

    return count;
}

void mergeFile(const char* firstName, const char* secondName, const char* resultName) {
    ifstream first(firstName);
    ifstream second(secondName);
    ofstream result(resultName);

    int a, b;
    int checkA = first >> a ? 1 : 0;
    int checkB = second >> b ? 1 : 0;

    while (checkA && checkB) {
        if (a <= b) {
            result << a << " ";
            checkA = first >> a ? 1 : 0;
        }
        else {
            result << b << " ";
            checkB = second >> b ? 1 : 0;
        }
    }

    while (checkA) {
        result << a << " ";
        checkA = first >> a ? 1 : 0;
    }

    while (checkB) {
        result << b << " ";
        checkB = second >> b ? 1 : 0;
    }

    first.close();
    second.close();
    result.close();
}

void naturalSort(const char* inputName, const char* outputName) {
    const char* partOne = "part1.txt";
    const char* partTwo = "part2.txt";
    const char* temp = "temp.txt";

    int series = divideFile(inputName, partOne, partTwo);

    while (series > 1) {
        mergeFile(partOne, partTwo, temp);
        series = divideFile(temp, partOne, partTwo);
    }

    ifstream input(partOne);
    ofstream output(outputName);

    int number;

    while (input >> number) output << number << " ";

    input.close();
    output.close();

    remove(partOne);
    remove(partTwo);
    remove(temp);
}

void showFile(const char* fileName) {
    ifstream file(fileName);

    int number;

    while (file >> number) cout << number << " ";

    cout << endl;

    file.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    int arr[N] = { 41, 8, 15, 24, 2, 1, 12, 7 ,23, 1 };

    ofstream input("input.txt");

    for (int i = 0; i < N; i++)
        input << arr[i] << " ";

    input.close();

    cout << "Исходные данные:" << endl;
    showFile("input.txt");

    naturalSort("input.txt", "output.txt");

    cout << "Отсортированные данные:" << endl;
    showFile("output.txt");
}