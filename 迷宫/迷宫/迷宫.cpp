#include <iostream>
#include <vector>
using namespace std;

const int N = 6;//�����Թ���С

void printMaze(const vector<vector<int>>& maze)//��ӡ����
{

    for (int i = -1; i < N; ++i)
    {
        if (i != -1) {
            cout  << i << "��" << "   ";
        }
        else {
            cout << "      ";
        }
    }
    cout << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j == 0)
            {
                cout <<  i << "��"<< "    ";
            }
            cout << maze[i][j] << "     ";
        }
        cout << endl;
    }
}

bool isSafe(const vector<vector<int>>& maze, int x, int y) //�ж��Ƿ���������
{
    return (x >= 0 && x < N && y >= 0 && y < N && (maze[x][y] == 0 || maze[x][y] == 3));
}

bool solveMazeUtil(vector<vector<int>>& maze, int x, int y, vector<pair<int, int>>& path) 
{
    if (x == N - 1 && y == N - 1) {
        path.push_back(std::make_pair(x, y));
        return true;
    }

    if (isSafe(maze, x, y)) {
        maze[x][y] = 2;//2��ʾ�߹���
        path.push_back(make_pair(x, y));
        //�ݹ�������������
        if (solveMazeUtil(maze, x + 1, y, path))
            return true;

        if (solveMazeUtil(maze, x, y + 1, path))
            return true;

        if (solveMazeUtil(maze, x - 1, y, path))
            return true;

        if (solveMazeUtil(maze, x, y - 1, path))
            return true;

        maze[x][y] = 3;//3������ͬ
        path.pop_back();
        return false;
    }

    return false;
}

void solveMaze(vector<vector<int>>& maze) {
    vector<pair<int, int>> path;

    if (solveMazeUtil(maze, 0, 0, path)) {
        cout << "�Թ�·��:" << endl;
        for (const auto& p : path) {
            if (p.first == N - 1 && p.second == N - 1) {
                cout << "<" << p.first << ", " << p.second << ">";
            }
            else
            {
                cout << "<" << p.first << ", " << p.second << "> --> ";
            }
        }
        cout << endl;
    }
    else {
        cout << "�����ڽ��·��" << endl;
    }
}

int main() {
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0}
    };

    cout << "�Թ���ͼ:" << endl;
    printMaze(maze);

    solveMaze(maze);

    return 0;
}
