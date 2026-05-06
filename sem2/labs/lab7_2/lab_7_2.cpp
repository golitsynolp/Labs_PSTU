#include <iostream>
#include <cstdarg>

using namespace std;

int min(int cnt, ...) {
    va_list args;
    va_start(args, cnt);

    int min_n = va_arg(args, int);

    for (int i = 1; i < cnt; i++) {
        int n = va_arg(args, int);
        if (n < min_n) {
            min_n = n;
        }
    }
    va_end(args);

    return min_n;
}

int main() {
    cout << min(5, -9, 90, 132, -20, 0) << endl;
    cout << min(10, -9, 90, 132, -20, 0, 1, -33, 100, 7, 12) << endl;
    cout << min(12, 9, 90, 132, 20, 0, 1, 3, 100, 7, 12, 30, 1000) << endl;

    return 0;
}