#include <iostream>
using namespace std;

const int MAX_N = 100; //�ڵ����ֵ
const int MAX_M = (MAX_N * (MAX_N - 1)) / 2; //���߽�

struct Edge {
    int u, v, cost;
};

Edge edges[MAX_M]; //����߽�
int parent[MAX_N]; //����ÿ���ڵ�ĸ��ڵ�

//��������
template<typename T>
T input(T l_limit, T U_limit)
{
    T num;
    while (true) {
        cin >> num;
        if (cin.fail() || num < l_limit || num > U_limit) {
            cout << "������������������" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        else
            return num;
    }
}

//��ʼ��������
void init(int n)
{
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

//���Ҹ��ڵ�
int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

//���������ڵ�
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        parent[x] = y;

}

//��������
void quicksort(Edge* edges, int left, int right)
{
    //������ң�����
    if (left >= right)
        return;

    int pivot = edges[left].cost;//�������ĵ�
    int l = left, r = right;

    while (l < r) {
        while (l < r && edges[r].cost >= pivot)
            --r;//���Ҳ��ƶ����������ĵ�ĵ�һ��Ԫ��
        while (l < r && edges[l].cost <= pivot)
            ++l;//������ƶ���С������ĵ�һ��Ԫ��
        if (l < r)
            swap(edges[l], edges[r]);//����󲻵����ң�����
    }
    swap(edges[left], edges[l]);//�����м�

    quicksort(edges, left, l - 1);//��
    quicksort(edges, l + 1, right);//��
}


//��kruskal�㷨������С����
int kruskal(Edge* edges, int n, int m)
{
    quicksort(edges, 0, m - 1); 

    init(n);//��ʼ��˫�׽ڵ�

    int minCost = 0;

    for (int i = 0, j = 0; i < m && j < n - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int cost = edges[i].cost;

        
        if (find(u) != find(v)) {
            unite(u, v);
            minCost += cost;//���
            ++j;
        }
    }

    return minCost;
}

int main()
{
    int n, m;
    cout << "������ڵ�����" << endl;
    n = input<int>(0, MAX_N);
    cout << "������ߵ�����" << endl;
    m = input<int>(0, MAX_M);

    
    for (int i = 0; i < m; ++i) {
        cout << "�������" << i + 1 << "���ߵĵ�һ���ڵ�" << endl;
        edges[i].u = input<int>(0, MAX_N);
        cout << "�������" << i + 1 << "���ߵĵڶ����ڵ�" << endl;
        edges[i].v = input<int>(0, MAX_N);
        cout << "�������" << i + 1 << "���ߵ����" << endl;
        edges[i].cost = input<int>(0, 1000000);
    }

    int result = kruskal(edges, n, m);
    cout << "��С��۵�����������ǣ�" << result << endl;

    return 0;
}
