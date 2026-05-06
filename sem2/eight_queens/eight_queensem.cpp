#include <iostream>

using namespace std;

const int N = 8;
int board[N];
bool col[N] = {};           
bool diag1[2 * N - 1] = {};
bool diag2[2 * N - 1] = {};
int solutions = 0;

void print_board() {
    cout << "Solution " << ++solutions << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i] == j ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

void solve(int row) {
    if (row == N) {
        print_board();
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!col[i] && !diag1[row + i] && !diag2[row - i + N - 1]) {
            board[row] = i;
            col[i] = true;
            diag1[row + i] = true;
            diag2[row - i + N - 1] = true;

            solve(row + 1);

            col[i] = false;
            diag1[row + i] = false;
            diag2[row - i + N - 1] = false;
        }
    }
}

int main() {
    solve(0);
    cout << "Find solution: " << solutions << endl;
    return 0;
}