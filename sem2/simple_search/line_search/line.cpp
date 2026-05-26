#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int lineSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++)
        if (arr[i] == key) return i;

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

    cout << "Введите число для поиска: ";
    cin >> value;

    int result = lineSearch(nums, size, value);

    if (result != -1)
        cout << "Число найдено. Индекс: " << result << endl;
    else
        cout << "Число не найдено" << endl;
}
