#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "stdio.h"
#include "def.h"

typedef int Datatype;

#define MaxVertices 100

typedef struct Node {
	int dest;                      //�ڽӱߵĻ�ͷ�������
	int cost;					   //�ڽӱ�Ȩֵ
	struct Node *next;             //�ڽӱߵ�����Ľ��ṹ��
}Edge;

typedef struct {
	Datatype data;                 //��������Ԫ��
	int source;                    //�ڽӱߵĻ�β�������
	Edge *adj;                     //�ڽӱߵ�ͷָ��
}AdjHeight;                        //���������Ԫ�����ͽṹ��

typedef struct {
	AdjHeight a[MaxVertices];       //�ڽӱ�����
	int numOfVerts;                 //�������
	int numOfEdges;                 //�߸���
}AdjLGraph;                          //�ڽӱ�ṹ��


void AdjInitiate(AdjLGraph *G);
void InsertVertex(AdjLGraph *G, int i, Datatype vertex);
Ret InsertEdge(AdjLGraph *G, int v1, int v2, int cost);
Ret DeleteEdge(AdjLGraph *G, int v1, int v2);
int GetFirstVex(AdjLGraph G, int v);
int GetNextVex(AdjLGraph G, int v1, const int v2);
void DestroyAdjLGraph(AdjLGraph *G);

#endif