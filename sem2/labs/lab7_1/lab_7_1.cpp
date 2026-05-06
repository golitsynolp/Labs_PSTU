#include <iostream>

using namespace std;

void subtraction(float a, float b) {
    cout << "a - b = " << (a - b) << endl;
}

void subtraction(float a1, float b1, float a2, float b2) {
    cout << "a1 + b1 * i - (a1 + b2 * i) = " << (a1 - a2) << " + (" << (b1 - b2) << ") * i" << endl;
}

int main() {
    float r_num1 = 123.45, r_num2 = 678.90;
    float c_num_a1 = 34.56, c_num_b1 = 7.8;
    float c_num_a2 = 90.12, c_num_b2 = 3.4;
    
    subtraction(r_num1, r_num2);
    subtraction(c_num_a2, c_num_b2, c_num_a1, c_num_b1);

    return 0;
}