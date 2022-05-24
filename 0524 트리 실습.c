/*
1. 이진트리의 중위순회 전위순회 후위순회 순서로 데이터를 출력하는 함수를 작성, ,
2. 이진트리의 모든 노드들의 데이터 값을 1씩 증가시키는 함수를 작성
3. 이진트리의 노드들의 데이터 값들 중 최대값을 갖는 노드를 찾아 포인터를 반환하는 함수를 작성
4. 자식이 하나만 있는 노드의 개수
5. 두 개의 이진트리가 동일한지 판단하는 함수 0 또는 1 반환
6. 이진트리를 복사하여 동일한 트리를 반환하는 함수

   - 구조가 같고 대응되는 노드들이 같은 데이터를 갖는 트리
   - 위 5의 함수를 이용하여 복사한 트리가 원래의 트리와 동일한지 확인*/
#include <stdio.h>
#include <stdlib.h>

//트리노드 정의
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

// 첫번째 이진트리
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* nroot = &n6;

// 두번째 이진트리
TreeNode e1 = { 3,NULL,NULL };
TreeNode e2 = { 8,NULL,NULL };
TreeNode e3 = { 6,&e1,&e2 };
TreeNode e4 = { 9,NULL,NULL };
TreeNode e5 = { 1,&e4,NULL };
TreeNode e6 = { 4,&e3,&e5 };
TreeNode e7 = { 7,NULL,NULL };
TreeNode t8 = { 3,NULL,NULL }; // 임시로 집어넣음
TreeNode e8 = { 2,&t8,NULL };
TreeNode e9 = { 10,&e7,&e8 };
TreeNode e10 = { 5,&e6,&e9 };
TreeNode* eroot = &e10;

// 세번째 이진트리
TreeNode k1 = { 1, NULL, NULL };
TreeNode k2 = { 4, &k1, NULL };
TreeNode k3 = { 16, NULL, NULL };
TreeNode k4 = { 25, NULL, NULL };
TreeNode k5 = { 20, &k3, &k4 };
TreeNode k6 = { 15, &k2, &k5 };
TreeNode* kroot = &k6;

TreeNode *max;

int count = 0;
int MAX;

//전위순회
void pre(TreeNode* t) {
	if (t != NULL) {
		printf("[%d] ", t->data);
		pre(t->left);
		pre(t->right);
	}
}

//중위순회
void inorder(TreeNode* t) {
	if (t != NULL) {
		inorder(t->left);
		printf("[%d] ", t->data);
		inorder(t->right);
	}
}

//후위순회
void post(TreeNode* t) {
	if (t != NULL) {
		post(t->left);
		post(t->right);
		printf("[%d] ", t->data);
	}
}

// 모든 노드 1씩 증가
void increase_node(TreeNode* t) {
	if (t != NULL) {
		increase_node(t->left);
		increase_node(t->right);
		t->data++;
	}
}

// 최댓값 노드 찾기
TreeNode* max_node(TreeNode* root) {
	if (root != NULL) {
		max_node(root->left);
		max_node(root->right);

		if (MAX < root->data) {
			MAX = root->data;
			max = root;
		}
	}

	return max;
}

// 노드가 한개
int one_node(TreeNode* t) {
	if (t != NULL) {
		one_node(t->left);
		one_node(t->right);

		if ((t->right == NULL && t->left != NULL) || (t->right != NULL && t->left == NULL))
			count++;
	}

	return count;
}

// 두개의 트리가 같은지 아닌지
int equal_tree(TreeNode* n,TreeNode * e) {
	if (n != NULL && e != NULL) {
		if (n->data != e->data) return 0;
		if (equal_tree(n->left, e->left) && equal_tree(n->right, e->right)) return 1;
		else return 0;
	}
	else if (n == NULL && e == NULL) return 1;
	else return 0;
}

// 트리 복사
TreeNode* copy_tree(TreeNode* n) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	
	if (n != NULL) {
		temp->left = copy_tree(n->left);
		temp->right = copy_tree(n->right);
		temp->data = n->data;
	}
	else return NULL;

	return temp;
}

