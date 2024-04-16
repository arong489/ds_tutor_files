/**
 * @file dsdiy.h
 * @author Paul Walker(nickname arong)
 * @brief this is a header file for 2023 data-struct class
 * @version 2.3
 * @date 2023-06-18
 *
 * copyright Copyright (c) 2023 : all for free
 *
 */

#ifndef COUNT_ARGS_HELPER
// 打表式获取宏参个数[注意##判空参去前逗号]
// 上限15
#define COUNT_ARGS_HELPER(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _N, _VA_ARGS_...) _N
#define COUNT_ARGS(_VA_ARGS_...) COUNT_ARGS_HELPER(, ##_VA_ARGS_, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#ifndef __ASSERT_H_
#include <assert.h>
#endif

#ifndef _INC_STDIO
#ifndef __STDIO_H
#include <stdio.h>
#endif
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef _DSDIY_H
#define _DSDIY_H 1
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
 * 基于数组的栈
 * 封装了：
 * 		刷新(第一次使用前需要刷新)
 * 		入栈
 * 		出栈
 * 		访问(获取栈顶但是不弹出)
 * 		判空
 * 		判满
 * 		获取内容个数
 */
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef DSDIY_STACK
#define DSDIY_STACK 3.0

/**
 * @brief 定义栈
 * @param STACK_LENTH_MAXSIZE 栈最大长度
 * @param STACK_ELEMENT_TYPE 栈元素类型
 * @attention 使用前记得用stack_flush(stack_name, set_max_length)初始化
 * @note 常见的例子有:
 * @note &emsp;     typedef define_stack(100, struct elem) stack 和
 * @note &emsp;     typedef define_stack(100, int) another_stack
 * @note &nbsp;
 * @note 方法合集:
 * @note &emsp;     stack_flush--初始化,
 * @note &emsp;     stack_push--入栈,
 * @note &emsp;     stack_pop--出栈,
 * @note &emsp;     stack_visit--访问栈顶,
 * @note &emsp;     stack_empty--判空栈,
 * @note &emsp;     stack_full--判满栈,
 * @note &emsp;     stack_length--栈元素数目,
 * @note &emsp;     stack_foreach--栈元素批量操作,
 * @note &emsp;     stack_find--栈元素查找,
 * @note &emsp;     stack_has--检查栈是否包含元素
 * @note &emsp;     _STACK_FOREACH--栈元素循环(当for使用)
 */
#define define_stack(STACK_LENTH_MAXSIZE, STACK_ELEMENT_TYPE) \
    struct {                                                  \
        STACK_ELEMENT_TYPE ELEM[STACK_LENTH_MAXSIZE];         \
        unsigned int top, DS_MAXSIZE_1, loopVar;              \
    }

/**
 * @brief 初始化栈，设定你需要的最大栈长
 * @param SAK 栈名
 * @param STACK_LENTH_MAXSIZE 最大栈长
 * @note 你不需要设置和define_stack时一样的长度，但请保证小于它
 */
#define stack_flush(SAK, STACK_LENTH_MAXSIZE) (SAK.top = 0, SAK.DS_MAXSIZE_1 = STACK_LENTH_MAXSIZE)

/**
 * @brief 入栈
 * @param SAK 栈名
 * @param element 入栈元素
 * @attention 会有assert检测是否超出stack_flush时设置的长度
 */
#define stack_push(SAK, element) ({     \
    assert(SAK.top < SAK.DS_MAXSIZE_1); \
    SAK.ELEM[SAK.top++] = element;      \
})

/**
 * @brief 栈顶弹出
 * @param SAK 栈名
 * @param ELEMENT [可选]的承接变量
 * @attention 不写第二个参数，默认开启assert检查边界, 写该参数不再assert检查
 * @return 写了ELEMENT参数，出栈失败返回0, 成功则返回非0; 没写ELEMENT返回栈顶元素
 */
#define stack_pop(SAK, _VA_ARGS_...) stack_pop_analysis(SAK, ##_VA_ARGS_, stack_pop2, stack_pop1)

#define stack_pop_analysis(_1, _2, pop_func, _VA_ARGS_...) pop_func(_1, _2)

#define stack_pop1(SAK, ABANDON) ({ \
    assert(SAK.top);                \
    SAK.ELEM[--SAK.top];            \
})

#define stack_pop2(SAK, ELEMENT) ({    \
    if (SAK.loopVar = SAK.top)         \
        ELEMENT = SAK.ELEM[--SAK.top]; \
    SAK.loopVar;                       \
})

/**
 * @brief 栈顶访问
 * @param SAK 栈名
 * @param ELEMENT [可选]的承接变量
 * @attention 不写第二个参数，默认开启assert检查边界, 写该参数不再assert检查
 * @return 写了ELEMENT参数则访问失败返回0, 成功则非0; 没写ELEMENT返回栈顶元素
 */
#define stack_visit(SAK, _VA_ARGS_...) stack_visit_analysis(SAK, ##_VA_ARGS_, stack_visit2, stack_visit1)

#define stack_visit_analysis(_1, _2, visit_func, _VA_ARGS_...) visit_func(_1, _2)

#define stack_visit1(SAK, ABANDON) ({ \
    assert(SAK.top);                  \
    SAK.ELEM[SAK.top - 1];            \
})

#define stack_visit2(SAK, ELEMENT) ({                    \
    SAK.top ? ELEMENT = SAK.ELEM[SAK.top - 1] : (void)0; \
    SAK.top;                                             \
})

/**
 * @brief 判断栈是否为空
 * @param SAK 栈名
 * @return 栈是否为空
 */
#define stack_empty(SAK) (!SAK.top)

/**
 * @brief 检查堆栈是否已满
 * @param SAK 栈名
 * @return 栈是否已满
 * @attention 依据是stack_flush时设置的长度
 */
