#include <iostream>
#include <conio.h>
using namespace std;

//��ͣ�ȴ���������
void pause()
{
	while (_getch() != '\r')
		;
	std::cout << std::endl;
}


//չʾ�˵�
void menuDisplay()
{
	cout << "            ����������              " << endl;
	cout << "====================================" << endl;
	cout << "  *         A---����������       *  " << endl;
	cout << "  *         B---��ӽڵ�         *  " << endl;
	cout << "  *         C---��ѯ�ڵ�         *  " << endl;
	cout << "  *         Q---�˳�����         *  " << endl;
	cout << "====================================" << endl;
}

//��������
template<typename T>
T input(T l_limit, T U_limit)
{
	T num;
	while (true) {
		std::cin >> num;
		if (cin.fail() || num < l_limit || num > U_limit) {
			cout<< "������������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			return num;
	}
}

//�����������ݽṹ
struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

//��˳����ʾ��
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

//�������ڵ�
void insert(TreeNode*& root, int key)
{
	//����ҵ����ĵײ���Ϊ���ݴ���һ���µ����ڵ�
	if (root == nullptr) {
		root = new(std::nothrow) TreeNode(key);
		if (root == NULL) {
			cout << "Ҷ�ӽ���ڴ�����ʧ��" << endl;
			return;
		}
	}
	else if (key < root->data)
		insert(root->left, key);//��
	else if (key > root->data)
		insert(root->right, key);//��
	else
		cout << "���нڵ�" << key << "�����У������ظ����룡" << endl;

}

//����
bool search(TreeNode* root, int key)
{
	if (root == nullptr)//�ڵײ�
		return false; 
	else if (key == root->data)//���
		return true; //�ҵ���
	else if (key < root->data)//С
		return search(root->left, key);//�����
	else //��
		return search(root->right, key);//�ұ���
}

int main()
{

	TreeNode* root = nullptr;//�������ڵ�

	//ѭ���������û��ظ�ִ�й���
	while (true) {
		//����
		system("cls");

		//��ʾ�˵�
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
					cout << "���������" << endl;
					return 0;
				case 'A':
				case 'a':
					cout << "���д�������������" << endl;
					int n;
					cout << "������������ڵ����" << endl;
					n = input<int>(1, INT_MAX);

					for (int i = 0; i < n; ++i) {
						int key;
						cout << "�������" << i + 1 << "���ڵ������" << endl;
						key = input<int>(INT_MIN, INT_MAX);
						insert(root, key);//�ѽڵ��������
					}
					cout << "��ǰ��Ϊ��" << endl;
					treeDisplay(root);
					cout << endl;
					cout << "������ɣ����س�����..." << endl;
					pause();
					break;
				case 'B':
				case 'b':
					cout << "������ӽڵ����" << endl;
					int key;
					cout << "��������������ڵ������" << endl;
					key = input<int>(INT_MIN, INT_MAX);
					insert(root, key);
					cout << "��ǰ��Ϊ��" << endl;
					treeDisplay(root);
					cout << endl;
					cout << "������ɣ����س�����..." << endl;
					pause();
					break;
				case 'c':
				case 'C':
					cout << "ѡ����Ҳ���" << endl;
					int target;
					cout << "������������ҵĽڵ�����" << endl;
					target = input<int>(INT_MIN, INT_MAX);

					if (search(root, target))
						cout << "�ڵ�" << target << "�ѱ��ҵ���" << endl;
					else
						cout << "�ڵ�" << target << "δ���ҵ�" << endl;
					cout << "������ɣ����س�����..." << endl;
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
