#include <iostream>
#include <ctime>

#define Size 100

using namespace std;

int main() {
    srand(time(0));

    int arr[Size];
    int real_size;
    int range_max = 100;

    cout << "Enter a size of list: ";
    cin >> real_size;

    for (int i = 0; i < real_size; i++) {
        arr[i] = ((double)rand() / RAND_MAX) * range_max;
        cout << arr[i] << " ";
    }
    cout << endl;

    int k, i = 0;
    bool is_del = false;

    cout << "Enter k: ";
    cin >> k; 
    
    while (i < real_size) {
        if ((i + 1) == k) {
            is_del = true;
        }
        if (is_del == true) {
            arr[i] = arr[i + 1];
        }
        i++;
    }

    int temp1, temp2;
    bool is_inserted = false;
    i = 0;

    while (i < real_size) {
        if (arr[i] % 2 == 0 && is_inserted == false) {
            temp1 = arr[i + 1];
            arr[i + 1] = arr[i - 1] + 2;
            is_inserted = true;
        }
        else if (is_inserted == true) {
            temp2 = arr[i + 1];
            arr[i + 1] = temp1;
            temp1 = temp2;
        }
        i++; 
    }

    for (int i = 0; i < real_size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}