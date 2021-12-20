#include<stdio.h>

const int INF = 987654321;

void floyd(int[][8]); //플로이드 알고리즘
void print(int[][8]); //배열 출력 함수
void path(int[][8], int, int); //최단경로 정점 찾는 함수
void resetP(int[][8]); //P를 0으로 초기화 하는 함수

int main(void) {

	int D[8][8] = {{0,0,0,0,0,0,0,0}, {0,0,4,INF,INF, INF, 10, INF},{0,3,0,INF,18,INF,INF,INF},{0,INF,6,0,INF,INF,INF,INF},
		{0, INF,5,15,0,2,19,5},{0,INF,INF,12,1,0,INF,INF},{0,INF,INF,INF,INF,INF,0,10},{0, INF, INF, INF, 8, INF, INF, 0}};

	int P[8][8];

	// P모두 0으로 초기화
	resetP(P);
	
	//초기값 출력
	printf("-----전-----\n");
	print(D);

	floyd(D, P); 
	
	//결과값 출력
	printf("<-----후----->\n");
	print(D);
	
	printf("<-----P----->\n");
	print(P);

	printf("<-----최단경로 출력--->\n");

	path(P, 7, 3);

	resetP(P); //P초기화

	int D2[8][8] = { {0,0,0,0,0,0,0,0}, {0, 0, INF, INF, INF, INF,INF, 10},{0,INF, 0, 1, 12, INF, INF, INF},{0,19, 2, 0, 15, 5, INF, 5},
		{0, INF, INF, INF, 0,6,INF,INF},{0,INF,INF,18,INF,0,3,INF},{0, 10,INF,INF,INF,4,0,INF},{0, INF,INF,8,INF,INF,INF,0} };

	//초기값 출력
	printf("\n-----전-----\n");
	print(D2);
	print(P);
	floyd(D2, P);

	//결과값 출력
	printf("<-----후----->\n");
	print(D2);

	printf("<-----P----->\n");
	print(P);

	printf("<-----최단경로 출력--->\n");

	path(P, 7, 4);

	return 0;
}

//P초기화 함수
void resetP(int P[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			P[i][j] = 0;
		}
	}
}

// 플로이드 알고리즘
void floyd(int D[][8], int P[][8]) {
	for (int k = 1; k <= 7; k++) {
		for (int j = 1; j <= 7; j++) {
			for (int i = 1; i <= 7; i++) {
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
			}
		}
		printf("<-----D(%d)----->\n",k);
		print(D);
		print(P);
	}
}

// 배열 출력 (출력할 배열 인자) 
void print(int arr[][8]) {
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			if (arr[i][j] == INF) printf("INF ");
			else printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//최단경로 탐색 및 출력
void path(int P[][8], int q, int r) {
	printf("path(%d, %d)= %d\n", q, r, P[q][r]);
	if (P[q][r] != 0) {
		path(P, q, P[q][r]);
		printf(" a%d\n", P[q][r]);
		path(P, P[q][r], r);
	}
}