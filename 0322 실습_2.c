// 2. {계수 , 지수} 쌍으로 저장
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	float coef;
	int expon;
}polynomial;

polynomial terms[MAX_TERMS] = { {0,0}, };

int avail ;

void input() {
	printf("Input : ");
	for (int i = 0; i < avail; i++)
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
}

char compare(int a, int b) { // 두개의 정수를 비교
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(float coef, int expon){ // 새로운 항을 다항식에 추가한다.

	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}

	terms[avail].coef = coef;
	terms[avail].expon = expon;

	avail++;
}

void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	float tempcoef;

	*Cs = avail;

	while (terms[As].expon == terms[Bs].expon) { // 최고차항의 계수가 똑같을 경우
		if (terms[As].coef == terms[Bs].coef) {
			As += 1;
			Bs += 1;
		}
	}

	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>': // A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++; break;

		case '=': // A의 차수 == B의 차수
			tempcoef = terms[As].coef - terms[Bs].coef;

			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++; break;

		case '<': // A의 차수 < B의 차수
			attach((-1 *terms[Bs].coef), terms[Bs].expon);
			Bs++; break;
		}



	for (; As <= Ae; As++) // A의 나머지 항들을 이동함
		attach(terms[As].coef, terms[As].expon);

	for (; Bs <= Be; Bs++) // B의 나머지 항들을 이동함
		attach(terms[Bs].coef, terms[Bs].expon);

	*Ce = avail - 1;
}
void print_poly(int s, int e){ //출력 함수

	printf("%3.1fx^%d ", terms[s].coef,terms[s].expon);

	for (int i = s+1; i <= e; i++) {
		if (terms[i].expon == 1) {
			if (terms[i].coef == 1) printf("+x ", terms[i].coef);
				
			else if (terms[i].coef == -1) printf("-x ", terms[i].coef);

			else printf("+%3.1fx ", terms[i].coef);
		}

		else if (terms[i].expon == 0) printf("+%3.1f\n", terms[e].coef);

		else {
			if (terms[i].coef == 1) printf("+x^%d  ", terms[i].expon);

			else if (terms[i].coef == -1) printf("-x^%d ", terms[i].expon);

			else printf("+%3.1fx^%d ", terms[i].coef, terms[i].expon);
		}
	}
}

float poly_eval(int s, int e , int x) { // X값 대입
	float result = 0;

	for (int i = e; i >= s; i--) {
		int k = 1;
		for (int a = terms[i].expon; a > 0; a--) {
			k *= x;
		}
		result += terms[i].coef * k;
	}

	return result;
}

int main(void){
	printf("A length : ");
	int Al;
	scanf("%d", &Al);

	printf("B length : ");
	int Bl;
	scanf("%d", &Bl);

	avail = Al + Bl;

	input();

	int x;
	printf("Input x : ");
	scanf("%d", &x);

	int As = 0; int Ae = Al - 1; int Bs = Al; int Be = Ae + Bl; int* Cs; int *Ce;
	poly_add2(As, Ae, Bs, Be, &Cs, &Ce);

	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("----------------------------------------------------------------------------\n");
	print_poly(Cs, Ce);

	printf("\n");
	printf("A(%d) : %3.1f\n", x,poly_eval(As, Ae, x));
	printf("B(%d) : %3.1f\n", x,poly_eval(Bs, Be, x));
	printf("C(%d) : %3.1f\n", x,poly_eval(Cs, Ce, x));

	return 0;
}