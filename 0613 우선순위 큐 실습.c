/*
- 아래의 삽입과 삭제 과정을 반복적으로 실행하고 내용을 확인하는 프로그램을 완성하시오.

(1) 초기 공백 Heap에 새로운 후원자 데이터 5개를 임의 순서로 차례로 삽입하면서, 저장되
는 내용을 일차원 배열 출력으로 보이시오.

(2) 현재의 Heap에서 최고 우선순위(최대 후원금)을 삭제한 후, 크기가 1 줄어든 Heap으로 
다시 재구성하고 그 결과를 일차원 배열로 출력하시오.

(3) 새로운 후원자 데이터를 현재의 Heap에 삽입하거나 우선순위가 가장 높은 후원자를 삭
제하는 과정을 반복하면서, 이 Heap이 우선순위큐로 동작하는 것을 확인하시오.

(시연 과정에서 삽입과 삭제를 임의 순서로 반복하면서 배열에 저장된 내용을 출력하고 그 
동작을 설명하시오
*/
#include <stdio.h>

#define MAX_ELEMENT 30

//=================== Heap ===================
typedef struct {
	char id[20]; // 후원자 ID
	int amount; // 후원금 액수이며, heap의 우선순위를 결정한다.
}element;
	
typedef struct {
	element heap[MAX_ELEMENT]; //배열 크기는 30으로 한다.
	int heap_size;
}HeapType;
//============================================

//생성함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

//현재 요소의 개수가 Heap_size인 히프 h에 item을 삽입한다.
//삽입함수
void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size); // 가장 끝 자식의 인덱스값
	
	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	//left = 부모 * 2  || right = 부모 * 2 + 1 || 부모: (자식인덱스) / 2
	while ((i != 1) && (item.amount > h->heap[i / 2].amount)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}

//삭제함수
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
		// 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) && (h->heap[child].amount) < h->heap[child + 1].amount)
			child++;
		if (temp.amount >= h->heap[child].amount) break;

		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void menu() {
	printf("============== [메뉴] ==============\n");
	printf("1. 삽입되어있는 데이터 배열로 출력\n");
	printf("2. 최대 후원금 삭제 및 배열로 출력\n");
	printf("3. 새로운 후원자 삽입\n");
	printf("0. 종료\n");
	printf("====================================\n");
	printf("입력: ");
}

int main(void) {
	int num = 0;

	element temp = { 0,0 };
	// 미리 입력한 자료들
	element e1 = { "James",100000 };
	element e3 = { "John",200000 };
	element e5 = { "Robert",300000 };
	element e2 = { "Michael",400000 };
	element e4 = { "Thomas",500000 };

	HeapType* heap = create(); // 히프생성
	init(heap); // 초기화

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
				printf("저장된 데이터가 없습니다.\n");
			for (int i = 1; i <= heap->heap_size; i++) printf("[%s : %d원] ", heap->heap[i].id, heap->heap[i].amount);
			printf("\n"); printf("\n");
			break;
			
		case 2:
			delete_max_heap(heap);
			printf("가장 큰 후원금 후원자가 삭제되었습니다.\n");
			break;

		case 3:
			printf("\n");
			printf("후원자 이름 및 후원금액을 적어주세요: ");
			scanf("%s %d", &temp.id, &temp.amount);
			insert_max_heap(heap, temp);
			printf("\n");
			break;

		default:
			printf("옳바르지 못한 값입니다.\n");
			break;
		}
	}
}