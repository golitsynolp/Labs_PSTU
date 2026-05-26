#include <iostream>

using namespace std;

struct Node {
    int num;
    Node* prev;
    Node* next;
};

Node* makeList(int size) {

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < size; i++) {
        Node* cur = new Node;
        cout << "Введите " << i + 1 << " элемент списка: ";
        cin >> cur->num;
        cur->prev = nullptr;
        cur->next = nullptr;

        if (head == nullptr) {
            head = cur;
            tail = cur;
        }
        else {
            cur->prev = tail;
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

    Node* cur = head;
    for (int i = 1; i < place and cur != nullptr; i++) cur = cur->next;

    if (cur == nullptr) return false;

    if (cur->prev != nullptr) cur->prev->next = cur->next;
    else head = cur->next;

    if (cur->next != nullptr) cur->next->prev = cur->prev;

    delete cur;
    return true;
}

bool addPlace(Node*& head, int count, int place) {
    if (count <= 0 or place <= 0) return false;

    Node* first = nullptr;
    Node* last = nullptr;

    for (int i = 0; i < count; i++) {
        Node* cur = new Node;
        cout << "Введите новый элемент: ";
        cin >> cur->num;
        cur->prev = nullptr;
        cur->next = nullptr;

        if (first == nullptr) {
            first = cur;
            last = cur;
        }
        else {
            cur->prev = last;
            last->next = cur;
            last = cur;
        }
    }

    if (place == 1) {
        last->next = head;
        if (head != nullptr) head->prev = last;
        head = first;
        return true;
    }

    Node* before = head;
    for (int i = 1; i < place - 1 and before != nullptr; i++) before = before->next;

    if (before == nullptr) return false;

    Node* after = before->next;
    before->next = first;
    first->prev = before;
    last->next = after;
    if (after != nullptr) after->prev = last;

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

    return 0;
}
