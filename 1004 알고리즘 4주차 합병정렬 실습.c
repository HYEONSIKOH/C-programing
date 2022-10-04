/*
1. ���� ������ n �� ���� ���� ��ȯȣ���� �̿��Ͽ� ���������ϴ� ���α׷��� �ۼ��Ͻÿ�
(�����). �ܰ躰 ����� Ȯ���� �� �ֵ��� ����Ͻÿ�.
�� �ܰ迡�� ���յ� ���� [I, j]�� Ȯ���� �� �ֵ��� ����� �߰��Ͻÿ�.

2. ���� ������ n �� ���� ���� �ݺ������� �̿��Ͽ� ���������ϴ� ���α׷��� �ۼ��Ͻÿ�
(�����).
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* arr;
int size;

// =================== ��� �Լ� ===================
void print(int s, int e) {
	for (int i = 0; i < size; i++) {
		if (i >= s && i <= e) printf("\033[0;32m%d\033[0m ", arr[i]);
		else printf("%d ", arr[i]);
	}
	printf(" [S:%d E:%d]", s, e);
	printf("\n");
}

// =================== ���� �Լ� ===================
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

// =================== 1�� �Լ� ===================
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

// =================== 2�� �Լ� ===================
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

// =================== ��Ÿ �Լ� ===================
void menu() {
	printf("=================== [�޴�] ===================\n");
	printf("1. ��ȯ�� �պ�����\n");
	printf("2. �ݺ��� �պ�����\n");
	printf("0. ����\n");
	printf("==============================================\n");
	printf("�Է� : ");
}

void resize_arr() {
	printf("�迭 ũ�⸦ �Է����ּ��� : ");
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
			printf("�߸��� �����Դϴ�.\n");
		}
		free(arr);
		menu();
		scanf("%d", &num);
	}

	return 0;
}