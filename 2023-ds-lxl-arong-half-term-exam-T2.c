#include <stdio.h>
#include <stdlib.h>
struct T2 {
    int id, times;
    struct T2* next;
} Header, *tail = &Header;
int main(int argc, char const* argv[])
{
    int n, m;
    unsigned long long tot = 0;
    struct T2 *cur, *pre;
    // freopen("./data/2023-ds-lxl-arong-half-term-exam-T2/1.in", "r", stdin);
    scanf("%d", &n);
    for (unsigned int i = 0; i < n; i++) {
        scanf("%d", &m);
        pre = &Header;
        cur = Header.next;
        while (cur != NULL && cur->id != m) {
            tot++;
            pre = cur;
            cur = cur->next;
        }
        if (cur) {
            tot++;
            cur->times++;
            if (Header.next != cur) {
                if (cur == tail)
                    tail = pre;
                pre->next = cur->next;
                cur->next = Header.next;
                Header.next = cur;
            }
        } else {
            cur = (struct T2*)malloc(sizeof(struct T2));
            cur->id = m;
            cur->times = 1;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
        }
    }
    cur = Header.next;
    for (unsigned int i = 0; i < 5 && cur; i++, cur = cur->next) {
        printf("%d %d\n", cur->id, cur->times);
    }
    printf("%llu", tot);
    return 0;
}