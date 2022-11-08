/*
���������˻�Ʈ�� AVL Ʈ���� Ű���� �����ϸ鼭 Ȯ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
- Ű ���� ���� ���Ե� �� �ұ����� ���� LL, RR, LR, RL �� �߻��� ���,
- ������ ȸ���� �����Ͽ� ���������˻�Ʈ�� AVL Ʈ���� �����ϵ��� �Ѵ�
- ��� Ʈ���� ���̿� ������ȸ ������ ����Ѵ�.
- AVL Ʈ���� �ƴ� ����� �����˻�Ʈ���� ������ ����� ���Ѵ�.
  (��) Ű������ {50, 60, 70, 90, 80, 75, 73, 72, 78} ������ ���Ե� ���,


�� (���û���) Ű ���� ������ ���� ���� ������� ������ �����ϴ� ���α׷����� �ϼ��ϱ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size = 9;
int arr[] = { 50, 60, 70, 90, 80, 75, 73, 72, 78};

// Ʈ�� ��� ����
typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

// ��带 �������� �����ϴ� �Լ�
treeNode* new_node(int item) {
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

// ������ȸ�� ���
void inorder(treeNode* t) {
    if (t != NULL) {
        inorder(t->left);
        printf("[%d] ", t->data);
        inorder(t->right);
    }
}

// Ʈ���� ���̸� ��ȯ
int get_height(treeNode* node) {
    int cnt = 0;
    if (node != NULL)
        cnt = 1 + max(get_height(node->left), get_height(node->right));

    return cnt;
}

// ����� �����μ��� ��ȯ
int get_balance(treeNode* node) {
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

// ���������� ȸ����Ű�� �Լ� => LL �� ��
treeNode* rotate_right(treeNode* parent) {
    treeNode* child = parent->left;
    parent->left = child->right;
    child->right = parent;

    // ���ο� ��Ʈ�� ��ȯ
    return child;
}

// �������� ȸ����Ű�� �Լ� => RR �� ��
treeNode* rotate_left(treeNode* parent) {
    treeNode* child = parent->right;
    parent->right = child->left;
    child->left = parent;

    // ���ο� ��Ʈ�� ��ȯ
    return child;
}

// AVL Ʈ���� ���ο� ��� �߰� �Լ�
// ���ο� ��Ʈ�� ��ȯ�Ѵ�.
treeNode* insert_AVL(treeNode* node, int key) {
    // ���� Ž�� Ʈ���� ��� �߰� ����
    if (node == NULL) return new_node(key);

    if (key < node->data) node->left = insert_AVL(node->left, key);
    else if (key > node->data) node->right = insert_AVL(node->right, key);
    else return node; // ������ Ű�� ������ ����!

    // ������ �����μ� ����
    int bal = get_balance(node);

    // LL Ÿ�� ó��
    if (bal > 1 && key < node->left->data) {
        printf("\n[LL Ÿ�� ó��]\n");
        return rotate_right(node);
    }

    // RR Ÿ�� ó��
    if (bal < -1 && key > node->right->data) {
        printf("\n[RR Ÿ�� ó��]\n");
        return rotate_left(node);
    }

    // LR Ÿ�� ó��
    if (bal > 1 && key > node->left->data) {
        printf("\n[LR Ÿ�� ó��]\n");
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RL Ÿ�� ó��
    if (bal < -1 && key < node->right->data) {
        printf("\n[RL Ÿ�� ó��]\n");
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

treeNode* insert(treeNode* node, int key) {
    // ���� Ž�� Ʈ���� ��� �߰� ����
    if (node == NULL) return new_node(key);

    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    else return node;

    return node;
}

// Ű ���� �����˻�Ʈ������ �����ϴ� �Լ�
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
        while (s->right != NULL) { // ???  �İ��� ã��
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

// �뷱�� �ٽ� �����.
treeNode * ReBal(treeNode* root) {
    if (root == NULL) return NULL;

    root->left = ReBal(root->left);
    root->right = ReBal(root->right);

    int bal = get_balance(root);
    if (bal >= -1 && bal <= 1) return root;

    if (bal > 1) {
        if (get_balance(root->left) > 0) rotate_right(root);
        else {
            root->right = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    else {
        if (get_balance(root->left) < 0) rotate_left(root);
        else {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }
}

// ���ΰ�α���(IPL)�� ����ϴ� �Լ� , ��հ˻����� ���ϱ�
int cnt = 0;
int IPL = 0;

void get_node_count(treeNode* node) {
    if (node != NULL) {
        cnt++;
        get_node_count(node->left);
        get_node_count(node->right);
    }
}

void get_IPL(treeNode* node, int n) {
    if (node != NULL) {
        printf("%d %d\n", node->data, n);
        IPL += n;
        get_IPL(node->left, n + 1);
        get_IPL(node->right, n + 1);
    }
}

double AVG_IPL() {
    return (double)IPL / (double)cnt;
}

void init() {
    cnt = 0, IPL = 0;
}

void menu() {
    printf("==========[�޴�]==========\n");
    printf("0. ����\n");
    printf("1. ���ο� Ű �� ����\n");
    printf("2. Ʈ������ ���ϴ� Ű �� ����\n");
    printf("3. ���� ��� ����(IPL) ���ϱ� �� ��� �˻� ���� ���\n");
    printf("==========================\n");
    printf("�Է�:");
}

int main() {
    int num = -1, n;

    treeNode* AVL_root = NULL;
    treeNode* root = NULL;

    /*for (int i = 0; i < size; i++) {
        AVL_root = insert_AVL(AVL_root, arr[i]);
        root = insert(root, arr[i]);
    }
    printf("\n������ȸ : ");
    inorder(AVL_root);
    printf("\n");*/

    menu();
    scanf("%d", &num);

    while (num != 0) {
        switch (num) {
        case 1:
            printf("������ �Է��ϼ��� : ");
            scanf("%d", &n);

            root = insert(root, n);
            AVL_root = insert_AVL(AVL_root, n);

            printf("\n������ȸ : ");
            inorder(AVL_root);
            printf("\n");
            printf("AVL ���� : %d\n",get_height(AVL_root));
            break;

        case 2:
            printf("������ �Է��ϼ��� : ");
            scanf("%d", &n);

            deleteNode(AVL_root, n);
            ReBal(AVL_root);

            deleteNode(root, n);

            printf("\n������ȸ : ");
            inorder(AVL_root);
            printf("\n");
            printf("AVL ���� : %d\n", get_height(AVL_root));
            break;

        case 3:
            get_node_count(AVL_root); get_IPL(AVL_root, 0);
            printf("\n[AVL] IPL : %d || ��尳�� : %d || ��� �˻� ���� : %0.1f\n", IPL,cnt, AVG_IPL());
            init();

            get_node_count(root); get_IPL(root, 0);
            printf("[N_Bin_Tree] IPL : %d || ��尳�� : %d || ��� �˻� ���� : %0.1f\n\n", IPL, cnt, AVG_IPL());
            init();
            break;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }
        menu();
        scanf("%d", &num);
    }
    return 0;
}
