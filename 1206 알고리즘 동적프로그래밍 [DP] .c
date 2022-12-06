/*
1. 임의의 양수로 채워진 5*5 행렬을 생성하고, 행렬 경로문제를 동적프로그래밍으로 완성하시오.

2. 위 문제 1을 재귀호출로 구현해서 답을 확인하고, 호출이 모두 몇 번 발생했는지도 확인하시오.

3. 위 1과 같은 행렬에서, 교재 290쪽 연습문제 06을 동적프로그래밍 방법으로 완성하시오.

4. 3*n 테이블을 음수를 포함한 임의의 정수로 채우고, 돌 놓기 문제를 동적 프로그래밍으로
   완성하시오.

5. 교재 294쪽 연습문제 17을 동적프로그래밍 방법으로 완성하시오.

6. N개 계단을 올라가려고 한다. 매번 계단을 1칸 또는 3칸을 올라갈 수 있다.
   맨 위까지 올라갈 수 있는 방법의 수는 몇 개인지 구하는 프로그램을 동적 프로그래밍 방법으로
   완성하시오.

7. 어느 우체국에는 80원짜리, 50원짜리, 10원짜리 우표가 있다.

   - (1) 특정 금액의 우편요금을 위해 사용하는 최소 개수의 우표 개수를 동적프로그래밍으로
         구하시오. (10, 20, 30, 40, 50 … 300원을 만드는 최소 우표 개수를 구하는 표를 완성하시오).
         선택사항으로, 최적의 해가 각 우표를 몇 장씩 사용하는지도 출력하시오.
   - (2) 만약, 우체국 직원이 그리디 알고리즘을 적용한다면 어떤 조합으로 우표들을 받게 되는지
         계산하는 프로그램을 작성하고, 그 결과가 최적의 결과인지 (1)과 비교하시오.

   입력: 우편요금 n, k 개 우표의 액면 d1>d2> .. > dk=10
   출력: C[n
    for i=1 to n C[i]= ∞
    C[0]=0
    for j=1 to n { // j=1은 10원, j=2은 20원 …
    for i=1 to k { // 액면이 가장 높은 우표부터 10원짜리 우표까지 차례로.
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
    printf("N을 입력하세요: ");
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
    printf("N을 입력하세요: ");
    int N;
    scanf("%d", &N);

    dp_Q5[1] = 1, dp_Q5[2] = 2;

    for (int i = 3; i <= N; i++) dp_Q5[i] = dp_Q5[i - 1] + dp_Q5[i - 2];

    for (int j = 1; j <= N; j++) printf("%d ", dp_Q5[j]);

    printf("\n\n경우의 수 : %d\n", dp_Q5[N]);
}

int dp_Q6[100];
void Q6() {
    printf("N을 입력하세요: ");
    int N;
    scanf("%d", &N);
    
    dp_Q6[1] = 1, dp_Q6[2] = 1, dp_Q6[3] = 2;

    for (int i = 4; i <= N; i++) dp_Q6[i] = dp_Q6[i - 3] + dp_Q6[i - 1];

    for (int j = 1; j <= N; j++) printf("%d ", dp_Q6[j]);

    printf("\n\n경우의 수 : %d\n", dp_Q6[N]);
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

                s[4][i] = s[4][i - (d[j] / 10)] + 1; // 우표 총 개수

                s[3][i] = s[3][i - (d[j] / 10)]; // 10원짜리
                s[2][i] = s[2][i - (d[j] / 10)]; // 50원짜리
                s[1][i] = s[1][i - (d[j] / 10)]; // 80원짜리
                s[j][i]++;
            }
        }
    }
    printf("-------------------------\n");
    printf("[%d원 DP] 총 %d장 => 80원: %2d개 || 50원: %2d개 || 10원: %2d개\n", s[0][index], s[4][index], s[1][index], s[2][index], s[3][index]);
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
    printf("[%d원 그리디] 총 %d장 => 80원: %2d개 || 50원: %2d개 || 10원: %2d개\n", cost, cnt, c, b, a);
}

void menu() {
    printf("\n==========[메인 메뉴]==========\n");
    printf("0. 종료\n");
    printf("1. 행렬 경로문제 - 반복문\n");
    printf("2. 행렬 경로문제 - 재귀문\n");
    printf("3. 행렬 경로문제 - 대각선 포함\n");
    printf("4. 돌놓기 문제\n");
    printf("5. 2 * 1 블럭\n");
    printf("6. 계단 올라가기 (1칸, 3칸)\n");
    printf("7. 우표\n");
    printf("===============================\n");
    printf("입력:");
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
            printf("재귀 불러온 횟수 : %d\n", count);
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
            printf("금액을 입력해주세요: ");
            scanf("%d", &cost);
            Q7_DP(cost);
            Q7_Greedy(cost);
            break;
        }
        menu();
        scanf("%d", &num);
    }
}
