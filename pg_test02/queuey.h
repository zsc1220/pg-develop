#pragma once
#ifndef _QUEUEY_H
#define _QUEUEY_H
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct {
		int size, eleNum;
		int* array;
		int front, tail; //front指向第一个元素，rear指向最后一个元素的下一个位置
	} Queue;


	//取出并移除第一个元素
	int poll(Queue* q); 

	//获取长度
	int len(Queue* q);

	//插入k，返回1表示插入成功
	int add(Queue* q, int k);

	//取出头部元素，不删除此元素，peek是“偷看”的意思
	int peek(Queue* q);

	//返回1表示为空，0表示不空
	int isEmpty(Queue* q);

	//创建大小为n的队列
	Queue* createQue(int n);


#ifdef __cplusplus
}
#endif
#endif