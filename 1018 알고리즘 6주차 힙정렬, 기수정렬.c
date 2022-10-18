/*
1. 교재 113쪽 알고리즘 4-7, 117쪽 알고리즘 4-8을 참조하여 힙(heap) 정렬 프로그램을 작성하시오. (최대힙을 이용하여, 오름차순 정렬을 수행한다)
    - 임의의 n개 정수 값을 갖는 배열을 입력으로 한다.
    - buildHeap( ) 을 수행하면서 중간과정에서 교환되는 값들을 출력으로 보이고,
      완성된 초기 힙을 출력한다.
    - 힙 정렬을 진행하면서 그 과정을 차례로 출력으로 보여준다.
     (힙 크기가 줄면서 재정비되는 중간 힙의 내용들을 단계별로 출력한다)

2. 힙의 중요한 응용인 우선순위 큐를 구현하시오(대기, 삭제, 삽입 구현).
   - 최대 n개 데이터가 대기할 수 있고(초기 상태는 0개),
     가장 큰 값이 가장 먼저 나갈 수 있도록 항상 최대힙 상태를 유지하며,
   - 언제든지 최대값이 나가고 나면, 크기가 1 감소한 최대힙으로 재구성한다.
   - 언제든지 새로운 데이터가 들어오면, 크기가 1 증가한 최대힙으로 재구성한다.

3. n개의 다섯자리 8진수들을 기수정렬(Radix sort)하는 프로그램을 작성하시오.
   8진수이므로 0~7 각 자리값들을 분류해서 모을 수 있는 버킷을 사용한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[10000] = { 0, };
int size = 0;

void swap(int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void menu() {
    printf("=================== [메뉴] ===================\n");
    printf("1. 힙 정렬\n");
    printf("2. 우선순위 큐\n");
    printf("3. 기수 정렬\n");
    printf("0. 종료\n");
    printf("==============================================\n");
    printf("입력 : ");
}

void resize_arr() {
    printf("크기 입력 : ");
    scanf("%d", &size);
    for (int i = 1; i <= size; i++) arr[i] = rand() % 100 + 1;
}

void resize_arr2() {
    printf("크기 입력 : ");
    scanf("%d", &size);
    printf("정렬할 수를 크기만큼 입력하세요 : ");
    for (int i = 0; i < size; i++) scanf("%d", &arr[i]);
}

void print_Radix(int x) {
    int cnt = 0;
    while (x != 1) {
        x /= 10;
        cnt++;
    }
    
    char str[1000][5];
    for (int i = 0; i < size; i++) {
        sprintf(str[i], "%d", arr[i]);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 5 - (cnt + 1)) printf("\033[0;32m%c\033[0m", str[i][j]);
            else printf("%c", str[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void clear_arr() {
    for (int i = 0; i < 10000; i++) arr[i] = 0;
    size = 0;
}

// =========================== 1번함수

// arr[1....n]을 힙으로 만든다.
void heapify(int k,int n) { 
    int left = 2 * k, right = (2 * k) + 1;
    int larger;

    // 큰 자식 고르기, larger : arr[2k]와 arr[2k+1]중에 큰 원소
    if (right <= n) larger = (arr[left] < arr[right]) ? right : left; // k가 두 자식을 가지는 경우
    else if (left <= n) larger = left;  // k의 왼쪽 자식만 잇는 경우
    else return;                        // arr[k]가 리프 노드일 경우, 끝난거다.

    // 만약 자식들 중, 가장 큰 값이 arr[k]값보다 큰 경우, 스왑하고 한번 더 최대힙인지 검사!
    if (arr[larger] >= arr[k]) {
        swap(larger, k);
        heapify(larger, n);
    }
}

void buildHeap() {
    for (int i = size / 2; i > 0; i--) heapify(i,size);
}

// arr[1...n]을 정렬한다.
void heapSort() {
    printf("정렬 전 : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf("\n");

    buildHeap(); // 최대 힙 만들기!

    printf("\n최대 힙 : ");
    for (int i = 1; i <= size; i++) printf("\033[0;36m%d\033[0m ", arr[i]);
    printf("\n");

    for (int i = size; i > 0; i--) {
        swap(1, i); // 가장 큰 값은 맨 뒤로 보내기!

        // 출력 ==========================================
        printf("   정렬 : ");
        for (int j = 1; j <= size; j++) {
            if (j >= i) printf("\033[0;32m%d\033[0m ", arr[j]);
            else printf("%d ", arr[j]);
        }
        printf("\n");

        heapify(1, i - 1);

        // 출력 ==========================================
        if (i != 1) {
            printf("\n최대 힙 : ");
            for (int j = 1; j <= size; j++) {
                if (j <= i - 1) printf("\033[0;36m%d\033[0m ", arr[j]);
                else printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }

    printf("\n정렬 후: ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf("\n");
}

// =========================== 2번함수
int Size;

void insert_max_heap() {
    printf("입력 : ");
    size++;
    scanf("%d", &arr[size]);
    Size = size;

    while (Size != 1) {
        heapify(Size / 2, Size);
        Size /= 2;
    }

    printf("현재 우선순위 큐 : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" 크기 : %d", size);
    printf("\n");
}

void delete_max_heap() {
    swap(1, size);
    size--;

    heapify(1, size);

    printf("현재 우선순위 큐 : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" 크기 : %d", size);
    printf("\n");
}

void show_heap() {
    printf("현재 우선순위 큐 : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" 크기 : %d", size);
    printf("\n");
}


// =========================== 3번함수

void Radixsort() {
    int x = 1;
    int* result = malloc(sizeof(int) * (size)); // 기수대로 정렬 한 후, 임시로 저장하는 공간
   
    for(int index = 0; index <5; index++) {
        int bucket[10] = { 0, }; // 각 자리 수가 몇개 있는지 계산
        
        for (int i = 0; i < size; i++) bucket[(arr[i] / x) % 10]++;

        for (int i = 1; i < 10; i++) bucket[i] += bucket[i - 1];

        for (int i = size-1; i >=0; i--) result[ --bucket[(arr[i] / x) % 10] ] = arr[i];

        for (int i = 0; i < size; i++) arr[i] = result[i];

        print_Radix(x);

        x *= 10;
    }
}

// =========================== 메인함수
int main(void) {
    menu();
    int num;
    scanf("%d", &num);
    int n;

    while (num != 0) {
        switch (num) {
        case 1:
            resize_arr();
            heapSort();
            break;

        case 2:
            printf("1. 삽입\n");
            printf("2. 삭제\n");
            printf("3. 대기\n");
            printf("입력 : ");
            scanf("%d", &n);
            printf("\n");
            while (n != 0) {
                switch (n) {
                case 1:
                    insert_max_heap();
                    break;

                case 2:
                    delete_max_heap();
                    break;

                case 3:
                    show_heap();
                    break;
                }

                printf("\n1. 삽입\n");
                printf("2. 삭제\n");
                printf("3. 대기\n");
                printf("0. 종료\n");
                printf("입력 : ");
                scanf("%d", &n);
            }
            Size = 0;
            break;

        case 3:
            resize_arr2();
            Radixsort();
            break;

        default:
            printf("잘못된 접근입니다.\n");
        }

        clear_arr();
        menu();
        scanf("%d", &num);
    }
}


