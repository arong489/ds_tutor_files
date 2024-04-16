/**
 * @brief 这是一个列表排序函数，它的思想是双向归并排序算法
 *
 * @param listNode:该列表的头节点指针
 * @param listNum:列表节点总数
 * @param get_nextNode:获取下一个节点指针的函数
 * @param set_nextNode:设置第二个节点在第一个节点之后的函数
 * !ATTATION:如果它是双链表，我们应该检查第二个节点是否为NULL
 * @param cmp_function:比较两个节点的函数。如果它的返回值大于零，那么两个节点的顺序将颠倒
 * @return void*:该列表的头节点指针
 * !ATTATION:如果是双链表，头节点的前向指针不会初始化为“NULL”
 */
void* list_twoMerge_sort(void* listNode, const unsigned int listNum, void* get_nextNode(const void*), void set_nextNode(const void*, const void*), int (*cmp_function)(const void*, const void*))
{
    if (listNum < 2 || cmp_function == NULL || get_nextNode == NULL)
        return listNode;

    // initialize
    unsigned int ltMs_tempPts_len = (listNum + 1) >> 1;
    void *ltMs_tempPts[ltMs_tempPts_len], *ltMs_tempPtA, *ltMs_tempPtB, *ltMs_tempPt;
    for (unsigned int ltMs_i = 0; ltMs_i < listNum; ltMs_i++) {
        if (ltMs_i & 1) {
            ltMs_tempPt = get_nextNode(listNode);
            if (cmp_function(ltMs_tempPts[ltMs_i >> 1], listNode) > 0) {
                set_nextNode(listNode, ltMs_tempPts[ltMs_i >> 1]);
                set_nextNode(ltMs_tempPts[ltMs_i >> 1], NULL);
                ltMs_tempPts[ltMs_i >> 1] = listNode;
            } else {
                set_nextNode(ltMs_tempPts[ltMs_i >> 1], listNode);
                set_nextNode(listNode, NULL);
            }
            listNode = ltMs_tempPt;
        } else {
            ltMs_tempPts[ltMs_i >> 1] = listNode;
            listNode = get_nextNode(listNode);
        }
    }

    char ltMs_likely;
    for (unsigned int ltMs_i = 1; ltMs_i < ltMs_tempPts_len; ltMs_i <<= 1) {
        for (unsigned int ltMs_j = 0; ltMs_j + ltMs_i < ltMs_tempPts_len; ltMs_j += 2 * ltMs_i) {
            ltMs_tempPtA = ltMs_tempPts[ltMs_j];
            ltMs_tempPtB = ltMs_tempPts[ltMs_j + ltMs_i];
            if (cmp_function(ltMs_tempPtA, ltMs_tempPtB) > 0) {
                ltMs_tempPts[ltMs_j] = ltMs_tempPt = ltMs_tempPtB;
                ltMs_tempPtB = get_nextNode(ltMs_tempPtB);
                ltMs_likely = 1;
            } else {
                ltMs_tempPts[ltMs_j] = ltMs_tempPt = ltMs_tempPtA;
                ltMs_tempPtA = get_nextNode(ltMs_tempPtA);
                ltMs_likely = 0;
            }
            do {
                if (ltMs_likely) { // B is likely to be inserted in the ans list
                    while (ltMs_tempPtB && cmp_function(ltMs_tempPtA, ltMs_tempPtB) > 0) {
                        ltMs_tempPt = ltMs_tempPtB;
                        ltMs_tempPtB = get_nextNode(ltMs_tempPtB);
                    }
                    // turn to 'A' branch
                    set_nextNode(ltMs_tempPt, ltMs_tempPtA);
                    ltMs_tempPt = ltMs_tempPtA;
                    ltMs_tempPtA = get_nextNode(ltMs_tempPtA);
                    ltMs_likely = 0;
                } else {
                    while (ltMs_tempPtA && cmp_function(ltMs_tempPtB, ltMs_tempPtA) > 0) {
                        ltMs_tempPt = ltMs_tempPtA;
                        ltMs_tempPtA = get_nextNode(ltMs_tempPtA);
                    }
                    set_nextNode(ltMs_tempPt, ltMs_tempPtB);
                    ltMs_tempPt = ltMs_tempPtB;
                    ltMs_tempPtB = get_nextNode(ltMs_tempPtB);
                    ltMs_likely = 1;
                }
            } while ((!ltMs_likely && ltMs_tempPtB) || (ltMs_likely && ltMs_tempPtA));
        }
    }

    return ltMs_tempPts[0];
}
/**
 * @brief 链表辅助结构，务必在链表结点中包含名为linker的成员
 * @param struct_type 结构体类型
 */
