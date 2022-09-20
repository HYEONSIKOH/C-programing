/*
1. n(=10, 20, 30)개의 정수를 정렬된 상태로 배열에 저장하고, 
임의의 값을 검색하는 이진검색(Binary Search) 함수를 작성하시오 (재귀/반복 중 선택). 
“….개 입력에 대해 이진검색은 비교 횟수가 … 번을 넘지 않는다”를 확인하는 실습입니다. 
(1) 임의의 값을 검색하는 과정을 추적할 수 있도록 출력문을 적절히 삽입하시오. 
 (현재 검색 범위, 중간 위치, 비교 값 등을 확인하기 좋게 화면에 표시) 
(2) 특정 키 값의 검색에 성공하는 경우, 전부 몇 회의 비교가 있었는지 출력하시오. 
(3) 특정 키 값의 검색에 실패하는 경우, 전부 몇 회의 비교가 있었는지 출력하시오. 
(4) 배열의 모든 값을 한 번씩 검색하면서, 평균 비교 횟수를 계산하시오. 
 또한, 그 중 최악의 경우, 몇 회인지 확인하시오.
(5) n+1 경우의 실패 경우 중 최악의 경우 몇 회의 비교가 있었는지 확인하시오.

2. 정렬된 순서로 정수값을 갖는 배열/연결리스트를 두 개 생성하고, 
 이 두 개를 병합하여 하나의 정렬된 배열/연결리스트로 완성하는 프로그램을 작성하시오. 
(예: {5, 7, 24, 56}과 {19, 45, 61, 79, 92}을 병합한 결과는 {5, 7, 19, 24, 45, 56, 61, 79, 92} 이다.) 
(1) 배열로 작성하시오 
(2) 연결리스트로 작성하시오. 단, 새로운 노드를 만들지 않고, 기존의 노드들로 결과를 완성하시오. 

3. 하노이타워 문제를 순환호출로 작성하시오 
(2n 속도로 증가하는 알고리즘의 대표적인 예) 
 3, 4, 5 ... 10개의 디스크를 입력으로 할 때 총 몇 번의 디스크 옮기기 동작을 포함하는지 테스트하시오. 
// hanoi 함수 : N개의 원판을 A에서 C로 옮긴다. B를 사용할 수 있다. 
hanoi(N, A, B, C) 
 if( N == 1) { 
 print "<1> 원판을 <A>에서 <C>로 옮긴다." // 원판을 A에서 C로 옮긴다. 
 } 
 else { 
 hanoi(N-1, A, C, B) //1. [1:N-1] 원판을 A에서 B로 옮긴다. 
 print "<N> 원판을 <A>에서 <C>로 옮긴다." //2. [N] 원판을 A에서 C로 옮긴다. 
 hanoi(N-1, B, A, C) //3. [1:N-1] 원판을 B에서 C로 옮긴다. 
 }
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int cnt = 0;
int hanoi_cnt = 0;
int* d;

// ================= 1번 함수 =================

int Binary_Search(int* arr, int size, int num) {
	int s = 0;
	int e = size - 1;
	int m;
	cnt = 0;

	while (e >= s) {
		m = (s + e) / 2;
		cnt++;
		if (arr[m] == num) {
			printf("[%d]와 [%d] 가운데 [%d]값이 %d값과 같습니다.\n", s, e, m, num);
			printf("총 %d번 탐색했습니다.\n", cnt);
			return;
		}

		else if (arr[m] > num) {
			printf("[%d]와 [%d] 가운데 [%d]값이 %d값보다 큽니다.\n", s, e, m, num);
			e = m - 1;
		}

		else {
			printf("[%d]와 [%d] 가운데 [%d]값이 %d값보다 작습니다.\n", s, e, m, num);
			s = m + 1;
		}
	}

	printf("총 %d번 탐색했지만, 실패했습니다.\n", cnt);
	return cnt;
}

int Binary_Search_Ave(int* arr, int size, int num) {
	int s = 0;
	int e = size - 1;
	int m;
	cnt = 0;

	while (e >= s) {
		m = (s + e) / 2;
		cnt++;
		if (arr[m] == num) return cnt;
		
		else if (arr[m] > num) e = m - 1;

		else s = m + 1;
	}

	return cnt;
}

int * sort(int a[],int size) {
	int temp;

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (a[i] > a[j]) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	return a;
}

void function(int n) {
	int search_num;
	d = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) d[i] = rand() % 100 + 1;
	sort(d, n);

	printf("배열 : ");
	for (int i = 0; i < n; i++) printf("[%d] ", d[i]);
	printf("\n");

	printf("찾는 값을 입력하세요 : ");
	scanf("%d", &search_num);

	Binary_Search(d, n, search_num);
}

//================= 2번 함수 =================

void array_merger (int* a, int* b,int a_size,int b_size) {
	int index_a = 0, index_b = 0;
	int c_size = a_size + b_size, index_c = 0;
	int* c = (int*)malloc(sizeof(int) * c_size);

	while (index_a != a_size && index_b != b_size) {
		if (a[index_a] < b[index_b]) c[index_c++] = a[index_a++];
		else c[index_c++] = b[index_b++];
	}

	while(index_a != a_size) c[index_c++] = a[index_a++];
	while(index_b != b_size) c[index_c++] = b[index_b++];

	printf("배열 : ");
	for (int i = 0; i < c_size; i++) printf("[%d] ", c[i]);
	printf("\n\n");
}

typedef struct ListNode { // 노드 타입
	int data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, int value) { // 헤드 노드 연결
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head; // 헤드 포인터의 값을 복사
	head = p;       // 헤드 포인터 변경
	return head;    // 변경된 헤드 포인터 반환
}
ListNode* insert(ListNode* head, ListNode* pre, int value) { // 중간 노드 연결
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

int list_length(ListNode* head) { // 노드의 개수를 반환하는 함수
	ListNode* p = head;
	int count = 0;

	for (ListNode* p = head; p != NULL; p = p->link) count++;


	return count;
}

void list_display(ListNode* head) { // 각 노드 출력
	printf("\n-----------------------------------------\n");
	printf("리스트 : ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("[%d] ", p->data);
	printf("\n-----------------------------------------\n");
}

void list_merger(ListNode * a,ListNode *b) {
	ListNode* c = NULL;
	ListNode* Link_c = NULL;

	while (a != NULL & b != NULL) {
		if (c == NULL) {
			if (a->data < b->data) {
				c = a;
				Link_c = c;
				a = a->link;
			}

			else {
				c = b;
				Link_c = c;
				b = b->link;
			}
		}

		else {
			if (a->data < b->data) {
				Link_c->link = a;
				Link_c = a;
				a = a->link;
			}
			else {
				Link_c->link = b;
				Link_c = b;
				b = b->link;
			}
		}
	}

	while (a != NULL) {
		Link_c->link = a;
		Link_c = a;
		a = a->link;
	}

	while (b != NULL) {
		Link_c->link = b;
		Link_c = b;
		b = b->link;
	}

	list_display(c);
}

//================= 3번 함수 =================

void hanoi(int N, char A, char B, char C) {
	hanoi_cnt++;
	if (N == 1) printf("[%d]번 원판을 <%c>에서 <%c>로 옮긴다.\n",N, A, C); // 원판을 A에서 C로 옮긴다. 
	
	else {
		hanoi(N - 1, A, C, B); //1. [1:N-1] 원판을 A에서 B로 옮긴다. 
		printf("[%d]번 원판을 <%c>에서 <%c>로 옮긴다.\n", N, A, C); // 2. [N] 원판을 A에서 C로 옮긴다. 
		hanoi(N - 1, B, A, C); //3. [1:N-1] 원판을 B에서 C로 옮긴다. 
	}
}

// ================= 메인 함수 =================
void menu() {
	printf("=================== [메뉴] ===================\n");
	printf("1. 이진검색 (Binary Search)\n");
	printf("2. 병합된 배열/연결리스트\n");
	printf("3. 하노이타워 (순환호출)\n");
	printf("0. 종료\n");
	printf("==============================================\n");
	printf("입력 : ");
}

int main() {
	int a[4] = { 5, 7, 24, 56 };
	int b[5] = { 19, 45, 61, 79, 92 };

	int num,n, search_num,k;
	int temp;

	menu();
	scanf("%d", &num);

	while (num != 0) {
		int max = 0;
		switch (num) {
		case 1:
			printf("10 , 20 , 30 중 한개를 입력하세요 : ");
			scanf("%d", &n);
			double ave = 0;
			
			if (n == 10) {
				function(n);
			
				printf("1. 다 맞는다 2. 다 틀린다. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n다 맞은 평균 : %f\n", ave / n);
					printf("\n최악의 경우의 수 : %d\n", max);
				}
				else {
					int A = n + 1;
					for (int i = 0; i < n + 1; i++) {
						if(i == n) ave += Binary_Search_Ave(d, n, d[n-1] + 1);
						else if (i > 0) {
							if (d[i] - 1 == d[i - 1]) A--;
							else ave += Binary_Search_Ave(d, n, d[i] - 1);
						}
						else ave += Binary_Search_Ave(d, n, d[i] - 1);
					}
					printf("\n다 틀린 평균 : %f\n", ave / A);
				}
			}
			else if (n == 20) {
				function(n);
			
				printf("1. 다 맞는다 2. 다 틀린다. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n다 맞은 평균 : %f\n", ave / n);
					printf("\n최악의 경우의 수 : %d\n", max);
				}
				else {
					int A = n + 1;
					for (int i = 0; i < n + 1; i++) {
						if (i == n) ave += Binary_Search_Ave(d, n, d[n - 1] + 1);
						else if (i > 0) {
							if (d[i] - 1 == d[i - 1]) A--;
							else ave += Binary_Search_Ave(d, n, d[i] - 1);
						}
						else ave += Binary_Search_Ave(d, n, d[i] - 1);
					}
					printf("\n다 틀린 평균 : %f\n", ave / A);
				}
			}

			else if (n == 30) {
				function(n);

				printf("1. 다 맞는다 2. 다 틀린다. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n다 맞은 평균 : %f\n", ave / n);
					printf("\n최악의 경우의 수 : %d\n", max);
				}
				else {
					int A = n + 1;
					for (int i = 0; i < n + 1; i++) {
						if (i == n) ave += Binary_Search_Ave(d, n, d[n - 1] + 1);
						else if (i > 0) {
							if (d[i] - 1 == d[i - 1]) A--;
							else ave += Binary_Search_Ave(d, n, d[i] - 1);
						}
						else ave += Binary_Search_Ave(d, n, d[i] - 1);
					}
					printf("\n다 틀린 평균 : %f\n", ave / A);
				}
			}
			break;
		case 2:
			printf("1. 배열 2.연결리스트 : ");
			scanf("%d", &n);
			if (n == 1) array_merger(a, b, 4, 5);
			else {
				ListNode* head1 = NULL;
				ListNode* head2 = NULL;
				ListNode* h1 = NULL;
				ListNode* h2 = NULL;

				for (int i = 0; i < 4; i++) {
					if (i == 0) {
						head1 = insert_first(head1, a[i]);
						h1 = head1;
					}
					else {
						head1 = insert(head1, h1, a[i]);
						h1 = h1->link;
					}
				}

				for (int i = 0; i < 5; i++) {
					if (i == 0) {
						head2 = insert_first(head2, b[i]);
						h2 = head2;
					}
					else {
						head2 = insert(head2, h2, b[i]);
						h2 = h2->link;
					}
				}

				list_merger(head1, head2);
			}

			break;

		case 3:
			printf("원판 개수를 입력해주세요 : ");
			scanf("%d", &n);
			hanoi(n, 'A', 'B', 'C');
			printf("\n 횟수 : %d \n", hanoi_cnt);
			hanoi_cnt = 0;
			break;

		default:
			printf("잘못된 입력입니다.\n");
		}

		menu();
		scanf("%d", &num);
	}

	return 0;
}