void main_menu() {
	printf("\n=====================[메뉴]=====================\n");
	printf("0. 종료\n");
	printf("1. 중위, 전위, 후위 순회 출력\n");
	printf("2. 모든 노드 1씩 증가\n");
	printf("3. 최댓값 노드 찾기\n");
	printf("4. 자식이 하나만 있는 노드의 개수\n");
	printf("5. 두 개의 이진트리가 같은지 (T / F) \n");
	printf("6. 이진트리 복사\n");
	printf("7. 복사한 트리 출력\n");
	printf("================================================\n");
	printf("입력: ");
}

void tree_menu() {
	printf("\n=====================[트리 선택]=====================\n");
	printf("1. 첫번째 트리\n");
	printf("2. 두번째 트리\n");
	printf("3. 세번째 트리\n");
	printf("=====================================================\n");
	printf("입력: ");
}

void equal_tree_menu() {
	printf("\n=====================[트리 선택]=====================\n");
	printf("1. 첫번째 두번째\n");
	printf("2. 두번째 세번째\n");
	printf("3. 세번째 첫번째\n");
	printf("=====================================================\n");
	printf("입력: ");
}

int main(void) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	int num = 0;
	int tree;
	while (1) {
		main_menu();
		scanf("%d", &num);
		if (num == 0) return 0;
		printf("\n");

		switch (num) {
		case 1:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				printf("전위: ");
				pre(nroot);
				printf("\n");

				printf("중위: ");
				inorder(nroot);
				printf("\n");

				printf("후위: ");
				post(nroot);
				printf("\n");
				
				break;

			case 2:
				printf("전위: ");
				pre(eroot);
				printf("\n");

				printf("중위: ");
				inorder(eroot);
				printf("\n");

				printf("후위: ");
				post(eroot);
				printf("\n");

				break;

			case 3:
				printf("전위: ");
				pre(kroot);
				printf("\n");

				printf("중위: ");
				inorder(kroot);
				printf("\n");

				printf("후위: ");
				post(kroot);
				printf("\n");

				break;
			}
			break;

		case 2:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				increase_node(nroot);

				break;

			case 2:
				increase_node(eroot);

				break;

			case 3:
				increase_node(kroot);

				break;
			}
			break;

		case 3:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				MAX = nroot->data;
				printf("최댓값 노드: %d\n", max_node(nroot)->data);
				break;

			case 2:
				MAX = eroot->data;
				printf("최댓값 노드: %d\n", max_node(eroot)->data);
				break;

			case 3:
				MAX = kroot->data;
				printf("최댓값 노드: %d\n", max_node(kroot)->data);
				break;
			}
			break;

		case 4:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				printf("자식이 한개인 노드는 [%d]개 입니다.\n", one_node(nroot));
				break;

			case 2:
				printf("자식이 한개인 노드는 [%d]개 입니다.\n", one_node(eroot));
				break;

			case 3:
				printf("자식이 한개인 노드는 [%d]개 입니다.\n", one_node(kroot));
				break;
			}
			count = 0;
			break;

		case 5:
			equal_tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				if (equal_tree(nroot, eroot) == 1) printf("같은 트리입니다.\n");
				else
					printf("같은 트리가 아닙니다.");
				break;

			case 2:
				if (equal_tree(eroot, kroot) == 1) printf("같은 트리입니다.\n");
				else
					printf("같은 트리가 아닙니다.");
				break;

			case 3:
				if (equal_tree(kroot, nroot) == 1) printf("같은 트리입니다.\n");
				else
					printf("같은 트리가 아닙니다.");
				break;
			}
			break;

		case 6:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				temp = copy_tree(nroot);
				break;

			case 2:
				temp = copy_tree(eroot);
				break;

			case 3:
				temp = copy_tree(kroot);
				break;
			}
			count = 0;
			break;

		case 7:
			printf("복사한 트리 전위: ");
			pre(temp);
			printf("\n");

			printf("복사한 트리 중위: ");
			inorder(temp);
			printf("\n");

			printf("복사한 트리 후위: ");
			post(temp);
			printf("\n");
			break;

		default:
			printf("옳바르지 않는 숫자입니다.\n");
			break;
		}
	}

	free(temp);
	return 0;
}


