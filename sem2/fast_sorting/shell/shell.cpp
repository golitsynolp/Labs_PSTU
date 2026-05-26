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

void shellSort(int arr[], int size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; i++) {
            int value = arr[i];
            int j = i;

            while (j >= step && arr[j - step] > value) {
                arr[j] = arr[j - step];
                j -= step;
            }

            arr[j] = value;
        }
    }
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

    shellSort(arr, N);

    cout << "Массив после методом Шелла:" << endl;
    showArray(arr, N);
}