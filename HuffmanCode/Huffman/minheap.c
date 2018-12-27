#include "minheap.h"


/*
	创建一个最小堆
*/
MinHeap *CreateMinHeap(void) {

	MinHeap *minheap = NULL;

	minheap = (MinHeap *)malloc(sizeof(MinHeap));

	minheap->symbolnum = 0;
	minheap->data = NULL;
	minheap->weight = NULL;

	if (minheap == NULL) {
		free(minheap);
		return NULL;
	}

	return minheap;
}


/*
	调整堆,成为最小堆
*/
void AdjustHeap(MinHeap *heap,unsigned int parent_index) {

	unsigned int leftchild = parent_index * 2 + 1;
	unsigned int rightchild = parent_index * 2 + 2;
	unsigned int smallest_index = parent_index;
	unsigned int temp = 0;


	if (leftchild < heap->symbolnum)
		if (heap->weight[leftchild] < heap->weight[parent_index])
			smallest_index = leftchild;

	if (rightchild < heap->symbolnum)
		if (heap->weight[rightchild] < heap->weight[smallest_index])
			smallest_index = rightchild;
	
	if (smallest_index != parent_index) {
		
		temp = heap->weight[smallest_index];
		heap->weight[smallest_index] = heap->weight[parent_index];
		heap->weight[parent_index]   = temp;

		temp = heap->data[smallest_index];
		heap->data[smallest_index] = heap->data[parent_index];
		heap->data[parent_index]   = temp;

		AdjustHeap(heap , smallest_index);
	}
}

Ret MinHeapInsert(MinHeap *heap,unsigned int *data,unsigned int weight) {
	int index = 0;
	int parent_index = 0;
	unsigned int temp = 0;


	if (heap->symbolnum == 0) {
		heap->data = (unsigned int *)malloc(sizeof(unsigned int));
		heap->weight = (unsigned int *)malloc(sizeof(unsigned int));

		heap->data[heap->symbolnum] = data;
		heap->weight[heap->symbolnum] = weight;

		heap->symbolnum++;
	}
	else {
		heap->data = (unsigned int *)realloc(heap->data,(heap->symbolnum + 1) * sizeof(unsigned int));
		heap->weight = (unsigned int *)realloc(heap->weight, (heap->symbolnum + 1) * sizeof(unsigned int));

		heap->data[heap->symbolnum] = data;
		heap->weight[heap->symbolnum] = weight;

		index = heap->symbolnum;

		while (index) {
			parent_index = (index - 1) / 2;

			if (heap->weight[parent_index] > heap->weight[index]) {
				temp = heap->weight[parent_index];
				heap->weight[parent_index] = heap->weight[heap->symbolnum];
				heap->weight[heap->symbolnum] = temp;

				temp = heap->data[parent_index];
				heap->data[parent_index] = heap->data[heap->symbolnum];
				heap->data[heap->symbolnum] = temp;
			}

			index = parent_index;
		}



		//heap->data[heap->symbolnum] = heap->data[0];
		//heap->weight[heap->symbolnum] = heap->weight[0];

		//heap->data[0] = data;
		//heap->weight[0] = weight;


		heap->symbolnum++;
	}

	AdjustHeap(heap, 0);

#if 0

	printf("-----------------------------\n经过堆调整后为：\n");

	unsigned int i = 0;

	for (i = 0; i < heap->symbolnum; i++) {
		printf("heap[%d] = %d\n",i,heap->weight[i]);
	}

	printf("------------------------------");

#endif // USING_DEBUG


	return RET_OK;

}

Ret MinHeapExtract(MinHeap *heap, unsigned int *data, unsigned int *weight) {

	*data = heap->data[0];
	*weight = heap->weight[0];

	heap->data[0] = heap->data[heap->symbolnum - 1];
	//free(&heap->data[heap->symbolnum - 1]);

	heap->weight[0] = heap->weight[heap->symbolnum - 1];
	//free(&heap->weight[heap->symbolnum-1]);

	heap->symbolnum--;

	AdjustHeap(heap,0);

	return RET_OK;
}


void MinHeapDestroy(MinHeap *heap) {
	//unsigned int i = 0;

	//for (i = 0; i < heap->symbolnum; i++) {
	//	free(&heap->data[i]);
	//	free(&heap->weight[i]);
	//}
	free(heap->data);
	free(heap->weight);

	free(heap);

}

