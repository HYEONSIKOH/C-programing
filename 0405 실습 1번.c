/*
괄호 매칭 번호 매기기 – 교재 143쪽 문제 11
수식에 있는 괄호의 번호를 출력하는 프로그램을 작성하라.왼쪽 괄호가 나올 때마다
괄호 번호는 하나씩 증가한다.오른쪽 괄호가 나오면 매칭되는 왼쪽 괄호의 번호를 출력한다.
예: ((()) (()))
1 2 3 3 2 4 5 5 4 1*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 101

typedef char element;

typedef struct {
	char data[MAX];
	int top;
}stacktype;

int is_full(stacktype* s) {
	return (s->top == 99);
}

int is_empty(stacktype* s) {
	return (s->top == -1);
}

void init_stack(stacktype* s) {
	s->top = -1;
}

void push(stacktype* s, char c) {
	if (is_full(s)) {
		printf("qERROR");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

element pop(stacktype* s) {
	if (is_empty(s)) {
		printf("2ERROR");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peak(stacktype* s) {
	if (is_empty(s)) {
		printf("3ERROR");
		exit(1);
	}
	else
		return s->data[s->top];
}

int check_matching(char* in) { //오류 체크하는 함수
	stacktype s;
	char ch, open_ch;
	init_stack(&s);

	for (int i = 0; i < strlen(in); i++) {
		ch = in[i];
		switch (ch) {
		case '(': case'[':case'{':
			push(&s, ch);
			break;

		case ')': case']':case'}':
			if (is_empty(&s)) return 0;
			else {
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}'))
					return 0;
			}
				break;
			}
		}

		if (!is_empty(&s)) return 0;

		return 1;
	}


int main(void) {
	char str[MAX];
	gets(str);
	char ch;

	stacktype stack_ch;
	stacktype stack_in;
	init_stack(&stack_ch);
	init_stack(&stack_in);

	if (check_matching(str) == 1)
		printf("괄호검사 성공\n");
	else {
		printf("괄호검사 실패");
		return 0;
	}
		

	for (int i = 0; i < strlen(str); i++) {
		ch = str[i];
		switch (ch) {
		case '(': case'[':case'{':
			push(&stack_ch, ch);
			push(&stack_in, stack_ch.top + 49);
			printf("%c ", peak(&stack_in));
			break;

		case ')': case']':case'}':
				printf("%c ", peak(&stack_in));
				pop(&stack_in);
				break;
		}
	}
	return 0;
}