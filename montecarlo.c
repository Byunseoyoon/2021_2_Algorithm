#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define N 8


//11
int col[N + 1];   
int promising(int);   //유망한가
int estimate_n_queens(int);

//14 
const int w[6] = { 2,10,13,17,22,42 };
int include[6] = { 0, };
int W = 52;
int s_promising(int, int, int);
void sum_of_subset(int, int, int);
void print();

//17
int estimate_sum_of_subsets(int);
int _w[6] = { 2,10,13,17,22,42 };
int _include[6] = { 0, };

int main(void) {
	srand((unsigned int)time(NULL));
	//11번
	int average = 0;

	for (int i = 0; i < 20; i++) {
		int nodes = estimate_n_queens(N);
		printf("%2d run : %d개\n", i + 1, nodes);
		if (nodes) {
			average += nodes;
		}
	}

	printf("평균 노드 개수 : %d\n", average / 20);

	printf("\n");

	//14번
	int num;
	int total = 0;

	for (int i = 0; i < 6; i++)
		total += w[i];

	sum_of_subset(0, 0, total);
	
	//17번
	int numnode = 0, total_node=0;
	for (int i = 0; i < 20; i++) {
		numnode = estimate_sum_of_subsets(6);

		printf("%2d run : %d개\n", i + 1, numnode);

		for (int m = 0; m < 6; m++) {
			_w[m] = w[m];
			_include[m] = 0;
		}
		total_node += numnode;
	}
	printf("평균 노드 개수 : %d\n", total_node / 20);
	
	return 0;
}

int estimate_n_queens(int n) {
	int i, j;
	int m, mprod, numnodes;
	int prom_children[N + 1] = { 0, };

	i = 0;
	numnodes = 1;
	m = 1;
	mprod = 1;

	while (m != 0 && i != n) {
		mprod = mprod * m;
		numnodes = numnodes + mprod * n;
		i++;
		m = 0;

		for (int k = 1; k <= N; k++) prom_children[k] = 0;

		for (j = 1; j <= n; j++) {
			col[i] = j;
			if (promising(i)) {
				prom_children[m] = j;
				m++;
			}
		}
		if (m != 0) {
			int index = 0;

			for (int k = 1; k <= N; k++)
				if (prom_children[k] != 0) index++;
			if (index == 0) index = 1;

			int random = (rand() % index) + 1;
			j = prom_children[random];
			col[i] = j;
		}
	}
	return numnodes;
}

int promising(int i) {  //유망한지 확인하는 함수
	int k = 1;
	int result = 1;

	while (k < i && result) {
		if (col[i] == col[k] || abs(col[i] - col[k]) == i - k) //같은 열 또는 대각선상에 있는지 확인
			result = 0;
		k++;
	}
	return result;
}



void sum_of_subset(int i, int weight, int total) {
	if (s_promising(i, weight, total)) {  //유망한가? 검사
		if (weight == W) {
			print();
		}
		else {
			//가중치를 포함했을 경우
			include[i + 1] = w[i + 1];
			sum_of_subset(i + 1, weight + w[i + 1], total - w[i - 1]);
			//가중치를 포함 안 했을 경우
			include[i + 1] = 0;
			sum_of_subset(i + 1, weight, total - w[i + 1]);
		}
	}
}

void print() {
	for (int j = 0; j < 6; j++) {
		if (include[j] != 0)
			printf("include[%d]: %d\n", j, include[j]); //정답 출력
	}
	printf("\n");
}

int s_promising(int i, int weight, int total) {
	if (weight + total >= W && (weight == W || weight + w[i + 1] <= W))
		return 1;
	return 0;
}

int estimate_sum_of_subsets(int n) {
	int i, j, m;
	int mprod, numnodes, weight = 0, total = 106;
	int prom_children[6] = { 0, }; //현재 깊이에서 유망한 자식 노드값 저장
	
	i = 0;
	numnodes = 1;
	m = 1;
	mprod = 1;

	while (m != 0 && i != 6) {
		mprod = mprod * m;
		numnodes = numnodes + mprod * 2;
		i++;
		m = 0;

		for (int k = 1; k <= N; k++) 
			if(k==0) prom_children[k] = 0;

		for (j = 1; j < 6; j++) {
			if (_w[j] != 0) {
				_include[j] = j;
				if (s_promising(i, weight, total)) {  //유망한지 확인 후 포함
					m++;
					prom_children[j] = _w[j];
				}
			}
		}
		if (m != 0) {
			while (1) {
				j = (rand() % 5) + 1;
				if (prom_children[j] != 0) break;
			}
			_include[j] = j;
			_w[j] = 0;
			weight += prom_children[j];
			total -= prom_children[j];
		}
	}
	return numnodes;
}