/*
다음과 같이 문자열을 압축하는 프로그램을 작성하시오. "4a3b"는 'a'가 4개, 'b'가 3개 있다는
의미이다. 소문자와 대문자는 구분하지 않고, 출력할 때는 소문자로 출력한다.
 예: 문자열 입력 aaaAbBb 압축결과 4a3b
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
		printf("FULL");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

void pop(stacktype* s) {
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}
	else
		s->data[--s->top];
}

element peak(stacktype* s) {
	if (is_empty(s)) {
		printf("3오류입니다.");
		exit(1);
	}
	else
		return s->data[s->top];
}

int main(void) {
	stacktype s;
	init_stack(&s);
	char str[MAX];
	gets(str);
	char sw = tolower(str[0]);
	

	for (int i = 0; i < strlen(str); i++) {
		push(&s, tolower(str[i]));
		if (peak(&s) != sw ) {
			pop(&s);
			printf("%d%c ", s.top + 1, peak(&s));

			init_stack(&s);
			push(&s, tolower(str[i]));
			sw = peak(&s);

			if (i == strlen(str) - 1) {
				printf("%d%c ", s.top + 1, peak(&s));
				break;
			}
		}
		else if (i == strlen(str) - 1)
			printf("%d%c ", s.top + 1, peak(&s));
	}
	return 0;
}