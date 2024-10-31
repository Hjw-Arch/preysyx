#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"


typedef List Queue;
Queue* (*Queue_create)(void) = List_create;
void (*Queue_destroy)(Queue *list) = List_destroy;
void (*Queue_send)(Queue *list, void *value) = List_push;
void *(*Queue_recv)(Queue *list) = List_shift;
void (*Queue_clear_destroy)(Queue *queue) = List_clear_destroy;

#define Queue_count(Q) List_count(Q)
#define Queue_peek(Q) List_first(Q)

#endif