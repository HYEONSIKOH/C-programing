/*
1. 임의 순서로 배열에 저장된 열 개의 정수값 중에서 최대값괴 최소값을 찾는 프로그램을
하나의 반복문장으로 작성하시오.

2. 키보드로 입력된 문자열의 길이를 구하는 프로그램을 (1) 반복문장으로 (2)순환호출로 작
성하시오. (단, strlen()를 사용하지 않는다.)

3. 십진수 n을 b진수로 변환하는 프로그램을 반복 문장으로 작성하시오. 
n과 b 값을 키보드 입력하되, 2진수부터 16진수까지 자유롭게 선택할 수 있도록 한다. 
 예를 들어, n=17이고 b=3인 경우, 출력은 122(3) 이다.

4. 이진검색트리에 임의의 정수 10개를 삽입하고, (1) 완성된 트리의 높이를 구하고 (2) 트리
를 중위순회한 순서를 말하시오.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ================= 1번 함수 =================
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

// ================= 2번 함수 =================
int R_len(char str[]) { // 반복문
	int count = 0;
	for (int i = 0; str[i] != NULL; i++) count++;

	return count;
}

int r_len(char *str) { // 순환문
	if (*str == NULL) return 0;
	else return 1 + r_len(str + 1);
}

// ================= 3번 함수 =================
char function(int num,int b) {
	char arr[100];
	int i = 0;

	while (num >= b) {
		arr[i] = num % b; // 나머지
		num /= b; // 몫
		i++; // 인덱스
	}
	arr[i] = num;

	for (; i >= 0; i--) {
		if (arr[i] < 10) printf("%c", arr[i] + '0');
		else printf("%c", arr[i] + 55);
	}
	printf("(%d)\n", b);
}

// ================= 4번 함수 =================
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

void display_ord(TreeNode* t) { // 중위 순회 출력
	if (t != NULL) {
		display_ord(t->left);
		printf("[%d] ", t->key);
		display_ord(t->right);
	}
}

void menu() {
	printf("=================== [메뉴] ===================\n");
	printf("1. 최대 최소 구하기\n");
	printf("2. 문자열 길이 구하기\n");
	printf("3. 십진수를 (b)진수로 구하기\n");
	printf("4. 이진검색트리 사용하기\n");
	printf("0. 종료\n");
	printf("==============================================\n");
	printf("입력 : ");
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
			printf("배열: ");
			for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
			printf("\n");
			Max_Min(arr);
			printf("\n최댓값: %d || 최솟값: %d\n", max, min);
			break;

		case 2:
			printf("\n1. 반복문 2. 순환문 \n");
			printf("입력: ");
			scanf("%d", &n);

			printf("문자열을 입력해주세요: ");
			scanf("%s",str);

			switch (n) {
			case 1:
				printf("문자열 길이: %d\n", R_len(str));
				break;

			case 2:
				printf("문자열 길이: %d\n", r_len(str,count));
				count++;
				break;
			}
			break;

		case 3:
			printf("10진수를 입력하고, 몇진수로 변환할지 입력하시오: ");
			scanf("%d %d", &a, &b);
			function(a, b);
			break;

		case 4:
			r = NULL;
			printf("10개의 정수를 입력하세요: ");
			for (int i = 0; i < 10; i++) {
				scanf("%d", &N);
				r = insert_node(r, N);
			}
			printf("높이 : %d\n", high(r));
			printf("중위순회 : ");
			display_ord(r);
			printf("\n");
			printf("\n");
			break;
		}
	}

	return 0;
}