#include <iostream> 
using namespace std;
int main(){ 
    float a, b, sum; 
    cin >> a >> b; 
    float *ptr_1 = &a; 
    float *ptr_2 = &b; 
    sum = *ptr_1 + *ptr_2; 
    cout << "a + b = " << sum << endl; 
    return 0;
}
