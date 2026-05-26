#include <iostream>
#include <string>

using namespace std;

int BoyerMooreSearch(string text, string word){
    const int SIZE = 256;
    int last[SIZE];
    int n = text.length();
    int m = word.length();

    if (m == 0) return 0;
    if (n < m) return -1;

    for (int i = 0; i < SIZE; i++) last[i] = -1;

    for (int i = 0; i < m; i++) last[(unsigned char)word[i]] = i;

    int pos = 0;
    while (pos <= n - m){
        int j = m - 1;

        while (j >= 0 && word[j] == text[pos + j]) j--;

        if (j < 0) return pos;

        int move = j - last[(unsigned char)text[pos + j]];
        if (move < 1) move = 1;

        pos += move;
    }

    return -1;
}

int main(){
    setlocale(LC_ALL, "Russian");

    string line;
    string fragment;

    cout << "Введите строку: ";
    getline(cin, line);

    cout << "Введите подстроку: ";
    getline(cin, fragment);

    int answer = BoyerMooreSearch(line, fragment);

    if (answer == -1) cout << "Подстрока не найдена" << endl;
    else cout << "Подстрока найдена. Индекс: " << answer << endl;
}
