/*
1. ���� ������ n �� ���� ���� �������� ������� �����Ͻÿ�. 
(1) �� �ܰ迡�� �ּҰ��� ���ϰ�, �� ���ڸ��� �̵��ϴ� ����� ����Ͻÿ�.
(2) �� �ܰ踶���� ��������� Ȯ���� �� �ֵ��� ������� ���̽ÿ�.
(3) �� �ܰ迡�� ��ȸ��, ��ü ������ ��ȸ���� ����Ͻÿ�.

2. ���� ������ n �� ���� ���� �������� ������� �����Ͻÿ�. 
�� �ܰ踶�� �Ʒ� ���ÿ� ������ �ܰ躰 �߰� ����� ���̵�, 
 (1) �� Ƚ�� (2) �κ� ���� �Ϸ�� ���� (3) ��ü �� Ƚ���� ����Ͻÿ�.

3. ���� ������ n �� ���� ���� �������� ������� �����Ͻÿ�.
���� ��ȯ�� �ѹ��� �Ͼ�� ���� ���� �Ǵ��Ͽ� �����ϴ� ����� ������ �� �ֵ��� �Ͻÿ�.
�� �ܰ� ���� ���� ���� ���¸� Ȯ���� �� �ֵ��� ����Ͻÿ�.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int size; // �迭 ����� ��������

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
	printf("=================== [�޴�] ===================\n");
	printf("1. ��������\n");
	printf("2. ��������\n");
	printf("3. �������� (T/F)\n");
	printf("4. �������� (Nomal)\n");
	printf("0. ����\n");
	printf("==============================================\n");
	printf("�Է� : ");
}

// =================================================== ���� 1�� �Լ�
void selection_sort(int* arr) {
	int min, min_index;
	int cnt=0, total_cnt=0;
	printf("���� �� �迭 : ");
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
		printf("%d) ��Ƚ�� : %d\n", i + 1, cnt);

		for (int k = 0; k < i; k++) printf("%d ", arr[k]);
		printf("[%d] ", arr[i]);
		for (int k = i+1; k<size; k++) printf("%d ", arr[k]);
		printf("\n\n");

		cnt = 0;
	}

	printf("\n\n�� �� Ƚ�� : %d\n", total_cnt);
	printf("���ĵ� �迭 : ");
	show_array(arr);
}

// =================================================== ���� 2�� �Լ�
void insertion_sort(int* arr) {
	int j, temp;
	int cnt = 0, total_cnt = 0;
	printf("���� �� �迭 : ");
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
		printf("%d�ܰ�) ", i);
		printf("| �� Ƚ�� : %d | ", cnt);

		for (int k = 0; k < i; k++) printf("\033[0;31m%d\033[0m ", arr[k]);
		for (int k = i; k < size; k++) printf("%d ", arr[k]);
		printf("\n\n");

		cnt = 0;
	}
	printf("\n�� �� Ƚ�� : %d\n", total_cnt);
	printf("���ĵ� �迭 : ");
	show_array(arr);
}

// =================================================== ���� 3�� �Լ�
void bubble_sort_bool(int* arr) {
	int bool, cnt = 0, total_cnt = 0;
	for(int i = 0; i<size-1; i++){
		bool = 1; // True or False ����

		printf("%d�ܰ�)\n", i + 1);
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
		printf("��Ƚ�� : %d\n",cnt);
		printf("==================================================\n");
		cnt = 0;

		if (bool) {
			printf("\n�� �� Ƚ�� : %d\n", total_cnt);
			printf("���ĵ� �迭 : ");
			show_array(arr);
			return;
		}
	
	}
	printf("\n\n�� �� Ƚ�� : %d\n", total_cnt);
}

void bubble_sort(int* arr) {
	int cnt = 0, total_cnt = 0;
	for (int i = 0; i < size - 1; i++) {
		printf("%d�ܰ�)\n", i + 1);
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
		printf("��Ƚ�� : %d\n", cnt);
		printf("==================================================\n");
		cnt = 0;
	}
	printf("\n\n�� �� Ƚ�� : %d\n", total_cnt);
}

int main() {
	menu();
	int num;
	scanf("%d", &num);

	while (num != 0) {
		printf("�迭 ũ�⸦ �Է��ϼ��� : ");
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
			printf("�ٽ� �Է����ּ���!\n");
		}

		free(arr);
		menu();
		scanf("%d", &num);
	}

	return 0;
}