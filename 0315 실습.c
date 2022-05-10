#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//문자열에서 알파벳 대문자, 소문자, 숫자, 특수문자(!, ? , *, #, $)가 모두 포함되어 있는지, 
//또 길이가 10자 이상인지 판단하는 함수 (그 밖의 문자는 포함 할 수 없음)

int Password(char* s) {
	int sc = 0;
	int nc = 0;
	int Ac = 0;
	int ac = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '!' || s[i] == '?' || s[i] == '*' || s[i] == '#' || s[i] == '$') // 특수기호
			sc++;
		else if (s[i] >= '0' && s[i] <= '9') // 숫자
			nc++;
		else if (s[i] >= 'A' && s[i] <= 'Z') // 대문자
			Ac++;
		else if (s[i] >= 'a' && s[i] <= 'z') // 소문자
			ac++;
	}
	int sum = sc + nc + Ac + ac; // 10자 이상인지 미만인지 구하는 식

	if (sc != 0 && nc != 0 && Ac != 0 && ac != 0 && sum >= 10)
		printf("정상입니다.");

	if (sc == 0)
		printf("\n특수기호가 없습니다.");

	if (nc == 0)
		printf("\n숫자가 없습니다.");

	if (Ac == 0)
		printf("\n대문자가 없습니다.");

	if (ac == 0)
		printf("\n소문자가 없습니다.");

	if (sum < 10)
		printf("\n길이가 10자 미만입니다.");
}




//구조체로 정의된 복소수 n개를 배열에 저장하고, 전체합을 구하는 순환호출 함수

typedef struct { // a+bi 복소수 구조체
	int a; //실수
	int b; //허수
}complex;


int add_a(complex* arr, int n) { // 실수 a의 합을 구하는 함수
	if (n < 0)
		return 0;
	else
		return arr[n].a + add_a(arr, n - 1);
}
int add_b(complex* arr, int n) { // 허수 bi의 합을 구하는 함수
	if (n < 0)
		return 0;
	else
		return arr[n].b + add_b(arr, n - 1);
}





// 문자열 길이 구하기

int len(char* str) {
	if (*str == 0)
		return 0;
	else
		return 1 + len(str + 1); // 순환함수
}





// 이진검색(binary search)함수 순환호출 방법으로 작성

int bs(int* arr, int num, int start, int end) {
	int n = (start + end) / 2; // 미드 값

	if (start > end) return printf("\n#########No result#########"); // 끝까지 찾았는데, 값이 없는 경우

	printf("\n시작 값:%d 끝 값:%d 중간 값:%d", arr[start], arr[end], arr[n]);

	if (num < arr[n]) return bs(arr, num, start, n - 1); // 미드 값이 찾는 값보다 큰 경우


	else if (num > arr[n]) return bs(arr, num, n + 1, end); // 미드 값이 찾는 값보다 작은 경우


	else if (num == arr[n]) return printf("\n%d는 %d번째 입니다.", num, n + 1); // 마지막 찾는 경우

}
int Sort(int* arr, int num) { // 오름차순 정렬
	int a;
	for (int i = 0; i < num; i++) {
		for (int n = 0; n + i < num; n++)
			if (arr[n] > arr[n + 1]) {
				a = arr[n];
				arr[n] = arr[n + 1];
				arr[n + 1] = a;
			}
	}
	return *arr;
}


int main(void) {
	while (1) {
		printf("\n---------------------------------------------------\n");
		printf("0 : 종료 \n1 : 패스워드 \n2 : 복소수 합 (순환호출)  \n3 : 문자열 길이 구하기 (순환호출) \n4 : 이진검색(binary search)함수 (순환호출)\n");
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
				printf("문장을 입력하세요:");
				char str[100];
				gets(str);
				Password(str);
				break;
			}

			case 2: {
				complex arr[] = { {1,1},{1,2},{2,3},{4,1} };
				printf("%d+%di 입니다.", add_a(arr, 3), add_b(arr, 3));
				break;
			}

			case 3: {
				char str[100];
				printf("Write the Sentence:");
				gets(str);

				printf("Strlen : %d", len(str));
				break;
			}

			case 4: {
				int search;
				int num;
				printf("Arr size:");
				scanf("%d", &num);

				int* arr = (int*)malloc(sizeof(int*) * num);
				printf("\nWrite %d number:", num);;
				for (int i = 0; i < num; i++) scanf("%d", &arr[i]);

				*arr = Sort(arr, num - 1);
				printf("Sort: ");
				for (int i = 0; i < num; i++) printf("%d ", arr[i]);

				printf("\nChoose the number:");
				scanf("%d", &search);

				bs(arr, search, 0, num - 1);

				break;
			}

			}
		}
	}
}
