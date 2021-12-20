#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 7
#define INF 1e9

//인접행렬
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

//bit flag 사용  

int P[N + 1][1 << (N - 1)] = { 0 }; // 경로 저장
int bits[N + 1] = { 0, 0, 1, 1 << 1, 1 << 2, 1<<3, 1<<4, 1<<5 }; // n번째 원소의 비트
int D[N + 1][1 << (N - 1)]; // D
int max_bit = (1 << (N - 1)) - 1; // full 일때의 비트
int bit_print[N + 1];
int patharr[N + 1] = { 0 };

int get_vertex(int num);
void print_seq(int i, int num, int min);
void path_print(int, int);  //path 찾는 함수

int main(void) {
    for (int i = 2; i <= N; i++) {  //A가 공집합(0개) 일때 저장
        D[i][0] = W[i][1];
        print_seq(i, 0, W[i][1]);
    }

    for (int k = 1; k <= N - 2; k++) {  // 중간에 거치는 값이 1~(N-2)개 일때, 즉 k는 집합 원소의 개수
        for (int num = 0; num < 1 << (N - 1); num++) {  //num => 집합의 원소들(정점) 비트로 저장한 값(A의 부분집합)
            if (get_vertex(num) != k) continue;  //원소의 개수와 집합이 같은지 확인(부분집합 개수 확인)
            for (int i = 2; i <= N; i++) {
                if ((num & bits[i]) != 0) continue;
                int min = INF;
                for (int j = 2; j <= N; j++) {  //D[i][A]의 최솟값 찾기
                    if ((num & bits[j]) == 0) continue;
                    int sum = W[i][j] + D[j][num & (~bits[j])];
                    if (min > sum) {
                        min = sum;
                        P[i][num] = j;  //i에서 num의 부분집합으로 가는 경로 저장
                    }
                }
                D[i][num] = min;
                print_seq(i, num, min); //출력
            }
        }
    }

    int min = INF;
    for (int j = 2; j <= N; j++) {  //v1부터~
        int sum = W[1][j] + D[j][max_bit & (~bits[j])];
        if (min > sum) {
            min = sum;
            P[1][max_bit] = j;
        }
    }
    print_seq(1, max_bit, min);  //출력

    patharr[1] = 1;
    path_print(1, max_bit, 2);

    printf("\n\n최적 일주 경로 : ");
    for (int i = 1; i <= N; i++) {
        printf("v%d - ", patharr[i]);
    } printf("v1\n\n");

    printf("최적 일주 경로의 값 : %d\n", min);

    return 0;
}

int get_vertex(int num) {  //정점 개수 환산(부분집합의 원소 갯수)
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
    if (min == INF) printf("∞\n");
    else printf("%d\n", min);
}

void path_print(int q, int r, int i) {
    patharr[i++] = P[q][r];
    if (P[q][r] != 0) {
        int tmp = P[q][r];
        path_print(tmp, r - bits[tmp], i);
    }
}
