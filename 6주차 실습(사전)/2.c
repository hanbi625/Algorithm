#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int findElement(int*, int, int);

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
int findElement(int* A, int n, int k) { 
	int a, b, mid;
	a = 0; //a에 처음 인덱스 저장
	b = n - 1; //b에 마지막 인덱스 저장
	while (a < b) { //a가 b보다 작을 동안 반복
		mid = (a + b) / 2; //mid에 a와 b의 중간값 저장
		if (k == A[mid]) //만약 k와 A[mid]의 값이 같다면 mid 반환
			return mid;
		else if (k < A[mid]) //k가 A[mid]보다 작으면 b를 mid로 저장후 다시 탐색
			b = mid ;
		else //그 외의 경우 a를 mid+1로 저장 후 다시 탐색
			a = mid + 1;
	}
	if (A[a] < k) //k보다 큰 사전의 키가 없으면 배열 크기 n 반환
		return n;
	return a;
}
