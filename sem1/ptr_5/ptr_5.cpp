#include <iostream>  
using namespace std;
int main(){
    int N, factorial = 1; 
    cin >> N; 
    int *ptr_1 = &N; 
    int *ptr_fact = &factorial; 
    for (int i = 1; i <= *ptr_1; i++) {
        *ptr_fact *= i;
    }
    cout << factorial; 
}
