////////////////////////////////////////////////////////////////////////////////
// Main File: prodcom.c
// This File: stats.c
//
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "stats.h"

void printStats(Queue *q){
	fprintf(stderr, "enqueueCount = %d\n", q->enqueueCount);
	fprintf(stderr, "dequeueCount = %d\n", q->dequeueCount);
	fprintf(stderr, "enqueueTime = %f\n", q->enqueueTime);
	fprintf(stderr, "dequeueTime = %f\n", q->dequeueTime);
}
