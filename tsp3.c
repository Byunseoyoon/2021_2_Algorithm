#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 7
#define INF 1e9

//�������
int W[N + 1][N + 1] = {
    {0,0,0,0,0,0,0,0},
    {0,0,4,INF,INF, INF, 10, INF},
    {0,3,0,INF,18,INF,INF,INF},
    {0,INF,6,0,INF,INF,INF,INF},
    {0, INF,5,15,0,2,19,5},
    {0,INF,INF,12,1,0,INF,INF},
    {0,INF,INF,INF,INF,INF,0,10},
    {0, INF, INF, INF, 8, INF, INF, 0}
};

//bit flag ���  

int P[N + 1][1 << (N - 1)] = { 0 }; // ��� ����
int bits[N + 1] = { 0, 0, 1, 1 << 1, 1 << 2, 1<<3, 1<<4, 1<<5 }; // n��° ������ ��Ʈ
int D[N + 1][1 << (N - 1)]; // D
int max_bit = (1 << (N - 1)) - 1; // full �϶��� ��Ʈ
int bit_print[N + 1];
int patharr[N + 1] = { 0 };

int get_vertex(int num);
void print_seq(int i, int num, int min);
void path_print(int, int);  //path ã�� �Լ�

int main(void) {
    for (int i = 2; i <= N; i++) {  //A�� ������(0��) �϶� ����
        D[i][0] = W[i][1];
        print_seq(i, 0, W[i][1]);
    }

    for (int k = 1; k <= N - 2; k++) {  // �߰��� ��ġ�� ���� 1~(N-2)�� �϶�, �� k�� ���� ������ ����
        for (int num = 0; num < 1 << (N - 1); num++) {  //num => ������ ���ҵ�(����) ��Ʈ�� ������ ��(A�� �κ�����)
            if (get_vertex(num) != k) continue;  //������ ������ ������ ������ Ȯ��(�κ����� ���� Ȯ��)
            for (int i = 2; i <= N; i++) {
                if ((num & bits[i]) != 0) continue;
                int min = INF;
                for (int j = 2; j <= N; j++) {  //D[i][A]�� �ּڰ� ã��
                    if ((num & bits[j]) == 0) continue;
                    int sum = W[i][j] + D[j][num & (~bits[j])];
                    if (min > sum) {
                        min = sum;
                        P[i][num] = j;  //i���� num�� �κ��������� ���� ��� ����
                    }
                }
                D[i][num] = min;
                print_seq(i, num, min); //���
            }
        }
    }

    int min = INF;
    for (int j = 2; j <= N; j++) {  //v1����~
        int sum = W[1][j] + D[j][max_bit & (~bits[j])];
        if (min > sum) {
            min = sum;
            P[1][max_bit] = j;
        }
    }
    print_seq(1, max_bit, min);  //���

    patharr[1] = 1;
    path_print(1, max_bit, 2);

    printf("\n\n���� ���� ��� : ");
    for (int i = 1; i <= N; i++) {
        printf("v%d - ", patharr[i]);
    } printf("v1\n\n");

    printf("���� ���� ����� �� : %d\n", min);

    return 0;
}

int get_vertex(int num) {  //���� ���� ȯ��(�κ������� ���� ����)
    int cnt = 0;
    for (; num != 0; num >>= 1) {
        if (num & 1) cnt++;
    }
    return cnt;
}
void print_seq(int i, int num, int min) {
    int bit_n = 0;
    int j;
    for (j = 2; j <= N; j++) {
        if ((num & bits[j]) != 0) {
            bit_print[bit_n++] = j;
        }
    }
    printf("D[v%d][{", i);
    for (j = 0; j < bit_n - 1; j++) {
        printf("v%d, ", bit_print[j]);
    }
    if (bit_print[j] != 0) printf("v");
    printf("%d}] = ", bit_print[j]);
    if (min == INF) printf("��\n");
    else printf("%d\n", min);
}

void path_print(int q, int r, int i) {
    patharr[i++] = P[q][r];
    if (P[q][r] != 0) {
        int tmp = P[q][r];
        path_print(tmp, r - bits[tmp], i);
    }
}
