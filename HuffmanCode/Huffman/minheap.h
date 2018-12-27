#ifndef _minheap_H_
#define _minheap_H_

#include "def.h"
#include "stdio.h"

typedef struct {
	unsigned int symbolnum;   //堆中元素个数
	unsigned int *data;               //堆中结点数据
	unsigned int *weight;             //堆中结点权值
}MinHeap;


MinHeap *CreateMinHeap(void);
void AdjustHeap(MinHeap *heap, unsigned int parent_index);
Ret MinHeapInsert(MinHeap *heap, unsigned int *data, unsigned int weight);
Ret MinHeapExtract(MinHeap *heap, unsigned int *data, unsigned int *weight);
void MinHeapDestroy(MinHeap *heap);


#endif // _minheap_H_
