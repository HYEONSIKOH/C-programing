// 1. ������ �������� �ʰ�, 0�� �����ϴ� ����� �迭�� ����
#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) (((a)>(b))?(a):(b))
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101

typedef struct { // ��� 1 ����ü
	int coef[MAX_DEGREE];
	int degree;
}polyn;

polyn input(polyn a) { // ��� 1 ����
	printf("Input degree : ");

	scanf("%d", &a.degree);
	
	printf("Input coef : ");
	for (int i = 0; i <= a.degree; i++) scanf("%d", &a.coef[i]);

	return a;
}


polyn poly_add1(polyn A, polyn B){
	polyn C; // ��� ���׽�
	int Apos = 0, Bpos = 0, Cpos = 0; // �迭 �ε��� ����
	int degree_a = A.degree;
	int degree_b = B.degree;

	C.degree = MAX(A.degree, B.degree); // ��� ���׽� ����

	if (A.degree == B.degree) { // �ְ������� ����� �������
		for (int i = 0; A.coef[i] == B.coef[i]; i++)
			C.degree--;

		Apos += A.degree - C.degree;
		Bpos += A.degree - C.degree;
	}

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A�� > B
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}

		else if (degree_a == degree_b) {  // A�� == B��
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--; degree_b--;
		}

		else { // B�� > A��
			C.coef[Cpos++] = (-1) * B.coef[Bpos++];
			degree_b--;
		}

	}

	return C;

}

void print (polyn a) { //���
	printf("%dx^%d", a.coef[0], a.degree); //�ְ����׸� ����

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

	int result_x = a.coef[a.degree]; //��� ��

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

	printf("\nPoly A�� x ���� �� : %d", result_A);
	printf("\nPoly B�� x ���� �� : %d", result_B);
	printf("\nPoly C�� x ���� �� : %d", result_C);
	return 0;
}