#define stack_full(SAK) (SAK.top == SAK.DS_MAXSIZE_1)

/**
 * @brief 获取栈元素数目
 * @param SAK 栈名
 */
#define stack_length(SAK) (SAK.top)

/**
 * @brief 对栈内全部元素批量长度
 * @param SAK 栈名
 * @param OPERATION 操作函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指操作函数需要的其它参数，不需要则不填)
 */
#define stack_foreach(SAK, OPERATION, _VA_ARGS_...) ({            \
    for (SAK.loopVar = 0; SAK.loopVar < SAK.top; SAK.loopVar++) { \
        OPERATION(SAK.ELEM[SAK.loopVar], ##_VA_ARGS_);            \
    }                                                             \
})

/**
 * @brief 栈元素查找
 * @param SAK 栈名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 * @return 返回查找的元素
 * @attention 规定没找到返回0，若要查是否含值为0的元素，请使用stack_has
 */
#define stack_find(SAK, COMPARATION, _VA_ARGS_...) ({                                                               \
    for (SAK.loopVar = 0; SAK.loopVar < SAK.top && !COMPARATION(SAK.ELEM[SAK.loopVar], ##_VA_ARGS_); SAK.loopVar++) \
        ;                                                                                                           \
    SAK.loopVar < SAK.top ? SAK.ELEM[SAK.loopVar] : 0;                                                              \
})

/**
 * @brief 栈是否包含元素
 * @param SAK 栈名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 * @return 没有返回0，有返回1
 */
#define stack_has(SAK, COMPARATION, _VA_ARGS_...) ({                                                                \
    for (SAK.loopVar = 0; SAK.loopVar < SAK.top && !COMPARATION(SAK.ELEM[SAK.loopVar], ##_VA_ARGS_); SAK.loopVar++) \
        ;                                                                                                           \
    SAK.loopVar < SAK.top ? 1 : 0;                                                                                  \
})

/**
 * @brief 栈批量Core
 * @param SAK 栈名
 * @param ELEMENT_POINTER 元素指针(便于改写元素)
 * @param BEGIN [可选参数]起始元素位置(包含这个位置)
 * @param END [可选参数]结束元素位置(不包含这个位置)
 * @attention BEGIN不选默认为0位置起始，END不选默认为最后一个元素的下一位，选择END之前必选BEGIN
 */
#define _STACK_FOREACH(SAK, ELEMENT_POINTER, _VA_ARGS_...) _STACK_FOREACH_analysis(SAK, ELEMENT_POINTER, ##_VA_ARGS_, _STACK_FOREACH2, _STACK_FOREACH1, _STACK_FOREACH0)

#define _STACK_FOREACH_analysis(SAK, ELEMENT_POINTER, _begin, _end, _stack_foreach_function, _VA_ARGS_...) _stack_foreach_function(SAK, ELEMENT_POINTER, _begin, _end)

#define _STACK_FOREACH0(SAK, ELEMENT_POINTER, ABANDON1, ABANDON2) for (SAK.loopVar = 0; (SAK.loopVar < SAK.top) && (ELEMENT_POINTER = SAK.ELEM + SAK.loopVar); SAK.loopVar++)

#define _STACK_FOREACH1(SAK, ELEMENT_POINTER, BEGIN, ABANDON) for (SAK.loopVar = BEGIN; (SAK.loopVar < SAK.top) && (ELEMENT_POINTER = SAK.ELEM + SAK.loopVar); SAK.loopVar++)

#define _STACK_FOREACH2(SAK, ELEMENT_POINTER, BEGIN, END) for (SAK.loopVar = BEGIN; (SAK.loopVar < SAK.top) && (SAK.loopVar < END) && (ELEMENT_POINTER = SAK.ELEM + SAK.loopVar); SAK.loopVar++)

#endif
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
 * 基于数组的队列
 * 封装了：
 * 		刷新(第一次使用前需要刷新)
 * 		队首尾压入
 * 		队首尾弹出
 * 		队首尾访问(获取但是不弹出)
 * 		判空
 * 		判满
 * 		获取内容个数
 */
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef DSDIY_QUQUE
#define DSDIY_QUQUE 3.0

/**
 * @brief 定义队
 * @param STACK_LENTH_MAXSIZE 队最大长度
 * @param STACK_ELEMENT_TYPE 队元素类型
 * @attention 使用前记得用queue_flush(queue_name, set_max_length)初始化
 * @note 常见的例子有:
 * @note &emsp;     typedef define_queue(100, struct elem) queue 和
 * @note &emsp;     typedef define_queue(100, int) another_queue
 * @note &nbsp;
 * @note 方法合集:
 * @note &emsp;     queue_flush--初始化,
 * @note &emsp;     queue_pushfront--入队首,
 * @note &emsp;     queue_popfront--出队首,
 * @note &emsp;     queue_visitfront--访问队首,
 * @note &emsp;     queue_pushback--入队尾,
 * @note &emsp;     queue_popback--出队尾,
 * @note &emsp;     queue_visitback--访问队尾,
 * @note &emsp;     queue_empty--判空队,
 * @note &emsp;     queue_full--判满队,
 * @note &emsp;     queue_length--队元素数目,
 * @note &emsp;     queue_foreach--队元素批量操作,
 * @note &emsp;     queue_find--队元素查找,
 * @note &emsp;     queue_has--队是否包含元素,
 * @note &emsp;     _QUEUE_FOREACH--队元素循环(当for使用)
 */
#define define_queue(QUEUE_LENTH_MAXSIZE, QUEUE_ELEMENT_TYPE) \
    struct {                                                  \
        QUEUE_ELEMENT_TYPE ELEM[QUEUE_LENTH_MAXSIZE + 1];     \
        unsigned int front, rear, DS_MAXSIZE_2, loopVar;      \
    }

