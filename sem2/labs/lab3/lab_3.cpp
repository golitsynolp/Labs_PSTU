#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a = 1, b = 2;
    double e = 0.00001;
    double step = (b - a) / 10.0;
   
    for (double x = a; x <= b; x += step) {
        double summ1 = 1.0, temp1 = 1.0;


        for(int n = 1; n < 15; n++) {
            temp1 *= x / n;
            summ1 += temp1;
        } 

        double summ2 = 1.0, temp2 = 1.0;
        int n = 1;

        while (fabs(temp2) > e) {
            temp2 *= x / n;
            summ2 += temp2;
            n++;
        }

        cout << "X: " << x << ", SN: " << summ1 << ", SE: " << summ2 << ", Y: " << pow(e, x) << endl;
    }

    return 0;
}