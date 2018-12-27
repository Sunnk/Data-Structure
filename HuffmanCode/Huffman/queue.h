#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "slist.h"

typedef struct{
    SList *slist;
}Queue;

Queue *queue_create(void);
Ret queue_enqueue(Queue *queue, void *data);
Ret queue_dequeue(Queue *queue, void **data);
void queue_destroy(Queue *queue);

#endif // _QUEUE_H_

