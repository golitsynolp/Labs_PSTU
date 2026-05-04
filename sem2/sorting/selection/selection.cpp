#include <iostream>

using namespace std;

int main()
{
    const int Size = 10;
    int arr[Size] = {1, 4, 0, 3, 9, 2, 1, 7, 0, 3};
    int max_n = 0;
    
    for (int i = 0; i < Size; i++) {
        int temp, indx;
        for (int j = 0; j < Size - i; j++) {
            if (arr[j] > max_n) {
                max_n = arr[j];
                indx = j;
            }
        }
        temp = arr[Size - 1 - i];
        arr[Size - 1 - i] = arr[indx];
        arr[indx] = temp;
        max_n = 0;
    }
    
    for (int i = 0; i < Size; i++) {
        cout << arr[i];
    }
    cout << endl;
    
    

    return 0;
}
