#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAZE_SIZE 10
#define MAX 100

typedef struct {
	short r;
	short c;
}element;

element here = { 1,0 }; // �� ��ġ

char maze[MAZE_SIZE][MAZE_SIZE] = { // �̷� e�� ���� ��ġ, 0�� ���, 1�� ��, x�� �ⱸ
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{ 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{ '0', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
{ '1', '1', '0', '0', '0', '0', '1', '1', '1', '0'},
{ '1', '1', '1', '1', '1', '0', '1', '1', '1', '0'},
{ '1', '1', '1', '1', '1', '0', '1', '1', '1', '0'},
{ '1', '1', '0', '0', '0', '0', '1', '1', '1', '0'},
{ '1', '1', '1', '1', '1', '0', '0', '0', '0', 'x'},
{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

typedef struct {
	element data[MAX];
	int top;
}stacktype;

int is_full(stacktype* s) { // �� á����
	return (s->top == 99);
}

int is_empty(stacktype* s) { // ���� �������
	return (s->top == -1);
}

void init_stack(stacktype* s) { // ���� �ʱ�ȭ
	s->top = -1;
}

void push(stacktype* s, element c) { // �Է��Լ�
	if (is_full(s)) {
		printf("FULL");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

element pop(stacktype* s) { // ���� �Լ�
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peak(stacktype* s) { // ���� �Լ�
	if (is_empty(s)) {
		printf("3�����Դϴ�.");
		exit(1);
	}
	else
		return s->data[s->top];
}

void peak_print(stacktype* s) { // ���� �Լ�
	if (is_empty(s)) {
		printf("3�����Դϴ�.");
		exit(1);
	}
	else
		printf("[%d , %d]\n", s->data[s->top].r, s->data[s->top].c);
}

void push_loc(stacktype* s, int r, int c) { // �� ��ġ�� ȭ�鿡 ����Ѵ�.
	if (r < 0 || c < 0) return;
	else if (r > 9 || c > 9) return;
	else if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
	else
		return;
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) { // �̷� ȭ�� ���
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void) {
	int num;
	stacktype m;
	init_stack(&m);
	int r, c;

	printf("0. ����\n1. �Ա����� �ⱸ������ �̷ΰ�θ� ���(�Ѱ�����)\n2. ��� Ż���� ���\n\n");
	printf("���ڸ� �Է����ּ���: ");
	scanf("%d", &num);
	printf("-------------------------------------------------------\n");
	switch (num) {
	case 0: printf("�ý����� �����մϴ�.......\n"); Sleep(2000); exit(1); // 0�̸� ����
	case 1:
		while (1) {
			r = here.r;
			c = here.c;
			if (maze[r][c] == 'x') {
				printf("\n****** ���� ******\n\n");
				exit(1);
			}
			else {
				maze[r][c] = '.';
				push_loc(&m, r + 1, c); //��
				push_loc(&m, r - 1, c); //��
				push_loc(&m, r, c - 1); //��
				push_loc(&m, r, c + 1); //��
				here = pop(&m);
				maze_print(maze);
			}
			
		}
	case 2:
		while (1) {
			r = here.r;
			c = here.c;
			if (maze[r][c] == 'x') {
				printf("\n****** ���� ******\n\n");
				here = pop(&m);
			}
			else {
				maze[r][c] = '.';
				push_loc(&m, r + 1, c); //��
				push_loc(&m, r - 1, c); //��
				push_loc(&m, r, c - 1); //��
				push_loc(&m, r, c + 1); //��

				maze_print(maze);
				if (is_empty(&m)) { // ������ ���� �� ���̻� ���� ���� ��
					printf("\n****** ����! ******\n\n");
					break;
				}

				else // ���� ĭ���� �Ѿ ��
					here = pop(&m);
			}
		}
	}
	return 0;
}
