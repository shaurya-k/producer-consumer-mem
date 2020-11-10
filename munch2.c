////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: munch2.c
//
////////////////////////////////////////////////////////////////////////////////
#include "queue.h"
#include "stats.h"
#include <string.h>
#include <pthread.h>
#include <ctype.h>

//will scan the line and convert all lower case letters to upper case 
//(e.g., convert "a" to "A"). It will then pass the line to thread Writer though 
//yet another queue of character strings.
void *munch2(void *queues){
	char *tempPtr = NULL;
	int index = 0;

    struct_args *queues_struct = (struct_args *) queues;
    Queue *queue_last = queues_struct->queue_last;
    Queue *queue_next = queues_struct->queue_next;
	
	// run the thread until we get the the termination key
	while(1){ // no busy waiting
		tempPtr = DequeueString(queue_last);

		//check if the end of the queue
		if(tempPtr == NULL){
			break;
		}

		// loop through string and capitalize
        index = 0;
        while(tempPtr[index] != '\0'){
			if(islower(tempPtr[index])) {
				tempPtr[index] = (char) toupper(tempPtr[index]);
			}
			index++;
		}
		EnqueueString(queue_next, tempPtr);
	}
	//send to writer thread that munch2 is done with end char
	EnqueueString(queue_next, NULL);
	pthread_exit(NULL);
}
