#include<stdio.h>
#include<stdlib.h>
#include "queuey.h"

/*��c����ʵ�ֶ��л�������
add(), ���Ԫ�ص���β
peek(), ��ȡ�������Ƴ�ͷ
poll(), ��ȡ���Ƴ�����Ԫ��
create(n), ������СΪn�Ķ���
isempty(), �ж϶����ǲ��ǿ�
*/

//typedef struct {
//	int size, eleNum;
//	int* array;
//	int front, tail; //frontָ���һ��Ԫ�أ�rearָ�����һ��Ԫ�ص���һ��λ��
//} Queue;


//ȡ�����Ƴ���һ��Ԫ��
int poll(Queue* q) {
	int res = q->array[q->front];
	q->front = (++(q->front)) % q->size;
	q->eleNum--;
	return res;
}

//��ȡ����
int len(Queue* q) {
	return q->eleNum;
}

//����k������1��ʾ����ɹ�
int add(Queue* q, int k) {
	if (q->size == q->eleNum) {
		return 0;
	}
	q->eleNum++;
	q->array[q->tail] = k;
	q->tail = (q->tail + 1) % q->size;

	return 1;
}

//ȡ��ͷ��Ԫ�أ���ɾ����Ԫ�أ�peek�ǡ�͵��������˼
int peek(Queue* q) {
	return q->array[q->front];
}

//����1��ʾΪ�գ�0��ʾ����
int isEmpty(Queue* q) {
	if (q->eleNum == 0) {
		return 1;
	}
	return 0;
}

//������СΪn�Ķ���
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
