#include <iostream>

using namespace std;

int main()
{
    const int Size = 10;
    int arr[Size] = {7, 4, 0, 9, 9, 1, 5, 7, 1, 1};
    
    for (int i = 1; i < Size; i++) {
        int temp;
        for (int j = 0; j < i; j++) {
            if (arr[i - j - 1] > arr[i - j]) {
                temp = arr[i - j - 1];
                arr[i - j - 1] = arr[i - j];
                arr[i - j] = temp;
            } 
        }
    }
    
    for (int i = 0; i < Size; i++) {
        cout << arr[i];
    }
    cout << endl;

    return 0;
}
