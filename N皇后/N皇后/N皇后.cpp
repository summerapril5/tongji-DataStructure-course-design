#include <iostream>
#include <vector>

using namespace std;

// 检查放置的皇后是否安全
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        //检查是否有皇后在同一列或对角线上
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// 递归解决N皇后问题
void solveNQueens(int n, int row, vector<int>& board, int& count) {
    if (row == n) {
        
        ++count;
        cout << "Solution " << count << ":"<<endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i] == j) {
                    cout << "X ";
                }
                else {
                    cout << "0 ";
                }

            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;  // 放置皇后
            solveNQueens(n, row + 1, board, count);
        }
    }
}

int main() {
    int n;
    cout << "输入皇后个数(N): ";
    cin >> n;
    cout << endl;
    cout << "皇后解法：" << endl << endl;
    vector<int> board(n, 0);  // 初始化棋盘，所有皇后在第一行
    int count = 0;

    solveNQueens(n, 0, board, count);

    cout << "共有" << count <<"种解法"<< endl;

    return 0;
}