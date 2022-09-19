/*
- C언어 소스코드 파일에 각 예약어들이 얼마나 자주 등장하는지를 계산하는 프로그램을
이진탐색트리를 사용하여 구현하시오.
(1) 입력 : 자신이 작성한 임의의 c 프로그램 소스파일을 "bst_in.txt"라고 파일명을 지정한다.
	출력 : 출현한 예약어들과 출현빈도(예약어들의 오름차순) 화면 출력한다 (o).
		   또는 출력파일을 "bst_out.txt"로 생성한다. (o)
(2) 이진탐색트리 각 노드의 데이터 필드는 예약어(문자열)과 출현빈도(정수)이다. (o)
(3) c언어의 예약어들 중에서 다음 예약어들의 출현 빈도를 계산한다. (o)
	{"break", "case","do","else","for","if","int","return","struct","switch","while"}
(4) 입력파일을 차례로 읽으면서,
	- 처음 출현하는 예약어는 이진탐색트리에 삽입하고 출현빈도를 1로 초기화한다. (o)
	- 검색 중 이미 트리에 존재하는 예약어는 출현빈도를 1만큼 증가시킨다. (o)
(5) 완성된 이진탐색트리를 중위순회하면서 예약어들과 출현빈도를 함께 출력한다. (o)
(6) 가장 자주 출현한 예약어(빈도수 최대값)가 무엇인지 찾아서 출력한다. (o)
(7) 이진트리에 존재하는 예약어들을 임의 순서로 하나씩 삭제하면서
	중간 결과를 중위순회 결과로 화면에서 확인한다. (공백트리가 될 때까지) */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct TreeNode {
	char res[1000];
	int number;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* r = NULL;
TreeNode* maximum;
int max;

void display(TreeNode* t) { // 중위 순회 출력
	if (t != NULL) {
		display(t->left);
		printf("[%s : %d]\n", t->res, t->number);
		display(t->right);
	}
}

int compare(char* str, TreeNode* e2) {
	return strcmp(str, e2->res);
}

// 검색 함수
TreeNode* search(TreeNode* node, char* key) {
	if (node == NULL) return NULL;

	if (strcmp(key, node->res) == 0) {
		return node;
	}
	else if (strcmp(key, node->res) < 0)
		return search(node->left, key);
	else
		return search(node->right, key);
}

// 노드 생성 함수
TreeNode* new_node(char* item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(temp->res, item);
	temp->number = 1;
	temp->left = temp->right = NULL;
	return temp;
}

// 삽입하는 함수
TreeNode* insert_node(TreeNode* node, char* key) {
	//트리가 공백이면 새로운 노드를 반환한다.
	if (node == NULL) return new_node(key);


	// 그렇지 않으면 순환적으로 트리를 내려간다.
	if (compare(key, node) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node) > 0)
		node->right = insert_node(node->right, key);

	// 변경된 루트 포인터를 반환한다.
	return node;
}

// 오른쪽 서브 트리의 최소값
TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}

// 노드 삭제 함수
TreeNode* delete_node(TreeNode* root, char* key) {
	if (root == NULL) return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있음
	if (compare(key, root) < 0)
		root->left = delete_node(root->left, key);

	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있음
	else if (compare(key, root) > 0)
		root->right = delete_node(root->right, key);

	else {
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}

		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// 세 번째의 경우
		TreeNode* temp = min_value_node(root->right);

		// 중위 순환시 후계 노드를 복사한다.
		strcpy(root->res, temp->res);
		root->number = temp->number;

		// 중위 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->res);
	}

	return root;
}

// 최댓값 찾는 함수
TreeNode* find_max(TreeNode* node) {
	if (node != NULL) {
		find_max(node->left);
		find_max(node->right);

		if (max < node->number) {
			max = node->number;
			maximum = node;
		}
	}

	return maximum;
}

void inorder_fprintf(TreeNode* p, FILE* fp2) {
	if (p != NULL) {
		inorder_fprintf(p->left, fp2);
		fprintf(fp2, "[%s : %d]\n", p->res, p->number);
		inorder_fprintf(p->right, fp2);
	}
}

void menu() {
	printf("==========[메뉴]==========\n");
	printf("0. 종료\n");
	printf("1. 중위순회로 출력\n");
	printf("2. 삭제할 예약어 입력\n");
	printf("3. 최대 빈도 예약어\n");
	printf("==========================\n");
	printf("입력:");
}

int main(void) {
	int num = 0;
	FILE* fp1 = fopen("bst_in.txt", "r");
	FILE* fp2 = fopen("bst_out.txt", "w");

	if (fp1 == NULL) {
		printf("파일이 존재하지 않습니다.\n");
		return 0;
	}

	char* p = (char*)malloc(sizeof(char) * 1000);
	char* str[] = { "break", "case","do","else","for","if","int","return","struct","switch","while" };

	while (!feof(fp1)) { //EOF가 나올때까지 계속 돌린다.
		fscanf(fp1, "%s ", p); // 공백 단위로 받아옴
		for (int i = 0; i < 11; i++) {
			if (strstr(p, str[i])) {
				if (search(r, str[i]) == NULL) { // 찾는 단어가 없을 때
					r = insert_node(r, str[i]);
					break; // 다음 단어 받아오기
				}
				else if (search(r, str[i]) != NULL) {
					search(r, str[i])->number++;
					break;
				}
			}
		}
	}

	inorder_fprintf(r, fp2); // 중위순회로 파일에 입력

	char* s = (char*)malloc(sizeof(char) * 1000);
	fclose(fp2);
	while (1) {
		menu();
		scanf("%d", &num);
		if (num == 0) return 0;

		switch (num) {
		case 1:
			display(r); //중위순회로 출력
			break;

		case 2:
			printf("삭제할 단어를 입력해주세요: ");
			scanf("%s", s);
			delete_node(r, s);
			break;

		case 3:
			maximum = r;
			max = r->number;
			printf("\n빈도 최대 값 = [%s : %d]\n", find_max(r)->res, find_max(r)->number);
			break;

		default:
			printf("다시 입력해주세요\n");
			break;
		}
	}

	free(p);
	fclose(fp1);

	return 0;
}