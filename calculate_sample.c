#include "dsdiy.h"
#include <stdio.h>
#include <stdlib.h>
struct Node {
    char type;
    int content;
    struct Node *left, *right;
}* p;

// 声明一个长度100，装struct Node*的栈
typedef define_stack(100, struct Node*) stack1;
// 声明一个长度100，装char的栈
typedef define_stack(100, char) stack2;

// 前序遍历（打印前缀表达式）
void preDFS(struct Node* node)
{
    if (node->type != 0)
    {
        printf("%d ", node->content);
        return;
    }
    printf("%c ", node->content);
    preDFS(node->left);
    preDFS(node->right);
}

// 中序遍历(没有括号会导致打印阅读混乱)
void midDFS(struct Node* node) {
    if (node->type != 0)
    {
        printf("%d ", node->content);
        return;
    }
    preDFS(node->left);
    printf("%c ", node->content);
    preDFS(node->right);
}

// 后序遍历（打开两个printf是后缀表达式）
int postDFS(struct Node* node)
{
    if (node->type != 0) {
        // printf("%d ", node->content);
        return node->content;
    }
    int a = postDFS(node->left);
    int b = postDFS(node->right);
    // printf("%c ", node->content);
    switch (node->content) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        exit(1);
    }
}

int main(int argc, char const* argv[])
{
    stack1 nodeStack;
    stack2 opStack;
    // 栈初始化
    stack_flush(opStack, 100);
    // 栈初始化
    stack_flush(nodeStack, 100);

    char read[1000];
    fgets(read, 999, stdin);
    // 过滤空格
    unsigned int i = 0, j = 0;
    while (read[i] != '=') {
        if (read[i] != ' ') {
            read[j++] = read[i];
        }
        i++;
    }
    read[j++] = '='; // 提前存入终结符号
    read[j] = '\0';
    // 处理逻辑
    // 设置优先表
    int pri[128] = {};
    pri['='] = -1;
    pri['('] = 0;
    pri[')'] = 1;
    pri['+'] = pri['-'] = 2;
    pri['*'] = pri['/'] = 3;
    i = 0;
    while (read[i] != 0) { // 会处理'='

        if ('0' <= read[i] && read[i] <= '9') {
            j = 0;
            while ('0' <= read[i] && read[i] <= '9') {
                j = j * 10 + read[i] - '0';
                i++;
            }
            // 数字节点直接入栈
            p = (struct Node*)malloc(sizeof(struct Node));
            p->content = j;
            p->type = 1;
            p->left = p->right = NULL;
            stack_push(nodeStack, p);
        }

        if (read[i] == '(')
            stack_push(opStack, read[i]);
        else {
            while (!stack_empty(opStack) && pri[stack_visit(opStack)] >= pri[read[i]]) {
                p = (struct Node*)malloc(sizeof(struct Node));
                p->content = stack_pop(opStack);
                p->type = 0;
                // 新节点获得俩子节点
                p->right = stack_pop(nodeStack);
                p->left = stack_pop(nodeStack);
                // 初始化后入栈
                stack_push(nodeStack, p);
            }
            if (read[i] == ')') //')'右括号被左括号阻断，设计上左括号会遗留，所以需要出栈
                stack_pop(opStack);
            else
                stack_push(opStack, read[i]);
        }

        i++;
    }
    int ans = postDFS(stack_pop(nodeStack));
    printf("%d\n", ans);
    return 0;
}