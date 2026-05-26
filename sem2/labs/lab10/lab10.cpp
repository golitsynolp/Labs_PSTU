#include <iostream>

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");

    int size, delNum, addCount, place;

    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        cout << "Размер массива должен быть положительным" << endl;
    }

    int* firstArr = new int[size];

    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < size; i++) cin >> firstArr[i];

    cout << "Введите номер удаляемого элемента: ";
    cin >> delNum;

    if (delNum < 1) delNum = 1;
    if (delNum > size) delNum = size;

    int shortSize = size - 1;
    int* shortArr = new int[shortSize];
    int pos = 0;

    for (int i = 0; i < size; i++) {
        if (i != delNum - 1) shortArr[pos++] = firstArr[i];
    }

    delete[] firstArr;

    cout << "Массив после удаления:" << endl;
    for (int i = 0; i < shortSize; i++) cout << shortArr[i] << " ";
    cout << endl;

    cout << "Введите количество добавляемых элементов: ";
    cin >> addCount;

    if (addCount < 0) addCount = 0;

    cout << "Введите номер, с которого нужно добавить элементы: ";
    cin >> place;

    if (place < 1) place = 1;
    if (place > shortSize + 1) place = shortSize + 1;

    int resultSize = shortSize + addCount;
    int* resultArr = new int[resultSize];

    for (int i = 0; i < place - 1; i++) resultArr[i] = shortArr[i];

    if (addCount > 0) cout << "Введите добавляемые элементы:" << endl;
    for (int i = 0; i < addCount; i++) cin >> resultArr[place - 1 + i];
    for (int i = place - 1; i < shortSize; i++) resultArr[i + addCount] = shortArr[i];

    delete[] shortArr;

    cout << "Итоговый массив:" << endl;
    for (int i = 0; i < resultSize; i++) cout << resultArr[i] << " ";
    cout << endl;

    delete[] resultArr;
}
