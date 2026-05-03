#include <iostream>

using namespace std;

int main()
{
    const int Size = 10;
    int arr[Size] = {1, 4, 0, 3, 9, 1, 5, 1, 6, 0};
    
    for (int i = 0; i < Size - 1; i++) {
        int temp;
        for (int j = 0; j < Size - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
            
        }
        
    }
    
    for (int i = 0; i < Size; i++) {
        cout << arr[i];
    }
    cout << endl;

    return 0;
}
