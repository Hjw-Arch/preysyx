#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

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
    for (node = list->first; node != NULL; node = node->next) {
        if (node->prev) {
            free(node->prev);
        }
    }
    free(node);
    free(list);
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
    node->next = NULL;
    node->prev = NULL;

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


void *List_copy(List *list) {
    List *new_list = calloc(1, sizeof(List));
    if (!new_list) assert(0);

    for (ListNode *node = list->first; node != NULL; node = node->next) {
        List_push(new_list, node->value);
    }

    return new_list;
}


// static Stack *stack = NULL;
// char *tests[] = {"test1 data", "test2 data", "test3 data"};
// #define NUM_TESTS 3


// char *test_create()
// {
//     stack = Stack_create();
//     mu_assert(stack != NULL, "Failed to create stack.");

//     return NULL;
// }

// char *test_destroy()
// {
//     mu_assert(stack != NULL, "Failed to make stack #2");
//     Stack_destroy(stack);

//     return NULL;
// }

// char *test_push_pop()
// {
//     int i = 0;
//     for(i = 0; i < NUM_TESTS; i++) {
//         Stack_push(stack, tests[i]);
//         mu_assert(Stack_peek(stack) == tests[i], "Wrong next value.");
//     }

//     mu_assert(Stack_count(stack) == NUM_TESTS, "Wrong count on push.");


//     for(i = NUM_TESTS - 1; i >= 0; i--) {
//         char *val = Stack_pop(stack);
//         mu_assert(val == tests[i], "Wrong value on pop.");
//     }

//     mu_assert(Stack_count(stack) == 0, "Wrong count after pop.");

//     return NULL;
// }

static Queue *queue = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3


char *test_create()
{
    queue = Queue_create();
    mu_assert(queue != NULL, "Failed to create queue.");

    return NULL;
}

char *test_destroy()
{
    mu_assert(queue != NULL, "Failed to make queue #2");
    Queue_destroy(queue);

    return NULL;
}

char *test_send_recv()
{
    int i = 0;
    for(i = 0; i < NUM_TESTS; i++) {
        Queue_send(queue, tests[i]);
        mu_assert(Queue_peek(queue) == tests[0], "Wrong next value.");
    }

    mu_assert(Queue_count(queue) == NUM_TESTS, "Wrong count on send.");

    for(i = 0; i < NUM_TESTS; i++) {
        char *val = Queue_recv(queue);
        mu_assert(val == tests[i], "Wrong value on recv.");
    }

    mu_assert(Queue_count(queue) == 0, "Wrong count after recv.");

    return NULL;
}

char *all_tests() {
    test_create();
    test_send_recv();
    test_destroy();


    return NULL;
}

int main() {
    all_tests();
    return 0;
}