#include<stdio.h>
#define n 8

void print(int arr[]) {
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

//��������
void selection_sort(int arr[]) { 
	int min, index;
	for (int i = 0; i < n; i++) { //���������� ���ʷ� ����
		min = arr[i];
		index = i;
		for (int j = i + 1; j < n; j++) {
			if (min > arr[j]) {
				min = arr[j];
				index = j;
			}
		}
		int tmp = arr[i];  //swap
		arr[i] = arr[index];
		arr[index] = tmp;
		print(arr);
	}
}

//��������
void buble_sort(int arr[]) { 
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {   //swap
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			print(arr);
		}
	}
}

//��������
void insertion_sort(int arr[]) { 
	int tmp, j;
	for (int i = 1; i < n; i++) {
		tmp = arr[i];
		for (j = i; j > 0 && arr[j-1]>tmp; j--) {
				arr[j] = arr[j-1];
		}
		arr[j] = tmp;
		print(arr);
	}
}

//�պ�����
void merge(int arr[], int left, int mid, int right) { 
	int tmp[n] = {0};
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while (i <= mid) tmp[k++] = arr[i++]; //�����ִ� �� ����
	while (j <= right) tmp[k++] = arr[j++];   //�����ִ� �� ����
	for (int m = left; m <= right; m++) arr[m] = tmp[m];
	print(arr);
}

void merge_sort(int arr[], int left, int right) { 
	int mid;
	if (left < right) {
		mid = (left+right)/2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

//������
void quick_sort(int arr[], int left, int right) { 
	int p;
	if (left < right) {
		p = partition(arr, left, right); //�ǹ�����
		quick_sort(arr, left, p-1); //�ǹ����� ����
		quick_sort(arr, p+1, right); //�ǹ����� ������
	}
}

int partition(int arr[], int left, int right) {
	int i = left, j = right, tmp;
	int p = left;

	while (i<= j){
		while (i <= right && arr[i] <= arr[p]) i++;
		while (j > left && arr[j] >= arr[p]) j--;

		if (i > j) {
			tmp = arr[j];
			arr[j] = arr[p];
			arr[p] = tmp;
		}
		else {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	print(arr);
	return j;
}

//������
void heapify(int arr[], int k) {
	for (int i = 1; i < k; i++) {
		int child = i; 
		do {
			int root = (child - 1) / 2;
			if (arr[root] < arr[child]) {
				int tmp = arr[root];
				arr[root] = arr[child];
				arr[child] = tmp;
			}
			child = root;
		} while (child!=0);
	}
}

void heap_sort(int arr[]) {
	int size = n;
	for (int i = 0; i < n; ++i) {
		heapify(arr, size);
		
		print(arr);

		int tmp = arr[0];
		arr[0] = arr[size-1];
		arr[size-1] = tmp;
		--size;
	}
}


int main(void) {
	printf("��������\n");
	int arr1[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	selection_sort(arr1);
	printf("���: ");
	print(arr1);

	printf("\n��������\n");
	int arr2[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	buble_sort(arr2);
	printf("���: ");
	print(arr2);

	printf("\n��������\n");
	int arr3[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	insertion_sort(arr3);
	printf("���: ");
	print(arr3);

	printf("\n�պ�����\n");
	int arr4[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	merge_sort(arr4, 0, n-1);
	printf("���: ");
	print(arr4);

	printf("\n������\n");
	int arr5[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	quick_sort(arr5,0,n-1);
	printf("���: ");
	print(arr5);

	printf("\n������\n");
	int arr6[n] = { 12, 30, 21, 55, 25, 72, 45, 50 };
	heap_sort(arr6);
	printf("���: ");
	print(arr5);


	return 0;
}