////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: stats.h
//
////////////////////////////////////////////////////////////////////////////////
#ifndef STATS
#define STATS
#include <pthread.h>

typedef struct{
    pthread_cond_t enqueue;
    pthread_cond_t dequeue;
    pthread_mutex_t mutex;
        char **strings;
        int beginning;
        int end;
        int capacity;
        int numOfElements;
        int enqueueCount;
        int dequeueCount;
        double enqueueTime;
        double dequeueTime;
}Queue;

void printStats(Queue *q);

#endif
