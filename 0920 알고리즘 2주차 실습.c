/*
1. n(=10, 20, 30)���� ������ ���ĵ� ���·� �迭�� �����ϰ�, 
������ ���� �˻��ϴ� �����˻�(Binary Search) �Լ��� �ۼ��Ͻÿ� (���/�ݺ� �� ����). 
����.�� �Է¿� ���� �����˻��� �� Ƚ���� �� ���� ���� �ʴ´١��� Ȯ���ϴ� �ǽ��Դϴ�. 
(1) ������ ���� �˻��ϴ� ������ ������ �� �ֵ��� ��¹��� ������ �����Ͻÿ�. 
 (���� �˻� ����, �߰� ��ġ, �� �� ���� Ȯ���ϱ� ���� ȭ�鿡 ǥ��) 
(2) Ư�� Ű ���� �˻��� �����ϴ� ���, ���� �� ȸ�� �񱳰� �־����� ����Ͻÿ�. 
(3) Ư�� Ű ���� �˻��� �����ϴ� ���, ���� �� ȸ�� �񱳰� �־����� ����Ͻÿ�. 
(4) �迭�� ��� ���� �� ���� �˻��ϸ鼭, ��� �� Ƚ���� ����Ͻÿ�. 
 ����, �� �� �־��� ���, �� ȸ���� Ȯ���Ͻÿ�.
(5) n+1 ����� ���� ��� �� �־��� ��� �� ȸ�� �񱳰� �־����� Ȯ���Ͻÿ�.

2. ���ĵ� ������ �������� ���� �迭/���Ḯ��Ʈ�� �� �� �����ϰ�, 
 �� �� ���� �����Ͽ� �ϳ��� ���ĵ� �迭/���Ḯ��Ʈ�� �ϼ��ϴ� ���α׷��� �ۼ��Ͻÿ�. 
(��: {5, 7, 24, 56}�� {19, 45, 61, 79, 92}�� ������ ����� {5, 7, 19, 24, 45, 56, 61, 79, 92} �̴�.) 
(1) �迭�� �ۼ��Ͻÿ� 
(2) ���Ḯ��Ʈ�� �ۼ��Ͻÿ�. ��, ���ο� ��带 ������ �ʰ�, ������ ����� ����� �ϼ��Ͻÿ�. 

3. �ϳ���Ÿ�� ������ ��ȯȣ��� �ۼ��Ͻÿ� 
(2n �ӵ��� �����ϴ� �˰����� ��ǥ���� ��) 
 3, 4, 5 ... 10���� ��ũ�� �Է����� �� �� �� �� ���� ��ũ �ű�� ������ �����ϴ��� �׽�Ʈ�Ͻÿ�. 
// hanoi �Լ� : N���� ������ A���� C�� �ű��. B�� ����� �� �ִ�. 
hanoi(N, A, B, C) 
 if( N == 1) { 
 print "<1> ������ <A>���� <C>�� �ű��." // ������ A���� C�� �ű��. 
 } 
 else { 
 hanoi(N-1, A, C, B) //1. [1:N-1] ������ A���� B�� �ű��. 
 print "<N> ������ <A>���� <C>�� �ű��." //2. [N] ������ A���� C�� �ű��. 
 hanoi(N-1, B, A, C) //3. [1:N-1] ������ B���� C�� �ű��. 
 }
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int cnt = 0;
int hanoi_cnt = 0;
int* d;

// ================= 1�� �Լ� =================

int Binary_Search(int* arr, int size, int num) {
	int s = 0;
	int e = size - 1;
	int m;
	cnt = 0;

	while (e >= s) {
		m = (s + e) / 2;
		cnt++;
		if (arr[m] == num) {
			printf("[%d]�� [%d] ��� [%d]���� %d���� �����ϴ�.\n", s, e, m, num);
			printf("�� %d�� Ž���߽��ϴ�.\n", cnt);
			return;
		}

		else if (arr[m] > num) {
			printf("[%d]�� [%d] ��� [%d]���� %d������ Ů�ϴ�.\n", s, e, m, num);
			e = m - 1;
		}

		else {
			printf("[%d]�� [%d] ��� [%d]���� %d������ �۽��ϴ�.\n", s, e, m, num);
			s = m + 1;
		}
	}

	printf("�� %d�� Ž��������, �����߽��ϴ�.\n", cnt);
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

	printf("�迭 : ");
	for (int i = 0; i < n; i++) printf("[%d] ", d[i]);
	printf("\n");

	printf("ã�� ���� �Է��ϼ��� : ");
	scanf("%d", &search_num);

	Binary_Search(d, n, search_num);
}

//================= 2�� �Լ� =================

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

	printf("�迭 : ");
	for (int i = 0; i < c_size; i++) printf("[%d] ", c[i]);
	printf("\n\n");
}

typedef struct ListNode { // ��� Ÿ��
	int data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, int value) { // ��� ��� ����
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head; // ��� �������� ���� ����
	head = p;       // ��� ������ ����
	return head;    // ����� ��� ������ ��ȯ
}
ListNode* insert(ListNode* head, ListNode* pre, int value) { // �߰� ��� ����
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

int list_length(ListNode* head) { // ����� ������ ��ȯ�ϴ� �Լ�
	ListNode* p = head;
	int count = 0;

	for (ListNode* p = head; p != NULL; p = p->link) count++;


	return count;
}

void list_display(ListNode* head) { // �� ��� ���
	printf("\n-----------------------------------------\n");
	printf("����Ʈ : ");
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

//================= 3�� �Լ� =================

void hanoi(int N, char A, char B, char C) {
	hanoi_cnt++;
	if (N == 1) printf("[%d]�� ������ <%c>���� <%c>�� �ű��.\n",N, A, C); // ������ A���� C�� �ű��. 
	
	else {
		hanoi(N - 1, A, C, B); //1. [1:N-1] ������ A���� B�� �ű��. 
		printf("[%d]�� ������ <%c>���� <%c>�� �ű��.\n", N, A, C); // 2. [N] ������ A���� C�� �ű��. 
		hanoi(N - 1, B, A, C); //3. [1:N-1] ������ B���� C�� �ű��. 
	}
}

// ================= ���� �Լ� =================
void menu() {
	printf("=================== [�޴�] ===================\n");
	printf("1. �����˻� (Binary Search)\n");
	printf("2. ���յ� �迭/���Ḯ��Ʈ\n");
	printf("3. �ϳ���Ÿ�� (��ȯȣ��)\n");
	printf("0. ����\n");
	printf("==============================================\n");
	printf("�Է� : ");
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
			printf("10 , 20 , 30 �� �Ѱ��� �Է��ϼ��� : ");
			scanf("%d", &n);
			double ave = 0;
			
			if (n == 10) {
				function(n);
			
				printf("1. �� �´´� 2. �� Ʋ����. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n�� ���� ��� : %f\n", ave / n);
					printf("\n�־��� ����� �� : %d\n", max);
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
					printf("\n�� Ʋ�� ��� : %f\n", ave / A);
				}
			}
			else if (n == 20) {
				function(n);
			
				printf("1. �� �´´� 2. �� Ʋ����. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n�� ���� ��� : %f\n", ave / n);
					printf("\n�־��� ����� �� : %d\n", max);
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
					printf("\n�� Ʋ�� ��� : %f\n", ave / A);
				}
			}

			else if (n == 30) {
				function(n);

				printf("1. �� �´´� 2. �� Ʋ����. : ");
				scanf("%d", &k);
				if (k == 1) {
					for (int i = 0; i < n; i++) {
						temp = Binary_Search_Ave(d, n, d[i]);
						ave += temp;
						if (max < temp) max = temp;
					}
					printf("\n�� ���� ��� : %f\n", ave / n);
					printf("\n�־��� ����� �� : %d\n", max);
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
					printf("\n�� Ʋ�� ��� : %f\n", ave / A);
				}
			}
			break;
		case 2:
			printf("1. �迭 2.���Ḯ��Ʈ : ");
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
			printf("���� ������ �Է����ּ��� : ");
			scanf("%d", &n);
			hanoi(n, 'A', 'B', 'C');
			printf("\n Ƚ�� : %d \n", hanoi_cnt);
			hanoi_cnt = 0;
			break;

		default:
			printf("�߸��� �Է��Դϴ�.\n");
		}

		menu();
		scanf("%d", &num);
	}

	return 0;
}