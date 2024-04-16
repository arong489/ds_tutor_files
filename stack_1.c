#include "dsdiy.h"
#include <stdio.h>
struct stack_element {
    int int_part;
    char char_part;
    long long_part;
};

// typedef define_queue(5 ,struct stack_element) stack;
typedef define_stack(100, struct stack_element) Stack;
int main()
{
    Stack stackTester;
    stack_flush(stackTester, 100);
    struct stack_element a = { 1, 2, 3 }, b = { 4, 5, 6 }, c, d;
    stack_push(stackTester, a);
    stack_push(stackTester, b);
    c = stack_visit(stackTester);
    printf("%d %d %d\n", c.int_part, c.char_part, c.long_part);
    stack_visit(stackTester, d);
    printf("%d %d %d\n", d.int_part, d.char_part, d.long_part);
    // stack s;
    // Queueflush(s,5);
    // int n;
    // struct stack_element e;
    // while(~scanf("%d",&n)&&n!=-1){
    //     switch(n){
    //         case 1:
    //             scanf("%d",&e.int_part);
    //             if(!(queue_pushback(s,e)))printf("error\n");
    //             break;
    //         case 0:
    //             if(queue_popup(s,e))printf("%d\n",e.int_part);
    //             else printf("error\n");
    //             break;
    //         default:
    //             fputs("=====1 int for pushback, 0 for popup=====\n", stdout);
    //             break;
    //     }
    // }
    struct stack_element *p;
    _STACK_FOREACH(stackTester, p){
        printf("%d ", p->int_part);
    }
    return 0;
}