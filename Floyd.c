#include<stdio.h>

const int INF = 987654321;

void floyd(int[][8]); //�÷��̵� �˰���
void print(int[][8]); //�迭 ��� �Լ�
void path(int[][8], int, int); //�ִܰ�� ���� ã�� �Լ�
void resetP(int[][8]); //P�� 0���� �ʱ�ȭ �ϴ� �Լ�

int main(void) {

	int D[8][8] = {{0,0,0,0,0,0,0,0}, {0,0,4,INF,INF, INF, 10, INF},{0,3,0,INF,18,INF,INF,INF},{0,INF,6,0,INF,INF,INF,INF},
		{0, INF,5,15,0,2,19,5},{0,INF,INF,12,1,0,INF,INF},{0,INF,INF,INF,INF,INF,0,10},{0, INF, INF, INF, 8, INF, INF, 0}};

	int P[8][8];

	// P��� 0���� �ʱ�ȭ
	resetP(P);
	
	//�ʱⰪ ���
	printf("-----��-----\n");
	print(D);

	floyd(D, P); 
	
	//����� ���
	printf("<-----��----->\n");
	print(D);
	
	printf("<-----P----->\n");
	print(P);

	printf("<-----�ִܰ�� ���--->\n");

	path(P, 7, 3);

	resetP(P); //P�ʱ�ȭ

	int D2[8][8] = { {0,0,0,0,0,0,0,0}, {0, 0, INF, INF, INF, INF,INF, 10},{0,INF, 0, 1, 12, INF, INF, INF},{0,19, 2, 0, 15, 5, INF, 5},
		{0, INF, INF, INF, 0,6,INF,INF},{0,INF,INF,18,INF,0,3,INF},{0, 10,INF,INF,INF,4,0,INF},{0, INF,INF,8,INF,INF,INF,0} };

	//�ʱⰪ ���
	printf("\n-----��-----\n");
	print(D2);
	print(P);
	floyd(D2, P);

	//����� ���
	printf("<-----��----->\n");
	print(D2);

	printf("<-----P----->\n");
	print(P);

	printf("<-----�ִܰ�� ���--->\n");

	path(P, 7, 4);

	return 0;
}

//P�ʱ�ȭ �Լ�
void resetP(int P[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			P[i][j] = 0;
		}
	}
}

// �÷��̵� �˰���
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

// �迭 ��� (����� �迭 ����) 
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

//�ִܰ�� Ž�� �� ���
void path(int P[][8], int q, int r) {
	printf("path(%d, %d)= %d\n", q, r, P[q][r]);
	if (P[q][r] != 0) {
		path(P, q, P[q][r]);
		printf(" a%d\n", P[q][r]);
		path(P, P[q][r], r);
	}
}