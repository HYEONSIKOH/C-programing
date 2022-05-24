/*
1. ����Ʈ���� ������ȸ ������ȸ ������ȸ ������ �����͸� ����ϴ� �Լ��� �ۼ�, ,
2. ����Ʈ���� ��� ������ ������ ���� 1�� ������Ű�� �Լ��� �ۼ�
3. ����Ʈ���� ������ ������ ���� �� �ִ밪�� ���� ��带 ã�� �����͸� ��ȯ�ϴ� �Լ��� �ۼ�
4. �ڽ��� �ϳ��� �ִ� ����� ����
5. �� ���� ����Ʈ���� �������� �Ǵ��ϴ� �Լ� 0 �Ǵ� 1 ��ȯ
6. ����Ʈ���� �����Ͽ� ������ Ʈ���� ��ȯ�ϴ� �Լ�

   - ������ ���� �����Ǵ� ������ ���� �����͸� ���� Ʈ��
   - �� 5�� �Լ��� �̿��Ͽ� ������ Ʈ���� ������ Ʈ���� �������� Ȯ��*/
#include <stdio.h>
#include <stdlib.h>

//Ʈ����� ����
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

// ù��° ����Ʈ��
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* nroot = &n6;

// �ι�° ����Ʈ��
TreeNode e1 = { 3,NULL,NULL };
TreeNode e2 = { 8,NULL,NULL };
TreeNode e3 = { 6,&e1,&e2 };
TreeNode e4 = { 9,NULL,NULL };
TreeNode e5 = { 1,&e4,NULL };
TreeNode e6 = { 4,&e3,&e5 };
TreeNode e7 = { 7,NULL,NULL };
TreeNode t8 = { 3,NULL,NULL }; // �ӽ÷� �������
TreeNode e8 = { 2,&t8,NULL };
TreeNode e9 = { 10,&e7,&e8 };
TreeNode e10 = { 5,&e6,&e9 };
TreeNode* eroot = &e10;

// ����° ����Ʈ��
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

//������ȸ
void pre(TreeNode* t) {
	if (t != NULL) {
		printf("[%d] ", t->data);
		pre(t->left);
		pre(t->right);
	}
}

//������ȸ
void inorder(TreeNode* t) {
	if (t != NULL) {
		inorder(t->left);
		printf("[%d] ", t->data);
		inorder(t->right);
	}
}

//������ȸ
void post(TreeNode* t) {
	if (t != NULL) {
		post(t->left);
		post(t->right);
		printf("[%d] ", t->data);
	}
}

// ��� ��� 1�� ����
void increase_node(TreeNode* t) {
	if (t != NULL) {
		increase_node(t->left);
		increase_node(t->right);
		t->data++;
	}
}

// �ִ� ��� ã��
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

// ��尡 �Ѱ�
int one_node(TreeNode* t) {
	if (t != NULL) {
		one_node(t->left);
		one_node(t->right);

		if ((t->right == NULL && t->left != NULL) || (t->right != NULL && t->left == NULL))
			count++;
	}

	return count;
}

// �ΰ��� Ʈ���� ������ �ƴ���
int equal_tree(TreeNode* n,TreeNode * e) {
	if (n != NULL && e != NULL) {
		if (n->data != e->data) return 0;
		if (equal_tree(n->left, e->left) && equal_tree(n->right, e->right)) return 1;
		else return 0;
	}
	else if (n == NULL && e == NULL) return 1;
	else return 0;
}

// Ʈ�� ����
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
	printf("\n=====================[�޴�]=====================\n");
	printf("0. ����\n");
	printf("1. ����, ����, ���� ��ȸ ���\n");
	printf("2. ��� ��� 1�� ����\n");
	printf("3. �ִ� ��� ã��\n");
	printf("4. �ڽ��� �ϳ��� �ִ� ����� ����\n");
	printf("5. �� ���� ����Ʈ���� ������ (T / F) \n");
	printf("6. ����Ʈ�� ����\n");
	printf("7. ������ Ʈ�� ���\n");
	printf("================================================\n");
	printf("�Է�: ");
}

void tree_menu() {
	printf("\n=====================[Ʈ�� ����]=====================\n");
	printf("1. ù��° Ʈ��\n");
	printf("2. �ι�° Ʈ��\n");
	printf("3. ����° Ʈ��\n");
	printf("=====================================================\n");
	printf("�Է�: ");
}

void equal_tree_menu() {
	printf("\n=====================[Ʈ�� ����]=====================\n");
	printf("1. ù��° �ι�°\n");
	printf("2. �ι�° ����°\n");
	printf("3. ����° ù��°\n");
	printf("=====================================================\n");
	printf("�Է�: ");
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
				printf("����: ");
				pre(nroot);
				printf("\n");

				printf("����: ");
				inorder(nroot);
				printf("\n");

				printf("����: ");
				post(nroot);
				printf("\n");
				
				break;

			case 2:
				printf("����: ");
				pre(eroot);
				printf("\n");

				printf("����: ");
				inorder(eroot);
				printf("\n");

				printf("����: ");
				post(eroot);
				printf("\n");

				break;

			case 3:
				printf("����: ");
				pre(kroot);
				printf("\n");

				printf("����: ");
				inorder(kroot);
				printf("\n");

				printf("����: ");
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
				printf("�ִ� ���: %d\n", max_node(nroot)->data);
				break;

			case 2:
				MAX = eroot->data;
				printf("�ִ� ���: %d\n", max_node(eroot)->data);
				break;

			case 3:
				MAX = kroot->data;
				printf("�ִ� ���: %d\n", max_node(kroot)->data);
				break;
			}
			break;

		case 4:
			tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				printf("�ڽ��� �Ѱ��� ���� [%d]�� �Դϴ�.\n", one_node(nroot));
				break;

			case 2:
				printf("�ڽ��� �Ѱ��� ���� [%d]�� �Դϴ�.\n", one_node(eroot));
				break;

			case 3:
				printf("�ڽ��� �Ѱ��� ���� [%d]�� �Դϴ�.\n", one_node(kroot));
				break;
			}
			count = 0;
			break;

		case 5:
			equal_tree_menu();
			scanf("%d", &tree);
			switch (tree) {
			case 1:
				if (equal_tree(nroot, eroot) == 1) printf("���� Ʈ���Դϴ�.\n");
				else
					printf("���� Ʈ���� �ƴմϴ�.");
				break;

			case 2:
				if (equal_tree(eroot, kroot) == 1) printf("���� Ʈ���Դϴ�.\n");
				else
					printf("���� Ʈ���� �ƴմϴ�.");
				break;

			case 3:
				if (equal_tree(kroot, nroot) == 1) printf("���� Ʈ���Դϴ�.\n");
				else
					printf("���� Ʈ���� �ƴմϴ�.");
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
			printf("������ Ʈ�� ����: ");
			pre(temp);
			printf("\n");

			printf("������ Ʈ�� ����: ");
			inorder(temp);
			printf("\n");

			printf("������ Ʈ�� ����: ");
			post(temp);
			printf("\n");
			break;

		default:
			printf("�ǹٸ��� �ʴ� �����Դϴ�.\n");
			break;
		}
	}

	free(temp);
	return 0;
}


