#pragma once
#ifndef _QUEUEY_H
#define _QUEUEY_H
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct {
		int size, eleNum;
		int* array;
		int front, tail; //frontָ���һ��Ԫ�أ�rearָ�����һ��Ԫ�ص���һ��λ��
	} Queue;


	//ȡ�����Ƴ���һ��Ԫ��
	int poll(Queue* q); 

	//��ȡ����
	int len(Queue* q);

	//����k������1��ʾ����ɹ�
	int add(Queue* q, int k);

	//ȡ��ͷ��Ԫ�أ���ɾ����Ԫ�أ�peek�ǡ�͵��������˼
	int peek(Queue* q);

	//����1��ʾΪ�գ�0��ʾ����
	int isEmpty(Queue* q);

	//������СΪn�Ķ���
	Queue* createQue(int n);


#ifdef __cplusplus
}
#endif
#endif