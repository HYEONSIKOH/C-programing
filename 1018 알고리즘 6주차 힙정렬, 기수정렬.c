/*
1. ���� 113�� �˰��� 4-7, 117�� �˰��� 4-8�� �����Ͽ� ��(heap) ���� ���α׷��� �ۼ��Ͻÿ�. (�ִ����� �̿��Ͽ�, �������� ������ �����Ѵ�)
    - ������ n�� ���� ���� ���� �迭�� �Է����� �Ѵ�.
    - buildHeap( ) �� �����ϸ鼭 �߰��������� ��ȯ�Ǵ� ������ ������� ���̰�,
      �ϼ��� �ʱ� ���� ����Ѵ�.
    - �� ������ �����ϸ鼭 �� ������ ���ʷ� ������� �����ش�.
     (�� ũ�Ⱑ �ٸ鼭 ������Ǵ� �߰� ���� ������� �ܰ躰�� ����Ѵ�)

2. ���� �߿��� ������ �켱���� ť�� �����Ͻÿ�(���, ����, ���� ����).
   - �ִ� n�� �����Ͱ� ����� �� �ְ�(�ʱ� ���´� 0��),
     ���� ū ���� ���� ���� ���� �� �ֵ��� �׻� �ִ��� ���¸� �����ϸ�,
   - �������� �ִ밪�� ������ ����, ũ�Ⱑ 1 ������ �ִ������� �籸���Ѵ�.
   - �������� ���ο� �����Ͱ� ������, ũ�Ⱑ 1 ������ �ִ������� �籸���Ѵ�.

3. n���� �ټ��ڸ� 8�������� �������(Radix sort)�ϴ� ���α׷��� �ۼ��Ͻÿ�.
   8�����̹Ƿ� 0~7 �� �ڸ������� �з��ؼ� ���� �� �ִ� ��Ŷ�� ����Ѵ�.
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
    printf("=================== [�޴�] ===================\n");
    printf("1. �� ����\n");
    printf("2. �켱���� ť\n");
    printf("3. ��� ����\n");
    printf("0. ����\n");
    printf("==============================================\n");
    printf("�Է� : ");
}

void resize_arr() {
    printf("ũ�� �Է� : ");
    scanf("%d", &size);
    for (int i = 1; i <= size; i++) arr[i] = rand() % 100 + 1;
}

void resize_arr2() {
    printf("ũ�� �Է� : ");
    scanf("%d", &size);
    printf("������ ���� ũ�⸸ŭ �Է��ϼ��� : ");
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

// =========================== 1���Լ�

// arr[1....n]�� ������ �����.
void heapify(int k,int n) { 
    int left = 2 * k, right = (2 * k) + 1;
    int larger;

    // ū �ڽ� ����, larger : arr[2k]�� arr[2k+1]�߿� ū ����
    if (right <= n) larger = (arr[left] < arr[right]) ? right : left; // k�� �� �ڽ��� ������ ���
    else if (left <= n) larger = left;  // k�� ���� �ڽĸ� �մ� ���
    else return;                        // arr[k]�� ���� ����� ���, �����Ŵ�.

    // ���� �ڽĵ� ��, ���� ū ���� arr[k]������ ū ���, �����ϰ� �ѹ� �� �ִ������� �˻�!
    if (arr[larger] >= arr[k]) {
        swap(larger, k);
        heapify(larger, n);
    }
}

void buildHeap() {
    for (int i = size / 2; i > 0; i--) heapify(i,size);
}

// arr[1...n]�� �����Ѵ�.
void heapSort() {
    printf("���� �� : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf("\n");

    buildHeap(); // �ִ� �� �����!

    printf("\n�ִ� �� : ");
    for (int i = 1; i <= size; i++) printf("\033[0;36m%d\033[0m ", arr[i]);
    printf("\n");

    for (int i = size; i > 0; i--) {
        swap(1, i); // ���� ū ���� �� �ڷ� ������!

        // ��� ==========================================
        printf("   ���� : ");
        for (int j = 1; j <= size; j++) {
            if (j >= i) printf("\033[0;32m%d\033[0m ", arr[j]);
            else printf("%d ", arr[j]);
        }
        printf("\n");

        heapify(1, i - 1);

        // ��� ==========================================
        if (i != 1) {
            printf("\n�ִ� �� : ");
            for (int j = 1; j <= size; j++) {
                if (j <= i - 1) printf("\033[0;36m%d\033[0m ", arr[j]);
                else printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }

    printf("\n���� ��: ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf("\n");
}

// =========================== 2���Լ�
int Size;

void insert_max_heap() {
    printf("�Է� : ");
    size++;
    scanf("%d", &arr[size]);
    Size = size;

    while (Size != 1) {
        heapify(Size / 2, Size);
        Size /= 2;
    }

    printf("���� �켱���� ť : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" ũ�� : %d", size);
    printf("\n");
}

void delete_max_heap() {
    swap(1, size);
    size--;

    heapify(1, size);

    printf("���� �켱���� ť : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" ũ�� : %d", size);
    printf("\n");
}

void show_heap() {
    printf("���� �켱���� ť : ");
    for (int i = 1; i <= size; i++) printf("%d ", arr[i]);
    printf(" ũ�� : %d", size);
    printf("\n");
}


// =========================== 3���Լ�

void Radixsort() {
    int x = 1;
    int* result = malloc(sizeof(int) * (size)); // ������ ���� �� ��, �ӽ÷� �����ϴ� ����
   
    for(int index = 0; index <5; index++) {
        int bucket[10] = { 0, }; // �� �ڸ� ���� � �ִ��� ���
        
        for (int i = 0; i < size; i++) bucket[(arr[i] / x) % 10]++;

        for (int i = 1; i < 10; i++) bucket[i] += bucket[i - 1];

        for (int i = size-1; i >=0; i--) result[ --bucket[(arr[i] / x) % 10] ] = arr[i];

        for (int i = 0; i < size; i++) arr[i] = result[i];

        print_Radix(x);

        x *= 10;
    }
}

// =========================== �����Լ�
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
            printf("1. ����\n");
            printf("2. ����\n");
            printf("3. ���\n");
            printf("�Է� : ");
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

                printf("\n1. ����\n");
                printf("2. ����\n");
                printf("3. ���\n");
                printf("0. ����\n");
                printf("�Է� : ");
                scanf("%d", &n);
            }
            Size = 0;
            break;

        case 3:
            resize_arr2();
            Radixsort();
            break;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }

        clear_arr();
        menu();
        scanf("%d", &num);
    }
}


