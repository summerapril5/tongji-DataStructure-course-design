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

//显示菜单
void MenuDisplay()
{
    cout << "            家谱管理系统            " << endl;
    cout << "====================================" << endl;
    cout << "  *         A---建立家谱         *  " << endl;
    cout << "  *         B---添加成员         *  " << endl;
    cout << "  *         C---解散局部家庭     *  " << endl;
    cout << "  *         D---修改成员         *  " << endl;
    cout << "  *         Q---退出程序         *  " << endl;
    cout << "====================================" << endl;
}

void inputname(char* name)
{
    char inputname[20];
    /* Loop to read and process each number from the input */

    while (true) {
        //读入一个名字
        std::cin >> inputname;
        if (cin.fail()) { // 错误处理
            cout<< "输入有误，请重新输入" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
            strcpy_s(inputname, "");
        }
        else if (strlen(inputname) >20) {
            cout << "输入名字超长，请重新输入" << endl;
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
            cerr << "输入有误，请重新输入" << endl;
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
    //建立树
    FamilyTree(char* name, int age)
    {
        root = new FamilyMember;
        if (root == NULL) {
            std::cout << "家谱内存申请失败" << std::endl;
            return;
        }
        strcpy_s(root->name, name);
        root->age = age;
    }
   
    //向一个成员添加孩子
    void addChild(char* parentName, char* childName, int childAge)
    {
        FamilyMember* parent = findMember(root, parentName);
        if (parent == nullptr) {
            cout << "未找到双亲" << endl;
            return;
        }
        if (parent->firstChild == nullptr) {
            parent->firstChild = new FamilyMember;
            if (parent->firstChild == NULL) {
                cout << "家谱内存申请失败" << endl;
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
                cout << "家谱内存申请失败" << endl;
                return;
            }
            sibling->nextSibling->age = childAge;
            strcpy_s(sibling->nextSibling->name, childName);
            sibling->nextSibling->nextSibling = nullptr;
        }
        cout << "将" << childName << "加入到" << parentName << "的家庭" << endl;
    }


    //通过名字检索一个成员
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

    //通过孩子找双亲
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


    //打印家谱
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

    //修改节点信息
    void modifyMember(char* name, char* newName, int newAge)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            strcpy_s(member->name, newName);
            member->age = newAge;
            cout << "修改了" << name << "的信息" << endl;
        }
        else {
            cout << "未找到该成员" << endl;
        }
    }

    //删除一个成员
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

    //解散家庭
    void disbandFamily(char* name)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            if (member == root) {
                cout << "不能解散整个家庭" << endl;
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
            cout << "已解散" << name << "的家庭" << endl;
        }
        else {
            cout << "未找到该成员" << endl;
        }
    }
};

int main() {

    //显示菜单
    MenuDisplay();

    while (true) {
        char controller = _getch();
        if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
            cout << controller << endl;
            switch (controller)
            {
            case 'q':
            case 'Q':
                cout << "程序结束！" <<endl;
                return 0;
            case 'a':
            case 'A':
                break;
            default:
                cout << "请先建立家谱！" << endl;
                continue;
            }
            break;
        }
    }

    int Ancestorsage;
    char AncestorsName[20];
    cout << "请输入祖先姓名" << endl;
    inputname(AncestorsName);
    cout << "请输入祖先年龄" << endl;
    Ancestorsage = input<int>(0, 100000000);

    FamilyTree family(AncestorsName, Ancestorsage);

    family.printFamilyTree(family.getRoot(), 0);
    cout << endl;
    cout << "本次操作完成，按回车键进行新一轮操作...";
    pause();

    while (true) {

        system("cls");

        MenuDisplay();


        char controller;//创建一个变量来保存我们的选择
        while (true) {
            controller = _getch();//
            if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
                cout << controller <<endl;
                switch (controller)
                {
                case 'q':
                case 'Q':
                    cout << "程序结束！" << endl;
                    return 0;

                case 'a':
                case 'A':
                    cout << "不可重复建立家谱！" << endl;
                    cout << endl;
                    cout << "本次操作完成，按回车键进行新一轮操作...";
                    pause();
                    break;

                case 'b':
                case 'B':
                    cout << "选择了 B---添加成员，进行添加成员操作" << endl;
                    {
                        int age;
                        char Pname[20];
                        char Nname[20];
                        cout << "请输入双亲姓名" << endl;
                        inputname(Pname);
                        cout << "请输入新添加成员姓名" << endl;
                        inputname(Nname);
                        cout << "请输入新添加成员年龄" << endl;
                        age = input<int>(0, 100000000);
                        family.addChild(Pname, Nname, age);
                    }
                    family.printFamilyTree(family.getRoot(), 0);
                    cout << endl;
                    cout << "本次操作完成，按回车键进行新一轮操作...";
                    pause();
                    break;
                case 'c':
                case 'C':
                    std::cout << "选择了 C---解散局部家庭，进行解散局部家庭操作" << std::endl;
                    {
                        char name[20];
                        cout << "请输入解散局部家庭成员姓名" << endl;
                        inputname(name);
                        family.disbandFamily(name);
                        family.printFamilyTree(family.getRoot(), 0);
                    }
                    cout << endl;
                    cout << "本次操作完成，按回车键进行新一轮操作...";
                    pause();
                    break;
                case 'D':
                case 'd':
                    cout << "选择了 D---修改成员，进行修改成员操作" << endl;
                    {
                        int age;
                        char name[20];
                        char Nname[20];
                        cout << "请输入修改成员原姓名" << endl;
                        inputname(name);
                        cout << "请输入修改成员现姓名" << endl;
                        inputname(Nname);
                        cout << "请输入修改成员现年龄" << endl;
                        age = input<int>(0, 100000000);
                        family.modifyMember(name, Nname, age);
                        family.printFamilyTree(family.getRoot(), 0);
                    }
                    cout << endl;
                    cout << "本次操作完成，按回车键进行新一轮操作...";
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



