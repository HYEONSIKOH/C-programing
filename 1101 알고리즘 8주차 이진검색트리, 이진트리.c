/*
1. �����˻�Ʈ�� T1
(1) �����˻�Ʈ������ ������ Ű ���� �˻��ϴ� �Լ��� �ۼ��Ͻÿ�.
(2) ���ο� Ű ���� �����˻�Ʈ���� �����ϴ� �Լ��� �ۼ��Ͻÿ�.
    ������ �� �Ǿ�����, ������ȸ�� �̿��Ͽ� Ȯ���Ͻÿ�.
(3) Ű ���� �����˻�Ʈ������ �����ϴ� �Լ��� �ۼ��Ͻÿ�.
    �ڽĳ�尡 �� ���� ��尡 ������ ��, ������ ����Ʈ������ �ּҰ��� ã�Ƽ� ����ϵ���
    �ۼ��Ͻÿ�,
(4) �����˻�Ʈ���� ���ΰ�α���(IPL)�� ����ϴ� �Լ��� �ۼ��Ͻÿ�.
(5) IPL�� �̿��Ͽ� �����˻�Ʈ���� ��� �˻� ������ ����ϴ� �Լ��� �ۼ��Ͻÿ�.

2. ����Ʈ�� T2
(6) �־��� ����Ʈ���� �����˻�Ʈ������ �ƴ��� Ȯ���ϴ� �Լ��� �ۼ��Ͻÿ�.
(7) ����Ʈ���� � ���� ���ϴ� ���� �ϳ� �־�����. Ʈ���� ��Ʈ���� ���� �������� ��
    ���� ���� ��� ���� ���� �־��� �հ� ���� ��ΰ� �ִ��� �Ǵ��ϴ� �Լ��� �ۼ��Ͻÿ�.
    hasPathSum(treeNode* root, int sum)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

treeNode n1 = { 1, NULL, NULL };
treeNode n2 = { 4, &n1, NULL };
treeNode n3 = { 16, NULL, NULL };
treeNode n4 = { 25, NULL, NULL };
treeNode n5 = { 14, &n3, &n4 };
treeNode n6 = { 15, &n2, &n5 };
treeNode* nroot = &n6;

int arr[8] = { 22,19,35,54,46,18,43,2 };

// 1. ������ Ű ���� �˻��ϴ� �Լ�
treeNode * treeSearch(treeNode* t, int x) {
    if (t == NULL || t->data == x) return t;
    
    if (x < t->data) return treeSearch(t->left, x);
    else return treeSearch(t->right, x);
}

// 2.  ���ο� Ű ���� �����˻�Ʈ���� �����ϴ� �Լ� �� ������ȸ�� �̿��Ͽ� Ȯ��
treeNode* new_node(int item) {
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

treeNode* insert(treeNode* node, int key) {
    // ���� Ž�� Ʈ���� ��� �߰� ����
    if (node == NULL) return new_node(key);

    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    else return node;

    return node;
}

void inorder(treeNode* t) {
    if (t != NULL) {
        inorder(t->left);
        printf("[%d] ",t->data);
        inorder(t->right);
    }
}

// 3. Ű ���� �����˻�Ʈ������ �����ϴ� �Լ�
void deleteNode(treeNode* root, int key) {
    treeNode* parent, * p, * s, * s_parent;
    treeNode* child;

    parent = NULL;
    p = root;
    while ((p != NULL) && (p->data != key)) {  // ������ ����� ��ġ Ž��
        parent = p;
        if (key < p->data) p = p->left;
        else p = p->right;
    }

    // ������ ��尡 ���� ���
    if (p == NULL) {
        printf("\n ã�� Ű�� �����ϴ�.\n");
        return;
    }

    // ������ ��尡 �ܸ� ����� ���
    if ((p->left == NULL) && (p->right == NULL)) {
        if (parent != NULL) {
            if (parent->left == p) parent->left = NULL;
            else parent->right = NULL;
        }
        else root = NULL;
    }

    // ������ ��尡 �ڽ� ��带 �� �� ���� ���
    else if ((p->left == NULL) || (p->right == NULL)) {
        if (p->left != NULL) child = p->left;
        else child = p->right;

        if (parent != NULL) {
            if (parent->left == p) parent->left = child;
            else parent->right = child;
        }
        else root = child;
    }

    // ������ ��尡 �ڽ� ��带 �� �� ���� ���
    else {
        s_parent = p;
        s = p->left;
        while (s ->right != NULL) { // ???  �İ��� ã��
            s_parent = s;
            s = s->right;
        }
        if (s_parent->left == s)  s_parent->left = s->left;
        else s_parent->right = s->left;
        p->data = s->data;
        p = s;
    }

    free(p);
}


// 4, 5. ���ΰ�α���(IPL)�� ����ϴ� �Լ� , ��հ˻����� ���ϱ�
int cnt = 0;
int IPL = 0;

void get_node_count(treeNode* node) {
    if (node != NULL) {
        cnt++;
        get_node_count(node->left);
        get_node_count(node->right);
    }
}

void get_IPL(treeNode* node,int n) {
    if (node != NULL) {
        IPL += n;
        get_IPL(node->left, n+1);
        get_IPL(node->right, n+1);
    }
}

double AVG_IPL() {
    return (double)IPL / (double)cnt;
}

void init() {
    cnt = 0, IPL = 0;
}

// 6. �����˻�Ʈ������ �ƴ��� �Ǻ��ϴ� �Լ�
int* temp;
void array_tree(treeNode * t) {
    get_node_count(t);
    temp = (int*)malloc(sizeof(int) * cnt);
}

int k = 0;
int* save_array(treeNode * t) {
    if (t != NULL) {
        save_array(t->left);
        temp[k++] = t->data;
        save_array(t->right);
    }
}

int check_binary_search_tree() {
    int n = temp[0];
    for (int i = 1; i < cnt; i++) {
        if (n > temp[i]) return 0;
        else n = temp[i];
    }

    cnt = 0;
    k = 0;
    free(temp);
    return 1;
}

// 7.
int hasPathSum(treeNode* root, int sum) {
    if (root == NULL)  return 0;

    if (root->left == NULL && root->right == NULL && sum - root->data == 0) {
        return 1;
    }
    else {
        return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
    }
}

// 0. ��Ÿ �Լ�
void menu() {
    printf("==========[�޴�]==========\n");
    printf("0. ����\n");
    printf("1. ������ Ű ���� �˻�\n");
    printf("2. ���ο� Ű �� ����\n");
    printf("3. Ʈ������ ���ϴ� Ű �� ����\n");
    printf("4. ���� ��� ����(IPL) ���ϱ� �� ��� �˻� ���� ���\n");
    printf("5. 4���� ����\n");
    printf("6. �����˻�Ʈ�� �Ǻ�\n");
    printf("7. hasPathSum\n");
    printf("==========================\n");
    printf("�Է�:");
}

int main() {
    treeNode* root = NULL;
    for (int i = 0; i < 8; i++) root = insert(root, arr[i]);
    inorder(root);
    printf("\n");
    menu();
    int num = 0;
    scanf("%d", &num);

    while (num != 0) {
        int n = 0;
        switch (num) {
        case 1:
            printf("\n�Է��ϼ���: ");
            scanf("%d", &n);
            if (treeSearch(root, n) == NULL) printf("False\n");
            else if (treeSearch(root, n)->data == n) printf("True\n");
            break;
        
        case 2:
            printf("\n�Է��ϼ���: ");
            scanf("%d", &n);
            root = insert(root, n);
            printf("������ȸ : ");
            inorder(root);
            printf("\n");
            break;
        
        case 3:
            printf("\n�Է��ϼ���: ");
            scanf("%d", &n);
            deleteNode(root, n);
            printf("������ȸ : ");
            inorder(root);
            printf("\n");
            break;
        
        case 4: case 5:
            get_node_count(root);
            get_IPL(root, 0); // IPL�� ���� ��������.
            printf("[IPL : %d], [��� ���� : %d], [��հ˻����� : %0.1f]\n", IPL, cnt, AVG_IPL());
            init();
            break;
        
        case 6:
            array_tree(nroot);
            save_array(nroot);
            int bool = check_binary_search_tree();

            if (bool) printf("�����˻�Ʈ���� �½��ϴ�.\n");
            else printf("�����˻�Ʈ���� �ƴմϴ�.\n");
            break;
        
        case 7:
            printf("\n�Է��ϼ���: ");
            scanf("%d", &n);
            if (hasPathSum(root, n)) printf("TRUE �Դϴ�.\n");
            else printf("FALSE �Դϴ�.\n");
            break;
        
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
        menu();
        scanf("%d", &num);
    }

    return 0;
}