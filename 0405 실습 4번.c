/*
 다음 연산자들을 포함하는 후위표기식 계산하는 프로그램을 스택을 이용하여 작성하시오.
 +, -, *, /, ^(거듭제곱) >, <, =(EQ), & (AND), | (OR)
 (예) 3 4 + 2 - 2 2 2 ^ * > 7 3 – 2 / 5 2 * &                  */

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
		printf("FULL");
		exit(1);
	}
	else
		s->data[++s->top] = c;
}

element pop(stacktype* s) {
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peak(stacktype* s) {
	if (is_empty(s)) {
		printf("3오류입니다.");
		exit(1);
	}
	else
		return s->data[s->top];
}

int square(int a, int b) { //제곱하는 함수
	int sum = 1;
	for (int i = 0; i < b; i++)
		sum *= a;

	return sum;
}

int eval(char* s) { // 후위연산을 계산하는 함수
	int op1, op2, value = 0;
	int len = strlen(s);
	char ch;
	stacktype k;
	init_stack(&k);

	for (int i = 0; i < len; i++) {
		ch = s[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|') {
			value = ch - '0';
			push(&k, value);
		}

		else {
			op2 = pop(&k);
			op1 = pop(&k);

			switch (ch) {
			case '+': push(&k, op1 + op2); printf("%d+%d = %d를 push 했습니다. \n", op1, op2, op1 + op2); break;
			case '-': push(&k, op1 - op2); printf("%d-%d = %d를 push 했습니다. \n", op1, op2, op1 - op2); break;
			case '*': push(&k, op1 * op2); printf("%d*%d = %d를 push 했습니다. \n", op1, op2, op1 * op2); break;
			case '/': push(&k, op1 / op2); printf("%d/%d = %d를 push 했습니다. \n", op1, op2, op1 / op2); break;
			case '^': push(&k, square(op1, op2)); printf("%d^%d = %d를 push 했습니다. \n", op1, op2, square(op1,op2)); break;
			case '>':
				if (op1 > op2) {
					push(&k, 1);
					printf("%d>%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}
				else {
					push(&k, 0);
					printf("%d>%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}

			case '<':
				if (op1 < op2) {
					push(&k, 1);
					printf("%d<%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}

				else {
					push(&k, 0);
					printf("%d<%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}

			case '=':
				if (op1 == op2) {
					push(&k, 1);
					printf("%d=%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}
				else {
					push(&k, 0);
					printf("%d=%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}
			case '&': push(&k, op1 && op2); printf("%d & %d %d push 했습니다. \n", op1, op2, op1 && op2); break;
			case '|': push(&k, op1 || op2); printf("%d l %d %d push 했습니다. \n", op1, op2, op1 && op2); break;
			}
		}
	}
	return pop(&k);
}

	int main(void) {
		int result;
		char str[MAX];
		scanf("%s", str);
		result = eval(str);

		printf("%d", result);

		return 0;
	}