#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
using namespace std;


void pause()
{
    while (_getch() != '\r')
        ;
    cout << endl;
}

struct FamilyMember {

    char name[20];
    int age;
    FamilyMember* firstChild;
    FamilyMember* nextSibling;

    FamilyMember() : name(" "), age(0), firstChild(nullptr), nextSibling(nullptr) {}
};

//��ʾ�˵�
void MenuDisplay()
{
    cout << "            ���׹���ϵͳ            " << endl;
    cout << "====================================" << endl;
    cout << "  *         A---��������         *  " << endl;
    cout << "  *         B---��ӳ�Ա         *  " << endl;
    cout << "  *         C---��ɢ�ֲ���ͥ     *  " << endl;
    cout << "  *         D---�޸ĳ�Ա         *  " << endl;
    cout << "  *         Q---�˳�����         *  " << endl;
    cout << "====================================" << endl;
}

void inputname(char* name)
{
    char inputname[20];
    /* Loop to read and process each number from the input */

    while (true) {
        //����һ������
        std::cin >> inputname;
        if (cin.fail()) { // ������
            cout<< "������������������" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
            strcpy_s(inputname, "");
        }
        else if (strlen(inputname) >20) {
            cout << "�������ֳ���������������" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
            strcpy_s(inputname, "");
        }
        else {
            strcpy(name, inputname);
            cin.clear();
            cin.ignore(65535, '\n');
            break;
        }
    }
}


template<typename T>
T input(T l_limit, T U_limit)
{
    T num;
    while (true) {
        cin >> num;
        if (cin.fail() || num < l_limit || num > U_limit) {
            cerr << "������������������" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        else
            return num;
    }
}
class FamilyTree {
private:
    FamilyMember* root;

public:
    //������
    FamilyTree(char* name, int age)
    {
        root = new FamilyMember;
        if (root == NULL) {
            std::cout << "�����ڴ�����ʧ��" << std::endl;
            return;
        }
        strcpy_s(root->name, name);
        root->age = age;
    }
   
    //��һ����Ա��Ӻ���
    void addChild(char* parentName, char* childName, int childAge)
    {
        FamilyMember* parent = findMember(root, parentName);
        if (parent == nullptr) {
            cout << "δ�ҵ�˫��" << endl;
            return;
        }
        if (parent->firstChild == nullptr) {
            parent->firstChild = new FamilyMember;
            if (parent->firstChild == NULL) {
                cout << "�����ڴ�����ʧ��" << endl;
                return;
            }
            parent->firstChild->age = childAge;
            strcpy_s(parent->firstChild->name, childName);
        }
        else {
            FamilyMember* sibling = parent->firstChild;
            while (sibling->nextSibling != nullptr) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = new FamilyMember;
            if (sibling->nextSibling == NULL) {
                cout << "�����ڴ�����ʧ��" << endl;
                return;
            }
            sibling->nextSibling->age = childAge;
            strcpy_s(sibling->nextSibling->name, childName);
            sibling->nextSibling->nextSibling = nullptr;
        }
        cout << "��" << childName << "���뵽" << parentName << "�ļ�ͥ" << endl;
    }


    //ͨ�����ּ���һ����Ա
    FamilyMember* findMember(FamilyMember* current, char* name)
    {
        if (current == nullptr) {
            return nullptr;
        }
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        FamilyMember* foundInChildren = findMember(current->firstChild, name);
        if (foundInChildren != nullptr) {
            return foundInChildren;
        }
        return findMember(current->nextSibling, name);
    }

    //ͨ��������˫��
    FamilyMember* findParent(FamilyMember* start, char* childName)
    {
        if (start == nullptr) {
            return nullptr;
        }

        FamilyMember* child = start->firstChild;
        while (child != nullptr) {
            if (strcmp(child->name, childName) == 0) {
                return start;
            }
            FamilyMember* parent = findParent(child, childName);
            if (parent != nullptr) {
                return parent;
            }
            child = child->nextSibling;
        }

        return nullptr;
    }


    //��ӡ����
    void printFamilyTree(FamilyMember* current, int level)
    {
        if (current == nullptr) {
            return;
        }
        for (int i = 0; i < level; i++) {
            std::cout << "--";
        }
        std::cout << "|_" << current->name << " (" << current->age << ")" << std::endl;
        printFamilyTree(current->firstChild, level + 1);
        printFamilyTree(current->nextSibling, level);
    }

    FamilyMember* getRoot()
    {
        return root;
    }

    //�޸Ľڵ���Ϣ
    void modifyMember(char* name, char* newName, int newAge)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            strcpy_s(member->name, newName);
            member->age = newAge;
            cout << "�޸���" << name << "����Ϣ" << endl;
        }
        else {
            cout << "δ�ҵ��ó�Ա" << endl;
        }
    }

    //ɾ��һ����Ա
    void deleteSubtree(FamilyMember* member)
    {
        if (member == nullptr) {
            return;
        }
        FamilyMember* child;
        child = member->firstChild;
        while (child != NULL) {
            FamilyMember* temp;
            temp = child->nextSibling;
            deleteSubtree(child);
            child = temp;
        }

        delete member;
    }

    //��ɢ��ͥ
    void disbandFamily(char* name)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            if (member == root) {
                cout << "���ܽ�ɢ������ͥ" << endl;
                return;
            }
            FamilyMember* parent = findParent(root, member->name);
            if (parent->firstChild == member)
                parent->firstChild = parent->firstChild->nextSibling;
            else {
                FamilyMember* child = parent->firstChild;
                while (child->nextSibling != member) {
                    child = child->nextSibling;
                }
                child->nextSibling = child->nextSibling->nextSibling;
            }
            deleteSubtree(member);
            cout << "�ѽ�ɢ" << name << "�ļ�ͥ" << endl;
        }
        else {
            cout << "δ�ҵ��ó�Ա" << endl;
        }
    }
};

