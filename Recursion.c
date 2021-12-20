#pragma warning(disable: 4996)
#include<stdio.h>

int binsearch(int arr[], int target, int low, int high) {
	if (low > high) return -1;
	int mid = (low + high) / 2;
	if (target == arr[mid]) return mid;
	else if (target < arr[mid]) return binsearch(arr,target, low, high = mid - 1);
	else return binsearch(arr, target, low = mid + 1, high);
}

int main(void) {

	int input;
	scanf("%d", &input);

	int arr[100] = { 0 };

	for (int i = 0; i < input; i++) scanf("%d", &arr[i]);

	int target;
	scanf("%d", &target);

	int index = binsearch(arr, target, 0, input - 1);

	if (index == -1) printf("½ÇÆĞ");
	else printf("%d", index+1);

	return 0;
}