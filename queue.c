////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: queue.c
//
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "queue.h"
#include "stats.h"

// initialize queue params to empty, take the size
Queue *CreateStringQueue(int size){
  Queue *newQueue = (Queue *) malloc(sizeof(Queue)); //create object

	if(newQueue == NULL){ //null check
		printf("ERROR: couldn't malloc newQueue\n");
		return NULL;
	}
   	//create enough space to store strings
	newQueue->strings = (char**) malloc(sizeof(char*) * size);
	if(newQueue->strings == NULL){
		printf("ERROR: couldn't malloc strings in newQueue\n");
		//free(newQueue); //free before return
		return NULL;
	}

  	//assign the variables before return newQueue
    if( pthread_cond_init(&newQueue->enqueue, NULL) != 0) {
        printf("ERROR: couldn't init condition\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_cond_init(&newQueue->dequeue, NULL) != 0) {
        printf("ERROR: couldn't init condition\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_mutex_init(&newQueue->mutex, NULL) != 0) {
        printf("ERROR: couldn't init condition\n");
        exit(EXIT_FAILURE);
    }
  	newQueue->beginning = 0;
	newQueue->end = size - 1;
	newQueue->capacity = size;
	newQueue->numOfElements = 0;
	newQueue->enqueueCount = 0;
	newQueue->dequeueCount = 0;
	newQueue->enqueueTime = 0;
	newQueue->dequeueTime = 0;

	return newQueue;
}

//This function places the pointer to the string at the 
//end of queue q. If the queue is full, then this function
//blocks until there is space available.
void EnqueueString(Queue *q, char *string){
    // lock thread and check capacity
    clock_t t;
    t = clock();
    if(pthread_mutex_lock(&q->mutex) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    if(q->numOfElements == q->capacity){
        if (string != NULL) {
            // wait for dequeue
            if(pthread_cond_wait(&q->dequeue, &q->mutex) != 0) {
                printf("Pthread Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // add string
    q->end = (q->end+1) % q->capacity;
    q->strings[q->end] = string;
    q->numOfElements++;

 	// if not last string
    if (string != NULL) {
        q->enqueueCount++;
    }

	//unlock blocked dequeue
    if(pthread_cond_signal(&q->enqueue) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_unlock(&q->mutex) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    q->enqueueTime += time_taken;
	
}

//This function removes a pointer to a string from the beginning of 
//queue q. If the queue is empty, then this function blocks until 
//there is a string placed into the queue. This function returns 
//the pointer that was removed from the queue.
char * DequeueString(Queue *q){
    // lock thread and check capacity
    clock_t t;
    t = clock();
    if(pthread_mutex_lock(&q->mutex) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    if(q->numOfElements == 0){
		// wait for enqueue
        if(pthread_cond_wait(&q->enqueue, &q->mutex) != 0){
            printf("Pthread Error\n");
            exit(EXIT_FAILURE);
        }
    }
    // get string
    char *string = q->strings[q->beginning];

    // wrap the head around
    q->beginning = (q->beginning + 1) % q->capacity;
    q->numOfElements--;

    if (string != NULL) {
        q->dequeueCount++;
    }

	//unlock blocked enqueue
    if(pthread_cond_signal(&q->dequeue) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_unlock(&q->mutex) != 0) {
        printf("Pthread Error\n");
        exit(EXIT_FAILURE);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    q->dequeueTime += time_taken;
    return string;
}

//prints the queue stats as required
void PrintQueueStats(Queue *q){
	printStats(q);
}

// for passing multiple queues into threads
struct_args* combineQueues(Queue *queue_last, Queue *queue_next){
    struct_args *queues = (struct_args*) malloc(sizeof(struct_args));
    if( queues == NULL)
    {
        fprintf(stderr, "Allocating memory failed for combining queues.");
        exit(EXIT_FAILURE);
    }
    queues->queue_last = queue_last;
    queues->queue_next = queue_next;
    return queues;
}