#define define_linker(STRUCT_TYPE)  \
    struct {                        \
        STRUCT_TYPE *former, *next; \
    }

/**
 * @brief 全局函数，使链表的某一个link_part有效
 * @param STRUCT_TYPE 节点结构体名
 * @param link_part 链接结构块名
 */
#define list_effective(STRUCT_TYPE, link_part)                \
    STRUCT_TYPE *TEMP_##link_part, *TEMP_foreach_##link_part; \
    char link_part##_delete_checker;                          \
    int link_part##_length;

/**
 * @brief 链表插入
 * @param HEADER 头节点名，为了防止头节点前插入
 * @param linker 链接结构块名
 * @param NODE 当前位置节点指针
 * @param OFFSET 偏移量(-1插在左边，0默认插在右边，超界自动在最边缘插入)
 * @param WAITTOINSERT 欲插入节点指针
 */
#define list_insert(HEADER, linker, NODE, OFFSET, WAITTOINSERT) __list_insert(HEADER, linker, NODE, OFFSET, WAITTOINSERT)

#define __list_insert(HEADER, linker, NODE, OFFSET, WAITTOINSERT) ({                     \
    if (NODE == NULL)                                                                    \
        NODE = WAITTOINSERT, NODE->linker.former = NODE->linker.next = NULL;             \
    else {                                                                               \
        TEMP##_##linker = NODE;                                                          \
        if (OFFSET >= 0)                                                                 \
            for (size_t list_insert_i = 0;; list_insert_i++) {                           \
                if (list_insert_i == OFFSET || (TEMP##_##linker)->linker.next == NULL) { \
                    WAITTOINSERT->linker.next = (TEMP##_##linker)->linker.next;          \
                    if ((TEMP##_##linker)->linker.next != NULL)                          \
                        (TEMP##_##linker)->linker.next->linker.former = WAITTOINSERT;    \
                    WAITTOINSERT->linker.former = (TEMP##_##linker);                     \
                    (TEMP##_##linker)->linker.next = WAITTOINSERT;                       \
                    (TEMP##_##linker) = NULL;                                            \
                    break;                                                               \
                }                                                                        \
                (TEMP##_##linker) = (TEMP##_##linker)->linker.next;                      \
            }                                                                            \
        else                                                                             \
            for (int list_insert_i = 0;; list_insert_i--) {                              \
                if (list_insert_i == OFFSET) {                                           \
                    WAITTOINSERT->linker.next = (TEMP##_##linker)->linker.next;          \
                    if ((TEMP##_##linker)->linker.next != NULL)                          \
                        (TEMP##_##linker)->linker.next->linker.former = WAITTOINSERT;    \
                    WAITTOINSERT->linker.former = (TEMP##_##linker);                     \
                    (TEMP##_##linker)->linker.next = WAITTOINSERT;                       \
                    (TEMP##_##linker) = NULL;                                            \
                    break;                                                               \
                }                                                                        \
                if ((TEMP##_##linker)->linker.former != NULL) {                          \
                    (TEMP##_##linker) = (TEMP##_##linker)->linker.former;                \
                } else {                                                                 \
                    (TEMP##_##linker)->linker.former = WAITTOINSERT;                     \
                    WAITTOINSERT->linker.former = NULL;                                  \
                    WAITTOINSERT->linker.next = (TEMP##_##linker);                       \
                    HEADER = WAITTOINSERT;                                               \
                    break;                                                               \
                }                                                                        \
            }                                                                            \
    }                                                                                    \
})

/**
 * @brief 链表删除
 * @param HEADER 头节点名，为了防止头节点删除
 * @param linker 链接结构名
 * @param NODE 当前位置节点指针
 * @param OFFSET 偏移量(0删除其本身，-1删除前序节点，1删除后序节点，超界删除边界节点)
 * @param FEEDBACK 删除反馈承接(只辅助重链表中拿出来，删除需要自己完成)
 * @note 当前节点NODE被删除时会自动指向下一个节点
 */
#define list_delete(HEADER, linker, NODE, OFFSET, FEEDBACK) __list_delete(HEADER, linker, NODE, OFFSET, FEEDBACK)

#define __list_delete(HEADER, linker, NODE, OFFSET, FEEDBACK) ({                                                              \
    if (NODE == NULL)                                                                                                         \
        FEEDBACK = NULL;                                                                                                      \
    else {                                                                                                                    \
        TEMP##_##linker = NODE;                                                                                               \
        if (OFFSET > 0)                                                                                                       \
            for (size_t list_insert_i = 0; list_insert_i < OFFSET && (TEMP##_##linker)->linker.next != NULL; list_insert_i++) \
                (TEMP##_##linker) = (TEMP##_##linker)->linker.next;                                                           \
        else if (OFFSET < 0)                                                                                                  \
            for (int list_insert_i = 0; list_insert_i > OFFSET && (TEMP##_##linker)->linker.former != NULL; list_insert_i--)  \
                (TEMP##_##linker) = (TEMP##_##linker)->linker.former;                                                         \
        else                                                                                                                  \
            NODE = NODE->linker.next;                                                                                         \
        FEEDBACK = (TEMP##_##linker);                                                                                         \
        if (FEEDBACK == TEMP##_##foreach##_##linker && FEEDBACK)                                                              \
            linker##_delete_checker = 1, TEMP##_##foreach##_##linker = FEEDBACK->linker.next;                                 \
        if (FEEDBACK->linker.former != NULL)                                                                                  \
            FEEDBACK->linker.former->linker.next = FEEDBACK->linker.next;                                                     \
        else                                                                                                                  \
            HEADER = FEEDBACK->linker.next;                                                                                   \
        if (FEEDBACK->linker.next != NULL)                                                                                    \
            FEEDBACK->linker.next->linker.former = FEEDBACK->linker.former;                                                   \
    }                                                                                                                         \
})

/**
 * @brief 链表定位
 * @param NODE 当前位置节点指针
 * @param linker 链接结构名
 * @param OFFSET 偏移量(-1获取左边，0默认获取本身，1获取右边，右超界自动获取NULL， 左超界获取头节点)
 * @param FEEDBACK 反馈指针
 */
#define list_get(NODE, linker, OFFSET, FEEDBACK) __list_get(NODE, linker, OFFSET, FEEDBACK)

#define __list_get(NODE, linker, OFFSET, FEEDBACK) ({                                                               \
    if (NODE != NULL) {                                                                                             \
        FEEDBACK = NODE;                                                                                            \
        if (OFFSET > 0)                                                                                             \
            for (size_t list_insert_i = 0; list_insert_i < OFFSET && FEEDBACK != NULL; list_insert_i++)             \
                FEEDBACK = FEEDBACK->linker.next;                                                                   \
        else if (OFFSET < 0)                                                                                        \
            for (int list_insert_i = 0; list_insert_i > OFFSET && FEEDBACK->linker.former != NULL; list_insert_i--) \
                FEEDBACK = FEEDBACK->linker.former;                                                                 \
    } else                                                                                                          \
        FEEDBACK = NULL;                                                                                            \
    FEEDBACK;                                                                                                       \
})

/**
 * @brief 链表判空
 * @param HEADNODE 链表头指针
 * @return 布尔值
 */
#define list_empty(HEADNODE) (HEADNODE == NULL)

/**
 * @brief 获取当前链表节点到末尾的长度
 * @param NODE 链表节点指针
 * @param linker 链接结构名
 * @return 长度(int)
 * @note 出于效率考量，请不要频繁重复地使用这个方法
 */
#define list_length(NODE, linker) list_length_feedback(NODE, linker, TEMP##_##linker)

/**
 * @brief 获取当前链表节点到末尾的长度
 * @param NODE 链表节点指针
 * @param linker 链接结构名
 * @param FEEDBACK 反馈尾节点
 * @return 长度(int)
 * @note 出于效率考量，请不要频繁重复地使用这个方法
 */
#define list_length_feedback(NODE, linker, FEEDBACK)                 \
    ({                                                               \
        FEEDBACK = NODE;                                             \
        linker##_length = 0;                                         \
        if (NODE != NULL) {                                          \
            linker##_length = 1;                                     \
            while (FEEDBACK->linker.next != NULL)                    \
                linker##_length++, FEEDBACK = FEEDBACK->linker.next; \
        }                                                            \
        linker##_length;                                             \
    })

/**
 * @brief 对节点内容进行批量操作
 * @param NODE 链表节点指针
 * @param linker 链接结构名
 * @param LENGTH 对NODE及之后LENGTH个节点进行操作
 * @param OPERATION 操作函数
 * @note 长度过长时在尾节点结束
 */
#define list_foreach(NODE, linker, LENGTH, OPERATION)                                                                    \
    ({                                                                                                                   \
        TEMP##_##foreach##_##linker = NODE;                                                                              \
        linker##_delete_checker = 0;                                                                                     \
        for (size_t list_insert_i = 0; list_insert_i < LENGTH && TEMP##_##foreach##_##linker != NULL; list_insert_i++) { \
            OPERATION(TEMP##_##foreach##_##linker);                                                                      \
            if (!linker##_delete_checker)                                                                                \
                TEMP##_##foreach##_##linker = TEMP##_##foreach##_##linker->linker.next;                                  \
            else                                                                                                         \
                linker##_delete_checker = 0;                                                                             \
        }                                                                                                                \
    })