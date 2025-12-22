#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float a = 0;
    float b = 2;
    double e = 0.000001;
    float c, fa, fb, fc;
    //func = 0.25^3 + x - 1.2502 = 0

    while (b - a > e) {
        c = (a + b) / 2;

        fa = (0.25 * pow(a, 3) + a - 1.2502);
        fb = (0.25 * pow(b, 3) + b - 1.2502);
        fc = (0.25 * pow(c, 3) + c - 1.2502);

        if (fa * fc < 0) {b = c;}
        else if (fb * fc < 0) {a = c;}
        else {cout << "!" << endl;}
    }

    cout << "Roots: " << a << "; " << b << endl;

    return 0;
}
