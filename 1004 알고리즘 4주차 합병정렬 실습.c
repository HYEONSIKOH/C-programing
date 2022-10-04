/*
1. 임의 순서의 n 개 정수 값을 순환호출을 이용하여 병합정렬하는 프로그램을 작성하시오
(하향식). 단계별 결과를 확인할 수 있도록 출력하시오.
각 단계에서 병합된 범위 [I, j]를 확인할 수 있도록 출력을 추가하시오.

2. 임의 순서의 n 개 정수 값을 반복문장을 이용하여 병합정렬하는 프로그램을 작성하시오
(상향식).
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* arr;
int size;

// =================== 출력 함수 ===================
void print(int s, int e) {
	for (int i = 0; i < size; i++) {
		if (i >= s && i <= e) printf("\033[0;32m%d\033[0m ", arr[i]);
		else printf("%d ", arr[i]);
	}
	printf(" [S:%d E:%d]", s, e);
	printf("\n");
}

// =================== 병합 함수 ===================
void merge(int start,int mid, int end) {
	int s = start;
	int m = mid + 1;
	int idx = 0;
	int* temp = (int*)malloc(sizeof(int) * (end - start + 1));

	while (s <= mid && m <= end) {
		if (arr[s] < arr[m]) temp[idx++] = arr[s++];
		else temp[idx++] = arr[m++];
	}

	while (s <= mid) temp[idx++] = arr[s++];
	while (m <= end) temp[idx++] = arr[m++];

	int idx2 = 0;
	int s2 = start;

	while (s2 <= end) arr[s2++] = temp[idx2++];
	free(temp);
}

// =================== 1번 함수 ===================
void merge_sort1(int start, int end) {
	int mid;

	if (start < end) {
		mid = (start + end) / 2;
		merge_sort1(start, mid);
		merge_sort1(mid + 1, end);
		merge(start,mid, end);
		print(start, end);
	}
}

// =================== 2번 함수 ===================
void merge_sort2(int start, int end) {
	for (int n = 1; n < size+1; n *= 2){
		for (int s = start; s < end; s += 2 * n){
			int e = min(s + 2 * n - 1, end);
			int m = s + n - 1;

			merge(s, m, e);
			print(s, e);
		}
	}
}

// =================== 기타 함수 ===================
void menu() {
	printf("=================== [메뉴] ===================\n");
	printf("1. 순환문 합병정렬\n");
	printf("2. 반복문 합병정렬\n");
	printf("0. 종료\n");
	printf("==============================================\n");
	printf("입력 : ");
}

void resize_arr() {
	printf("배열 크기를 입력해주세요 : ");
	scanf("%d", &size);
	arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) arr[i] = rand() % 100 + 1;
}

int main() {
	int num;
	menu();
	scanf("%d", &num);

	while (num != 0) {
		switch (num) {
		case 1:
			resize_arr();
			merge_sort1(0, size - 1);
			break;

		case 2:
			resize_arr();
			merge_sort2(0, size - 1);
			break;

		default:
			printf("잘못된 접근입니다.\n");
		}
		free(arr);
		menu();
		scanf("%d", &num);
	}

	return 0;
}