/*
1. 이진검색트리 T1
(1) 이진검색트리에서 임의의 키 값을 검색하는 함수를 작성하시오.
(2) 새로운 키 값을 이진검색트리에 삽입하는 함수를 작성하시오.
    삽입이 잘 되었는지, 중위순회를 이용하여 확인하시오.
(3) 키 값을 이진검색트리에서 삭제하는 함수를 작성하시오.
    자식노드가 두 개인 노드가 삭제될 때, 오른쪽 서브트리에서 최소값을 찾아서 대신하도록
    작성하시오,
(4) 이진검색트리의 내부경로길이(IPL)을 계산하는 함수를 작성하시오.
(5) IPL을 이용하여 이진검색트리의 평균 검색 성능을 계산하는 함수를 작성하시오.

2. 이진트리 T2
(6) 주어진 이진트리가 이진검색트리인지 아닌지 확인하는 함수를 작성하시오.
(7) 이진트리와 어떤 합을 뜻하는 수가 하나 주어진다. 트리의 루트에서 리프 노드까지의 경
    로의 값을 모두 합한 값이 주어진 합과 같은 경로가 있는지 판단하는 함수를 작성하시오.
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

// 1. 임의의 키 값을 검색하는 함수
treeNode * treeSearch(treeNode* t, int x) {
    if (t == NULL || t->data == x) return t;
    
    if (x < t->data) return treeSearch(t->left, x);
    else return treeSearch(t->right, x);
}

// 2.  새로운 키 값을 이진검색트리에 삽입하는 함수 및 중위순회를 이용하여 확인
treeNode* new_node(int item) {
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

treeNode* insert(treeNode* node, int key) {
    // 이진 탐색 트리의 노드 추가 수행
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

// 3. 키 값을 이진검색트리에서 삭제하는 함수
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
        while (s ->right != NULL) { // ???  후계자 찾기
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


// 4, 5. 내부경로길이(IPL)을 계산하는 함수 , 평균검색성능 구하기
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

// 6. 이진검색트리인지 아닌지 판별하는 함수
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

// 0. 기타 함수
void menu() {
    printf("==========[메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 임의의 키 값을 검색\n");
    printf("2. 새로운 키 값 삽입\n");
    printf("3. 트리에서 원하는 키 값 삭제\n");
    printf("4. 내부 경로 길이(IPL) 구하기 및 평균 검색 성능 계산\n");
    printf("5. 4번과 동일\n");
    printf("6. 이진검색트리 판별\n");
    printf("7. hasPathSum\n");
    printf("==========================\n");
    printf("입력:");
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
            printf("\n입력하세요: ");
            scanf("%d", &n);
            if (treeSearch(root, n) == NULL) printf("False\n");
            else if (treeSearch(root, n)->data == n) printf("True\n");
            break;
        
        case 2:
            printf("\n입력하세요: ");
            scanf("%d", &n);
            root = insert(root, n);
            printf("중위순회 : ");
            inorder(root);
            printf("\n");
            break;
        
        case 3:
            printf("\n입력하세요: ");
            scanf("%d", &n);
            deleteNode(root, n);
            printf("중위순회 : ");
            inorder(root);
            printf("\n");
            break;
        
        case 4: case 5:
            get_node_count(root);
            get_IPL(root, 0); // IPL도 같이 구해진다.
            printf("[IPL : %d], [노드 개수 : %d], [평균검색성능 : %0.1f]\n", IPL, cnt, AVG_IPL());
            init();
            break;
        
        case 6:
            array_tree(nroot);
            save_array(nroot);
            int bool = check_binary_search_tree();

            if (bool) printf("이진검색트리가 맞습니다.\n");
            else printf("이진검색트리가 아닙니다.\n");
            break;
        
        case 7:
            printf("\n입력하세요: ");
            scanf("%d", &n);
            if (hasPathSum(root, n)) printf("TRUE 입니다.\n");
            else printf("FALSE 입니다.\n");
            break;
        
        default:
            printf("잘못된 접근입니다.\n");
        }
        menu();
        scanf("%d", &num);
    }

    return 0;
}