#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/*====================break line==========================*/
// 定义操作符栈和操作数栈
#define MAXSIZE 100

struct {
    unsigned int top;
    char ELEM[MAXSIZE];
} operators;

struct {
    unsigned int top;
    int ELEM[MAXSIZE];
} numbers;

/*=====================break line=======================*/
// 宏定义函数实现泛型
#define push_back(stack, element) ({                     \
    if (stack.top == MAXSIZE)                            \
        fputs("pushback while stack is full\n", stderr); \
    assert(stack.top < MAXSIZE);                         \
    stack.ELEM[stack.top++] = element;                   \
})

#define pop_up(stack, element) ({                      \
    if (stack.top == 0)                                \
        fputs("popup while stack is empty\n", stderr); \
    assert(stack.top > 0);                             \
    element = stack.ELEM[--stack.top];                 \
})

#define peek_top(stack, element) ({                       \
    if (stack.top == 0)                                   \
        fputs("peek top while stack is empty\n", stderr); \
    assert(stack.top > 0);                                \
    element = stack.ELEM[stack.top - 1];                  \
})

#define stack_falsh(stack) (stack.top = 0)

#define stack_empty(stack) (stack.top == 0)

#define stack_full(stack) (stack.top == MAXSIZE)

/*=====================beak line======================*/
// 帮助，工具函数
#define isdigit(c) ('0' <= c && c <= '9')
#define isoperator(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
/**
 * @brief Get the number object
 *
 * @param s 源字符串
 * @param gap 源串第一个数字字符串得长度，用于偏移量推移
 * @return int 读取结果
 */
int get_number(char* s, int* gap)
{
    int temp = 0, i = 0;
    while ('0' <= s[i] && s[i] <= '9') {
        temp = temp * 10 + (s[i] - '0');
        ++i;
    }
    if (gap != NULL)
        *gap = i; // 记录跳跃长度
    return temp;
}

/*===================break line======================*/
// 功能函数，优先级比较函数
int cmpOperator(char op1, char op2)
{
    // 清算符号
    if (op1 == '=')
        return -1;
    // op2在栈内，不会是')',报错，无需了解
    if (op2 == ')')
        fputs("operator stack error runtime status\n", stderr);
    assert(op2 != ')');

    // 操作符四种情况 +-    */    (     )
    if (op1 == '(')
        return 1; // 直接入栈，视为op1优先级最高
    if (op1 == ')')
        return op2 == '(' ? 1 : -1; // 除(以外都出栈，视为op2优先级高于op1

    if (op1 == '*' || op1 == '/') {
        if (op2 == '+' || op2 == '-' || op2 == '(')
            return 1;
        else
            return 0; // op2一定是 */
    } else { // op1 一定是 +-
        if (op2 == '+' || op2 == '-')
            return 0;
        if (op2 == '(')
            return 1;
        else
            return -1; // op2一定是 */
    }
}

int main()
{
    int num1, num2; // 数字
    char op1, op2; // 操作符
    char expression[1000]; // 表达式
    fgets(expression, 1000, stdin); // 读入表达式字符串
    int i, j; // 数组下标

    // 某次作业填空题的去空格
    i = j = -1;
    do {
        if (expression[++i] != ' ')
            expression[++j] = expression[i];
    } while (expression[i] != '=');

    i = -1;
    do {
        ++i;
        if (isdigit(expression[i])) {
            push_back(numbers, get_number(expression + i, &j));
            i += j - 1;
        } else if (isoperator(expression[i])) {
            op1 = expression[i];
            while (!stack_empty(operators)) {
                peek_top(operators, op2);
                if (cmpOperator(op1, op2) > 0)
                    break;
                pop_up(numbers, num2);
                pop_up(numbers, num1);
                switch (op2) {
                case '+':
                    push_back(numbers, num1 + num2);
                    break;
                case '-':
                    push_back(numbers, num1 - num2);
                    break;
                case '*':
                    push_back(numbers, num1 * num2);
                    break;
                case '/':
                    push_back(numbers, num1 / num2);
                    break;
                default:
                    break;
                }
                pop_up(operators, op2);
            }

            if (op1 != ')')
                push_back(operators, op1); // 非右括号入栈
            else
                pop_up(operators, op1); // 左括号出栈
        }
    } while (expression[i] != '=');
    printf("%d", numbers.ELEM[0]);
    return 0;
}