/*
1. 임의 순서의 n 개 정수 값을 선택정렬 방법으로 정렬하시오. 
(1) 각 단계에서 최소값을 구하고, 맨 앞자리로 이동하는 방법을 사용하시오.
(2) 각 단계마다의 진행과정을 확인할 수 있도록 출력으로 보이시오.
(3) 각 단계에서 비교회수, 전체 과정의 비교회수를 계산하시오.

2. 임의 순서의 n 개 정수 값을 삽입정렬 방법으로 정렬하시오. 
각 단계마다 아래 예시와 유사한 단계별 중간 결과를 보이되, 
 (1) 비교 횟수 (2) 부분 정렬 완료된 범위 (3) 전체 비교 횟수를 계산하시오.

3. 임의 순서의 n 개 정수 값을 버블정렬 방법으로 정렬하시오.
값의 교환이 한번도 일어나지 않은 것은 판단하여 종료하는 방법을 선택할 수 있도록 하시오.
각 단계 마다 정렬 진행 상태를 확인할 수 있도록 출력하시오.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int size; // 배열 사이즈를 전역변수

void swap(int* arr,int a,int b) {
	int temp;
	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void show_array(int* arr) {
	for (int i = 0; i < size; i++) printf("[%d] ", arr[i]);
	printf("\n");
}

void menu() {
	printf("=================== [메뉴] ===================\n");
	printf("1. 선택정렬\n");
	printf("2. 삽입정렬\n");
	printf("3. 버블정렬 (T/F)\n");
	printf("4. 버블정렬 (Nomal)\n");
	printf("0. 종료\n");
	printf("==============================================\n");
	printf("입력 : ");
}

// =================================================== 문제 1번 함수
void selection_sort(int* arr) {
	int min, min_index;
	int cnt=0, total_cnt=0;
	printf("정렬 전 배열 : ");
	show_array(arr);
	for (int i = 0; i < size - 1; i++) {
		min = arr[i];
		min_index = i;
		for (int j = i+1; j < size; j++) {
			cnt++;
			if (min > arr[j]) {
				min = arr[j];
				min_index = j;
			}
		}
		swap(arr, min_index, i);
		total_cnt += cnt;
		printf("%d) 비교횟수 : %d\n", i + 1, cnt);

		for (int k = 0; k < i; k++) printf("%d ", arr[k]);
		printf("[%d] ", arr[i]);
		for (int k = i+1; k<size; k++) printf("%d ", arr[k]);
		printf("\n\n");

		cnt = 0;
	}

	printf("\n\n총 비교 횟수 : %d\n", total_cnt);
	printf("정렬된 배열 : ");
	show_array(arr);
}

// =================================================== 문제 2번 함수
void insertion_sort(int* arr) {
	int j, temp;
	int cnt = 0, total_cnt = 0;
	printf("정렬 전 배열 : ");
	show_array(arr);
	printf("\n");

	int bool;
	for (int i = 1; i < size; i++) {
		temp = arr[i];
		bool = 1;
		for (j = i-1; j >=0; j--) {
			cnt++;
			if (temp < arr[j]) {
				arr[j + 1] = arr[j];
				bool = 0;
			}
			else break;
		}
		arr[j+1] = temp;
		total_cnt += cnt;
		printf("%d단계) ", i);
		printf("| 비교 횟수 : %d | ", cnt);

		for (int k = 0; k < i; k++) printf("\033[0;31m%d\033[0m ", arr[k]);
		for (int k = i; k < size; k++) printf("%d ", arr[k]);
		printf("\n\n");

		cnt = 0;
	}
	printf("\n총 비교 횟수 : %d\n", total_cnt);
	printf("정렬된 배열 : ");
	show_array(arr);
}

// =================================================== 문제 3번 함수
void bubble_sort_bool(int* arr) {
	int bool, cnt = 0, total_cnt = 0;
	for(int i = 0; i<size-1; i++){
		bool = 1; // True or False 변수

		printf("%d단계)\n", i + 1);
		for (int j = 0; j < size - 1 - i; j++) {
			cnt++;
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
				bool = 0;

				for (int k = 0; k < j; k++) printf("%d ", arr[k]);
				printf("\033[0;32m%d\033[0m \033[0;32m%d\033[0m ", arr[j], arr[j + 1]);
				for (int k = j + 2; k < size; k++) printf("%d ", arr[k]);
				printf("\n");
			}

			else {
				for (int k = 0; k < size; k++) printf("%d ", arr[k]);
				printf("\n");
			}
		}
		total_cnt += cnt;
		printf("비교횟수 : %d\n",cnt);
		printf("==================================================\n");
		cnt = 0;

		if (bool) {
			printf("\n총 비교 횟수 : %d\n", total_cnt);
			printf("정렬된 배열 : ");
			show_array(arr);
			return;
		}
	
	}
	printf("\n\n총 비교 횟수 : %d\n", total_cnt);
}

void bubble_sort(int* arr) {
	int cnt = 0, total_cnt = 0;
	for (int i = 0; i < size - 1; i++) {
		printf("%d단계)\n", i + 1);
		for (int j = 0; j < size - 1 - i; j++) {
			cnt++;
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);

				for (int k = 0; k < j; k++) printf("%d ", arr[k]);
				printf("\033[0;32m%d\033[0m \033[0;32m%d\033[0m ", arr[j], arr[j + 1]);
				for (int k = j + 2; k < size; k++) printf("%d ", arr[k]);
				printf("\n");
			}

			else {
				for (int k = 0; k < size; k++) printf("%d ", arr[k]);
				printf("\n");
			}
		}
		total_cnt += cnt;
		printf("비교횟수 : %d\n", cnt);
		printf("==================================================\n");
		cnt = 0;
	}
	printf("\n\n총 비교 횟수 : %d\n", total_cnt);
}

int main() {
	menu();
	int num;
	scanf("%d", &num);

	while (num != 0) {
		printf("배열 크기를 입력하세요 : ");
		scanf("%d", &size);
		int* arr = (int*)malloc(sizeof(int) * size);
		for (int i = 0; i < size; i++) arr[i] = rand() % 100 + 1;

		switch (num) {
		case 1:
			selection_sort(arr);
			break;
		case 2:
			insertion_sort(arr);
			break;
		case 3:
			bubble_sort_bool(arr);
			break;
		case 4:
			bubble_sort(arr);
			break;
		default:
			printf("다시 입력해주세요!\n");
		}

		free(arr);
		menu();
		scanf("%d", &num);
	}

	return 0;
}