////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: reader.c
//
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"


void * reader(void *queue) {
    // Max buffer size
    int MAX_BUFFER = 4096;

    // make buffer
    char *buffer = (char *)malloc(MAX_BUFFER * sizeof(char));
    if( buffer == NULL)
    {
        fprintf(stderr, "Allocating memory failed for reader.");
        exit(EXIT_FAILURE);
    }

    int current_char;
    int index = 0;
    do {
        // read the line
        current_char = getchar();

        // if not over the max buffer
        if (index >= MAX_BUFFER) {
            fprintf(stderr, "Input too long, and has not been added\n");

            // flush input stream
            buffer[index-1] = '\0';
            while ((current_char = getchar()) != '\n' && current_char != EOF);

            // reset buffer
            index = 0;
            free(buffer);
            buffer = (char *)malloc(MAX_BUFFER * sizeof(char));
            if( buffer == NULL)
            {
                fprintf(stderr, "Allocating memory failed for reader.");
                exit(EXIT_FAILURE);
            }
            continue;
        }

        // if not end of line
        if (current_char != '\n' && current_char != EOF) {
            buffer[index++] = (char) current_char;
        }

        // reach the end of line
        if (current_char == '\n' || current_char == EOF) {
            // if we typed ctrl-d
            if (index == 0 && current_char == EOF) {
                continue;
            }

            // when reached end of line, add EOF char to string doesnt reach out of bounds
            if (current_char == '\n') {
                buffer[index] = '\0';
            }

            // pass to munch1
            EnqueueString(queue, buffer);

            // reset buffer
            index = 0;
            buffer = (char *)malloc(MAX_BUFFER * sizeof(char));
            if( buffer == NULL)
            {
                fprintf(stderr, "Allocating memory failed for reader.");
                exit(EXIT_FAILURE);
            }
        }
    }
    while(current_char != EOF);

    EnqueueString(queue, NULL);
    pthread_exit(0);
}
