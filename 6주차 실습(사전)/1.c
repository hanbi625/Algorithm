#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int findElement(int*, int, int);
int rFE(int*, int, int, int);
int main() {
	int n, k;
	int* A = NULL;

	scanf("%d %d", &n, &k); //배열의 크기와 탐색할 키 k 입력받기
	A = (int*)malloc(sizeof(int) * n); //크기가 n인 배열 동적할당
	for (int i = 0; i < n; i++) //배열의 원소 입력받기
		scanf("%d", &A[i]);
	printf("%d\n", findElement(A, n, k)); //k의 위치 출력하기

	if (A != NULL) //A 해제 후 NULL 삽입
		free(A);
	A = NULL;
	return 0;
}
int findElement(int* A, int n, int k) { //재귀버전의 이진탐색
	return rFE(A, k, 0, n - 1);
}
int rFE(int *A, int k, int l, int r) {
	int mid = r; //mid 값 r(가장 큰 값)로 초기화
	if (l > r) return r; //값이 없으면 r 반환
	mid = (l + r) / 2; //mid에 l과 r의 중간값 저장
	if (k == A[mid]) //만약 k가 A[mid]와 같으면 mid가 k의 위치임
		return mid;
	else if (k < A[mid]) //만약 k가 A[mid]보다 작으면 mid보다 작은 부분 탐색
		return rFE(A, k, l, mid - 1);
	else //그외의 경우 mid보다 큰 부분 탐색
		return rFE(A, k, mid + 1, r);
}
