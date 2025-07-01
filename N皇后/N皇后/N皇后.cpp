#include <iostream>
#include <vector>

using namespace std;

// ������õĻʺ��Ƿ�ȫ
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        //����Ƿ��лʺ���ͬһ�л�Խ���
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// ���ݷ����N�ʺ�����
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
            board[row] = col;  // ���ûʺ�
            solveNQueens(n, row + 1, board, count);
        }
    }
}

int main() {
    int n;
    cout << "������ʺ�ĸ���(N): ";
    cin >> n;
    cout << endl;
    cout << "�ʺ�ⷨ��" << endl << endl;
    vector<int> board(n, 0);  // ��ʼ�����̣������лʺ��ڵ�һ��
    int count = 0;

    solveNQueens(n, 0, board, count);

    cout << "����" << count <<"�ֽⷨ"<< endl;

    return 0;
}
