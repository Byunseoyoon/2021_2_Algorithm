#include <stdio.h>
#include <stdlib.h>

struct node { //Ʈ������� ���� ���
    char* key;
    struct node* left;
    struct node* right;
};
typedef struct node nodeptr;

float p[7] = { -1, 0.05, 0.15, 0.05, 0.35, 0.05, 0.35 };  //Ȯ�� -1�� NULL�� ���
char* KEY[6] = { {"CASE"}, {"ELSE"}, {"END"}, {"IF"}, {"OF"}, {"THEN"} };   //Ű��


float sum(int, int);
void optsearchtree(int, int**); //���� ����Ʈ�� Ž��
void print(float**, int);
nodeptr* tree(int, int, int**);


int main() {
    int n = 6;
    int** R = (int**)malloc(sizeof(int*) * (n + 2));  //�迭�Ҵ�
    for (int i = 0; i < (n + 2); i++) 
      R[i] = (int*)malloc(sizeof(int) * (n + 1));
   
    
    optsearchtree(n, R);

    nodeptr* head;
    head = tree(1, 6, R); //�迭-> Ʈ�� �����
    for (int i = 0; i < n + 2; i++) {
        free(R[i]);
    }

    return 0;
}

float sum(int start, int end) {
    float total = 0;
    for (int i = start; i <= end; i++) {
        total += p[i];
    }
    return total;
}

void optsearchtree(int n, int** R) {
    int i, j, k, diagonal;
    float** A = (float**)malloc(sizeof(float*) * (n + 2));
    float min;
    for (int s = 0; s < (n + 2); s++) {
        A[s] = (float*)malloc(sizeof(float) * (n + 1));
    }

    //��� ���ϴ� ���� �� �ʱ�ȭ
    for (i = 1; i <= n; i++) {
        A[i][i - 1] = 0;
        A[i][i] = p[i];
        A[0][i - 1] = -1; //NULL�� ��� ����
        R[i][i] = i;
        R[i][i - 1] = 0;
        R[0][i - 1] = -1;  
    }

    A[0][n] = -1;
    A[n + 1][n] = 0;
    R[0][n] = NULL;
    R[n + 1][n] = 0;

    for (diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            min = A[i][i - 1] + A[i + 1][j] + sum(i, j);
            for (k = i; k <= j; k++) {
                if (min >= A[i][k - 1] + A[k + 1][j] + sum(i, j)) {
                    min = A[i][k - 1] + A[k + 1][j] + sum(i, j);
                    R[i][j] = k;
                }
            }
            A[i][j] = min;
        }
    }

    printf("<<-----------A�迭---------->>\n");
    print(A, n);
    for (i = 0; i < n + 2; i++) {
        free(A[i]);
    }
    free(A);

    printf("<<----------R�迭---------->>\n");
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (R[i][j] < 0) printf("  ");
            else printf("%d ", R[i][j]);
        }
        printf("\n");
    }
}

void print(float** A, int n) {
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n; j++) {
            if (A[i][j] < 0) printf("     ");
            else printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }
}

//���� Ʈ���� ����� ����ϴ� �Լ�
nodeptr* tree(int i, int j, int** R) {
    nodeptr* _node = (nodeptr*)malloc(sizeof(nodeptr));
    int k = R[i][j];
    if (k == 0)
        return 0;
    else {
        _node->key = KEY[k - 1];
        _node->left = tree(i, k - 1, R);
        _node->right = tree(k + 1, j, R);
        printf("[%s] -> ", _node->key);
        printf(" left: ");
        if (_node->left == NULL)
            printf("NONE");
        else
            printf("[%s] -> ", _node->left->key);
        printf(" right: ");
        if (_node->right == NULL)
            printf("None");
        else
            printf("[%s] -> ", _node->right->key);
        printf("\n");
        return _node;
    }
}