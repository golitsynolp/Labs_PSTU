#include <iostream>

using namespace std;

struct Elem {
    int num;
    Elem* next;
};

struct MyStack {
    Elem* top;
    int count;

    void start() {
        top = NULL;
        count = 0;
    }

    void add(int value) {
        Elem* p = new Elem;
        p->num = value;
        p->next = top;
        top = p;
        count++;
    }

    int take() {
        if (count == 0) return 0;
        Elem* p = top;
        int value = p->num;
        top = top->next;
        delete p;
        count--;
        return value;
    }

    void clean() {
        while (count > 0) take();
    }
};

void show(MyStack& a) {
    MyStack b;
    b.start();

    while (a.count > 0) {
        int value = a.take();
        cout << value << " ";
        b.add(value);
    }
    cout << endl;

    while (b.count > 0) a.add(b.take());
}

void readStack(MyStack& a, int n) {
    MyStack b;
    b.start();

    for (int i = 1; i <= n; i++) {
        int value;
        cout << "Введите " << i << " элемент стека: ";
        cin >> value;
        b.add(value);
    }

    while (b.count > 0) a.add(b.take());
}

bool deleteNumber(MyStack& a, int k) {
    if (k < 1 || k > a.count) {
        cout << "Удаление невозможно" << endl;
        return false;
    }

    MyStack b;
    b.start();

    for (int i = 1; i < k; i++) b.add(a.take());

    a.take();

    while (b.count > 0) a.add(b.take());

    return true;
}

bool pasteNumber(MyStack& a, int k, int m) {
    if (k < 1 || k > a.count + 1) {
        cout << "Добавление невозможно" << endl;
        return false;
    }

    MyStack b, c;
    b.start();
    c.start();

    for (int i = 1; i < k; i++) b.add(a.take());

    for (int i = 1; i <= m; i++) {
        int value;
        cout << "Введите добавляемый элемент: ";
        cin >> value;
        c.add(value);
    }

    while (c.count > 0) a.add(c.take());
    while (b.count > 0) a.add(b.take());

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    MyStack a;
    a.start();

    int n;
    cout << "Введите размер стека: ";
    cin >> n;

    readStack(a, n);

    int k;
    cout << "Введите номер удаляемого элемента: ";
    cin >> k;

    if (deleteNumber(a, k)) {
        cout << "Стек после удаления: ";
        show(a);

        int m;
        cout << "Введите количество добавляемых элементов: ";
        cin >> m;

        pasteNumber(a, k, m);

        cout << "Стек после добавления: ";
        show(a);
    }

    a.clean();
}
