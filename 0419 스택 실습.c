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

element here = { 1,0 }; // 현 위치

char maze[MAZE_SIZE][MAZE_SIZE] = { // 미로 e가 현재 위치, 0은 경로, 1은 벽, x는 출구
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

int is_full(stacktype* s) { // 꽉 찼을때
	return (s->top == 99);
}

int is_empty(stacktype* s) { // 텅텅 비었을때
	return (s->top == -1);
}

void init_stack(stacktype* s) { // 스택 초기화
	s->top = -1;
}

void push(stacktype* s, element c) { // 입력함수
	if (is_full(s)) {
		printf("FULL");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

element pop(stacktype* s) { // 삭제 함수
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peak(stacktype* s) { // 참조 함수
	if (is_empty(s)) {
		printf("3오류입니다.");
		exit(1);
	}
	else
		return s->data[s->top];
}

void peak_print(stacktype* s) { // 참조 함수
	if (is_empty(s)) {
		printf("3오류입니다.");
		exit(1);
	}
	else
		printf("[%d , %d]\n", s->data[s->top].r, s->data[s->top].c);
}

void push_loc(stacktype* s, int r, int c) { // 현 위치를 화면에 출력한다.
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

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) { // 미로 화면 출력
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

	printf("0. 종료\n1. 입구부터 출구까지의 미로경로를 출력(한가지만)\n2. 모든 탈출경로 출력\n\n");
	printf("숫자를 입력해주세요: ");
	scanf("%d", &num);
	printf("-------------------------------------------------------\n");
	switch (num) {
	case 0: printf("시스템을 종료합니다.......\n"); Sleep(2000); exit(1); // 0이면 종료
	case 1:
		while (1) {
			r = here.r;
			c = here.c;
			if (maze[r][c] == 'x') {
				printf("\n****** 성공 ******\n\n");
				exit(1);
			}
			else {
				maze[r][c] = '.';
				push_loc(&m, r + 1, c); //상
				push_loc(&m, r - 1, c); //하
				push_loc(&m, r, c - 1); //좌
				push_loc(&m, r, c + 1); //우
				here = pop(&m);
				maze_print(maze);
			}
			
		}
	case 2:
		while (1) {
			r = here.r;
			c = here.c;
			if (maze[r][c] == 'x') {
				printf("\n****** 성공 ******\n\n");
				here = pop(&m);
			}
			else {
				maze[r][c] = '.';
				push_loc(&m, r + 1, c); //상
				push_loc(&m, r - 1, c); //하
				push_loc(&m, r, c - 1); //좌
				push_loc(&m, r, c + 1); //우

				maze_print(maze);
				if (is_empty(&m)) { // 스택이 텅텅 비어서 더이상 길이 없을 때
					printf("\n****** 실패! ******\n\n");
					break;
				}

				else // 다음 칸으로 넘어갈 때
					here = pop(&m);
			}
		}
	}
	return 0;
}
