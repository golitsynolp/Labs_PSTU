#include <iostream>

using namespace std;

struct Item {
    int value;
    Item* next;
};

struct Queue {
    Item* first;
    Item* last;
    int size;
};

void initQueue(Queue& q) {
    q.first = nullptr;
    q.last = nullptr;
    q.size = 0;
}

void addBack(Queue& q, int value) {
    Item* elem = new Item;
    elem->value = value;
    elem->next = nullptr;

    if (q.size == 0) {
        q.first = elem;
        q.last = elem;
    }
    else {
        q.last->next = elem;
        q.last = elem;
    }

    q.size++;
}

int takeFront(Queue& q) {
    if (q.size == 0) return 0;

    Item* elem = q.first;
    int value = elem->value;
    q.first = q.first->next;

    if (q.first == nullptr) q.last = nullptr;

    delete elem;
    q.size--;
    return value;
}

void printQueue(Queue& q) {
    Queue copy;
    initQueue(copy);

    cout << "Очередь: ";
    while (q.size > 0) {
        int value = takeFront(q);
        cout << value << " ";
        addBack(copy, value);
    }
    cout << endl;

    while (copy.size > 0) addBack(q, takeFront(copy));
}

void clearQueue(Queue& q) {
    while (q.size > 0) takeFront(q);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Queue q;
    initQueue(q);

    int n;
    cout << "Введите размер очереди: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int value;
        cout << "Введите элемент очереди: ";
        cin >> value;
        addBack(q, value);
    }

    int pos;
    cout << "Введите номер элемента для удаления: ";
    cin >> pos;

    if (pos < 1 || pos > q.size) cout << "Удаление невозможно" << endl;
    else {
        int oldSize = q.size;
        for (int i = 1; i <= oldSize; i++) {
            int value = takeFront(q);
            if (i != pos) addBack(q, value);
        }
    }

    printQueue(q);

    int count;
    cout << "Введите количество добавляемых элементов: ";
    cin >> count;

    if (pos < 1 || pos > q.size + 1) cout << "Добавление невозможно" << endl;
    else {
        int oldSize = q.size;
        for (int i = 1; i <= oldSize; i++) {
            if (i == pos) {
                for (int j = 1; j <= count; j++) {
                    int value;
                    cout << "Введите добавляемый элемент: ";
                    cin >> value;
                    addBack(q, value);
                }
            }
            addBack(q, takeFront(q));
        }
        if (pos == oldSize + 1) {
            for (int j = 1; j <= count; j++) {
                int value;
                cout << "Введите добавляемый элемент: ";
                cin >> value;
                addBack(q, value);
            }
        }
    }

    printQueue(q);
    clearQueue(q);
}
