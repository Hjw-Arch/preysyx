#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"


typedef List Queue;
Queue* (*Queue_create)(void) = List_create;
void (*Queue_destroy)(Queue *list) = List_destroy;
void (*Queue_enqueue)(Queue *list, void *value) = List_push;
void *(*Queue_dequeue)(Queue *list) = List_shift;
void (*Queue_clear_destroy)(Queue *queue) = List_clear_destroy;



#endif