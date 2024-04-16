#include<stdio.h>
#include<stdlib.h>
#define LIST_CORE_MODE 1
#include"dsdiy.h"

/*//////////////////////////////////////////////////*/
//*                                                 //
//*         a test example for list marco           //
//*                                                 //
/*//////////////////////////////////////////////////*/

//必要的声明
typedef struct list_test test;
typedef define_linker(test) linker;
typedef struct list_test
{
    int int_part;
    char chat_part;
    linker vertical_link_part;//这是必要部分，前面的看自己设定
    linker horizontal_link_part;
} test;//"test"和"vertical_link_part"和"horizontal_link_part"可以换名，但是对应地方必须一致

list_effective(test, vertical_link_part);//使链表函数有效化
list_effective(test, horizontal_link_part);

int main(int argc, char const *argv[])
{
    test *inverse_header = NULL, *sort_header = NULL, *check;//必须初始化，否则会有意向不到的后果
    //输入插入测试
    int n;
    system("chcp 65001 1>nul");
    scanf("%d", &n);
    for(size_t i = 0; i < n; i++) {
        test *temp = (test*)malloc(sizeof(test));
        scanf("%d", &temp->int_part);
        list_insert(inverse_header, vertical_link_part, inverse_header, -1, temp);//第五个参数和上述结构成员link_part同名
        list_insert(sort_header, horizontal_link_part, sort_header, i, temp);
    }
    test *temp;
    fputs("测试头前插入:\n", stdout);
    list_get(inverse_header, vertical_link_part, 0, temp);//获取头节点
    while (temp) {
        printf("%d ", temp->int_part);
        list_get(temp, vertical_link_part, 1, temp);
    }

    fputs("\n测试尾后插入和删除\n", stdout);
    list_get(sort_header, horizontal_link_part, 0, temp);//获取头节点
    while (temp) {
        printf("%d ", temp->int_part);
        test *dele;
        list_delete(sort_header, horizontal_link_part, temp, 0, dele);//删除测试
        // free(dele);不能删除，因为两条链共用了元素内存
        list_get(sort_header, horizontal_link_part, 0, temp);
    }
    if (list_empty(sort_header)) fputs("\n[correct]sort list is empty\n", stdout);
    else fputs("\n[error]sort list is no empty\n", stdout);
    
    fputs("隔项get测试\n", stdout);
    list_get(inverse_header, vertical_link_part, 0, temp);//获取头节点
    int i = 0;
    while (temp) {
        printf("%d ", temp->int_part);
        i++;
        list_get(temp, vertical_link_part, i, temp);
    }
    return 0;
}
