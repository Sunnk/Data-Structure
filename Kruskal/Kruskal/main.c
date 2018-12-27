#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)；

#include "stdio.h"
#include "Graph.h"
#include "Kruskal.h"

typedef struct {
	int row;
	int col;
	int cost;
}RowCol;


/*
	v---顶点数组
	n---顶点数目
	d---边
	e---边数目
*/
void CreateGraph(AdjLGraph *G, Datatype v[], int n, RowCol d[], int e) {
	int i, k;
	
	AdjInitiate(G);
	
	for (i = 0; i < n; i++) {
		InsertVertex(G,i,v[i]);
	}
	for (k = 0; k < e; k++)
		InsertEdge(G,d[k].row,d[k].col,d[k].cost);

}


int main()
{
	Datatype v[7] = {0,1,2,3,4,5,6};
	RowCol   d[20] ;
	AdjLGraph *G = (AdjLGraph *)malloc(sizeof(AdjLGraph));
	edge *e;
	edge *result;


	d[0].col = 0; d[0].row = 1; d[0].cost = 50;
	d[1].col = 0; d[1].row = 2; d[1].cost = 60;
	d[2].col = 1; d[2].row = 0; d[2].cost = 50;
	d[3].col = 1; d[3].row = 3; d[3].cost = 65;
	d[4].col = 1; d[4].row = 4; d[4].cost = 40;
	d[5].col = 2; d[5].row = 0; d[5].cost = 60;
	d[6].col = 2; d[6].row = 3; d[6].cost = 52;
	d[7].col = 2; d[7].row = 6; d[7].cost = 45;
	d[8].col = 3; d[8].row = 1; d[8].cost = 65;
	d[9].col = 3; d[9].row = 2; d[9].cost = 52;
	d[10].col = 3; d[10].row = 4; d[10].cost = 50;
	d[11].col = 3; d[11].row = 5; d[11].cost = 30;
	d[12].col = 3; d[12].row = 6; d[12].cost = 42;
	d[13].col = 4; d[13].row = 1; d[13].cost = 40;
	d[14].col = 4; d[14].row = 3; d[14].cost = 50;
	d[15].col = 4; d[15].row = 5; d[15].cost = 70;
	d[16].col = 5; d[16].row = 3; d[16].cost = 30;
	d[17].col = 5; d[17].row = 4; d[17].cost = 70;
	d[18].col = 6; d[18].row = 2; d[18].cost = 45;
	d[19].col = 6; d[19].row = 3; d[19].cost = 42;


	CreateGraph(G,v,7,d,20);
	//从邻接表中取出所有边并去掉重复
	e = VisitGraph(G);
	printf("从邻接表中取出的所有边\n");
	Printedge(e, 10);
	//冒泡排序所有的边
	GraphBubbleSort(e,10);
	printf("冒泡排序后的边\n");
	Printedge(e, 10);
	result = Kruskal(G,e);
	//经过克鲁斯卡尔算法留下的边
	printf("经过克鲁斯卡尔算法留下的边\n");
	Printedge(result, 6);
	system("pause");
	return 0;
}