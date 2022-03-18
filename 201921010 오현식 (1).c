#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// <���� 1��>
//���ڿ��� �Էµ� �������� �������� ��ȯ�ϴ� �Լ� (���ڿ��� Ű���� �Է�) 
//���� ���, ���ڿ� "234" �� ������ 234��, "-234" �� -234�� ��ȯ�ȴ�.

int len(char* str) { // ���ڿ� ���� ���ϱ�
	int count = 0;
	for (int i = 0; str[i] != 0; i++)
		count++;

	return count;
}

int change_num(char* str) { // ���ڿ��� ������ ��ȯ
	int result = 0;
	for (int i = 0; i < len(str); i++) {

		if (str[0] == '-' && i == 0) // ������ ���, �� �տ� '-'��ȣ�� �����ϱ� ���� ó������ i++ ����
			i++;

		int num = 1;

		for (int a = i; a < len(str) - 1; a++) // num �������ٰ� 1000�� �ڸ��� 1000, 100�� �ڸ��� 100 
			num *= 10;

		result += ((str[i] - 48) * num); //���ڿ��� �ƽ�Ű�ڵ� ���� 48�� �� ������, num ���� ����
	}
	return result;
}

//<���� 2��> 
//��ǥ(x, y)�� ǥ���ϴ� ����ü �����ϰ�, 5�� ��ǥ�� ����ü �迭�� �����ϰ�,
//�迭�� ����� 5�� ��ǥ �� ������������ ���� �� ��ǥ ���ϱ�

typedef struct { // pos��� (x,y) ����ü ����
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

// <���� 3��>
//8�ڸ� ������� (���� ���, ��20200308��) �� ���� �迭�� �����ϰ�, 
//�� �� m(1 <= m <= 12) �� ���� �� ������ ����ϱ�(m�� Ű���� �Է�)

int change_month(char* str) { //4��°,5��° ���ڸ� 4��°�� 10�� �ڸ� , 5��°�� ���� �ڸ��� ���ϰ� ���������� ��
	int month = ((int)str[4] - 48) * 10 + ((int)str[5] - 48);
	return month;
}

// <����4��>
//���� m���� n���� ���� ���ϱ� (m<=n �̰� m�� n�� Ű���� �Է�) 
//(1) �ݺ����� �̿��ϱ�(for ���� �Ǵ� while ����)
//(2) ��ȯȣ�� �̿��ϱ�

int sum(int m, int n) { // for���� �̿��� �ݺ�����
	int num = 0;
	for (; m < n + 1; m++)
		num += m;

	return num;
}

int rotaiton(int m, int n) { // ��ȯȣ�� �̿�
	if (m > n)
		return 0;
	else
		m = rotaiton(m + 1, n);

	return m;
}


int main(void) {
	while (1) {
		printf("---------------------------------------------------\n");
		printf("0 : ���� \n1 : ���ڿ� ���� ��ȯ \n2 : ���� �� ��ǥ �� ���ϱ� \n3 : ������� ����ִ��� ���ϱ� \n4 : M���� N������ �� ���ϱ�\n");
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
				char str[100];
				printf("-----------------------------------\n");
				printf("���ڿ��� ���ڷθ� �Է����ּ���: ");
				gets(str);

				if (str[0] == '-') { //������ ���, 0���� ������� ����
					printf("-----------------------------------\n");
					printf("int������ ��ȯ : %d \n", (0 - change_num(str)));
				}
				else { //����� ��� �״�� ���
					printf("-----------------------------------\n");
					printf("int������ ��ȯ : %d \n", change_num(str));
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
				printf("Month�� �Է����ּ���:");
				scanf("%d", &m);
				while (m < 1 || m>12) {
					printf("-----------------------------------\n");
					printf("1���� 12������ �Է����ּ���:");
					scanf("%d", &m);
				}

				int count = 0;

				for (int i = 0; i < 9; i++) {
					if (m == change_month(bir[i]))
						count++;
				}


				printf("%d���� %d�� �Դϴ�. \n", m, count);
				break;
			}



			case 4: {
				printf("1. �ݺ��� (for , while)\n2. ����Լ�\n");
				int c;
				scanf("%d", &c);
				switch (c) {
				case 1: {
					printf("-----------------------------------\n");
					printf("�� ���� ������ �Է����ּ���:");

					int m, n;
					scanf("%d %d", &m, &n);

					while (m > n) {
						printf("-----------------------------------\n");
						printf("���� ���� �� �۰� �Է����ּ���:");

						scanf("%d %d", &m, &n);
					}

					printf("�� : %d \n", sum(m, n));
					break;
				}
				case 2: {
					printf("-----------------------------------\n");
					printf("�� ���� ������ �Է����ּ���:");

					int m, n;
					scanf("%d %d", &m, &n);

					while (m > n) {
						printf("-----------------------------------\n");
						printf("���� ���� �� �۰� �Է����ּ���:");
						scanf("%d %d", &m, &n);
					}

					printf("�� : %d \n", sum(m, n));
					break;
				}
				}
			}

			}
		}
	}
}