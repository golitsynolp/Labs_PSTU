#include <iostream>

using namespace std;

int main() {
    string s = "12job34a";

    for (int i = 0; i < s.size() - 1; i++) {
        for (int j = 0; j < s.size() - 1; j++) {
            if ((48 <= s[j] && s[j] <= 57) && (s[j + 1] < 48 || s[j + 1] > 57)) {
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
    cout << s << endl;

    return 0;
}