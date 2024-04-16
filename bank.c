#include<stdlib.h>
#include<stdio.h>
#include"dsdiy.h"

//顾客链表定义
struct Customer{
    int id;
    int arriveTime;
    int handleTime;
    // 如果在struct Customer前"typedef define_linker(struct Customer) link;"那么也可以写link linker;
    define_linker(struct Customer) linker;
    // define_linker(struct Customer) another_linker;//同一个节点可以参与不同的链表
};
list_effective(struct Customer, linker);//使能链接块，应当保证全部链表节点的全部link块不重名，对每个链接的每个link块，应该一一赋值

struct Customer *windowHeader = NULL, *customerHeader = NULL;//链表头需要初始化为NULL

//用队列储存进人周期
//定义队列
typedef define_queue(200, int) queue;



void handle(struct Customer *cus) {//按道理处理函数也可以写成宏函数，或者 xxx handle(void* xxx);
    cus->handleTime--;
    if (cus->handleTime==0) {
        struct Customer *temp;
        list_delete(windowHeader, linker, cus, 0, temp);//foreach内不影响被删除的节点下一个节点的操作
        free(temp);
    }
}


int main(int argc, char const *argv[])
{
    struct Customer *temp;
    // 甚至可以直接用define_queue(200, int) inQueue;
    queue inQueue;
    //初始化队列
    queue_flush(inQueue, 200);
    int n, num, id=0, winNum=3, roundTime = 0;
    int waitLength, handleLength;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &num);
        queue_pushback(inQueue, num);
    }


    while (!queue_empty(inQueue) || !list_empty(customerHeader)) {
        roundTime++;
        if (num=queue_popfront(inQueue)) {//出队失败会返回0
            //初始化客户信息并入队
            for (int i = 0; i < num; i++) {
                temp = (struct Customer*) malloc(sizeof(struct Customer));
                temp->id = ++id;
                temp->arriveTime = roundTime;
                scanf("%d", &temp->handleTime);
                //在customerHeader打头linker链接的链表的customerHeader节点后的第114514个节点后插入temp
                //超界会自动插在边界外
                list_insert(customerHeader, linker, customerHeader, 114514, temp);
            }

            //获取custmoerHeader打头的linker链接的链表长度
            waitLength = list_length(customerHeader, linker);
            while (waitLength/winNum>=7&&winNum<5) winNum++;
        }

        //对windowHeader开始linker链接的自己及之后4个节点(共5个)进行批量handle操作
        //void handle(typeof(windowHeader))
        list_foreach(windowHeader, linker, 5, handle);

        //获取windowHeader打头的linker链接的链表长度
        handleLength = list_length(windowHeader, linker);
        
        // 处于效率考虑不建议频繁使用list_length，虽然也可以像下一行一样写
        // while (handleLength < winNum && !list_empty(customerHeader)) {
        while (handleLength < winNum && !list_empty(customerHeader)) {
            //对customerHeader打头linker链接的customerHeader后第0个(其本身)进行删除，并将其放入temp中
            list_delete(customerHeader, linker, customerHeader, 0, temp);
            //将temp插入到windowHeader打头linker链接的windowHeader后第0个(其本身)后进行删除
            list_insert(windowHeader, linker, windowHeader, 0, temp);
            printf("%d : %d\n", temp->id, roundTime-temp->arriveTime);
            handleLength++;
        }


        waitLength = list_length(customerHeader, linker);
        while (waitLength/winNum<7 && winNum>3) winNum--;

    }
    
    return 0;
}