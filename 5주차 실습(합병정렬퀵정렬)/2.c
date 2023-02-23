#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void swap(int*, int*);
int findPivot(int*, int, int);
int inPlacePartition(int*, int, int, int);
void inPlaceQuickSort(int*, int, int);
int main() {
	int* L, n;

	scanf("%d", &n); //배열의 원소 개수 입력받기
	L = (int*)malloc(sizeof(int) * n); //크기가 n인 배열 동적할당
	for (int i = 0; i < n; i++)
		scanf("%d", &L[i]); //배열의 원소 입력받기
	inPlaceQuickSort(L, 0, n - 1); //제자리 퀵정렬 함수 실행
	for (int i = 0; i < n; i++)
		printf(" %d", L[i]); //정렬 후 배열의 원소 출력
	

	return 0;
}
void swap(int* a, int *b) { //두 변수의 값 바꾸는 함수
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int findPivot(int* L, int l, int r) { //부리스트의 수들 중 1개의 위치 무작위로 선택
	int p;
	srand(time(NULL));
	p = rand() % (r + 1 - l) + l; //pivot위치 정하기
	return p; //피봇 반환
}
int inPlacePartition(int* L, int l, int r, int k) {
	int p, i, j;
	p = L[k]; //피봇 정하기
	swap(&L[k], &L[r]); //피봇 숨기기
	i = l; //i에 l저장
	j = r - 1; //j에 r-1 저장
	while (i <= j) { //i가 j보다 작거나 같은 경우 반복
		while (i <= j && L[i] <= p) //L[i]가 피봇보다 작거나 같으면
			i++; //i증가(LQ 저장)
		while (j >= i && L[j] >= p) //L[i]가 피봇보다 크거나 같으면
			j--; //j증가(GT 저장)
		if (i < j) { //i가 j보다 작으면
			swap(&L[i], &L[j]); //L[i]와 L[j] 바꾸기
		}
	}
	swap(&L[i], &L[r]); //L[i]와 L[r]바꿔서 피봇 대체하기
	return i; //피봇의 위치 반환
}
void inPlaceQuickSort(int* L, int l, int r) {
	int a;
	if (l < r) { //베이스케이스(l이 r보다 작을때)
		int k = findPivot(L, l, r); //l과 r사이의 피봇 반환
		a = inPlacePartition(L, l, r, k); 
		inPlaceQuickSort(L, l, a - 1); //l부터 a-1까지의 원소 재귀함수 통해 정렬
		inPlaceQuickSort(L, a + 1, r); //a+1부터 r까지의 원소 재귀함수 통해 정렬
	}
}
