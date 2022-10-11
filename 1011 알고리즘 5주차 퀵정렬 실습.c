/*
1. 임의 순서의 n 개 정수 값을 퀵정렬 방법으로 정렬하는 프로그램을 작성하시오.
아래 세 가지 분할 방식을 각각 함수로 작성하고,
서로 다른 퀵정렬이 진행되는 과정을 단계별로 출력하시오.
초기값의 순서는 동일하고, 중간단계들의 결과들은 분할방식마다 다르고,
최종 결과는 오름차순 정렬된 순서로 동일하다.

(1) 함수 partition1( )으로 정렬
구간의 맨 마지막 위치의 값을 피봇으로 – 교재 104쪽 알고리즘 4-6 참조

(2) 함수 partition2( )로 정렬
구간의 맨 앞 위치의 값을 피봇으로 – 교재 129쪽 연습문제 15 참조

(3) 아래의 함수를 partition3( )로 사용하여 정렬 (코드를 삽입하여 직접 활용하기 전에 충분
히 이해하기를 권함)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size;
int* arr;

// =================== 기타 함수 ===================
void resize_arr() {
	printf("크기 입력 : ");
	scanf("%d", &size);
	arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) arr[i] = rand() % 100 + 1;
}

void swap(int a, int b) {
	int temp;

	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void menu() {
	printf("=================== [메뉴] ===================\n");
	printf("1. partition1( )\n");
	printf("2. partition2( )\n");
	printf("3. partition3( )\n");
	printf("0. 종료\n");
	printf("==============================================\n");
	printf("입력 : ");
}

void print(int s, int e, int p) {
	for (int i = 0; i < size; i++) {
		if (i >= s && i <= e && i != p) printf("\033[0;32m%d\033[0m ", arr[i]);
		else if (i == p) printf("\033[0;31m%d\033[0m ", arr[i]);
		else printf("%d ", arr[i]);
	}
	if(s!=-1 && e!=-1) printf(" [S:%d E:%d]", s, e);
	printf("\n");
}

// 1번 => 피봇이 맨 끝
int partition1(int start, int end) {
	int j = start; // swap을 진행할 기준 위치
	int p = arr[end]; // 기준 원소

	for (int i = start; i < end; i++)
		if (arr[i] < p)
			swap(i, j++);

	swap(j, end);
	print(start, end, j);
	return j; // mid값을 반환하기 위해!
}

void quickSort1(int start, int end) {
	if (start < end) {
		int mid = partition1(start, end);
		quickSort1(start, mid - 1);
		quickSort1(mid + 1, end);
	}
}

// 2번 => 피봇이 맨 앞
int partition2(int start, int end) {
	int j = start; // swap을 진행할 기준 위치
	int p = arr[start]; // 기준 원소

	for (int i = start + 1; i <= end; i++)
		if (arr[i] < p)
			swap(i, ++j);

	swap(j, start);
	print(start, end, j);
	return j; // mid값을 반환하기 위해!
}

void quickSort2(int start, int end) {
	if (start < end) {
		int mid = partition2(start, end);
		quickSort2(start, mid - 1);
		quickSort2(mid + 1, end);
	}
}

// 3번 => 피봇이 처음인가 나중인가....?
int partition3(int start, int end) {
	int Pivot_Value = arr[start];
	int Left_Mark = start + 1, Right_Mark = end;

	while (Left_Mark <= Right_Mark) {
		while (arr[Left_Mark] <= Pivot_Value) Left_Mark++;
		while (arr[Right_Mark] > Pivot_Value) Right_Mark--;
		if (Left_Mark < Right_Mark) swap(Left_Mark, Right_Mark);
	}

	swap(start, Right_Mark);
	print(start, end, Right_Mark);
	return Right_Mark;
}

void quickSort3(int start, int end) {
	if (start < end) {
		int mid = partition3(start, end);
		quickSort3(start, mid - 1);
		quickSort3(mid + 1, end);
	}
}

int main() {
	int num;
	menu();
	scanf("%d", &num);

	while (num != 0) {
		switch (num) {
		case 1:
			resize_arr();
			printf("원래 배열 : ");
			print(-1, -1, -1);
			printf("\n");
			quickSort1(0, size - 1);
			break;

		case 2:
			resize_arr();
			printf("원래 배열 : ");
			print(-1, -1, -1);
			printf("\n");
			quickSort2(0, size - 1);
			break;

		case 3:
			resize_arr();
			printf("원래 배열 : ");
			print(-1, -1, -1);
			printf("\n");
			quickSort3(0, size - 1);
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