#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream f1("F1.txt");
    ofstream f2("F2.txt");
    string stroka;
    string glasnye = "AEIOUYaeiouyАЕЁИОУЫЭЮЯаеёиоуыэюя";
    int k, nomer = 1, kolvo = 0;

    cout << "Введите K от 1 до 10: ";
    cin >> k;

    while (getline(f1, stroka)) {
        if (nomer >= k && nomer <= k + 5) f2 << stroka << endl;
        nomer++;
    }

    f1.close();
    f2.close();

    ifstream fin("F2.txt");

    while (getline(fin, stroka)) {
        for (int i = 0; i < stroka.length(); i++) {
            for (int j = 0; j < glasnye.length(); j++) {
                if (stroka[i] == glasnye[j]) kolvo++;
            }
        }
    }

    fin.close();

    cout << "Строки с " << k << " до " << k + 5 << " скопированы в файл F2.txt" << endl;
    cout << "Количество гласных букв в файле F2.txt: " << kolvo << endl;
}
