#include <iostream>

#include "Money.h"

int main() {
    Money a;
    std::cin >> a;
    std::cout << "a = " << a << std::endl;

    Money b(10, 50);
    std::cout << "b = " << b << std::endl;

    Money c(b);
    std::cout << "c (copy of b) = " << c << std::endl;

    Money d;
    d = a;
    std::cout << "d = a = " << d << std::endl;

    Money sum = a + b;
    std::cout << a << " + " << b << " = " << sum << std::endl;

    Money diff = a - b;
    std::cout << a << " - " << b << " = " << diff << std::endl;

    Money e(5, 30);
    Money f(10, 80);
    Money neg = e - f;
    std::cout << e << " - " << f << " = " << neg << std::endl;

    return 0;
}