/*
(1) 데이터 { 문자열 음악제목 문자열 가수(연주자) 문자 장르 정수 발표년도 } 를 저장하는
    ('B' 'C' 'H' 'J' 'T' ) 연결리스트 노드의 자료구조 정의 여기서 장르는 중 하나
(2) insert_node( ) : 새 노드를 현재 리스트의 특정 위치에 삽입하는 함수 작성
(3) list_length( ) : 현재 리스트에 연결된 노드의 개수를 계산해서 반환하는 함수 작성
(4) list_display( ) : 현재 리스트에 연결된 각 노드에서 { 음악제목, 가수(연주자), 장르, 발표년도} 를 출력

main() : 함수에서는 빈 리스트에서 시작하여 아래와 같은 메뉴로 테스트

      -  좋아하는 음악에 대한 데이터를 저장한 새 노드를 만들고, 
         현재 리스트에 삽입 제목의 오름차순을 유지하도록 연결
      - list_length( ) , 를 호출하여 현재 리스트에 연결된 노드의 개수를 계산
      - list_display( )를 호출하여 현재 리스트에 연결된 각 노드의 데이터를 출력*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char name[100]; // 노래 이름
    char singer[30]; // 가수
    char genre; // 장르
    int year; // 연도
}element;

typedef struct ListNode{ // 노드 타입
    element data;
    struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element value) { // 헤드 노드 연결
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head; // 헤드 포인터의 값을 복사
    head = p;       // 헤드 포인터 변경
    return head;    // 변경된 헤드 포인터 반환
}
ListNode* insert(ListNode* head, ListNode* pre, element value) { // 중간 노드 연결
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* insert_node(ListNode* head, element item) { // 오름차순 노드 연결
    ListNode* p = head;

    if (head == NULL || (strcmp(head->data.name, item.name) >= 0)) head = insert_first(head, item); // head의 name 값이 item의 name 값보다 사전적으로 뒤일 때 , head의 값이 비어있을 때,

    else {
        while (p->link != NULL) {
            if (strcmp(p->link->data.name, item.name) > 0) { // p의 name 값이 item의 name 값보다 사전적으로 뒤일 때
                head = insert(head, p, item);
                return head;
            }
            p = p->link;
        }
        head = insert(head, p, item); // 끝까지 갔는데, 사전적으로 뒤가 없을 때
        return head;
    }
}

int list_length(ListNode* head) { // 노드의 개수를 반환하는 함수
    ListNode* p = head;
    int count = 0;

    for (ListNode* p = head; p != NULL; p = p->link) count++;
    
   
    return count;
}

element input(){ // 노래 정보 입력 함수
    printf("노래 제목 , 가수(연주자), 장르 (B, C, H, J, T), 발매 년도를 입력해주세요\n");
    printf("입력: ");
    element p;
    scanf("%s %s %c %d", p.name, p.singer, &p.genre, &p.year);
    printf("\n\n\n");
    return p;
}

void list_display(ListNode* head) { // 각 노드 출력
    printf("-----------------------------------------\n");
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("노래제목: %-20s 가수: %-10s 장르: %-2c 발매년도: %-4d\n", p->data.name, p->data.singer, p->data.genre, p->data.year);
    printf("-----------------------------------------\n");
}

void main_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. 종료\n");
    printf("1. 오름차순으로 입력\n");
    printf("2. 노드의 개수\n");
    printf("3. 각 노드 출력\n");
    printf("--------------------------------------------\n");
    printf("입력: ");
}

int main(void) {
    int menu = 0;
    int count = 0;
    ListNode* head = NULL;
    while (1) {
        main_menu();
        scanf("%d", &menu);
        printf("\n");

        if (menu == 0) {
            printf("종료합니다.....\n");
            Sleep(1000);
            return 0;
        }
            
        else {
            switch (menu) {
            case 1:
                head = insert_node(head, input());
                break;

            case 2:
                printf("-----------------------------------------\n");
                printf("노드의 개수는 총 %d개 입니다.\n", list_length(head));
                printf("-----------------------------------------\n");
                break;

            case 3:
                list_display(head);
                break;
            
            default:
                printf("            [잘못된 선택입니다.]\n");
                break;
            }
        }
    }
}