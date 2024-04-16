#include "dsdiy.h"
typedef define_list(int) List;
typedef define_list(char) LIST;
#define print(x) printf("%d ", x)
void print_func(int x)
{
    printf("%d ", x);
}
int main(int argc, char const* argv[])
{
    List list;
    LIST list2;
    int* n;
    list_flush(list);
    list_pushback(list, 1);
    list_insert(list, 1, 2);
    list_pushback(list, 3);
    list_insert(list, 3, 4);
    list_insert(list, 4, 5);
    list_popfront(list);
    list_popback(list);
    list_remove(list, 0);
    list_swap(list, 0, 1);
    list_foreach(list, print);
    _LIST_FOREACH(list, n, 0, 1)
    {
        printf("%d ", *n);
    }
    list_foreach(list, print_func);
    list_clear(list);
    return 0;
}