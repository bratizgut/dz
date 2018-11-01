#include <stdio.h>

void swap(int i, int j, int arr[]){
	int c;
	c = arr[i];
	arr[i] = arr[j];
	a[j] = c;
}

void insert(int count, int arr[], int  N){
	a[i] = count;
	siftup(i);
}

void siftup(int i, int arr[]){
	while((i > 0) && (arr[(i - 1) div 2]) > arr[i]){
		swap(i, (i - 1) div 2, arr);
		i = (i - 1) div 2;
	}
}

int main() {
    unsigned int N;
    int count;
    scanf("%u", &N);
    int arr[N];
    scanf("%d",&arr[0] );
    for (int i = 1; i < N; i++){
        scanf("%d", &count);
		insert(count, arr, i);
    }
    return 0;
}
