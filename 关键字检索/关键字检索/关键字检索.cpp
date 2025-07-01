#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string fileName;
    cout << "请输入文件名（包括扩展名，比如file.txt）：";
    cin >> fileName;

    // 创建一个输出文件流
    ofstream file(fileName);

    if (!file) {
        cout << "无法创建文件！" << endl;
        return 1;
    }

    cout << "请输入一段英文，以回车结束：" << endl;

    // 读取用户输入的文本内容并写入文件
    string line;
    while (getline(cin, line)) {
        file << line << endl;  // 写入一行文本并换行
        if (getchar() == '\n')
            break;

    }

    file.close(); // 关闭文件流

    string keyword;
    cout << "请输入要检索的关键字：";
    cin >> keyword;

    // 重新打开文件以读取内容
    ifstream readFile(fileName);

    if (!readFile) {
        cout << "无法打开文件！" << std::endl;
        return 1;
    }

    string word;
    int count = 0;

    // 逐个单词读取文件内容并统计关键字出现次数
    while (readFile >> word) {
        if (word == keyword) {
            count++;
        }
    }

    cout << "在源文件中共检索到: " << count << "个关键字 '" << keyword << "'"<<endl;

    readFile.close(); // 关闭文件流

    return 0;
}
