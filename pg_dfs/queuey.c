#include<stdio.h>
#include<stdlib.h>
#include "queuey.h"

/*用c语音实现队列基本操作
add(), 添加元素到队尾
peek(), 获取但并不移出头
poll(), 获取并移出队首元素
create(n), 创建大小为n的队列
isempty(), 判断队列是不是空
*/

//typedef struct {
//	int size, eleNum;
//	int* array;
//	int front, tail; //front指向第一个元素，rear指向最后一个元素的下一个位置
//} Queue;


//取出并移除第一个元素
int poll(Queue* q) {
	int res = q->array[q->front];
	q->front = (++(q->front)) % q->size;
	q->eleNum--;
	return res;
}

//获取长度
int len(Queue* q) {
	return q->eleNum;
}

//插入k，返回1表示插入成功
int add(Queue* q, int k) {
	if (q->size == q->eleNum) {
		return 0;
	}
	q->eleNum++;
	q->array[q->tail] = k;
	q->tail = (q->tail + 1) % q->size;

	return 1;
}

//取出头部元素，不删除此元素，peek是“偷看”的意思
int peek(Queue* q) {
	return q->array[q->front];
}

//返回1表示为空，0表示不空
int isEmpty(Queue* q) {
	if (q->eleNum == 0) {
		return 1;
	}
	return 0;
}

//创建大小为n的队列
Queue* createQue(int n) {

	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->size = n;
	que->eleNum = 0;
	que->array = (int*)malloc(sizeof(int)*n);
	que->front = 0;
	que->tail = 0;

	return que;
}

void display(Queue* q) {
	int i = q->front;
	printf("elements: ");
	while (i != q->tail) {
		printf("%d ", q->array[i]);
		i = (i + 1) % q->size;
	}
	printf("\n");
	printf("size: %d,elements num: %d\n", q->size, q->eleNum);
	printf("front: %d, tail:%d \n", q->front, q->tail);
}

int main02() {

	Queue* q = createQue(10);

	add(q, 10); add(q, 11); add(q, 12);
	poll(q); poll(q);
	display(q);

	system("pause");
	return EXIT_SUCCESS;
}
