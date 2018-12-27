#ifndef _SLIST_H_
#define _SLIST_H_

#include "def.h"

typedef struct SingleListNode SLNode;
struct SingleListNode{
    void *data;
    SLNode *next;
};

typedef struct SingleList SList;
struct SingleList{
    SLNode head;//头节点
    uint32_t length;//链表长度
};

SList *slist_create(void);
Ret slist_append(SList *slist, void *data);
Ret slist_prepend(SList *slist, void *data);
Ret slist_insert(SList* slist, uint32_t nth, void *data);
Ret slist_delete(SList* slist, uint32_t nth, void **data);
Ret slist_get_nth_data(SList *slist, uint32_t nth, void **data);
void slist_traverse(SList *slist, VisitFunc func, void *user_data);
int32_t slist_count_length(SList *slist);
void slist_destroy(SList *slist);
void slist_sort_merge(SList *slist1, SList *slist2, SList *slist3, CompareFunc compare_func, void *user_data);
#endif // _SLIST_H_


