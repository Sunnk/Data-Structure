#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include "Graph.h"
#include "stdio.h"

typedef struct edges edge;
struct edges {
	int col;
	int row;
	int cost;
};


edge *VisitGraph(AdjLGraph *G);
void GraphBubbleSort(edge *e, int num);
edge *Kruskal(AdjLGraph *G, edge *e);
void Printedge(edge *e, int num);
#endif