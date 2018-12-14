#pragma once
#ifndef __GRAPH_REPRESENT_H
#define __GRAPH_REPRESENT_H
#ifdef __cplusplus
extern "C" {
#endif
	//�ڽӱ��е�����ڵ�
	struct vNode {
		int value;
		struct vNode* next;
	};

	//���ڽӱ��в���һ�����ݣ�����֤�ڽӱ��������
	void insertIntoAdjVertics(struct vNode** adjVertics, int start, int end);

	void BFS(struct vNode** adj, int n, int s, int* parent, int* result);

	////��ӡ�ڽӾ���
	//void displayNeighborMatrix(int** neighborMatrix, int n);

	////��ӡ�ڽӱ�
	//void displayAdjVertice(struct vNode** adjVertics, int n);



#ifdef __cplusplus
}
#endif
#endif