#include "ex33.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

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


void bubble_sort(List *list) {
    if (!list || list->count < 2) return;

    int swapped;
    do {
        swapped = 0;
        ListNode *current = list->first;

        while (current && current->next) {
            char *str1 = (char *)current->value;
            char *str2 = (char *)current->next->value;

            if (strcmp(str1, str2) > 0) {
                // Swap values
                current->value = str2;
                current->next->value = str1;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// 合并两个有序列表
List *merge(List *left, List *right) {
    List *result = List_create();
    ListNode *leftNode = left->first;
    ListNode *rightNode = right->first;

    while (leftNode && rightNode) {
        if (strcmp((char *)leftNode->value, (char *)rightNode->value) <= 0) {
            List_push(result, leftNode->value);
            leftNode = leftNode->next;
        } else {
            List_push(result, rightNode->value);
            rightNode = rightNode->next;
        }
    }

    while (leftNode) {
        List_push(result, leftNode->value);
        leftNode = leftNode->next;
    }

    while (rightNode) {
        List_push(result, rightNode->value);
        rightNode = rightNode->next;
    }

    return result;
}

// 归并排序
List *merge_sort(List *list) {
    if (!list || list->count < 2) return list;

    ListNode *slow = list->first;
    ListNode *fast = list->first;

    // 找到中间节点
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // 分割成两个列表
    List *left = List_create();
    List *right = List_create();
    
    ListNode *node = list->first;
    int flag = 0;
    while (node) {
        if (node == slow || flag) {
            flag = 1;
            List_push(right, node->value);
            node = node->next;
        } else {
            List_push(left, node->value);
            node = node->next;
        }
    }

    // 递归排序
    left = merge_sort(left);
    right = merge_sort(right);

    // 合并两个有序列表
    List *sortedList = merge(left, right);

    List_clear_destroy(left);
    List_clear_destroy(right);

    return sortedList;
}


char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            printf("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    bubble_sort(words);
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    bubble_sort(words);
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    bubble_sort(words);
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = merge_sort(words);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    // List *res2 = merge_sort(res);
    // mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
    // List_destroy(res2);
    // List_destroy(res);

    // List_destroy(words);
    return NULL;
}


char *all_tests()
{
    test_bubble_sort();
    test_merge_sort();

    return NULL;
}

int main() {
    all_tests();
    return 0;
}


