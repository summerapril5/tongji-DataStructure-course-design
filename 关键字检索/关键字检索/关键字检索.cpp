#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string fileName;
    cout << "�������ļ�����������չ��������file.txt����";
    cin >> fileName;

    // ����һ������ļ���
    ofstream file(fileName);

    if (!file) {
        cout << "�޷������ļ���" << endl;
        return 1;
    }

    cout << "������һ��Ӣ�ģ��Իس�������" << endl;

    // ��ȡ�û�������ı����ݲ�д���ļ�
    string line;
    while (getline(cin, line)) {
        file << line << endl;  // д��һ���ı�������
        if (getchar() == '\n')
            break;

    }

    file.close(); // �ر��ļ���

    string keyword;
    cout << "������Ҫ�����Ĺؼ��֣�";
    cin >> keyword;

    // ���´��ļ��Զ�ȡ����
    ifstream readFile(fileName);

    if (!readFile) {
        cout << "�޷����ļ���" << std::endl;
        return 1;
    }

    string word;
    int count = 0;

    // ������ʶ�ȡ�ļ����ݲ�ͳ�ƹؼ��ֳ��ִ���
    while (readFile >> word) {
        if (word == keyword) {
            count++;
        }
    }

    cout << "��Դ�ļ��й�������: " << count << "���ؼ��� '" << keyword << "'"<<endl;

    readFile.close(); // �ر��ļ���

    return 0;
}