/**
 * @brief 队初始化
 * @param QEE 队名
 * @param QUEUE_LENTH_MAXSIZE 队设定最大长度
 * @note 这里设置的最大长度不必与define_queue时一致，但是使用时以这里定义的长度为准
 */
#define queue_flush(QEE, QUEUE_LENTH_MAXSIZE) (QEE.front = QEE.rear = 0, QEE.DS_MAXSIZE_2 = QUEUE_LENTH_MAXSIZE)

/**
 * @brief 队尾压入
 * @param QEE 队名
 * @param element 入队元素
 * @attention 会有assert检查是否队满
 */
#define queue_pushback(QEE, element) ({                                          \
    assert(QEE.rear != (QEE.front + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1)); \
    QEE.ELEM[QEE.rear++] = element;                                              \
    QEE.rear %= (QEE.DS_MAXSIZE_2 + 1);                                          \
})

/**
 * @brief 队首弹出
 * @param QEE 队名
 * @param ELEMENT [可选参数]承接出队元素的变量
 * @return 若填写ELEMENT则返回操作是否成功，若不填则返回出队元素
 * @attention 不填写ELEMENT会开启assert检查边界
 */
#define queue_popfront(QEE, _VA_ARGS_...) queue_popfront_analysis(QEE, ##_VA_ARGS_, queue_popfront2, queue_popfront1)

#define queue_popfront_analysis(_1, _2, queue_popfront_func, _VA_ARGS_...) queue_popfront_func(_1, _2)

#define queue_popfront1(QEE, ABANDON) ({ \
    assert(QEE.rear != QEE.front);       \
    QEE.loopVar = QEE.front++;           \
    QEE.front %= (QEE.DS_MAXSIZE_2 + 1); \
    QEE.ELEM[QEE.loopVar];               \
})

#define queue_popfront2(QEE, ELEMENT) ({         \
    if (QEE.loopVar = (QEE.rear != QEE.front)) { \
        ELEMENT = QEE.ELEM[QEE.front++];         \
        QEE.front %= (QEE.DS_MAXSIZE_2 + 1);     \
    }                                            \
    QEE.loopVar;                                 \
})

/**
 * @brief 队首访问
 * @param QEE 队名
 * @param ELEMENT [可选参数]承接队首元素的变量
 * @return 若填写ELEMENT则返回操作是否成功，若不填则返回访问元素
 * @attention 不填写ELEMENT会开启assert检查边界
 */
#define queue_visitfront(QEE, _VA_ARGS_...) queue_visitfront_analysis(QEE, ##_VA_ARGS_, queue_visitfront2, queue_visitfront1)

#define queue_visitfront_analysis(_1, _2, queue_visitfront_func, _VA_ARGS_...) queue_visitfront_func(_1, _2)

#define queue_visitfront1(QEE, ABANDON) ({ \
    assert(QEE.rear != QEE.front);         \
    QEE.ELEM[QEE.front];                   \
})

#define queue_visitfront2(QEE, ELEMENT) ({     \
    if (QEE.loopVar = (QEE.rear != QEE.front)) \
        QEE.ELEM[QEE.front];                   \
    QEE.loopVar;                               \
})

/**
 * @brief 判队空
 * @param QEE 队名
 * @return 队是否为空
 */
#define queue_empty(x) (x.front == x.rear)

/**
 * @brief 判队满
 * @param QEE 队名
 * @return 是否队满
 */
#define queue_full(x) (x.rear == (x.front + x.DS_MAXSIZE_2) % (x.DS_MAXSIZE_2 + 1))

/**
 * @brief 获取队元素数目
 * @param QEE 队名
 * @return 队元素数目
 */
#define queue_length(x) ((x.rear - x.front + x.DS_MAXSIZE_2 + 1) % (x.DS_MAXSIZE_2 + 1))

/**
 * @brief 队首压入
 * @param QEE 队名
 * @param element 入队元素
 * @attention 会有assert检查是否队满
 */
#define queue_pushfront(QEE, element) ({                                 \
    QEE.front = (QEE.front + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1); \
    assert(QEE.rear != QEE.front);                                       \
    QEE.ELEM[QEE.front] = element;                                       \
})

/**
 * @brief 队尾弹出
 * @param QEE 队名
 * @param ELEMENT [可选参数]承接出队元素的变量
 * @return 若填写ELEMENT则返回操作是否成功，若不填则返回出队元素
 * @attention 不填写ELEMENT会开启assert检查边界
 */
#define queue_popback(_VA_ARGS_...) queue_popback_analysis(_VA_ARGS_, queue_popback2, queue_popback1)

#define queue_popback_analysis(_1, _2, queue_popback_func, _VA_ARGS_...) queue_popback_func(_1, _2)

#define queue_popback1(QEE, ABANDON) ({                                \
    assert(QEE.rear != QEE.front);                                     \
    QEE.rear = (QEE.rear + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1); \
    QEE.ELEM[QEE.rear];                                                \
})

#define queue_popback2(QEE, ELEMENT) ({                                    \
    if (QEE.loopVar = (QEE.rear != QEE.front)) {                           \
        QEE.rear = (QEE.rear + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1); \
        ELEMENT = QEE.ELEM[QEE.rear];                                      \
    }                                                                      \
    QEE.loopVar;                                                           \
})

/**
 * @brief 队尾访问
 * @param QEE 队名
 * @param ELEMENT [可选参数]承接队尾元素的变量
 * @return 若填写ELEMENT则返回操作是否成功，若不填则返回访问元素
 * @attention 不填写ELEMENT会开启assert检查边界
 */
#define queue_visitback(_VA_ARGS_...) queue_visitback_analysis(_VA_ARGS_, queue_visitback2, queue_visitback1)

