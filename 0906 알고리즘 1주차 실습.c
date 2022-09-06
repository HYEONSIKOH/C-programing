/*
1. ���� ������ �迭�� ����� �� ���� ������ �߿��� �ִ밪�� �ּҰ��� ã�� ���α׷���
�ϳ��� �ݺ��������� �ۼ��Ͻÿ�.

2. Ű����� �Էµ� ���ڿ��� ���̸� ���ϴ� ���α׷��� (1) �ݺ��������� (2)��ȯȣ��� ��
���Ͻÿ�. (��, strlen()�� ������� �ʴ´�.)

3. ������ n�� b������ ��ȯ�ϴ� ���α׷��� �ݺ� �������� �ۼ��Ͻÿ�. 
n�� b ���� Ű���� �Է��ϵ�, 2�������� 16�������� �����Ӱ� ������ �� �ֵ��� �Ѵ�. 
 ���� ���, n=17�̰� b=3�� ���, ����� 122(3) �̴�.

4. �����˻�Ʈ���� ������ ���� 10���� �����ϰ�, (1) �ϼ��� Ʈ���� ���̸� ���ϰ� (2) Ʈ��
�� ������ȸ�� ������ ���Ͻÿ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ================= 1�� �Լ� =================
int max, min;
int arr[10] = { 3,9,8,6,1,2,4,10,25,109 };
void Max_Min(int a[]) {
	max = a[0];
	min = a[0];

	for (int i = 0; i < 10; i++) {
		if (max < a[i]) max = a[i];
		if (min > a[i]) min = a[i];
	}
}

// ================= 2�� �Լ� =================
int R_len(char str[]) { // �ݺ���
	int count = 0;
	for (int i = 0; str[i] != NULL; i++) count++;

	return count;
}

int r_len(char *str) { // ��ȯ��
	if (*str == NULL) return 0;
	else return 1 + r_len(str + 1);
}

// ================= 3�� �Լ� =================
char function(int num,int b) {
	char arr[100];
	int i = 0;

	while (num >= b) {
		arr[i] = num % b; // ������
		num /= b; // ��
		i++; // �ε���
	}
	arr[i] = num;

	for (; i >= 0; i--) {
		if (arr[i] < 10) printf("%c", arr[i] + '0');
		else printf("%c", arr[i] + 55);
	}
	printf("(%d)\n", b);
}

// ================= 4�� �Լ� =================
typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key) {
	if (node == NULL) return new_node(key);

	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	return node;
}

int high(TreeNode* node) {
	int height = 0;
	if (node != NULL) 
		height = 1 + max(high(node->left), high(node->right));

	return height;
}

void display_ord(TreeNode* t) { // ���� ��ȸ ���
	if (t != NULL) {
		display_ord(t->left);
		printf("[%d] ", t->key);
		display_ord(t->right);
	}
}

void menu() {
	printf("=================== [�޴�] ===================\n");
	printf("1. �ִ� �ּ� ���ϱ�\n");
	printf("2. ���ڿ� ���� ���ϱ�\n");
	printf("3. �������� (b)������ ���ϱ�\n");
	printf("4. �����˻�Ʈ�� ����ϱ�\n");
	printf("0. ����\n");
	printf("==============================================\n");
	printf("�Է� : ");
}

int main() {
	int num = -1, n = -1, count = 0 , a, b;
	char str[1000];
	int N = 0;

	TreeNode* r;

	while (num != 0) {
		menu(); scanf("%d", &num);
		switch (num) {
		case 1:
			printf("-----------------------------------------\n");
			printf("�迭: ");
			for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
			printf("\n");
			Max_Min(arr);
			printf("\n�ִ�: %d || �ּڰ�: %d\n", max, min);
			break;

		case 2:
			printf("\n1. �ݺ��� 2. ��ȯ�� \n");
			printf("�Է�: ");
			scanf("%d", &n);

			printf("���ڿ��� �Է����ּ���: ");
			scanf("%s",str);

			switch (n) {
			case 1:
				printf("���ڿ� ����: %d\n", R_len(str));
				break;

			case 2:
				printf("���ڿ� ����: %d\n", r_len(str,count));
				count++;
				break;
			}
			break;

		case 3:
			printf("10������ �Է��ϰ�, �������� ��ȯ���� �Է��Ͻÿ�: ");
			scanf("%d %d", &a, &b);
			function(a, b);
			break;

		case 4:
			r = NULL;
			printf("10���� ������ �Է��ϼ���: ");
			for (int i = 0; i < 10; i++) {
				scanf("%d", &N);
				r = insert_node(r, N);
			}
			printf("���� : %d\n", high(r));
			printf("������ȸ : ");
			display_ord(r);
			printf("\n");
			printf("\n");
			break;
		}
	}

	return 0;
}