#include <iostream>
#include <string>

using namespace std;

int KMPSearch(string text, string word){
    int n = text.length();
    int m = word.length();

    if (m == 0 || n < m) return -1;

    int* prefix = new int[m];
    prefix[0] = 0;

    for (int i = 1, j = 0; i < m; i++){
        while (j > 0 && word[i] != word[j]) j = prefix[j - 1];
        if (word[i] == word[j]) j++;
        prefix[i] = j;
    }

    for (int i = 0, j = 0; i < n; i++){
        while (j > 0 && text[i] != word[j]) j = prefix[j - 1];
        if (text[i] == word[j]) j++;

        if (j == m){
            delete[] prefix;
            return i - m + 1;
        }
    }

    delete[] prefix;
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

    int answer = KMPSearch(line, fragment);

    if (answer == -1) cout << "Подстрока не найдена" << endl;
    else cout << "Подстрока найдена. Индекс: " << answer << endl;
}