#define queue_visitback_analysis(_1, _2, queue_visitback_func, _VA_ARGS_...) queue_visitback_func(_1, _2)

#define queue_visitback1(QEE, ABANDON) ({                             \
    assert(QEE.rear != QEE.front);                                    \
    QEE.ELEM[(QEE.rear + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1)]; \
})

#define queue_visitback2(QEE, ELEMENT) ({                                           \
    if (QEE.loopVar = (QEE.rear != QEE.front))                                      \
        ELEMENT = QEE.ELEM[(QEE.rear + QEE.DS_MAXSIZE_2) % (QEE.DS_MAXSIZE_2 + 1)]; \
    QEE.loopVar;                                                                    \
})

/**
 * @brief 对队内全部元素作批量操作
 * @param QEE 队名
 * @param OPERATION 操作函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指操作函数需要的其它参数，不需要则不填)
 */
#define queue_foreach(QEE, OPERATION, _VA_ARGS_...) ({                                                                 \
    for (QEE.loopVar = QEE.front; QEE.loopVar != QEE.rear; QEE.loopVar = (QEE.loopVar + 1) % (QEE.DS_MAXSIZE_2 + 1)) { \
        OPERATION(QEE.ELEM[QEE.loopVar], ##_VA_ARGS_);                                                                 \
    }                                                                                                                  \
})

/**
 * @brief 队元素查找
 * @param QEE 队名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 * @return 返回查找的元素
 * @attention 规定没找到返回0值，若要查是否含值为0的元素，请使用queue_has
 */
#define queue_find(QEE, COMPARATION, _VA_ARGS_...) ({                                                                                                                    \
    for (QEE.loopVar = QEE.front; QEE.loopVar != QEE.rear && !COMPARATION(QEE.ELEM[QEE.loopVar], ##_VA_ARGS_); QEE.loopVar = (QEE.loopVar + 1) % (QEE.DS_MAXSIZE_2 + 1)) \
        ;                                                                                                                                                                \
    QEE.loopVar != QEE.rear ? QEE.ELEM[QEE.loopVar] : 0;                                                                                                                 \
})

/**
 * @brief 检查队是否包含元素
 * @param QEE 队名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 * @return 包含返回1，不包含返回0
 */
#define queue_has(QEE, COMPARATION, _VA_ARGS_...) ({                                                                                                                     \
    for (QEE.loopVar = QEE.front; QEE.loopVar != QEE.rear && !COMPARATION(QEE.ELEM[QEE.loopVar], ##_VA_ARGS_); QEE.loopVar = (QEE.loopVar + 1) % (QEE.DS_MAXSIZE_2 + 1)) \
        ;                                                                                                                                                                \
    QEE.loopVar != QEE.rear ? 1 : 0;                                                                                                                                     \
})

/**
 * @brief 队批量Core
 * @param QEE 队名
 * @param ELEMENT_POINTER 元素指针(便于改写元素)
 * @param BEGIN [可选参数]起始元素位置(包含这个位置)
 * @param END [可选参数]结束元素位置(不包含这个位置)
 * @attention BEGIN不选默认为0位置起始，END不选默认为最后一个元素的下一位，选择END之前必选BEGIN
 */
#define _QUEUE_FOREACH(QEE, ELEMENT_POINTER, _VA_ARGS_...) _QUEUE_FOREACH_analysis(QEE, ELEMENT_POINTER, ##_VA_ARGS_, _QUEUE_FOREACH2, _QUEUE_FOREACH1, _QUEUE_FOREACH0)

#define _QUEUE_FOREACH_analysis(QEE, ELEMENT_POINTER, _begin, _end, _queue_foreach_function, _VA_ARGS_...) _queue_foreach_function(QEE, ELEMENT_POINTER, _begin, _end)

#define _QUEUE_FOREACH0(QEE, ELEMENT_POINTER, ABANDON1, ABANDON2) for (QEE.loopVar = QEE.front; (QEE.loopVar != QEE.rear) && (ELEMENT_POINTER = QEE.ELEM + QEE.loopVar); QEE.loopVar = (QEE.loopVar + 1) % (QEE.DS_MAXSIZE_2 + 1))

#define _QUEUE_FOREACH1(QEE, ELEMENT_POINTER, BEGIN, ABANDON) for (QEE.loopVar = (QEE.front + BEGIN) % (QEE.DS_MAXSIZE_2 + 1); (QEE.loopVar != QEE.rear) && (ELEMENT_POINTER = QEE.ELEM + QEE.loopVar); QEE.loopVar = (QEE.loopVar + 1) % (QEE.DS_MAXSIZE_2 + 1))

#define _QUEUE_FOREACH2(QEE, ELEMENT_POINTER, BEGIN, END) for (QEE.loopVar = BEGIN; (QEE.loopVar < END) && ((QEE.loopVar + QEE.front) % (QEE.DS_MAXSIZE_2 + 1) != QEE.rear) && (ELEMENT_POINTER = QEE.ELEM + (QEE.loopVar + QEE.front) % (QEE.DS_MAXSIZE_2 + 1)); QEE.loopVar++)

#endif
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
 *
 * 链表(有待扩充)
 * 出于易用性考虑，链表(Core版)已废止
 * 现在使用(iterator版)链表
 */
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef DSDIY_LSIT
#define DSDIY_LSIT 3.0

