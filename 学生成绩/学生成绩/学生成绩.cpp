#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <iomanip>
#include <list>
using namespace std;

struct information
{
	int candidate_number;
	char name[8];
	char gender[3];
	int age;
	char category[20];
	information* next;
}s1;

void clear(information* current)
{
	current->candidate_number = 0;
	strcpy(current->name, "");
	strcpy(current->gender, "");
	strcpy(current->category, "");
	current->age = 0;
	current->next = NULL;
}

void input_information(information* current)
{

	while (1)
	{
		cin >> current->candidate_number >> current->name >> current->gender >> current->age >> current->category;

		if (cin.fail())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (current->candidate_number <= 0 )
		{
			cout << "��������������������롣" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (!(strcmp(current->gender, "��") == 0 || strcmp(current->gender, "Ů") == 0))
		{
			cout << "�Ա������������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (current->age <= 10 && current->age >= 80)
		{
			cout << "���䲻��������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else
		{
			break;
		}
	}
}

class ExamRegistrationSystem {
private:
	information* head=new information;

public:
	ExamRegistrationSystem()
	{
		head = new information;//Create a head node;
		if (head == NULL) {
			std::cout << "�����ڴ�����ʧ��!" << std::endl;
			return;
		}

	}

	

	bool input()
	{
		if (head == NULL) {
			std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
			return 0;
		}
		cout << "�����뽨��������Ϣϵͳ��" << endl;
		cout << "�����뿼��������" << endl;
		int people_number;
		while (1)
		{
			cin >> people_number;
			if (cin.fail()|| people_number<=0) {
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else 
				break;
		}

		
		cout << "���������뿼�����ţ��������Ա����估�������" << endl;
		head->next = new information;
		input_information(head->next);

		information* last = head->next;

		for (int i = 0; i < people_number - 1; i++) {
			information* current = new  information;
			if (current == NULL) {
				std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
				return 0;
			}
			last->next = current;
			input_information(current);
			last = current;
		}

		last->next = NULL;


		return 1;
	}

	void display()
	{	
		information* current=head->next;
		cout << endl;
		cout << setiosflags(ios::left) << setw(10) << "����"
			<< setw(10) << "����" << setw(5) << "�Ա�" << setw(5) << "����" << setw(20) << "�������" << endl;
	    while (current)
		{
			cout << setiosflags(ios::left) << setw(10) << current->candidate_number
				<< setw(10) << current->name << setw(5) << current->gender << setw(5)
				<< current->age << current->category << endl;
			
			current = current->next;
		}
		cout << endl;
	}

	void insert()
	{
		cout << "��������Ҫ���뿼����λ�ã�" ;
		int position;
		while (1)
		{
			cin >> position;
			if (cin.fail() || position <= 0) {
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		information* current = head;
		for (int i = 0; i < position - 1; i++, current = current->next) {
			if (current->next == NULL) {
				cout << "��ǰλ���޷�����Ԫ��" << endl;
				break;
			}
		}

		cout << "�������뿼���Ŀ��ţ��������Ա����估�������:" << endl;

		information* newlist = new information;
		input_information(newlist);

		information* p;
		p = current->next;
		current->next = newlist;
		newlist->next = p;
	}

	void delete1()
	{
		cout << "��������Ҫɾ�������Ŀ��ţ�" ;
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "ɾ������ѧ����Ϣ:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "����"
					<< setw(10) << "����" << setw(5) << "�Ա�" << setw(5) << "����" << setw(20) << "�������" << endl;

				cout << setiosflags(ios::left) << setw(10) << current->next->candidate_number
					<< setw(10) << current->next->name << setw(5) << current->next->gender << setw(5)
					<< current->next->age << current->next->category << endl;

				information* p = current->next->next;
				delete current->next;
				current->next = p;
			}
		}

	}

	void search()
	{
		cout << "��������Ҫ���ҿ����Ŀ��ţ�";
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "�����ҵ�ѧ����Ϣ��:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "����"
					<< setw(10) << "����" << setw(5) << "�Ա�" << setw(5) << "����" << setw(20) << "�������" << endl;

				cout << setiosflags(ios::left) << setw(10) << current->next->candidate_number
					<< setw(10) << current->next->name << setw(5) << current->next->gender << setw(5)
					<< current->next->age << current->next->category << endl;

			}
		}
	}

	void change()
	{
		cout << "��������Ҫ�޸Ŀ����Ŀ��ţ�";
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "�޸�����ѧ����Ϣ:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "����"
					<< setw(10) << "����" << setw(5) << "�Ա�" << setw(5) << "����" << setw(20) << "�������" << endl;

				cout << setiosflags(ios::left) << setw(10) << current->next->candidate_number
					<< setw(10) << current->next->name << setw(5) << current->next->gender << setw(5)
					<< current->next->age << current->next->category << endl;

				cout << "���������޸ĺ����Ŀ��ţ��������Ա����估�������" << std::endl;
				input_information(current->next);

			}
		}
	}

	void statistics()
	{
		int cal_male = 0; int cal_female = 0;
		for (information* current = head->next; current != NULL; current = current->next) {
			if (std::strcmp(current->gender, "��") == 0) {
				cal_male++;
			}
			else
				cal_female++;
		}
		cout << "ͳ�ƽ��Ϊ��һ����" << cal_male + cal_female << "�ˣ�����������" << cal_male << "�ˣ�Ů����" << cal_female << "��" << endl;

	}

	~ExamRegistrationSystem()
	{
		for (information* current = head; current != NULL;) {
			information* temp = current->next;
			delete current;
			current = temp;
		}
	}

};

int main()
{
	
	ExamRegistrationSystem list;

	bool a=list.input();
	if (a == 0)
	{
		cout << "������ʧ�ܣ������½��г���" << endl;
		return 0;
	}
	else{ 
	}

	list.display();

	while (1) {
		cout << "��ѡ��������еĲ�������0Ϊ�˳���1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�:" ;
		char input = 'a';
		cin >> input;
		switch (input)
		{
		case'0':
			cout << "�������"<<endl;
			return 0;
		case'1':
			list.insert();
			list.display();
			cout << "���������������ѡ�����"<<endl;
			continue;
		case'2':
			list.delete1();
			list.display();
			cout << "���������������ѡ�����" << endl;
			continue;
		case'3':
			list.search();
			cout << "���������������ѡ�����" << endl;
			continue;
		case'4':
			list.change();
			cout << "�޸ĺ�Ŀ�����ϢΪ��";
			list.display();
			cout << "���������������ѡ�����" << endl;
			continue;
		case'5':
			list.statistics();
			cout << "���������������ѡ�����" << endl;
			continue;
		default:
			cout << "������������½���" << endl;
		}
	}
	return 0;
}