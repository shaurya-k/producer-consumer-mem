////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: prodcom.c
//
////////////////////////////////////////////////////////////////////////////////
#include "reader.h"
#include "queue.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>


int main( ) {

    // create 3 queues
    Queue *munch1_queue = CreateStringQueue(10);
    Queue *munch2_queue = CreateStringQueue(10);
    Queue *writer_queue = CreateStringQueue(10);

    // 4 threads
    pthread_t reader_id;
    pthread_t munch1_id;
    pthread_t munch2_id;
    pthread_t writer_id;

    // create threads
    if(pthread_create(&reader_id, NULL, reader, munch1_queue) != 0){
        fprintf(stderr, "reader: thread creation failed");
        return 2;
    }
    if(pthread_create(&munch1_id, NULL, munch1, combineQueues(munch1_queue, munch2_queue)) != 0){
        fprintf(stderr, "munch1: thread creation failed");
        return 2;
    }
    if(pthread_create(&munch2_id, NULL, munch2, combineQueues(munch2_queue, writer_queue)) != 0){
        fprintf(stderr, "munch2: thread creation failed");
        return 2;
    }
    if(pthread_create(&writer_id, NULL, writer, writer_queue) != 0){
        fprintf(stderr, "writer: thread creation failed");
        return 2;
        }

    // join threads and wait
    if(pthread_join(reader_id, (void **)NULL) != 0){
        fprintf(stderr, "reader: thread join failed");
        return  2;
    }
    if(pthread_join(munch1_id, (void **)NULL) != 0){
        fprintf(stderr, "munch1: thread join failed");
        return 2;
    }
    if(pthread_join(munch2_id, (void **)NULL) != 0){
        fprintf(stderr, "munch2: thread join failed");
        return 2;
    }

    if (pthread_join(writer_id, (void **) NULL) != 0){
        fprintf(stderr, "writer: thread join failed");
        return 2;
    }

    // print stats
    fprintf(stderr, "\nStats for queues:\nreader -> munch1\n");
    PrintQueueStats(munch1_queue);
    fprintf(stderr, "\nmunch1 -> munch2\n");
    PrintQueueStats(munch2_queue);
    fprintf(stderr, "\nmunch2 -> writer\n");
    PrintQueueStats(writer_queue);
    return 0;
}
