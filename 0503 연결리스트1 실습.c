/*
(1) ������ { ���ڿ� �������� ���ڿ� ����(������) ���� �帣 ���� ��ǥ�⵵ } �� �����ϴ�
    ('B' 'C' 'H' 'J' 'T' ) ���Ḯ��Ʈ ����� �ڷᱸ�� ���� ���⼭ �帣�� �� �ϳ�
(2) insert_node( ) : �� ��带 ���� ����Ʈ�� Ư�� ��ġ�� �����ϴ� �Լ� �ۼ�
(3) list_length( ) : ���� ����Ʈ�� ����� ����� ������ ����ؼ� ��ȯ�ϴ� �Լ� �ۼ�
(4) list_display( ) : ���� ����Ʈ�� ����� �� ��忡�� { ��������, ����(������), �帣, ��ǥ�⵵} �� ���

main() : �Լ������� �� ����Ʈ���� �����Ͽ� �Ʒ��� ���� �޴��� �׽�Ʈ

      -  �����ϴ� ���ǿ� ���� �����͸� ������ �� ��带 �����, 
         ���� ����Ʈ�� ���� ������ ���������� �����ϵ��� ����
      - list_length( ) , �� ȣ���Ͽ� ���� ����Ʈ�� ����� ����� ������ ���
      - list_display( )�� ȣ���Ͽ� ���� ����Ʈ�� ����� �� ����� �����͸� ���*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    char name[100]; // �뷡 �̸�
    char singer[30]; // ����
    char genre; // �帣
    int year; // ����
}element;

typedef struct ListNode{ // ��� Ÿ��
    element data;
    struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element value) { // ��� ��� ����
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head; // ��� �������� ���� ����
    head = p;       // ��� ������ ����
    return head;    // ����� ��� ������ ��ȯ
}
ListNode* insert(ListNode* head, ListNode* pre, element value) { // �߰� ��� ����
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* insert_node(ListNode* head, element item) { // �������� ��� ����
    ListNode* p = head;

    if (head == NULL || (strcmp(head->data.name, item.name) >= 0)) head = insert_first(head, item); // head�� name ���� item�� name ������ ���������� ���� �� , head�� ���� ������� ��,

    else {
        while (p->link != NULL) {
            if (strcmp(p->link->data.name, item.name) > 0) { // p�� name ���� item�� name ������ ���������� ���� ��
                head = insert(head, p, item);
                return head;
            }
            p = p->link;
        }
        head = insert(head, p, item); // ������ ���µ�, ���������� �ڰ� ���� ��
        return head;
    }
}

int list_length(ListNode* head) { // ����� ������ ��ȯ�ϴ� �Լ�
    ListNode* p = head;
    int count = 0;

    for (ListNode* p = head; p != NULL; p = p->link) count++;
    
   
    return count;
}

element input(){ // �뷡 ���� �Է� �Լ�
    printf("�뷡 ���� , ����(������), �帣 (B, C, H, J, T), �߸� �⵵�� �Է����ּ���\n");
    printf("�Է�: ");
    element p;
    scanf("%s %s %c %d", p.name, p.singer, &p.genre, &p.year);
    printf("\n\n\n");
    return p;
}

void list_display(ListNode* head) { // �� ��� ���
    printf("-----------------------------------------\n");
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("�뷡����: %-20s ����: %-10s �帣: %-2c �߸ų⵵: %-4d\n", p->data.name, p->data.singer, p->data.genre, p->data.year);
    printf("-----------------------------------------\n");
}

void main_menu() {
    printf("------------------ [MENU] ------------------\n");
    printf("0. ����\n");
    printf("1. ������������ �Է�\n");
    printf("2. ����� ����\n");
    printf("3. �� ��� ���\n");
    printf("--------------------------------------------\n");
    printf("�Է�: ");
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
            printf("�����մϴ�.....\n");
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
                printf("����� ������ �� %d�� �Դϴ�.\n", list_length(head));
                printf("-----------------------------------------\n");
                break;

            case 3:
                list_display(head);
                break;
            
            default:
                printf("            [�߸��� �����Դϴ�.]\n");
                break;
            }
        }
    }
}