/**
 * @brief 定义链表
 * @param TYPE 链表元素类型(不同于栈和队列，这里只能填单个词的类型)
 * @attention 只能使用单个单词的类型，使用前使用list_flush(LIST)进行初始化
 * @note 常见使用样例
 * @note &emsp;     typedef struct Node node;
 * @note &emsp;     typedef define_list(node) List1
 * @note &emsp;     typedef define_list(int) List2
 * @note &nbsp;
 * @note 操作合集:
 * @note &emsp;     list_clear--链表清空
 * @note &emsp;     list_insert--链表插入
 * @note &emsp;     list_pushback--链表尾插入
 * @note &emsp;     list_pushfront--链表头插入
 * @note &emsp;     list_popback--链表尾弹出
 * @note &emsp;     list_popfront--链表头弹出
 * @note &emsp;     list_empty--链表判空
 * @note &emsp;     list_length--获取链表长度
 * @note &emsp;     list_foreach--链表元素批量操作
 * @note &emsp;     list_get--链表元素获取
 * @note &emsp;     list_swap--链表元素交换
 * @note &emsp;     list_remove--单个链表元素删除
 * @note &emsp;     list_remove_if--全链表元素条件删除
 * @note &emsp;     list_remove_range--范围内链表元素删除
 * @note &emsp;     list_has--链表是否拥有元素
 * @note &emsp;     list_find--链表元素查找
 * @note &emsp;     _LIST_FOREACH--链表循环头
 */
#define define_list(STRUCT_TYPE)                            \
    struct {                                                \
        struct STRUCT_TYPE##_ITERATOR {                     \
            STRUCT_TYPE content;                            \
            struct STRUCT_TYPE##_ITERATOR *former, *after;  \
        } *head, *tail;                                     \
        struct STRUCT_TYPE##_ITERATOR *loopNode, *tempNode; \
        unsigned int length, loopVar;                       \
        STRUCT_TYPE OUTPUT;                                 \
    }

/**
 * @brief 链表初始化
 * @param LIST 链表名
 * @attention 使用前必须用这个初始化
 */
#define list_flush(LIST) ({       \
    (LIST).length = 0;              \
    (LIST).head = (LIST).tail = NULL; \
})

/**
 * @brief 链表清空
 * @param LIST 链表名
 * @param DESTROY [可选参数]清除函数
 */
#define list_clear(LIST, _VA_ARGS_...) list_clear_analysis(LIST, ##_VA_ARGS_, list_destroy2, list_destroy1)
#define list_clear_analysis(_1, _2, list_destroy_func, _VA_ARGS_...) list_destroy_func(_1, _2)

#define list_destroy1(LIST, ABANDON) ({                                                          \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != (LIST).tail; (LIST).loopNode = (LIST).tempNode) { \
        (LIST).tempNode = (LIST).loopNode->after;                                                    \
        (LIST).loopNode->after = (LIST).loopNode->former = NULL;                                     \
        free((LIST).loopNode);                                                                     \
    }                                                                                            \
    (LIST).length = 0;                                                                             \
    (LIST).head = (LIST).tail = 0;                                                                   \
})

#define list_destroy2(LIST, DESTROY) ({                                                          \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != (LIST).tail; (LIST).loopNode = (LIST).tempNode) { \
        DESTROY((LIST).loopNode->content);                                                         \
        (LIST).tempNode = (LIST).loopNode->after;                                                    \
        (LIST).loopNode->after = (LIST).loopNode->former = NULL;                                     \
        free((LIST).loopNode);                                                                     \
    }                                                                                            \
    (LIST).length = 0;                                                                             \
    (LIST).head = (LIST).tail = 0;                                                                   \
})

/**
 * @brief 链表插入
 * @param LIST 链表名
 * @param INDEX 插入地址(0代表第一个，1代表第一个后面)
 * @param ELEMENT 插入的元素
 */
#define list_insert(LIST, INDEX, ELEMENT) ({                                                                                          \
    assert(INDEX <= (LIST).length);                                                                                                     \
    (LIST).tempNode = malloc(sizeof(ELEMENT) + sizeof(void*) * 2);                                                                      \
    (LIST).tempNode->content = ELEMENT;                                                                                                 \
    if (INDEX == 0) {                                                                                                                 \
        (LIST).tempNode->after = (LIST).head;                                                                                             \
        (LIST).tempNode->former = NULL;                                                                                                 \
        if ((LIST).head)                                                                                                                \
            (LIST).head->former = (LIST).tempNode;                                                                                        \
        else                                                                                                                          \
            (LIST).tail = (LIST).tempNode;                                                                                                \
        (LIST).head = (LIST).tempNode;                                                                                                    \
    } else if (INDEX == (LIST).length) {                                                                                                \
        (LIST).tail->after = (LIST).tempNode;                                                                                             \
        (LIST).tempNode->former = (LIST).tail;                                                                                            \
        (LIST).tempNode->after = NULL;                                                                                                  \
        (LIST).tail = (LIST).tempNode;                                                                                                    \
    } else {                                                                                                                          \
        for ((LIST).loopNode = (LIST).head, (LIST).loopVar = 1; (LIST).loopVar < INDEX; (LIST).loopVar++, (LIST).loopNode = (LIST).loopNode->after) \
            ;                                                                                                                         \
        (LIST).tempNode->after = (LIST).loopNode->after;                                                                                  \
        (LIST).tempNode->former = (LIST).loopNode;                                                                                        \
        (LIST).loopNode->after = (LIST).tempNode;                                                                                         \
    }                                                                                                                                 \
    (LIST).length++;                                                                                                                    \
})

/**
 * @brief 链表尾元素插入
 * @param LIST 链表名
 * @param ELEMENT 插入元素
 */
#define list_pushback(LIST, ELEMENT) ({                          \
    (LIST).tempNode = malloc(sizeof(ELEMENT) + sizeof(void*) * 2); \
    (LIST).tempNode->content = ELEMENT;                            \
    if ((LIST).tail) {                                             \
        (LIST).tail->after = (LIST).tempNode;                        \
        (LIST).tempNode->former = (LIST).tail;                       \
        (LIST).tempNode->after = NULL;                             \
        (LIST).tail = (LIST).tempNode;                               \
    } else {                                                     \
        (LIST).tail = (LIST).head = (LIST).tempNode;                   \
        (LIST).tail->former = (LIST).tail->after = NULL;             \
    }                                                            \
    (LIST).length++;                                               \
})

