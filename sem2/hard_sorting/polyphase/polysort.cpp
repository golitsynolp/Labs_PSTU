#include <iostream>
#include <fstream>

using namespace std;

const int N = 10;

void sortSmallArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minInd = i;

        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[minInd]) minInd = j;

        int temp = arr[i];
        arr[i] = arr[minInd];
        arr[minInd] = temp;
    }
}

void makeRuns(const char* inputName, const char* firstName, const char* secondName) {
    ifstream input(inputName);
    ofstream first(firstName);
    ofstream second(secondName);

    int block[2];
    int count = 0;
    int number;
    bool toFirst = true;

    while (input >> number) {
        block[count] = number;
        count++;

        if (count == 2) {
            sortSmallArray(block, count);

            if (toFirst) {
                for (int i = 0; i < count; i++)
                    first << block[i] << " ";
            }
            else {
                for (int i = 0; i < count; i++)
                    second << block[i] << " ";
            }

            toFirst = !toFirst;
            count = 0;
        }
    }

    if (count > 0) {
        sortSmallArray(block, count);

        if (toFirst) {
            for (int i = 0; i < count; i++)
                first << block[i] << " ";
        }
        else {
            for (int i = 0; i < count; i++)
                second << block[i] << " ";
        }
    }

    input.close();
    first.close();
    second.close();
}

void mergeParts(const char* firstName, const char* secondName, const char* outputName) {
    ifstream first(firstName);
    ifstream second(secondName);
    ofstream output(outputName);

    int a, b;
    int checkA = first >> a ? 1 : 0;
    int checkB = second >> b ? 1 : 0;

    while (checkA && checkB) {
        if (a <= b) {
            output << a << " ";
            checkA = first >> a ? 1 : 0;
        }
        else {
            output << b << " ";
            checkB = second >> b ? 1 : 0;
        }
    }

    while (checkA) {
        output << a << " ";
        checkA = first >> a ? 1 : 0;
    }

    while (checkB) {
        output << b << " ";
        checkB = second >> b ? 1 : 0;
    }

    first.close();
    second.close();
    output.close();
}

void polyphaseSort(const char* inputName, const char* outputName) {
    const char* firstFile = "file1.txt";
    const char* secondFile = "file2.txt";

    makeRuns(inputName, firstFile, secondFile);
    mergeParts(firstFile, secondFile, outputName);

    remove(firstFile);
    remove(secondFile);
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

    polyphaseSort("input.txt", "output.txt");

    cout << "Отсортированные данные:" << endl;
    showFile("output.txt");
}