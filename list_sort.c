#include<stdlib.h>
#include"dsdiy.h"
#include<stdio.h>
#define print(LIST) \
while (LIST != NULL) {\
	printf("%d ", LIST->num);\
	LIST = LIST->next;\
}

struct vstest1 {
	int num;
	struct vstest1 *next;
};// single linked list

struct vstest2 {
	int num;
	struct vstest2 *pre,*next;
};// double linked list
int cmp1(const void* e1, const void* e2) {
	return ((struct vstest1*)e1)->num < ((struct vstest1*)e2)->num ? -1 : 1;
}

int cmp2(const void* e1, const void* e2) {
	return ((struct vstest2*)e1)->num < ((struct vstest2*)e2)->num ? -1 : 1;
}

void *get_next1(const void* e) {
	return ((struct vstest1*)e)->next;
}

void *get_next2(const void* e) {
	return ((struct vstest2*)e)->next;
}

void set_next1(const void* e1, const void* e2) {
	((struct vstest1*)e1)->next = (struct vstest1*)e2;
}

//! check if "e2" is "NULL"
void set_next2(const void* e1, const void* e2) {
	((struct vstest2*)e1)->next = (struct vstest2*)e2;
	if (e2 != NULL) ((struct vstest2*)e2)->pre = (struct vstest2*)e1;
}


int main(int argc, char const *argv[]) {
	struct vstest1 *head1 = 0, *p1, *tail1;
	struct vstest2 *head2 = 0, *p2, *tail2;
	int newNum, len1 = 0, len2 = 0;
	system("chcp 65001 1>nul");
	while (~scanf("%d", &newNum)) {
		p1 = (struct vstest1*)malloc(sizeof(struct vstest1));
		p1->next = NULL;
		p1->num = newNum;
		if (head1 == NULL) tail1 = head1 = p1;
		else tail1->next = p1, tail1 = p1;
		len1++;

		p2 = (struct vstest2*)malloc(sizeof(struct vstest2));
		p2->next = p2->pre = NULL;
		p2->num = newNum;
		if (head2 == NULL) tail2 = head2 = p2;
		else tail2->next = p2, p2->pre = tail2, tail2 = p2;
		len2++;
	}

	head1 = (struct vstest1*) list_twoMerge_sort(head1, len1, get_next1, set_next1, cmp1);
	head2 = (struct vstest2*) list_twoMerge_sort(head2, len2, get_next2, set_next2, cmp2);
	// we should maintain the forward pointer of head node on our own
	// 我们应该自己维护头节点的前序指针
	// head2->pre = NULL;
	
	fputs("单向链表排序结果:\n",stdout);
	print(head1);
	fputs("\n双向链表排序结果:\n",stdout);
	print(head2);
	return 0;
}