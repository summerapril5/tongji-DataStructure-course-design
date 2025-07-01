#include <iostream>
#include <conio.h>
using namespace std;

//暂停等待键盘输入
void pause()
{
	while (_getch() != '\r')
		;
	std::cout << std::endl;
}


//展示菜单
void menuDisplay()
{
	cout << "            二叉树排序              " << endl;
	cout << "====================================" << endl;
	cout << "  *         A---建立二叉树       *  " << endl;
	cout << "  *         B---添加节点         *  " << endl;
	cout << "  *         C---查询节点         *  " << endl;
	cout << "  *         Q---退出程序         *  " << endl;
	cout << "====================================" << endl;
}

//输入数据
template<typename T>
T input(T l_limit, T U_limit)
{
	T num;
	while (true) {
		std::cin >> num;
		if (cin.fail() || num < l_limit || num > U_limit) {
			cout<< "输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			return num;
	}
}

//二叉树的数据结构
struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

//按顺序显示树
void treeDisplay(TreeNode* root)
{
	if (root == nullptr)
		return;
	else {
		treeDisplay(root->left);
		cout << root->data << "  ";
		treeDisplay(root->right);
	}

}

//插入树节点
void insert(TreeNode*& root, int key)
{
	//如果找到树的底部，为数据创建一个新的树节点
	if (root == nullptr) {
		root = new(std::nothrow) TreeNode(key);
		if (root == NULL) {
			cout << "叶子结点内存申请失败" << endl;
			return;
		}
	}
	else if (key < root->data)
		insert(root->left, key);//左
	else if (key > root->data)
		insert(root->right, key);//右
	else
		cout << "已有节点" << key << "在树中，将不重复插入！" << endl;

}

//搜索
bool search(TreeNode* root, int key)
{
	if (root == nullptr)//在底部
		return false; 
	else if (key == root->data)//相等
		return true; //找到了
	else if (key < root->data)//小
		return search(root->left, key);//左边找
	else //大
		return search(root->right, key);//右边找
}

int main()
{

	TreeNode* root = nullptr;//创建根节点

	//循环可以让用户重复执行过程
	while (true) {
		//清屏
		system("cls");

		//显示菜单
		menuDisplay();

		char controller;
		while (true) {
			controller = _getch();

			if ((controller == 'Q' || controller == 'q') || (controller >= 'a' && controller <= 'c') || (controller >= 'A' && controller <= 'C')) {
				cout << controller << endl;
				switch (controller)
				{
				case 'Q':
				case 'q':
					cout << "程序结束！" << endl;
					return 0;
				case 'A':
				case 'a':
					cout << "进行创建二叉树操作" << endl;
					int n;
					cout << "请输入二叉树节点个数" << endl;
					n = input<int>(1, INT_MAX);

					for (int i = 0; i < n; ++i) {
						int key;
						cout << "请输入第" << i + 1 << "个节点的数据" << endl;
						key = input<int>(INT_MIN, INT_MAX);
						insert(root, key);//把节点插入树中
					}
					cout << "当前树为：" << endl;
					treeDisplay(root);
					cout << endl;
					cout << "操作完成，按回车继续..." << endl;
					pause();
					break;
				case 'B':
				case 'b':
					cout << "进行添加节点操作" << endl;
					int key;
					cout << "请输入第你想加入节点的数据" << endl;
					key = input<int>(INT_MIN, INT_MAX);
					insert(root, key);
					cout << "当前树为：" << endl;
					treeDisplay(root);
					cout << endl;
					cout << "操作完成，按回车继续..." << endl;
					pause();
					break;
				case 'c':
				case 'C':
					cout << "选择查找操作" << endl;
					int target;
					cout << "请输入你想查找的节点数据" << endl;
					target = input<int>(INT_MIN, INT_MAX);

					if (search(root, target))
						cout << "节点" << target << "已被找到！" << endl;
					else
						cout << "节点" << target << "未被找到" << endl;
					cout << "操作完成，按回车继续..." << endl;
					pause();
					break;
				default:
					continue;
				}
				break;
			}
		}


	}

	return 0;
}
