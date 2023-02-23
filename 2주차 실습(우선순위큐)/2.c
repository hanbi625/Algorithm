#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int* inPlaceInsertionSort(int*, int);
int main() {
	int* x = NULL;
	int n;

	scanf("%d", &n); //배열 크기 입력받기
	x = (int*)malloc(sizeof(int) * n); //크기가 n인 배열 동적할당하기
	for (int i = 0; i < n; i++)
		scanf("%d", &x[i]); //배열에 양의 정수 저장하기
	x = inPlaceInsertionSort(x, n); //제자리 정렬 함수(삽입정렬) 실행
	for (int i = 0; i < n; i++) //배열의 원소 출력
		printf(" %d", x[i]);

	return 0;
}
int* inPlaceInsertionSort(int* x, int n) {
	int i, j, tmp;

	for (i = 1; i < n; i++) { //앞부분을 정렬 상태로 유지 + 삽입 정렬
		tmp = x[i];
		j = i - 1;
		while ((j >= 0) && (x[j] > tmp)) {
			x[j + 1] = x[j];
			j--;
		}
		x[j + 1] = tmp;
	}

	return x;
}
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void inPlaceSelectionSort(int*, int);
void inPlaceInsertionSort(int*, int);
void reverseSort(int*, int);
int main() {
	int* A = NULL, * B = NULL;
	int n;

	scanf("%d", &n); //정수 n 입력
	A = (int*)malloc(sizeof(int) * n); //배열 A 동적할당
	B = (int*)malloc(sizeof(int) * n); //배열 B 동적할당

	srand(time(NULL)); //난수
	for (int i = 0; i < n; i++) { //난수로 배열 초기화
		A[i] = rand() % 100 + 1;
		B[i] = A[i];
	}
	//난수 데이터 정렬
	LARGE_INTEGER ticksPerSec;
	QueryPerformanceFrequency(&ticksPerSec);
    //A 시간 측정
	LARGE_INTEGER start_A, end_A, diff_A;
	QueryPerformanceCounter(&start_A);
	inPlaceSelectionSort(A, n);
	QueryPerformanceCounter(&end_A);
	diff_A.QuadPart = end_A.QuadPart - start_A.QuadPart;
	printf("%.12fms\n", ((double)diff_A.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
    //B 시간 측정 
	LARGE_INTEGER start_B, end_B, diff_B;
	QueryPerformanceCounter(&start_B);
	inPlaceInsertionSort(B, n);
	QueryPerformanceCounter(&end_B);
	diff_B.QuadPart = end_B.QuadPart - start_B.QuadPart;
	printf("%.12fms\n", ((double)diff_B.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


	return 0;
}
void inPlaceSelectionSort(int* x, int n) {
	int i, j, k, tmp;
	for (i = n - 1; i > 0; i--) { //뒷부분 정렬 상태 유지 (선택 정렬)
		k = 0;
		for (j = 0; j <= i; j++) {
			if (x[k] < x[j])
				k = j;
		}
		tmp = x[i];
		x[i] = x[k];
		x[k] = tmp;
	}
}
void inPlaceInsertionSort(int* x, int n) {
	int i, j, tmp;

	for (i = 1; i < n; i++) { //앞부분을 정렬 상태로 유지 (삽입 정렬)
		tmp = x[i];
		j = i - 1;
		while ((j >= 0) && (x[j] > tmp)) {
			x[j + 1] = x[j];
			j--;
		}
		x[j + 1] = tmp;
	}
}
void reverseSort(int* x, int n) {
	int i, j, k, tmp;
	for (i = n - 1; i > 0; i--) { //역순 정렬
		k = i;
		for (j = 0; j < i; j++) {
			if (x[k] > x[j])
				k = j;
		}
		tmp = x[k];
		x[k] = x[i];
		x[i] = tmp;
	}
}
삽입 정렬시 선택 정렬보다 시간이 빠르다

*/
