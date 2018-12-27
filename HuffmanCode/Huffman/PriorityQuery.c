#include "PriorityQuery.h"

PriorityQuery *CreatePriorityQuery(void) {
	PriorityQuery *tempPriorityQuery = NULL;

	tempPriorityQuery =(PriorityQuery *) malloc(sizeof(PriorityQuery));
	return_val_if_fail(tempPriorityQuery != NULL, NULL);

	tempPriorityQuery->miniumheap = CreateMinHeap();

	return tempPriorityQuery;
}

Ret PriorityQueryEnqueue(PriorityQuery *priorityqueue, unsigned int *data, unsigned int weight) {

	return MinHeapInsert(priorityqueue->miniumheap,data,weight);
}

Ret PriorityQueryDequeue(PriorityQuery *priorityqueue, unsigned int *data, unsigned int *weight) {

	return MinHeapExtract(priorityqueue->miniumheap,data,weight);
}

void PriorityQueryDestroy(PriorityQuery *priorityqueue) {
	return_val_if_fail(priorityqueue != NULL, NULL);

	MinHeapDestroy(priorityqueue->miniumheap);
	free(priorityqueue);


}