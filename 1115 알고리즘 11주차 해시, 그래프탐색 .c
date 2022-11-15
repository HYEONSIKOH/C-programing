/*
1. 해시 테이블
   (1) 교재 242쪽 연습문제 01, 02, 03을 프로그램으로 구현하여 확인하시오.
       각 경우에 대해 키 값들이 해시테이블에 저장된 상태를 출력으로 보이시오.
   (2) 크기가 11인 해시테이블을 가정하자, 해시함수로는 h(x) = x mod 11 을 사용한다.
       키 값들이 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5의 순서로 입력될 때, 아래 각 경우에 대
       해 저장된 해시테이블의 내용을 각각 출력하시오.
       - 충돌을 선형조사법으로 처리한다.
       - 충돌을 이차조사법으로 처리한다.
       - 충돌을 f(x) = 7 – (x mod 7) 를 이용하여 더블해싱 방법으로 처리한다.
       - 충돌을 체이닝 방법으로 처리한다.

2. 그래프 탐색 (깊이우선 탐색)
   정점을 최대 20개를 갖는 각자의 그래프 G1, G2, G3를 그림으로 그리시오.
   - G1은 방향없는 연결된 그래프이고 인접행렬로 저장,
   - G2는 방향없는 연결되지 않은 그래프이고, 인접리스트로 저장
   - G3는 방향있는 그래프이고, 인접리스트로 저장하시오
.
    (1) 완성된 인접행렬과 인접리스트를 출력한다.
    (2) 각 그래프에 대해서 임의의 정점에서 깊이우선탐색하는 함수를 작성하시오.
        만약, 이 그래프가 연결되어 있지 않다면 연결된 각 부분들을 구한다.
    
    // 깊이우선탐색 함수를 (교재 309쪽 알고리즘 10-2 참조)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Q1[] = { 10,20,30,40,33,46,50,60 };
int Q2[] = { 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5};
int* t; // 해시 테이블

void init_hash_table(int size) {
    t = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) t[i] = 0;
}

// ==== 선형조사법 ====
void LP(int item, int size) {
	int i, hash_value = 0;
	hash_value = i = item % size;

	printf("\nNum : %d || 주소 = %d ", item ,i);
	while (t[i] != 0) {
		if (t[i] == item) return; // 이미 해시 테이블에 값이 있을 때

		i = (i + 1) % size;

		if (hash_value == i) return; // 자리가 꽉 찼을 때

		printf(">> %d ", i);
	}
	t[i] = item;
	printf("\n");

    for (int j = 0; j < size; j++) {
        if (j == i) printf("[\033[0;32m%d\033[0m] ", t[j]);
        else if (t[j] == 0) printf("[  ] ");
        else printf("[%d] ", t[j]);
    }
    printf("\n\n--------------------------------------\n");
}

// ==== 이차원 조사법 ====
void QP(int item, int size) {
    int i, hash_value = 0;
    hash_value = i = item % size;
    int n = 1;

    printf("\nNum : %d || 주소 = %d ", item, i);
    while (t[i] != 0) {
        if (t[i] == item) return; // 이미 해시 테이블에 값이 있을 때

        i = (hash_value + (n*n)) % size;
        n++;

        if (hash_value == i) return; // 자리가 꽉 찼을 때

        printf(">> %d ", i);
    }
    t[i] = item;
    printf("\n");

    for (int j = 0; j < size; j++) {
        if (j == i) printf("[\033[0;32m%d\033[0m] ", t[j]);
        else if (t[j] == 0) printf("[  ] ");
        else printf("[%d] ", t[j]);
    }
    printf("\n\n--------------------------------------\n");
}

// ==== 더블 해싱 조사법 ====

int mode1(int x) {
    return 1 + (x % 11);
}

int mode2(int x) {
    return 7 - (x % 11);
}

void DH(int item, int size, char mode) {
    int i, hash_value = 0, n;
    hash_value = i = item % size;
    
    if (mode == '1') n = mode1(item);
    else n = mode2(item);

    printf("\nNum : %d || 주소 = %d ", item, i);
    while (t[i] != 0) {
        if (t[i] == item) return; // 이미 해시 테이블에 값이 있을 때

        i = (i + n) % size;

        if (hash_value == i) return; // 자리가 꽉 찼을 때

        printf(">> %d ", i);
    }
    t[i] = item;
    printf("\n");

    for (int j = 0; j < size; j++) {
        if (j == i) printf("[\033[0;32m%d\033[0m] ", t[j]);
        else if (t[j] == 0) printf("[  ] ");
        else printf("[%d] ", t[j]);
    }
    printf("\n\n--------------------------------------\n");
}

// ==== 체이닝 ====

typedef struct list {
    int item;
    struct list* link;
}list;

list* table[11];

void Chaining(int item) {
    int hash_value = item % 11;

    list* p = (list*)malloc(sizeof(list));
    p->item = item;
    p->link = NULL;

    list* node_before = NULL;

    // 이미 리스트 안에 같은 값이 있을 때!
    for (list* node = table[hash_value]; node; node_before = node, node = node->link) if (node->item == item) return;

    if (node_before) node_before->link = p;
    else table[hash_value] = p;

    for (int i = 0; i < 11; i++) {
        printf("[%2d] -> ",i);

        for (list* ptr = table[i]; ptr; ptr = ptr->link) {
            printf("%d ", ptr->item);
            if (ptr->link) printf("-> ");
        }

        printf("\n");
    }

    printf("\n--------------------------------------\n");
}

// ===================================================================================================================================
// 그래프 탐색
#define max_size 21

int matrix[max_size][max_size];
list* graph[max_size];

int visit[max_size] = { 0, };

void insert(int a, int b) {
    list* p = (list*)malloc(sizeof(list));
    p->item = b;
    p->link = NULL;

    list* node_before = NULL;

    // 이미 리스트 안에 같은 값이 있을 때!
    for (list* node = graph[a]; node; node_before = node, node = node->link) if (node->item == b) return;

    if (node_before) node_before->link = p;
    else graph[a] = p;
}

void G1() {
    matrix[1][2] = matrix[2][1] = 1;
    matrix[3][2] = matrix[2][3] = 1;
    matrix[4][3] = matrix[3][4] = 1;
    matrix[4][5] = matrix[5][4] = 1;
    matrix[6][2] = matrix[2][6] = 1;
    matrix[6][7] = matrix[7][6] = 1;
    matrix[8][6] = matrix[6][8] = 1;
}

void G2() {
    insert(1, 2);
    insert(2, 1);

    insert(3, 2);
    insert(2, 3);

    insert(4, 2);
    insert(2, 4);

    insert(3, 4);
    insert(4, 3);

    insert(1, 4);
    insert(4, 1);

    insert(4, 5);
    insert(5, 4);

    insert(5, 2);
    insert(2, 5);

    insert(8, 7);
    insert(7, 8);

    insert(8, 6);
    insert(6, 8);
}

void G3() {
    insert(2, 1);
    insert(1, 6);
    insert(2, 5);
    insert(4, 2);
    insert(6, 3);
    insert(3, 4);
    insert(5, 8);
    insert(8, 7);
}

void print_matrix(int size) {
    printf("\n=============================================\n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }
    printf("\n=============================================\n");
}

void print_list(int size) {
    printf("\n=============================================\n");
    for (int i = 1; i <= size; i++) {
        printf("[%2d] -> ", i);

        for (list* ptr = graph[i]; ptr; ptr = ptr->link) {
            printf("%d ", ptr->item);
            if (ptr->link) printf("-> ");
        }

        printf("\n");
    }
    printf("\n=============================================\n");
}

void dfs_matrix(int s, int size) {
    visit[s] = 1;
    printf(">> %d ", s);
    for (int i = 1; i <= size; i++)
        if (matrix[s][i] == 1 && visit[i] == 0) dfs_matrix(i,size);
}

void dfs_list(int s) {
    visit[s] = 1;
    printf("%d >> ", s);

    for (list* ptr = graph[s]; ptr; ptr = ptr->link)
        if (visit[ptr->item] == 0) dfs_list(ptr->item);
}

void init_graph(int size) {
    for (int i = 1; i <= size; i++) for (int j = 0; j <= size; j++) matrix[i][j] = 0;

    for (int i = 1; i <= size; i++) {
        graph[i] = NULL;
        visit[i] = 0;
    }
}

void main_menu() {
    printf("==========[메인 메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 해시 충돌\n");
    printf("2. 그래프 탐색\n");
    printf("===============================\n");
    printf("입력:");
}

void hash_menu() {
    printf("==========[HASH 메뉴]==========\n");
    printf("1. { 10, 20, 30, 40, 33, 46, 50, 60 }\n");
    printf("2. { 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5}\n");
    printf("===============================\n");
    printf("입력:");
}

void choose_graph() {
    printf("==========[ 선택해주세요 ]==========\n");
    printf("1. G1 => 방향이 없는 행렬\n");
    printf("2. G2 => 방향이 없는 리스트\n");
    printf("3. G3 => 방향이 있는 리스트\n");
    printf("====================================\n");
    printf("입력:");
}

int main() {
    int num, N, n, k;
    main_menu();
    scanf("%d", &num);

    while (num != 0) {
        switch (num) {
        case 1:
            hash_menu();
            scanf("%d", &N);

            switch (N) {
            case 1:
                init_hash_table(13);

                printf("==========[ 선택해주세요 ]==========\n");
                printf("1. 선형\n");
                printf("2. 이차원\n");
                printf("3. 더블해싱\n");
                printf("====================================\n");
                printf("입력:"); scanf("%d", &n);

                if (n == 1) for (int i = 0; i < 8; i++) LP(Q1[i], 13);
                if (n == 2) for (int i = 0; i < 8; i++) QP(Q1[i], 13);
                if (n == 3) for (int i = 0; i < 8; i++) DH(Q1[i], 13, '1');

                break;
            case 2:
                init_hash_table(11);
                for (int i = 0; i < 11; i++) table[i] = NULL;

                printf("==========[ 선택해주세요 ]==========\n");
                printf("1. 선형\n");
                printf("2. 이차원\n");
                printf("3. 더블해싱\n");
                printf("4. 체이닝\n");
                printf("====================================\n");
                printf("입력:"); scanf("%d", &n);

                if (n == 1) for (int i = 0; i < 11; i++) LP(Q2[i], 11);
                if (n == 2) for (int i = 0; i < 11; i++) QP(Q2[i], 11);
                if (n == 3) for (int i = 0; i < 11; i++) DH(Q2[i], 11, '2');
                if (n == 4) for (int i = 0; i < 11; i++) Chaining(Q2[i]);

                break;
            }

            break;

        case 2:
            choose_graph(); scanf("%d", &N);
            init_graph(8);
            switch (N) {
            case 1:
                G1();

                print_matrix(8);
                printf("시작 정점을 입력해주세요 : ");
                scanf("%d", &k);
                dfs_matrix(k, 8);
                printf("\n");

                break;
            case 2:
                G2();
                 print_list(8);
                
                 printf("시작 정점을 입력해주세요 : ");
                 scanf("%d", &k);
                 dfs_list(k);
                 printf("\n");
                
                break;
            case 3:
                G3();

                print_list(8);
               
                printf("시작 정점을 입력해주세요 : ");
                scanf("%d", &k);
                dfs_list(k);
                printf("\n");
              
                break;
            }
            break;
        }
        main_menu();
        scanf("%d", &num);
    }

    return 0;
}