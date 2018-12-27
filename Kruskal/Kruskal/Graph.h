#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "stdio.h"
#include "def.h"

typedef int Datatype;

#define MaxVertices 100

typedef struct Node {
	int dest;                      //邻接边的弧头顶点序号
	int cost;					   //邻接边权值
	struct Node *next;             //邻接边单链表的结点结构体
}Edge;

typedef struct {
	Datatype data;                 //顶点数据元素
	int source;                    //邻接边的弧尾顶点序号
	Edge *adj;                     //邻接边的头指针
}AdjHeight;                        //数组的数据元素类型结构体

typedef struct {
	AdjHeight a[MaxVertices];       //邻接表数组
	int numOfVerts;                 //顶点个数
	int numOfEdges;                 //边个数
}AdjLGraph;                          //邻接表结构体


void AdjInitiate(AdjLGraph *G);
void InsertVertex(AdjLGraph *G, int i, Datatype vertex);
Ret InsertEdge(AdjLGraph *G, int v1, int v2, int cost);
Ret DeleteEdge(AdjLGraph *G, int v1, int v2);
int GetFirstVex(AdjLGraph G, int v);
int GetNextVex(AdjLGraph G, int v1, const int v2);
void DestroyAdjLGraph(AdjLGraph *G);

#endif