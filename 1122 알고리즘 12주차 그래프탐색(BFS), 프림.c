/*
1. 정점의 개수와 간선의 개수를 입력하면, 임의의 무방향 그래프를 생성하는 프로그램을
   작성하시오 (연결그래프 여부를 선택할 수 있도록).
   (1) 생성된 그래프를 인접행렬로 저장하시오
   (2) 생성된 그래프를 인접리스트로 저장하시오.

2. 임의로 생성된 그래프에서 너비우선탐색(BFS)을 실행하는 프로그램을 작성하시오.
   (1) 인접행렬에서
   (2) 인접그래프에서

3. 임의로 생성된 가중치를 갖는 연결그래프에서, Prim의 알고리즘으로 최소신장트리(MST)
   를 구하는 프로그램을 작성하시오 (인접행렬 또는 인접리스트 중 선택).
   - 교재 314쪽, 알고리즘 10-4 참조.
   - 집합 Q 대신 이미 선택된 정점인지 구분하는 배열로 구현할 수 있음.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 21
#define true 1
#define false 0
#define INF 987654321

typedef struct {
	int n; // 정점의 개수
    int arr[MAX_SIZE][MAX_SIZE];
}matrixType;

typedef struct list {
    int cur; // 도착 정점
    int cost; // 비용
    struct list* link;
}list;

typedef struct {
    int n; // 정점의 개수
    list *arr[MAX_SIZE];
}listType;

matrixType G1;
listType G2;

// 리스트 연결하기
int insert(int a, int b, int cost) {
    list* p = (list*)malloc(sizeof(list));
    p->cur = b;
    p->cost = cost;
    p->link = NULL;

    list* node_before = NULL;

    // 이미 리스트 안에 같은 값이 있을 때!
    for (list* node = G2.arr[a]; node; node_before = node, node = node->link) if (node->cur == b) return 0;

    if (node_before) node_before->link = p;
    else G2.arr[a] = p;

    return 1;
}

int N, M; // N : 정점 개수, M : 간선 개수


// ===================== [1번 함수] =====================
void Random_matrix() {
    G1.n = N;

    int a, b, cost;
    srand(time(NULL));
    for (int i = 0; i < M; i++) {
        a = rand() % (N);
        b = rand() % (N);
        while (a == b) b = rand() % (N);
        cost = rand() % 30;
        while (!cost) cost = rand() % 30;
        
        /*while (G1.arr[a][b]) {
            a = rand() % (N - 1);
            b = rand() % (N - 1);
            while (a == b) b = rand() % (N - 1);
        }
        printf("%d %d %d\n", a, b, cost);*/
        G1.arr[a][b] = cost;
        G1.arr[b][a] = cost;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (!G1.arr[i][j]) G1.arr[i][j] = INF;
        }
    }

    for (int i = 0; i < M; i++) G1.arr[i][i] = 0;
    printf("\n");
}

void Random_list() {
    G2.n = N;

    int a, b, cost;
    srand(time(NULL));
    for (int i = 0; i < M; i++) {
        a = rand() % (N);
        b = rand() % (N );
        while(a == b) b = rand() % (N);
        cost = rand() % 30;
        while (!cost) cost = rand() % 30;

        /*while (!insert(a, b, cost)) {
            a = rand() % (N - 1);
            b = rand() % (N - 1);
            while (a == b) b = rand() % (N - 1);
        }*/
        insert(a, b, cost);
        insert(b, a, cost);
    }
}

void print_matrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(G1.arr[i][j] == INF) printf("%2d ", 0);
            else printf("%2d ", G1.arr[i][j]);
        }
        printf("\n");
    }
}

void print_list() {
    for (int i = 0; i < N; i++) {
        printf("[%2d] -> ", i);

        for (list* ptr = G2.arr[i]; ptr; ptr = ptr->link) {
            printf("{정점: %d 비용: %2d} ", ptr->cur, ptr->cost);
            if (ptr->link) printf("-> ");
        }

        printf("\n");
    }
}

// ===================== [2번 함수] =====================
#define MAX_QUEUE_SIZE  20

