#pragma once
#ifndef __GRAPH_REPRESENT_H
#define __GRAPH_REPRESENT_H
#ifdef __cplusplus
extern "C" {
#endif
	//邻接表中的链表节点
	struct vNode {
		int value;
		struct vNode* next;
	};

	//向邻接表中插入一个数据，并保证邻接表的有序性
	void insertIntoAdjVertics(struct vNode** adjVertics, int start, int end);

	void BFS(struct vNode** adj, int n, int s, int* parent, int* result);

	////打印邻接矩阵
	//void displayNeighborMatrix(int** neighborMatrix, int n);

	////打印邻接表
	//void displayAdjVertice(struct vNode** adjVertics, int n);



#ifdef __cplusplus
}
#endif
#endif