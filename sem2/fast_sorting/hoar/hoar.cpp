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

int hoarePart(int arr[], int left, int right) {
    int pivot = arr[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) return j;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void hoareSort(int arr[], int left, int right) {
    if (left < right) {
        int border = hoarePart(arr, left, right);

        hoareSort(arr, left, border);
        hoareSort(arr, border + 1, right);
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

    hoareSort(arr, 0, N - 1);

    cout << "Массив после методом Хоара:" << endl;
    showArray(arr, N);
}