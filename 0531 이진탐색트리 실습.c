/*
- C��� �ҽ��ڵ� ���Ͽ� �� �������� �󸶳� ���� �����ϴ����� ����ϴ� ���α׷���
����Ž��Ʈ���� ����Ͽ� �����Ͻÿ�.
(1) �Է� : �ڽ��� �ۼ��� ������ c ���α׷� �ҽ������� "bst_in.txt"��� ���ϸ��� �����Ѵ�.
	��� : ������ ������� ������(�������� ��������) ȭ�� ����Ѵ� (o).
		   �Ǵ� ��������� "bst_out.txt"�� �����Ѵ�. (o)
(2) ����Ž��Ʈ�� �� ����� ������ �ʵ�� �����(���ڿ�)�� ������(����)�̴�. (o)
(3) c����� ������ �߿��� ���� �������� ���� �󵵸� ����Ѵ�. (o)
	{"break", "case","do","else","for","if","int","return","struct","switch","while"}
(4) �Է������� ���ʷ� �����鼭,
	- ó�� �����ϴ� ������ ����Ž��Ʈ���� �����ϰ� �����󵵸� 1�� �ʱ�ȭ�Ѵ�. (o)
	- �˻� �� �̹� Ʈ���� �����ϴ� ������ �����󵵸� 1��ŭ ������Ų��. (o)
(5) �ϼ��� ����Ž��Ʈ���� ������ȸ�ϸ鼭 ������� �����󵵸� �Բ� ����Ѵ�. (o)
(6) ���� ���� ������ �����(�󵵼� �ִ밪)�� �������� ã�Ƽ� ����Ѵ�. (o)
(7) ����Ʈ���� �����ϴ� �������� ���� ������ �ϳ��� �����ϸ鼭
	�߰� ����� ������ȸ ����� ȭ�鿡�� Ȯ���Ѵ�. (����Ʈ���� �� ������) */

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

void display(TreeNode* t) { // ���� ��ȸ ���
	if (t != NULL) {
		display(t->left);
		printf("[%s : %d]\n", t->res, t->number);
		display(t->right);
	}
}

int compare(char* str, TreeNode* e2) {
	return strcmp(str, e2->res);
}

// �˻� �Լ�
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

// ��� ���� �Լ�
TreeNode* new_node(char* item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(temp->res, item);
	temp->number = 1;
	temp->left = temp->right = NULL;
	return temp;
}

// �����ϴ� �Լ�
TreeNode* insert_node(TreeNode* node, char* key) {
	//Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (node == NULL) return new_node(key);


	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (compare(key, node) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node) > 0)
		node->right = insert_node(node->right, key);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}

// ������ ���� Ʈ���� �ּҰ�
TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}

// ��� ���� �Լ�
TreeNode* delete_node(TreeNode* root, char* key) {
	if (root == NULL) return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� ����
	if (compare(key, root) < 0)
		root->left = delete_node(root->left, key);

	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� ����
	else if (compare(key, root) > 0)
		root->right = delete_node(root->right, key);

	else {
		// ù ��°�� �� ��° ���
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

		// �� ��°�� ���
		TreeNode* temp = min_value_node(root->right);

		// ���� ��ȯ�� �İ� ��带 �����Ѵ�.
		strcpy(root->res, temp->res);
		root->number = temp->number;

		// ���� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->res);
	}

	return root;
}

// �ִ� ã�� �Լ�
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
	printf("==========[�޴�]==========\n");
	printf("0. ����\n");
	printf("1. ������ȸ�� ���\n");
	printf("2. ������ ����� �Է�\n");
	printf("3. �ִ� �� �����\n");
	printf("==========================\n");
	printf("�Է�:");
}

int main(void) {
	int num = 0;
	FILE* fp1 = fopen("bst_in.txt", "r");
	FILE* fp2 = fopen("bst_out.txt", "w");

	if (fp1 == NULL) {
		printf("������ �������� �ʽ��ϴ�.\n");
		return 0;
	}

	char* p = (char*)malloc(sizeof(char) * 1000);
	char* str[] = { "break", "case","do","else","for","if","int","return","struct","switch","while" };

	while (!feof(fp1)) { //EOF�� ���ö����� ��� ������.
		fscanf(fp1, "%s ", p); // ���� ������ �޾ƿ�
		for (int i = 0; i < 11; i++) {
			if (strstr(p, str[i])) {
				if (search(r, str[i]) == NULL) { // ã�� �ܾ ���� ��
					r = insert_node(r, str[i]);
					break; // ���� �ܾ� �޾ƿ���
				}
				else if (search(r, str[i]) != NULL) {
					search(r, str[i])->number++;
					break;
				}
			}
		}
	}

	inorder_fprintf(r, fp2); // ������ȸ�� ���Ͽ� �Է�

	char* s = (char*)malloc(sizeof(char) * 1000);
	fclose(fp2);
	while (1) {
		menu();
		scanf("%d", &num);
		if (num == 0) return 0;

		switch (num) {
		case 1:
			display(r); //������ȸ�� ���
			break;

		case 2:
			printf("������ �ܾ �Է����ּ���: ");
			scanf("%s", s);
			delete_node(r, s);
			break;

		case 3:
			maximum = r;
			max = r->number;
			printf("\n�� �ִ� �� = [%s : %d]\n", find_max(r)->res, find_max(r)->number);
			break;

		default:
			printf("�ٽ� �Է����ּ���\n");
			break;
		}
	}

	free(p);
	fclose(fp1);

	return 0;
}