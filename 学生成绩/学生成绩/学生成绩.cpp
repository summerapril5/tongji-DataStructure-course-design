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
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (current->candidate_number <= 0 )
		{
			cout << "考号输入错误，请重新输入。" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (!(strcmp(current->gender, "男") == 0 || strcmp(current->gender, "女") == 0))
		{
			cout << "性别输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			clear(current);
		}
		else if (current->age <= 10 && current->age >= 80)
		{
			cout << "年龄不合理，请重新输入" << endl;
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
			std::cout << "链表内存申请失败!" << std::endl;
			return;
		}

	}

	

	bool input()
	{
		if (head == NULL) {
			std::cerr << "建立链表时内存申请失败，程序结束" << std::endl;
			return 0;
		}
		cout << "首先请建立考生信息系统！" << endl;
		cout << "请输入考生人数：" << endl;
		int people_number;
		while (1)
		{
			cin >> people_number;
			if (cin.fail()|| people_number<=0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else 
				break;
		}

		
		cout << "请依次输入考生考号，姓名，性别，年龄及报考类别：" << endl;
		head->next = new information;
		input_information(head->next);

		information* last = head->next;

		for (int i = 0; i < people_number - 1; i++) {
			information* current = new  information;
			if (current == NULL) {
				std::cerr << "建立链表时内存申请失败，程序结束" << std::endl;
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
		cout << setiosflags(ios::left) << setw(10) << "考号"
			<< setw(10) << "姓名" << setw(5) << "性别" << setw(5) << "年龄" << setw(20) << "报考类别" << endl;
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
		cout << "请输入你要插入考生的位置：" ;
		int position;
		while (1)
		{
			cin >> position;
			if (cin.fail() || position <= 0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		information* current = head;
		for (int i = 0; i < position - 1; i++, current = current->next) {
			if (current->next == NULL) {
				cout << "当前位置无法插入元素" << endl;
				break;
			}
		}

		cout << "依次输入考生的考号，姓名，性别，年龄及报考类别:" << endl;

		information* newlist = new information;
		input_information(newlist);

		information* p;
		p = current->next;
		current->next = newlist;
		newlist->next = p;
	}

	void delete1()
	{
		cout << "请输入你要删除考生的考号：" ;
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "删除以下学生信息:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "考号"
					<< setw(10) << "姓名" << setw(5) << "性别" << setw(5) << "年龄" << setw(20) << "报考类别" << endl;

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
		cout << "请输入你要查找考生的考号：";
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "您查找的学生信息是:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "考号"
					<< setw(10) << "姓名" << setw(5) << "性别" << setw(5) << "年龄" << setw(20) << "报考类别" << endl;

				cout << setiosflags(ios::left) << setw(10) << current->next->candidate_number
					<< setw(10) << current->next->name << setw(5) << current->next->gender << setw(5)
					<< current->next->age << current->next->category << endl;

			}
		}
	}

	void change()
	{
		cout << "请输入你要修改考生的考号：";
		int number;
		while (1)
		{
			cin >> number;
			if (cin.fail() || number <= 0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}

		for (information* current = head; current->next != NULL; current = current->next)
		{
			if (current->next->candidate_number == number) {
				cout << "修改以下学生信息:" << endl;
				cout << setiosflags(ios::left) << setw(10) << "考号"
					<< setw(10) << "姓名" << setw(5) << "性别" << setw(5) << "年龄" << setw(20) << "报考类别" << endl;

				cout << setiosflags(ios::left) << setw(10) << current->next->candidate_number
					<< setw(10) << current->next->name << setw(5) << current->next->gender << setw(5)
					<< current->next->age << current->next->category << endl;

				cout << "依次输入修改后考生的考号，姓名，性别，年龄及报考类别！" << std::endl;
				input_information(current->next);

			}
		}
	}

	void statistics()
	{
		int cal_male = 0; int cal_female = 0;
		for (information* current = head->next; current != NULL; current = current->next) {
			if (std::strcmp(current->gender, "男") == 0) {
				cal_male++;
			}
			else
				cal_female++;
		}
		cout << "统计结果为：一共有" << cal_male + cal_female << "人，其中男生有" << cal_male << "人，女生有" << cal_female << "人" << endl;

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
		cout << "链表建立失败，请重新进行程序" << endl;
		return 0;
	}
	else{ 
	}

	list.display();

	while (1) {
		cout << "请选择您想进行的操作：（0为退出，1为插入，2为删除，3为查找，4为修改，5为统计）:" ;
		char input = 'a';
		cin >> input;
		switch (input)
		{
		case'0':
			cout << "程序结束"<<endl;
			return 0;
		case'1':
			list.insert();
			list.display();
			cout << "操作结束，请继续选择操作"<<endl;
			continue;
		case'2':
			list.delete1();
			list.display();
			cout << "操作结束，请继续选择操作" << endl;
			continue;
		case'3':
			list.search();
			cout << "操作结束，请继续选择操作" << endl;
			continue;
		case'4':
			list.change();
			cout << "修改后的考生信息为：";
			list.display();
			cout << "操作结束，请继续选择操作" << endl;
			continue;
		case'5':
			list.statistics();
			cout << "操作结束，请继续选择操作" << endl;
			continue;
		default:
			cout << "输入错误，请重新进行" << endl;
		}
	}
	return 0;
}