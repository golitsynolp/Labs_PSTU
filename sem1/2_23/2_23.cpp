#include <iostream> 
#include <cmath>
using namespace std; 
int main(){
    int N, c; 
    float maxA, a;
    cin >> N; 
    maxA = sin(N + (1/N));
    for(int i = 2; i <= N; i++){
        a = sin(N + (i/N));
        if (a > maxA){
            maxA = a;
            c = 1;
        }
        else if (a == maxA){ c++; }
    }
    cout << "zn = " << maxA << " count =" << c << endl;
}
