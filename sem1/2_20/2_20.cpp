#include <iostream> 
#include <cmath>
using namespace std; 
int main(){
    int N, S, a; 
    bool flag = false;
    cin >> N >> S; 
    for(int i = 1; i <= N; i++){
        a = sin(N + (i/N));
        if (a == S){
            flag == true; 
            cout << "Да, число существует в последовательности" << endl; 
        }
    }
    if (flag == false){
        cout << "Нет, числа не существует в последовательности" << endl; 
    }
    return 0;
}
