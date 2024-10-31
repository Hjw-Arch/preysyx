#ifndef STACK_H
#define STACK_H

#include "list.h"


typedef List Stack;


Stack* (*Stack_create)(void) = List_create;
void (*Stack_destroy)(Stack *list) = List_destroy;
void (*Stack_push)(Stack *list, void *value) = List_push;
void *(*Stack_pop)(Stack *list) = List_pop;
void (*Stack_clear_destroy)(Stack *stack) = List_clear_destroy;

#define Stack_peek(S)    ((S)->last ? (S)->last->value : NULL)
#define Stack_count(S)   ((S)->count)

#define STACK_FOREACH(S, M, V) LIST_FOREACH(S, last, prev, V)

#endif