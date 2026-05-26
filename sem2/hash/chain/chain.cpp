#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 150;

struct Data {
    string fio;
    string address;
    int passport;
};

struct Node {
    Data data;
    Node* next;
};

int getHash(int key, int m) {
    double A = 0.618033;
    double x = key * A;
    x = x - int(x);
    return int(m * x);
}

void addToChain(Node* table[], int m, Data item) {
    int index = getHash(item.passport, m);

    Node* temp = new Node;
    temp->data = item;
    temp->next = table[index];
    table[index] = temp;
}

void clearTable(Node* table[], int m) {
    for (int i = 0; i < m; i++) {
        while (table[i] != nullptr) {
            Node* temp = table[i];
            table[i] = table[i]->next;
            delete temp;
        }
    }
}

void makeTable(Node* table[], int m, Data arr[], int n) {
    clearTable(table, m);
    for (int i = 0; i < n; i++) addToChain(table, m, arr[i]);
}

void searchByPassport(Node* table[], int m) {
    int key;
    cout << "Введите ключ поиска - номер паспорта: ";
    cin >> key;
    int index = getHash(key, m);
    Node* temp = table[index];
    while (temp != nullptr) {
        if (temp->data.passport == key) {
            cout << "Запись найдена" << endl;
            cout << "ФИО: " << temp->data.fio << endl;
            cout << "Адрес: " << temp->data.address << endl;
            cout << "Паспорт: " << temp->data.passport << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Запись не найдена" << endl;
}

void printTable(Node* table[], int m) {
    for (int i = 0; i < m; i++) {
        cout << i << ": ";
        Node* temp = table[i];
        while (temp != nullptr) {
            cout << "[" << temp->data.fio << ", " << temp->data.passport << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

void createArray(Data arr[], int& n) {
    string fio[10] = { "Иванов Иван", "Петров Петр", "Сидоров Сергей", "Козлов Кирилл", "Орлов Олег", "Миронов Максим", "Федоров Федор", "Смирнов Семен", "Волков Виктор", "Зайцев Захар" };
    string address[10] = { "Ленина 1", "Мира 10", "Советская 7", "Пушкина 4", "Гагарина 8", "Кирова 15", "Победы 3", "Лесная 6", "Новая 12", "Школьная 9" };

    n = 100;
    for (int i = 0; i < n; i++) {
        arr[i].fio = fio[rand() % 10];
        arr[i].address = address[rand() % 10];
        arr[i].passport = 100000 + rand() % 900000;
    }
    cout << "Массив из 100 записей создан" << endl;
}

void saveFile(Data arr[], int n) {
    ofstream file("data.txt");
    for (int i = 0; i < n; i++)
        file << arr[i].fio << ";" << arr[i].address << ";" << arr[i].passport << endl;

    file.close();
    cout << "Массив сохранен в файл" << endl;
}

void loadFile(Data arr[], int& n) {
    ifstream file("data.txt");

    if (!file.is_open()) {
        cout << "Файл не найден" << endl;
        return;
    }
    n = 0;
    while (getline(file, arr[n].fio, ';')) {
        getline(file, arr[n].address, ';');
        file >> arr[n].passport;
        file.ignore();
        n++;
    }

    file.close();
    cout << "Массив загружен из файла" << endl;
}

void addRecord(Data arr[], int& n) {
    if (n >= MAX) {
        cout << "Массив заполнен" << endl;
        return;
    }

    cin.ignore();

    cout << "Введите ФИО: ";
    getline(cin, arr[n].fio);

    cout << "Введите адрес: ";
    getline(cin, arr[n].address);

    cout << "Введите номер паспорта: ";
    cin >> arr[n].passport;

    n++;

    cout << "Запись добавлена" << endl;
}

void deleteRecord(Data arr[], int& n) {
    int key;
    int index = -1;

    cout << "Введите номер паспорта для удаления: ";
    cin >> key;

    for (int i = 0; i < n; i++)
        if (arr[i].passport == key) index = i;

    if (index == -1) {
        cout << "Запись не найдена" << endl;
        return;
    }

    for (int i = index; i < n - 1; i++)
        arr[i] = arr[i + 1];

    n--;

    cout << "Запись удалена" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    Data arr[MAX];
    int n = 0;
    int choice;

    const int M = 40;
    Node* table[M];

    for (int i = 0; i < M; i++) table[i] = nullptr;

    do {
        cout << endl<< "1. Создать массив" << endl;
        cout << "2. Сохранить в файл" << endl;
        cout << "3. Загрузить из файла" << endl;
        cout << "4. Добавить запись" << endl;
        cout << "5. Удалить запись" << endl;
        cout << "6. Построить и вывести хэш-таблицу" << endl;
        cout << "7. Найти по номеру паспорта" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        if (choice == 1) createArray(arr, n);

        if (choice == 2) saveFile(arr, n);

        if (choice == 3) loadFile(arr, n);

        if (choice == 4) addRecord(arr, n);

        if (choice == 5) deleteRecord(arr, n);

        if (choice == 6) {
            makeTable(table, M, arr, n);
            printTable(table, M);
        }

        if (choice == 7) {
            makeTable(table, M, arr, n);
            searchByPassport(table, M);
        }

    } while (choice != 0);
    clearTable(table, M);
}