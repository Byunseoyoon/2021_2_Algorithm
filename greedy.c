#include<stdio.h>
#include<stdlib.h>
#define INF 999
#define MAX 10 //매트릭스의 최대 행, 열

//인접 행렬
int W[MAX][MAX] = {
    {0,32,INF,17,INF,INF,INF,INF,INF,INF},
    {32,0,INF,INF,45,INF,INF,INF,INF,INF},
    {INF,INF,0,18,INF,INF,5,INF,INF,INF},
    {17,INF,18,0,10,INF,INF,3,INF,INF},
    {INF,45,INF,10,0,28,INF,INF,25,INF},
    {INF,INF,INF,INF,28,0,INF,INF,INF,6},
    {INF,INF,5,INF,INF,INF,0,59,INF,INF},
    {INF,INF,INF,3,INF,INF,59,0,4,INF},
    {INF,INF,INF,INF,25,INF,INF,4,0,12},
    {INF,INF,INF,INF,INF,6,INF,INF,12,0}
};

int parent[MAX];  //각 정점의 부모 노드
int edge_num = 0; //간선의 개수

typedef struct{
    int u, v,weight;  //정점 u, v사이 간선의 가중치
}Edge;

void prim(int); //프림 알고리즘
int getMinVertex(int*, int*);  //가장작은 거리를 가지고 있는 정점 찾기

void kruskal();  //크루스칼 알고리즘
//union-find 사용
void set_init(); //초기화
void set_union(int, int);  //두 집합 합치기(union 만들기)
int set_find(int);  //정점 집합의 부모반환
int compare(const void* a, const void* b);
void edge_set(Edge*);

int main(void) //메인함수
{
    printf("<-------v1부터 시작------->\n");
    prim(0);
    printf("\n");

    printf("<-------v8부터 시작------->\n");
    prim(7);
    printf("\n");

    printf("<-------kruskal------->\n");
    kruskal();

    return 0;
}

int getMinVertex(int* selected, int *distance) {  //가장 작은 가중치(거리)의 정점 찾기
    int i, minv;
    for (i = 0; i < MAX; i++)   //선택되지 않은 정점을 minv에 저장
        if (!selected[i]) {  
            minv = i;
            break;
        }

    for (i = 0; i < MAX; i++) {  //최소 가중치를 가지고 있는 정점 찾기  
        if (!selected[i] && (distance[i] < distance[minv]))  //연결 되지 않은 정점, 가중치 비교
            minv = i;
    }
    return minv;
}

void prim(int start)
{
    int i, minv;
    int selected[MAX];  //MST에 포함되어 있는 정점 이면 1, 아니면 0 저장
    int distance[MAX];  //인접 정점들을 연결하는 간선의 가중치

    for (i = 0 ; i < MAX; i++) {      //초기화
        selected[i] = 0;             //MST에 포함된 정점이 아직 없으니 0으로 초기화
        distance[i] = W[start][i];     // vi와 v1을 잇는 이음선의 가중치로 초기화
    }

    for (i = 0; i < MAX; i++) {    //모든 정점 조사
        minv = getMinVertex(selected, distance);  //가장 작은 가중치 정점 찾기
        selected[minv] = 1;  //방문시 1등록
        
        if (distance == INF) return; //경로가 없다면 함수 종료
        
        for (int k = 0; k < MAX; k++) {
            if(W[minv][k]==distance[minv])
                printf("정점 v%d - v%d 연결\n", k+1 ,minv + 1);
        }

        for (int k = 0; k < MAX; k++) { //새롭게 발견한 정보 저장
            if (W[minv][k] != INF) {  //선택된 정점을 기준으로 정점과 연결되어 있는 정점까지의 거리 비교
                if (!selected[k] && (W[minv][k] < distance[k]))
                    distance[k] = W[minv][k];    // 거리가 더 작은 가중치로 거리 갱신
            }
        }
    }
}

//초기화
void set_init() {   
    for (int i = 0; i < MAX; i++) 
        parent[i] = -1;      //부모 노드의 배열은 모두 -1로 초기화
}
//정점이 속하는 집합의 루트 반환
int set_find(int vertex) {
    while (parent[vertex] != -1) vertex = parent[vertex]; // parent를 타고타고 루트 노드 찾기
    return vertex;
}
//두 집합 합치기
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2; // 부모 노드끼리 같지 않으면 root1의 부모를 root2로 합침
    printf("정점 v%d - v%d 연결",a+1,b+1);

    printf("\n");
}
//qsort (오름차순)비교를 위한 함수
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return ((x->weight) - (y->weight));
}
//간선들의 집합 만들기
void edge_set(Edge *edge) {
    for (int i = 0; i < MAX; i++)
        for (int k = i; k < MAX; k++)
            if (W[i][k] != INF && W[i][k] != 0) {
                edge[edge_num].weight = W[i][k];
                edge[edge_num].u = i;
                edge[edge_num].v = k;
                edge_num++;
            }
}
void kruskal() {
    int edge_selected_num = 0; //현재까지 선택된 간선의 수
    int u, v;

    Edge edge[MAX * 2];
    edge_set(edge);
    qsort(edge, edge_num, sizeof(Edge), compare);
    set_init();

    for (int i = 0; edge_selected_num < (MAX - 1); i++) {
        u = edge[i].u;
        v = edge[i].v;
        if (set_find(u) != set_find(v)) {  //사이클이 생기는지 확인
            edge_selected_num++;
            set_union(u, v);
        }
    }

}