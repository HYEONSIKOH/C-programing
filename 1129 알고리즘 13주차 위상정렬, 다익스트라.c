/*
1. 사이클이 없는 방향그래프를 인접리스트로 저장하고,
   임의의 정점에서 시작하는 깊이우선탐색(DFS)을 이용하여 위상정렬 순서를 구하는 프로그램을
   완성하시오. 추가의 예로, 아래의 그래프를 저장하고 테스트하시오.
   - (1) 연습문제 15의 그래프에 간선 3개를 더 추가해서 테스트하시오.
   - (2) 아래 그래프를 입력하고 테스트하시오.

2. 가중치를 갖는 유향그래프에서 다익스트라(Dijkstra) 알고리즘을 이용하여 임의 출발 정점에서
   다른 모든 정점에 이르는 최단경로를 구하는 프로그램을 완성하시오 (음의 가중치는 허용하지 않음).
   - (1) 교재 333쪽의 그래프에 각자 정점번호를 붙이고, 임의의 정점에서 시작하도록 한다.
   - (2) 연습문제 16번의 그래프를 입력하고 같은 방법으로 테스트한다.
   - (3) 모든 쌍의 정점에 대한 최단경로를 구하도록 위 알고리즘을 반복 수행하는 함수를 포함한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct list {
	int v;
	struct list* link;
}list;

typedef struct listtype {
	int n; // 정점 개수
	list* arr[MAX_VERTICES];
}listtype;

listtype G1;
int visit[MAX_VERTICES] = { 0, };

// 그래프 초기화
int Arr[8];
void init() {
	G1.n = 0;

    for (int v = 0; v < MAX_VERTICES; v++) {
        G1.arr[v] = NULL;
        visit[v] = FALSE;
        if (v < 9) Arr[v] = -1;
    }
}

// 정점 늘리기
void insert_vertex(int i) {
	G1.n++;
}

// 리스트 연결하기
void insert(int a, int b) {
    list* p = (list*)malloc(sizeof(list));
    p->v = b;
    p->link = NULL;

    list* node_before = NULL;

    // 이미 리스트 안에 같은 값이 있을 때!
    for (list* node = G1.arr[a]; node; node_before = node, node = node->link) if (node->v == b) return;

    if (node_before) node_before->link = p;
    else G1.arr[a] = p;
}

int c = 0;
int c1 = 0;
void insert_ans(int v) {
    for (int i = 0; i <= c; i++) 
        if (Arr[i] == v) return;
        
    Arr[c++] = v;
}

void print_ans() {
    for (int i = c-1; i >= c1; i--) printf("%d -> ", Arr[i]);
}

void Q1_init() {
    insert(1, 2);
    insert(2, 3);
    insert(2, 4);
    insert(2, 5);
    insert(5, 6);
    insert(5, 7);
    insert(6, 8);
    insert(7, 8);
    insert(4, 7);
    insert(3, 8);
}

void dfs_list(int s) {
    if (G1.arr[s] == NULL) insert_ans(s);
    
    if (!visit[s]) {
        visit[s] = TRUE;

        for (list* ptr = G1.arr[s]; ptr; ptr = ptr->link) {
            dfs_list(ptr->v);
        }
    }

    if(visit[s]) insert_ans(s);
}

// 다익스트라
#define MAX_VERTICES2 8
typedef struct GraphType2 {
    int n;
    int weight[MAX_VERTICES2][MAX_VERTICES2];
}GraphType2;

GraphType2 g1 = { 8, {{0,8,11,9,0,0,0,0},
              {0,0,0,0,10,0,0,0},
              {0,0,0,0,0,8,8,0},
              {0,6,3,0,1,0,0,0},
              {0,0,0,0,0,0,0,2},
              {0,0,0,0,0,0,7,0},
              {0,0,0,12,0,0,0,5},
              {0,0,0,0,0,4,0,0}} };

GraphType2 g2 = { 8, {{0,10,7,4,0,0,0,0},
              {0,0,0,0,8,0,0,0},
              {0,2,0,2,8,0,0,0},
              {0,0,0,0,0,0,8,20},
              {0,0,0,0,0,12,0,0},
              {0,0,0,0,0,0,0,4},
              {0,0,12,0,0,7,0,0},
              {0,0,0,0,0,0,3,0}} };

void graph_init() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!g2.weight[i][j]) g2.weight[i][j] = 100;
            if (!g1.weight[i][j]) g1.weight[i][j] = 100;
        }
    }
}


int distance[MAX_VERTICES2]; // 시작정점으로부터의 최단경로 거리
int Visit[MAX_VERTICES2]; // 방문한 정점 표시
int prev[MAX_VERTICES2];

// 가장 짧은 길이의 정점을 찾아내는 함수
int nextVertex(int n) { // n은 정점의 개수
    int min, minpos;
    min = INT_MAX;
    minpos = -1;

    for (int i = 0; i < n; i++)
        if (distance[i] < min && !Visit[i]) {
            min = distance[i];
            minpos = i;
        }

    return minpos;
}

int cnt = 1;

// 출력하는 함수
void printStep(GraphType2* g) {
    printf("[%d번째]\n", cnt++);
    printf("distance : ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == 100)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n   Visit : ");
    for (int i = 0; i < g->n; i++)
        printf("%2d ", Visit[i]);
    printf("\n    prev : ");
    for (int i = 0; i < g->n; i++) {
        if (prev[i] == -2) printf(" \033[0;32mS\033[0m ");
        else if (prev[i] != -1) printf("%2d ", prev[i]);
        else printf(" - ");
    }
    printf("\n----------------------------------\n");
}

void Dijkstra_shortestPath(GraphType2* g, int start) {
    int u, w;

    for (int i = 0; i < g->n; i++) prev[i] = -1;

    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        Visit[i] = FALSE;
        if (g->weight[start][i] != 100) prev[i] = start;
    }

    Visit[start] = TRUE;
    distance[start] = 0;
    prev[start] = -2;

    for (int i = 0; i < g->n - 1; i++) {
        printStep(g);
        u = nextVertex(g->n);
        Visit[u] = TRUE;

        for (w = 0; w < g->n; w++)
            if (!Visit[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    prev[w] = u;
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
    }

    printf("\n");
    for (int i = 0; i < g->n; i++) {
        if(distance[i] != 100) printf("%d의 최단경로 %2d\n", i, distance[i]);
        else printf("%d의 최단경로 --\n", i);
    }
}

void Dijkstra_NoPrint(GraphType2* g, int start) {
    int u, w;

    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        Visit[i] = FALSE;
    }

    Visit[start] = TRUE;
    distance[start] = 0;

    for (int i = 0; i < g->n - 1; i++) {
        u = nextVertex(g->n);
        Visit[u] = TRUE;

        for (w = 0; w < g->n; w++)
            if (!Visit[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
    }
}

void menu() {
    printf("\n==========[메인 메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 위상정렬\n");
    printf("2. 다익스트라\n");
    printf("===============================\n");
    printf("입력:");
}

int main() {
    menu();
    int num = 0, n, start;
    scanf("%d", &num);

    while (num){
        switch (num) {
        case 1:
            c = c1 = 0;
            init();
            for (int i = 0; i < 9; i++) insert_vertex(i + 1);
            Q1_init();
            
            printf("출발 정점을 입력하세요 : ");
            scanf("%d", &n);

            dfs_list(n);
            print_ans();

            c1 = c;
            for (int i = 1; i < n; i++) {
                if (!visit[i]) {        
                    dfs_list(i);
                }
            }
            print_ans();
            
            break;

        case 2:
            graph_init();
            cnt = 1;
            printf("그래프를 선택해주세요 : ");
            scanf("%d", &n);

            if (n == 1) {
                printf("출발 정점을 입력하세요 : ");
                scanf("%d", &start);
                Dijkstra_shortestPath(&g1, start);
                printf("\n");

                printf("\n======================================\n");
                for (int i = 0; i < 8; i++) {
                    printf("[Start : %d]\n", i);

                    Dijkstra_NoPrint(&g1, i);

                    printf("Distance : ");
                    for (int j = 0; j < 8; j++) {
                        if (distance[j] == 100) printf("-- ");
                        else if (distance[j] < 10) printf("0%d ", distance[j]);
                        else printf("%2d ", distance[j]);
                    }
                    printf("\n------------------------------------\n");
                }
            }

            if (n == 2) {
                printf("출발 정점을 입력하세요 : ");
                scanf("%d", &start);
                Dijkstra_shortestPath(&g2, start);
                printf("\n");

                printf("\n======================================\n");
                for (int i = 0; i < 8; i++) {
                    printf("[Start : %d]\n", i);
                    
                    Dijkstra_NoPrint(&g2, i);
                    
                    printf("Distance : ");
                    for (int j = 0; j < 8; j++) {
                        if (distance[j] == 100) printf("-- ");
                        else if (distance[j] < 10) printf("0%d ", distance[j]);
                        else printf("%2d ", distance[j]);
                    }
                        printf("\n------------------------------------\n");
                }
            }
        }
        menu();
        scanf("%d", &num);
    }
}




