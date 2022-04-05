/*
palindrome – 교재 144쪽 문제 16
회문은 앞뒤 어느 쪽에서 읽어도 같은 단어를 의미한다(예: "eye" "madam" "race car" 등)
구두점이나 스페이스, 대소문자 등은 무시해야 한다.
스택을 사용해서 주어진 문자열이 회문인지 아닌지 결정하는 프로그램을 작성하시오.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char str[MAX];
	gets(str);
	stacktype s;
	init_stack(&s);

	for (int i = 0; i < strlen(str); i++) {
		if (65 <= str[i] && str[i] <= 90 || 97 <= str[i] && str[i] <= 122)
			push(&s, tolower(str[i]));
	}
	int index = s.top;
	char* a = s.data;

	for (int i = 0; i < index; i++) {
		if (a[i] != peak(&s)) {
			printf("회문이 아닙니다.");
			return 0;
		}
		else
			pop(&s);
	}
	printf("회문입니다.");
	return 0;
}