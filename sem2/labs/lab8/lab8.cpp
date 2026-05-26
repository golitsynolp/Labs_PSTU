#include <iostream>
#include <cstdio>

using namespace std;

struct Human {
    char surname[40];
    char name[40];
    char patronymic[40];
    char address[80];
    char phone[25];
    int age;
};

void inputHuman(Human &p) {
    cout << "Фамилия: ";
    cin >> p.surname;
    cout << "Имя: ";
    cin >> p.name;
    cout << "Отчество: ";
    cin >> p.patronymic;
    cout << "Домашний адрес: ";
    cin >> p.address;
    cout << "Номер телефона: ";
    cin >> p.phone;
    cout << "Возраст: ";
    cin >> p.age;
}

void printHuman(Human p, int num) {
    cout << "Номер: " << num << endl;
    cout << "Фамилия: " << p.surname << endl;
    cout << "Имя: " << p.name << endl;
    cout << "Отчество: " << p.patronymic << endl;
    cout << "Домашний адрес: " << p.address << endl;
    cout << "Номер телефона: " << p.phone << endl;
    cout << "Возраст: " << p.age << endl << endl;
}

void printList(Human a[], int n) {
    if (n == 0) {
        cout << "Список пуст" << endl;
        return;
    }
    for (int i = 0; i < n; i++) printHuman(a[i], i + 1);
}

bool readTextFile(const char fileName[], Human a[], int &n) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) return false;
    n = 0;
    while (n < 20 && fscanf(f, "%39s %39s %39s %79s %24s %d", a[n].surname, a[n].name, a[n].patronymic, a[n].address, a[n].phone, &a[n].age) == 6) n++;
    fclose(f);
    return true;
}

bool writeTextFile(const char fileName[], Human a[], int n) {
    FILE *f = fopen(fileName, "w");
    if (f == NULL) return false;
    for (int i = 0; i < n; i++) fprintf(f, "%s %s %s %s %s %d\n", a[i].surname, a[i].name, a[i].patronymic, a[i].address, a[i].phone, a[i].age);
    fclose(f);
    return true;
}

void deleteByAge(Human a[], int &n, int age) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].age != age) {
            a[k] = a[i];
            k++;
        }
    }
    n = k;
}

void addAfterNumber(Human a[], int &n, int num, Human x) {
    for (int i = n; i > num; i--) a[i] = a[i - 1];
    a[num] = x;
    n++;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const char fileName[] = "people.txt";
    const int maxCount = 20;
    Human people[maxCount];
    int count = 0;

    cout << "Исходный список из файла" << endl;
    printList(people, count);

    int age;
    cout << "Введите возраст для удаления: ";
    cin >> age;
    deleteByAge(people, count, age);

    cout << "Список после удаления" << endl;
    printList(people, count);

    int num;
    Human newPerson;
    cout << "Введите номер элемента, после которого нужно добавить человека: ";
    cin >> num;
    if (num < 1 || num > count) cout << "Ошибка: такого номера нет" << endl;
    else {
        cout << "Введите данные нового человека" << endl;
        inputHuman(newPerson);
        addAfterNumber(people, count, num, newPerson);
    }

    cout << "Итоговый список" << endl;
    printList(people, count);
}
