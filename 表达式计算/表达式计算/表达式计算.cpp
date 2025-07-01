#include <iostream>
using namespace std;

//树节点类
class TreeNode {
public:
    int data;
    char op;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data, char val) : data(data), op(val), left(nullptr), right(nullptr) {}
};


class MyStack {
private:
    TreeNode** data;
    int capacity;
    int top;

public:
    MyStack(int cap); //初始化栈堆（动态申请一个空间）
    ~MyStack();
    void push(TreeNode* node);//把一个树节点压入栈中
    TreeNode* pop();//Pop出树节点
    TreeNode* peek();
    bool isEmpty();//检查栈是否为空
};

//初始化栈堆
MyStack::MyStack(int cap) : capacity(cap), top(-1)
{
    data = new(std::nothrow) TreeNode * [capacity];
    if (data == NULL) {
        cout << "栈内存申请失败！" << endl;
        return;
    }
}


MyStack::~MyStack()
{
    delete[] data;
}


void MyStack::push(TreeNode* node)
{
    if (data == NULL) {
        cout << "当前栈不存在" << endl;
        return;
    }
    if (top < capacity - 1)
        data[++top] = node;
}


TreeNode* MyStack::pop()
{
    if (data == NULL) {
        cout << "当前栈不存在" << endl;
        return NULL;
    }
    if (top >= 0)
        return data[top--];
    return nullptr; 
}


TreeNode* MyStack::peek()
{
    if (data == NULL) {
        cout << "当前栈不存在" << endl;
        return NULL;
    }
    if (top >= 0)
        return data[top];
    return nullptr; 
}

//检查栈是否为空
bool MyStack::isEmpty()
{
    if (data == NULL) {
        cout << "当前栈不存在" << endl;
        return false;
    }
    return top == -1;
}

//检查是否为操作符
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//计算运算符的优先级
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

//创建表达式树
TreeNode* createExpressionTree(const char* expression, int& pos)
{
    MyStack nodes(100); //最大容量为100
    MyStack operators(100); // 承装操作符的栈

    while (expression[pos] != '\0') {

        char token = expression[pos];

        if (isdigit(token)) {
            int operand = 0;//计算它的值

            while (isdigit(expression[pos])) {
                operand = operand * 10 + (expression[pos] - '0');
                ++pos;
            } 
            TreeNode* operandNode = new TreeNode(operand, '\0');//创建树节点去储存它
            nodes.push(operandNode);//把其push进节点
        }
        else if (isOperator(token)) {
            //如果运算符堆栈不为空，并且我们正在检查的运算符在前
            while (!operators.isEmpty() && getPrecedence(operators.peek()->op) >= getPrecedence(token)) {
                TreeNode* operatorNode = operators.pop();//获取运算符顶部元素
                TreeNode* rightNode = nodes.pop();
                TreeNode* leftNode = nodes.pop();
                operatorNode->left = leftNode;//连接两个元素
                operatorNode->right = rightNode;
                nodes.push(operatorNode);//把运算符节点push进节点栈
            }
            
            TreeNode* operatorNode = new TreeNode(0, token);
            operators.push(operatorNode);
            ++pos;
        }
        else if (token == '(') {
            ++pos;
            TreeNode* subexpression = createExpressionTree(expression, pos); //创建一个子表达式并使其成为节点
            ++pos; 
            nodes.push(subexpression);
        }
        else if (token == ')')
            break;
        else
            ++pos;//读入空
    }
    //处理，直到运算符堆栈为空
    while (!operators.isEmpty()) {
        TreeNode* operatorNode = operators.pop();//获取运算符顶部元素
        TreeNode* rightNode = nodes.pop();
        TreeNode* leftNode = nodes.pop();
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;
        nodes.push(operatorNode);//把运算符节点push进节点栈
    }

    return nodes.pop();//此堆栈中将只有一个根树节点
}

//前序遍历打印树
void printorder(TreeNode* root) {
    if (root) {
        if (root->op != '\0')
            cout << root->op << ' ';
        else
            cout << root->data << ' ';
        printorder(root->left);
        printorder(root->right);
    }
}

//中序遍历打印树
void printInorder(TreeNode* root) {
    if (root) {
        printInorder(root->left);
        if (root->op != '\0')
            cout << root->op << ' ';
        else
            cout << root->data << ' ';
        printInorder(root->right);
    }
}

//后序遍历打印树
void printPostorder(TreeNode* root) {
    if (root) {
        printPostorder(root->left);
        printPostorder(root->right);
        if (root->op != '\0')
            cout << root->op << ' ';
        else
            cout << root->data << ' ';
    }
}

//计算结果
int evaluateExpression(TreeNode* root) {
    if (!root) //没有直接return
        return 0;

    if (root->op == '\0') //读入数字就返回它
        return root->data;


    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    //读入操作符
    switch (root->op) {
        
    case '+':
        return leftValue + rightValue;
    case '-':
        return leftValue - rightValue;
    case '*':
        return leftValue * rightValue;
    case '/':
        if (rightValue != 0) {
            return leftValue / rightValue;
        }
        else {
            cout << "零不能作为除数！" << endl;
            exit(1);
        }
    }

    return 0; 
}

int main() {

    char infixExpression[100];
    cout << "请输入表达式" << endl;
    cin.getline(infixExpression, 100);

    int pos = 0;
    TreeNode* expressionTree = createExpressionTree(infixExpression, pos);

    cout << "原表达式: " << infixExpression << endl;
    cout << "中序表达式: ";
    printInorder(expressionTree);
    cout << endl;

    cout << "逆波兰式: ";
    printPostorder(expressionTree);
    cout << endl;

    cout << "波兰表达式: ";
    printorder(expressionTree);
    cout << endl;

    int result = evaluateExpression(expressionTree);
    cout << "结果: " << result << endl;


    return 0;
}
