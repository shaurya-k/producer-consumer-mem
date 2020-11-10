////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: munch1.c
//
////////////////////////////////////////////////////////////////////////////////
#include "queue.h"
#include "stats.h"
#include <string.h>
#include <pthread.h>


// This function will scan the line and replace each space character 
//(not tabs or newlines) with an asterisk ("*") character. It will 
//then pass the line to thread Munch2 through another queue of character strings.
void *munch1(void *queues){
	char *compare = NULL;
	char *tempPtr = NULL;

    struct_args *queues_struct = (struct_args *) queues;
    Queue *queue_last = queues_struct->queue_last;
    Queue *queue_next = queues_struct->queue_next;
	
	// run the thread until we get the the termination key
	while(1){ // no busy waiting
	    compare = DequeueString(queue_last);

        if(compare == NULL) {
            break;
        }

		while (1){
			tempPtr = strchr(compare, ' ');
			// if ptr is NULL than there are no more spaces in string
			if(tempPtr == NULL){
				break;
			}else{
				*(tempPtr) = '*';
			}
		}
		// add the manipulated string onto next queue
		EnqueueString(queue_next, compare);
	}

	EnqueueString(queue_next, NULL);
	pthread_exit(NULL);
}
