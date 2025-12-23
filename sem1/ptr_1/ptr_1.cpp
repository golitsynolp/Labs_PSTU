#include <iostream> 
using namespace std; 
int main(){
    int N;
    cout << "Введите изначальное число: "; 
    cin >> N;
    int *ptr = &N; 
    cout << "Введите измененное число: "; 
    cin >> *ptr; 
    cout << N << endl;
    return 0;
}
