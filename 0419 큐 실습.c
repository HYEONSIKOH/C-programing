/*
큐 활용하기

간단한 알고리즘의 미팅 중개 프로그램을 작성한다.
2개의 원형큐를 사용하며, 각각 남학생과 여학생의 대기 큐이다.
새로운 남(여)학생이 등록을 하면 여(남)학생 큐에서 삭제하여 미팅이 성사된다. 
만약 여(남)학생 큐에 이미 대기하고 있는 학생이 없으면 남(여)학생은 큐에 들어가서 기다리기로 한다.

랜덤으로 발생되는 홀수와 짝수로 남녀 학생을 구분하기로 한다
큐에는 학생의 이름이 입력된다.
전체 100명의 학생(남녀 랜덤)에 대해서 미팅을 중개하며,
미팅이 성사될 때마다, 화면에 내용을 출력한다.


(예)
남1 입장 - 대기
남2 입장 - 대기
남3 입장 - 대기
여1 입장 - 여1/남1 매칭
여2 입장 - 여2/남2 매칭
남4 입장 - 대기
남5 입장 - 대기
여3 입장 - 여3/남3 매칭
여4 입장 - 여4/남4  매칭
여5 입장 - 여5/남5 매칭
여6 입장 - 대기
여7 입장 - 대기
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_QUEUE_SIZE  20

typedef struct {
	char name[10];
}element;

typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q){
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q){
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q){
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함
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

// 삽입 함수
void enqueue(QueueType* q, element item){
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q){
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 참조 함수
element peek(QueueType* q){
	if (is_empty(q))
		error("큐가 공백상태입니다");

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

		if (random == 1) { // 남자
			sprintf(n.name, "남%d", ++m);
			enqueue(&man, n);
			if (!is_empty(&man) && !is_empty(&woman))
				printf("남%d 입장 - %s / %s 매칭\n", m, dequeue(&woman).name, dequeue(&man).name);
			
			else
				printf("남%d 입장 - 대기\n",m);
		}

		else if (random == 0) { // 여자
			sprintf(n.name, "여%d", ++w);
			enqueue(&woman, n);
			if (!is_empty(&man) && !is_empty(&woman)) {
				printf("여%d 입장 - %s / %s 매칭\n", w, dequeue(&woman).name, dequeue(&man).name);
			}
			else
				printf("여%d 입장 - 대기\n", w);
		}

	}
	return 0;
}