#include <stdio.h>
#include<stdlib.h>
int *p, *q;

void init(){
    //!局部变量生存周期问题
    int a = 1;
    p = &a;
    q = (int*)malloc(sizeof(int));
    *q = 1;
    //! a (that is to say *p) is killed here
}

void print(){
    printf("malloc is still alive:\t%d\n", *q);
    printf("\"a\" in init() is already dead:\t%d\n", *p);
}

int main(int argc, char const* argv[])
{
    //!不同类型跨度不同
    printf("int*:%d char*:%d\n", (int*)8 - (int*)4, (char*)8 - (char*)4);
    int* pint;
    char* pchar;
    int c;
    pint = pchar = &c;
    *pchar = fgetc(stdin);
    //!指针值相同时，对同处值进行操作
    printf("ascii of char '%c' is %#x\n", c, *pint);
    //!有符号短值到长值的位拓展问题
    printf("(char)(0x80) to u_int:%x\tint to u_int%x\n", (char)(0x80), 0x80);

    init();
    print();
    return 0;
}