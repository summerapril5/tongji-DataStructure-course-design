#include <iostream>
using namespace std;

const int MAX_N = 100; //节点最大值
const int MAX_M = (MAX_N * (MAX_N - 1)) / 2; //最大边界

struct Edge {
    int u, v, cost;
};

Edge edges[MAX_M]; //储存边界
int parent[MAX_N]; //储存每个节点的父节点

//输入数据
template<typename T>
T input(T l_limit, T U_limit)
{
    T num;
    while (true) {
        cin >> num;
        if (cin.fail() || num < l_limit || num > U_limit) {
            cout << "输入有误，请重新输入" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        else
            return num;
    }
}

//初始化父数组
void init(int n)
{
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

//查找根节点
int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

//连接两个节点
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        parent[x] = y;

}

//快速排序
void quicksort(Edge* edges, int left, int right)
{
    //左等于右，返回
    if (left >= right)
        return;

    int pivot = edges[left].cost;//设置中心点
    int l = left, r = right;

    while (l < r) {
        while (l < r && edges[r].cost >= pivot)
            --r;//将右侧移动到大于中心点的第一个元素
        while (l < r && edges[l].cost <= pivot)
            ++l;//将左侧移动到小于枢轴的第一个元素
        if (l < r)
            swap(edges[l], edges[r]);//如果左不等于右，交换
    }
    swap(edges[left], edges[l]);//换到中间

    quicksort(edges, left, l - 1);//左
    quicksort(edges, l + 1, right);//右
}


//用kruskal算法计算最小花费
int kruskal(Edge* edges, int n, int m)
{
    quicksort(edges, 0, m - 1); 

    init(n);//初始化双亲节点

    int minCost = 0;

    for (int i = 0, j = 0; i < m && j < n - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int cost = edges[i].cost;

        
        if (find(u) != find(v)) {
            unite(u, v);
            minCost += cost;//求和
            ++j;
        }
    }

    return minCost;
}

int main()
{
    int n, m;
    cout << "请输入节点数量" << endl;
    n = input<int>(0, MAX_N);
    cout << "请输入边的数量" << endl;
    m = input<int>(0, MAX_M);

    
    for (int i = 0; i < m; ++i) {
        cout << "请输入第" << i + 1 << "条边的第一个节点" << endl;
        edges[i].u = input<int>(0, MAX_N);
        cout << "请输入第" << i + 1 << "条边的第二个节点" << endl;
        edges[i].v = input<int>(0, MAX_N);
        cout << "请输入第" << i + 1 << "条边的造价" << endl;
        edges[i].cost = input<int>(0, 1000000);
    }

    int result = kruskal(edges, n, m);
    cout << "最小造价电网的总造价是：" << result << endl;

    return 0;
}
