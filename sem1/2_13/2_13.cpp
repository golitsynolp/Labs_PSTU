#include <iostream>
#include <math.h>

using namespace std;

int main() {
    float a, b, c, d, x_1, x_2;

    cin >> a >> b >> c;

    d = (b * b - 4 * a * c);

    if (d < 0 || a == 0 ) {
        cout << "Error" << endl;
    }
    else if (d == 0) {
        x_1 = sqrt(d) / (2 * a);
        cout << x_1 << endl;
    }
    else {
        x_1 = sqrt(d) / (2 * a);
        x_2 = -(sqrt(d) / (2 * a));
        cout << x_1 << " " << x_2 << endl;
    }
    
    return 0;
}