int main() {

    //��ʾ�˵�
    MenuDisplay();

    while (true) {
        char controller = _getch();
        if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
            cout << controller << endl;
            switch (controller)
            {
            case 'q':
            case 'Q':
                cout << "���������" <<endl;
                return 0;
            case 'a':
            case 'A':
                break;
            default:
                cout << "���Ƚ������ף�" << endl;
                continue;
            }
            break;
        }
    }

    int Ancestorsage;
    char AncestorsName[20];
    cout << "��������������" << endl;
    inputname(AncestorsName);
    cout << "��������������" << endl;
    Ancestorsage = input<int>(0, 100000000);

    FamilyTree family(AncestorsName, Ancestorsage);

    family.printFamilyTree(family.getRoot(), 0);
    cout << endl;
    cout << "���β�����ɣ����س���������һ�ֲ���...";
    pause();

    while (true) {

        system("cls");

        MenuDisplay();


        char controller;//����һ���������������ǵ�ѡ��
        while (true) {
            controller = _getch();//
            if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
                cout << controller <<endl;
                switch (controller)
                {
                case 'q':
                case 'Q':
                    cout << "���������" << endl;
                    return 0;

                case 'a':
                case 'A':
                    cout << "�����ظ��������ף�" << endl;
                    cout << endl;
                    cout << "���β�����ɣ����س���������һ�ֲ���...";
                    pause();
                    break;

                case 'b':
                case 'B':
                    cout << "ѡ���� B---��ӳ�Ա��������ӳ�Ա����" << endl;
                    {
                        int age;
                        char Pname[20];
                        char Nname[20];
                        cout << "������˫������" << endl;
                        inputname(Pname);
                        cout << "����������ӳ�Ա����" << endl;
                        inputname(Nname);
                        cout << "����������ӳ�Ա����" << endl;
                        age = input<int>(0, 100000000);
                        family.addChild(Pname, Nname, age);
                    }
                    family.printFamilyTree(family.getRoot(), 0);
                    cout << endl;
                    cout << "���β�����ɣ����س���������һ�ֲ���...";
                    pause();
                    break;
                case 'c':
                case 'C':
                    std::cout << "ѡ���� C---��ɢ�ֲ���ͥ�����н�ɢ�ֲ���ͥ����" << std::endl;
                    {
                        char name[20];
                        cout << "�������ɢ�ֲ���ͥ��Ա����" << endl;
                        inputname(name);
                        family.disbandFamily(name);
                        family.printFamilyTree(family.getRoot(), 0);
                    }
                    cout << endl;
                    cout << "���β�����ɣ����س���������һ�ֲ���...";
                    pause();
                    break;
                case 'D':
                case 'd':
                    cout << "ѡ���� D---�޸ĳ�Ա�������޸ĳ�Ա����" << endl;
                    {
                        int age;
                        char name[20];
                        char Nname[20];
                        cout << "�������޸ĳ�Աԭ����" << endl;
                        inputname(name);
                        cout << "�������޸ĳ�Ա������" << endl;
                        inputname(Nname);
                        cout << "�������޸ĳ�Ա������" << endl;
                        age = input<int>(0, 100000000);
                        family.modifyMember(name, Nname, age);
                        family.printFamilyTree(family.getRoot(), 0);
                    }
                    cout << endl;
                    cout << "���β�����ɣ����س���������һ�ֲ���...";
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



