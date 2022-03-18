#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//���ڿ����� ���ĺ� �빮��, �ҹ���, ����, Ư������(!, ? , *, #, $)�� ��� ���ԵǾ� �ִ���, 
//�� ���̰� 10�� �̻����� �Ǵ��ϴ� �Լ� (�� ���� ���ڴ� ���� �� �� ����)

int Password(char* s) {
	int sc = 0;
	int nc = 0;
	int Ac = 0;
	int ac = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '!' || s[i] == '?' || s[i] == '*' || s[i] == '#' || s[i] == '$') // Ư����ȣ
			sc++;
		else if (s[i] >= '0' && s[i] <= '9') // ����
			nc++;
		else if (s[i] >= 'A' && s[i] <= 'Z') // �빮��
			Ac++;
		else if (s[i] >= 'a' && s[i] <= 'z') // �ҹ���
			ac++;
	}
	int sum = sc + nc + Ac + ac; // 10�� �̻����� �̸����� ���ϴ� ��

	if (sc != 0 && nc != 0 && Ac != 0 && ac != 0 && sum >= 10)
		printf("�����Դϴ�.");

	if (sc == 0)
		printf("\nƯ����ȣ�� �����ϴ�.");

	if (nc == 0)
		printf("\n���ڰ� �����ϴ�.");

	if (Ac == 0)
		printf("\n�빮�ڰ� �����ϴ�.");

	if (ac == 0)
		printf("\n�ҹ��ڰ� �����ϴ�.");

	if (sum < 10)
		printf("\n���̰� 10�� �̸��Դϴ�.");
}




//����ü�� ���ǵ� ���Ҽ� n���� �迭�� �����ϰ�, ��ü���� ���ϴ� ��ȯȣ�� �Լ�

typedef struct { // a+bi ���Ҽ� ����ü
	int a; //�Ǽ�
	int b; //���
}complex;


int add_a(complex* arr, int n) { // �Ǽ� a�� ���� ���ϴ� �Լ�
	if (n < 0)
		return 0;
	else
		return arr[n].a + add_a(arr, n - 1);
}
int add_b(complex* arr, int n) { // ��� bi�� ���� ���ϴ� �Լ�
	if (n < 0)
		return 0;
	else
		return arr[n].b + add_b(arr, n - 1);
}





// ���ڿ� ���� ���ϱ�

int len(char* str) {
	if (*str == 0)
		return 0;
	else
		return 1 + len(str + 1); // ��ȯ�Լ�
}





// �����˻�(binary search)�Լ� ��ȯȣ�� ������� �ۼ�

int bs(int* arr, int num, int start, int end) {
	int n = (start + end) / 2; // �̵� ��

	if (start > end) return printf("\n#########No result#########"); // ������ ã�Ҵµ�, ���� ���� ���

	printf("\n���� ��:%d �� ��:%d �߰� ��:%d", arr[start], arr[end], arr[n]);

	if (num < arr[n]) return bs(arr, num, start, n - 1); // �̵� ���� ã�� ������ ū ���


	else if (num > arr[n]) return bs(arr, num, n + 1, end); // �̵� ���� ã�� ������ ���� ���


	else if (num == arr[n]) return printf("\n%d�� %d��° �Դϴ�.", num, n + 1); // ������ ã�� ���

}
int Sort(int* arr, int num) { // �������� ����
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
		printf("0 : ���� \n1 : �н����� \n2 : ���Ҽ� �� (��ȯȣ��)  \n3 : ���ڿ� ���� ���ϱ� (��ȯȣ��) \n4 : �����˻�(binary search)�Լ� (��ȯȣ��)\n");
		printf("---------------------------------------------------\n");
		int a;
		scanf("%d", &a);
		getchar();

		if (a == 0) {
			printf("�����մϴ�...");
			return 0;
		}

		else if (a > 4 || a < 0) {
			printf("-----------------------------------\n");
			printf("0 ~ 4 ������ �Է����ּ���.\n");
			printf("-----------------------------------\n");
			int a;
			scanf("%d", &a);
			getchar();
		}

		else {
			switch (a) {
			case 1: {
				printf("������ �Է��ϼ���:");
				char str[100];
				gets(str);
				Password(str);
				break;
			}

			case 2: {
				complex arr[] = { {1,1},{1,2},{2,3},{4,1} };
				printf("%d+%di �Դϴ�.", add_a(arr, 3), add_b(arr, 3));
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
