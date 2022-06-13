/*
- �Ʒ��� ���԰� ���� ������ �ݺ������� �����ϰ� ������ Ȯ���ϴ� ���α׷��� �ϼ��Ͻÿ�.

(1) �ʱ� ���� Heap�� ���ο� �Ŀ��� ������ 5���� ���� ������ ���ʷ� �����ϸ鼭, �����
�� ������ ������ �迭 ������� ���̽ÿ�.

(2) ������ Heap���� �ְ� �켱����(�ִ� �Ŀ���)�� ������ ��, ũ�Ⱑ 1 �پ�� Heap���� 
�ٽ� �籸���ϰ� �� ����� ������ �迭�� ����Ͻÿ�.

(3) ���ο� �Ŀ��� �����͸� ������ Heap�� �����ϰų� �켱������ ���� ���� �Ŀ��ڸ� ��
���ϴ� ������ �ݺ��ϸ鼭, �� Heap�� �켱����ť�� �����ϴ� ���� Ȯ���Ͻÿ�.

(�ÿ� �������� ���԰� ������ ���� ������ �ݺ��ϸ鼭 �迭�� ����� ������ ����ϰ� �� 
������ �����Ͻÿ�
*/
#include <stdio.h>

#define MAX_ELEMENT 30

//=================== Heap ===================
typedef struct {
	char id[20]; // �Ŀ��� ID
	int amount; // �Ŀ��� �׼��̸�, heap�� �켱������ �����Ѵ�.
}element;
	
typedef struct {
	element heap[MAX_ELEMENT]; //�迭 ũ��� 30���� �Ѵ�.
	int heap_size;
}HeapType;
//============================================

//�����Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//�ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

//���� ����� ������ Heap_size�� ���� h�� item�� �����Ѵ�.
//�����Լ�
void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size); // ���� �� �ڽ��� �ε�����
	
	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	//left = �θ� * 2  || right = �θ� * 2 + 1 || �θ�: (�ڽ��ε���) / 2
	while ((i != 1) && (item.amount > h->heap[i / 2].amount)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}

//�����Լ�
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	if ((h->heap_size) <= 0)
		(h->heap_size) = 0;

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) && (h->heap[child].amount) < h->heap[child + 1].amount)
			child++;
		if (temp.amount >= h->heap[child].amount) break;

		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void menu() {
	printf("============== [�޴�] ==============\n");
	printf("1. ���ԵǾ��ִ� ������ �迭�� ���\n");
	printf("2. �ִ� �Ŀ��� ���� �� �迭�� ���\n");
	printf("3. ���ο� �Ŀ��� ����\n");
	printf("0. ����\n");
	printf("====================================\n");
	printf("�Է�: ");
}

int main(void) {
	int num = 0;

	element temp = { 0,0 };
	// �̸� �Է��� �ڷ��
	element e1 = { "James",100000 };
	element e3 = { "John",200000 };
	element e5 = { "Robert",300000 };
	element e2 = { "Michael",400000 };
	element e4 = { "Thomas",500000 };

	HeapType* heap = create(); // ��������
	init(heap); // �ʱ�ȭ

	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);
	insert_max_heap(heap, e4);
	insert_max_heap(heap, e5);

	while (1) {
		menu();
		scanf("%d", &num);
		if (num == 0) exit(1);
		
		switch (num) {
		case 1:
			printf("\n");
			if (heap->heap_size == 0)
				printf("����� �����Ͱ� �����ϴ�.\n");
			for (int i = 1; i <= heap->heap_size; i++) printf("[%s : %d��] ", heap->heap[i].id, heap->heap[i].amount);
			printf("\n"); printf("\n");
			break;
			
		case 2:
			delete_max_heap(heap);
			printf("���� ū �Ŀ��� �Ŀ��ڰ� �����Ǿ����ϴ�.\n");
			break;

		case 3:
			printf("\n");
			printf("�Ŀ��� �̸� �� �Ŀ��ݾ��� �����ּ���: ");
			scanf("%s %d", &temp.id, &temp.amount);
			insert_max_heap(heap, temp);
			printf("\n");
			break;

		default:
			printf("�ǹٸ��� ���� ���Դϴ�.\n");
			break;
		}
	}
}