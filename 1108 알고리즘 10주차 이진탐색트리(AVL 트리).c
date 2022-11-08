/*
균형이진검색트리 AVL 트리에 키값을 삽입하면서 확인하는 프로그램을 작성하시오.
- 키 값이 새로 삽입될 때 불균형의 유형 LL, RR, LR, RL 이 발생할 경우,
- 적절한 회전을 수행하여 균형이진검색트리 AVL 트리를 유지하도록 한다
- 결과 트리의 높이와 중위순회 순서를 출력한다.
- AVL 트리가 아닌 경우의 이진검색트리에 삽입한 결과를 비교한다.
  (예) 키값들이 {50, 60, 70, 90, 80, 75, 73, 72, 78} 순서로 삽입된 경우,


※ (선택사항) 키 값이 삭제될 때도 같은 방법으로 균형을 유지하는 프로그램으로 완성하기.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size = 9;
int arr[] = { 50, 60, 70, 90, 80, 75, 73, 72, 78};

// 트리 노드 정의
typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

// 노드를 동적으로 생성하는 함수
treeNode* new_node(int item) {
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 중위순회로 출력
void inorder(treeNode* t) {
    if (t != NULL) {
        inorder(t->left);
        printf("[%d] ", t->data);
        inorder(t->right);
    }
}

// 트리의 높이를 반환
int get_height(treeNode* node) {
    int cnt = 0;
    if (node != NULL)
        cnt = 1 + max(get_height(node->left), get_height(node->right));

    return cnt;
}

// 노드의 균형인수를 반환
int get_balance(treeNode* node) {
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

// 오른쪽으로 회전시키는 함수 => LL 일 때
treeNode* rotate_right(treeNode* parent) {
    treeNode* child = parent->left;
    parent->left = child->right;
    child->right = parent;

    // 새로운 루트를 반환
    return child;
}

// 왼쪽으로 회전시키는 함수 => RR 일 때
treeNode* rotate_left(treeNode* parent) {
    treeNode* child = parent->right;
    parent->right = child->left;
    child->left = parent;

    // 새로운 루트를 반환
    return child;
}

// AVL 트리에 새로운 노드 추가 함수
// 새로운 루트를 반환한다.
treeNode* insert_AVL(treeNode* node, int key) {
    // 이진 탐색 트리의 노드 추가 수행
    if (node == NULL) return new_node(key);

    if (key < node->data) node->left = insert_AVL(node->left, key);
    else if (key > node->data) node->right = insert_AVL(node->right, key);
    else return node; // 동일한 키는 허용되지 않음!

    // 노드들의 균형인수 재계산
    int bal = get_balance(node);

    // LL 타입 처리
    if (bal > 1 && key < node->left->data) {
        printf("\n[LL 타입 처리]\n");
        return rotate_right(node);
    }

    // RR 타입 처리
    if (bal < -1 && key > node->right->data) {
        printf("\n[RR 타입 처리]\n");
        return rotate_left(node);
    }

    // LR 타입 처리
    if (bal > 1 && key > node->left->data) {
        printf("\n[LR 타입 처리]\n");
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RL 타입 처리
    if (bal < -1 && key < node->right->data) {
        printf("\n[RL 타입 처리]\n");
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

treeNode* insert(treeNode* node, int key) {
    // 이진 탐색 트리의 노드 추가 수행
    if (node == NULL) return new_node(key);

    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    else return node;

    return node;
}

// 키 값을 이진검색트리에서 삭제하는 함수
void deleteNode(treeNode* root, int key) {
    treeNode* parent, * p, * s, * s_parent;
    treeNode* child;

    parent = NULL;
    p = root;
    while ((p != NULL) && (p->data != key)) {  // 삭제할 노드의 위치 탐색
        parent = p;
        if (key < p->data) p = p->left;
        else p = p->right;
    }

    // 삭제할 노드가 없는 경우
    if (p == NULL) {
        printf("\n 찾는 키가 없습니다.\n");
        return;
    }

    // 삭제할 노드가 단말 노드인 경우
    if ((p->left == NULL) && (p->right == NULL)) {
        if (parent != NULL) {
            if (parent->left == p) parent->left = NULL;
            else parent->right = NULL;
        }
        else root = NULL;
    }

    // 삭제할 노드가 자식 노드를 한 개 가진 경우
    else if ((p->left == NULL) || (p->right == NULL)) {
        if (p->left != NULL) child = p->left;
        else child = p->right;

        if (parent != NULL) {
            if (parent->left == p) parent->left = child;
            else parent->right = child;
        }
        else root = child;
    }

    // 삭제할 노드가 자식 노드를 두 개 가진 경우
    else {
        s_parent = p;
        s = p->left;
        while (s->right != NULL) { // ???  후계자 찾기
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

// 밸런스 다시 맞춘다.
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

// 내부경로길이(IPL)을 계산하는 함수 , 평균검색성능 구하기
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
    printf("==========[메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 새로운 키 값 삽입\n");
    printf("2. 트리에서 원하는 키 값 삭제\n");
    printf("3. 내부 경로 길이(IPL) 구하기 및 평균 검색 성능 계산\n");
    printf("==========================\n");
    printf("입력:");
}

int main() {
    int num = -1, n;

    treeNode* AVL_root = NULL;
    treeNode* root = NULL;

    /*for (int i = 0; i < size; i++) {
        AVL_root = insert_AVL(AVL_root, arr[i]);
        root = insert(root, arr[i]);
    }
    printf("\n중위순회 : ");
    inorder(AVL_root);
    printf("\n");*/

    menu();
    scanf("%d", &num);

    while (num != 0) {
        switch (num) {
        case 1:
            printf("정수를 입력하세요 : ");
            scanf("%d", &n);

            root = insert(root, n);
            AVL_root = insert_AVL(AVL_root, n);

            printf("\n중위순회 : ");
            inorder(AVL_root);
            printf("\n");
            printf("AVL 높이 : %d\n",get_height(AVL_root));
            break;

        case 2:
            printf("정수를 입력하세요 : ");
            scanf("%d", &n);

            deleteNode(AVL_root, n);
            ReBal(AVL_root);

            deleteNode(root, n);

            printf("\n중위순회 : ");
            inorder(AVL_root);
            printf("\n");
            printf("AVL 높이 : %d\n", get_height(AVL_root));
            break;

        case 3:
            get_node_count(AVL_root); get_IPL(AVL_root, 0);
            printf("\n[AVL] IPL : %d || 노드개수 : %d || 평균 검색 성능 : %0.1f\n", IPL,cnt, AVG_IPL());
            init();

            get_node_count(root); get_IPL(root, 0);
            printf("[N_Bin_Tree] IPL : %d || 노드개수 : %d || 평균 검색 성능 : %0.1f\n\n", IPL, cnt, AVG_IPL());
            init();
            break;

        default:
            printf("잘못된 접근입니다.\n");
        }
        menu();
        scanf("%d", &num);
    }
    return 0;
}
