/*
1. ������ ������ ������ ������ �Է��ϸ�, ������ ������ �׷����� �����ϴ� ���α׷���
   �ۼ��Ͻÿ� (����׷��� ���θ� ������ �� �ֵ���).
   (1) ������ �׷����� ������ķ� �����Ͻÿ�
   (2) ������ �׷����� ��������Ʈ�� �����Ͻÿ�.

2. ���Ƿ� ������ �׷������� �ʺ�켱Ž��(BFS)�� �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
   (1) ������Ŀ���
   (2) �����׷�������

3. ���Ƿ� ������ ����ġ�� ���� ����׷�������, Prim�� �˰������� �ּҽ���Ʈ��(MST)
   �� ���ϴ� ���α׷��� �ۼ��Ͻÿ� (������� �Ǵ� ��������Ʈ �� ����).
   - ���� 314��, �˰��� 10-4 ����.
   - ���� Q ��� �̹� ���õ� �������� �����ϴ� �迭�� ������ �� ����.
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
	int n; // ������ ����
    int arr[MAX_SIZE][MAX_SIZE];
}matrixType;

typedef struct list {
    int cur; // ���� ����
    int cost; // ���
    struct list* link;
}list;

typedef struct {
    int n; // ������ ����
    list *arr[MAX_SIZE];
}listType;

matrixType G1;
listType G2;

// ����Ʈ �����ϱ�
int insert(int a, int b, int cost) {
    list* p = (list*)malloc(sizeof(list));
    p->cur = b;
    p->cost = cost;
    p->link = NULL;

    list* node_before = NULL;

    // �̹� ����Ʈ �ȿ� ���� ���� ���� ��!
    for (list* node = G2.arr[a]; node; node_before = node, node = node->link) if (node->cur == b) return 0;

    if (node_before) node_before->link = p;
    else G2.arr[a] = p;

    return 1;
}

int N, M; // N : ���� ����, M : ���� ����


// ===================== [1�� �Լ�] =====================
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
            printf("{����: %d ���: %2d} ", ptr->cur, ptr->cost);
            if (ptr->link) printf("-> ");
        }

        printf("\n");
    }
}

// ===================== [2�� �Լ�] =====================
#define MAX_QUEUE_SIZE  20

typedef struct { // ť Ÿ��
    int data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// ���� �Լ�
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void push(QueueType* q, int item) {
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
int pop(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// ���� �Լ�
int front(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�");

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


// ===================== [3�� �Լ�] =====================
int dist[100];

int get_min_v(int n) {
    int v;
    for (int i = 0; i < n; i++) {
        if (!visit[i]) {
            v = i; // ���� ��
            break;
        }
    }

    for (int i = 0; i < n; i++)
        if (!visit[i] && (dist[i] < dist[v])) v = i; // �Ÿ��� ���� ���� ã��!

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
            printf("\n�ּ� ���д� Ʈ���� �������մϴ�.\n");
            return 0;
        }

        visit[u] = 1;

        printf("%d -> ", u);

        // DFS Ž��
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
            printf("\n�ּ� ���д� Ʈ���� �������մϴ�.\n");
            return 0;
        }

        visit[u] = 1;

        printf("%d -> ", u);

        // DFS Ž��
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

    printf("\n�� ��� : %d", ans);
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
    printf("\n==========[���� �޴�]==========\n");
    printf("0. ����\n");
    printf("1. ���\n");
    printf("2. ����Ʈ\n");
    printf("===============================\n");
    printf("�Է�:");
}

int main() {
    menu();
    int num = 0;
    int n;
    int k;
    scanf("%d", &num);

    while (num) {
        printf("������ ������ ������ ������ �Է����ּ��� : ");
        scanf("%d %d", &N, &M);

        switch (num) {
        case 1:
            Random_matrix();
            print_matrix();
            printf("\n\n");

            printf("������ ���� ��ġ�� ���ϼ���: ");
            scanf("%d", &n);

            printf("\n============ [BFS] ============ ");
            matrix_bfs(n);
            printf("\n=============================== ");

            printf("\n\n���� : ");
            k = matrix_prim(n);
            
            print_visit();
            if (k == 1) print_dist();
            break;

        case 2:
            Random_list();
            print_list();
            printf("\n\n");

            printf("������ ���� ��ġ�� ���ϼ���: ");
            scanf("%d", &n);

            printf("\n============ [BFS] ============ ");
            list_bfs(n);
            printf("\n=============================== ");

            printf("\n\n���� : ");
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



