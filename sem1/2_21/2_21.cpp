#include <iostream> 
using namespace std; 
int main(){
    int N, T; 
    bool flag = true;
    cin >> N; 
    if ( N == 0){ return 0; }
    while(true){
        cin >> T; 

        if(T == 0){
            break;
        }
        if(T <= N){
            flag = false;
        }
        N = T; 
    }
    if (flag){
        cout << "yes" << endl;
    }
    else{
        cout << "no" << endl;
    }
    return 0;
}
