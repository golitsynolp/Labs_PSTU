#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 15;

void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void countingSort(int arr[], int size) {
    int maxNum = arr[0];

    for (int i = 1; i < size; i++)
        if (arr[i] > maxNum) maxNum = arr[i];

    int* amount = new int[maxNum + 1];

    for (int i = 0; i <= maxNum; i++)
        amount[i] = 0;

    for (int i = 0; i < size; i++)
        amount[arr[i]]++;

    int index = 0;

    for (int i = 0; i <= maxNum; i++) {
        while (amount[i] > 0) {
            arr[index] = i;
            index++;
            amount[i]--;
        }
    }

    delete[] amount;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int arr[N];

    cout << "Исходный массив:" << endl;

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }

    cout << endl;

    countingSort(arr, N);

    cout << "Массив после сортировки подсчетом:" << endl;
    showArray(arr, N);
}