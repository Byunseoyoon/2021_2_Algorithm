#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define n 8

void print(double arr[]) {
	for (int i = 0; i < n; i++)
		printf("%.3lf ", arr[i]);
	printf("\n");
}

//선택정렬
void selection_sort(double arr[]) {
	double min;
	int index;
	for (int i = 0; i < n; i++) { //작은값부터 차례로 정렬
		min = arr[i];
		index = i;
		for (int j = i + 1; j < n; j++) {
			if (min > arr[j]) {
				min = arr[j];
				index = j;
			}
		}
		double tmp = arr[i];  //swap
		arr[i] = arr[index];
		arr[index] = tmp;
	}
}

//버블정렬
void buble_sort(double arr[]) {
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {   //swap
				double tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

//삽입정렬
void insertion_sort(double arr[]) {
	double tmp;
	int j;
	for (int i = 1; i < n; i++) {
		tmp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > tmp; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

//합병정렬
void merge(double arr[], int left, int mid, int right) {
	double tmp[n];
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while (i <= mid) tmp[k++] = arr[i++]; //남아있는 값 복사
	while (j <= right) tmp[k++] = arr[j++];   //남아있는 값 복사
	for (int m = left; m <= right; m++) arr[m] = tmp[m];
}

void merge_sort(double arr[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

//퀵정렬
void quick_sort(double arr[], int left, int right) {
	int p;
	if (left < right) {
		p = partition(arr, left, right); //피벗기준
		quick_sort(arr, left, p - 1); //피벗기준 왼쪽
		quick_sort(arr, p + 1, right); //피벗기준 오른쪽
	}
}

int partition(double arr[], int left, int right) {
	int i = left, j = right, p = left;
	double tmp;

	while (i <= j) {
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
	return j; //피벗위치의 index 리턴
}

//힙정렬
void heapify(double arr[], int k) {
	for (int i = 1; i < k; i++) {
		int child = i;
		do {
			int root = (child - 1) / 2;
			if (arr[root] < arr[child]) {
				double tmp = arr[root];
				arr[root] = arr[child];
				arr[child] = tmp;
			}
			child = root;
		} while (child != 0);
	}
}

void heap_sort(double arr[]) {
	int size = n;
	for (int i = 0; i < n; ++i) {
		heapify(arr, size);
		double tmp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = tmp;
		--size;
	}
}

void rand_make(double arr[]) {
	srand(1000);
	for (int i = 0; i < n; i++) {
		arr[i] = (2 * ((double)rand() / RAND_MAX)) - 1;
	}

}

int main(void) {
	double arr[n];

	rand_make(arr);

	printf("<----선택정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	selection_sort(arr);
	printf("정렬 후 :");
	print(arr);

	rand_make(arr);

	printf("\n<----버블정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	buble_sort(arr);
	printf("정렬 후: ");
	print(arr);

	rand_make(arr);

	printf("\n<----삽입정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	insertion_sort(arr);
	printf("정렬 후: ");
	print(arr);

	rand_make(arr);

	printf("\n<----합병정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	merge_sort(arr, 0, n - 1);
	printf("정렬 후: ");
	print(arr);

	rand_make(arr);

	printf("\n<----퀵정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	quick_sort(arr, 0, n - 1);
	printf("정렬 후: ");
	print(arr);

	rand_make(arr);

	printf("\n<----힙정렬---->\n");
	printf("정렬 전: ");
	print(arr);
	heap_sort(arr);
	printf("정렬 후: ");
	print(arr);


	return 0;
}