#include <iostream>
using namespace std;

//���ڵ���
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
    MyStack(int cap); //��ʼ��ջ�ѣ���̬����һ���ռ䣩
    ~MyStack();
    void push(TreeNode* node);//��һ�����ڵ�ѹ��ջ��
    TreeNode* pop();//Pop�����ڵ�
    TreeNode* peek();
    bool isEmpty();//���ջ�Ƿ�Ϊ��
};

//��ʼ��ջ��
MyStack::MyStack(int cap) : capacity(cap), top(-1)
{
    data = new(std::nothrow) TreeNode * [capacity];
    if (data == NULL) {
        cout << "ջ�ڴ�����ʧ�ܣ�" << endl;
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
        cout << "��ǰջ������" << endl;
        return;
    }
    if (top < capacity - 1)
        data[++top] = node;
}


TreeNode* MyStack::pop()
{
    if (data == NULL) {
        cout << "��ǰջ������" << endl;
        return NULL;
    }
    if (top >= 0)
        return data[top--];
    return nullptr; 
}


TreeNode* MyStack::peek()
{
    if (data == NULL) {
        cout << "��ǰջ������" << endl;
        return NULL;
    }
    if (top >= 0)
        return data[top];
    return nullptr; 
}

//���ջ�Ƿ�Ϊ��
bool MyStack::isEmpty()
{
    if (data == NULL) {
        cout << "��ǰջ������" << endl;
        return false;
    }
    return top == -1;
}

//����Ƿ�Ϊ������
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//��������������ȼ�
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

//�������ʽ��
TreeNode* createExpressionTree(const char* expression, int& pos)
{
    MyStack nodes(100); //�������Ϊ100
    MyStack operators(100); // ��װ��������ջ

    while (expression[pos] != '\0') {

        char token = expression[pos];

        if (isdigit(token)) {
            int operand = 0;//��������ֵ

            while (isdigit(expression[pos])) {
                operand = operand * 10 + (expression[pos] - '0');
                ++pos;
            } 
            TreeNode* operandNode = new TreeNode(operand, '\0');//�������ڵ�ȥ������
            nodes.push(operandNode);//����push���ڵ�
        }
        else if (isOperator(token)) {
            //����������ջ��Ϊ�գ������������ڼ����������ǰ
            while (!operators.isEmpty() && getPrecedence(operators.peek()->op) >= getPrecedence(token)) {
                TreeNode* operatorNode = operators.pop();//��ȡ���������Ԫ��
                TreeNode* rightNode = nodes.pop();
                TreeNode* leftNode = nodes.pop();
                operatorNode->left = leftNode;//��������Ԫ��
                operatorNode->right = rightNode;
                nodes.push(operatorNode);//��������ڵ�push���ڵ�ջ
            }
            
            TreeNode* operatorNode = new TreeNode(0, token);
            operators.push(operatorNode);
            ++pos;
        }
        else if (token == '(') {
            ++pos;
            TreeNode* subexpression = createExpressionTree(expression, pos); //����һ���ӱ��ʽ��ʹ���Ϊ�ڵ�
            ++pos; 
            nodes.push(subexpression);
        }
        else if (token == ')')
            break;
        else
            ++pos;//�����
    }
    //����ֱ���������ջΪ��
    while (!operators.isEmpty()) {
        TreeNode* operatorNode = operators.pop();//��ȡ���������Ԫ��
        TreeNode* rightNode = nodes.pop();
        TreeNode* leftNode = nodes.pop();
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;
        nodes.push(operatorNode);//��������ڵ�push���ڵ�ջ
    }

    return nodes.pop();//�˶�ջ�н�ֻ��һ�������ڵ�
}

//ǰ�������ӡ��
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

//���������ӡ��
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

//���������ӡ��
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

//������
int evaluateExpression(TreeNode* root) {
    if (!root) //û��ֱ��return
        return 0;

    if (root->op == '\0') //�������־ͷ�����
        return root->data;


    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    //���������
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
            cout << "�㲻����Ϊ������" << endl;
            exit(1);
        }
    }

    return 0; 
}

int main() {

    char infixExpression[100];
    cout << "��������ʽ" << endl;
    cin.getline(infixExpression, 100);

    int pos = 0;
    TreeNode* expressionTree = createExpressionTree(infixExpression, pos);

    cout << "ԭ���ʽ: " << infixExpression << endl;
    cout << "������ʽ: ";
    printInorder(expressionTree);
    cout << endl;

    cout << "�沨��ʽ: ";
    printPostorder(expressionTree);
    cout << endl;

    cout << "�������ʽ: ";
    printorder(expressionTree);
    cout << endl;

    int result = evaluateExpression(expressionTree);
    cout << "���: " << result << endl;


    return 0;
}
