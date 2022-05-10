/*
�������� ���α׷��� �ܼ����Ḯ��Ʈ���� ���߿��Ḯ��Ʈ�� �����Ͽ� �����Ͻÿ�.
( 1) (1~10 ) . �� �������ʵ忡 ����ð� �� �� ����Ÿ������ �߰��ȴ�
( 2) 230-231 . �� ���� �ʿ� ���õ� ����带 ���´�
����޴����� ������ ���� ����� ���� �Ǵ� �߰��Ѵ�.
(1) , , . �����Լ� ��尳�� ����Լ� ��ü����Լ��� ���߿��Ḯ��Ʈ�� �µ��� ����
(2) : ������������ �ڷ� �˻��ϴ� �Լ�
 , NULL ����Ʈ���� ã���� �ش� ��带 ��ȯ�ϰ� ����Ʈ�� �������� ������ ��ȯ
(3) . Ư�� ���ǿ� ���� ��带 �����ϴ� �Լ�
(4) . ���� �ֱٿ� ��ǥ�� ������ �˻��ϴ� �Լ�
(5) . ���ϴ� �帣�� ���ǵ鸸 ����ϴ� �Լ�
(6) ��P�� : ����޴� �� �߰��Ѵ�
 - ȣ���Լ��� ���� ����� ����ð���ŭ ����Ѵ� ����ð��� �� �� ������ ���� ( 0 )
 progressive bar( ..........) �ð��� ȿ���� ���� �� ��� ����
 - . ����� �Ϸ�Ǹ� �ڵ����� ���� ���� �̵��Ѵ�
(7) ��>�� . ���� ����� ���� ���� �̵��ؼ� ����ϴ� �� �߰��Ѵ�
(8) ��<�� . ���� ����� ���� ���� �̵��ؼ� ����ϴ� �� �߰��Ѵ�
(9) ��F/f�� . �� ���� ��ȭ�� �̵��ؼ� ����ϴ� �� �߰��Ѵ�
(10) ��L/l�� .
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char name[100]; // �뷡 �̸�
    char singer[30]; // ����
    char genre; // �帣
    int year; // ����
    int play_time;
}element;

typedef struct ListNode { // ��� Ÿ��
    element data;
    struct ListNode* rlink;
    struct ListNode* llink;
}DListNode;

//����Ʈ�� �ʱ�ȭ
void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// ��� �Է�
void dinsert(DListNode* before, element data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));

    newnode->data = data;
    newnode->llink = before; // ���ο� ����� ���� ��ũ�� before ��带 ����
    newnode->rlink = before->rlink; // ���ο� ����� ������ ���� before�� ������ ��ũ�� ����

    before->rlink->llink = newnode; // before�� ���� �տ� �ִ� ����� ������ ��ũ��
    before->rlink = newnode; // before�� ���� ��ũ�� newnode�� �����Ų��.
}

// ��� removed�� �����Ѵ�.
void ddelete(DListNode* head, DListNode* removed) {
    if (removed == head) return;

    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;

    free(removed);
}

// ��� ��ü�� ���
void print_dlist(DListNode* head) {
    for (DListNode* p = head->rlink; p != head; p = p->rlink)
        printf("�뷡����: %-20s ����: %-10s �帣: %-2c �߸ų⵵: %-4d  ����ð�:%d\n", p->data.name, p->data.singer, p->data.genre, p->data.year,p->data.play_time);
}

// ����� ������ ��ȯ�ϴ� �Լ�
int list_length(DListNode* head) {
    int count = 0;

    for (DListNode* p = head->rlink; p != head; p = p->rlink) count++;

    return count;
}

// �������� ��� ����
void insert_node(DListNode* head, element item) {
    DListNode* p = head->rlink;

    if (head->rlink == head || (strcmp(head->rlink->data.name, item.name) >= 0)) {
        dinsert(head, item); // head�� ���� ������� ��,
        return;
    }

    else {
        while (p->rlink != head) {
            if (strcmp(p->rlink->data.name, item.name) > 0) { // p�� name ���� item�� name ������ ���������� ���� ��
                dinsert(p, item);
                return;
            }
            p = p->rlink;
        }
        dinsert(p, item); // ������ ���µ�, ���������� �ڰ� ���� ��
    }
}

element input() { // �뷡 ���� �Է� �Լ�
    printf("�뷡 ���� , ����(������), �帣 (B, C, H, J, T), �߸� �⵵, ����ð� �� �Է����ּ���\n");
    printf("�Է�: ");
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
    printf("���� �ֱٿ� �߸ŵ� ������, %d�� \"%s\" �Դϴ�.\n", max, terms->data.name);
}

void main_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. ����\n");
    printf("1. ������������ �Է�\n");
    printf("2. ����� ����\n");
    printf("3. �� ��� ���\n");
    printf("4. ���� ���\n");
    printf("5. ���� ���� �˻�\n");
    printf("6. ���ϴ� ���� ����\n");
    printf("7. ���� �ֱٿ� ��ǥ�� ���� �˻�\n");
    printf("8. ���ϴ� �帣 �˻� �� ���\n");
    printf("--------------------------------------------\n");
    printf("�Է�: ");
}

void play_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. ����\n");
    printf("p. ���\n");
    printf(">. ������ ���\n");
    printf("<. ������ ���\n");
    printf("F/f. ó���� ���\n");
    printf("L/l. �������� ���\n");
    printf("--------------------------------------------\n");
    printf("�Է�: ");
}

void play_music_message(DListNode * head, DListNode * p) {
    int count = p->data.play_time;
    printf("���� \"%s\" ���� ������Դϴ�....\n",p->data.name);
    for (int i = 1; i <= count; i++) {
        printf("...\n", i);
        Sleep(1000);
    }
    p = p->rlink;

    if (p == head)
        p = p->rlink;

    printf("\n");
}

DListNode* name_search(DListNode* head) { // �̸��� �˻��ؼ� ���
    if (head->rlink == head) {
        printf("����� ���� �����ϴ�.\n");
        return NULL;
    }
    printf("���� ������ �Է����ּ���: ");
    char n[30] = { 0, };
    scanf("%s", n);
    printf("\n");
    DListNode* p = head->rlink;
    while (p != head) {
        if (strcmp(n, p->data.name) == 0) {
            printf("����: %s  ����:%s  �帣: %c  �⵵: %d ����ð�: %d��\n", p->data.name, p->data.singer, p->data.genre, p->data.year, p->data.play_time);
            return p;
        }
        p = p->rlink;
    }
    printf("���� ������ �����ϴ�.\n");
    return NULL;
}

void* search_genre(DListNode* head) {
    if (head->rlink == head) {
        printf("����� ���� �����ϴ�.\n");
        return;
    }
    printf("�帣 (B, C, H, J, T) �Ѱ����� �Է����ּ���: ");
    char genre;
    scanf(" %c", &genre);
    int count = 0;

    for (DListNode* p = head->rlink; p != head; p = p->rlink) {
        if (genre == p->data.genre) {
            printf("�뷡����: %-20s ����: %-10s �帣: %-2c �߸ų⵵: %-4d ����ð�:%d\n", p->data.name, p->data.singer, p->data.genre, p->data.year, p->data.play_time);
            count++;
        }
    }

    if (count == 0)
        printf("���� �帣�� ������ �����ϴ�.\n");
}

void play_music(DListNode * head) {
    DListNode* p = head->rlink;
    if (head->rlink == head) {
        printf("����� ���� �����ϴ�.\n");
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
            printf("ù��° ������ �̵��մϴ�.\n ");
            p = head->rlink;
            play_music_message(head,p);
            break;

        case 'L': case 'l':
            printf("������ ������ �̵��մϴ�.\n ");
            p = head->llink;
            play_music_message(head,p);
            break;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
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
            printf("��� ��带 �����ϰ�, �����մϴ�.....\n");
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
                printf("����� ������ �� %d�� �Դϴ�.\n", list_length(head));
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
                printf("            [�߸��� �����Դϴ�.]\n");
                break;
            }
        }
    }
}