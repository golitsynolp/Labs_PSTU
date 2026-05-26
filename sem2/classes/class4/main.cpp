#include <iostream>

#include "Class4-1.h"
#include "Class4-2.h"

int main() {
    // Демонстрация PAIR
    PAIR p1(2, 3), p2(4, 5);
    PAIR p3 = p1 + p2;          // (6, 8)
    std::cout << "p1 + p2 = " << p3 << std::endl;

    // Демонстрация LONG
    LONG a(1, 7);   // 1*10 + 7 = 17
    LONG b(2, 5);   // 2*10 + 5 = 25

    LONG sum = a + b;   // 17 + 25 = 42  => (4,2)
    LONG dif = a - b;   // 17 - 25 = -8  => (-1, 2)  т.к. -1*10 + 2 = -8
    LONG mul = a * b;   // 17 * 25 = 425 => (42, 5)

    std::cout << "LONG a: " << a;
    std::cout << "LONG b: " << b;
    std::cout << "a + b = " << sum;
    std::cout << "a - b = " << dif;
    std::cout << "a * b = " << mul;

    return 0;
}