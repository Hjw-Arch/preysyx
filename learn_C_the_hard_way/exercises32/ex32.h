#ifndef EX32_H
#define EX32_H

#include <stdlib.h>

struct ListNode;

typedef struct ListNode
{
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destory(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first)
#define List_last(A)  ((A)->last)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);





#endif