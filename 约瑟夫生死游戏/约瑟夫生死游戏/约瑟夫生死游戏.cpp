#include <iostream>
using namespace std;

//创建单向循环链表
class node
{
public:
	int data;
	node* next;
};
class list
{
public:
	int size;
	node* head;
};
list* list_init()
{
	list* L = new list;
	L->size = 0;
	L->head = new node;
	L->head->data = NULL;
	L->head->next = L->head;
	return L;
}
//链表插入数据
void list_insert(list* L, int pos, int num)
{
	node* new_node = new node;
	new_node->data = num;
	new_node->next = NULL;

	node* pcurrent = L->head;
	for (int i = 0; i < pos; i++)
	{
		pcurrent = pcurrent->next;
	}
	new_node->next = pcurrent->next;
	pcurrent->next = new_node;
	L->size++;
}
//删除链表（按值）
void list_delete(list* L, int num)
{
	node* pcurrent = L->head->next;
	int pos = 0;
	for (int i = 0; i < L->size; i++)
	{
		if (pcurrent->data == num)
		{
			break;
		}
		pcurrent = pcurrent->next;
		pos++;
	}
	pcurrent = L->head;
	for (int i = 0; i < pos; i++)
	{
		pcurrent = pcurrent->next;
	}
	pcurrent->next = pcurrent->next->next;
	L->size--;
}
//打印链表
void list_print(list* L, int num)
{
	node* pcurrent = L->head;
	for (int i = 0; i < num; i++)
	{
		if (pcurrent == L->head)
		{
			pcurrent = pcurrent->next;
		}
		cout << pcurrent->data << "\t";
		pcurrent = pcurrent->next;
	}
	cout << endl;
}


int main()
{

	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开环，直至剩下K不人为止" << endl<<endl;
	int N=0, S=0, M=0, K=0;
	cout << "当前游戏人数N(10-50):";
	while(1)
	{
		cin >> N;
		if (cin.fail() || N < 10 || N>50)
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "当前开始位置S:" ;
	while (1)
	{
		cin >> S;
		if (cin.fail() || S <=0 || S>N)
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "当前死亡数字M:" ;
	while (1)
	{
		cin >> M;
		if (cin.fail() || M<= 0 || M> N)
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "当前存活人数K:" ;
	while (1)
	{
		cin >> K;
		if (cin.fail() || K <= 0 || K >= N)
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	//在链表中插入1~N
	list* L = list_init();
	for (int i = 0; i < N; i++)
	{
		list_insert(L, i, i + 1);
	}
	
	//开始解决约瑟夫问题
	cout  << endl;
	node* pcurrent = L->head;
	int iter = 1;
	for (int i = 0; i < S ; i++)
	{
		if (pcurrent == L->head)  //排除头node
		{
			pcurrent = pcurrent->next;
		}
		pcurrent = pcurrent->next;
		if (pcurrent == L->head) //排除头node
		{
			pcurrent = pcurrent->next;
		}
	}
	while (L->size != 0)
	{
		for (int i = 0; i < M-1; i++)
		{
			if (pcurrent == L->head)  //排除头node
			{
				pcurrent = pcurrent->next;
			}
			pcurrent = pcurrent->next;
			if (pcurrent == L->head) //排除头node
			{
				pcurrent = pcurrent->next;
			}
		}
		cout << "第" << iter << "个死者的位置是：" << pcurrent->data << endl;
		//node* temp_p=pcurrent;
		list_delete(L, pcurrent->data);
		pcurrent = pcurrent->next;
		iter++;
		if (iter == N-K+1)
			break;
	}

	cout << endl;
	cout << "最后剩下" << K << "人" << endl;
	cout << "剩余生者位置：" << endl;
	list_print(L, K);

	system("pause");
	return 0;
}