#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp1(const void* a, const void* b)
{
    int *va = (int*)a, *vb = (int*)b;
    return *va < *vb ? -1 : 1;
}
int cmp2(const void* a, const void* b)
{
    long long va = **(long long(*)[10])a;
    long long vb = **(long long(*)[10])b;
    return *((int*)va) < *((int*)vb)? -1 : 1;
}
int main(int argc, char const* argv[])
{
    int* p[10];
    int* q[10];
    int* r;
    int array[10];
    srand(0);
    for (size_t i = 0; i < 10; i++) {
        p[i] = array + i;
        q[i] = (int*)malloc(sizeof(int));
        // r = (int*)malloc(sizeof(int));
        // free(r);
        *p[i] = *q[i] = rand();
    }
    qsort(p, 10, sizeof(p[0]), cmp2);
    for (size_t i = 0; i < 10; i++) {
        printf("%d ", *p[i]);
    }
    fputc('\n', stdout);

    // qsort(q, 10, sizeof(q[0]), cmp1);
    // for (size_t i = 0; i < 10; i++) {
    //     printf("%d ", *q[i]);
    // }
    // fputc('\n', stdout);

    r = array;
    qsort(r, 10, sizeof(int), cmp1);
    for (size_t i = 0; i < 10; i++) {
        printf("%d ", r[i]);
    }

    // qsort(p[0], 10, sizeof(*p[0]), cmp1);
    // for (size_t i = 0; i < 10; i++) {
    //     printf("%d ", *p[i]);
    // }
    // fputc('\n', stdout);

    // int cmp2(...){
    // 	int *va = (int*)a;
    // }
    // int cmp3(...){
    // 	int **va = (int **)a; -> int *va = *(int**)a;
    // }
    // qsort(int*, num, size, cmp2);
    // qsort(int**, num, size, cmp3);

    return 0;
}
