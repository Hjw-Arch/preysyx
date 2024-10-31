#include "ex32.h"
#include <stdio.h>
#include <assert.h>

List *List_create() {
    List *list = calloc(1, sizeof(List));
    if (!list) assert(0);
    return list;
}

#define mu_assert(cond, ...)    \
do {    \
    if (!(cond)) {  \
        printf(__VA_ARGS__);   \
    }    \
} while(0)  

void List_destroy(List *list) {
    ListNode *node = NULL;
    for (node = list->first; node->next != NULL; node = node->next) {
        if (node->prev) {
            free(node->prev);
        }
    }
    free(node);
}

void List_clear(List *list) {
    ListNode *node = NULL;
    for (node = list->first; node != NULL; node = node->next) {
        if (node->value) {
            free(node->value);
        }
    }
}

void List_clear_destroy(List *list) {
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    if (!node) assert(0);

    node->value = value;

    if (list->last == NULL) {
        list->last = node;
        list->first = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
}

void *List_remove(List *list, ListNode *node) {
    if (!list->count) return NULL;

    if (list->count == 1 && list->first == node) {
        list->first = NULL;
        list->last = NULL;
        goto free;
    }

    if (node == list->first) {
        node->next->prev = NULL;
        list->first = node->next;
        goto free;
    }

    if (node == list->last) {
        node->prev->next = NULL;
        list->last = node->prev;
        goto free;
    }

    ListNode *_node = NULL;
    for (_node = list->first->next; _node != list->last; _node = _node->next) {
        if (node == _node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            goto free;
        }
    }
    
    puts("Error node");
    assert(0);

free:
    list->count--;
    void *val = node->value;
    free(node);
    return val;
}

void *List_pop(List *list) {
    return List_remove(list, list->last);
}

void List_unshift(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    if (!node) assert(0);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

}

void *List_shift(List *list) {
    return List_remove(list, list->first);
}

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;

}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list)->value == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list)->value == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list)->value == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    // val = List_pop(list);
    // mu_assert(val == test2, "Wrong value on pop.");

    // val = List_pop(list);
    // mu_assert(val == test1, "Wrong value on pop.");
    // mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}



char *all_tests() {

    test_create();
    test_push_pop();
    // test_unshift();
    // test_remove();
    // test_shift();
    // test_destroy();

    return NULL;
}



int main() {
    all_tests();
    return 0;
}