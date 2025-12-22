#include <iostream> 
#include <cmath>
using namespace std; 
int main(){
    int N, num; 
    float maxA, a;
    cin >> N; 
    maxA = sin(N + (1/N));
    for(int i = 2; i <= N; i++){
        a = sin(N + (i/N));
        if (a > maxA){
            maxA = a; 
            num = i;
        }
    }
    cout << "zn = " << maxA << " num =" << num << endl;
}
