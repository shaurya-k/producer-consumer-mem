////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: writer.c
//
////////////////////////////////////////////////////////////////////////////////
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

// write queue to output
void * writer(void *queue) {
    char *line = DequeueString(queue);

    long write_count = 0;
    while(line != NULL){
        printf("%s\n", line);
        free(line);
        line = DequeueString(queue);
        write_count++;
    }

    printf("\nNumber of strings processed: %ld\n", write_count);
    pthread_exit(0);
}
