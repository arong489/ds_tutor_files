#include "dsdiy.h"
typedef struct LoginData {
    int id;
    char name[16];
    int machineId;
    int time;
}* LoginDataPtr;

typedef define_list(LoginDataPtr) LoginDataList;
define_stack(200, LoginDataPtr) errors;

char findStudent(LoginDataPtr loginDataPtr, int id)
{
    return loginDataPtr->id == id;
}

// void print(LoginDataPtr loginDataPtr) {
//     printf("%d %s\n", loginDataPtr->id, loginDataPtr->name);
// }

#define print(loginDataPtr) (printf("%d %s\n", loginDataPtr->id, loginDataPtr->name))

int cmp(const void* a, const void* b) {
    LoginDataPtr pa = *(LoginDataPtr*)a, pb = *(LoginDataPtr*)b;
    return pa->id < pb->id ? -1 : 1;
}

int main(int argc, char const* argv[])
{
    LoginDataList loginDatas;
    list_flush(loginDatas);
    stack_flush(errors, 200);
    LoginDataPtr loginDataPtr;
    int loginDataNum;
    scanf("%d", &loginDataNum);
    int id, j, machineId, time;
    char name[16];
    for (int i = 0; i < loginDataNum; i++) {
        scanf("%d%s%d%d", &id, name, &machineId, &time);
        loginDataPtr = list_find(loginDatas, findStudent, id);
        if (loginDataPtr == NULL) {
            loginDataPtr = (LoginDataPtr)malloc(sizeof(struct LoginData));
            loginDataPtr->id = id;
            loginDataPtr->machineId = machineId;
            loginDataPtr->time = time;
            j = -1;
            do {
                j++;
                loginDataPtr->name[j] = name[j];
            } while (name[j]);
            list_pushback(loginDatas, loginDataPtr);
        } else {
            if (loginDataPtr->machineId != machineId) {
                if (stack_find(errors, findStudent, id) == NULL) {
                    stack_push(errors, loginDataPtr);
                }
            }
        }
    }
    qsort(errors.ELEM, stack_length(errors), sizeof(LoginDataPtr), cmp);
    stack_foreach(errors, print);
    return 0;
}