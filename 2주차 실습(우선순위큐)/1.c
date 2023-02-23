#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int* inPlaceSelectionSort(int*, int);
int main() {
	int* x = NULL;
	int n;

	scanf("%d", &n); //배열 크기 입력받기
	x = (int*)malloc(sizeof(int) * n); //크기가 n인 배열 동적할당하기
	for (int i = 0; i < n; i++)
		scanf("%d", &x[i]); //배열에 양의 정수 저장하기
	x = inPlaceSelectionSort(x, n); //제자리 정렬 함수 실행
	for (int i = 0; i < n; i++) //배열의 원소 출력
		printf(" %d", x[i]);

	return 0;
}
int* inPlaceInsertionSort(int* x, int n) {
	int i, j, k, tmp;
	for (i = n - 1; i > 0; i--) { //뒷부분 정렬 상태 유지
		k = 0;
		for (j = 0; j <= i; j++) {
			if (x[k] < x[j])
				k = j;
		}
		tmp = x[i];
		x[i] = x[k];
		x[k] = tmp;
	}
	return x;
}