/**
 * @brief 链表头元素插入
 * @param LIST 链表名
 * @param ELEMENT 插入元素
 */
#define list_pushfront(LIST, ELEMENT) ({                         \
    (LIST).tempNode = malloc(sizeof(ELEMENT) + sizeof(void*) * 2); \
    (LIST).tempNode->content = ELEMENT;                            \
    if ((LIST).head) {                                             \
        (LIST).head->former = (LIST).tempNode;                       \
        (LIST).tempNode->after = (LIST).head;                        \
        (LIST).tempNode->former = NULL;                            \
        (LIST).head = (LIST).tempNode;                               \
    } else {                                                     \
        (LIST).tail = (LIST).head = (LIST).tempNode;                   \
        (LIST).head->former = (LIST).head->after = NULL;             \
    }                                                            \
    (LIST).length++;                                               \
})

/**
 * @brief 链表尾弹出
 * @param LIST 链表名
 * @return 链表尾元素
 */
#define list_popback(LIST) ({                            \
    (LIST).OUTPUT = (LIST).tail->content;                    \
    (LIST).tempNode = (LIST).tail;                           \
    (LIST).tail = (LIST).tail->former;                       \
    if ((LIST).tail)                                       \
        (LIST).tail->after = NULL;                         \
    else                                                 \
        (LIST).head = NULL;                                \
    (LIST).length--;                                       \
    (LIST).tempNode->after = (LIST).tempNode->former = NULL; \
    free((LIST).tempNode);                                 \
    (LIST).OUTPUT;                                         \
})

/**
 * @brief 链表头弹出
 * @param LIST 链表名
 * @return 链表头元素
 */
#define list_popfront(LIST) ({                           \
    (LIST).OUTPUT = (LIST).head->content;                    \
    (LIST).tempNode = (LIST).head;                           \
    (LIST).head = (LIST).head->after;                        \
    if ((LIST).head)                                       \
        (LIST).head->former = NULL;                        \
    else                                                 \
        (LIST).tail = NULL;                                \
    (LIST).length--;                                       \
    (LIST).tempNode->after = (LIST).tempNode->former = NULL; \
    free((LIST).tempNode);                                 \
    (LIST).OUTPUT;                                         \
})

/**
 * @brief 判断链表是否为空
 * @param LIST 链表名
 * @return 链表是否为空
 */
#define list_empty(LIST) ((LIST).head == NULL)

/**
 * @brief 获取链表长度
 * @param LIST 链表名
 * @return 链表长度
 */
#define list_length(LIST) ((LIST).length)

/**
 * @brief 链表全部元素批量操作
 * @param LIST 链表名
 * @param OPERATION 操作函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指操作函数需要的其它参数，不需要则不填)
 */
#define list_foreach(LIST, OPERATION, _VA_ARGS_...) ({                                             \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != NULL; (LIST).loopNode = (LIST).loopNode->after) { \
        OPERATION((LIST).loopNode->content, ##_VA_ARGS_);                                            \
    }                                                                                              \
})

/**
 * @brief 获取链表元素
 * @param LIST 链表名
 * @param INDEX 元素位置(0 到 list_length-1)
 * @return 链表元素
 */
#define list_get(LIST, INDEX) ({                                                                                                                     \
    assert(INDEX < (LIST).length);                                                                                                                     \
    if (INDEX > (LIST).length / 2) {                                                                                                                   \
        for ((LIST).loopVar = (LIST).length - 1, (LIST).loopNode = (LIST).tail; (LIST).loopVar > INDEX; (LIST).loopVar--, (LIST).loopNode = (LIST).loopNode->former) \
            ;                                                                                                                                        \
    } else {                                                                                                                                         \
        for ((LIST).loopVar = 0, (LIST).loopNode = (LIST).head; (LIST).loopVar < INDEX; (LIST).loopVar++, (LIST).loopNode = (LIST).loopNode->after)                \
            ;                                                                                                                                        \
    }                                                                                                                                                \
    (LIST).loopNode->content;                                                                                                                          \
})

/**
 * @brief 链表元素交换
 * @param LIST 链表名
 * @param iINDEX 第一个元素的位置(0 到 list_length-1)
 * @param jINDEX 第二个元素的位置(0 到 list_length-1)
 */
#define list_swap(LIST, iINDEX, jINDEX) ({                                                                                                                        \
    assert(iINDEX < (LIST).length && jINDEX < (LIST).length);                                                                                                         \
    if (iINDEX != jINDEX) {                                                                                                                                       \
        for ((LIST).loopVar = 0, (LIST).loopNode = (LIST).head; (LIST).loopVar < iINDEX || (LIST).loopVar < jINDEX; (LIST).loopVar++, (LIST).loopNode = (LIST).loopNode->after) { \
            if ((LIST).loopVar == iINDEX || (LIST).loopVar == jINDEX)                                                                                                 \
                (LIST).tempNode = (LIST).loopNode;                                                                                                                    \
        }                                                                                                                                                         \
        (LIST).OUTPUT = (LIST).tempNode->content;                                                                                                                     \
        (LIST).tempNode->content = (LIST).loopNode->content;                                                                                                          \
        (LIST).loopNode->content = (LIST).OUTPUT;                                                                                                                     \
    }                                                                                                                                                             \
})

/**
 * @brief 链表单个元素删除
 * @param LIST 链表名
 * @param INDEX 删除元素位置(0 到 (list).length-1)
 * @return 被删除元素
 */
