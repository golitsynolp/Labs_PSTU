#include <iostream>

using namespace std;

struct Node {
    int num;
    Node* next;
};

Node* makeList(int size) {

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < size; i++) {
        Node* cur = new Node;
        cout << "Введите " << i + 1 << " элемент списка: ";
        cin >> cur->num;
        cur->next = nullptr;

        if (head == nullptr) {
            head = cur;
            tail = cur;
        }
        else {
            tail->next = cur;
            tail = cur;
        }
    }

    return head;
}

void showList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->num << " ";
        cur = cur->next;
    }
    cout << endl;
}

bool deletePlace(Node*& head, int place) {
    if (head == nullptr or place <= 0) return false;

    if (place == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* prev = head;
    for (int i = 1; i < place - 1 and prev != nullptr; i++) prev = prev->next;

    if (prev == nullptr or prev->next == nullptr) return false;

    Node* temp = prev->next;
    prev->next = temp->next;
    delete temp;

    return true;
}

bool addPlace(Node*& head, int count, int place) {
    if (count <= 0 or place <= 0) return false;

    Node* prev = nullptr;
    if (place > 1) {
        prev = head;
        for (int i = 1; i < place - 1 and prev != nullptr; i++) prev = prev->next;
        if (prev == nullptr) return false;
    }

    Node* first = nullptr;
    Node* last = nullptr;

    for (int i = 0; i < count; i++) {
        Node* cur = new Node;
        cout << "Введите новый элемент: ";
        cin >> cur->num;
        cur->next = nullptr;

        if (first == nullptr) {
            first = cur;
            last = cur;
        }
        else {
            last->next = cur;
            last = cur;
        }
    }

    if (place == 1) {
        last->next = head;
        head = first;
        return true;
    }

    last->next = prev->next;
    prev->next = first;

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "Введите количество элементов списка: ";
    cin >> size;

    Node* head = makeList(size);

    cout << "Исходный список: ";
    showList(head);

    int place;
    cout << "Введите номер элемента для удаления: ";
    cin >> place;

    if (deletePlace(head, place)) cout << "Элемент удален" << endl;
    else cout << "Удаление невозможно" << endl;

    cout << "Список после удаления: ";
    showList(head);

    int count;
    cout << "Введите количество добавляемых элементов: ";
    cin >> count;

    if (addPlace(head, count, place)) cout << "Элементы добавлены" << endl;
    else cout << "Добавление невозможно" << endl;

    cout << "Итоговый список: ";
    showList(head);
}
