#ifndef _minheap_H_
#define _minheap_H_

#include "def.h"
#include "stdio.h"

typedef struct {
	unsigned int symbolnum;   //����Ԫ�ظ���
	unsigned int *data;               //���н������
	unsigned int *weight;             //���н��Ȩֵ
}MinHeap;


MinHeap *CreateMinHeap(void);
void AdjustHeap(MinHeap *heap, unsigned int parent_index);
Ret MinHeapInsert(MinHeap *heap, unsigned int *data, unsigned int weight);
Ret MinHeapExtract(MinHeap *heap, unsigned int *data, unsigned int *weight);
void MinHeapDestroy(MinHeap *heap);


#endif // _minheap_H_
