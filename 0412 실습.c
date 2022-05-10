/*
중위표기수식을 후위표기수식으로 변환 (교재 프로그램4.8) 하고,
이어서, 변환된 후위표기수식의 값을 계산 (교재 프로그램 4.7) 하는 전체 프로그램을 완성하시오.

입력 예 : 중위표기(2 + 3)* (4 – 1)
중간결과 예 : 후위표기 2 3 + 4 1 - *
연산결과 값 : 15

(1) + , -, *, / 에 추가하여 나머지 연산자 % 를 포함하시오.
예 : (4 + 9 - 1) % (2 + 1)
(2) 거듭제곱 연산의 기호를 ‘ ^ ’라고 가정하고 거듭제곱연산을 포함하시오.
예 : 3 + 2 ^ 3 ^ 2 – 1
(3) 관계연산자 ‘<’와 ‘>’을 포함하시오.
예 : 3 + 4 – 2 > 2 * 3 ^ 2
(4) 논리연산 AND와 OR의 기호를 각각 ‘ & ’와 ‘ | ’라고 가정하고, 이 연산자들을 포함하시오.
예: 3 + 4 – 2 > 2 * 2 ^ 2 & (5 – 3) % 2 < 5 * 2

	main()에서는:
-위 사칙연산자와 위의(1)~(4) 연산자를 포함하는 중위표기식을 키보드로 입력하고,
-함수호출하여 중위표기식을 후위표기식으로 변환해서 문자열에 저장하고,
-함수호출하여 후위표기식을 계산하고 결과값을 출력한다.
- 위의 두 과정에서, 스택의 동작이 화면에 출력되도록 하시오. */

/* 
    < 예제 >
(1) (4+9-1)%(2+1)
(2) 3+2^3^2–1
(3) 3+4–2>2*3^2
(4) 3+4–2>2*2^2&(5–3)%2<5*2
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef char element;

typedef struct {
	char data[MAX];
	int num[MAX];
	int top;
}stacktype;

int is_full(stacktype* s) {
	return (s->top == 99);
}

int is_empty(stacktype* s) {
	return (s->top == -1);
}

void init_stack(stacktype* s) { // 스택 초기화
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

void push_2(stacktype* s, int c) { // int형 임시 스택
	if (is_full(s)) {
		printf("FULL");
		exit(1);
	}
	else
		s->num[++s->top] = c;


}
element pop(stacktype* s) {
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}
	else 
		return s->data[(s->top)--];
}

int pop_2(stacktype* s) { // int형 임시 스택
	if (is_empty(s)) {
		printf("EMPTY");
		exit(1);
	}

	else 
		return s->num[(s->top)--];
	
}

element peak(stacktype* s) { 
	if (is_empty(s))
		return 2;
	
	else
		return s->data[s->top];
}

element peak_2(stacktype* s) { // int형 임시 스택
	if (is_empty(s))
		return 2;
	
	else
		return s->num[s->top];
}

int rank(char ch) { // 연산 순위
	switch (ch) {
	case '(': return 0;
	case '^': return 6;
	case '*': case'/': case'%': return 5;
	case '+': case'-': return 4;
	case '<': case'>': return 3;
	case '&': return 2;
	case '|': return 1;
	}
}

void fix(char* str) { // 중위에서 후위로 변환하는 함수
	stacktype s;
	init_stack(&s);

	int len = strlen(str);
	char ch;
	char terms[MAX] = { 0, };

	int index = 0;
	printf("--------중위에서 후위 변환중--------\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		
		if (47 < ch && ch < 58)
			terms[index++] = ch;

		else {
			if (s.top == -1 || ch == '(') {
				push(&s, ch);
				printf("%c를 push 했습니다.\n", ch);
			}

			else if (peak(&s) == '^' && ch == '^') {
				printf("%c를 push 했습니다.\n", ch);
				push(&s, ch);
			}

			else if (ch == ')') {
				while (peak(&s) != '(') {
					printf("%c를 pop 했습니다.\n", peak(&s));
					terms[index++] = pop(&s);
				}

				printf("%c를 pop 했습니다.\n", peak(&s));
				pop(&s);
			}
				
			else if (rank(peak(&s)) >= rank(ch) && ch != '(') { 
				while (! is_empty(&s) && rank(peak(&s)) >= rank(ch)) { // 순서가 높은 연산식이 두개 이상일때
					printf("%c를 pop 했습니다.\n", peak(&s));
					terms[index++] = pop(&s);
				}
				printf("%c를 push 했습니다.\n", ch);
				push(&s, ch);
			}

			else {
				printf("%c를 push 했습니다.\n", ch);
				push(&s, ch);
			}
				
		}
	}

	while (s.top != -1) {
		printf("%c를 pop 했습니다.\n", peak(&s));
		terms[index++] = pop(&s);
	}
		

	
	printf("\n후위연산: ");
	printf("%s\n\n", terms);

	printf("------------계산중------------\n");
	printf("\n값: %d\n\n",eval(terms));
	
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
		if (ch !='%' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|') {
			value = ch - '0';
			push_2(&k, value);
		}

		else {
			op2 = pop_2(&k);
			op1 = pop_2(&k);

			switch (ch) {
			case '+': push_2(&k, op1 + op2); printf("%d+%d = %d를 push 했습니다. \n", op1, op2, op1 + op2); break;
			case '-': push_2(&k, op1 - op2); printf("%d-%d = %d를 push 했습니다. \n", op1, op2, op1 - op2); break;
			case '*': push_2(&k, op1 * op2); printf("%d*%d = %d를 push 했습니다. \n", op1, op2, op1 * op2); break;
			case '%': push_2(&k, op1 % op2); printf("%d%c%d = %d를 push 했습니다. \n", op1,37, op2, op1 % op2); break;
			case '/': push_2(&k, op1 / op2); printf("%d/%d = %d를 push 했습니다. \n", op1, op2, op1 / op2); break;
			case '^': push_2(&k, square(op1, op2)); printf("%d^%d = %d를 push 했습니다. \n", op1, op2, square(op1, op2)); break;
			case '>':
				if (op1 > op2) {
					push_2(&k, 1);
					printf("%d>%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}
				else {
					push_2(&k, 0);
					printf("%d>%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}

			case '<':
				if (op1 < op2) {
					push_2(&k, 1);
					printf("%d<%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}

				else {
					push_2(&k, 0);
					printf("%d<%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}

			case '=':
				if (op1 == op2) {
					push_2(&k, 1);
					printf("%d=%d 참이므로 1 push 했습니다. \n", op1, op2);
					break;
				}
				else {
					push_2(&k, 0);
					printf("%d=%d 거짓이므로  0 push 했습니다. \n", op1, op2);
					break;
				}
			case '&': push_2(&k, op1 && op2); printf("%d & %d %d push 했습니다. \n", op1, op2, op1 && op2); break;
			case '|': push_2(&k, op1 || op2); printf("%d l %d %d push 했습니다. \n", op1, op2, op1 && op2); break;
			}
		}
	}
	return pop_2(&k);
}

int main(void) {
	char str[MAX] = { 0, };
	gets(str);

	char terms[MAX];
	printf("\n중위연산: %s\n\n", str);

	fix(str);
	
	return 0;
}