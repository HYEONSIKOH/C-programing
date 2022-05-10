/*
ť Ȱ���ϱ�

������ �˰����� ���� �߰� ���α׷��� �ۼ��Ѵ�.
2���� ����ť�� ����ϸ�, ���� ���л��� ���л��� ��� ť�̴�.
���ο� ��(��)�л��� ����� �ϸ� ��(��)�л� ť���� �����Ͽ� ������ ����ȴ�. 
���� ��(��)�л� ť�� �̹� ����ϰ� �ִ� �л��� ������ ��(��)�л��� ť�� ���� ��ٸ���� �Ѵ�.

�������� �߻��Ǵ� Ȧ���� ¦���� ���� �л��� �����ϱ�� �Ѵ�
ť���� �л��� �̸��� �Էµȴ�.
��ü 100���� �л�(���� ����)�� ���ؼ� ������ �߰��ϸ�,
������ ����� ������, ȭ�鿡 ������ ����Ѵ�.


(��)
��1 ���� - ���
��2 ���� - ���
��3 ���� - ���
��1 ���� - ��1/��1 ��Ī
��2 ���� - ��2/��2 ��Ī
��4 ���� - ���
��5 ���� - ���
��3 ���� - ��3/��3 ��Ī
��4 ���� - ��4/��4  ��Ī
��5 ���� - ��5/��5 ��Ī
��6 ���� - ���
��7 ���� - ���
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_QUEUE_SIZE  20

typedef struct {
	char name[10];
}element;

typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q){
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q){
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q){
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� ��
void queue_print(QueueType* q){
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;

		} while (i != q->front);
	}
	printf("\n");
}

// ���� �Լ�
void enqueue(QueueType* q, element item){
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q){
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q){
	if (is_empty(q))
		error("ť�� ��������Դϴ�");

	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	QueueType man;
	QueueType woman;
	init_queue(&man);
	init_queue(&woman);
	int w = 0, m = 0;

	for (int i = 0; i < 100; i++) {
		element n;
		int random = rand() % 2;

		if (random == 1) { // ����
			sprintf(n.name, "��%d", ++m);
			enqueue(&man, n);
			if (!is_empty(&man) && !is_empty(&woman))
				printf("��%d ���� - %s / %s ��Ī\n", m, dequeue(&woman).name, dequeue(&man).name);
			
			else
				printf("��%d ���� - ���\n",m);
		}

		else if (random == 0) { // ����
			sprintf(n.name, "��%d", ++w);
			enqueue(&woman, n);
			if (!is_empty(&man) && !is_empty(&woman)) {
				printf("��%d ���� - %s / %s ��Ī\n", w, dequeue(&woman).name, dequeue(&man).name);
			}
			else
				printf("��%d ���� - ���\n", w);
		}

	}
	return 0;
}