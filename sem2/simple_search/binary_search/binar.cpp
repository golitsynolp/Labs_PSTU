#include <iostream>
#include <ctime>

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

int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key) return mid;

        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
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

    int result = binarySearch(nums, size, value);

    if (result != -1)
        cout << "Число найдено. Индекс: " << result << endl;
    else
        cout << "Число не найдено" << endl;
}