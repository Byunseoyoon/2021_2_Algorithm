#include<stdio.h>
#include<stdlib.h>
#define INF 999
#define MAX 10 //��Ʈ������ �ִ� ��, ��

//���� ���
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

int parent[MAX];  //�� ������ �θ� ���
int edge_num = 0; //������ ����

typedef struct{
    int u, v,weight;  //���� u, v���� ������ ����ġ
}Edge;

void prim(int); //���� �˰���
int getMinVertex(int*, int*);  //�������� �Ÿ��� ������ �ִ� ���� ã��

void kruskal();  //ũ�罺Į �˰���
//union-find ���
void set_init(); //�ʱ�ȭ
void set_union(int, int);  //�� ���� ��ġ��(union �����)
int set_find(int);  //���� ������ �θ��ȯ
int compare(const void* a, const void* b);
void edge_set(Edge*);

int main(void) //�����Լ�
{
    printf("<-------v1���� ����------->\n");
    prim(0);
    printf("\n");

    printf("<-------v8���� ����------->\n");
    prim(7);
    printf("\n");

    printf("<-------kruskal------->\n");
    kruskal();

    return 0;
}

int getMinVertex(int* selected, int *distance) {  //���� ���� ����ġ(�Ÿ�)�� ���� ã��
    int i, minv;
    for (i = 0; i < MAX; i++)   //���õ��� ���� ������ minv�� ����
        if (!selected[i]) {  
            minv = i;
            break;
        }

    for (i = 0; i < MAX; i++) {  //�ּ� ����ġ�� ������ �ִ� ���� ã��  
        if (!selected[i] && (distance[i] < distance[minv]))  //���� ���� ���� ����, ����ġ ��
            minv = i;
    }
    return minv;
}

void prim(int start)
{
    int i, minv;
    int selected[MAX];  //MST�� ���ԵǾ� �ִ� ���� �̸� 1, �ƴϸ� 0 ����
    int distance[MAX];  //���� �������� �����ϴ� ������ ����ġ

    for (i = 0 ; i < MAX; i++) {      //�ʱ�ȭ
        selected[i] = 0;             //MST�� ���Ե� ������ ���� ������ 0���� �ʱ�ȭ
        distance[i] = W[start][i];     // vi�� v1�� �մ� �������� ����ġ�� �ʱ�ȭ
    }

    for (i = 0; i < MAX; i++) {    //��� ���� ����
        minv = getMinVertex(selected, distance);  //���� ���� ����ġ ���� ã��
        selected[minv] = 1;  //�湮�� 1���
        
        if (distance == INF) return; //��ΰ� ���ٸ� �Լ� ����
        
        for (int k = 0; k < MAX; k++) {
            if(W[minv][k]==distance[minv])
                printf("���� v%d - v%d ����\n", k+1 ,minv + 1);
        }

        for (int k = 0; k < MAX; k++) { //���Ӱ� �߰��� ���� ����
            if (W[minv][k] != INF) {  //���õ� ������ �������� ������ ����Ǿ� �ִ� ���������� �Ÿ� ��
                if (!selected[k] && (W[minv][k] < distance[k]))
                    distance[k] = W[minv][k];    // �Ÿ��� �� ���� ����ġ�� �Ÿ� ����
            }
        }
    }
}

//�ʱ�ȭ
void set_init() {   
    for (int i = 0; i < MAX; i++) 
        parent[i] = -1;      //�θ� ����� �迭�� ��� -1�� �ʱ�ȭ
}
//������ ���ϴ� ������ ��Ʈ ��ȯ
int set_find(int vertex) {
    while (parent[vertex] != -1) vertex = parent[vertex]; // parent�� Ÿ��Ÿ�� ��Ʈ ��� ã��
    return vertex;
}
//�� ���� ��ġ��
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2) parent[root1] = root2; // �θ� ��峢�� ���� ������ root1�� �θ� root2�� ��ħ
    printf("���� v%d - v%d ����",a+1,b+1);

    printf("\n");
}
//qsort (��������)�񱳸� ���� �Լ�
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return ((x->weight) - (y->weight));
}
//�������� ���� �����
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
    int edge_selected_num = 0; //������� ���õ� ������ ��
    int u, v;

    Edge edge[MAX * 2];
    edge_set(edge);
    qsort(edge, edge_num, sizeof(Edge), compare);
    set_init();

    for (int i = 0; edge_selected_num < (MAX - 1); i++) {
        u = edge[i].u;
        v = edge[i].v;
        if (set_find(u) != set_find(v)) {  //����Ŭ�� ������� Ȯ��
            edge_selected_num++;
            set_union(u, v);
        }
    }

}