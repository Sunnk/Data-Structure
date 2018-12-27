#include "Kruskal.h"



/*
	遍历图，将边加入edge，并去掉重复的边
*/
edge *VisitGraph(AdjLGraph *G) {
	
	edge *e = (edge *)malloc((G->numOfEdges/2)*sizeof(edge));
	int i,j;
	int num = 0;
	int LiveFlag = 1;
	//AdjHeight *FirstElem = NULL;
	Edge *operatorElem = NULL;

	for (i = 0; i < G->numOfVerts; i++) {

		operatorElem = G->a[i].adj;

		while (operatorElem != NULL) {
			//遍历列表，去掉重复的边
			for (j = 0; j < num ; j++) {
				if ((e[j].col == G->a[i].source && e[j].row == operatorElem->dest)
					|| (e[j].row == G->a[i].source && e[j].col == operatorElem->dest)) {
					LiveFlag = 0;
					break;
				}
				else
					LiveFlag = 1;
			}

			if (G->a[i].source > operatorElem->dest && LiveFlag)
			{
				e[num].col = operatorElem->dest;
				e[num].row = G->a[i].source;
				e[num].cost = operatorElem->cost;

				num++;
			}
			else if (LiveFlag) {
				e[num].col = G->a[i].source;
				e[num].row = operatorElem->dest;
				e[num].cost = operatorElem->cost;

				num++;
			}
			else
				;
			operatorElem = operatorElem->next;
		}

		
	}

	return e;
}

/*
	对edges排序，采用冒泡排序法
*/
void GraphBubbleSort(edge *e,int num) {
	int i = 0;
	int j = 0;
	int tempcol, temprow, tempcost;

	for (i = 0; i < num; i++) {
		for (j = 0; j < num - 1; j++) {
			if (e[j].cost > e[j + 1].cost) {
				tempcol = e[j].col;
				temprow = e[j].row;
				tempcost = e[j].cost;

				e[j].col = e[j + 1].col;
				e[j].row = e[j + 1].row;
				e[j].cost = e[j + 1].cost;

				e[j + 1].col = tempcol;
				e[j + 1].cost = tempcost;
				e[j + 1].row = temprow;
			}
		}
	}

}


edge *Kruskal(AdjLGraph *G,edge *e) {
	int num = G->numOfVerts;
	//Datatype *T = (Datatype *)malloc(num*sizeof(Datatype));  //顶点集合
	int *TLinkerFlag = (int *)malloc(num*sizeof(int));       //顶点连通区域集合
	edge *result = (edge *)malloc((G->numOfVerts - 1)*sizeof(edge)); //输出边集合
	int Flag = 1;
	int countflag = 0;
	int i = 0;
	int k = 0;
	int j = 1;
	int m = 0;
	int tempmin, tempmax;
	int tempflag;

	for (i = 0; i < num; i++) {
		TLinkerFlag[i] = 0;
	}

	for (i = 0; i < (G->numOfVerts - 1); i++) {
		result[i].col = 0;
		result[i].cost = 0;
		result[i].row = 0;
	}

	i = 0;

	while (Flag) {

		//判断两个顶点是否属于同一个连通分量
		if (TLinkerFlag[e[i].col] == TLinkerFlag[e[i].row] && TLinkerFlag[e[i].col] != 0) {

		}
		else {
			//加入边
			result[k].col = e[i].col;
			result[k].row = e[i].row;
			result[k].cost = e[i].cost;
			k++;
			//更改TLinkerFlag
			if (e[i].col > e[i].row) {
				tempmin = e[i].row;
				tempmax = e[i].col;
			}
			else {
				tempmin = e[i].col;
				tempmax = e[i].row;
			}
			
			if (TLinkerFlag[tempmin] != 0) {
				if (TLinkerFlag[tempmax] != 0) {
					tempflag = TLinkerFlag[tempmax];
					for (m = 0; m < num; m++) {
						if (TLinkerFlag[m] == tempflag) {
							TLinkerFlag[m] = TLinkerFlag[tempmin];
						}
					}

				}
				else {
					TLinkerFlag[tempmax] = TLinkerFlag[tempmin];
				}
			}
			else {
				if (TLinkerFlag[tempmax] != 0) {
					TLinkerFlag[tempmin] = TLinkerFlag[tempmax];
				}
				else {
					TLinkerFlag[tempmin] = j;
					TLinkerFlag[tempmax] = j;
					j++;
				}
			}
		}

		tempflag = TLinkerFlag[0];

		for (m = 0 , countflag = 0; m < num; m++) {
			if (TLinkerFlag[m] == tempflag)
				countflag++;
		}
		if (countflag == num)
			Flag = 0;


		i++;
	}

	return result;     
}


void Printedge(edge *e,int num) {
	int i = 0;
	for (i = 0; i < num; i++) {
		printf("(%d,%d,%d)\n",e[i].col,e[i].row,e[i].cost);
	}
}