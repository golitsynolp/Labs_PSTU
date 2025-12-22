#include <iostream> 
using namespace std; 
int main(){
    int N, S; 
    cout << "Введите количество слагаемых "; 
    cin >> N; 
    for (int i = 1; i <= N; i++){
        if (i%3== 0){
            S-=i; 
        } 
        else{
            S+=i;
        } 
    }
    cout << "S = " << S << endl; 
} 
