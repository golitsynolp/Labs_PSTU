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

void mergeParts(int arr[], int left, int mid, int right) {
    int temp[N];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int p = left; p <= right; p++) arr[p] = temp[p];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        mergeParts(arr, left, mid, right);
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

    mergeSort(arr, 0, N - 1);

    cout << "Массив после сортировки подсчетом:" << endl;
    showArray(arr, N);
}