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

int lomutoPart(int arr[], int left, int right) {
    int pivot = arr[right];
    int border = left - 1;

    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            border++;

            int temp = arr[border];
            arr[border] = arr[i];
            arr[i] = temp;
        }
    }

    int temp = arr[border + 1];
    arr[border + 1] = arr[right];
    arr[right] = temp;

    return border + 1;
}

void lomutoSort(int arr[], int left, int right) {
    if (left < right) {
        int place = lomutoPart(arr, left, right);

        lomutoSort(arr, left, place - 1);
        lomutoSort(arr, place + 1, right);
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

    lomutoSort(arr, 0, N - 1);

    cout << "Массив после сортировки подсчетом:" << endl;
    showArray(arr, N);
}