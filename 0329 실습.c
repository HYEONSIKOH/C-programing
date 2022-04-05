/*
(1) 이차원 배열에 저장된 희소행렬을 SparseMatrix 구조로 저장하는 함수 (o)

(2) 두 개의 SparseMatrix를 매개변수로 받아서 덧셈한 결과로 SparseMatrix를 반환하는 함수 (o)

(3) SparseMatrix에 저장된 내용을 0을 포함한 이차원 형렬 형태로 출력하는 함수 (o)


- main()에서 테스트하기

위 배열 a[][], b[][], c[][]를 (1)을 이용하여 각각 SparseMatrix A, B, C로 변환하기

A+B를 (2)로 계산하고,반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기

A+C를 (2)로 계산하여 반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기

B+C를 (2)로 계산하여 반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기*/
#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 항의 개수
} SparseMatrix;

SparseMatrix Change_matrix (int ar,int ac,int *a){ //변환 함수
    SparseMatrix b;
    int c = 0;

    for (int i = 0; i < ar; i++) {
        for (int j = 0; j < ac; j++) {
            if (*a != 0) {
                b.data[c].row = i;
                b.data[c].col = j;
                b.data[c++].value = *a;
            }
            *a++;
        }
    }
    b.terms = c;
    b.rows = ar;
    b.cols = ac;

    return b;
}

void Print_matrix(SparseMatrix a) { //출력 함수
    int in = 0;
    int zero = 0;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (a.data[in].row == i && a.data[in].col == j)
                printf("%2d ", a.data[in++].value);
           
            else
                printf("%2d ",zero);
        }
        printf("\n");
    }
}

SparseMatrix Add_matrix(SparseMatrix a, SparseMatrix b) { //덧셈 함수
    SparseMatrix sum;
    int ia = 0, ib = 0, ic = 0;
    sum.rows = a.rows;
    sum.cols = b.cols;
    int pos_a, pos_b;

    while (ia < a.terms && ib < b.terms) {
        pos_a = a.data[ia].row * a.rows + a.data[ia].col;
        pos_b = b.data[ib].row * b.rows + b.data[ib].col;

        if (pos_a < pos_b)
            sum.data[ic++] = a.data[ia++];

        else if (pos_a == pos_b) {
            if (a.data[ia].value + b.data[ib].value != 0) {
                sum.data[ic].row = a.data[ia].row;
                sum.data[ic].col = a.data[ia].col;
                sum.data[ic++].value = a.data[ia++].value + b.data[ib++].value;
            }

            else {
                ia++;
                ib++;
            }
        }

        else
            sum.data[ic++] = b.data[ib++];
    }

   while (ia < a.terms)
        sum.data[ic++] = a.data[ia++];
   
    while (ib < b.terms)
        sum.data[ic++] = b.data[ib++];
   

    sum.terms = ic;
    return sum;
}

int main(void) {
    SparseMatrix as, bs, cs;
    SparseMatrix sum_a, sum_b, sum_c;
    int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };




    int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };



    int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

                     { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };

   as = Change_matrix(8, 10, a);
   bs = Change_matrix(8, 10, b);
   cs = Change_matrix(8, 10, c);

  printf("A+B-----------------------------------\n");
   sum_a = Add_matrix(as,bs);
   Print_matrix(sum_a);

   printf("A+C-----------------------------------\n");
   sum_b = Add_matrix(as, cs);
   Print_matrix(sum_b);

   printf("B+C-----------------------------------\n");
   sum_c = Add_matrix(bs, cs);
   Print_matrix(sum_c); 

   return 0;
}
