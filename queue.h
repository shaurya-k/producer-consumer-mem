////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: queue.h
//
////////////////////////////////////////////////////////////////////////////////
#ifndef QUEUE
#define QUEUE
#include <pthread.h>
#include "stats.h"

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char * DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

typedef struct struct_args{
    Queue *queue_last;
    Queue *queue_next;
}struct_args;

struct_args* combineQueues(Queue *queue_last, Queue *queue_next);

#endif
