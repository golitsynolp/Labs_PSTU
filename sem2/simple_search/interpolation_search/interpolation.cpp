#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int interpol(int mas[], int kol, int x) {
    int levo = 0;
    int pravo = kol - 1;

    while (levo <= pravo && x >= mas[levo] && x <= mas[pravo]) {
        if (mas[levo] == mas[pravo]) {
            if (mas[levo] == x) return levo;
            return -1;
        }

        int mesto = levo + (x - mas[levo]) * (pravo - levo) / (mas[pravo] - mas[levo]);

        if (mas[mesto] == x) return mesto;
        if (mas[mesto] < x) levo = mesto + 1;
        else pravo = mesto - 1;
    }

    return -1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    const int size = 10;
    int nums[size];
    int value;

    cout << "Массив:" << endl;

    for (int i = 0; i < size; i++) {
        nums[i] = rand() % 50;
        cout << nums[i] << " ";
    }

    cout << endl << endl;

    sortArray(nums, size);

    cout << "Отсортированный массив:" << endl;

    for (int i = 0; i < size; i++)
        cout << nums[i] << " ";

    cout << endl << endl;

    cout << "Введите число для поиска: ";
    cin >> value;

    int result = interpol(nums, size, value);

    if (result != -1)
        cout << "Число найдено. Индекс: " << result << endl;
    else
        cout << "Число не найдено" << endl;
}
