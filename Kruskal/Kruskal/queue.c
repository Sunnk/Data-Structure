#include "queue.h"

//��������
Queue *queue_create(void)
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	return_val_if_fail(queue != NULL, NULL);

	queue->slist = slist_create();

	if (queue->slist == NULL) {
		free(queue);
		return_val_if_fail(queue->slist != NULL, NULL);
	}

	return queue;

}

//����Ԫ�����
Ret queue_enqueue(Queue *queue, void *data)
{

	return slist_append(queue->slist, data);
}

//����Ԫ�س���
Ret queue_dequeue(Queue *queue, void **data)
{
	return_val_if_fail(queue != NULL, RET_INVALID_ARGUMENT);

	return slist_delete(queue->slist, 0, data);
}

//���ٶ���
void queue_destroy(Queue *queue)
{
	return_val_if_fail(queue != NULL, RET_INVALID_ARGUMENT);

	slist_destroy(queue->slist);

	free(queue);
}
