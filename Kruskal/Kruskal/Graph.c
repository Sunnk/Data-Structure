#include "Graph.h"


/*
	��ʼ��ͼG
*/
void AdjInitiate(AdjLGraph *G) {
	int i;

	G->numOfVerts = 0;
	G->numOfEdges = 0;

	for (i = 0; i < MaxVertices; i++) {
		G->a[i].source = i;
		G->a[i].adj = NULL;
	}

}


/*
	���붥��
*/
void InsertVertex(AdjLGraph *G, int i, Datatype vertex) {
	
	if (i >= 0 && i < MaxVertices) {
		G->a[i].data - vertex;
		G->numOfVerts++;
	}
	else
	{
		printf("����Խ�磡\n");
	}
}

/*
	�����
*/
Ret InsertEdge(AdjLGraph *G, int v1, int v2 ,int cost) {
	Edge *p;

	if (v1 < 0 || v1>G->numOfVerts || v2<0 || v2>G->numOfVerts) {
		printf("����v1��v2Խ�����\n");
		return RET_INVALID_ARGUMENT;
	}

	p = (Edge *)malloc(sizeof(Edge));

	p->dest = v2;
	p->cost = cost;
	p->next = G->a[v1].adj;
	G->a[v1].adj = p;
	G->numOfEdges++;

	return RET_OK;
}

/*
	ɾ����<v1,v2>
*/
Ret DeleteEdge(AdjLGraph *G, int v1, int v2) {
	Edge *curr, *pre;
	
	if (v1 < 0 || v1>G->numOfVerts || v2<0 || v2>G->numOfVerts) {
		printf("����v1��v2Խ�����\n");
		return RET_INVALID_ARGUMENT;
	}

	pre = NULL;
	curr = G->a[v1].adj;

	while (curr != NULL && curr->dest != v2) {
		pre = curr;
		curr = curr->next;
	}

	if (curr != NULL && curr->dest == v2 && pre == NULL) {
		G->a[v1].adj = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else if (curr != NULL && curr->dest == v2 && pre != NULL) {
		pre->next = curr->next;
		free(curr);
		G->numOfEdges--;
	}
	else{
		printf("��v1,v2������\n");
		return RET_INVALID_ARGUMENT;
	}

	return RET_OK;
	
}

int GetFirstVex(AdjLGraph G, int v) {
	Edge *p;

	if (v < 0 || v >= G.numOfEdges) {
		printf("����vԽ��\n");
		return -1;
	}

	p = G.a[v].adj;
	
	if (p != NULL){
		return p->dest;
	}
	else {
		return -1;
	}

}


int GetNextVex(AdjLGraph G, int v1, const int v2) {
	Edge *p;

	if (v1 < 0 || v1 > G.numOfVerts || v2<0 || v2 > G.numOfVerts) {
		printf("����v1��v2Խ�����\n");
		return -1;
	}

	p = G.a[v1].adj;

	while (p != NULL) {
		
		if (p->dest != v2) {
			p = p->next;
			continue;
		}
		else
			break;
	}
	p = p->next;
	if (p != NULL)
		return p->dest;
	else
		return -1;

}

void DestroyAdjLGraph(AdjLGraph *G) {
	int i;
	Edge *p, *q;

	for (i = 0; 1 < G->numOfVerts; i++) {
		p = G->a[i].adj;

		while (p != NULL) {
		
			q = p->next;
			free(p);
			p = q;
		}
	}
}