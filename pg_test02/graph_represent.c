#include <stdio.h>
#include <stdlib.h>
#include "graph_represent.h"
#include "queuey.h"

//图的表示，输入节点个数和边，构造图的邻接矩阵和邻接表

////邻接表中的链表节点
//struct vNode {
//	int value;
//	struct vNode* next;
//};

//向邻接表中插入一个数据，并保证邻接表的有序性
void insertIntoAdjVertics(struct vNode** adjVertics, int start, int end) {

	struct vNode* node = (struct vNode*)malloc(sizeof(struct vNode));
	struct vNode* head = adjVertics[start];

	node->value = end;
	node->next = NULL;

	if (head == NULL) {
		adjVertics[start] = node;
		return;
	}

	if (head->next == NULL && head->value>end) {
		node->next = head;
		adjVertics[start] = node;
		return;
	}

	while (head->next != NULL && head->next->value<end) {
		head = head->next;
	}

	if (head->next == NULL) {
		head->next = node;
		return;
	}

	node->next = head->next;
	head->next = node;
}

void BFS(struct vNode** adj, int n, int s, int* parent,int* result) {
	int* color = (int*)malloc(sizeof(int)*(n)); //-1:未发现，0:已发现，未处理, 1:已经处理
	int i;
	Queue* pending = createQue(n);  //创建队列

	for (i = 0; i<n; i++) {
		color[i] = -1;  //所有节点处于“未发现”状态
	}

	parent[s] = -1;
	color[s] = 0;
	add(pending, s);     //入队操作


	int j = 0;

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
		//printf("%d ", v);/**在这里处理节点**/
		result[j] = v;
		j++;
		color[v] = 1;
	}
	//printf("\n");
}

////打印邻接矩阵
//void displayNeighborMatrix(int** neighborMatrix, int n) {
//	int i, j;
//
//	printf("\n");
//	for (i = 0; i<n; i++) {
//		for (j = 0; j<n; j++) {
//			printf("%d ", neighborMatrix[i][j]);
//		}
//		printf("\n");
//	}
//}
//
////打印邻接表
//void displayAdjVertice(struct vNode** adjVertics, int n) {
//	int i;
//	for (i = 0; i<n; i++) {
//		struct vNode* head = adjVertics[i];
//		printf("%d: ", i);
//		while (head != NULL) {
//			printf("->%d ", head->value);
//			head = head->next;
//		}
//
//		printf("\n");
//	}
//}
//
//
//int default_wraper(struct vNode*** adjVertics) {
//	int n, i, j;
//	int** neighborMatrix;
//	//struct vNode** adjVertics;
//	int start[9] = { 0,0,1,1,2,2,3,4,5 };
//	int end[9] = { 1,2,2,3,3,5,5,5,6 };
//	n = 7;
//	/*printf("input vertex number: ");
//	scanf_s("%d", &n);*/
//
//	//初始化邻接矩阵
//	neighborMatrix = (int**)malloc(sizeof(int*)*n);
//	for (i = 0; i<n; i++) {
//		neighborMatrix[i] = (int*)malloc(sizeof(int)*n);
//		for (j = 0; j<n; j++) {
//			neighborMatrix[i][j] = 0;
//		}
//	}
//
//	//adjVertics = (struct vNode**)malloc(sizeof(struct vNode*)*n);
//	for (i = 0; i<n; i++) {
//		adjVertics[i] = NULL;
//	}
//
//	//输入定点，格式为 1 2
//	printf("input start and end vertex, format 1 2, stop by -1. \n");
//
//	for (int i = 0; i < 9; ++i)
//	{
//		neighborMatrix[start[i]][end[i]] = 1;		//对称矩阵
//		neighborMatrix[end[i]][start[i]] = 1;
//		insertIntoAdjVertics(adjVertics, start[i], end[i]);
//		insertIntoAdjVertics(adjVertics, end[i], start[i]);
//	}
//
//	//while (1) {
//	//	scanf_s("%d", &start);
//	//	if (start == -1) {
//	//		break;
//	//	}
//	//	scanf_s("%d", &end);
//
//	//	neighborMatrix[start][end] = 1;		//对称矩阵
//	//	neighborMatrix[end][start] = 1;
//	//	insertIntoAdjVertics(adjVertics, start, end);
//	//	insertIntoAdjVertics(adjVertics, end, start);
//	//}
//
//	//displayNeighborMatrix(neighborMatrix, n);
//	//printf("-------------\n");
//	//displayAdjVertice(adjVertics, n);
//	//system("pause");
//	return EXIT_SUCCESS;
//}

