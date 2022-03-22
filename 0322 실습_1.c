// 1. 지수를 저장하지 않고, 0을 포함하는 계수만 배열에 저장
#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) (((a)>(b))?(a):(b))
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101

typedef struct { // 방법 1 구조체
	int coef[MAX_DEGREE];
	int degree;
}polyn;

polyn input(polyn a) { // 방법 1 저장
	printf("Input degree : ");

	scanf("%d", &a.degree);
	
	printf("Input coef : ");
	for (int i = 0; i <= a.degree; i++) scanf("%d", &a.coef[i]);

	return a;
}


polyn poly_add1(polyn A, polyn B){
	polyn C; // 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;

	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	if (A.degree == B.degree) { // 최고차항의 계수가 같을경우
		for (int i = 0; A.coef[i] == B.coef[i]; i++)
			C.degree--;

		Apos += A.degree - C.degree;
		Bpos += A.degree - C.degree;
	}

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A항 > B
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}

		else if (degree_a == degree_b) {  // A항 == B항
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--; degree_b--;
		}

		else { // B항 > A항
			C.coef[Cpos++] = (-1) * B.coef[Bpos++];
			degree_b--;
		}

	}

	return C;

}

void print (polyn a) { //출력
	printf("%dx^%d", a.coef[0], a.degree); //최고차항만 별도

	int num = a.degree - 1;

	for (int i = 1; i <= a.degree; i++) {
		if (num != 0) {
			if (a.coef[i] > 0 && a.coef[i] != 1) {
				printf(" +%dx^%d", a.coef[i], num);
				num--;
			}

			else if (a.coef[i] < 0 && a.coef[i] != -1) {
				printf(" %dx^%d", a.coef[i], num);
				num--;
			}

			else if (a.coef[i] == 1) {
				printf(" +x^%d", num);
				num--;
			}

			else if (a.coef[i] == -1) {
				printf(" -x^%d", num);
				num--;
			}

			else if (a.coef[i] == 0) num--;
		}

		else if (num == 0) {

			if (a.coef[i] > 0) {
				printf(" +%d", a.coef[i]);
				num--;
			}

			else if (a.coef[i] < 0) {
				printf(" %d", a.coef[i]);
				num--;
			}

			else {
				num--;
			}
		}
	}
}

int poly_eval(polyn a, float x) {

	int result_x = a.coef[a.degree]; //상수 값

	int j = 1;

	for (int i = 1; i <= a.degree; i++) {
		j *= x;
		result_x += a.coef[a.degree - i] * j;
	}

	return result_x;
}


int main(void) {
	polyn a = { 0,{0,} };
	polyn b = { 0,{0,} };
	polyn c = { 0,{0,} };
	a = input(a);

	print(a);

	printf("\n");
	b = input(b);

	c = poly_add1(a, b);

	printf("\nA - B :");
	print(c);

	int x;
	printf("\nInput X : ");
	scanf("%d", &x);

	int result_A = poly_eval(a, x);
	int result_B = poly_eval(b, x);
	int result_C = poly_eval(c, x);

	printf("\nPoly A의 x 대입 값 : %d", result_A);
	printf("\nPoly B의 x 대입 값 : %d", result_B);
	printf("\nPoly C의 x 대입 값 : %d", result_C);
	return 0;
}