typedef struct { // 큐 타입
    int data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 오류 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void push(QueueType* q, int item) {
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
int pop(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 참조 함수
int front(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다");

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void clear(QueueType* q) {
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) q->data[i] = NULL;
}

QueueType q;

int visit[MAX_SIZE] = { 0, };
void matrix_bfs(int x) {
    printf("\n");
    push(&q, x);
    visit[x] = 1;
    printf("%d -> ", x);

    while (is_empty(&q) == 0) {
        int front = pop(&q);

        for (int i = 0; i < N; i++) {
            if (G1.arr[front][i] != INF && G1.arr[front][i] != 0) {
                if (visit[i] == 0) {
                    push(&q, i);
                    visit[i] = 1;
                    printf("%d -> ", i);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) if (!visit[i]) matrix_bfs(i);
}

void list_bfs(int x) {
    printf("\n");
    visit[x] = 1;
    push(&q, x);
    printf("%d -> ", x);

    while (is_empty(&q) == 0) {
        int front = pop(&q);

        list* node_before = NULL;

        for (list* node = G2.arr[front]; node; node_before = node, node = node->link) {
            if (visit[node->cur] != 1) {
                push(&q, node->cur);
                visit[node->cur] = 1;
                printf("%d ", node->cur);
                printf("-> ");
            }
        }
    }
    for (int i = 0; i < N; i++) if (!visit[i]) list_bfs(i);
}

void init() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            G1.arr[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        G2.arr[i] = NULL;
        visit[i] = 0;
    }
}


// ===================== [3번 함수] =====================
int dist[100];

int get_min_v(int n) {
    int v;
    for (int i = 0; i < n; i++) {
        if (!visit[i]) {
            v = i; // 기준 점
            break;
        }
    }

    for (int i = 0; i < n; i++)
        if (!visit[i] && (dist[i] < dist[v])) v = i; // 거리가 작은 정점 찾기!

    return v;
}

int matrix_prim(int s) {
    int u, size = G1.n;

    for (int i = 0; i < size; i++) {
        dist[i] = INF;
        visit[i] = 0;
    }
    dist[s] = 0;

    for (int i = 0; i < size; i++) {
        u = get_min_v(size);

        if (dist[u] == INF) {
            printf("\n최소 스패닝 트리에 부적합합니다.\n");
            return 0;
        }

        visit[u] = 1;

        printf("%d -> ", u);

        // DFS 탐색
        for (int v = 0; v < size; v++) {
            if (G1.arr[u][v] != INF && G1.arr[u][v] != 0) {
                if (!visit[v] && G1.arr[u][v] < dist[v]) {
                    dist[v] = G1.arr[u][v];
                }
            }
        }
    }

    return 1;
}

int list_prim(int s) {
    int u, size = G2.n;

    for (int i = 0; i < size; i++) {
        dist[i] = INF;
        visit[i] = 0;
    }

    dist[s] = 0;

    for (int i = 0; i < size; i++) {
        u = get_min_v(size);

        if (dist[u] == INF) {
            printf("\n최소 스패닝 트리에 부적합합니다.\n");
            return 0;
        }

        visit[u] = 1;

        printf("%d -> ", u);

        // DFS 탐색
        list* node_before = NULL;
        for (list* node = G2.arr[u]; node; node_before = node, node = node->link) {
            if (!visit[node->cur] && node->cost < dist[node->cur]) {
                dist[node->cur] = node->cost;
            }
        }
    }

    return 1;
}

void print_dist() {
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if(dist[i] == INF) printf("[%d] :%2d", i, 0);
        else {
            printf("[%d] :%2d", i, dist[i]);
            ans += dist[i];
        }
        if (i != N - 1) printf(" || ");
    }

    printf("\n총 비용 : %d", ans);
    printf("\n");
}

void print_visit() {
    printf("\n");
    for (int i = 0; i < N; i++) {
        if(visit[i] != 0) printf("[%d] : \033[0;32mT\033[0m", i);
        else printf("[%d] : \033[0;31mF\033[0m", i);

        if(i != N-1) printf(" || ");
    }
    printf("\n");
}

void menu() {
    printf("\n==========[메인 메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 행렬\n");
    printf("2. 리스트\n");
    printf("===============================\n");
    printf("입력:");
}

int main() {
    menu();
    int num = 0;
    int n;
    int k;
    scanf("%d", &num);

    while (num) {
        printf("정점의 개수와 간선의 개수를 입력해주세요 : ");
        scanf("%d %d", &N, &M);

        switch (num) {
        case 1:
            Random_matrix();
            print_matrix();
            printf("\n\n");

            printf("시작할 정점 위치를 정하세요: ");
            scanf("%d", &n);

            printf("\n============ [BFS] ============ ");
            matrix_bfs(n);
            printf("\n=============================== ");

            printf("\n\n프림 : ");
            k = matrix_prim(n);
            
            print_visit();
            if (k == 1) print_dist();
            break;

        case 2:
            Random_list();
            print_list();
            printf("\n\n");

            printf("시작할 정점 위치를 정하세요: ");
            scanf("%d", &n);

            printf("\n============ [BFS] ============ ");
            list_bfs(n);
            printf("\n=============================== ");

            printf("\n\n프림 : ");
            k = list_prim(n);
            
            print_visit();
            if (k == 1) print_dist();
        }

        init();
        menu();
        scanf("%d", &num);
    }

    return 0;
}