#define list_remove(LIST, INDEX) ({                                                                                                                      \
    if ((LIST).length - 1 == INDEX) {                                                                                                                      \
        list_popback(LIST);                                                                                                                              \
    } else if (INDEX == 0) {                                                                                                                             \
        list_popfront(LIST);                                                                                                                             \
    } else {                                                                                                                                             \
        if (INDEX > (LIST).length / 2) {                                                                                                                   \
            for ((LIST).loopVar = (LIST).length - 1, (LIST).loopNode = (LIST).tail; (LIST).loopVar > INDEX; (LIST).loopVar--, (LIST).loopNode = (LIST).loopNode->former) \
                ;                                                                                                                                        \
        } else {                                                                                                                                         \
            for ((LIST).loopVar = 0, (LIST).loopNode = (LIST).head; (LIST).loopVar < INDEX; (LIST).loopVar++, (LIST).loopNode = (LIST).loopNode->after)                \
                ;                                                                                                                                        \
        }                                                                                                                                                \
        (LIST).loopNode->after->former = (LIST).loopNode->former;                                                                                            \
        (LIST).loopNode->former->after = (LIST).loopNode->after;                                                                                             \
        (LIST).loopNode->after = (LIST).loopNode->former = NULL;                                                                                             \
        (LIST).OUTPUT = (LIST).loopNode->content;                                                                                                            \
        free((LIST).loopNode);                                                                                                                             \
        (LIST).length--;                                                                                                                                   \
    }                                                                                                                                                    \
    (LIST).OUTPUT;                                                                                                                                         \
})

/**
 * @brief 链表元素条件删除
 * @param LIST 链表名
 * @param CONDITION 条件函数(可以是宏函数也可以不是)
 * @param ... 其它参数(指条件函数需要的其它参数，不需要则不填)
 * @return 删除是否成功
 */
#define list_remove_if(LIST, CONDITION, _VA_ARGS_...) ({                                    \
    (LIST).loopVar = (LIST).length;                                                             \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != NULL; (LIST).loopNode = (LIST).tempNode) { \
        (LIST).tempNode = (LIST).loopNode->after;                                               \
        if (CONDITION((LIST).loopNode->content, ##_VA_ARGS_)) {                               \
            if ((LIST).loopNode->former)                                                      \
                (LIST).loopNode->former->after = (LIST).loopNode->after;                        \
            else                                                                            \
                (LIST).head = (LIST).loopNode->after;                                           \
            if ((LIST).loopNode->after)                                                       \
                (LIST).loopNode->after->former = (LIST).loopNode->former;                       \
            else                                                                            \
                (LIST).tail = (LIST).loopNode->former;                                          \
            (LIST).loopNode->after = (LIST).loopNode->former = NULL;                            \
            free((LIST).loopNode);                                                            \
            (LIST).length--;                                                                  \
        }                                                                                   \
    }                                                                                       \
    (LIST).loopVar != (LIST).length;                                                            \
})

/**
 * @brief 链表元素条件删除前n个
 * @param LIST 链表名
 * @param N 欲删除个数
 * @param CONDITION 条件函数(可以是宏函数也可以不是)
 * @param ... 其它参数(指条件函数需要的其它参数，不需要则不填)
 * @return 删除是否成功
 */
#define list_removeN_if(LIST, N, CONDITION, _VA_ARGS_...) ({                                                \
    (LIST).loopVar = N;                                                                                       \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != NULL && (LIST).loopVar; (LIST).loopNode = (LIST).tempNode) { \
        (LIST).tempNode = (LIST).loopNode->after;                                                               \
        if (CONDITION((LIST).loopNode->content, ##_VA_ARGS_)) {                                               \
            if ((LIST).loopNode->former)                                                                      \
                (LIST).loopNode->former->after = (LIST).loopNode->after;                                        \
            else                                                                                            \
                (LIST).head = (LIST).loopNode->after;                                                           \
            if ((LIST).loopNode->after)                                                                       \
                (LIST).loopNode->after->former = (LIST).loopNode->former;                                       \
            else                                                                                            \
                (LIST).tail = (LIST).loopNode->former;                                                          \
            (LIST).loopNode->after = (LIST).loopNode->former = NULL;                                            \
            free((LIST).loopNode);                                                                            \
            (LIST).length--;                                                                                  \
            (LIST).loopVar--;                                                                                 \
        }                                                                                                   \
    }                                                                                                       \
    (LIST).loopVar != N;                                                                                      \
})

/**
 * @brief 链表范围删除
 * @param LIST 链表名
 * @param _BEGIN_INDEX 起始地址(包含)
 * @param _END_INDEX 终止地址(不包含)
 */
#define list_remove_range(LIST, _BEGIN_INDEX, _END_INDEX) ({                                                                                                \
    assert(_BEGIN_INDEX < (LIST).length && _END_INDEX < (LIST).length && _BEGIN_INDEX < _END_INDEX);                                                            \
    if (_BEGIN_INDEX > (LIST).length / 2) {                                                                                                                   \
        for ((LIST).loopVar = (LIST).length - 1, (LIST).loopNode = (LIST).tail; (LIST).loopVar > _BEGIN_INDEX; (LIST).loopVar--, (LIST).loopNode = (LIST).loopNode->former) \
            ;                                                                                                                                               \
    } else {                                                                                                                                                \
        for ((LIST).loopVar = 0, (LIST).loopNode = (LIST).head; (LIST).loopVar < _BEGIN_INDEX; (LIST).loopVar++, (LIST).loopNode = (LIST).loopNode->after)                \
            ;                                                                                                                                               \
    }                                                                                                                                                       \
    for (; (LIST).loopVar < _END_INDEX; (LIST).loopNode = (LIST).tempNode, (LIST).loopVar++) {                                                                      \
        (LIST).tempNode = (LIST).loopNode->after;                                                                                                               \
        if ((LIST).loopNode->former)                                                                                                                          \
            (LIST).loopNode->former->after = (LIST).loopNode->after;                                                                                            \
        else                                                                                                                                                \
            (LIST).head = (LIST).loopNode->after;                                                                                                               \
        if ((LIST).loopNode->after)                                                                                                                           \
            (LIST).loopNode->after->former = (LIST).loopNode->former;                                                                                           \
        else                                                                                                                                                \
            (LIST).tail = (LIST).loopNode->former;                                                                                                              \
        (LIST).loopNode->after = (LIST).loopNode->former = NULL;                                                                                                \
        free((LIST).loopNode);                                                                                                                                \
    }                                                                                                                                                       \
    (LIST).length -= _END_INDEX - _BEGIN_INDEX;                                                                                                               \
})

