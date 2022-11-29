/*
1. ����Ŭ�� ���� ����׷����� ��������Ʈ�� �����ϰ�,
   ������ �������� �����ϴ� ���̿켱Ž��(DFS)�� �̿��Ͽ� �������� ������ ���ϴ� ���α׷���
   �ϼ��Ͻÿ�. �߰��� ����, �Ʒ��� �׷����� �����ϰ� �׽�Ʈ�Ͻÿ�.
   - (1) �������� 15�� �׷����� ���� 3���� �� �߰��ؼ� �׽�Ʈ�Ͻÿ�.
   - (2) �Ʒ� �׷����� �Է��ϰ� �׽�Ʈ�Ͻÿ�.

2. ����ġ�� ���� ����׷������� ���ͽ�Ʈ��(Dijkstra) �˰����� �̿��Ͽ� ���� ��� ��������
   �ٸ� ��� ������ �̸��� �ִܰ�θ� ���ϴ� ���α׷��� �ϼ��Ͻÿ� (���� ����ġ�� ������� ����).
   - (1) ���� 333���� �׷����� ���� ������ȣ�� ���̰�, ������ �������� �����ϵ��� �Ѵ�.
   - (2) �������� 16���� �׷����� �Է��ϰ� ���� ������� �׽�Ʈ�Ѵ�.
   - (3) ��� ���� ������ ���� �ִܰ�θ� ���ϵ��� �� �˰����� �ݺ� �����ϴ� �Լ��� �����Ѵ�.
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
	int n; // ���� ����
	list* arr[MAX_VERTICES];
}listtype;

listtype G1;
int visit[MAX_VERTICES] = { 0, };

// �׷��� �ʱ�ȭ
int Arr[8];
void init() {
	G1.n = 0;

    for (int v = 0; v < MAX_VERTICES; v++) {
        G1.arr[v] = NULL;
        visit[v] = FALSE;
        if (v < 9) Arr[v] = -1;
    }
}

// ���� �ø���
void insert_vertex(int i) {
	G1.n++;
}

// ����Ʈ �����ϱ�
void insert(int a, int b) {
    list* p = (list*)malloc(sizeof(list));
    p->v = b;
    p->link = NULL;

    list* node_before = NULL;

    // �̹� ����Ʈ �ȿ� ���� ���� ���� ��!
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

// ���ͽ�Ʈ��
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


int distance[MAX_VERTICES2]; // �����������κ����� �ִܰ�� �Ÿ�
int Visit[MAX_VERTICES2]; // �湮�� ���� ǥ��
int prev[MAX_VERTICES2];

// ���� ª�� ������ ������ ã�Ƴ��� �Լ�
int nextVertex(int n) { // n�� ������ ����
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

// ����ϴ� �Լ�
void printStep(GraphType2* g) {
    printf("[%d��°]\n", cnt++);
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
        if(distance[i] != 100) printf("%d�� �ִܰ�� %2d\n", i, distance[i]);
        else printf("%d�� �ִܰ�� --\n", i);
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
    printf("\n==========[���� �޴�]==========\n");
    printf("0. ����\n");
    printf("1. ��������\n");
    printf("2. ���ͽ�Ʈ��\n");
    printf("===============================\n");
    printf("�Է�:");
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
            
            printf("��� ������ �Է��ϼ��� : ");
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
            printf("�׷����� �������ּ��� : ");
            scanf("%d", &n);

            if (n == 1) {
                printf("��� ������ �Է��ϼ��� : ");
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
                printf("��� ������ �Է��ϼ��� : ");
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




