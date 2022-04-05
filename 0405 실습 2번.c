/*
������ ���� ���ڿ��� �����ϴ� ���α׷��� �ۼ��Ͻÿ�. "4a3b"�� 'a'�� 4��, 'b'�� 3�� �ִٴ�
�ǹ��̴�. �ҹ��ڿ� �빮�ڴ� �������� �ʰ�, ����� ���� �ҹ��ڷ� ����Ѵ�.
 ��: ���ڿ� �Է� aaaAbBb ������ 4a3b
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
		printf("3�����Դϴ�.");
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