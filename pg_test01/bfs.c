#include <stdio.h>
#include <stdlib.h>
#include "queuey.h"
#include "graph_represent.h"

void BFS(struct vNode** adj, int n, int s, int* parent) {
	int* color = (int*)malloc(sizeof(int)*(n)); //-1:未发现，0:已发现，未处理, 1:已经处理
	int i;
	Queue* pending = createQue(n);  //创建队列

	for (i = 0; i<n; i++) {
		color[i] = -1;  //所有节点处于“未发现”状态
	}

	parent[s] = -1;
	color[s] = 0;
	add(pending, s);     //入队操作

	while (!isEmpty(pending)) {
		int v = poll(pending);

		struct vNode* w = adj[v];
		while (w != NULL) {
			if (color[w->value] == -1) {
				color[w->value] = 0;
				add(pending, w->value);
				parent[w->value] = v;/**在这里处理树边**/
			}
			w = w->next;
		}
		printf("%d ", v);/**在这里处理节点**/
		color[v] = 1;
	}
	printf("\n");
}


void main03() {

	//获得默认图,一共有7个节
	int n=7, i, j;
	int** neighborMatrix;
	int start[9] = { 0,0,1,1,2,2,3,4,5 };
	int end[9] = { 1,2,2,3,3,5,5,5,6 };

	//初始化邻接矩阵
	neighborMatrix = (int**)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++) {
		neighborMatrix[i] = (int*)malloc(sizeof(int)*n);
		for (j = 0; j<n; j++) {
			neighborMatrix[i][j] = 0;
		}
	}
	struct vNode** adjVertics = (struct vNode**)malloc(sizeof(struct vNode*)*n);
	for (i = 0; i<n; i++) {
		adjVertics[i] = NULL;
	}

	for (int i = 0; i < 9; ++i)
	{
		neighborMatrix[start[i]][end[i]] = 1;		//对称矩阵
		neighborMatrix[end[i]][start[i]] = 1;
		insertIntoAdjVertics(adjVertics, start[i], end[i]);
		insertIntoAdjVertics(adjVertics, end[i], start[i]);
	}

	int* parent = (int*)malloc(sizeof(int)*n);

	printf("\nbreadth first search:\n");
	BFS(adjVertics, n, 2, parent);//从第二个节点开始遍历
	system("pause");
}
