#ifndef _PriorityQuery_H_
#define _PriorityQuery_H_

#include "def.h"
#include "minheap.h"

typedef struct {
	MinHeap *miniumheap;
}PriorityQuery;

PriorityQuery *CreatePriorityQuery(void);
Ret PriorityQueryEnqueue(PriorityQuery *priorityqueue, unsigned int *data, unsigned int weight);
Ret PriorityQueryDequeue(PriorityQuery *priorityqueue, unsigned int *data, unsigned int *weight);
void PriorityQueryDestroy(PriorityQuery *priorityqueue);



#endif
