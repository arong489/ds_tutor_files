#include "dsdiy.h"
#include <stdio.h>
#include <stdlib.h>
//声明一个长202，装int的队列
typedef define_queue(202, int) Queue;
int comp(const void* a, const void* b)
{
    int *pa = *(int(*)[2])(a), *pb = *(int(*)[2])(b);
    // int *pa = *(int **)a, *pb = (int *)b;
    if (pa[1] == pb[1])
        return pa[0] < pb[0] ? -1 : 1;
    else
        return pa[1] < pb[1] ? 1 : -1;
}
int main()
{
    int m, n, num, port[102][2] = {}, branch[102][3] = {}, change[102] = {};
    Queue temp;
    queue_flush(temp, 202);

    // 输入
    scanf("%d", &m);
    // 广搜队预先插入最初的节点
    queue_pushback(temp, m);

    while (~m) {
        num = 0;
        while (~scanf("%d", &n) && ~n) {
            // 存储分支信息
            //-99说明分支从100-99开始编号，均不为0，遇到0说明其后没有分支
            branch[m - 99][num++] = n;
        }
        scanf("%d", &m);
    }
    // 记录port客流量和原本编号，因为排序会改变排序
    while (~scanf("%d%d", &m, &n)) {
        port[m][0] = m;
        port[m][1] = n;
    }
    // 对port排序
    qsort(port, 100, sizeof(int[2]), comp);
    // 广度优先搜索，记录对换信息
    // 广搜容器是temp
    num = 0;
    int id;
    while (!queue_empty(temp)) {
        id = queue_popfront(temp);
        if (id < 100)
            // 记录对换信息，乘机口不入队
            change[num++] = id;
        else {
            id -= 99;
            for (size_t i = 0; i < 3 && branch[id][i]; i++)
                queue_pushback(temp, branch[id][i]);
        }
    }
    for (size_t i = 0; port[i][0]; i++)
        printf("%d->%d\n", port[i][0], change[i]);
    return 0;
}