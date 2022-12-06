/*
1. ������ ����� ä���� 5*5 ����� �����ϰ�, ��� ��ι����� �������α׷������� �ϼ��Ͻÿ�.

2. �� ���� 1�� ���ȣ��� �����ؼ� ���� Ȯ���ϰ�, ȣ���� ��� �� �� �߻��ߴ����� Ȯ���Ͻÿ�.

3. �� 1�� ���� ��Ŀ���, ���� 290�� �������� 06�� �������α׷��� ������� �ϼ��Ͻÿ�.

4. 3*n ���̺��� ������ ������ ������ ������ ä���, �� ���� ������ ���� ���α׷�������
   �ϼ��Ͻÿ�.

5. ���� 294�� �������� 17�� �������α׷��� ������� �ϼ��Ͻÿ�.

6. N�� ����� �ö󰡷��� �Ѵ�. �Ź� ����� 1ĭ �Ǵ� 3ĭ�� �ö� �� �ִ�.
   �� ������ �ö� �� �ִ� ����� ���� �� ������ ���ϴ� ���α׷��� ���� ���α׷��� �������
   �ϼ��Ͻÿ�.

7. ��� ��ü������ 80��¥��, 50��¥��, 10��¥�� ��ǥ�� �ִ�.

   - (1) Ư�� �ݾ��� �������� ���� ����ϴ� �ּ� ������ ��ǥ ������ �������α׷�������
         ���Ͻÿ�. (10, 20, 30, 40, 50 �� 300���� ����� �ּ� ��ǥ ������ ���ϴ� ǥ�� �ϼ��Ͻÿ�).
         ���û�������, ������ �ذ� �� ��ǥ�� �� �徿 ����ϴ����� ����Ͻÿ�.
   - (2) ����, ��ü�� ������ �׸��� �˰����� �����Ѵٸ� � �������� ��ǥ���� �ް� �Ǵ���
         ����ϴ� ���α׷��� �ۼ��ϰ�, �� ����� ������ ������� (1)�� ���Ͻÿ�.

   �Է�: ������ n, k �� ��ǥ�� �׸� d1>d2> .. > dk=10
   ���: C[n
    for i=1 to n C[i]= ��
    C[0]=0
    for j=1 to n { // j=1�� 10��, j=2�� 20�� ��
    for i=1 to k { // �׸��� ���� ���� ��ǥ���� 10��¥�� ��ǥ���� ���ʷ�.
    if (di<=j) and (C[j-di]+1 < C[j])
      C[j]=C[j-di]+1
      }
    }
    return C[n]
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5

int arr[MAX][MAX] = { {0,0,0,0,0}, {0,6,7,12,8}, {0,5,3,11,18}, {0,7,17,3,3}, {0,8,10,14,9} };
int dp[MAX][MAX] = { 0 };

void init_dp() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dp[i][j] = 0;
        }
    }
}

void print_dp() {
    for (int i = 1; i < MAX; i++) {
        for (int j = 1; j < MAX; j++) {
            printf("[%2d] ", dp[i][j]);
        }
        printf("\n");
    }
}

void Q1() {
    dp[1][1] = arr[1][1];
    for (int i = 1; i < MAX; i++) {
        for (int j = 1; j < MAX; j++) {
            int cost = arr[i][j];
            dp[i][j] = max(dp[i][j - 1] + cost, dp[i - 1][j] + cost);
        }
    }
}

int range(int y, int x) {
    if (y >= 0 && x >= 0 && x < 5 && y < 5) return 1;
    else return 0;
}

int count = 0;
int Q2(int y,int x) {
    count++;
    if (x == 0 || y == 0) return 0;
    else {
        int cost = arr[y][x];
        dp[y][x] = cost + max(Q2(y - 1, x), Q2(y, x - 1));
        return dp[y][x];
    }
}

void Q3() {
    dp[0][0] = arr[0][0];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            int cost = arr[i][j];
            if (i == 0) dp[i][j] = max(cost, dp[i][j - 1] + cost);
            else if (j == 0) dp[i][j] = max(cost, dp[i - 1][j] + cost);
            else if (i != 0 && j != 0) dp[i][j] = max(dp[i][j - 1] + cost, max(dp[i - 1][j] + cost, dp[i - 1][j - 1] + cost));
        }
    }
}

int table[3][100];
// { {6,7,12,-5,5,3,11,3},{-8,10,14,9,7,13,8,5},{11,12,7,4,8,-2,9,4} }
int dp_Q4[4][100] = { 0 };
void Q4() {
    printf("N�� �Է��ϼ���: ");
    int N;
    scanf("%d", &N);

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            table[i][j] = rand() % 50 - 25;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            printf("[%3d] ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    dp_Q4[0][0] = table[0][0];
    dp_Q4[1][0] = table[1][0];
    dp_Q4[2][0] = table[2][0];
    dp_Q4[3][0] = table[0][0] + table[2][0];

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            int cost = table[j][i];
            if (j == 0) dp_Q4[j][i] = max(dp_Q4[1][i - 1] + cost, dp_Q4[2][i - 1] + cost);
            if (j == 1) dp_Q4[j][i] = max(dp_Q4[0][i - 1], max(dp_Q4[2][i - 1] + cost, dp_Q4[3][i - 1] + cost));
            if (j == 2) dp_Q4[j][i] = max(dp_Q4[1][i - 1] + cost, dp_Q4[0][i - 1] + cost);
            if (j == 3) dp_Q4[j][i] = dp_Q4[1][i - 1] + table[2][i] + table[0][i];
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N; j++) {
            printf("[%3d] ", dp_Q4[i][j]);
        }
        printf("\n");
    }
}

int dp_Q5[100];
void Q5() {
    printf("N�� �Է��ϼ���: ");
    int N;
    scanf("%d", &N);

    dp_Q5[1] = 1, dp_Q5[2] = 2;

    for (int i = 3; i <= N; i++) dp_Q5[i] = dp_Q5[i - 1] + dp_Q5[i - 2];

    for (int j = 1; j <= N; j++) printf("%d ", dp_Q5[j]);

    printf("\n\n����� �� : %d\n", dp_Q5[N]);
}

int dp_Q6[100];
void Q6() {
    printf("N�� �Է��ϼ���: ");
    int N;
    scanf("%d", &N);
    
    dp_Q6[1] = 1, dp_Q6[2] = 1, dp_Q6[3] = 2;

    for (int i = 4; i <= N; i++) dp_Q6[i] = dp_Q6[i - 3] + dp_Q6[i - 1];

    for (int j = 1; j <= N; j++) printf("%d ", dp_Q6[j]);

    printf("\n\n����� �� : %d\n", dp_Q6[N]);
}
#define STAMP_SIZE 31
int s[5][STAMP_SIZE];

int d[] = { 0,80,50,10 };
void Q7_DP(int n) {
    for (int i = 0; i < STAMP_SIZE; i++)
        s[0][i] = 10 * i;

    for (int i = 0; i < 5; i++)
        s[i][0] = 0;

    for (int i = 1; i < STAMP_SIZE; i++)
        s[4][i] = 9999;

    int index = n / 10;

    for (int i = 1; i <= index; i++) {
        for (int j = 1; j <= 3; j++) {
            if (d[j] <= s[0][i] && s[4][i - (d[j] / 10)] + 1 < s[4][i]) {

                s[4][i] = s[4][i - (d[j] / 10)] + 1; // ��ǥ �� ����

                s[3][i] = s[3][i - (d[j] / 10)]; // 10��¥��
                s[2][i] = s[2][i - (d[j] / 10)]; // 50��¥��
                s[1][i] = s[1][i - (d[j] / 10)]; // 80��¥��
                s[j][i]++;
            }
        }
    }
    printf("-------------------------\n");
    printf("[%d�� DP] �� %d�� => 80��: %2d�� || 50��: %2d�� || 10��: %2d��\n", s[0][index], s[4][index], s[1][index], s[2][index], s[3][index]);
}

void Q7_Greedy(int n) {
    int cost = n;
    int a, b, c;
    
    if (n < d[1]) c = 0;
    else {
        c = n / d[1];
        n %= d[1];
    }

    if (n < d[2]) b = 0;
    else {
        b = n / d[2];
        n %= d[2];
    }

    if (n < d[3]) a = 0;
    else {
        a = n / d[3];
        n %= d[3];
    }
    
    int cnt = a + b + c;

    printf("-------------------------\n");
    printf("[%d�� �׸���] �� %d�� => 80��: %2d�� || 50��: %2d�� || 10��: %2d��\n", cost, cnt, c, b, a);
}

void menu() {
    printf("\n==========[���� �޴�]==========\n");
    printf("0. ����\n");
    printf("1. ��� ��ι��� - �ݺ���\n");
    printf("2. ��� ��ι��� - ��͹�\n");
    printf("3. ��� ��ι��� - �밢�� ����\n");
    printf("4. ������ ����\n");
    printf("5. 2 * 1 ��\n");
    printf("6. ��� �ö󰡱� (1ĭ, 3ĭ)\n");
    printf("7. ��ǥ\n");
    printf("===============================\n");
    printf("�Է�:");
}

int main() {
    int num = -1;
    int cost;
    menu();
    scanf("%d", &num);

    while (num) {
        init_dp();
        switch (num) {
        case 1:
            Q1();
            print_dp();
            break;
        case 2:
            Q2(5,5);
            printf("��� �ҷ��� Ƚ�� : %d\n", count);
            count = 0;
            print_dp();
            break;

        case 3:
            Q3();
            print_dp();
            break;

        case 4:
            Q4();
            break;
        
        case 5:
            Q5();
            break;
        
        case 6:
            Q6();
            break;
        
        case 7:
            printf("�ݾ��� �Է����ּ���: ");
            scanf("%d", &cost);
            Q7_DP(cost);
            Q7_Greedy(cost);
            break;
        }
        menu();
        scanf("%d", &num);
    }
}
