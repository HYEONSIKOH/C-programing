/*
음악정보 프로그램을 단순연결리스트에서 이중연결리스트로 변경하여 구현하시오.
( 1) (1~10 ) . 주 데이터필드에 재생시간 초 이 정수타입으로 추가된다
( 2) 230-231 . 주 교재 쪽에 제시된 헤드노드를 갖는다
실행메뉴에는 다음과 같은 기능을 수정 또는 추가한다.
(1) , , . 삽입함수 노드개수 계산함수 전체출력함수를 이중연결리스트에 맞도록 수정
(2) : 음악제목으로 자료 검색하는 함수
 , NULL 리스트에서 찾으면 해당 노드를 반환하고 리스트에 존재하지 않으면 반환
(3) . 특정 음악에 대한 노드를 삭제하는 함수
(4) . 가장 최근에 발표된 음악을 검색하는 함수
(5) . 원하는 장르의 음악들만 출력하는 함수
(6) ‘P’ : 재생메뉴 를 추가한다
 - 호출함수는 현재 노드의 재생시간만큼 대기한다 재생시간이 이 될 때까지 감소 ( 0 )
 progressive bar( ..........) 시각적 효과를 위해 예 출력 권장
 - . 재생이 완료되면 자동으로 다음 노드로 이동한다
(7) ‘>’ . 현재 노드의 다음 노드로 이동해서 재생하는 를 추가한다
(8) ‘<’ . 현재 노드의 이전 노드로 이동해서 재생하는 를 추가한다
(9) ‘F/f’ . 맨 앞의 영화로 이동해서 재생하는 가 추가한다
(10) ‘L/l’ .
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char name[100]; // 노래 이름
    char singer[30]; // 가수
    char genre; // 장르
    int year; // 연도
    int play_time;
}element;

typedef struct ListNode { // 노드 타입
    element data;
    struct ListNode* rlink;
    struct ListNode* llink;
}DListNode;

//리스트를 초기화
void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// 노드 입력
void dinsert(DListNode* before, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));

    newnode->data = data;
    newnode->llink = before; // 새로운 노드의 왼쪽 링크는 before 노드를 연결
    newnode->rlink = before->rlink; // 새로운 노드의 오른쪽 노드는 before의 오른쪽 링크와 연결

    before->rlink->llink = newnode; // before의 원래 앞에 있던 노드의 오른쪽 링크와
    before->rlink = newnode; // before의 왼쪽 링크를 newnode로 연결시킨다.
}

// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed) {
    if (removed == head) return;

    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;

    free(removed);
}

// 노드 전체를 출력
void print_dlist(DListNode* head) {
    for (DListNode* p = head->rlink; p != head; p = p->rlink)
        printf("노래제목: %-20s 가수: %-10s 장르: %-2c 발매년도: %-4d  재생시간:%d\n", p->data.name, p->data.singer, p->data.genre, p->data.year,p->data.play_time);
}

// 노드의 개수를 반환하는 함수
int list_length(DListNode* head) {
    int count = 0;

    for (DListNode* p = head->rlink; p != head; p = p->rlink) count++;

    return count;
}

// 오름차순 노드 연결
void insert_node(DListNode* head, element item) {
    DListNode* p = head->rlink;

    if (head->rlink == head || (strcmp(head->rlink->data.name, item.name) >= 0)) {
        dinsert(head, item); // head의 값이 비어있을 때,
        return;
    }

    else {
        while (p->rlink != head) {
            if (strcmp(p->rlink->data.name, item.name) > 0) { // p의 name 값이 item의 name 값보다 사전적으로 뒤일 때
                dinsert(p, item);
                return;
            }
            p = p->rlink;
        }
        dinsert(p, item); // 끝까지 갔는데, 사전적으로 뒤가 없을 때
    }
}

element input() { // 노래 정보 입력 함수
    printf("노래 제목 , 가수(연주자), 장르 (B, C, H, J, T), 발매 년도, 재생시간 을 입력해주세요\n");
    printf("입력: ");
    element p;
    scanf("%s %s %c %d %d", p.name, p.singer, &p.genre, &p.year, &p.play_time);
    printf("\n\n");
    return p;
}

void search_year(DListNode * head){
    int max = 0;
    DListNode* terms = (DListNode *)malloc(sizeof(DListNode));

    for (DListNode* p = head->rlink; p != head; p = p->rlink) {
        if (p->data.year > max) {
            max = p->data.year;
            terms = p;
        }
    }
    printf("가장 최근에 발매된 음악은, %d년 \"%s\" 입니다.\n", max, terms->data.name);
}

void main_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. 종료\n");
    printf("1. 오름차순으로 입력\n");
    printf("2. 노드의 개수\n");
    printf("3. 각 노드 출력\n");
    printf("4. 음악 재생\n");
    printf("5. 음악 정보 검색\n");
    printf("6. 원하는 음악 삭제\n");
    printf("7. 가장 최근에 발표된 음악 검색\n");
    printf("8. 원하는 장르 검색 및 출력\n");
    printf("--------------------------------------------\n");
    printf("입력: ");
}

void play_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. 종료\n");
    printf("p. 재생\n");
    printf(">. 다음곡 재생\n");
    printf("<. 이전곡 재생\n");
    printf("F/f. 처음곡 재생\n");
    printf("L/l. 마지막곡 재생\n");
    printf("--------------------------------------------\n");
    printf("입력: ");
}

void play_music_message(DListNode * head, DListNode * p) {
    int count = p->data.play_time;
    printf("현재 \"%s\" 곡이 재생중입니다....\n",p->data.name);
    for (int i = 1; i <= count; i++) {
        printf("...\n", i);
        Sleep(1000);
    }
    p = p->rlink;

    if (p == head)
        p = p->rlink;

    printf("\n");
}

DListNode* name_search(DListNode* head) { // 이름을 검색해서 출력
    if (head->rlink == head) {
        printf("저장된 곡이 없습니다.\n");
        return NULL;
    }
    printf("음악 제목을 입력해주세요: ");
    char n[30] = { 0, };
    scanf("%s", n);
    printf("\n");
    DListNode* p = head->rlink;
    while (p != head) {
        if (strcmp(n, p->data.name) == 0) {
            printf("제목: %s  가수:%s  장르: %c  년도: %d 재생시간: %d초\n", p->data.name, p->data.singer, p->data.genre, p->data.year, p->data.play_time);
            return p;
        }
        p = p->rlink;
    }
    printf("같은 제목이 없습니다.\n");
    return NULL;
}

void* search_genre(DListNode* head) {
    if (head->rlink == head) {
        printf("저장된 곡이 없습니다.\n");
        return;
    }
    printf("장르 (B, C, H, J, T) 한가지만 입력해주세요: ");
    char genre;
    scanf(" %c", &genre);
    int count = 0;

    for (DListNode* p = head->rlink; p != head; p = p->rlink) {
        if (genre == p->data.genre) {
            printf("노래제목: %-20s 가수: %-10s 장르: %-2c 발매년도: %-4d 재생시간:%d\n", p->data.name, p->data.singer, p->data.genre, p->data.year, p->data.play_time);
            count++;
        }
    }

    if (count == 0)
        printf("같은 장르의 음악이 없습니다.\n");
}

void play_music(DListNode * head) {
    DListNode* p = head->rlink;
    if (head->rlink == head) {
        printf("저장된 곡이 없습니다.\n");
        return;
    }
    play_music_message(head,p);
    char ch;
    while (1) {
        play_menu();
        scanf(" %c", &ch);
        if (ch == '0') break;

        switch (ch) {
        case 'p':
            play_music_message(head, p);
            break;

        case '<':
            if (p->llink == head) p = p->llink;
            p = p->llink;
            play_music_message(head,p);
            break;

        case '>':
            if (p->rlink == head) p = p->rlink;
            p = p->rlink;
            play_music_message(head,p);
            break;

        case 'F': case 'f':
            printf("첫번째 곡으로 이동합니다.\n ");
            p = head->rlink;
            play_music_message(head,p);
            break;

        case 'L': case 'l':
            printf("마지막 곡으로 이동합니다.\n ");
            p = head->llink;
            play_music_message(head,p);
            break;

        default:
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
        }
    }
}

int main(void) {
    int menu = 0;
    int count = 0;
    DListNode *terms = (DListNode*)malloc(sizeof(DListNode));
    DListNode* head = (DListNode *)malloc(sizeof(DListNode));
    init(head);
    while (1) {
        main_menu();
        scanf("%d", &menu);
        printf("\n");

        if (menu == 0) {
            printf("모든 노드를 삭제하고, 종료합니다.....\n");
            for (DListNode* p = head; p != head; p = p->rlink) free(p);
            return 0;
        }

        else {
            switch (menu) {
            case 1:
                insert_node(head, input());
                break;

            case 2:
                printf("-----------------------------------------\n");
                printf("노드의 개수는 총 %d개 입니다.\n", list_length(head));
                printf("-----------------------------------------\n");
                break;

            case 3:
                print_dlist(head);
                break;

            case 4:
                play_music(head);
                break;

            case 5:
                name_search(head);
                break;

            case 6:
                terms = name_search(head);
                if (terms == NULL) {
                    break;
                }
                ddelete(head, terms);
                break;

            case 7:
                search_year(head);
                break;

            case 8:
                search_genre(head);
                break;

            default:
                printf("            [잘못된 선택입니다.]\n");
                break;
            }
        }
    }
}