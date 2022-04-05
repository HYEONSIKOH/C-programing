#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

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
		printf("1오류입니다.");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

void pop(stacktype* s) {
	if (is_empty(s)) {
		printf("2오류입니다.");
		exit(1);
	}
	else
		--s->top;
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
	char sw;
	char temp;
	sw = peak(&s);

	for (int i = 0; i < strlen(str); i++) {
		if (sw == peak(&s))
			pop(&s);
		else {
			
		}
			
	}

}