/**
 * @brief 检查链表包含元素
 * @param LIST 链表名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 */
#define list_has(LIST, COMPARATION, _VA_ARGS_...) ({                                                                                                    \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != NULL && !(COMPARATION((LIST).loopNode->content, ##_VA_ARGS_)); (LIST).loopNode = (LIST).loopNode->after) \
        ;                                                                                                                                               \
    (LIST).loopNode != NULL;                                                                                                                              \
})

/**
 * @brief 链表元素查找
 * @param LIST 链表名
 * @param COMPARATION 比较函数(可宏函数也可不宏函数)
 * @param ... 其它参数(指比较函数需要的其它参数，不需要则不填)
 * @return 返回查找的元素
 * @attention 规定没找到返回0
 */
#define list_find(LIST, COMPARATION, _VA_ARGS_...) ({                                                                                                   \
    for ((LIST).loopNode = (LIST).head; (LIST).loopNode != NULL && !(COMPARATION((LIST).loopNode->content, ##_VA_ARGS_)); (LIST).loopNode = (LIST).loopNode->after) \
        ;                                                                                                                                               \
    (LIST).loopNode ? (LIST).loopNode->content : 0;                                                                                                         \
})

/**
 * @brief 链表元素循环头
 * @param LIST 链表名
 * @param ELEMENT_POINTER 元素指针(便于改写元素)
 * @param BEGIN [可选参数]起始元素位置(包含这个位置)
 * @param END [可选参数]结束元素位置(不包含这个位置)
 * @attention BEGIN不选默认为0位置起始，END不选默认为最后一个元素的下一位，选择END之前必选BEGIN
 */
#define _LIST_FOREACH(LIST, ELEMENT_POINTER, _VA_ARGS_...) _LIST_FOREACH_analysis(LIST, ELEMENT_POINTER, ##_VA_ARGS_, _LIST_FOREACH2, _LIST_FOREACH1, _LIST_FOREACH0)

#define _LIST_FOREACH_analysis(LIST, ELEMENT_POINTER, _begin, _end, _list_foreach_function, _VA_ARGS_...) _list_foreach_function(LIST, ELEMENT_POINTER, _begin, _end)

#define _LIST_FOREACH0(LIST, ELEMENT_POINTER, ABANDON1, ABANDON2) for ((LIST).loopNode = (LIST).head; ((LIST).loopNode != NULL) && (ELEMENT_POINTER = &((LIST).loopNode->content)); (LIST).loopNode = (LIST).loopNode->after)

#define _LIST_FOREACH1(LIST, ELEMENT_POINTER, BEGIN, ABANDON) for (list_get(LIST, BEGIN); ((LIST).loopNode != NULL) && (ELEMENT_POINTER = &((LIST).loopNode->content)); (LIST).loopNode = (LIST).loopNode->after)

#define _LIST_FOREACH2(LIST, ELEMENT_POINTER, BEGIN, END) for (list_get(LIST, BEGIN), (LIST).loopVar = BEGIN; ((LIST).loopVar < END) && ((LIST).loopNode != NULL) && (ELEMENT_POINTER = &((LIST).loopNode->content)); (LIST).loopNode = (LIST).loopNode->after, (LIST).loopVar++)

#endif

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
 *
 * 工具
 */
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/**
 * @brief 进制转化(36进制内)
 *
 * @param resource 源进制字符串
 * @param ResourseBase 源串进制
 * @param AnswerBase 目标进制
 * @return 目标字符串
 * @attention 返回的答案字符串内存请用户自行管理(使用free释放)
 */
char* BaseConversion(char* resource, int ResourseBase, int AnswerBase)
{
#define _BC_inner_char2int(c) (c <= '9' ? c - '0' : c <= 'Z' ? c - 'A' + 10 \
                                                             : c - 'a' + 10)
#define _BC_inner_int2char(n) (n < 10 ? '0' + n : 'A' + n - 10)
    int j = 0, temp, len = 0;
    while (resource[j++] != 0)
        ;
    // 粗略计算中间答案长度
    temp = ResourseBase;
    while (AnswerBase < temp) { 
        len++;
        temp /= AnswerBase;
    }
    len += temp != 1;
    //||||||||||||||||||||||||||||||||||||||||
    char* midans = (char*)calloc(len * j, 1);
    for (size_t i = 0; resource[i]; i++) {
        temp = _BC_inner_char2int(resource[i]); // 检错
        if (temp >= ResourseBase)
            return 0;
        for (j = 0; j < len || temp; j++, temp /= AnswerBase) {
            temp += midans[j] * ResourseBase;
            midans[j] = temp % AnswerBase;
        }
        len = j;
    }
    //输出模块
    char* answer = (char*)malloc(len + 1);
    len--;
    for (size_t i = 0; i <= len; i++) {
        answer[i] = _BC_inner_int2char(midans[len - i]);
    }
    free(midans);
    answer[len + 1] = 0;
    return answer;
}

#endif