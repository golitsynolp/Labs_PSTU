#include <iostream>
#include <cmath>

using namespace std;

//метод Ньютона
//первоначальная функция: 0.25 * x^3 + x - 1.2502
//первая производная: 0.75 * x^2 + 1
//вторая производная: 1.5 * x
//[0, 2]

int main() {
    float x, xPrev;
    double e = 0.000001;

    //f(b) * f``(b)
    //f(b): 0.25 * b^3 + b - 1.2502 = 0.25 * 2^3 + 2 - 1.2502 = 2.7498
    //f``(b): 1.5 * 2 = 3
    // 2 *  2.7498 > 0 => x0 = 2

    x = 2;
    xPrev = 0;

    while (abs(x - xPrev) > e) {
        xPrev = x; 
        // x(i-1) - f(x(i - 1) / f`(x(i - 1)))
        x = xPrev - (0.25 * pow(xPrev, 3) + xPrev - 1.2502) / (0.75 * pow(xPrev, 2) + 1);
    }
    cout << "Root: " << x << endl;

    return 0;
}
