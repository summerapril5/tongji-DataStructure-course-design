#include <iostream>
using namespace std;

//��������ѭ������
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
//�����������
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
//ɾ��������ֵ��
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
//��ӡ����
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

	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�����ֱ��ʣ��K����Ϊֹ" << endl<<endl;
	int N=0, S=0, M=0, K=0;
	cout << "��ǰ��Ϸ����N(10-50):";
	while(1)
	{
		cin >> N;
		if (cin.fail() || N < 10 || N>50)
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "��ǰ��ʼλ��S:" ;
	while (1)
	{
		cin >> S;
		if (cin.fail() || S <=0 || S>N)
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "��ǰ��������M:" ;
	while (1)
	{
		cin >> M;
		if (cin.fail() || M<= 0 || M> N)
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	cout << "��ǰ�������K:" ;
	while (1)
	{
		cin >> K;
		if (cin.fail() || K <= 0 || K >= N)
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}

	//�������в���1~N
	list* L = list_init();
	for (int i = 0; i < N; i++)
	{
		list_insert(L, i, i + 1);
	}
	
	//��ʼ���Լɪ������
	cout  << endl;
	node* pcurrent = L->head;
	int iter = 1;
	for (int i = 0; i < S ; i++)
	{
		if (pcurrent == L->head)  //�ų�ͷnode
		{
			pcurrent = pcurrent->next;
		}
		pcurrent = pcurrent->next;
		if (pcurrent == L->head) //�ų�ͷnode
		{
			pcurrent = pcurrent->next;
		}
	}
	while (L->size != 0)
	{
		for (int i = 0; i < M-1; i++)
		{
			if (pcurrent == L->head)  //�ų�ͷnode
			{
				pcurrent = pcurrent->next;
			}
			pcurrent = pcurrent->next;
			if (pcurrent == L->head) //�ų�ͷnode
			{
				pcurrent = pcurrent->next;
			}
		}
		cout << "��" << iter << "�����ߵ�λ���ǣ�" << pcurrent->data << endl;
		//node* temp_p=pcurrent;
		list_delete(L, pcurrent->data);
		pcurrent = pcurrent->next;
		iter++;
		if (iter == N-K+1)
			break;
	}

	cout << endl;
	cout << "���ʣ��" << K << "��" << endl;
	cout << "ʣ������λ�ã�" << endl;
	list_print(L, K);

	system("pause");
	return 0;
}