#include <iostream>
#include <cmath>

using namespace std;

//f(x) = 0.25 * x^3 + x - 1.2502
//f`(x) = 0.75 * x^2 + 1
//f``(x) = 1.5 * x
//[0,2]

//v(x) = x + L * f(x); v - фи, L -лямбда
//-1/r < L < 0, if f`() > 0
//0 < L < 1/r, if f`() < 0
// r = max(|f`(a)|, |f`(b)|) = max(0.75 * 0^2 + 1, 0.75 * 2^2 + 1) = max(1, 5) => r = 5
// -1/r < L < 0 => -0.2 < L < 0
// L = -0.1

int main() {
    float x, xPrev;
    double e = 0.000001;
    double lambda = -0.1;

    x = 1;
    xPrev = 0;

    while (abs(x - xPrev) > e) {
        xPrev = x;
        x = lambda * (0.25 * pow(xPrev, 3) + xPrev - 1.2502) + xPrev;
    }

    cout << "Root: " << x << endl;

    return 0;
}
