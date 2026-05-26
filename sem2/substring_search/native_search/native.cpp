#include <iostream>
#include <string>

using namespace std;

int NaiveSearch(string text, string word){
    int n = text.length();
    int m = word.length();

    if (m == 0 || n < m) return -1;

    for (int i = 0; i <= n - m; i++){
        int j = 0;

        while (j < m && text[i + j] == word[j]) j++;

        if (j == m) return i;
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

    int answer = NaiveSearch(line, fragment);

    if (answer == -1) cout << "Подстрока не найдена" << endl;
    else cout << "Подстрока найдена. Индекс: " << answer << endl;
}
