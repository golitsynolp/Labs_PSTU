#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 15;
const int K = 4;

void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void bucketSort(int arr[], int size) {
    int parts[K][N];
    int count[K];

    for (int i = 0; i < K; i++) count[i] = 0;

    for (int i = 0; i < size; i++) {
        int place = arr[i] / 25;

        if (place >= K) place = K - 1;

        parts[place][count[place]] = arr[i];
        count[place]++;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < count[i] - 1; j++) {
            int minInd = j;

            for (int p = j + 1; p < count[i]; p++)
                if (parts[i][p] < parts[i][minInd]) minInd = p;

            int temp = parts[i][j];
            parts[i][j] = parts[i][minInd];
            parts[i][minInd] = temp;
        }
    }

    int pos = 0;

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[pos] = parts[i][j];
            pos++;
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

    bucketSort(arr, N);

    cout << "Массив после блочной сортировки:" << endl;
    showArray(arr, N);
}