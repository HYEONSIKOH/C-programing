#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// <문제 1번>
//문자열로 입력된 정수값을 십진수로 변환하는 함수 (문자열을 키보드 입력) 
//예를 들면, 문자열 "234" 는 정수값 234로, "-234" 는 -234로 변환된다.

int len(char* str) { // 문자열 길이 구하기
	int count = 0;
	for (int i = 0; str[i] != 0; i++)
		count++;

	return count;
}

int change_num(char* str) { // 문자열을 정수로 변환
	int result = 0;
	for (int i = 0; i < len(str); i++) {

		if (str[0] == '-' && i == 0) // 음수일 경우, 맨 앞에 '-'부호를 생략하기 위해 처음에만 i++ 실행
			i++;

		int num = 1;

		for (int a = i; a < len(str) - 1; a++) // num 변수에다가 1000의 자리면 1000, 100의 자리면 100 
			num *= 10;

		result += ((str[i] - 48) * num); //문자열을 아스키코드 에서 48을 뺀 값에서, num 값을 곱함
	}
	return result;
}

//<문제 2번> 
//좌표(x, y)를 표현하는 구조체 정의하고, 5개 좌표를 구조체 배열에 저장하고,
//배열에 저장된 5개 좌표 중 원점에서부터 제일 먼 좌표 구하기

typedef struct { // pos라는 (x,y) 구조체 선언
	int x;
	int y;
}pos;

double dismax(pos* a) {
	double arrlen[5];
	for (int i = 0; i < 5; i++)
		arrlen[i] = sqrt(a[i].x * a[i].x + a[i].y * a[i].y);

	double max = arrlen[0];
	int num;

	for (int i = 1; i < 5; i++) {
		if (max < arrlen[i]) {
			max = arrlen[i];
			num = i;
		}
	}
	return num;
}

// <문제 3번>
//8자리 생년월일 (예를 들면, “20200308”) 열 개를 배열에 저장하고, 
//그 중 m(1 <= m <= 12) 월 생이 몇 명인지 계산하기(m을 키보드 입력)

int change_month(char* str) { //4번째,5번째 문자를 4번째는 10의 자리 , 5번째는 일의 자리로 합하고 정수형으로 비교
	int month = ((int)str[4] - 48) * 10 + ((int)str[5] - 48);
	return month;
}

// <문제4번>
//정수 m부터 n까지 합을 구하기 (m<=n 이고 m과 n은 키보드 입력) 
//(1) 반복문장 이용하기(for 문장 또는 while 문장)
//(2) 순환호출 이용하기

int sum(int m, int n) { // for문을 이용한 반복문장
	int num = 0;
	for (; m < n + 1; m++)
		num += m;

	return num;
}

int rotaiton(int m, int n) { // 순환호출 이용
	if (m > n)
		return 0;
	else
		m = rotaiton(m + 1, n);

	return m;
}


int main(void) {
	while (1) {
		printf("---------------------------------------------------\n");
		printf("0 : 종료 \n1 : 문자열 정수 변환 \n2 : 가장 먼 좌표 값 구하기 \n3 : 몇월생이 몇명있는지 구하기 \n4 : M부터 N까지의 합 구하기\n");
		printf("---------------------------------------------------\n");
		int a;
		scanf("%d", &a);
		getchar();

		if (a == 0) {
			printf("종료합니다...");
			return 0;
		}

		else if (a > 4 || a < 0) {
			printf("-----------------------------------\n");
			printf("0 ~ 4 까지만 입력해주세요.\n");
			printf("-----------------------------------\n");
			int a;
			scanf("%d", &a);
			getchar();
		}
		else {
			switch (a) {


			case 1: {
				char str[100];
				printf("-----------------------------------\n");
				printf("문자열을 숫자로만 입력해주세요: ");
				gets(str);

				if (str[0] == '-') { //음수일 경우, 0에서 결과값을 빼고
					printf("-----------------------------------\n");
					printf("int형으로 변환 : %d \n", (0 - change_num(str)));
				}
				else { //양수일 경우 그대로 출력
					printf("-----------------------------------\n");
					printf("int형으로 변환 : %d \n", change_num(str));
				}

				break;
			}



			case 2: {
				pos arr[5] = { {0,9},{1,7},{2,1},{1,1},{-4,9} };

				printf("-----------------------------------\n");
				for (int i = 0; i < 5; i++)
					printf("%d. {%d , %d}\n", i + 1, arr[i].x, arr[i].y);


				int i = dismax(arr);
				printf("-----------------------------------\n");
				printf("MAX X POS : %d  ||  MAX Y POS : %d \n", arr[i].x, arr[i].y);

				break;
			}



			case 3: {
				char* bir[10] = { {"20000407"},{"20011103"},{"20060803"},{"19720501"},{"19691120"},
								  {"20001103"},{"19990803"},{"20000812"},{"19970601"},{"19450625"} };
				int m;
				printf("Month를 입력해주세요:");
				scanf("%d", &m);
				while (m < 1 || m>12) {
					printf("-----------------------------------\n");
					printf("1부터 12까지만 입력해주세요:");
					scanf("%d", &m);
				}

				int count = 0;

				for (int i = 0; i < 9; i++) {
					if (m == change_month(bir[i]))
						count++;
				}


				printf("%d월생 %d명 입니다. \n", m, count);
				break;
			}



			case 4: {
				printf("1. 반복문 (for , while)\n2. 재귀함수\n");
				int c;
				scanf("%d", &c);
				switch (c) {
				case 1: {
					printf("-----------------------------------\n");
					printf("두 개의 정수를 입력해주세요:");

					int m, n;
					scanf("%d %d", &m, &n);

					while (m > n) {
						printf("-----------------------------------\n");
						printf("앞의 수가 더 작게 입력해주세요:");

						scanf("%d %d", &m, &n);
					}

					printf("합 : %d \n", sum(m, n));
					break;
				}
				case 2: {
					printf("-----------------------------------\n");
					printf("두 개의 정수를 입력해주세요:");

					int m, n;
					scanf("%d %d", &m, &n);

					while (m > n) {
						printf("-----------------------------------\n");
						printf("앞의 수가 더 작게 입력해주세요:");
						scanf("%d %d", &m, &n);
					}

					printf("합 : %d \n", sum(m, n));
					break;
				}
				}
			}

			}
		}
	}
}